#include "ImagePreLim.h"

ImagePreLim::ImagePreLim(char *name) :
		ParamMap(name) {
	outputFolderName = getStringParam("outputFolderName");
	inputFolderName = getStringParam("inputFolderName");

	imageFileName = getStringParam("imageFileName");
	nRows = getIntParam("imageRows");
	nCols = getIntParam("imageCols");

	doSubDivide = getIntParam("doSubDivide");
}

void ImagePreLim::ReadImage(vector<vector<Vertex> > &image) {
	//-----> x coordinate
	//-
	//-
	//-
	//y coordinate (meaning x is horizontally, y is vertically)

	//vertex.x[0] = x coordinate
	//vertex.x[1] = y coordinate

	image.resize(nRows);

	string finalImageFileName;
	finalImageFileName.assign(inputFolderName);
	finalImageFileName.append(imageFileName);

	vector<int> array(nRows * nCols);
	ReadCSVimage(finalImageFileName, array);
	Vertex newVertex;
	for (int rowI = 0; rowI < nRows; rowI++) {
		vector<Vertex> vertexRow(nCols);
		for (int colI = 0; colI < nCols; colI++) {
			int vecIndex = rowI * nCols + colI;
			newVertex.val = array.at(vecIndex);
			newVertex.x[0] = colI;
			newVertex.x[1] = rowI;

			vertexRow.at(colI) = newVertex;
		}
		image.at(rowI) = vertexRow;
	}
}

void ImagePreLim::ReadCSVimage(string fileName, vector<int> &array) {
	char finalName[200];
	strcpy(finalName, fileName.c_str());

	ifstream fileStream(finalName);
	string numStr;
	int number = 0;
	int ind = 0;

	while (getline(fileStream, numStr, ',')) {
		//cout << numStr << endl;
		istringstream convert(numStr);
		convert >> number;
		//cout << number << endl;
		array.at(ind) = number;
		ind++;
	}
}
