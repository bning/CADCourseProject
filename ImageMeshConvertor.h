/*
 * ImageMeshConvertor.h
 *
 *  Created on: Apr 2, 2015
 *      Author: bo
 */
#include "Mesh.h"

#ifndef IMAGEMESHCONVERTOR_H_
#define IMAGEMESHCONVERTOR_H_

class GDLImage {
public:
	unsigned int rowNum;
	unsigned int colNum;
	std::vector<std::vector<int> > data;
};

class ImageMeshConvertor {
public:
	GDLImage image;
	bool loadImage();
	bool convert(Mesh &mesh);
};

#endif /* IMAGEMESHCONVERTOR_H_ */
