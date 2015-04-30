#ifndef _ImagePreLim_H
#define _ImagePreLim_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <queue>

#include "Param.h"
#include "trans/Image2TriMesh.h"

using namespace std;

class Node {
public:
	int val;
	bool isLeafNode;
	vector<Node*> childrenNode;
	Node* parentNode;
	int noChildren;

	int nodeOrder;
	int nodeDepth;

	int nodeRows;
	int nodeCols;
	int startRow;
	int startCol;

	bool isHanging[4]; //        0| _ |2

public:
	Node(int a_startRow, int a_startCol, int a_nodeRows, int a_nodeCols);

	void SplitQuadNode(list<Node> &allElements, vector<vector<Vertex> > &image,
			bool doSplit);
	void RemoveHangingPoint(list<Node> &allElements,
			vector<vector<Vertex> > &image);
	void CloseSiblingHangingPoint();
};

class ImagePreLim: public ParamMap {
private:
	string outputFolderName;
	string inputFolderName;

	string imageFileName;
	int nRows;
	int nCols;

	int doSubDivide;
	string testSubImageFileName;

public:
	ImagePreLim(char *name);
	void ReadImage(vector<vector<Vertex> > &image);
	void UnderSampleImage(vector<vector<Vertex> >& image, int uSfactor,
			vector<vector<Vertex> >& uSimage);

	void SubDivide(vector<vector<Vertex> > &image, vector<Cell> &quadTree,
			int* cellCount);

	string getOutputFolderName();
	string getInputFolderName();
	string getImageFileName();

private:
	void ReadCSVimage(string fileName, vector<int> &array);

	void ConvertTreeToCellStructure(Node* motherNode, vector<Cell> &quadTree,
			int* cellCount);
	void WriteTestSubCSVImage(vector<int> &reWriteSubImage, int wSize,
			int hSize, string testSubImageFileName);
	void TestCellIntoSubImage(vector<Cell> &quadTree, vector<int> &subImage,
			int valCellCount);
};

#endif
