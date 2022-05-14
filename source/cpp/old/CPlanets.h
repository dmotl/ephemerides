/*!
*  \file      CPlanets.h
*  \author    David Motl
*  \date      2022-01-31
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

/*!
* Model of positions of the planets, the Sun and the Moon
*
* The CPlanets class implements a mathematical model for computing
* position of the planets, the Sun and the Moon. 
* 
* Source:
* Pokorny Z.: Astronomicke algoritmy pro kalkulatory, Prague 1988
* 
*/
class CPlanets
{
public:
	/*
	* \brief Constructor
	* 
	* \param jd_utc time as Julian date in UTC
	*/
	explicit CPlanets(double jd_utc = 0);

	/*
	* Reinitialize the object for different time
	* 
	* \param jd_utc time as Julian date in UTC
	*/
	void setJD(double jd_utc);

	/* Moon
	*  
	* The function computes the equatorial coordinates of the Moon, Earth-Moon
	* distance and lunar phase. 
	* 
	* The phase is expressed in radians:
	* - 0 for new moon
	* - pi/2 for first quarter
	* - pi for full moon
	* - 3pi/2 for last quarter
	* 
	* \param ra right ascention of equatorial coordinates, in radians
	* \param dec declination of equatorial coordinates, in radians
	* \param rad Earth-Moon distance in AU
	* \param phase phase in radians - see description
	*/
	void Moon(double *ra, double *dec, double *rad = nullptr, double *phase = nullptr) const;

	/* Sun
	* 
	* The function computes the equatorial coordinates of the Sun and the Sun-Earth distance.
	* 
	* \param ra right ascention of equatorial coordinates, in radians
	* \param dec declination of equatorial coordinates, in radians
	* \param rad Earth-Moon distance in AU
	*/
	void Sun(double* ra, double* dec, double* rad = nullptr) const;

	/* Mercury
	*
	* The function computes the equatorial coordinates of Mercury, its distance
	* to the Earth and its phase.
	*
	* \param ra right ascention of equatorial coordinates, in radians
	* \param dec declination of equatorial coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	void Mercury(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;

	/* Venus
	*
	* The function computes the equatorial coordinates of Venus, its distance
	* to the Earth and its phase.
	*
	* \param ra right ascention of equatorial coordinates, in radians
	* \param dec declination of equatorial coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	void Venus(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;

	/* Mars
	*
	* The function computes the equatorial coordinates of Mars, its distance
	* to the Earth and its phase.
	*
	* \param ra right ascention of equatorial coordinates, in radians
	* \param dec declination of equatorial coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	void Mars(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;

	/* Jupiter
	*
	* The function computes the equatorial coordinates of Jupiter, its distance
	* to the Earth and its phase.
	*
	* \param ra right ascention of equatorial coordinates, in radians
	* \param dec declination of equatorial coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	void Jupiter(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;

	/* Saturn
	*
	* The function computes the equatorial coordinates of Saturn, its distance
	* to the Earth and its phase.
	*
	* \param ra right ascention of equatorial coordinates, in radians
	* \param dec declination of equatorial coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	void Saturn(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;

	/* Uranus
	*
	* The function computes the equatorial coordinates of Uranus, its distance
	* to the Earth and its phase.
	*
	* \param ra right ascention of equatorial coordinates, in radians
	* \param dec declination of equatorial coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	void Uranus(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;

	/* Neptune
	*
	* The function computes the equatorial coordinates of Neptune, its distance
	* to the Earth and its phase.
	*
	* \param ra right ascention of equatorial coordinates, in radians
	* \param dec declination of equatorial coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	void Neptune(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;

	/* Pluto
	*
	* The function computes the equatorial coordinates of Pluto, its distance
	* to the Earth and its phase.
	*
	* \param ra right ascention of equatorial coordinates, in radians
	* \param dec declination of equatorial coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	void Pluto(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;

private:
	// Julian date (UTC)
	double m_jd;

	// Mercury
	double m_m1, m_u1, m_VL1;

	// Venus
	double m_m2, m_u2, m_VL2;

	// Mars
	double m_m4, m_u4, m_VL4;

	// Jupiter
	double m_m5, m_u5, m_VL5;

	// Saturn
	double m_m6, m_u6, m_VL6;

	// Uranus
	double m_m7, m_u7, m_VL7;

	// Neptune
	double m_m8, m_u8, m_VL8;

	// Pluto
	double m_m9, m_u9, m_VL9;

	// Sun
	double m_ms, m_Ls;
	double m_lambdas, m_betas, m_ds;

	// Moon
	double m_mm, m_um, m_fm, m_om, m_Lm;

	// Miscellaneous
	double m_VT2000, m_eps;

	// Miscellaneous
	double m_t, m_vt;

	void Init();
	void Done(double lr, double br, double* ra, double* de) const;
	void DoneGeoc(double la, double be, double* ra, double* de) const;
	void DoneHelioc(double l, double b, double r, double* ra, double* de, double* rad, double* phase) const;
	void _Moon(double& la, double& be, double& r) const;
	void _Sun(double& la, double& r) const;
	void _Mercury(double& l, double& b, double& r) const;
	void _Venus(double& l, double& b, double& r) const;
	void _Mars(double& l, double& b, double& r) const;
	void _Jupiter(double& l, double& b, double& r) const;
	void _Saturn(double& l, double& b, double& r) const;
	void _Uranus(double& l, double& b, double& r) const;
	void _Neptune(double& l, double& b, double& r) const;
	void _Pluto(double& l, double& b, double& r) const;
};
