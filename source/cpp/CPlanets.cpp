#include "CPlanets.h"

#define _USE_MATH_DEFINES

#include <math.h>

inline double frac(double x) { double y;  return modf(x, &y); }

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

static double cropAngle(double rad)
{
    if (rad > M_PI_2)
        return M_PI_2;
    else if (rad < -M_PI_2)
        return -M_PI_2;
    else
        return rad;
}

CPlanets::CPlanets(double jd): m_jd(0), m_VT2000(0), m_eps(0), m_t(0), m_vt(0),
	m_m1(0), m_u1(0), m_VL1(0),
	m_m2(0), m_u2(0), m_VL2(0),
	m_m4(0), m_u4(0), m_VL4(0),
	m_m5(0), m_u5(0), m_VL5(0),
	m_m6(0), m_u6(0), m_VL6(0),
	m_m7(0), m_u7(0), m_VL7(0),
	m_m8(0), m_u8(0), m_VL8(0),
	m_m9(0), m_u9(0), m_VL9(0),
	m_ms(0), m_Ls(0), m_lambdas(0), m_betas(0), m_ds(0),
	m_mm(0), m_um(0), m_fm(0), m_om(0), m_Lm(0)
{
	if (jd > 0)
		setJD(jd);
}

void CPlanets::setJD(double jd_utc)
{
    m_jd = jd_utc;
    Init();
}

void CPlanets::Init()
{
    m_t = m_jd - 2451545;
    m_vt = 1 + (m_t / 36525);
    m_VT2000 = m_t / 36525;
    m_eps = (23.4392911 - 0.0130042 * m_VT2000 - 0.00000164 * m_VT2000 * m_VT2000 + 0.000000503 * m_VT2000 * m_VT2000 * m_VT2000) / 180 * M_PI;

    // Moon
    m_Lm = (0.606434 + 0.03660110129 * m_t) * 2 * M_PI;
    m_mm = (0.374897 + 0.03629164709 * m_t) * 2 * M_PI;
    m_um = (0.259091 + 0.03674819520 * m_t) * 2 * M_PI;
    m_fm = (0.827362 + 0.03386319198 * m_t) * 2 * M_PI;
    m_om = (0.347343 - 0.00014709391 * m_t) * 2 * M_PI;

    // Sun
    m_Ls = (0.779072 + 0.00273790931 * m_t) * 2 * M_PI;
    m_ms = (0.993126 + 0.00273777850 * m_t) * 2 * M_PI;

    // Mercury
    m_VL1 = (0.700695 + 0.01136771400 * m_t) * 2 * M_PI;
    m_m1 = (0.485541 + 0.01136759566 * m_t) * 2 * M_PI;
    m_u1 = (0.566441 + 0.01136762384 * m_t) * 2 * M_PI;

    // Venus
    m_VL2 = (0.505498 + 0.00445046867 * m_t) * 2 * M_PI;
    m_m2 = (0.140023 + 0.00445036173 * m_t) * 2 * M_PI;
    m_u2 = (0.292498 + 0.00445040017 * m_t) * 2 * M_PI;

    // Mars
    m_VL4 = (0.987353 + 0.00145575328 * m_t) * 2 * M_PI;
    m_m4 = (0.053856 + 0.00145561327 * m_t) * 2 * M_PI;
    m_u4 = (0.849694 + 0.00145569465 * m_t) * 2 * M_PI;

    // Jupiter
    m_VL5 = (0.089608 + 0.00023080893 * m_t) * 2 * M_PI;
    m_m5 = (0.056531 + 0.00023080893 * m_t) * 2 * M_PI;
    m_u5 = (0.814734 + 0.00023080893 * m_t) * 2 * M_PI;

    // Saturn
    m_VL6 = (0.133295 + 0.00009294371 * m_t) * 2 * M_PI;
    m_m6 = (0.882987 + 0.00009294371 * m_t) * 2 * M_PI;
    m_u6 = (0.821218 + 0.00009294371 * m_t) * 2 * M_PI;

    // Uranus
    m_VL7 = (0.870169 + 0.00003269438 * m_t) * 2 * M_PI;
    m_m7 = (0.400589 + 0.00003269438 * m_t) * 2 * M_PI;
    m_u7 = (0.664614 + 0.00003265562 * m_t) * 2 * M_PI;

    // Neptune
    m_VL8 = (0.846912 + 0.00001672092 * m_t) * 2 * M_PI;
    m_m8 = (0.725368 + 0.00001672092 * m_t) * 2 * M_PI;
    m_u8 = (0.480856 + 0.00001663715 * m_t) * 2 * M_PI;

    // Pluto
    m_VL9 = (0.663854 + 0.00001115482 * m_t) * 2 * M_PI;
    m_m9 = (0.041020 + 0.00001104864 * m_t) * 2 * M_PI;
    m_u9 = (0.357355 + 0.00001104864 * m_t) * 2 * M_PI;

    // Sun
    _Sun(m_lambdas, m_ds);
    m_lambdas = normalizeAngle(m_lambdas / 3600 / 180 * M_PI);
}

void CPlanets::Done(double lr, double br, double* ra, double* de) const
{
    if (fabs(lr - M_PI / 2) < 0.000001) { 
        if (ra)
            *ra = M_PI / 2; 
        if (de)
            *de = m_eps; 
    }
    else if (fabs(lr - 3 * M_PI / 2) < 0.000001) { 
        if (ra)
            *ra = -(M_PI / 2); 
        if (de)
            *de = -m_eps; 
    }
    else {
        if (ra)
            *ra = atan2(sin(br) * sin(-m_eps) + cos(m_eps) * cos(br) * sin(lr), cos(br) * cos(lr));
        if (de)
            *de = asin(sin(br) * cos(m_eps) + cos(br) * sin(m_eps) * sin(lr));
    }
}

