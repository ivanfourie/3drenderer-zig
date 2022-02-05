#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define SDL_DISABLE_IMMINTRIN_H
#include <SDL.h>
#include "upng.h"
#include "array.h"
#include "display.h"
#include "vector.h"
#include "light.h"
#include "matrix.h"
#include "triangle.h"
#include "texture.h"
#include "mesh.h"


#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

//
// Array of triangles that should be rendered frame by frame
//
triangle_t* triangles_to_render = NULL;

vec3_t camera_position = { .x = 0, .y = 0, .z = 0 };
mat4_t proj_matrix;

//
// Global variables for execution status and game loop
//
bool is_running = false;
int previous_frame_time = 0;

bool is_autorotate = true;
float rotation_rate = 0.05;
float rotation_increment = 0.01;

//
// Setup function to initialise variables and game objects
//
void setup(void) {
    // Initialize render mode and triangle culling method
    render_method = RENDER_TEXTURED;
    cull_method = CULL_BACKFACE;
    
    // Allocate the required memory in bytes for the color and z buffers
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
    z_buffer = (float*) malloc(sizeof(float) * window_width * window_height);

    // Creating a SDL texture that is used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );

    // Inititialize the perspective projection matrix
    float fov = M_PI / 3.0; // in radians - the same as 180 / 3 or 60 degrees
    float aspect = (float) window_height / window_width;
    float znear = 0.1;
    float zfar = 100.0;
    proj_matrix = mat4_make_perspective(fov, aspect, znear, zfar);

    // Loads the cube values in the mesh data structure
    // load_cube_mesh_data();
    load_obj_file_data("./assets/f117.obj");

    // Load texture information from an external PNG file
    load_png_texture_data("./assets/f117.png");
}

//
// Poll system events and handle keyboard input
//
void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT: 
            is_running = false;
            break;
        case SDL_KEYDOWN:
            // Handle key strokes
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    is_running = false;
                    break;
                case SDLK_1:
                    // Display the wireframe and a small red dot for each triangle vertex
                    printf("Mode: Show the wireframe and a small red dot for each triangle vertex.\n");
                    render_method = RENDER_WIRE_VERTEX;
                    break;
                case SDLK_2:
                    // Display only the wireframe lines
                    printf("Mode: Show only the wireframe lines.\n");
                    render_method = RENDER_WIRE;
                    break;
                case SDLK_3:
                    // Display filled triangles with a solid color
                    printf("Mode: Show filled triangles with a solid color.\n");
                    render_method = RENDER_FILL_TRIANGLE;
                    break;
                case SDLK_4:
                    // Display both filled triangles and wireframe lines
                    printf("Mode: Show both filled triangles and wireframe lines.\n");
                    render_method = RENDER_FILL_TRIANGLE_WIRE;
                    break;
                case SDLK_5:
                    // Display both filled triangles and wireframe lines
                    printf("Mode: Show textured triangles.\n");
                    render_method = RENDER_TEXTURED;
                    break;
                case SDLK_6:
                    // Display both filled triangles and wireframe lines
                    printf("Mode: Show textured triangles with a wireframe.\n");
                    render_method = RENDER_TEXTURE_WIRE;
                    break;
                case SDLK_c:
                    // Toggle back-face culling
                    if (cull_method == CULL_BACKFACE) {
                        cull_method = CULL_NONE;
                    } else {
                        cull_method = CULL_BACKFACE;
                    }
                    printf("Mode: Back-face culling %s.\n", cull_method == CULL_BACKFACE ? "on" : "off");
                    
                    break;
                case SDLK_r:
                    // Toggle autorotation
                    is_autorotate = !is_autorotate;
                    printf("Mode: Automatic rotation is %s.\n", is_autorotate ? "on" : "off");
                    break;
                case SDLK_UP:
                    // Rotate up
                    mesh.rotation.x -= rotation_rate;
                    break;
                case SDLK_DOWN:
                    // Rotate down
                    mesh.rotation.x += rotation_rate;
                    break;
                case SDLK_LEFT:
                    // Rotate left
                    mesh.rotation.y -= rotation_rate;
                    break;
                case SDLK_RIGHT:
                    // Rotate right
                    mesh.rotation.y += rotation_rate;
                    break;
                case SDLK_PERIOD:
                    // Increase rotation rate
                    rotation_rate += rotation_increment;
                    printf("Rotation increased to %f.\n", rotation_rate);
                    break;
                case SDLK_COMMA:
                    // Decrease rotation rate
                    rotation_rate -= rotation_increment;
                    printf("Rotation decreased to %f.\n", rotation_rate);
                    break;
            }
            break;
    }
}

