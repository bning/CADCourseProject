/*
 * Line2.h
 *
 *  Created on: Apr 2, 2015
 *      Author: bo
 */
#include "Vector2.h"

#ifndef LINE2_H_
#define LINE2_H_

class Line2 {
public:
	Vector2 start;
	Vector2 end;

	Line2(Vector2 &start, Vector2 &end) :
			start(start), end(end) {
	}
	;

	Vector2 getDirection();

	bool isParalell(Line2 &other);

	bool isVertical(Line2 &other);

	Vector2 midPoint();
};

#endif /* LINE2_H_ */
