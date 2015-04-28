/*
 * Application.h
 *
 *  Created on: Apr 27, 2015
 *      Author: bo
 */

#ifndef SRC_PROJ_APPLICATION_H_
#define SRC_PROJ_APPLICATION_H_

#include "prelim/ImagePreLim.h"
#include "trans/Image2TriMesh.h"
#include "postproc/PostProcessor.h"
#include <iostream>

class Vertex;
class Triangle;
class Cell;

using namespace std;

class Application {
private:
	char* path;
	vector< vector<Vertex> > image;
	vector<Cell> quadTree;

public:
	Application(char* path);
	void run();
	void printImage(void);
};

#endif /* SRC_PROJ_APPLICATION_H_ */