void CPlanets::DoneGeoc(double la, double be, double* ra, double* de) const
{
    la = normalizeAngle(la / 3600 / 180 * M_PI);
    be = cropAngle(be / 3600 / 180 * M_PI);
    Done(la, be, ra, de);
}

void CPlanets::DoneHelioc(double l, double b, double r, double* ra, double* de, double *rad, double *phase) const
{
    l = normalizeAngle(l / 3600 / 180 * M_PI);
    b = cropAngle(b / 3600 / 180 * M_PI);
    double delta = sqrt(m_ds * m_ds + r * r + 2 * r * m_ds * cos(b) * cos(l - m_lambdas));
    double la = atan2(r * cos(b) * sin(l - m_Ls), r * cos(b) * cos(l - m_lambdas) + m_ds) + m_lambdas;
    double be = asin(r / delta * sin(b));
    Done(la, be, ra, de);
    if (rad)
        *rad = r;
    if (phase) {
        double fi = acos((r * r + delta * delta - m_ds * m_ds) / 2 / r / delta);
        *phase = (sin(m_lambdas - la) <= 0 ? M_PI - fi : M_PI + fi);
    }
}

void CPlanets::_Moon(double& la, double& be, double& r) const
{
    la = m_Lm * 3600 * 180 / M_PI + 22640 * sin(m_mm)
        - 4586 * sin(m_mm - 2 * m_fm)
        + 2370 * sin(2 * m_fm)
        + 769 * sin(2 * m_mm)
        - 668 * sin(m_ms)
        - 412 * sin(2 * m_um)
        - 212 * sin(2 * m_mm - 2 * m_fm)
        - 206 * sin(m_mm - 2 * m_fm + m_ms)
        + 192 * sin(m_mm + 2 * m_fm)
        + 165 * sin(2 * m_fm - m_ms)
        + 148 * sin(m_mm - m_ms)
        - 125 * sin(m_fm)
        - 110 * sin(m_mm + m_ms)
        - 55 * sin(2 * m_um - 2 * m_fm)
        - 45 * sin(m_mm + 2 * m_um)
        + 40 * sin(m_mm - 2 * m_um)
        - 38 * sin(m_mm - 4 * m_fm)
        + 36 * sin(3 * m_mm)
        - 31 * sin(2 * m_mm - 4 * m_fm)
        + 28 * sin(m_mm - 2 * m_fm - m_ms)
        - 24 * sin(2 * m_fm + m_ms)
        + 19 * sin(m_mm - m_fm)
        + 18 * sin(m_fm + m_ms)
        + 15 * sin(m_mm + 2 * m_fm - m_ms)
        + 14 * sin(2 * m_mm + 2 * m_fm)
        + 14 * sin(4 * m_fm)
        - 13 * sin(3 * m_mm - 2 * m_fm)
        - 11 * sin(m_mm - 16 * m_Ls - 18 * m_VL2)
        + 10 * sin(2 * m_mm - m_ms)
        + 9 * sin(m_mm - 2 * m_um - 2 * m_fm)
        + 9 * cos(m_mm + 16 * m_Ls - 18 * m_VL2)
        - 9 * sin(2 * m_mm - 2 * m_fm + m_ms)
        - 8 * sin(m_mm - m_fm)
        + 8 * sin(2 * m_fm - 2 * m_ms)
        - 8 * sin(2 * m_ms + m_ms)
        - 7 * sin(2 * m_ms)
        - 7 * sin(m_mm - 2 * m_fm + 2 * m_ms)
        + 7 * sin(m_om)
        - 6 * sin(m_mm - 2 * m_um + 2 * m_fm)
        - 6 * sin(2 * m_um + 2 * m_fm)
        - 4 * sin(m_mm - 4 * m_fm + m_ms)
        + 4 * m_vt * cos(m_mm + 16 * m_Ls - 18 * m_VL2)
        - 4 * sin(2 * m_mm - 2 * m_um)
        + 4 * m_vt * sin(m_mm + 16 * m_Ls - 18 * m_VL2)
        + 3 * sin(m_mm - 3 * m_fm)
        - 3 * sin(m_mm + 2 * m_fm + m_ms)
        - 3 * sin(2 * m_mm - 4 * m_fm + m_ms)
        - 3 * sin(m_mm - 2 * m_ms)
        + 3 * sin(m_mm - 2 * m_fm - 2 * m_ms)
        - 2 * sin(2 * m_mm - 2 * m_fm - m_ms)
        - 2 * sin(2 * m_um - 2 * m_fm + m_ms)
        + 2 * sin(m_mm + 4 * m_fm)
        + 2 * sin(4 * m_mm)
        + 2 * sin(4 * m_fm - m_ms)
        + 2 * sin(2 * m_mm - m_fm);

    be = 18461 * sin(m_um)
        + 1010 * sin(m_mm + m_um)
        + 1000 * sin(m_mm - m_um)
        - 624 * sin(m_um - 2 * m_fm)
        - 199 * sin(m_mm - m_um - 2 * m_fm)
        - 167 * sin(m_mm + m_um - 2 * m_fm)
        + 117 * sin(m_um - 2 * m_fm)
        + 62 * sin(2 * m_mm + m_um)
        + 33 * sin(m_mm - m_um + 2 * m_fm)
        + 32 * sin(2 * m_mm - m_um)
        + 30 * sin(m_um - 2 * m_fm + m_ms)
        - 16 * sin(2 * m_mm + m_um - 2 * m_fm)
        + 15 * sin(m_mm + m_um + 2 * m_fm)
        + 12 * sin(m_um - 2 * m_fm - m_ms)
        - 9 * sin(m_mm - m_um - 2 * m_fm + m_ms)
        - 8 * sin(m_um - m_om)
        + 8 * sin(m_um + 2 * m_fm - m_ms)
        - 7 * sin(m_mm + m_um - 2 * m_fm + m_ms)
        + 7 * sin(m_mm + m_um - m_ms)
        - 7 * sin(m_mm + m_um - 4 * m_fm)
        - 6 * sin(m_um + m_ms)
        - 6 * sin(3 * m_um)
        + 6 * sin(m_mm - m_um - m_ms)
        - 5 * sin(m_um - m_fm)
        - 5 * sin(m_mm + m_um + m_ms)
        - 5 * sin(m_mm - m_um + m_ms)
        + 5 * sin(m_um - m_ms)
        + 5 * sin(m_um - m_fm)
        + 4 * sin(3 * m_mm + m_um)
        - 4 * sin(m_um - 4 * m_fm)
        - 3 * sin(m_mm - m_um - 4 * m_fm)
        + 3 * sin(m_mm - 3 * m_um)
        - 2 * sin(2 * m_mm - m_um - 4 * m_fm)
        - 2 * sin(3 * m_um - 2 * m_fm)
        + 2 * sin(2 * m_mm - m_um + 2 * m_fm)
        + 2 * sin(m_mm - m_um + 2 * m_fm - m_ms)
        + 2 * sin(2 * m_mm - m_um - 2 * m_fm)
        + 2 * sin(3 * m_mm - m_um);

    r = 60.36298
        - 3.27746 * cos(m_mm)
        - 0.57994 * cos(m_mm - 2 * m_fm)
        - 0.46357 * cos(2 * m_fm)
        - 0.08904 * cos(2 * m_mm)
        + 0.03865 * cos(2 * m_mm - 2 * m_fm)
        - 0.03237 * cos(2 * m_fm - m_ms)
        - 0.02688 * cos(m_mm + 2 * m_fm)
        - 0.02358 * cos(m_mm - 2 * m_fm + m_ms)
        - 0.02030 * cos(m_mm - m_ms)
        + 0.01719 * cos(m_fm)
        + 0.01671 * cos(m_mm + m_ms)
        + 0.01247 * cos(m_mm - 2 * m_um)
        + 0.00704 * cos(m_ms)
        + 0.00529 * cos(2 * m_fm + m_ms)
        - 0.00524 * cos(m_mm - 4 * m_fm)
        + 0.00398 * cos(m_mm - 2 * m_fm - m_ms)
        - 0.00366 * cos(3 * m_mm)
        - 0.00295 * cos(2 * m_mm - 4 * m_fm)
        - 0.00263 * cos(m_fm + m_ms)
        + 0.00249 * cos(3 * m_mm - 2 * m_fm)
        - 0.00221 * cos(m_mm + 2 * m_fm - m_ms)
        + 0.00185 * cos(2 * m_um - 2 * m_fm)
        - 0.00161 * cos(2 * m_fm - 2 * m_ms)
        + 0.00147 * cos(m_mm + 2 * m_um - 2 * m_fm)
        - 0.00142 * cos(4 * m_fm)
        + 0.00139 * cos(2 * m_mm - 2 * m_fm + m_ms)
        - 0.00118 * cos(2 * m_mm - 4 * m_fm + m_ms)
        - 0.00116 * cos(2 * m_mm - 2 * m_fm)
        - 0.00110 * cos(2 * m_mm - m_ms);
}

