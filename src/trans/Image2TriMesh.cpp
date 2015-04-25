#include "Image2TriMesh.h"

void Image2TriMesh_2D::ReadImage(string fn, vector<vector<Vertex> >& pts)
{
	//input: Image data, e.g. .txt file
	//output: point coordinates, point values
}

void Image2TriMesh_2D::WriteTriMesh(string fn)
{
	//input: point coordinates, connectivity of points that define triangles
	//output: .stl file
}

void Image2TriMesh_2D::QuadTreeSub()
{
	//input: image data from ReadImage()
	//output: quad tree struture, each edge of a cell at most have one hanging node; see Class Cell
}

void Image2TriMesh_2D::MeshGenerator()
{
	//input: quad tree struture from QuadTreeSub()
	//output: triangles
}