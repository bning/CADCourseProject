/*
 * Vector3.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: bo
 */

#include "Vector3.h"

const Vector3 Vector3::Zero = Vector3(0, 0, 0);
const Vector3 Vector3::Ones = Vector3(1, 1, 1);
const Vector3 Vector3::UnitX = Vector3(1, 0, 0);
const Vector3 Vector3::UnitY = Vector3(0, 1, 0);
const Vector3 Vector3::UnitZ = Vector3(0, 0, 1);

std::ostream& operator<<(std::ostream& os, const Vector3& v) {
	return os << '(' << v.x << ',' << v.y << ',' << v.z << ')';
}

