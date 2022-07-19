/*!
*  \file      CQuaternion.h
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

#include "CVector3.h"
#include "CMatrix3.h"

template<typename T>
class CQuaternion : public std::array<T, 4>
{
public:
	CQuaternion() { at(0) = 1; at(1) = at(2) = at(3) = 0; }

	CQuaternion(const T& scalar, const T& x, const T& y, const T& z) { at(0) = scalar; at(1) = x; at(2) = y; at(3) = z; }

	CQuaternion(const T& scalar, const CVector3<T>& vector) { at(0) = scalar; at(1) = vector[0]; at(2) = vector[1]; at(3) = vector[2]; }

	CQuaternion(int n, const T* sxyz) { assert(n == 4); at(0) = sxyz[0]; at(1) = sxyz[1]; at(2) = sxyz[2]; at(3) = sxyz[3]; }

	T& scalar(void) { return at(0); }
	const T& scalar(void) const { return at(0); }
	void setScalar(const T& val) { at(0) = val; }

	T& x(void) { return at(1); }
	const T& x(void) const { return at(1); }
	void setX(const T& val) { at(1) = val; }

	T& y(void) { return at(2); }
	const T& y(void) const { return at(2); }
	void setY(const T& val) { at(2) = val; }

	T& z(void) { return at(3); }
	const T& z(void) const { return at(3); }
	void setZ(const T& val) { at(3) = val; }

	CVector3<T> vector() const 
	{
		return { at(1), at(2), at(3) };
	}
	void setVector(const CVector3<T>& v)
	{
		at(1) = v.at(0); at(2) = v.at(1); at(3) = v.at(2);
	}

	T& at(int i)
	{
		return std::array<T, 4>::at(i);
	}
	const T& at(int i) const
	{
		return std::array<T, 4>::at(i);
	}

	static CQuaternion<T> identity()
	{
		return CQuaternion<T>();
	}

	bool isNull() const
	{
		return at(0) == 0 && at(1) == 0 && at(2) == 0 && at(3) == 0;
	}

	bool isIdentity() const
	{
		return at(0) == 1 && at(1) == 0 && at(2) == 0 && at(3) == 0;
	}

	T dotProduct(const CQuaternion& b) const
	{
		return dotProduct(*this, b);
	}

	static T dotProduct(const CQuaternion& q1, const CQuaternion& q2)
	{
		return q1.at(0) * q2.at(0) + q1.at(1) * q2.at(1) + q1.at(2) * q2.at(2) + q1.at(3) * q2.at(3);
	}

	T length() const
	{
		return norm();
	}

	T norm() const
	{
		return std::sqrt(dotProduct(*this, *this));
	}

	T lengthSquared() const
	{
		return dotProduct(*this, *this);
	}

	CQuaternion normalized() const
	{
		const T scale = length();
		if (scale == 1)
			return *this;
		if (scale == 0)
			return { 0, 0, 0, 0 };
		return *this / scale;
	}

	void normalize()
	{
		const T len = length();
		if (len != 1.0 && len != 0.0) {
			at(0) /= len;
			at(1) /= len;
			at(2) /= len;
			at(3) /= len;
		}
	}

	CQuaternion inverted() const
	{
		double len = length();
		if (len != 0)
			return { at(0) / len, -at(1) / len, -at(2) / len, -at(3) / len };
		return { 0, 0, 0, 0 };
	}

	CQuaternion conjugated() const
	{
		return { at(0), -at(1), -at(2), -at(3) };
	}

	CVector3<T> rotatedVector(const CVector3<T>& vec) const
	{
		return (*this * CQuaternion(0, vec) * conjugated()).vector();
	}

	CQuaternion& operator+=(const CQuaternion& quaternion)
	{
		at(0) += quaternion.at(0);
		at(1) += quaternion.at(1);
		at(2) += quaternion.at(2);
		at(3) += quaternion.at(3);
		return *this;
	}

	CQuaternion& operator-=(const CQuaternion& quaternion)
	{
		at(0) -= quaternion.at(0);
		at(1) -= quaternion.at(1);
		at(2) -= quaternion.at(2);
		at(3) -= quaternion.at(3);
		return *this;
	}

	CQuaternion& operator*=(const T& factor)
	{
		at(0) *= factor;
		at(1) *= factor;
		at(2) *= factor;
		at(3) *= factor;
		return *this;
	}

	inline CQuaternion& operator*=(const CQuaternion& quaternion)
	{
		*this = *this * quaternion;
		return *this;
	}

	CQuaternion& operator/=(const T& divisor)
	{
		at(0) /= divisor;
		at(1) /= divisor;
		at(2) /= divisor;
		at(3) /= divisor;
		return *this;
	}

	void getAxisAndAngle(CVector3<T>* axis, T* angle) const
	{
		T aX, aY, aZ;
		getAxisAndAngle(&aX, &aY, &aZ, angle);
		*axis = QVector3D(aX, aY, aZ);
	}

	CQuaternion fromAxisAndAngle(const CVector3<T>& axis, const T& angle)
	{
		// Algorithm from:
		// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q56
		// We normalize the result just in case the values are close
		// to zero, as suggested in the above FAQ.
		T s = std::sin(angle);
		T c = std::cos(angle);
		QVector3D ax = axis.normalized();
		return CQuaternion(c, ax.x() * s, ax.y() * s, ax.z() * s).normalized();	}

	void getAxisAndAngle(T* x, T* y, T* z, T* angle) const
	{
		assert(x != nullptr && y != nullptr && z != nullptr && angle != nullptr);

		// The quaternion representing the rotation is
		//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

		const T length = std::hypot(at(1), at(2), at(3));
		if (length > 0) {
			if (length == 1) {
				*x = at(1);
				*y = at(2);
				*z = at(3);
			}
			else {
				*x = at(1) / length;
				*y = at(2) / length;
				*z = at(3) / length;
			}
			*angle = 2.0 * std::acos(at(0));
		}
		else {
			// angle is 0 (mod 2*pi), so any axis will fit
			*x = *y = *z = *angle = 0;
		}
	}

	CQuaternion fromAxisAndAngle(const T& x, const T& y, const T& z, const T& angle)
	{
		T length = std::hypot(x, y, z);
		if (length != 1 && length != 0) {
			x /= length;
			y /= length;
			z /= length;
		}
		T a = angle / 2.0;
		T s = std::sin(a);
		T c = std::cos(a);
		return CQuaternion(c, x * s, y * s, z * s).normalized();
	}

	CVector3<T> toEulerAngles() const
	{
		T pitch, yaw, roll;
		getEulerAngles(&pitch, &yaw, &roll);
		return QVector3D(pitch, yaw, roll);
	}

	CQuaternion fromEulerAngles(const CVector3<T>& eulerAngles)
	{
		return CQuaternion::fromEulerAngles(eulerAngles.x(), eulerAngles.y(), eulerAngles.z());
	}

	T pitch(void) const
	{
		// Algorithm adapted from:
		// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q37

		const T len = length();
		const bool rescale = len != 1 && len != 0;
		const T xps = rescale ? at(1) / len : at(1);
		const T yps = rescale ? at(2) / len : at(2);
		const T zps = rescale ? at(3) / len : at(3);
		const T wps = rescale ? at(0) / len : at(0);

		const T xw = xps * wps;
		const T yz = yps * zps;

		const T sinp = -2.0 * (yz - xw);
		return (std::abs(sinp) >= 1.0 ? std::copysign(M_PI_2, sinp) : std::asin(sinp));
	}

	T yaw(void) const
	{
		// Algorithm adapted from:
		// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q37

		const T len = length();
		const bool rescale = len != 1 && len != 0;
		const T xps = rescale ? at(1) / len : at(1);
		const T yps = rescale ? at(2) / len : at(2);
		const T zps = rescale ? at(3) / len : at(3);
		const T wps = rescale ? at(0) / len : at(0);

		const T xx = xps * xps;
		const T xy = xps * yps;
		const T xz = xps * zps;
		const T xw = xps * wps;
		const T yy = yps * yps;
		const T yz = yps * zps;
		const T yw = yps * wps;
		const T zz = zps * zps;
		const T zw = zps * wps;

		const T sinp = -2.0 * (yz - xw);
		const T pitch = (std::abs(sinp) >= 1.0 ? std::copysign(M_PI_2, sinp) : std::asin(sinp));
		if (pitch < M_PI_2) {
			if (pitch > -M_PI_2) {
				return std::atan2(2.0f * (xz + yw), 1.0f - 2.0f * (xx + yy));
			}
			else {
				// not a unique solution
				return -std::atan2(-2.0f * (xy - zw), 1.0f - 2.0f * (yy + zz));
			}
		}
		else {
			// not a unique solution
			return std::atan2(-2.0f * (xy - zw), 1.0f - 2.0f * (yy + zz));
		}
	}

	T roll(void) const
	{
		// Algorithm adapted from:
		// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q37

		const T len = length();
		const bool rescale = len != 1 && len != 0;
		const T xps = rescale ? at(1) / len : at(1);
		const T yps = rescale ? at(2) / len : at(2);
		const T zps = rescale ? at(3) / len : at(3);
		const T wps = rescale ? at(0) / len : at(0);

		const T xx = xps * xps;
		const T xy = xps * yps;
		const T xz = xps * zps;
		const T xw = xps * wps;
		const T yy = yps * yps;
		const T yz = yps * zps;
		const T yw = yps * wps;
		const T zz = zps * zps;
		const T zw = zps * wps;

		const T sinp = -2.0 * (yz - xw);
		const T pitch = (std::abs(sinp) >= 1.0 ? std::copysign(M_PI_2, sinp) : std::asin(sinp));
		if (pitch < M_PI_2 && pitch > -M_PI_2)
			return std::atan2(2.0 * (xy + zw), 1.0 - 2.0 * (xx + zz));
		return 0;
	}

	void getEulerAngles(T* pitch, T* yaw, T* roll) const
	{
		Q_ASSERT(pitch && yaw && roll);

		// Algorithm adapted from:
		// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q37

		const T len = length();
		const bool rescale = len != 1 && len != 0;
		const T xps = rescale ? at(1) / len : at(1);
		const T yps = rescale ? at(2) / len : at(2);
		const T zps = rescale ? at(3) / len : at(3);
		const T wps = rescale ? at(0) / len : at(0);

		const T xx = xps * xps;
		const T xy = xps * yps;
		const T xz = xps * zps;
		const T xw = xps * wps;
		const T yy = yps * yps;
		const T yz = yps * zps;
		const T yw = yps * wps;
		const T zz = zps * zps;
		const T zw = zps * wps;

		const T sinp = -2.0 * (yz - xw);
		if (std::abs(sinp) >= 1.0)
			*pitch = std::copysign(M_PI_2, sinp);
		else
			*pitch = std::asin(sinp);
		if (*pitch < M_PI_2) {
			if (*pitch > -M_PI_2) {
				*yaw = std::atan2(2.0 * (xz + yw), 1.0 - 2.0 * (xx + yy));
				*roll = std::atan2(2.0 * (xy + zw), 1.0 - 2.0 * (xx + zz));
			}
			else {
				// not a unique solution
				*roll = 0;
				*yaw = -std::atan2(-2.0 * (xy - zw), 1.0 - 2.0 * (yy + zz));
			}
		}
		else {
			// not a unique solution
			*roll = 0;
			*yaw = std::atan2(-2.0 * (xy - zw), 1.0 - 2.0 * (yy + zz));
		}
	}

	static CQuaternion fromPitch(const T& pitch)
	{
		// Algorithm from:
		// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q60

		pitch *= 0.5f;

		const T c3 = std::cos(pitch);
		const T s3 = std::sin(pitch);

		return CQuaternion(c3, s3, 0, 0);
	}

	static CQuaternion fromYaw(const T& yaw)
	{
		// Algorithm from:
		// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q60

		yaw *= 0.5f;

		const T c1 = std::cos(yaw);
		const T s1 = std::sin(yaw);

		return CQuaternion(c1, 0, s1, 0);
	}

	static CQuaternion fromRoll(const T& roll)
	{
		// Algorithm from:
		// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q60

		roll *= 0.5f;

		const T c2 = std::cos(roll);
		const T s2 = std::sin(roll);

		return CQuaternion(c2, 0, 0, s2);
	}

	static CQuaternion fromEulerAngles(const T& pitch, const T& yaw, const T& roll)
	{
		// Algorithm from:
		// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q60

		T half_pitch = pitch * 0.5, half_yaw = yaw * 0.5, half_roll = roll * 0.5;

		const T c1 = std::cos(half_yaw);
		const T s1 = std::sin(half_yaw);
		const T c2 = std::cos(half_roll);
		const T s2 = std::sin(half_roll);
		const T c3 = std::cos(half_pitch);
		const T s3 = std::sin(half_pitch);
		const T c1c2 = c1 * c2;
		const T s1s2 = s1 * s2;

		const T w = c1c2 * c3 + s1s2 * s3;
		const T x = c1c2 * s3 + s1s2 * c3;
		const T y = s1 * c2 * c3 - c1 * s2 * s3;
		const T z = c1 * s2 * c3 - s1 * c2 * s3;

		return CQuaternion(w, x, y, z);	
	}

	static CQuaternion rotationTo(const CVector3<T>& from, const CVector3<T>& to)
	{
		// Based on Stan Melax's article in Game Programming Gems

		const CVector3<T> v0(from.normalized());
		const CVector3<T> v1(to.normalized());

		T d = CVector3<T>::dotProduct(v0, v1) + 1.0;

		// if dest vector is close to the inverse of source vector, ANY axis of rotation is valid
		if (d == 0) {
			CVector3<T> axis = CVector3<T>::crossProduct(CVector3<T>(1.0, 0.0, 0.0), v0);
			if (axis.lengthSquared() == 0)
				axis = CVector3<T>::crossProduct(CVector3<T>(0.0, 1.0, 0.0), v0);
			axis.normalize();

			// same as CQuaternion::fromAxisAndAngle(axis, 180.0f)
			return CQuaternion(0.0, axis.x(), axis.y(), axis.z());
		}
		else {
			d = std::sqrt(2.0 * d);
			const CVector3<T> axis(CVector3<T>::crossProduct(v0, v1) / d);
			return CQuaternion(d * 0.5, axis).normalized();
		}
	}

	CMatrix3<T> toRotationMatrix() const
	{
		// Algorithm from:
		// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q54

		const T f2x = at(1) + at(1);
		const T f2y = at(2) + at(2);
		const T f2z = at(3) + at(3);
		const T f2xw = f2x * at(0);
		const T f2yw = f2y * at(0);
		const T f2zw = f2z * at(0);
		const T f2xx = f2x * at(1);
		const T f2xy = f2x * at(2);
		const T f2xz = f2x * at(3);
		const T f2yy = f2y * at(2);
		const T f2yz = f2y * at(3);
		const T f2zz = f2z * at(3);

		CMatrix3<T> rot3x3;
		rot3x3.at(0, 0) = 1.0 - (f2yy + f2zz);
		rot3x3.at(0, 1) = f2xy - f2zw;
		rot3x3.at(0, 2) = f2xz + f2yw;
		rot3x3.at(1, 0) = f2xy + f2zw;
		rot3x3.at(1, 1) = 1.0 - (f2xx + f2zz);
		rot3x3.at(1, 2) = f2yz - f2xw;
		rot3x3.at(2, 0) = f2xz - f2yw;
		rot3x3.at(2, 1) = f2yz + f2xw;
		rot3x3.at(2, 2) = 1.0 - (f2xx + f2yy);

		return rot3x3;
	}

	static CQuaternion<T> fromRotationMatrix(const CMatrix3<T>& rot3x3)
	{
		// Algorithm from:
		// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q55

		T scalar;
		T axis[3];

		const T trace = rot3x3(0, 0) + rot3x3(1, 1) + rot3x3(2, 2);
		if (trace > 0.00000001f) {
			const T s = 2.0f * std::sqrt(trace + 1.0f);
			scalar = 0.25f * s;
			axis[0] = (rot3x3(2, 1) - rot3x3(1, 2)) / s;
			axis[1] = (rot3x3(0, 2) - rot3x3(2, 0)) / s;
			axis[2] = (rot3x3(1, 0) - rot3x3(0, 1)) / s;
		}
		else {
			static int s_next[3] = { 1, 2, 0 };
			int i = 0;
			if (rot3x3(1, 1) > rot3x3(0, 0))
				i = 1;
			if (rot3x3(2, 2) > rot3x3(i, i))
				i = 2;
			int j = s_next[i];
			int k = s_next[j];

			const T s = 2.0f * std::sqrt(rot3x3(i, i) - rot3x3(j, j) - rot3x3(k, k) + 1.0f);
			axis[i] = 0.25f * s;
			scalar = (rot3x3(k, j) - rot3x3(j, k)) / s;
			axis[j] = (rot3x3(j, i) + rot3x3(i, j)) / s;
			axis[k] = (rot3x3(k, i) + rot3x3(i, k)) / s;
		}

		return CQuaternion<T>(scalar, axis[0], axis[1], axis[2]);
	}

	void getAxes(CVector3<T>* xAxis, CVector3<T>* yAxis, CVector3<T>* zAxis) const
	{
		Q_ASSERT(xAxis && yAxis && zAxis);

		const CMatrix3<T> rot3x3(toRotationMatrix());

		*xAxis = CVector3<T>(rot3x3(0, 0), rot3x3(1, 0), rot3x3(2, 0));
		*yAxis = CVector3<T>(rot3x3(0, 1), rot3x3(1, 1), rot3x3(2, 1));
		*zAxis = CVector3<T>(rot3x3(0, 2), rot3x3(1, 2), rot3x3(2, 2));
	}

	static CQuaternion<T> fromAxes(const CVector3<T>& xAxis, const CVector3<T>& yAxis, const CVector3<T>& zAxis)
	{
		CMatrix3<T> rot3x3(Qt::Uninitialized);
		rot3x3(0, 0) = xAxis.x();
		rot3x3(1, 0) = xAxis.y();
		rot3x3(2, 0) = xAxis.z();
		rot3x3(0, 1) = yAxis.x();
		rot3x3(1, 1) = yAxis.y();
		rot3x3(2, 1) = yAxis.z();
		rot3x3(0, 2) = zAxis.x();
		rot3x3(1, 2) = zAxis.y();
		rot3x3(2, 2) = zAxis.z();

		return CQuaternion<T>::fromRotationMatrix(rot3x3);
	}

	bool operator==(const CQuaternion<T>& other) const
	{
		return at(0) == other.at(0) && at(1) == other.at(1) && at(2) == other.at(2) && at(3) == other.at(3);
	}

	bool operator!=(const CQuaternion<T>& other) const 
	{ 
		return !operator==(other); 
	}
};

template<typename T>
inline CQuaternion<T> operator*(const CQuaternion<T>& q1, const CQuaternion<T>& q2)
{
	T yy = (q1.at(0) - q1.at(2)) * (q2.at(0) + q2.at(3));
	T zz = (q1.at(0) + q1.at(2)) * (q2.at(0) - q2.at(3));
	T ww = (q1.at(3) + q1.at(1)) * (q2.at(1) + q2.at(2));
	T xx = ww + yy + zz;
	T qq = 0.5 * (xx + (q1.at(3) - q1.at(1)) * (q2.at(1) - q2.at(2)));

	T w = qq - ww + (q1.at(3) - q1.at(2)) * (q2.at(2) - q2.at(3));
	T x = qq - xx + (q1.at(1) + q1.at(0)) * (q2.at(1) + q2.at(0));
	T y = qq - yy + (q1.at(0) - q1.at(1)) * (q2.at(2) + q2.at(3));
	T z = qq - zz + (q1.at(3) + q1.at(2)) * (q2.at(0) - q2.at(1));

	return CQuaternion(w, x, y, z);
}

template<typename T>
inline const CQuaternion<T> operator+(const CQuaternion<T>& q1, const CQuaternion<T>& q2)
{
	return CQuaternion(q1.at(0) + q2.at(0), q1.at(1) + q2.at(1), q1.at(2) + q2.at(2), q1.at(3) + q2.at(3));
}

template<typename T>
inline const CQuaternion<T> operator-(const CQuaternion<T>& q1, const CQuaternion<T>& q2)
{
	return CQuaternion(q1.at(0) - q2.at(0), q1.at(1) - q2.at(1), q1.at(2) - q2.at(2), q1.at(3) - q2.at(3));
}

template<typename T>
inline const CQuaternion<T> operator*(T factor, const CQuaternion<T>& quaternion)
{
	return CQuaternion(quaternion.at(0) * factor, quaternion.at(1) * factor, quaternion.at(2) * factor, quaternion.at(3) * factor);
}

template<typename T>
inline const CQuaternion<T> operator*(const CQuaternion<T>& quaternion, T factor)
{
	return CQuaternion(quaternion.at(0) * factor, quaternion.at(1) * factor, quaternion.at(2) * factor, quaternion.at(3) * factor);
}

template<typename T>
inline const CQuaternion<T> operator-(const CQuaternion<T>& quaternion)
{
	return CQuaternion(-quaternion.at(0), -quaternion.at(1), -quaternion.at(2), -quaternion.at(3));
}

template<typename T>
inline const CQuaternion<T> operator/(const CQuaternion<T>& quaternion, T divisor)
{
	return CQuaternion(quaternion.at(0) / divisor, quaternion.at(1) / divisor, quaternion.at(2) / divisor, quaternion.at(3) / divisor);
}

using CQuaterniond = CQuaternion<double>;
