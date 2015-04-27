#ifndef _ImagePreLim_H
#define _ImagePreLim_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>

#include "Param.h"
#include "trans/Image2TriMesh.h"

using namespace std;

class ImagePreLim: public ParamMap {
private:
	string outputFolderName;
	string inputFolderName;

	string imageFileName;
	int nRows;
	int nCols;

	int doSubDivide;

public:
	ImagePreLim(char *name);
	void ReadImage(vector<vector<Vertex> > &image);

private:
	void ReadCSVimage(string fileName, vector<int> &array);

};

#endif
