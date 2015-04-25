/*
 * Line2.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: bo
 */

#include "Line2.h"

Vector2 Line2::getDirection() {
	return normalize(end - start);
}

bool Line2::isParalell(Line2 &other) {
	return std::abs(dot(end - start, other.end - other.start))
			== length(end - start) * length(other.end - other.start);
}

bool Line2::isVertical(Line2 &other) {
	return dot(end - start, other.end - other.start) == 0;
}

Vector2 Line2::midPoint() {
	return Vector2(0.5 * (start.x + end.x), 0.5 * (start.y + end.y));
}
