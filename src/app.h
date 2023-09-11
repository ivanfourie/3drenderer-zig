#ifndef APP_H
#define APP_H

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
#include "camera.h"
#include "triangle.h"
#include "texture.h"
#include "mesh.h"
#include "clipping.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

//
// Global variables for execution status and game loop
//
extern bool is_running;
extern int previous_frame_time;
extern float delta_time;
extern bool is_autorotate;
extern float rotation_rate;
extern float rotation_increment;

//
// Array of triangles that should be rendered frame by frame
//
#define MAX_TRIANGLES_PER_MESH 10000
extern triangle_t triangles_to_render[MAX_TRIANGLES_PER_MESH];
extern int num_triangles_to_render;

//
// Declaration of global transformation matrices
//
extern mat4_t world_matrix;
extern mat4_t proj_matrix;
extern mat4_t view_matrix; 

//
// Functions
//
void setup(void);
void process_input(void);
void update(void);
void render(void);
void free_resources(void);

#endif