//
// Update function frame by frame with a fixed time step
//
void update(void) {
    // Wait some time until we reach the target frame time in milliseconds
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);
    
    // Only delay execution if we are running too fast
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }
    
    previous_frame_time = SDL_GetTicks();

    // Initialise array of triangles to render
    triangles_to_render = NULL;
    

    // Change the mesh scale, rotation & translation values per animation frame
    if (is_autorotate) {
        mesh.rotation.x -= rotation_rate;
        //mesh.rotation.y += 0.008;
        //mesh.rotation.z += 0.01;
    }
    mesh.translation.z = 5.0;

    // Create a scale matrix, rotation and translation that will be used to multiply the mesh vertices 
    mat4_t scale_matrix = mat4_make_scale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
    mat4_t translation_matrix = mat4_make_translation(mesh.translation.x, mesh.translation.y, mesh.translation.z);
    mat4_t rotation_matrix_x = mat4_make_rotation_x(mesh.rotation.x);
    mat4_t rotation_matrix_y = mat4_make_rotation_y(mesh.rotation.y);
    mat4_t rotation_matrix_z = mat4_make_rotation_z(mesh.rotation.z);
    
    // Loop all triangle faces of our mesh
    int num_faces = array_length(mesh.faces);
    for (int i = 0; i < num_faces; i++) {
        face_t mesh_face = mesh.faces[i];
        
        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.a];
        face_vertices[1] = mesh.vertices[mesh_face.b];
        face_vertices[2] = mesh.vertices[mesh_face.c];

        vec4_t transformed_vertices[3];

        // Loop all three vertices of this current face and apply transformations
        for (int j = 0; j < 3; j++) {
            vec4_t transformed_vertex = vec4_from_vec3(face_vertices[j]);

            // Create a World Matrix cominging scale, rptatopm amd translation matrices
            mat4_t world_matrix = mat4_identity(); // Start with the eye/identity matix
            // Order matters: First scale, then rotate, then translate. [T]*[R]*[S]*v

            // #1 Scale
            world_matrix = mat4_mul_mat4(scale_matrix, world_matrix);
            // #2 Rotate
            world_matrix = mat4_mul_mat4(rotation_matrix_z, world_matrix);
            world_matrix = mat4_mul_mat4(rotation_matrix_y, world_matrix);
            world_matrix = mat4_mul_mat4(rotation_matrix_x, world_matrix);
            // #3 Translate
            world_matrix = mat4_mul_mat4(translation_matrix, world_matrix);

            // Multiply the wolrd matrix by the original vector
            transformed_vertex = mat4_mul_vec4(world_matrix, transformed_vertex);

            // Save transformed vertex in the array of transformed vertices
            transformed_vertices[j] = transformed_vertex;
        }
        
        
        // Get individual vectors from A, B and C vertices to compute normal
        vec3_t vector_a = vec3_from_vec4(transformed_vertices[0]); /*   A   */
        vec3_t vector_b = vec3_from_vec4(transformed_vertices[1]); /*  / \  */
        vec3_t vector_c = vec3_from_vec4(transformed_vertices[2]); /* C---B */

        // Get the vector subtraction (B-A) and (C-A)
        vec3_t vector_ab = vec3_sub(vector_b, vector_a);
        vec3_t vector_ac = vec3_sub(vector_c, vector_a);
        // Normalize to normal vectors
        vec3_normalize(&vector_ab);
        vec3_normalize(&vector_ac);

        // Compute the face normal (using cross product to find perpendicular)
        // because the coordinate system is left handed the cross product will (AB cross CA)
        vec3_t normal = vec3_cross(vector_ab, vector_ac);

        // Normalize the face normal vector
        vec3_normalize(&normal);

        // Find the the vector between a point in the triangle and the camera origin
        vec3_t camera_ray = vec3_sub(camera_position, vector_a);

        // Calculate how aligned the camera ray is with the dot normal (using dot product)
        float dot_normal_camera = vec3_dot(normal, camera_ray);

        // Backface culling test to see if the current face should be projected
        if (cull_method == CULL_BACKFACE) {
            // Bypass triangle that are looking away from the camera
            if (dot_normal_camera < 0)
                continue;
        }
            
        vec4_t projected_points[3];

        // Loop all three vertices to perform the projection
        for (int j = 0; j < 3; j++) {
            // Project the current vertex
            projected_points[j] = mat4_mul_vec4_project(proj_matrix, transformed_vertices[j]);

            // Flip vertically since the y values of the 3D mesh grow bottom->up and in screen space y values grow top->down
            projected_points[j].y *= -1;

            // Scale into the view
            projected_points[j].x *= window_width / 2.0;
            projected_points[j].y *= window_height / 2.0;

            // Translate the projected point to the middle of the screen
            projected_points[j].x += (window_width / 2.0);
            projected_points[j].y += (window_height / 2.0);

        }

        // Calculate the average depth for each face based on the vertices after transformation
        float avg_depth = (transformed_vertices[0].z + transformed_vertices[1].z + transformed_vertices[2].z) / 3.0;

        // Calculate the shade intensity based on how alighen the face normal and the inverse of the light ray
        float light_intensity_factor = -vec3_dot(normal, light.direction);

        // Calculate the color based on the light angle
        uint32_t triangle_color = light_apply_intensity(mesh_face.color, light_intensity_factor);

        triangle_t projected_triangle = {
            .points = {
                { projected_points[0].x, projected_points[0].y, projected_points[0].z, projected_points[0].w },
                { projected_points[1].x, projected_points[1].y, projected_points[1].z, projected_points[1].w },
                { projected_points[2].x, projected_points[2].y, projected_points[2].z, projected_points[2].w }
            },
            .texcoords = {
                { mesh_face.a_uv.u, mesh_face.a_uv.v },
                { mesh_face.b_uv.u, mesh_face.b_uv.v },
                { mesh_face.c_uv.u, mesh_face.c_uv.v }
            },
            .color = triangle_color,
            .avg_depth = avg_depth
        };
       
        // Save the projected triangle in the array of triangles to render
        array_push(triangles_to_render, projected_triangle);
    }
}



