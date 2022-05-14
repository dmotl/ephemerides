/*!
*  \file      CPlanets.cpp
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
#include "CPlanets.h"

#define _USE_MATH_DEFINES

#include <math.h>

#include "vsop87.h"
#include "elp82.h"
#include "SkyChartUtils.h"

//
// Fractional part of x
//
inline double frac(double x) { double y;  return modf(x, &y); }


//
// Normalize angle to range of 0 .. 2pi
//
static double normalizeAngle(double rad)
{
    double i;

    if (rad > 2 * M_PI) {
        rad = modf(rad / (2 * M_PI), &i);
        rad = rad * (2 * M_PI);
    }
    else if (rad < 0) {
        rad = modf(-rad / (2 * M_PI), &i);
        rad = (1 - rad) * (2 * M_PI);
    }
    if (rad == 2 * M_PI)
        return 0;
    return rad;
}


//
// Crop angle to range of -pi .. pi
//
static double cropAngle(double rad)
{
    if (rad > M_PI_2)
        return M_PI_2;
    else if (rad < -M_PI_2)
        return -M_PI_2;
    else
        return rad;
}

//
// Constructor
//
CPlanets::CPlanets(double jd) : m_jd(0)
{
    for (int i = 0; i < sizeof(m_eclipticPos) / sizeof(Utils::CVector3d); i++)
        m_eclipticPos[i] = m_eclipticVelocity[3] = Utils::CVector3d();
    m_moon = Utils::CVector3d();
    if (jd > 0)
        setJD(jd);
}


//
// Reinitialize the model
//
void CPlanets::setJD(double jd_utc)
{
    m_jd = jd_utc;
    Init();
}


//
// Compute model
//
void CPlanets::Init()
{
    // Planets
    for (int i = 1; i < 9; i++) {
        tVSOP87_Rect xyz;
        vsop87c(i, m_jd, &xyz);
        m_eclipticPos[i] = Utils::CVector3d(xyz.X);
        m_eclipticVelocity[3] = Utils::CVector3d(xyz.X + 3);
    }

    // Moon
    tELP82_Rect xyz, xyz_10;
    elp82b(0, m_jd, &xyz);
    m_moon = Utils::CVector3d(xyz.X);
}


//
// Moon
//
Utils::CVector3d CPlanets::Moon(void) const
{
    return m_moon;
}


//
// Sun
//
Utils::CVector3d CPlanets::Sun(void) const
{
    Utils::CVector3d dist = m_eclipticPos[3] * (-1.0);
    return (dist + Utils::aberrationPush(m_eclipticPos[3].length(), m_eclipticVelocity[3]));
}


//
// Planets
//
Utils::CVector3d CPlanets::_Planet(int ibody) const
{
    Utils::CVector3d dist = m_eclipticPos[ibody] - m_eclipticPos[3];
    return (dist + Utils::aberrationPush(dist.length(), m_eclipticVelocity[3]));
}
