/*
 * Vector3.h
 *
 *  Created on: Apr 2, 2015
 *      Author: bo
 */

#include <cassert>
#include <cmath>
#include "Vector2.h"

#ifndef VECTOR3_H_
#define VECTOR3_H_

class Vector3 {
public:

	/**
	 * The number of dimensions.
	 */
	static const unsigned int DIM = 3;

	/**
	 * The zero vector.
	 */
	static const Vector3 Zero;

	/**
	 * The vector (1,1,1).
	 */
	static const Vector3 Ones;

	/**
	 * The vector (1,0,0)
	 */
	static const Vector3 UnitX;

	/**
	 * The vector (0,1,0)
	 */
	static const Vector3 UnitY;

	/**
	 * The vector (0,0,1)
	 */
	static const Vector3 UnitZ;

	/**
	 * Components of this vector.
	 */
	double x, y, z;

	/**
	 * Default constructor. Leaves values unitialized.
	 */
	Vector3() :
			x(0), y(0), z(0) {
	}

	/**
	 * Create a vector with the given values.
	 */
	Vector3(double x, double y, double z) :
			x(x), y(y), z(z) {
	}

	/**
	 * Create a vector from a 2d vector.
	 */
	Vector3(const Vector2& v, double z) :
			x(v.x), y(v.y), z(z) {
	}

	/**
	 * Create a vector from a float array.
	 */
	explicit Vector3(const float arr[3]) :
			x(arr[0]), y(arr[1]), z(arr[2]) {
	}

	// also uses default copy and assignment

	Vector3 operator+(const Vector3& rhs) const {
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vector3& operator+=(const Vector3& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3 operator-(const Vector3& rhs) const {
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vector3& operator-=(const Vector3& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vector3 operator*(double s) const {
		return Vector3(x * s, y * s, z * s);
	}

	Vector3& operator*=(double s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Vector3 operator/(double s) const {
		double inv = 1.0 / s;
		return Vector3(x * inv, y * inv, z * inv);
	}

	Vector3& operator/=(double s) {
		double inv = 1.0 / s;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}

	Vector3 operator-() const {
		return Vector3(-x, -y, -z);
	}

	/**
	 * @remark No bounds checking.
	 */
	const double& operator[](unsigned int i) const {
		// assumes all members are in a contiguous block
		assert(i >= 0 && i < DIM);
		return (&x)[i];
	}

	/**
	 * @remark No bounds checking.
	 */
	double& operator[](unsigned int i) {
		// assumes all members are in a contiguous block
		assert(i >= 0 && i < DIM);
		return (&x)[i];
	}

	bool operator==(const Vector3& rhs) const {
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

	bool operator!=(const Vector3& rhs) const {
		return !operator==(rhs);
	}

	void to_array(float arr[DIM]) const {
		arr[0] = float(x);
		arr[1] = float(y);
		arr[2] = float(z);
	}
};

/**
 * Returns the dot product of two vectors
 */
inline double dot(const Vector3& lhs, const Vector3& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

/**
 * Returns the cross product of two vectors
 */
inline Vector3 cross(const Vector3& lhs, const Vector3& rhs) {
	return Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x);
}

/**
 * Efficiency function: does not require square root operation.
 */
inline double squared_length(const Vector3& v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

/**
 * Returns the length of a vector.
 */
inline double length(const Vector3& v) {
	return sqrt(squared_length(v));
}

/**
 * Calculate the positive distance between two vectors.
 */
inline double distance(const Vector3& lhs, const Vector3& rhs) {
	return length(lhs - rhs);
}

/**
 * Efficiency function: does not require square root operation.
 */
inline double squared_distance(const Vector3& lhs, const Vector3& rhs) {
	return squared_length(lhs - rhs);
}

/**
 * Returns the unit vector pointing in the same direction as this vector.
 */
inline Vector3 normalize(const Vector3& v) {
	return v / length(v);
}

/**
 * Returns a vector whose elements are the absolute values of all the
 * elements of this vector.
 */
inline Vector3 vabs(const Vector3& v) {
	return Vector3(fabs(v.x), fabs(v.y), fabs(v.z));
}

/**
 * Returns the element-wise maximum of the two vectors.
 */
inline Vector3 vmax(const Vector3& lhs, const Vector3& rhs) {
	return Vector3(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y),
			std::max(lhs.z, rhs.z));
}

/**
 * Returns the element-wise minimum of the two vectors.
 */
inline Vector3 vmin(const Vector3& lhs, const Vector3& rhs) {
	return Vector3(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y),
			std::min(lhs.z, rhs.z));
}

inline Vector3 operator*(double s, const Vector3& rhs) {
	return rhs * s;
}

/**
 * Outputs a vector text formatted as "(x,y,z)".
 */
std::ostream& operator<<(std::ostream& os, const Vector3& rhs);

#endif /* VECTOR3_H_ */
