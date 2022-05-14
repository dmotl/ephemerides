/*!
*  \file      SkyChartUtils.h
*  \author    David Motl
*  \date      2022-05-11
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

namespace Utils
{
	template<typename T>
	class CVector3
	{
	public:
		CVector3() {}
		CVector3(const T& x, const T& y, const T& z) { m_x[0] = x; m_x[1] = y; m_x[2] = z; }
		CVector3(const double *xyz) { m_x[0] = xyz[0]; m_x[1] = xyz[1]; m_x[2] = xyz[2]; }

		double x() const { return m_x[0]; }
		double y() const { return m_x[1]; }
		double z() const { return m_x[2]; }

		CVector3<T> operator*(double k) const {
			return CVector3<T>(k * m_x[0], k * m_x[1], k * m_x[2]);
		}
		double length() const {
			return sqrt((*this) * (*this));
		}
		double operator*(const CVector3<T> b) const {
			return m_x[0] * b.m_x[0] + m_x[1] * b.m_x[1] + m_x[2] * b.m_x[2];
		}
		CVector3<T> operator+(const CVector3<T> b) const
		{
			return CVector3<T>(m_x[0] + b.m_x[0], m_x[1] + b.m_x[1], m_x[2] + b.m_x[2]);
		}
		CVector3<T> operator-(const CVector3<T> b) const
		{
			return CVector3<T>(m_x[0] - b.m_x[0], m_x[1] - b.m_x[1], m_x[2] - b.m_x[2]);
		}

		bool isNull() const {
			return (*this) * (*this) == 0;
		}

	private:
		T m_x[3];
	};

	using CVector3d = CVector3<double>;

	/* Converts VSOP87 ecliptical rectangular coordinates to the
	 * equatorial frame FK5 J2000. This should be used
	 * for VSOP87A and VSOP87E.
	 *
	 * \param in VSOP87 coordinates
	 * \param out FK5 J2000 coordinates
	 */
	CVector3d vsop87ToFK5(const CVector3d& in);

	/* Convert equatorial rectangular coordinates to spherical ones.
	* 
	* \param xyz FK5 J2000 equatorial coordinates
	* \return equatorial spherical coordinates
	 */
	void rectangularToSperical(const CVector3d& xyz, double *lng, double *lat);

	/* Compute aberration shift to position of a planet
	 *
	 * \param planet_distance distance between the observer and the planet [AU]
	 * \param earth_velocity ecliptic velocity of the observer [AU/d]
	 * \return aberration shift [AU]
	 */
	CVector3d aberrationPush(double planet_distance, const CVector3d& earth_velocity);
}
