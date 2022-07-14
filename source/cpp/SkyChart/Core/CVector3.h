/*!
*  \file      CVector3.h
*  \author    David Motl
*  \date      2022-07-05
*
*  \copyright
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted
*  provided that the following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions
*      and the following disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list
*      of conditions and the following disclaimer in the documentation and/or other materials provided
*      with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of its contributors may be used
*      to endorse or promote products derived from this software without specific prior written
*      permission.
*/
#pragma once

#include <assert.h>
#include <cmath>

#include "CPoint.h"

/*!
* The CVector3 template class defines a point using tree coordinates of an arbitrary precision
* specified as the template parameter T.
*
* A vector is specified by a x, y and z coordinates which can be accessed using
* the x(), y() and z() functions, respecively. The isNull() function returns true if all x, y and z coordinates
* are set to 0. The coordinates can be set (or altered) using the setX(), setY() and setZ() functions.
*
* A vector can also be used as a 3D vector. Addition and subtraction are defined as for vectors
* (each component is added separately). A CVector3 object can also be divided or multiplied by
* a factor (a divisor), respectively. The dot product and cross product of two vectors are also defined.
*/
template<typename T>
class CVector3 : public std::array<T, 3>
{
public:
	/*!
	* \brief Default constructor
	*
	* Creates a null vector
	*/
	CVector3() {}

	/*! Copy constructor */
	CVector3(const CVector3& other) : std::array<T, 3>(other) {}

	/*!
	* \brief Constructor
	*
	* Creates a point with coordinates (x, y, z)
	* \param x x coordinate
	* \param y y coordinate
	* \param z z coordinate
	*/
	CVector3(const T& x, const T& y, const T& z) { at(0) = x; at(1) = y; at(2) = z; }

	/*!
	* \brief Constructor
	*
	* Creates a point with coordinates from an array
	* \param n size of array (must be 3)
	* \param xyz array of T with coordinates [x, y, z]
	*/
	CVector3(int n, const T* xyz) { assert(n == 3); at(0) = xyz[0]; at(1) = xyz[1]; at(2) = xyz[2]; }

	/*!
	* \brief Constructor
	*
	* Creates a point with coordinates (p.x(), p.y(), z)
	* \param p point
	* \param z coordinate
	*/
	CVector3(const CPoint<T>& p, const T& z = 0) { at(0) = p.x(); at(1) = p.y(); at(2) = z; }

	/*!
	* \brief Get reference to i-th coordinate
	*
	* \param i 0: x coordinate, 1: y coordinate, 2: z coordinate
	*/
	T& at(int i)
	{
		return std::array<T, 3>::at(i);
	}

	/*!
	* \brief Get const reference to i-th coordinate
	*
	* \param i 0: x coordinate, 1: y coordinate, 2: z coordinate
	*/
	const T& at(int i) const
	{
		return std::array<T, 3>::at(i);
	}

	/*!
	* \brief Get const reference to x coordinate
	*/
	const T& x() const { return at(0); }

	/*!
	* \brief Get reference to x coordinate
	*/
	T& x() { return at(0); }

	/*!
	* \brief Set the x coordinate
	*/
	void setX(const T& x) { at(0) = x; }

	/*!
	* \brief Get const reference to y coordinate
	*/
	const T& y() const { return at(1); }

	/*!
	* \brief Get reference to y coordinate
	*/
	T& y() { return at(1); }

	/*!
	* \brief Set the x coordinate
	*/
	void setY(const T& value) { at(1) = value; }

	/*!
	* \brief Get const reference to z coordinate
	*/
	const T& z() const { return at(2); }

	/*!
	* \brief Get reference to z coordinate
	*/
	T& z() { return at(2); }

	/*!
	* \brief Set the x coordinate
	*/
	void setZ(const T& value) { at(2) = value; }

	/*! Get a point with x and y coordinates */
	CPoint<T> toPoint(void) const
	{
		return { at(0), at(1) };
	}

	/*!
	* \brief Get normalized vector
	*
	* The function returns a vector that has the same direction
	* but the unit length. If the vector has zero length, the function
	* returns a null vector.
	*/
	CVector3<T> normalized(void) const
	{
		T l = length();
		return (l > 0 ? *this / l : CVector3<T>());
	}

	/*!
	* \brief Normalize vector
	*
	* The function modifies the vector so the vector has the same direction
	* but the unit length. If the vector has zero length, the function
	* does nothing.
	*/
	void normalize(void)
	{
		T l = length();
		if (l > 0) {
			at(0) /= l;
			at(1) /= l;
			at(2) /= l;
		}
	}