void CPlanets::_Sun(double& la, double& r) const
{
    la = m_Ls * 3600 * 180 / M_PI + 6910 * sin(m_ms)
        + 72 * sin(2 * m_ms)
        - 17 * m_vt * sin(m_ms)
        - 7 * cos(m_ms - m_m5)
        + 6 * sin(m_Lm - m_Ls)
        + 5 * sin(4 * m_ms + 8 * m_m4 + 3 * m_m5)
        - 5 * cos(2 * m_ms - 2 * m_m2)
        - 4 * sin(m_ms - m_m2)
        + 4 * cos(4 * m_ms - 8 * m_m4 + 3 * m_m5)
        + 3 * sin(2 * m_ms - 2 * m_m2)
        - 3 * sin(m_m5)
        - 3 * sin(2 * m_ms - 2 * m_m5);
    r = 1.00014 - 0.01675 * cos(m_ms) - 0.00014 * cos(2 * m_ms);
}

void CPlanets::_Mercury(double& l, double& b, double& r) const
{
    l = m_VL1 * 3600 * 180 / M_PI + 84378 * sin(m_m1)
        + 10733 * sin(2 * m_m1)
        + 1892 * sin(3 * m_m1)
        - 646 * sin(2 * m_u1)
        + 381 * sin(4 * m_m1)
        - 306 * sin(m_m1 - 2 * m_u1)
        - 274 * sin(m_m1 + 2 * m_u1)
        - 92 * sin(2 * m_m1 + 2 * m_u1)
        + 83 * sin(5 * m_m1)
        - 28 * sin(3 * m_m1 + 2 * m_u1)
        + 25 * sin(2 * m_m1 - 2 * m_u1)
        + 19 * sin(6 * m_m1)
        - 9 * sin(4 * m_m1 + 2 * m_u1)
        + 8 * m_vt * sin(m_m1)
        + 7 * cos(m_m1 - 5 * m_m2);
    b = 24134 * sin(m_u1)
        + 5180 * sin(m_m1 - m_u1)
        + 4910 * sin(m_m1 + m_u1)
        + 1124 * sin(2 * m_m1 + m_u1)
        + 271 * sin(3 * m_m1 + m_u1)
        + 132 * sin(2 * m_m1 - m_u1)
        + 67 * sin(4 * m_m1 + m_u1)
        + 18 * sin(5 * m_m1 + m_u1)
        - 10 * sin(3 * m_u1)
        + 9 * sin(m_m1 - 3 * m_u1);
    r = 0.39528
        - 0.07834 * cos(m_m1)
        - 0.00795 * cos(2 * m_m1)
        - 0.00121 * cos(3 * m_m1)
        - 0.00022 * cos(4 * m_m1);
}

