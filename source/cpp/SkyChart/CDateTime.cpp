/*!
*  \file      CDateTime.cpp
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
#include "CDateTime.h"

#include "CJulianDate.h"

//
// Constructor 
//
CDateTime::CDateTime(const double jd):m_year(0), m_month(0), m_day(0), m_hour(0), m_minute(0), m_second(0), m_millisecond(0)
{
	CJulianDate(jd).toDateTime(&m_year, &m_month, &m_day, &m_hour, &m_minute, &m_second, &m_millisecond);
}

//
// Julian date
//
double CDateTime::toJD() const
{
	return CJulianDate(m_year, m_month, m_day, m_hour, m_minute, m_second, m_millisecond).jd_utc();
}
