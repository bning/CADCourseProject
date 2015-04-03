/*
 * Mesh.h
 *
 *  Created on: Apr 2, 2015
 *      Author: bo
 */
#include <vector>
#include "Vector2.h"
#include "Vector3.h"

#ifndef MESH_H_
#define MESH_H_

struct MeshVertex {
	Vector2 position;
	Vector3 color;
	MeshVertex() {
		position = Vector2(0.0, 0.0);
		color = Vector3(0.0, 0.0, 0.0);
	}
};

struct MeshTriangle {
	unsigned int vertexInd[3];
};

class Mesh {
public:
	typedef std::vector<MeshTriangle> MeshTriangleList;
	typedef std::vector<MeshVertex> MeshVertexList;

	MeshTriangleList triangles;
	MeshVertexList vertices;

	bool writeSTLFile();
	bool writeWRLFile();

};

#endif /* MESH_H_ */
