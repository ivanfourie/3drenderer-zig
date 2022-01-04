#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int window_width = 1920;
int window_height = 1080;

// Delcare a pointer to an array of uint32 elments
uint32_t* color_buffer = NULL;

// SDL Texture
SDL_Texture* color_buffer_texture = NULL;

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    };

    // Use SDL to find out max. width and height for fullscreen
    // Does not work so well with WSL2 + XLaunch (VCXSRV)
    // SDL_DisplayMode display_mode;
    // SDL_GetCurrentDisplayMode(0, &display_mode);

    // window_width = display_mode.w;
    // window_height = display_mode.h;

    // Create a SDL Window
    window = SDL_CreateWindow(
            NULL, 
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            window_width,
            window_height,
            SDL_WINDOW_SHOWN
    );
    
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");   
        return false;
    }
    
    // Create a SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    // Crashes on WSL :(
    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void draw_grid(void) {
    // Draw a background grid that fills the entire window.
    // Lines should be rendedered at every row/col multiple of 10.
    int grid_size = 10;
    uint32_t grid_color = 0xFF444444;

    for (int y = 0; y < window_height; y+=grid_size) {
        for (int x = 0; x < window_width; x+=grid_size) {
            color_buffer[(window_width * y) + x] = grid_color;
        }
    }
}

void draw_pixel(int x, int y, uint32_t color) {
    if (x < window_width && y < window_height) {
        color_buffer[(window_width * y) + x] = color;
    }
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t color) {
    // Use Digital Differential Analyzer line drawing algorythm to draw a line

    int delta_x = (x1 - x0); // run
    int delta_y = (y1 - y0); // rise 

    // Find the the longest side lenght to iterate
    // Sometimes delta_y is greate than delta_x meaning we need to run the total delta_y side length instead of of delta_x
    int longest_side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

    // Find how much we should increment in both x and y
    float x_inc = delta_x / (float)longest_side_length;
    float y_inc = delta_y / (float)longest_side_length;

    float current_x = x0;
    float current_y = y0;

    for (int i = 0; i <= longest_side_length; i++) {
        draw_pixel(round(current_x), round(current_y), color);
        current_x += x_inc;
        current_y += y_inc;
    }
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int current_x = x + i;
            int current_y = y + j;
            draw_pixel(current_x, current_y, color);
        }
    }
}

void render_color_buffer(void) {
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int) (window_width * sizeof(uint32_t))
    );
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
    
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            color_buffer[(window_width * y) + x] = color;
        }
    }    
}

void destroy_window(void) {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
