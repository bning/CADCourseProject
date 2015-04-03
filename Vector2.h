/*
 * Vector2.h
 *
 *  Created on: Apr 2, 2015
 *      Author: bo
 */

#include <cassert>
#include <cmath>
#include <iostream>

#ifndef VECTOR2_H_
#define VECTOR2_H_

class Vector2 {
public:

	/**
	 * The number of dimensions.
	 */
	static const unsigned int DIM = 2;

	/**
	 * The zero vector.
	 */
	static const Vector2 Zero;

	/**
	 * The vector (1,1).
	 */
	static const Vector2 Ones;

	/**
	 * The vector (1,0).
	 */
	static const Vector2 UnitX;

	/**
	 * The vector (0,1).
	 */
	static const Vector2 UnitY;

	/**
	 * Components of this vector.
	 */
	double x, y;

	/**
	 * Default constructor. Leaves values unitialized.
	 */
	Vector2() :
			x(0), y(0) {
	}

	/**
	 * Create a vector with the given values.
	 */
	Vector2(double x, double y) :
			x(x), y(y) {
	}

	// also uses default copy and assignment

	Vector2 operator+(const Vector2& rhs) const {
		return Vector2(x + rhs.x, y + rhs.y);
	}

	Vector2& operator+=(const Vector2& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2 operator-(const Vector2& rhs) const {
		return Vector2(x - rhs.x, y - rhs.y);
	}

	Vector2& operator-=(const Vector2& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vector2 operator*(double s) const {
		return Vector2(x * s, y * s);
	}

	Vector2& operator*=(double s) {
		x *= s;
		y *= s;
		return *this;
	}

	Vector2 operator/(double s) const {
		double inv = 1.0 / s;
		return Vector2(x * inv, y * inv);
	}

	Vector2& operator/=(double s) {
		double inv = 1.0 / s;
		x *= inv;
		y *= inv;
		return *this;
	}

	Vector2 operator-() const {
		return Vector2(-x, -y);
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

	bool operator==(const Vector2& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	bool operator!=(const Vector2& rhs) const {
		return !operator==(rhs);
	}

	void to_array(float arr[DIM]) const {
		arr[0] = float(x);
		arr[1] = float(y);
	}
};

/**
 * Returns the dot product of two vectors
 */
inline double dot(const Vector2& lhs, const Vector2& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

/**
 * Efficiency function: does not require square root operation.
 */
inline double squared_length(const Vector2& v) {
	return v.x * v.x + v.y * v.y;
}

/**
 * Returns the length of a vector.
 */
inline double length(const Vector2& v) {
	return sqrt(squared_length(v));
}

/**
 * Calculate the positive distance between two vectors.
 */
inline double distance(const Vector2& lhs, const Vector2& rhs) {
	return length(lhs - rhs);
}

/**
 * Efficiency function: does not require square root operation.
 */
inline double squared_distance(const Vector2& lhs, const Vector2& rhs) {
	return squared_length(lhs - rhs);
}

/**
 * Returns the unit vector pointing in the same direction as this vector.
 */
inline Vector2 normalize(const Vector2& v) {
	return v / length(v);
}

/**
 * Returns a vector whose elements are the absolute values of all the
 * elements of this vector.
 */
inline Vector2 vabs(const Vector2& v) {
	return Vector2(fabs(v.x), fabs(v.y));
}

/**
 * Returns the element-wise maximum of the two vectors.
 */
inline Vector2 vmax(const Vector2& lhs, const Vector2& rhs) {
	return Vector2(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y));
}

/**
 * Returns the element-wise minimum of the two vectors.
 */
inline Vector2 vmin(const Vector2& lhs, const Vector2& rhs) {
	return Vector2(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y));
}

inline Vector2 operator*(double s, const Vector2& rhs) {
	return rhs * s;
}

/**
 * Outputs a vector text formatted as "(x,y,z)".
 */
std::ostream& operator<<(std::ostream& os, const Vector2& rhs);

#endif /* VECTOR2_H_ */
