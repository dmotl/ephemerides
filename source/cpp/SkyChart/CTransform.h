/*!
*  \file      CTransform.h
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

#include "CPoint.h"
#include <CMatrix3.h>

/*!
* The CTransform template class specifies transformations of a 2D coordinate system
* 
* A transformation specifies how to translate, scale, shear, rotate or project the 
* 2D coordinate system. 
* 
* A CTransform object can be built using the setMatrix(), scale(), rotate(), translate() 
* and shear() functions. Alternatively, it can be built by applying basic matrix operations. 
* The matrix can also be defined when constructed, and it can be reset to the identity 
* matrix (the default) using the reset() function.
* 
* The CTransform class supports mapping of graphic primitives: A given point, line or path.
* 
* The CTransform provides the isIdentity() function which returns true if the matrix is the 
* identity matrix, and the isInvertible() function which returns true if the matrix is non-singular 
* (i.e. AB = BA = I). The inverted() function returns an inverted copy of this matrix if it is invertible 
* (otherwise it returns the identity matrix), and adjoint() returns the matrix's classical adjoint. 
* In addition, CTransform provides the determinant() function which returns the matrix's determinant.
* 
* Finally, the CTransform class supports matrix multiplication, addition and subtraction.
*/
template<typename T>
class CTransform : public CMatrix3<T>
{
public:
	/*! Constructs an identity matrix */
	CTransform() {}

	/*! Constructor with initialization */
	CTransform(const T& m11, const T& m12, const T& m21, const T& m22, const T& dx, const T& dy)
	{
		CMatrix3<T>::at(0, 0) = m11;
		CMatrix3<T>::at(0, 1) = m12;
		CMatrix3<T>::at(1, 0) = m21;
		CMatrix3<T>::at(1, 1) = m22;
		CMatrix3<T>::at(2, 0) = dx;
		CMatrix3<T>::at(2, 1) = dy;
	}

	/*! Copy constructor */
	CTransform(const CMatrix3<T>& other) : CMatrix3<T>(other) {}

	/*! Copy constructor */
	CTransform(const CTransform<T>& other) : CMatrix3<T>(other) {}

	/*! Map x and y coordinates
	* 
	* Maps the given coordinates x and y into the coordinate system defined by this matrix. 
	* The resulting values are put in *tx and *ty, respectively.
	*/
	void map(const T& x, const T& y, const T* tx, const T* ty) const
	{
		if (tx)
			*tx = m11() * x + m21() * y + dx();
		if (ty)
			*ty = m12() * x + m22() * y + dy();
	}

	/*! Map a point
	* 
	* Returns a CPoint object with is a copy of the given point, mapped
	* to the coordinate system defined by this transformation.
	*/
	CPoint<T> map(const CPoint<T>& point) const
	{
		const T& fx = point.x(), & fy = point.y();
		return { m11() * fx + m21() * fy + dx(), m12() * fx + m22() * fy + dy() };
	}

	const T& m11() const { return CMatrix3<T>::at(0, 0); }
	const T& m12() const { return CMatrix3<T>::at(0, 1); }
	const T& m13() const { return CMatrix3<T>::at(0, 2); }
	const T& m21() const { return CMatrix3<T>::at(1, 0); }
	const T& m22() const { return CMatrix3<T>::at(1, 1); }
	const T& m23() const { return CMatrix3<T>::at(1, 2); }
	const T& m31() const { return CMatrix3<T>::at(2, 0); }
	const T& m32() const { return CMatrix3<T>::at(2, 1); }
	const T& m33() const { return CMatrix3<T>::at(2, 2); }

	const T& dx() const { return m31(); }
	const T& dy() const { return m32(); }

	static CTransform<T> fromRotation(double angle)
	{
		T sina = std::sin(angle);
		T cosa = std::cos(angle);

		CMatrix3<T> t;
		t.at(0, 0) = cosa;
		t.at(0, 1) = sina;
		t.at(1, 0) = -sina;
		t.at(1, 1) = cosa;
		return t;
	}

	static CTransform<T> fromScale(const T& sx, const T& sy)
	{
		return CTransform<T>(sx, 0, 0, sy, 0, 0);
	}

	static CTransform<T> fromTranslate(const T& dx, const T& dy)
	{
		return CTransform<T>(1, 0, 0, 1, dx, dy);
	}

	constexpr friend inline CPoint<T> operator*(const CPoint<T>& p, const CTransform& m)
	{
		return m.map(p);
	}
};

//using CTransformd = CTransform<double>;