void CPlanets::_Venus(double& l, double& b, double& r) const
{
    l = m_VL2 * 3600 * 180 / M_PI + 2814 * sin(m_m2)
        - 181 * sin(2 * m_u2)
        - 20 * m_vt * sin(m_m2)
        + 12 * sin(2 * m_m2)
        - 10 * cos(2 * m_ms - 2 * m_m2)
        + 7 * cos(3 * m_ms - 3 * m_m2);
    b = 12215 * sin(m_u2)
        + 83 * sin(m_m2 + m_u2)
        + 83 * sin(m_m2 - m_u2);
    r = 0.72335 - 0.00493 * cos(m_m2);
}

void CPlanets::_Mars(double& l, double& b, double& r) const
{
    l = m_VL4 * 3600 * 180 / M_PI
        + 38451 * sin(m_m4)
        + 2238 * sin(2 * m_m4)
        + 181 * sin(3 * m_m4)
        - 52 * sin(2 * m_u4)
        + 37 * m_vt * sin(m_m4)
        - 22 * cos(m_m4 - 2 * m_m5)
        - 19 * sin(m_m4 - m_m5)
        + 17 * cos(m_m4 - m_m5)
        + 17 * sin(4 * m_m4)
        - 16 * cos(2 * m_m4 - 2 * m_m5)
        + 13 * cos(m_ms - 2 * m_m4)
        - 10 * sin(m_m4 - 2 * m_u2)
        - 10 * sin(m_m4 + 2 * m_u4)
        + 7 * cos(m_ms - m_m4)
        - 7 * cos(2 * m_ms - 3 * m_m4)
        - 5 * sin(m_m2 - 3 * m_m4)
        - 5 * sin(m_ms - m_m4)
        - 5 * sin(m_ms - 2 * m_m4)
        - 4 * cos(2 * m_ms - 4 * m_m4)
        + 4 * m_vt * sin(2 * m_m4)
        + 4 * cos(m_m5)
        + 3 * cos(m_m2 - 3 * m_m4)
        + 3 * cos(2 * m_m4 - 2 * m_m5);
    b = 6603 * sin(m_u4)
        + 622 * sin(m_m4 - m_u4)
        + 615 * sin(m_m4 + m_u4)
        + 64 * sin(2 * m_m4 + m_u4);
    r = 1.53031 - 0.14170 * cos(m_m4)
        - 0.00660 * cos(2 * m_m4)
        - 0.00047 * cos(3 * m_m4);
}

