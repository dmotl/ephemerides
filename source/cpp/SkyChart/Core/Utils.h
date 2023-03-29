/*!
*  \file      Utils.h
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

enum class tObjectType
{
	UNKNOWN,
	GALAXY,
	OPEN_CLUSTER,
	GLOB_CLUSTER,
	NEBULA,
	PLAN_NEBULA,
	TRIPPLE_STAR,
	DOUBLE_STAR,
	STAR,
	UNCERTAIN,
	CL_AND_NB,
	ASTERISM,
	KNOT,
	NON_EXISTENT,
	DEFECT,
	SUPERNOVA,
	VARIABLE_STAR
};

enum class tEventType
{
	Unknown,
	PRIMARY_MINIMUM,
	SECONDARY_MINIMUM
};

/*
* \brief Degrees to radians
* 
* The macro converts an angle in degrees to radians
* \param deg angle in degrees
* \return angle in radians
*/
#define DEG_TO_RAD(deg) (static_cast<double>(deg) / 180.0 * M_PI)

/*
* \brief Radians to degrees
*
* The macro converts an angle in radians to degrees
* \param deg angle in radians
* \return angle in degrees
*/
#define RAD_TO_DEG(rad) (static_cast<double>(rad) / M_PI * 180.0)


#define DMS_TO_RAD(d, m, s) ((abs(d) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 180 * M_PI)
#define RA_TO_RAD(h, m, s) (((h) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 12 * M_PI)
#define DEC_TO_RAD(d, m, s) DMS_TO_RAD(d, m, s)

/*
* \brief Time to fractions of day
*
* The macro converts time specified as hour, minute and second
* to a fractional part of the day since midnight.
* \param h hour
* \param m minute
* \param s second
* \return fractional part of the day since midnight
* 
*/
#define HMS_TO_JD(h, m, s) (((h) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 24)

/*
* Invalid magnitude value
* 
* The value used to indicate an invalid magnitude of an object.
*/
#define INVALID_MAG -99
