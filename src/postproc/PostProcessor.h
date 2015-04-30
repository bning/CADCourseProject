/*
 * PostProcessor.h
 *
 *  Created on: Apr 27, 2015
 *      Author: bo
 */

#ifndef SRC_POSTPROC_POSTPROCESSOR_H_
#define SRC_POSTPROC_POSTPROCESSOR_H_

#include <vector>
#include <string>
#include <fstream>
#include "util/Vector3.h"
#include "trans/Image2TriMesh.h"

using namespace std;

class Vertex;
class Triangle;
class Cell;

class PostProcessor {
private:
	vector< vector<Vertex> >* imgPtr;
	vector<Vertex>* vertPtr;
	vector<Triangle>* triPtr;
	vector<Cell>* quadPtr;

	void writeFacetSTL(int index, ofstream& fs);
	void writeVerticesSTL(int index, ofstream& fs);

	// background
	void writeInfoVRML(ofstream& of);
	// axes
	void writeAxesVRML(ofstream& fs);
	// image
	void writeImageVRML(ofstream& of);
	void writeEachImageCell(ofstream& of, int row, int col);
	// mesh
	void writeMeshVRML(ofstream& of);
	void writeEachMeshTriangleVRML(ofstream& of, int index);
	// quad tree
	void writeTreeVRML(ofstream& of);
	void writeEachTreeCellVRML(ofstream& of, int index);

public:
	PostProcessor(vector< vector<Vertex> >* imgPtr, vector< Vertex >* vertPtr, vector<Triangle>* triPtr, vector<Cell>* quadPtr);
	void writeSTL(const string& dir, const string& inFileName);
	void writeVRML(const string& dir, const string& inFileName, char* argv1);
};

#endif /* SRC_POSTPROC_POSTPROCESSOR_H_ */
