#include "Utils.h"

#define _USE_MATH_DEFINES

#include <math.h>

//
// Angular distance of two objects
//
double Utils::AngularDistance(double ra1, double de1, double ra2, double de2)
{
	return acos(sin(de1) * sin(de2) + cos(de1) * cos(de2) * cos(ra1 - ra2));
}