void CPlanets::_Jupiter(double& l, double& b, double& r) const
{
    l = m_VL5 * 3600 * 180 / M_PI
        + 19934 * sin(m_m5)
        + 5023 * m_vt
        + 2511
        + 1093 * cos(2 * m_m5 - 5 * m_m6)
        + 601 * sin(2 * m_m5)
        - 479 * sin(2 * m_m5 - 5 * m_m6)
        - 185 * sin(2 * m_m5 - 2 * m_m6)
        + 137 * sin(3 * m_m5 - 5 * m_m6)
        - 131 * sin(m_m5 - 2 * m_m6)
        + 79 * cos(m_m5 - m_m6)
        - 76 * cos(2 * m_m5 - 2 * m_m6)
        - 74 * m_vt * cos(m_m5)
        + 68 * m_vt * sin(m_m5)
        + 66 * cos(2 * m_m5 - 3 * m_m6)
        + 63 * cos(3 * m_m5 - 5 * m_m6)
        + 53 * cos(m_m5 - 5 * m_m6)
        + 49 * sin(2 * m_m5 - 3 * m_m6)
        - 43 * m_vt * sin(2 * m_m5 - 5 * m_m6)
        - 37 * cos(m_m5)
        + 25 * sin(2 * m_VL5)
        + 25 * sin(3 * m_m5)
        - 23 * sin(m_m5 - 5 * m_m6)
        - 19 * m_vt * sin(2 * m_m5 - 5 * m_m6)
        + 17 * cos(2 * m_m5 - 4 * m_m6)
        + 17 * cos(3 * m_m5 - 3 * m_m6)
        - 14 * sin(m_m5 - m_m6)
        - 13 * sin(3 * m_m5 - 4 * m_m6)
        - 9 * cos(m_VL5)
        + 9 * cos(m_m6)
        - 9 * sin(m_m6)
        - 9 * sin(3 * m_m5 - 2 * m_m6)
        + 9 * sin(4 * m_m5 - 5 * m_m6)
        + 9 * sin(2 * m_m5 - 6 * m_m6 + 3 * m_m7)
        - 8 * cos(4 * m_m5 - 10 * m_m6)
        + 7 * cos(3 * m_m5 - 4 * m_m6)
        - 7 * cos(m_m5 - 3 * m_m6)
        - 7 * sin(4 * m_m5 - 10 * m_m6)
        - 7 * sin(m_m5 - 3 * m_m6)
        + 6 * cos(4 * m_m5 - 5 * m_m6)
        - 6 * sin(3 * m_m5 - 3 * m_m6)
        + 5 * cos(2 * m_m6)
        - 4 * sin(4 * m_m5 - 4 * m_m6)
        - 4 * cos(3 * m_m6)
        + 4 * cos(2 * m_m5 - m_m6)
        - 4 * cos(3 * m_m5 - 2 * m_m6)
        - 4 * m_vt * cos(2 * m_m5)
        + 3 * m_vt * sin(2 * m_m5)
        + 3 * cos(5 * m_m6)
        + 3 * cos(5 * m_m5 - 10 * m_m6)
        + 3 * sin(2 * m_m6)
        - 2 * sin(2 * m_VL5 - m_m5)
        + 2 * sin(2 * m_VL5 + m_m5)
        - 2 * m_vt * sin(3 * m_m5 - 5 * m_m6)
        - 2 * m_vt * sin(m_m5 - 5 * m_m6);
    b = -4692 * cos(m_m5)
        + 259 * sin(m_m5)
        + 227
        - 227 * cos(2 * m_m5)
        + 30 * m_vt * sin(m_m5)
        + 21 * m_vt * cos(m_m5)
        + 16 * sin(3 * m_m5 - 5 * m_m6)
        - 13 * sin(m_m5 - 5 * m_m6)
        - 12 * cos(3 * m_m5)
        + 12 * sin(2 * m_m5)
        + 7 * cos(3 * m_m5 - 5 * m_m6)
        - 5 * cos(m_m5 - 5 * m_m6);
    r = 5.20883
        - 0.25122 * cos(m_m5)
        - 0.00604 * cos(2 * m_m5)
        + 0.00260 * cos(2 * m_m5 - 2 * m_m6)
        - 0.00170 * cos(3 * m_m5 - 5 * m_m6)
        - 0.00091 * m_vt * sin(m_m5)
        - 0.00084 * m_vt * cos(m_m5)
        + 0.00069 * sin(2 * m_m5 - 3 * m_m6)
        - 0.00067 * sin(m_m5 - 5 * m_m6)
        + 0.00066 * sin(3 * m_m5 - 5 * m_m6)
        + 0.00063 * sin(m_m5 - m_m6)
        - 0.00051 * cos(2 * m_m5 - 3 * m_m6)
        - 0.00046 * sin(m_m5)
        - 0.00029 * cos(m_m5 - 5 * m_m6)
        + 0.00027 * cos(m_m5 - 2 * m_m6)
        - 0.00022 * cos(3 * m_m5)
        - 0.00021 * sin(2 * m_m5 - 5 * m_m6);
}

