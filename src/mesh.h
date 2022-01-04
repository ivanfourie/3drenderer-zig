#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define M_MESH_VERTICES 8
extern vec3_t mesh_vertices[M_MESH_VERTICES];

#define M_MESH_FACES (6 * 2) // 6 cube faces, 2 traingles per face
extern face_t mesh_faces[M_MESH_FACES];

#endif
