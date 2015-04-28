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
	cout << ">> Starting writing STL file: " + outPath << "...";
	ofstream fs;
	fs.open(outPath.c_str(), std::fstream::out);
	fs << "solid " << solidName << "\n";
	for (int i = 0; i < triPtr->size(); i++) {
		writeFacetSTL(i, fs);
	}
	fs << "endsolid " << solidName << "\n";
	cout << "Done." << endl;
	fs.close();
	return;
}

void PostProcessor::writeFacetSTL(int index, ofstream& fs) {
	Vector3 norm(0, 0, 1);
	fs << "    " << "facet normal " << std::scientific << norm.x
			<< std::scientific << " " << norm.y << std::scientific << " "
			<< norm.z << std::scientific << "\n";
	writeVerticesSTL(index, fs);
	fs << "    " << "endfacet\n";
}

void PostProcessor::writeVerticesSTL(int index, ofstream& fs) {
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



void PostProcessor::writeVRML(const string& dir, const string& inFileName) {
	string solidName = inFileName.substr(0, inFileName.size() - 4);
	string outPath = dir + solidName + ".wrl";
	cout << ">> Starting writing VRML file: " + outPath << "...";
	ofstream fs;
	fs.open(outPath.c_str(), std::fstream::out);
	fs << "#VRML V2.0 utf8" << endl << endl;
	writeImageVRML(fs);
	writeTreeVRML(fs);
	writeMeshVRML(fs);
	writeAxesVRML(fs);
	writeInfoVRML(fs);
	cout << "Done." << endl;
	fs.close();
	return;
}


void PostProcessor::writeInfoVRML(ofstream &of) {
	of << "NavigationInfo {" << endl;
		of << "\t type \"EXAMINE\"" << endl;
	of << "}" << endl;

	of << "Background {" << endl;
		of << "\t skyColor 1 1 1" << endl;
	of << "}" << endl;
	of << endl;
}


void PostProcessor::writeAxesVRML(ofstream& of) {
	of << "Shape {" << endl;
		of << "\t geometry Extrusion {" << endl;
			of << "\t\t spine [0 0 0, 24 0 0, 24 0 0, 28 0 0]" << endl;
			of << "\t\t crossSection [1 0, 0 1, -1 0, 0 -1, 1 0]" << endl;
			of << "\t\t scale [0.1 0.1, 0.1 0.1, 0.4 0.4, 0 0]" << endl;
		of << "\t }" << endl;

		of << "\t appearance Appearance {" << endl;
			of << "\t\t material Material {" << endl;
				of << "\t\t\t diffuseColor 0 0 0" << endl;
			of << "\t\t }" << endl;
		of << "\t }" << endl;
	of << "}" << endl;

	of << "Shape {" << endl;
		of << "\t geometry Extrusion {" << endl;
			of << "\t\t spine [0 0 0, 0 24 0, 0 24 0, 0 28 0]" << endl;
			of << "\t\t crossSection [1 0, 0 1, -1 0, 0 -1, 1 0]" << endl;
			of << "\t\t scale [0.1 0.1, 0.1 0.1, 0.4 0.4, 0 0]" << endl;
		of << "\t }" << endl;

		of << "\t appearance Appearance {" << endl;
			of << "\t\t material Material {" << endl;
				of << "\t\t\t diffuseColor 0 0 0" << endl;
			of << "\t\t }" << endl;
		of << "\t }" << endl;
	of << "}" << endl;

	of << "Shape {" << endl;
		of << "\t geometry Extrusion {" << endl;
			of << "\t\t spine [0 0 0, 0 0 24, 0 0 24, 0 0 28]" << endl;
			of << "\t\t crossSection [1 0, 0 1, -1 0, 0 -1, 1 0]" << endl;
			of << "\t\t scale [0.1 0.1, 0.1 0.1, 0.4 0.4, 0 0]" << endl;
		of << "\t }" << endl;

		of << "\t appearance Appearance {" << endl;
			of << "\t\t material Material {" << endl;
				of << "\t\t\t diffuseColor 0 0 0" << endl;
			of << "\t\t }" << endl;
		of << "\t }" << endl;
	of << "}" << endl;
	of << endl;
}


void PostProcessor::writeImageVRML(ofstream& of) {
	for (int i = 0; i < imgPtr->size() - 1; ++i) {
		for (int j = 0; j < (*imgPtr)[0].size() - 1; ++j) {
			writeEachImageCell(of, i, j);
		}
	}
}

void PostProcessor::writeEachImageCell(ofstream& of, int row, int col) {
	of << "Shape {" << endl;
		of << "\t geometry IndexedFaceSet {" << endl;
			of << "\t\t coord Coordinate {" << endl;
				of << "\t\t\t point [" << endl;
					of << "\t\t\t\t " << (*imgPtr)[row][col].x[0] << " " << (*imgPtr)[row][col].x[1] << " " << 0.0 << endl;
					of << "\t\t\t\t " << (*imgPtr)[row + 1][col].x[0] << " " << (*imgPtr)[row + 1][col].x[1] << " " << 0.0 << endl;
					of << "\t\t\t\t " << (*imgPtr)[row + 1][col + 1].x[0] << " " << (*imgPtr)[row + 1][col + 1].x[1] << " " << 0.0 << endl;
					of << "\t\t\t\t " << (*imgPtr)[row][col + 1].x[0] << " " << (*imgPtr)[row][col + 1].x[1] << " " << 0.0 << endl;
				of << "\t\t\t ]" << endl;
			of << "\t\t }" << endl;

			of << "\t\t coordIndex [" << endl;
				of << "\t\t\t 0 1 2 3 -1" << endl;
			of << "\t\t ]" << endl;
		of << "\t }" << endl;

		of << "\t appearance Appearance {" << endl;
			of << "\t\t material Material {" << endl;
				double color = 0.25 * ((*imgPtr)[row][col].val + (*imgPtr)[row + 1][col].val + (*imgPtr)[row + 1][col + 1].val + (*imgPtr)[row][col + 1].val);
				color = (color > 0.5) ? 1 : 0;
				of << "\t\t\t diffuseColor " << color << " " << color << " " << color << endl;
			of << "\t\t }" << endl;
		of << "\t }" << endl;

	of << "}" << endl;
	of << endl;
}

void PostProcessor::writeMeshVRML(ofstream& of) {
	for (int i = 0; i < triPtr->size(); ++i) {
		writeEachMeshTriangleVRML(of, i);
	}
}

void PostProcessor::writeEachMeshTriangleVRML(ofstream& of, int index) {
	int ind_a = (*triPtr)[index].id[0];
	int ind_b = (*triPtr)[index].id[1];
	int ind_c = (*triPtr)[index].id[2];
	Vector3 vtx_a ((*vertPtr)[ind_a].x[0], (*vertPtr)[ind_a].x[1], -2);
	Vector3 vtx_b ((*vertPtr)[ind_b].x[0], (*vertPtr)[ind_b].x[1], -2);
	Vector3 vtx_c ((*vertPtr)[ind_c].x[0], (*vertPtr)[ind_c].x[1], -2);
	of << "Shape {" << std::endl;
		of << "\t geometry IndexedLineSet {" << std::endl;
			of << "\t\t colorPerVertex FALSE" << std::endl;
			of << "\t\t coord Coordinate {" << std::endl;
				of << "\t\t\t point [" << std::endl;
					of << "\t\t\t\t " << vtx_a.x << " " << vtx_a.y << " " << vtx_a.z << std::endl;
					of << "\t\t\t\t " << vtx_b.x << " " << vtx_b.y << " " << vtx_b.z << std::endl;
					of << "\t\t\t\t " << vtx_c.x << " " << vtx_c.y << " " << vtx_c.z << std::endl;
				of << "\t\t\t ]" << std::endl;
			of << "\t\t }" << std::endl;

			of << "\t\t coordIndex [" << std::endl;
				of << "\t\t\t 0 1 -1" << std::endl;
				of << "\t\t\t 1 2 -1" << std::endl;
				of << "\t\t\t 2 0 -1" << std::endl;
			of << "\t\t ]" << std::endl;

			of << "\t\t color Color {" << std::endl;
				of << "\t\t\t color [" << std::endl;
					of << "\t\t\t\t 1.0 0.0 0.0" << std::endl;
					of << "\t\t\t\t 1.0 0.0 0.0" << std::endl;
					of << "\t\t\t\t 1.0 0.0 0.0" << std::endl;
				of << "\t\t\t ]" << std::endl;
			of << "\t\t }" << std::endl;

		of << "\t }" << std::endl;
	of << "}" << std::endl;
	of << std::endl;
}

void PostProcessor::writeTreeVRML(ofstream& of) {
	for (int i = 0; i < quadPtr->size(); ++i) {
		writeEachTreeCellVRML(of, i);
	}
}

void PostProcessor::writeEachTreeCellVRML(ofstream& of, int index) {
	int ind_a = (*quadPtr)[index].corner[0];
	int ind_b = (*quadPtr)[index].corner[1];
	int ind_c = (*quadPtr)[index].corner[2];
	int ind_d = (*quadPtr)[index].corner[3];
	Vector3 vtx_a ((*imgPtr)[ind_a/(*imgPtr)[0].size()][ind_a%(*imgPtr)[0].size()].x[0], (*imgPtr)[ind_a/(*imgPtr)[0].size()][ind_a%(*imgPtr)[0].size()].x[1], -1);
	Vector3 vtx_b ((*imgPtr)[ind_b/(*imgPtr)[0].size()][ind_b%(*imgPtr)[0].size()].x[0], (*imgPtr)[ind_b/(*imgPtr)[0].size()][ind_b%(*imgPtr)[0].size()].x[1], -1);
	Vector3 vtx_c ((*imgPtr)[ind_c/(*imgPtr)[0].size()][ind_c%(*imgPtr)[0].size()].x[0], (*imgPtr)[ind_c/(*imgPtr)[0].size()][ind_c%(*imgPtr)[0].size()].x[1], -1);
	Vector3 vtx_d ((*imgPtr)[ind_d/(*imgPtr)[0].size()][ind_d%(*imgPtr)[0].size()].x[0], (*imgPtr)[ind_d/(*imgPtr)[0].size()][ind_d%(*imgPtr)[0].size()].x[1], -1);;
	of << "Shape {" << std::endl;
		of << "\t geometry IndexedLineSet {" << std::endl;
			of << "\t\t colorPerVertex FALSE" << std::endl;
			of << "\t\t coord Coordinate {" << std::endl;
				of << "\t\t\t point [" << std::endl;
					of << "\t\t\t\t " << vtx_a.x << " " << vtx_a.y << " " << vtx_a.z << std::endl;
					of << "\t\t\t\t " << vtx_b.x << " " << vtx_b.y << " " << vtx_b.z << std::endl;
					of << "\t\t\t\t " << vtx_c.x << " " << vtx_c.y << " " << vtx_c.z << std::endl;
					of << "\t\t\t\t " << vtx_d.x << " " << vtx_d.y << " " << vtx_d.z << std::endl;
				of << "\t\t\t ]" << std::endl;
			of << "\t\t }" << std::endl;

			of << "\t\t coordIndex [" << std::endl;
				of << "\t\t\t 0 1 -1" << std::endl;
				of << "\t\t\t 1 2 -1" << std::endl;
				of << "\t\t\t 2 3 -1" << std::endl;
				of << "\t\t\t 3 0 -1" << std::endl;
			of << "\t\t ]" << std::endl;

			of << "\t\t color Color {" << std::endl;
				of << "\t\t\t color [" << std::endl;
					of << "\t\t\t\t 0.0 1.0 0.0" << std::endl;
					of << "\t\t\t\t 0.0 1.0 0.0" << std::endl;
					of << "\t\t\t\t 0.0 1.0 0.0" << std::endl;
					of << "\t\t\t\t 0.0 1.0 0.0" << std::endl;
				of << "\t\t\t ]" << std::endl;
			of << "\t\t }" << std::endl;

		of << "\t }" << std::endl;
	of << "}" << std::endl;
	of << std::endl;
}

