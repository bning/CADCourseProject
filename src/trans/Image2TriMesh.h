#ifndef IMAGE_2_TRI_MESH_H
#define IMAGE_2_TRI_MESH_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Vertex {
public:
	double x[2]; //coordinates of vertex
	int val; //image data, 0 or 1
};

class Triangle {
public:
	int id[3]; //counter-clockwise store IDs of thress vertcies of a triangle
	Triangle(int x, int y, int z) {
		id[0] = x;
		id[1] = y;
		id[2] = z;
	}
};

class Cell {
public:
	int corner[4]; //store ID of four corner points of a cell
	int hang[4]; //if a edge of a cell contains a hanging node, store its ID, otherwise store -1
};

class Image2TriMesh_2D {
public:
	void ReadImage(string fn, vector<vector<Vertex> >& pts); //nx by ny points
	void WriteTriMesh(string fn); //depend on which format we want to use

	void QuadTreeSub();

	void MeshGenerator(); //1 to mesh material, 0 to mesh air, 2 to mesh both together

	//void LookupTable();//build 16 cases
	//void Quad2Tri();
	//int ResolveAmbuity();

private:
	vector<Vertex> vertex;
	vector<Triangle> trimesh;
};

#endif
