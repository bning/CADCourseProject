#ifndef IMAGE_2_TRI_MESH_H
#define IMAGE_2_TRI_MESH_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Vertex {
public:
	Vertex();
	double x[2]; //coordinates of vertex
	int val; //image data, 0 or 1
	bool operator==(const Vertex&);
	Vertex operator+(const Vertex&);
	Vertex operator-(const Vertex&);
	Vertex operator/(const double&);
	Vertex operator*(const double&);
};

class Triangle {
public:
	int id[3]; //counter-clockwise store IDs of thress vertcies of a triangle
};

class Cell {
public:
	int corner[4]; //store ID of four corner points of a cell
	int hang[4]; //if a edge of a cell contains a hanging node, store its ID, otherwise store -1
};

class Image2TriMesh_2D {
public:
	void SetProblem(const vector<vector<Vertex> >& pts);
	void ReadImage(string fn, vector<vector<Vertex> >& pts); //nx by ny points
	void WriteTriMesh(string fn); //depend on which format we want to use

	void QuadTreeSub();

	void MeshGenerator(); //1 to mesh material, 0 to mesh air, 2 to mesh both together

	//int ResolveAmbuity();
	//void BoundaryCellSplit(const Cell& cl);
	//void InteriorCellSplit(const Cell& cl);
	void UniformMeshGenerator();
	void AdaptiveMeshGenerator();
	int FindCase(Cell& cl);        //case 0-5
	void AppendVertex(const Cell& cl, int cid[4]);
	void Case1(const Cell& cl);        //four solid vertices
	void Case2(const Cell& cl);        //three solid vertices
	void Case3(const Cell& cl);        //two solid vertices one side
	void Case4(const Cell& cl);        //two solid vertices diagonal
	void Case5(const Cell& cl);        //one solid vertex
	void Case1_adap(Cell& cl);
	int FindCaseAdap(Cell& cl);
	void AppendHandingNode(const Cell& cl, int hid[4]);
	void Case1_1(const Cell& cl);        //one handing node
	void Case1_2(const Cell& cl);        //two handing nodes, next to
	void Case1_3(const Cell& cl);        //two handing nodes, opposite to
	void Case1_4(const Cell& cl);        //three handing nodes
	void Case1_5(const Cell& cl);        //four handing nodes

//private:
	vector<Vertex> cellpts;
	vector<Cell> cells;
	vector<Vertex> tripts;
	vector<Triangle> trimesh;
};

#endif
