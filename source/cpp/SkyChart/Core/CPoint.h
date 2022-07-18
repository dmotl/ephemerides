/*!
*  \file      CPoint.h
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

#include <array>

/*! 
* The CPoint template class defines a point using two coordinates of an arbitrary precision
* specified as the template parameter T. 
* 
* A point is specified by a x coordinate and an y coordinate which can be accessed using 
* the x() and y() functions. The isNull() function returns true if both x and y are set to 0.0. 
* The coordinates can be set (or altered) using the setX() and setY() functions.
* 
* A point can also be used as a 2D vector. Addition and subtraction are defined as for vectors 
* (each component is added separately). A CPoint object can also be divided or multiplied by 
* a factor (a divisor), respectively. The dot product is also defined.
*
*/
template<typename T>
class CPoint : public std::array<T, 2>
{
public:
	/*!
	* \brief Default constructor
	*
	* Creates a point with coordinates (0, 0)
	*/
	CPoint() {}

	/*! Copy constructor */
	CPoint(const CPoint& other) : std::array<T, 2>(other) {}

	/*!
	* \brief Constructor
	* 
	* Creates a point with coordinates (x, y)
	* \param x x coordinate
	* \param y y coordinate
	*/
	CPoint(const T& x, const T& y) { at(0) = x; at(1) = y; }

	/*!
	* \brief Constructor
	*
	* Creates a point with coordinates in an array
	* \param n size of array (must be 2)
	* \param xy array of T with coordinates [x, y]
	*/
	CPoint(int n, const T* xy) { assert(n == 2); at(0) = xy[0]; at(1) = xy[1]; }

	/*!
	* \brief Get reference to i-th coordinate
	* 
	* \param i 0: x coordinate, 1: y coordinate
	*/ 
	T& at(int i)
	{
		return std::array<T, 2>::at(i);
	}

	/*!
	* \brief Get const reference to i-th coordinate
	*
	* \param i 0: x coordinate, 1: y coordinate
	*/
	const T& at(int i) const
	{
		return std::array<T, 2>::at(i);
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
	* \brief Get normalized vector
	* 
	* The function returns a vector that has the same direction
	* but the unit length. If the vector has zero length, the function 
	* returns a null vector.
	*/
	CPoint<T> normalized(void) const
	{
		T l = length();
		return (l > 0 ? *this / l : CPoint<T>());
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
		}
	}

	/*!
	* \brief Get transposed vector
	*
	* The function returns a vector with x and y coordinates exchanged.
	*/
	CPoint<T> transposed(void) const
	{
		return { at(1), at(0) };
	}

	/*!
	* \brief Tranpose vector
	*
	* The function modifies the vector so the vector has the x and y
	* coordinates exchanged.
	*/
	void transpose(void)
	{
		std::swap(at(0), at(1));
	}

	/*! Returns Euclidean length of the vector. */
	double length() const
	{
		return std::hypot(at(0), at(1));
	}

	/*! Returns the dot product of the vector with itself. */
	T lengthSquared() const
	{
		return dotProduct(*this, *this);
	}

	/*! Returns Dot product with another vector */
	T dotProduct(const CPoint<T>& b) const 
	{
		return dotProduct(*this, b);
	}

	/*! Returns true if the x and y coordinates are set to zero */
	bool isNull() const
	{
		return at(0) == 0 && at(1) == 0;
	}

	/*! Returns dot product of two given vectors */
	static T dotProduct(const CPoint<T>& a, const CPoint<T>& b)
	{
		return a.at(0) * b.at(0) + a.at(1) * b.at(1);
	}

	/*! Returns sum of the vector with another vector */
	CPoint<T> operator+(const CPoint<T>& b) const
	{
		return { at(0) + b.at(0), at(1) + b.at(1) };
	}

	/*! Returns sum of the vector with another vector */
	CPoint<T> operator+=(const CPoint<T>& b) 
	{
		at(0) += b.at(0);
		at(1) += b.at(1);
		return *this;
	}

	/*! Returns difference between the vector and another vector */
	CPoint<T> operator-(const CPoint<T>& b) const
	{
		return { at(0) - b.at(0), at(1) - b.at(1) };
	}

	/*! Returns difference between the vector and another vector */
	CPoint<T> operator-=(const CPoint<T>& b) const
	{
		at(0) -= b.at(0);
		at(1) -= b.at(1);
		return *this;
	}

	/*! Return true if the vectors have the same x and y coordinates */
	bool operator==(const CPoint<T>& other) const
	{
		return at(0) == other.at(0) && at(1) == other.at(1);
	}

	/*! Return true if the vectors have the same x and y coordinates */
	bool operator!=(const CPoint<T>& other) const 
	{ 
		return !operator==(other); 
	}

	/*! Return a vectors with x and y coordinates multipled by a factor */
	CPoint operator*=(const T& factor) 
	{
		at(0) *= factor;
		at(1) *= factor;
		return *this;
	}

	/*! Return a vectors with x and y coordinates divided by a divisor */
	CPoint operator/=(const T& divisor) 
	{
		at(0) /= divisor;
		at(1) /= divisor;
		return *this;
	}

	/*! Return a vectors with x and y coordinates multipled by a factor */
	constexpr friend inline CPoint operator*(const T& factor, const CPoint<T>& vector) noexcept
	{
		return { factor * vector[0], factor * vector[1] };
	}

	/*! Return a vectors with x and y coordinates multipled by a factor */
	constexpr friend inline CPoint operator*(const CPoint<T>& vector, const T& factor) noexcept
	{
		return { vector[0] * factor, vector[1] * factor };
	}

	/*! Return a vectors with x and y coordinates divided by a divisor */
	constexpr friend inline CPoint operator/(const CPoint<T>& vector, const T& divisor) noexcept
	{
		return { vector[0] / divisor, vector[1] / divisor };
	}

	/*! Return a copy of the vector */
	constexpr friend inline CPoint operator+(const CPoint& point) noexcept
	{
		return point;
	}

	/*! Return the vector with x and y coordinates negated */
	constexpr friend inline CPoint operator-(const CPoint& point)
	{
		return CPoint<T>().operator-(point);
	}
};

using CPointd = CPoint<double>;
