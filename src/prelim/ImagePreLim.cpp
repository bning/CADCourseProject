#include "ImagePreLim.h"

ImagePreLim::ImagePreLim(char *name) : ParamMap(name)
{
	outputFolderName = getStringParam("outputFolderName");
	inputFolderName = getStringParam("inputFolderName");

	imageFileName = getStringParam("imageFileName");
	nRows = getIntParam("imageRows");
	nCols = getIntParam("imageRows");

	doSubDivide = getIntParam("doSubDivide");	
}

void ImagePreLim::ReadImage(vector<vector<Vertex> > &image)
{
	string finalImageFileName;
	finalImageFileName.assign(inputFolderName);
	finalImageFileName.append(imageFileName);

	
}

void ImagePreLim::ReadCSVimage(string fileName, vector<int> &array)
{
	char finalName[200];
	strcpy(finalName,fileName.c_str());

	ifstream fileStream(finalName);
	string numStr;
	int number = 0;
	int ind = 0;

	while (getline(fileStream, numStr, ','))
	{
		//cout << numStr << endl;
		istringstream convert(numStr);
		convert >> number;
		//cout << number << endl;
		array.at(ind) = number;
		ind++;
	}	
}