	/*! Returns Euclidean length of the vector. */
	double length() const
	{
		return std::hypot(at(0), at(1), at(2));
	}

	/*! Returns the dot product of the vector with itself. */
	T lengthSquared() const
	{
		return dotProduct(*this, *this);
	}

	/*! Returns Dot product with another vector */
	T dotProduct(const CVector3<T>& b) const
	{
		return dotProduct(*this, b);
	}

	CVector3<T> crossProduct(const CVector3<T>& v2) const
	{
		return crossProduct(*this, v2);
	}

	/*! Returns true if the x and y coordinates are set to zero */
	bool isNull() const
	{
		return at(0) == 0 && at(1) == 0 && at(2) == 0;
	}

	/*! Returns dot product of two given vectors */
	static T dotProduct(const CVector3<T>& a, const CVector3<T>& b)
	{
		return a.at(0) * b.at(0) + a.at(1) * b.at(1) + a.at(2) * b.at(2);
	}

	/*! Returns cross product of two given vectors */
	static CVector3<T> crossProduct(const CVector3<T>& v1, const CVector3<T>& v2)
	{
		return CVector3<T>(
			v1.at(1) * v2.at(2) - v1.at(2) * v2.at(1),
			v1.at(2) * v2.at(0) - v1.at(0) * v2.at(2),
			v1.at(0) * v2.at(1) - v1.at(1) * v2.at(0)
		);
	}

	/*! Returns sum of the vector with another vector */
	CVector3<T> operator+(const CVector3<T>& b) const
	{
		return { at(0) + b.at(0), at(1) + b.at(1), at(2) + b.at(2) };
	}

	/*! Returns difference between the vector and another vector */
	CVector3<T> operator-(const CVector3<T>& b) const
	{
		return { at(0) - b.at(0), at(1) - b.at(1), at(2) - b.at(2) };
	}

	/*! Returns sum of the vector with another vector */
	CVector3<T> operator+=(const CVector3<T>& b)
	{
		at(0) += b.at(0);
		at(1) += b.at(1);
		at(2) += b.at(2);
		return *this;
	}

	/*! Returns difference between the vector and another vector */
	CVector3<T> operator-=(const CVector3<T>& b) 
	{
		at(0) -= b.at(0);
		at(1) -= b.at(1);
		at(2) -= b.at(2);
		return *this;
	}

	/*! Return a vectors with x and y coordinates multipled by a factor */
	CVector3<T> operator*=(const T& factor)
	{
		at(0) *= factor;
		at(1) *= factor;
		at(2) *= factor;
		return *this;
	}

	/*! Return a vectors with x and y coordinates multipled by a factor */
	CVector3<T> operator/=(const T& divisor)
	{
		at(0) /= divisor;
		at(1) /= divisor;
		at(2) /= divisor;
		return *this;
	}

	/*! Return true if the vectors have the same x and y coordinates */
	bool operator==(const CVector3<T>& other) const
	{
		return at(0) == other.at(0) && at(1) == other.at(1) && at(2) == other.at(2);
	}

	/*! Return true if the vectors have the same x and y coordinates */
	bool operator!=(const CVector3<T>& other) const
	{
		return !operator==(other);
	}

	/*! Return a vectors with x and y coordinates multipled by a factor */
	constexpr friend inline CVector3 operator*(const T& factor, const CVector3<T>& vector) noexcept
	{
		return { factor * vector[0], factor * vector[1], factor * vector[2] };
	}

	/*! Return a vectors with x and y coordinates multipled by a factor */
	constexpr friend inline CVector3 operator*(const CVector3<T>& vector, const T& factor) noexcept
	{
		return { vector[0] * factor, vector[1] * factor, vector[2] * factor};
	}

	/*! Return a vectors with x and y coordinates divided by a divisor */
	constexpr friend inline CVector3 operator/(const CVector3<T>& vector, const T& divisor) noexcept
	{
		return { vector[0] / divisor, vector[1] / divisor, vector[2] / divisor };
	}

	/*! Return a copy of the vector */
	constexpr friend inline CVector3 operator+(const CVector3& point) noexcept
	{
		return point;
	}

	/*! Return the vector with x and y coordinates negated */
	constexpr friend inline CVector3 operator-(const CVector3& vector)
	{
		return { -vector[0], -vector[1], -vector[2] };
	}
};

//using CVector3d = CVector3<double>;
