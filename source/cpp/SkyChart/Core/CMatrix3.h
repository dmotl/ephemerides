/*!
*  \file      CMatrix3.h
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

#include "CVector3.h"

/*!
* The CMatrix3 template class specifies 3-by-3 matrix
*
* The CMatrix3 class supports matrix multiplication, addition and subtraction.
*/
template<typename T>
class CMatrix3
{
private:
	std::array<std::array<T, 3>, 3> m_matrix;

public:
	/*! Constructs an identity matrix */
	CMatrix3() :m_matrix{ { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } } } {}

	/*! Copy constructor */
	CMatrix3(const CMatrix3& other) : m_matrix(other.m_matrix) {}

	/*! Get reference to a value in given row index and column index */
	T& at(int row, int col) { return m_matrix[row][col]; }

	/*! Get const reference to a value in given row index and column index */
	const T& at(int row, int col) const { return m_matrix[row][col]; }

	/*! Get reference to a value in given row index and column index */
	T& operator()(int row, int col) { return m_matrix[row][col]; }

	/*! Get const reference to a value in given row index and column index */
	const T& operator()(int row, int col) const { return m_matrix[row][col]; }

	/*! Resets the matrix to an identity matrix */
	void reset()
	{
		at(0, 1) = at(0, 2) = at(1, 0) = at(1, 2) = at(2, 0) = at(2, 1) = 0;
		at(0, 0) = at(1, 1) = at(2, 2) = 1;
	}

	bool operator==(const CMatrix3& o) const
	{
		return m_matrix == o.m_matrix;
	}

	bool operator!=(const CMatrix3& o) const
	{
		return !operator==(o);
	}

	CMatrix3 operator*(const CMatrix3& m) const
	{
		T m11 = at(0, 0) * m.at(0, 0) + at(0, 1) * m.at(1, 0) + at(0, 2) * m.at(2, 0);
		T m12 = at(0, 0) * m.at(0, 1) + at(0, 1) * m.at(1, 1) + at(0, 2) * m.at(2, 1);
		T m13 = at(0, 0) * m.at(0, 2) + at(0, 1) * m.at(1, 2) + at(0, 2) * m.at(2, 2);

		T m21 = at(1, 0) * m.at(0, 0) + at(1, 1) * m.at(1, 0) + at(1, 2) * m.at(2, 0);
		T m22 = at(1, 0) * m.at(0, 1) + at(1, 1) * m.at(1, 1) + at(1, 2) * m.at(2, 1);
		T m23 = at(1, 0) * m.at(0, 2) + at(1, 1) * m.at(1, 2) + at(1, 2) * m.at(2, 2);

		T m31 = at(2, 0) * m.at(0, 0) + at(2, 1) * m.at(1, 0) + at(2, 2) * m.at(2, 0);
		T m32 = at(2, 0) * m.at(0, 1) + at(2, 1) * m.at(1, 1) + at(2, 2) * m.at(2, 1);
		T m33 = at(2, 0) * m.at(0, 2) + at(2, 1) * m.at(1, 2) + at(2, 2) * m.at(2, 2);

		CMatrix3<T> t;
		t.at(0, 0) = m11; t.at(0, 1) = m12; t.at(0, 2) = m13;
		t.at(1, 0) = m21; t.at(1, 1) = m22; t.at(1, 2) = m23;
		t.at(2, 0) = m31; t.at(2, 1) = m32; t.at(2, 2) = m33;
		return t;
	}

	CMatrix3& operator*=(const CMatrix3& o)
	{
		T m11 = at(0, 0) * o.at(0, 0) + at(0, 1) * o.at(1, 0) + at(0, 2) * o.at(2, 0);
		T m12 = at(0, 0) * o.at(0, 1) + at(0, 1) * o.at(1, 1) + at(0, 2) * o.at(2, 1);
		T m13 = at(0, 0) * o.at(0, 2) + at(0, 1) * o.at(1, 2) + at(0, 2) * o.at(2, 2);

		T m21 = at(1, 0) * o.at(0, 0) + at(1, 1) * o.at(1, 0) + at(1, 2) * o.at(2, 0);
		T m22 = at(1, 0) * o.at(0, 1) + at(1, 1) * o.at(1, 1) + at(1, 2) * o.at(2, 1);
		T m23 = at(1, 0) * o.at(0, 2) + at(1, 1) * o.at(1, 2) + at(1, 2) * o.at(2, 2);

		T m31 = at(2, 0) * o.at(0, 0) + at(2, 1) * o.at(1, 0) + at(2, 2) * o.at(2, 0);
		T m32 = at(2, 0) * o.at(0, 1) + at(2, 1) * o.at(1, 1) + at(2, 2) * o.at(2, 1);
		T m33 = at(2, 0) * o.at(0, 2) + at(2, 1) * o.at(1, 2) + at(2, 2) * o.at(2, 2);

		at(0, 0) = m11; at(0, 1) = m12; at(0, 2) = m13;
		at(1, 0) = m21; at(1, 1) = m22; at(1, 2) = m23;
		at(2, 0) = m31; at(2, 1) = m32; at(2, 2) = m33;

		return *this;
	}

	CMatrix3 operator+(const CMatrix3& m) const
	{
		T m11 = at(0, 0) + m.at(0, 0);
		T m12 = at(0, 1) + m.at(0, 1);
		T m13 = at(0, 2) + m.at(0, 2);

		T m21 = at(1, 0) + m.at(1, 0);
		T m22 = at(1, 1) + m.at(1, 1);
		T m23 = at(1, 2) + m.at(1, 2);

		T m31 = at(2, 0) + m.at(2, 0);
		T m32 = at(2, 1) + m.at(2, 1);
		T m33 = at(2, 2) + m.at(2, 2);

		CMatrix3<T> t;
		t.at(0, 0) = m11; t.at(0, 1) = m12; t.at(0, 2) = m13;
		t.at(1, 0) = m21; t.at(1, 1) = m22; t.at(1, 2) = m23;
		t.at(2, 0) = m31; t.at(2, 1) = m32; t.at(2, 2) = m33;
		return t;
	}

	CMatrix3 operator+=(const CMatrix3& m)
	{
		at(0, 0) += m.at(0, 0);
		at(0, 1) += m.at(0, 1);
		at(0, 2) += m.at(0, 2);

		at(1, 0) += m.at(1, 0);
		at(1, 1) += m.at(1, 1);
		at(1, 2) += m.at(1, 2);

		at(2, 0) += m.at(2, 0);
		at(2, 1) += m.at(2, 1);
		at(2, 2) += m.at(2, 2);
	}

	CMatrix3 operator-(const CMatrix3& m) const
	{
		T m11 = at(0, 0) - m.at(0, 0);
		T m12 = at(0, 1) - m.at(0, 1);
		T m13 = at(0, 2) - m.at(0, 2);

		T m21 = at(1, 0) - m.at(1, 0);
		T m22 = at(1, 1) - m.at(1, 1);
		T m23 = at(1, 2) - m.at(1, 2);

		T m31 = at(2, 0) - m.at(2, 0);
		T m32 = at(2, 1) - m.at(2, 1);
		T m33 = at(2, 2) - m.at(2, 2);

		CMatrix3<T> t;
		t.at(0, 0) = m11; t.at(0, 1) = m12; t.at(0, 2) = m13;
		t.at(1, 0) = m21; t.at(1, 1) = m22; t.at(1, 2) = m23;
		t.at(2, 0) = m31; t.at(2, 1) = m32; t.at(2, 2) = m33;
		return t;
	}

	CMatrix3 operator-=(const CMatrix3& m) const
	{
		at(0, 0) -= m.at(0, 0);
		at(0, 1) -= m.at(0, 1);
		at(0, 2) -= m.at(0, 2);

		at(1, 0) -= m.at(1, 0);
		at(1, 1) -= m.at(1, 1);
		at(1, 2) -= m.at(1, 2);

		at(2, 0) -= m.at(2, 0);
		at(2, 1) -= m.at(2, 1);
		at(2, 2) -= m.at(2, 2);
	}

	CMatrix3 operator*(const T& factor) const
	{
		T m11 = at(0, 0) * factor;
		T m12 = at(0, 1) * factor;
		T m13 = at(0, 2) * factor;

		T m21 = at(1, 0) * factor;
		T m22 = at(1, 1) * factor;
		T m23 = at(1, 2) * factor;

		T m31 = at(2, 0) * factor;
		T m32 = at(2, 1) * factor;
		T m33 = at(2, 2) * factor;

		CMatrix3<T> t;
		t.at(0, 0) = m11; t.at(0, 1) = m12; t.at(0, 2) = m13;
		t.at(1, 0) = m21; t.at(1, 1) = m22; t.at(1, 2) = m23;
		t.at(2, 0) = m31; t.at(2, 1) = m32; t.at(2, 2) = m33;
		return t;
	}

	CMatrix3 operator*=(const T& factor) const
	{
		at(0, 0) *= factor;
		at(0, 1) *= factor;
		at(0, 2) *= factor;

		at(1, 0) *= factor;
		at(1, 1) *= factor;
		at(1, 2) *= factor;

		at(2, 0) *= factor;
		at(2, 1) *= factor;
		at(2, 2) *= factor;
	}

	CMatrix3 operator/(const T& divisor) const
	{
		T m11 = at(0, 0) / divisor;
		T m12 = at(0, 1) / divisor;
		T m13 = at(0, 2) / divisor;

		T m21 = at(1, 0) / divisor;
		T m22 = at(1, 1) / divisor;
		T m23 = at(1, 2) / divisor;

		T m31 = at(2, 0) / divisor;
		T m32 = at(2, 1) / divisor;
		T m33 = at(2, 2) / divisor;

		CMatrix3<T> t;
		t.at(0, 0) = m11; t.at(0, 1) = m12; t.at(0, 2) = m13;
		t.at(1, 0) = m21; t.at(1, 1) = m22; t.at(1, 2) = m23;
		t.at(2, 0) = m31; t.at(2, 1) = m32; t.at(2, 2) = m33;
		return t;
	}

	CMatrix3 operator/=(const T& divisor) const
	{
		at(0, 0) /= divisor;
		at(0, 1) /= divisor;
		at(0, 2) /= divisor;

		at(1, 0) /= divisor;
		at(1, 1) /= divisor;
		at(1, 2) /= divisor;

		at(2, 0) /= divisor;
		at(2, 1) /= divisor;
		at(2, 2) /= divisor;
	}

	static CMatrix3<T> identity()
	{
		return CMatrix3<T>();
	}

	static CMatrix3<T> zeroes()
	{
		CMatrix3<T> t;
		t.at(0, 0) = t.at(0, 1) = t.at(0, 2) = 0;
		t.at(1, 0) = t.at(1, 1) = t.at(1, 2) = 0;
		t.at(2, 0) = t.at(2, 1) = t.at(2, 2) = 0;
		return t;
	}

	inline double determinant() const
	{
		return
			at(0, 0) * (at(2, 2) * at(1, 1) - at(2, 1) * at(1, 2)) -
			at(1, 0) * (at(2, 2) * at(0, 1) - at(2, 1) * at(0, 2)) +
			at(2, 0) * (at(1, 2) * at(0, 1) - at(1, 1) * at(0, 2));
	}

	bool isInvertible() const
	{
		return determinant() != 0;
	}

	CMatrix3<T> inverted(bool* ok = nullptr) const
	{
		double det = determinant();
		if (det != 0) {
			CMatrix3<T> invert = adjoint() / det;
			if (ok)
				*ok = true;
			return invert;
		}
		else {
			if (ok)
				*ok = false;
			return identity();
		}
	}

	CMatrix3<T> adjoint() const
	{
		T h11, h12, h13, h21, h22, h23, h31, h32, h33;
		h11 = at(1, 1) * at(2, 2) - at(1, 2) * at(2, 1);
		h21 = at(1, 2) * at(2, 0) - at(1, 0) * at(2, 2);
		h31 = at(1, 0) * at(2, 1) - at(1, 1) * at(2, 0);
		h12 = at(0, 2) * at(2, 1) - at(0, 1) * at(2, 2);
		h22 = at(0, 0) * at(2, 2) - at(0, 2) * at(2, 0);
		h32 = at(0, 1) * at(2, 0) - at(0, 0) * at(2, 1);
		h13 = at(0, 1) * at(1, 2) - at(0, 2) * at(1, 1);
		h23 = at(0, 2) * at(1, 0) - at(0, 0) * at(1, 2);
		h33 = at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0);

		CMatrix3<T> t;
		t.at(0, 0) = h11; t.at(0, 1) = h12; t.at(0, 2) = h13;
		t.at(1, 0) = h21; t.at(1, 1) = h22; t.at(1, 2) = h23;
		t.at(2, 0) = h31; t.at(2, 1) = h32; t.at(2, 2) = h33;
		return t;
	}

	CMatrix3 transposed() const
	{
		CMatrix3<T> t;
		t.at(0, 0) = at(0, 0); t.at(0, 1) = at(1, 0); t.at(0, 2) = at(2, 0);
		t.at(0, 1) = at(1, 0); t.at(1, 1) = at(1, 1); t.at(1, 2) = at(2, 1);
		t.at(0, 2) = at(2, 0); t.at(2, 1) = at(1, 2); t.at(2, 2) = at(2, 2);
		return t;
	}

	CMatrix3 t() const
	{
		return transposed();
	}

	CVector3<T> operator*(const CVector3<T>& point) const
	{
		return CVector3<T>(
			point.x() * at(0, 0) + point.y() * at(0, 1) + point.z() * at(0, 2),
			point.x() * at(1, 0) + point.y() * at(1, 1) + point.z() * at(1, 2),
			point.x() * at(2, 0) + point.y() * at(2, 1) + point.z() * at(2, 2)
			);
	}
};

using CMatrix3d = CMatrix3<double>;
