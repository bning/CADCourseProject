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
void Application::run(char* argv1) {
        cout << ">> Starting Pre-processing..." << endl;
        ImagePreLim imgPre(path);

        // Pre processing
        imgPre.ReadImage(image);
        // printImage();

        vector<vector<Vertex> > underSampledImage;
        int uSfactor = 4;
        imgPre.UnderSampleImage(image, uSfactor, underSampledImage);

        int cellCount = 0;
        //vector<Cell> quadTree;
        imgPre.SubDivide(image, quadTree, &cellCount);

        cout << ">> Starting Transformation..." << endl;
        // Do the mesh generation process to fill #vertices# #triangles# and #quadTree#
        Image2TriMesh_2D trans;
        trans.SetProblem(underSampledImage);
        trans.UniformMeshGenerator();

        cout << ">> Starting Post-processing..." << endl;
        PostProcessor post(&image, &trans.tripts, &trans.trimesh, &quadTree);
        post.writeSTL(imgPre.getOutputFolderName(), imgPre.getImageFileName());
        post.writeVRML(imgPre.getOutputFolderName(), imgPre.getImageFileName(), argv1);
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