void CPlanets::_Saturn(double& l, double& b, double& r) const
{
    l = m_VL6 * 3600 * 180 / M_PI
        + 23045 * sin(m_m6)
        + 5014 * m_vt
        - 2689 * cos(2 * m_m5 - 5 * m_m6)
        + 2507
        + 1177 * sin(2 * m_m5 - 5 * m_m6)
        - 826 * cos(2 * m_m5 - 4 * m_m6)
        + 802 * sin(2 * m_m6)
        + 425 * sin(m_m5 - 2 * m_m6)
        - 229 * m_vt * cos(m_m6)
        - 153 * cos(2 * m_m5 - 6 * m_m6)
        - 142 * m_vt * sin(m_m6)
        - 114 * cos(m_m6)
        + 101 * m_vt * sin(2 * m_m5 - 5 * m_m6)
        - 70 * cos(2 * m_VL6)
        + 67 * sin(2 * m_VL6)
        + 66 * sin(2 * m_m5 - 6 * m_m6)
        + 60 * m_vt * cos(2 * m_m5 - 5 * m_m6)
        + 41 * sin(m_m5 - 3 * m_m6)
        + 39 * sin(3 * m_m6)
        + 31 * sin(m_m5 - m_m6)
        + 31 * sin(2 * m_m5 - 2 * m_m6)
        - 29 * cos(2 * m_m5 - 3 * m_m6)
        - 28 * sin(2 * m_m5 - 6 * m_m6 + 3 * m_m7)
        + 28 * cos(m_m5 - 3 * m_m6)
        + 22 * m_vt * sin(2 * m_m5 - 4 * m_m6)
        - 22 * sin(m_m6 - 3 * m_m7)
        + 20 * sin(2 * m_m5 - 3 * m_m6)
        + 20 * cos(4 * m_m5 - 10 * m_m6)
        + 19 * cos(2 * m_m6 - 3 * m_m7)
        + 19 * sin(4 * m_m5 - 10 * m_m6)
        - 17 * m_vt * cos(2 * m_m6)
        - 16 * cos(m_m6 - 3 * m_m7)
        - 12 * sin(2 * m_m5 - 4 * m_m6)
        + 12 * cos(m_m5)
        - 12 * sin(2 * m_m6 - 2 * m_m7)
        - 11 * m_vt * sin(2 * m_m6)
        - 11 * cos(2 * m_m5 - 7 * m_m6)
        + 10 * sin(2 * m_m6 - 3 * m_m7)
        + 10 * cos(2 * m_m5 + 2 * m_m6)
        + 9 * sin(4 * m_m5 - 9 * m_m6)
        - 8 * sin(m_m6 - 2 * m_m7)
        - 8 * cos(m_VL6 + m_m6)
        + 8 * cos(m_VL6 - m_m6)
        + 8 * sin(m_m6 - m_m7)
        - 8 * sin(2 * m_VL6 - m_m6)
        + 7 * sin(2 * m_VL6 + m_m6)
        - 7 * cos(m_m5 - 2 * m_m6)
        - 7 * cos(2 * m_m6)
        - 6 * m_vt * sin(4 * m_m5 - 10 * m_m6)
        + 6 * m_vt * cos(4 * m_m5 - 10 * m_m6)
        + 6 * m_vt * sin(2 * m_m5 - 6 * m_m6)
        - 5 * sin(3 * m_m5 - 7 * m_m6)
        - 5 * cos(3 * m_m5 - 3 * m_m6)
        - 5 * cos(2 * m_m6 - 2 * m_m7)
        + 5 * sin(3 * m_m5 - 4 * m_m6)
        + 5 * sin(2 * m_m5 - 7 * m_m6)
        + 4 * sin(3 * m_m5 - 5 * m_m6)
        + 4 * m_vt * cos(m_m5 - 2 * m_m6)
        + 3 * m_vt * cos(3 * m_m5 - 4 * m_m6)
        + 3 * cos(2 * m_m5 - 6 * m_m6 + 3 * m_m7)
        - 3 * m_vt * sin(2 * m_VL6)
        + 3 * m_vt * cos(2 * m_m5 - 6 * m_m6)
        - 3 * m_vt * cos(2 * m_VL6)
        + 3 * cos(3 * m_m5 - 7 * m_m6)
        + 3 * cos(4 * m_m5 - 9 * m_m6)
        + 3 * sin(3 * m_m5 - 6 * m_m6)
        + 3 * sin(2 * m_m5 - m_m6)
        + 3 * sin(m_m5 - 4 * m_m6)
        + 2 * cos(3 * m_m6 - 3 * m_m7)
        + 2 * m_vt * sin(m_m5 - 2 * m_m6)
        + 2 * sin(4 * m_m6)
        - 2 * cos(3 * m_m5 - 4 * m_m6)
        - 2 * cos(2 * m_m5 - m_m6)
        - 2 * sin(2 * m_m5 - 7 * m_m6 + 3 * m_m7)
        + 2 * cos(m_m5 - 4 * m_m6)
        + 2 * cos(4 * m_m5 - 11 * m_m6)
        - 2 * sin(m_m6 - m_m7);
    b = 8297 * sin(m_m6)
        - 3346 * cos(m_m6)
        + 462 * sin(2 * m_m6)
        - 189 * cos(2 * m_m6)
        + 185
        - 79 * m_vt * cos(m_m6)
        - 71 * cos(2 * m_m5 - 4 * m_m6)
        + 46 * sin(2 * m_m5 - 4 * m_m6)
        - 45 * cos(2 * m_m5 - 6 * m_m6)
        + 29 * sin(3 * m_m6)
        - 20 * cos(2 * m_m5 - 3 * m_m6)
        + 18 * m_vt * sin(m_m6)
        - 14 * cos(2 * m_m5 - 5 * m_m6)
        - 11 * cos(3 * m_m6)
        - 10 * m_vt
        + 9 * sin(m_m5 - 3 * m_m6)
        + 8 * sin(m_m5 - m_m6)
        - 6 * sin(2 * m_m5 - 3 * m_m6)
        + 5 * sin(2 * m_m5 - 7 * m_m6)
        - 5 * cos(2 * m_m5 - 7 * m_m6)
        + 4 * sin(2 * m_m5 - 5 * m_m6)
        - 4 * m_vt * sin(2 * m_m6)
        - 3 * cos(m_m5 - m_m6)
        + 3 * cos(m_m5 - 3 * m_m6)
        + 3 * m_vt * sin(2 * m_m5 - 4 * m_m6)
        + 3 * sin(m_m5 - 2 * m_m6)
        + 2 * sin(4 * m_m6)
        - 2 * cos(2 * m_m5 - 2 * m_m6);
    r = 9.55774
        - 0.53252 * cos(m_m6)
        - 0.01878 * sin(2 * m_m5 - 4 * m_m6)
        - 0.01482 * cos(2 * m_m6)
        + 0.00817 * sin(m_m5 - m_m6)
        - 0.00539 * cos(m_m5 - 2 * m_m6)
        - 0.00524 * m_vt * sin(m_m6)
        + 0.00349 * sin(2 * m_m5 - 5 * m_m6)
        + 0.00328 * m_vt * cos(m_m6)
        - 0.00225 * sin(m_m6)
        + 0.00149 * cos(2 * m_m5 - 6 * m_m6)
        - 0.00126 * cos(2 * m_m5 - 2 * m_m6)
        + 0.00104 * cos(m_m5 - m_m6)
        + 0.00101 * cos(2 * m_m5 - 5 * m_m6)
        + 0.00098 * cos(m_m5 - 3 * m_m6)
        - 0.00073 * cos(2 * m_m5 - 3 * m_m6)
        - 0.00062 * cos(3 * m_m6)
        + 0.00042 * sin(2 * m_m6 - 3 * m_m7)
        + 0.00041 * sin(2 * m_m5 - 2 * m_m6)
        - 0.00040 * sin(m_m5 - 3 * m_m6)
        + 0.00040 * cos(2 * m_m5 - 4 * m_m6)
        - 0.00028 * m_vt
        - 0.00023 * sin(m_m5)
        + 0.00020 * sin(2 * m_m5 - 7 * m_m6);
}

