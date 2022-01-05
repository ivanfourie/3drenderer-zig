#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define M_CUBE_VERTICES 8
#define M_CUBE_FACES (6 * 2) // 6 cube faces, 2 traingles per face

extern vec3_t cube_vertices[M_CUBE_VERTICES];
extern face_t cube_faces[M_CUBE_FACES];

// Define a struct for dynamic size meshes
typedef struct {
	vec3_t* vertices;	// dynamic array of vertices
	face_t* faces;		// dynamic array of faces
	vec3_t rotation;	// rotation with x, y, z values
} mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data(void);
void load_obj_file_data(char* filename);

#endif
