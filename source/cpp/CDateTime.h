/*!
*  \file      CDateTime.h
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
* \brief Timestamp as date and time
*
* The CDateTime class holds a timestamp (date and time) as seven integer numbers - year,
* month, day of month, hour, minute, second and millisecond. The class is used to
* provide Qt-independent means to represent a date and time and convert dates and 
* times from and to Julian date.
* 
* The values are stored as integer numbers with 1 millisecond precision. The range
* of dates it can hold is given by limit for integer numbers as a year. Please note,
* that the conversion to and from Julian date is limited.
*/
class CDateTime
{
public:
	/*! 
	* \brief Constructor
	* 
	* The constructor creates an invalid timestamp.
	*/
	CDateTime() : m_year(0), m_month(0), m_day(0), m_hour(0), m_minute(0), m_second(0), m_millisecond(0) {}

	/*! 
	* \brief Constructor with initialization
	* 
	* The constructor creates a timestamp from year, month, day of month, hour, minute, second and millisecond.
	* \param year year
	* \param month month (1-12)
	* \param day day of month (1-31)
	* \param hour hour (0 - 23)
	* \param minute minute (0 - 59)
	* \param second second (0 - 59)
	* \param millisecond millisecond (0 - 999)
	*/
	CDateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0) : m_year(year), m_month(month), m_day(day),
		m_hour(hour), m_minute(minute), m_second(second), m_millisecond(millisecond) {}

	/*! 
	* \brief Constructor from Julian date
	* 
	* The constructor creates CDateTime instance and initializes it with given Julian date. 
	*/
	explicit CDateTime(const double jd);

	/*! 
	* \brief Check the instance
	* 
	* The function returns true if the object has been constructed using a default constructor
	* and false otherwise. The default construed instances are used as function return value
	* to represent a failure.
	*/
	bool isValid() const { return m_year >= 1583 && m_year <= 3500 && m_month != 0; }

	/*! 
	* \brief Convert to Julian date 
	* 
	* The method returns timestamp as a Julian date. It returns zero if the object has not 
	* been properly initialized.
	*/
	double toJD() const;

	/*! \brief year */
	int year(void) const { return m_year; }

	/*! \brief month (1 - 12) */
	int month(void) const { return m_month; }

	/*! \brief day of month (1 - 31) */
	int day(void) const { return m_day; }

	/*! \brief hour (0 - 23) */
	int hour(void) const { return m_hour; }

	/*! \brief minute (0 - 59) */
	int minute(void) const { return m_minute; }

	/*! \brief second (0 - 59) */
	int second(void) const { return m_second; }

	/*! \brief millisecond (0 - 999) */
	int millisecond(void) const { return m_minute; }

private:
	int m_year, m_month, m_day;
	int m_hour, m_minute, m_second;
	int m_millisecond;
};