void CPlanets::_Uranus(double& l, double& b, double& r) const
{
    l = m_VL7 * 3600 * 180 / M_PI
        + 19397 * sin(m_m7)
        + 570 * sin(2 * m_m7)
        - 536 * m_vt * cos(m_m7)
        + 143 * sin(m_m6 - 2 * m_m7)
        + 110 * m_vt * sin(m_m7)
        + 102 * sin(m_m6 - 3 * m_m7)
        + 76 * cos(m_m6 - 3 * m_m7)
        - 49 * sin(m_m5 - m_m7)
        + 32 * m_vt * m_vt
        - 30 * m_vt * cos(2 * m_m7)
        + 29 * sin(2 * m_m5 - 6 * m_m6 + 3 * m_m7)
        + 29 * cos(2 * m_m7 - 2 * m_m8)
        - 28 * cos(m_m7 - m_m8)
        + 23 * sin(3 * m_m7)
        - 21 * cos(m_m5 - m_m7)
        + 20 * sin(m_m7 - m_m8)
        + 20 * cos(m_m6 - 2 * m_m7)
        - 19 * cos(m_m6 - m_m7)
        + 17 * sin(2 * m_m7 - 3 * m_m8)
        + 14 * sin(3 * m_m7 - 3 * m_m8)
        + 13 * sin(m_m6 - m_m7)
        - 12 * m_vt * m_vt * cos(m_m7)
        - 12 * cos(m_m7)
        + 10 * sin(2 * m_m7 - 2 * m_m8)
        - 9 * sin(2 * m_u7)
        - 9 * m_vt * m_vt * sin(m_m7)
        + 9 * cos(2 * m_m7 - 3 * m_m8)
        + 8 * m_vt * cos(m_m6 - 2 * m_m7)
        + 7 * m_vt * cos(m_m6 - 3 * m_m7)
        - 7 * m_vt * sin(m_m6 - 3 * m_m7)
        + 7 * m_vt * sin(2 * m_m7)
        + 6 * sin(2 * m_m5 - 6 * m_m6 + 2 * m_m7)
        + 6 * cos(2 * m_m5 - 6 * m_m6 + 2 * m_m7)
        + 5 * sin(m_m6 - 4 * m_m7)
        - 4 * sin(3 * m_m7 - 4 * m_m8)
        + 4 * cos(3 * m_m7 - 3 * m_m8)
        - 3 * cos(m_m8)
        - 2 * sin(m_m8);
    b = 2775 * sin(m_u7)
        + 131 * sin(m_m7 - m_u7)
        + 130 * sin(m_m7 + m_u7);
    r = 19.21216
        - 0.90154 * cos(m_m7)
        - 0.02488 * m_vt * sin(m_m7)
        - 0.00585 * cos(m_m6 - 2 * m_m7)
        - 0.00508 * m_vt * cos(m_m7)
        - 0.00451 * cos(m_m5 - m_m7)
        + 0.00336 * sin(m_m6 - m_m7)
        + 0.00198 * sin(m_m5 - m_m7)
        + 0.00118 * cos(m_m6 - 3 * m_m7)
        + 0.00107 * sin(m_m6 - 2 * m_m7)
        - 0.00103 * m_vt * sin(2 * m_m7)
        - 0.00081 * cos(3 * m_m7 - 3 * m_m8);
}

void CPlanets::_Neptune(double& l, double& b, double& r) const
{
    l = m_VL8 * 3600 * 180 / M_PI
        + 3523 * sin(m_m8)
        - 50 * sin(2 * m_u8)
        - 43 * m_vt * cos(m_m8)
        + 29 * sin(m_m5 - m_m8)
        + 19 * sin(2 * m_m8)
        + 19 * sin(2 * m_m8)
        - 18 * cos(m_m5 - m_m8)
        + 13 * cos(m_m6 - m_m8)
        + 13 * sin(m_m6 + m_m8)
        - 9 * sin(2 * m_m7 - 3 * m_m8)
        + 9 * cos(2 * m_m7 - 2 * m_m8)
        - 5 * cos(2 * m_m7 - 3 * m_m8)
        - 4 * m_vt * sin(m_m8)
        + 4 * cos(m_m7 - 2 * m_m8)
        + 4 * m_vt * m_vt * sin(m_m8);
    b = 6404 * sin(m_u8)
        + 55 * sin(m_m8 + m_u8)
        + 55 * sin(m_m8 - m_u8)
        - 33 * m_vt * sin(m_u8);
    r = 30.07175
        - 0.25701 * cos(m_m8)
        - 0.00787 * cos(2 * m_VL7 - m_m7 - 2 * m_VL8)
        + 0.00409 * cos(m_m5 - m_m8)
        - 0.00314 * m_vt * sin(m_m8)
        + 0.00250 * sin(m_m5 - m_m8)
        - 0.00194 * sin(m_m6 - m_m8)
        + 0.00185 * cos(m_m6 - m_m8);
}

