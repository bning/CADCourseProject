#include "trans/Image2TriMesh.h"
#include "prelim/ImagePreLim.h"

int main(int argc, char* argv[])
{
	ImagePreLim imagePreLim(argv[1]);
	Image2TriMesh_2D i2t;

	string fn1(" "), fn2(" ");
	vector<vector<Vertex> > pts;
	i2t.ReadImage(fn1,pts);
	i2t.QuadTreeSub();
	i2t.MeshGenerator();
	i2t.WriteTriMesh(fn2);
	return 0;
}
