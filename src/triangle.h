#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

// Stores vertex index
typedef struct {
	int a;
	int b;
	int c;
} face_t;

// Stores the actual vec2 point of the triangle in the screen
typedef struct {
	vec2_t points[3];
} triangle_t;

#endif