void CPlanets::_Pluto(double& l, double& b, double& r) const
{
    l = m_VL9 * 3600 * 180 / M_PI
        + 101577 * sin(m_m9)
        + 15517 * sin(2 * m_m9)
        - 3593 * sin(2 * m_u9)
        + 3414 * sin(3 * m_m9)
        - 2201 * sin(m_m9 - 2 * m_u9)
        - 1871 * sin(m_m9 - 2 * m_u9)
        + 839 * sin(4 * m_m9)
        - 757 * sin(2 * m_m9 + 2 * m_u9)
        - 285 * sin(3 * m_m9 + 2 * m_u9)
        + 227 * m_vt * m_vt * sin(m_m9)
        + 218 * sin(2 * m_m9 - 2 * m_u9)
        + 200 * m_vt * sin(m_m9);
    b = 57726 * sin(m_u9)
        + 15257 * sin(m_m9 - m_u9)
        + 14102 * sin(m_m9 + m_u9)
        + 3870 * sin(2 * m_m9 + m_u9)
        + 1138 * sin(3 * m_m9 + m_u9)
        + 472 * sin(2 * m_m9 - m_u9)
        + 353 * sin(4 * m_m9 + m_u9)
        - 144 * sin(m_m9 - 3 * m_u9)
        - 119 * sin(3 * m_u9)
        - 111 * sin(m_m9 + 3 * m_u9);
    r = 40.74638
        - 9.58235 * cos(m_m9)
        - 1.16703 * cos(2 * m_m9)
        - 0.22649 * cos(3 * m_m9)
        - 0.04996 * cos(4 * m_m9);
}

void CPlanets::JupiterSatellites(double jd_utc, tJupiterSatellites& jsat)
{
    double d = jd_utc - 2415020;
    double Mz = (358.476 + 0.9856003 * d) / 180 * M_PI;
    double Mj = (225.328 + 0.0830853 * d) / 180 * M_PI;
    double Lzj = (221.647 + 0.9025179 * d) / 180 * M_PI;
    double A = (1.92 * sin(Mz) + 0.02 * sin(Mz * 2)) / 180 * M_PI;
    double B = (5.537 * sin(Mj) + 0.167 * sin(Mj * 2)) / 180 * M_PI;
    double K = (Lzj + A - B);
    double Dl = sqrt(28.07 - 10.406 * cos(K));
    double fi = asin(sin(K) / Dl);
    double g1 = (84.5506 + 203.4058630 * (d - Dl / 173) + fi - B) * M_PI / 180;
    double g2 = (41.5015 + 101.2916323 * (d - Dl / 173) + fi - B) * M_PI / 180;
    double g3 = (109.9770 + 50.2345169 * (d - Dl / 173) + fi - B) * M_PI / 180;
    double g4 = (176.3586 + 21.4879802 * (d - Dl / 173) + fi - B) * M_PI / 180;
    jsat[0][0] = 5.906 * sin(g1);
    jsat[1][0] = 9.397 * sin(g2);
    jsat[2][0] = 14.989 * sin(g3);
    jsat[3][0] = 26.364 * sin(g4);
    jsat[0][1] = cos(g1);
    jsat[1][1] = cos(g2);
    jsat[2][1] = cos(g3);
    jsat[3][1] = cos(g4);
}

void CPlanets::Moon(double* ra, double* dec, double* rad, double* phase) const
{
    double l, b, r;
    _Moon(l, b, r);
    DoneGeoc(l, b, ra, dec);
    if (rad)
        *rad = r / 23454.8; /* AU */;
    if (phase)
        *phase = normalizeAngle(((m_jd - 1721088.5) / 29.53059) * 2 * M_PI);
}

void CPlanets::Sun(double* ra, double* dec, double* rad) const
{
    Done(m_lambdas, 0, ra, dec);
    if (rad)
        *rad = m_ds;
}

void CPlanets::Mercury(double* ra, double* dec, double* rad, double* phase) const
{
    double l, b, r;
    _Mercury(l, b, r);
    DoneHelioc(l, b, r, ra, dec, rad, phase);
}

void CPlanets::Venus(double* ra, double* dec, double* rad, double* phase) const
{
    double l, b, r;
    _Venus(l, b, r);
    DoneHelioc(l, b, r, ra, dec, rad, phase);
}

void CPlanets::Mars(double* ra, double* dec, double* rad, double* phase) const
{
    double l, b, r;
    _Mars(l, b, r);
    DoneHelioc(l, b, r, ra, dec, rad, phase);
}

void CPlanets::Jupiter(double* ra, double* dec, double* rad, double* phase) const
{
    double l, b, r;
    _Jupiter(l, b, r);
    DoneHelioc(l, b, r, ra, dec, rad, phase);
}

void CPlanets::Saturn(double* ra, double* dec, double* rad, double* phase) const
{
    double l, b, r;
    _Saturn(l, b, r);
    DoneHelioc(l, b, r, ra, dec, rad, phase);
}

void CPlanets::Uranus(double* ra, double* dec, double* rad, double* phase) const
{
    double l, b, r;
    _Uranus(l, b, r);
    DoneHelioc(l, b, r, ra, dec, rad, phase);
}

void CPlanets::Neptune(double* ra, double* dec, double* rad, double* phase) const
{
    double l, b, r;
    _Neptune(l, b, r);
    DoneHelioc(l, b, r, ra, dec, rad, phase);
}

void CPlanets::Pluto(double* ra, double* dec, double* rad, double* phase) const
{
    double l, b, r;
    _Pluto(l, b, r);
    DoneHelioc(l, b, r, ra, dec, rad, phase);
}