//
// Render function to draw objects on the display 
//
void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_grid();

    // Loop all projected triangles and render them
    int num_triangles = array_length(triangles_to_render);
    for (int i = 0; i < num_triangles; i++) {
        triangle_t triangle = triangles_to_render[i];
        
        // Draw vertex points
        if (render_method == RENDER_WIRE_VERTEX) {
            draw_rect(triangle.points[0].x - 3, triangle.points[0].y - 3, 6, 6, 0xFFFF0000); // vertex A
            draw_rect(triangle.points[1].x - 3, triangle.points[1].y - 3, 6, 6, 0xFFFF0000); // vertex B
            draw_rect(triangle.points[2].x - 3, triangle.points[2].y - 3, 6, 6, 0xFFFF0000); // vertex C
        }

        // Draw filled triangle
        if (render_method == RENDER_FILL_TRIANGLE || render_method == RENDER_FILL_TRIANGLE_WIRE) {
            draw_filled_triangle(
                triangle.points[0].x, triangle.points[0].y, // vertex A
                triangle.points[1].x, triangle.points[1].y, // vertex B
                triangle.points[2].x, triangle.points[2].y, // vertex C
                triangle.color
            );
        }

        // Draw textured triangle
        if (render_method == RENDER_TEXTURED || render_method == RENDER_TEXTURE_WIRE) {
            draw_textured_triangle(
                triangle.points[0].x, triangle.points[0].y, triangle.points[0].z, triangle.points[0].w, triangle.texcoords[0].u, triangle.texcoords[0].v, // vertex A
                triangle.points[1].x, triangle.points[1].y, triangle.points[1].z, triangle.points[1].w, triangle.texcoords[1].u, triangle.texcoords[1].v, // vertex B
                triangle.points[2].x, triangle.points[2].y, triangle.points[2].z, triangle.points[2].w, triangle.texcoords[2].u, triangle.texcoords[2].v, // vertex C
                mesh_texture
            );
        }

        // Draw unfilled triangle
        if (    render_method == RENDER_WIRE 
            ||  render_method == RENDER_WIRE_VERTEX 
            ||  render_method == RENDER_FILL_TRIANGLE_WIRE
            ||  render_method == RENDER_TEXTURE_WIRE
            ) {
            draw_triangle(
                triangle.points[0].x, triangle.points[0].y, // vertex A
                triangle.points[1].x, triangle.points[1].y, // vertex B
                triangle.points[2].x, triangle.points[2].y, // vertex C
                0xFFFFFFFF
            );
        }

    }
    
    // Clear the array of triangles to render
    array_free(triangles_to_render);

    render_color_buffer();
    clear_color_buffer(0xFF000000);
    clear_z_buffer();

    SDL_RenderPresent(renderer);
}

//
// Free the memory that was dynamically allocated by the program
//
void free_resources(void) {
    free(color_buffer);
    free(z_buffer);
    upng_free(png_texture);
    array_free(mesh.faces);
    array_free(mesh.vertices);
}

//
// Main function
//
int main(int argc, char* args[]) {
    
    // Create a SDL window
    is_running = initialize_window();

    setup();

    // Event loop
    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();
    free_resources();

    return 0;
}
