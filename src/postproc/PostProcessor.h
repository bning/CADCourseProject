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

	void writeFacet(int index, ofstream& fs);
	void writeVertices(int index, ofstream& fs);

public:
	PostProcessor(vector< vector<Vertex> >* imgPtr, vector< Vertex >* vertPtr, vector<Triangle>* triPtr, vector<Cell>* quadPtr);
	void writeSTL(const string& dir, const string& inFileName);
	void writeVRML(const string& dir, const string& inFileName);
};

#endif /* SRC_POSTPROC_POSTPROCESSOR_H_ */
