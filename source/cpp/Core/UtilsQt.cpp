/*!
*  \file      UtilsQt.cpp
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
#include "UtilsQt.h"

QString UtilsQt::compassPointName(CAzimuth::tCompassPoint pt)
{
	switch (pt)
	{
	case CAzimuth::N:
		return QCoreApplication::translate("CompassRose", "N");
	case CAzimuth::NNE:
		return QCoreApplication::translate("CompassRose", "NNE");
	case CAzimuth::NE:
		return QCoreApplication::translate("CompassRose", "NE");
	case CAzimuth::ENE:
		return QCoreApplication::translate("CompassRose", "ENE");
	case CAzimuth::E:
		return QCoreApplication::translate("CompassRose", "E");
	case CAzimuth::ESE:
		return QCoreApplication::translate("CompassRose", "ESE");
	case CAzimuth::SE:
		return QCoreApplication::translate("CompassRose", "SE");
	case CAzimuth::SSE:
		return QCoreApplication::translate("CompassRose", "SSE");
	case CAzimuth::S:
		return QCoreApplication::translate("CompassRose", "S");
	case CAzimuth::SSW:
		return QCoreApplication::translate("CompassRose", "SSW");
	case CAzimuth::SW:
		return QCoreApplication::translate("CompassRose", "SW");
	case CAzimuth::WSW:
		return QCoreApplication::translate("CompassRose", "WSW");
	case CAzimuth::W:
		return QCoreApplication::translate("CompassRose", "W");
	case CAzimuth::WNW:
		return QCoreApplication::translate("CompassRose", "WNW");
	case CAzimuth::NW:
		return QCoreApplication::translate("CompassRose", "NW");
	case CAzimuth::NNW:
		return QCoreApplication::translate("CompassRose", "NNW");
	default:
		return QString();
	}
}

QString UtilsQt::eventTypeShortCaption(tEventType evtype)
{
	switch (evtype)
	{
	case tEventType::PRIMARY_MINIMUM:
		return QCoreApplication::translate("EventTypeShort", "P");
	case tEventType::SECONDARY_MINIMUM:
		return QCoreApplication::translate("EventTypeShort", "S");
	default:
		return QString();
	}
}
