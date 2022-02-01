#pragma once

#define DEG_TO_RAD(deg) ((deg) / 180 * M_PI)
#define RAD_TO_DEG(rad) ((rad) / M_PI * 180)
#define HMS_TO_JD(h, m, s) (((h) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 24)

namespace Utils
{
	// Angular distance of two objects
	double AngularDistance(double Ra1, double De1, double Ra2, double De2);
};
