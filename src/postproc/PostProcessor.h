/*
 * PostProcessor.h
 *
 *  Created on: Apr 27, 2015
 *      Author: bo
 */

#ifndef SRC_POSTPROC_POSTPROCESSOR_H_
#define SRC_POSTPROC_POSTPROCESSOR_H_

class PostProcessor {
public:
	void writeSTL(const char* fileName);
	void writeVRML(const char* fileName);
};

#endif /* SRC_POSTPROC_POSTPROCESSOR_H_ */
