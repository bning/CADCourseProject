/*
 * Application.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: bo
 */

#include "Application.h"

Application::Application(char* path) {
	this->path = path;
}
void Application::run() {
	cout << ">> Starting Pre-processing..." << endl;
	ImagePreLim imgPre(path);
	Image2TriMesh_2D trans;

	imgPre.ReadImage(image);
	// printImage();

	cout << ">> Starting Transformation..." << endl;
	// Do the mesh generation process to fill #vertices# #triangles# and #quadTree#

	cout << ">> Starting Post-processing..." << endl;
	PostProcessor post(&image, &vertices, &triangles, &quadTree);
	post.writeSTL(imgPre.getOutputFolderName(), imgPre.getImageFileName());
	post.writeVRML(imgPre.getOutputFolderName(), imgPre.getImageFileName());
}


void Application::printImage(void) {
	cout << ">> Printing the image..." << endl;
	for (int i = 0; i < image.size(); ++i) {
		for (int j = 0; j < image[0].size(); ++j) {
			if (image[i][j].val == 1) {
				cout << "*";
			} else {
				cout << " ";
			}
		}
		cout << "" << endl;
	}
}
