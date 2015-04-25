/*
 * Vector2.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: bo
 */

#include "Vector2.h"

const Vector2 Vector2::Zero = Vector2(0, 0);
const Vector2 Vector2::Ones = Vector2(1, 1);
const Vector2 Vector2::UnitX = Vector2(1, 0);
const Vector2 Vector2::UnitY = Vector2(0, 1);

std::ostream& operator<<(std::ostream& os, const Vector2& v) {
	return os << '(' << v.x << ',' << v.y << ')';
}
