/*
 * PostProcessor.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: bo
 */

#include "PostProcessor.h"

PostProcessor::PostProcessor(vector<vector<Vertex> >* imgPtr,
		vector<Vertex>* vertPtr, vector<Triangle>* triPtr,
		vector<Cell>* quadPtr) {
	this->imgPtr = imgPtr;
	this->quadPtr = quadPtr;
	this->triPtr = triPtr;
	this->vertPtr = vertPtr;
}

void PostProcessor::writeSTL(const string& dir, const string& inFileName) {
	string solidName = inFileName.substr(0, inFileName.size() - 4);
	string outPath = dir + solidName + ".stl";
	ofstream fs;
	fs.open("outPath", std::fstream::out);
	fs << "solid " << solidName << "\n";
	for (int i = 0; i < triPtr->size(); i++) {
		writeFacet(i, fs);
	}
	fs << "endsolid " << solidName << "\n";
	fs.close();
	return;
}

void PostProcessor::writeFacet(int index, ofstream& fs) {
	Vector3 norm(0, 0, 1);
	fs << "    " << "facet normal " << std::scientific << norm.x
			<< std::scientific << " " << norm.y << std::scientific << " "
			<< norm.z << std::scientific << "\n";
	writeVertices(index, fs);
	fs << "    " << "endfacet\n";
}

void PostProcessor::writeVertices(int index, ofstream& fs) {
	int ind_a = (*triPtr)[index].id[0];
	int ind_b = (*triPtr)[index].id[1];
	int ind_c = (*triPtr)[index].id[2];
	Vector3 vtx_a ((*vertPtr)[ind_a].x[0], (*vertPtr)[ind_a].x[1], 0);
	Vector3 vtx_b ((*vertPtr)[ind_b].x[0], (*vertPtr)[ind_b].x[1], 0);
	Vector3 vtx_c ((*vertPtr)[ind_c].x[0], (*vertPtr)[ind_c].x[1], 0);
	fs << "        " << "outer loop\n";
	fs << "            " << "vertex " << std::scientific << vtx_a.x
			<< std::scientific << " " << vtx_a.y << std::scientific << " "
			<< vtx_a.z << std::scientific << "\n";
	fs << "            " << "vertex " << std::scientific << vtx_b.x
			<< std::scientific << " " << vtx_b.y << std::scientific << " "
			<< vtx_b.z << std::scientific << "\n";
	fs << "            " << "vertex " << std::scientific << vtx_c.x
			<< std::scientific << " " << vtx_c.y << std::scientific << " "
			<< vtx_c.z << std::scientific << "\n";
	fs << "        " << "endloop\n";
}

void PostProcessor::writeVRML(const string& dir, const string& inFIleName) {

	return;
}

