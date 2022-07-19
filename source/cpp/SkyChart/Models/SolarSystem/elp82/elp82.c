/*!
*  \file      elp82.c
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
#include "elp82.h"

#include "elp82_1.h"
#include "elp82_2.h"
#include "elp82_3.h"
#include "elp82_4.h"
#include "elp82_5.h"
#include "elp82_6.h"
#include "elp82_7.h"
#include "elp82_8.h"
#include "elp82_9.h"
#include "elp82_10.h"
#include "elp82_11.h"
#include "elp82_12.h"
#include "elp82_13.h"
#include "elp82_14.h"
#include "elp82_15.h"
#include "elp82_16.h"
#include "elp82_17.h"
#include "elp82_18.h"
#include "elp82_19.h"
#include "elp82_20.h"
#include "elp82_21.h"
#include "elp82_22.h"
#include "elp82_23.h"
#include "elp82_24.h"
#include "elp82_25.h"
#include "elp82_26.h"
#include "elp82_27.h"
#include "elp82_28.h"
#include "elp82_29.h"
#include "elp82_30.h"
#include "elp82_31.h"
#include "elp82_32.h"
#include "elp82_33.h"
#include "elp82_34.h"
#include "elp82_35.h"
#include "elp82_36.h"

#define _USE_MATH_DEFINES

#include <math.h>

// astronomical unit (m)
#define AU 149597870691.0

int elp82b(int ibody, double tjd, tELP82_Rect* xyz)
{
	double w[4][6], eart[6], peri[6], p[9][3], del[5][6], zeta[3];
	double r[4], t[6], coef[8], ilu[5], ipla[12];

    static const double rad = 3600.0 * 180.0 / M_PI;
    static const double deg = M_PI / 180.0;
    static const double ath = 384747.9806743165;
    static const double a0 = 384747.9806448954;
    static const double am = 0.074801329518;
    static const double alfa = 0.002571881335;
    
    r[0] = r[1] = r[2] = r[3] = 0;
    xyz->X[0] = xyz->X[1] = xyz->X[3] = 0;

    //
    // Lunar arguments.
    //

    w[1][1] = (218.0 + 18.0 / 60.0 + 59.95571 / 3600.0) * deg;
    w[2][1] = (83.0 + 21.0 / 60.0 + 11.67475 / 3600.0) * deg;
    w[3][1] = (125.0 + 2.0 / 60.0 + 40.39816 / 3600.0) * deg;
    eart[1] = (100.0 + 27.0 / 60.0 + 59.22059 / 3600.0) * deg;
    peri[1] = (102.0 + 56.0 / 60.0 + 14.42753 / 3600.0) * deg;
    w[1][2] = 1732559343.73604 / rad;
    w[2][2] = 14643420.2632 / rad;
    w[3][2] = -6967919.3622 / rad;
    eart[2] = 129597742.2758 / rad;
    peri[2] = 1161.2283 / rad;
    w[1][3] = -5.8883 / rad;
    w[2][3] = -38.2776 / rad;
    w[3][3] = 6.3622 / rad;
    eart[3] = -0.0202 / rad;
    peri[3] = 0.5327 / rad;
    w[1][4] = 0.6604e-2 / rad;
    w[2][4] = -0.45047e-1 / rad;
    w[3][4] = 0.7625e-2 / rad;
    eart[4] = 0.9e-5 / rad;
    peri[4] = -0.138e-3 / rad;
    w[1][5] = -0.3169e-4 / rad;
    w[2][5] = 0.21301e-3 / rad;
    w[3][5] = -0.3586e-4 / rad;
    eart[5] = 0.15e-6 / rad;
    peri[5] = 0;

    //
    // Planetary arguments.
    //

    double preces = 5029.0966 / rad;
    p[1][1] = (252.0 + 15.0 / 60.0 + 3.25986 / 3600.0) * deg;
    p[2][1] = (181.0 + 58.0 / 60.0 + 47.28305 / 3600.0) * deg;
    p[3][1] = eart[1];
    p[4][1] = (355.0 + 25.0 / 60.0 + 59.78866 / 3600.0) * deg;
    p[5][1] = (34.0 + 21.0 / 60.0 + 5.34212 / 3600.0) * deg;
    p[6][1] = (50.0 + 4.0 / 60.0 + 38.89694 / 3600.0) * deg;
    p[7][1] = (314.0 + 3.0 / 60.0 + 18.01841 / 3600.0) * deg;
    p[8][1] = (304.0 + 20.0 / 60.0 + 55.19575 / 3600.0) * deg;
    p[1][2] = 538101628.68898 / rad;
    p[2][2] = 210664136.43355 / rad;
    p[3][1] = eart[2];
    p[4][2] = 68905077.59284 / rad;
    p[5][2] = 10925660.42861 / rad;
    p[6][2] = 4399609.65932 / rad;
    p[7][2] = 1542481.19393 / rad;
    p[8][2] = 786550.32074 / rad;

    //
    // Corrections of the constants(fit to DE200 / LE200).
    //

    double delnu = 0.55604 / rad / w[1][2];
    double dele = 0.01789 / rad;
    double delg = -0.08066 / rad;
    double delnp = -0.06424 / rad / w[1][2];
    double delep = -0.12879 / rad;

    // 
    // Delaunay's arguments.
    // 

    for (int i = 1; i <= 5; i++) {
        del[1][i] = w[1][i] - eart[i];
        del[4][i] = w[1][i] - w[3][i];
        del[3][i] = w[1][i] - w[2][i];
        del[2][i] = eart[i] - peri[i];
    }

    del[1][1] = del[1][1] + M_PI;
    zeta[1] = w[1][1];
    zeta[2] = w[1][2] + preces;

    //
    // Precession matrix.
    // 
       
    static const double p1 = 0.10180391e-4;
    static const double p2 = 0.47020439e-6;
    static const double p3 = -0.5417367e-9;
    static const double p4 = -0.2507948e-11;
    static const double p5 = 0.463486e-14;

    static const double q1 = -0.113469002e-3;
    static const double q2 = 0.12372674e-6;
    static const double q3 = 0.1265417e-8;
    static const double q4 = -0.1371808e-11;
    static const double q5 = -0.320334e-14;

    t[1] = 1.0;

    t[2] = (tjd - 2451545.0) / 36525.0;
    t[3] = t[2] * t[2];
    t[4] = t[3] * t[2];
    t[5] = t[4] * t[2];

    for (int ific = 1; ific <= 36; ific++) {
        if (ific >= 1 && ific <= 3) {
            static const tELP82Table* tabs[3] = { elp82_1, elp82_2, elp82_3 };
            static const int sizes[3] = {
                sizeof(elp82_1) / sizeof(tELP82Table), sizeof(elp82_2) / sizeof(tELP82Table), sizeof(elp82_3) / sizeof(tELP82Table)
            };

            const tELP82Table* tab = tabs[ific - 1];
            int size = sizes[ific - 1];

            // 
            // Main problem
            //
            // MAIN PROBLEM. LONGITUDE(SINE)
            // 0  0  0  2 - 411.60287      168.48 - 18433.81 - 121.62        0.40 - 0.18        0.00
            // 
            //read(nulog, 1000, end = 600, err = 700) a

            int iv = ((ific - 1) % 3) + 1;

            for (int i = 0; i < size; i++, tab++) {
                // 210: read(nulog, 1001, end = 230, err = 700) ilu, coef
                // 1001  format (4i3,2x,f13.5,6(2x,f10.2))
                ilu[1] = tab->i[0], ilu[2] = tab->i[1], ilu[3] = tab->i[2], ilu[4] = tab->i[3];
                coef[1] = tab->A, coef[2] = tab->B[0], coef[3] = tab->B[1], coef[4] = tab->B[2];
                coef[5] = tab->B[3], coef[6] = tab->B[4], coef[7] = tab->B[5];

                const double dtasm = 2.0 * alfa / (3.0 * am);
                double tgv = coef[2] + dtasm * coef[6];
                if (ific == 3)
                    coef[1] -= 2.0 * coef[1] * delnu / 3.0;
                double x = coef[1] + tgv * (delnp - am * delnu) + coef[3] * delg + coef[4] * dele + coef[5] * delep;
                double y = 0;
                for (int k = 1; k <= 5; k++) {
                    for (int i = 1; i <= 4; i++)
                        y += ilu[i] * del[i][k] * t[k];
                }
                if (iv != 3)
                    r[iv] += x * sin(y);
                else
                    r[iv] += x * cos(y);
            }
        }
        else if (ific >= 4 && ific <= 9) {
            static const tELP82Table* tabs[6] = { elp82_4, elp82_5, elp82_6, elp82_7, elp82_8, elp82_9 };
            static const int sizes[6] = {
                sizeof(elp82_4) / sizeof(tELP82Table), sizeof(elp82_5) / sizeof(tELP82Table), sizeof(elp82_6) / sizeof(tELP82Table),
                sizeof(elp82_7) / sizeof(tELP82Table), sizeof(elp82_8) / sizeof(tELP82Table), sizeof(elp82_9) / sizeof(tELP82Table)
            };

            const tELP82Table* tab = tabs[ific - 4];
            int size = sizes[ific - 4];

            //
            // Figures - Tides - Relativity - Solar eccentricity.
            // 
            // EARTH FIGURE PERTURBATIONS.LONGITUDE
            //    0  0  0  0  1 270.00000   0.00003     0.075

            int iv = ((ific - 1) % 3) + 1;

            for (int i = 0; i < size; i++, tab++) {
                // 310   read (nulog,1002,end=330,err=700) iz,ilu,pha,x,per
                // 1002  format (5i3,1x,f9.5,1x,f9.5,1x,f9.3)

                int iz = tab->i[0];
                ilu[1] = tab->i[1], ilu[2] = tab->i[2], ilu[3] = tab->i[3], ilu[4] = tab->i[4];
                double pha = tab->B[0], x = tab->B[1], per = tab->B[3];

                if (ific >= 7 && ific <= 9)
                    x *= t[2];

                double y = pha * deg;
                for (int k = 1; k <= 2; k++) {
                    y += iz * zeta[k] * t[k];
                    for (int i = 1; i <= 4; i++)
                        y += ilu[i] * del[i][k] * t[k];
                }

                r[iv] += x * sin(y);
            }
        }
        else if (ific >= 10 && ific <= 21) {
            static const tELP82Table* tabs[12] = { elp82_10, elp82_11, elp82_12, elp82_13, elp82_14, elp82_15, elp82_16, elp82_17, elp82_18, elp82_19, elp82_20, elp82_21 };
            static const int sizes[12] = {
                sizeof(elp82_10) / sizeof(tELP82Table), sizeof(elp82_11) / sizeof(tELP82Table), sizeof(elp82_12) / sizeof(tELP82Table),
                sizeof(elp82_13) / sizeof(tELP82Table), sizeof(elp82_14) / sizeof(tELP82Table), sizeof(elp82_15) / sizeof(tELP82Table),
                sizeof(elp82_16) / sizeof(tELP82Table), sizeof(elp82_17) / sizeof(tELP82Table), sizeof(elp82_18) / sizeof(tELP82Table),
                sizeof(elp82_19) / sizeof(tELP82Table), sizeof(elp82_20) / sizeof(tELP82Table), sizeof(elp82_21) / sizeof(tELP82Table)
            };

            const tELP82Table* tab = tabs[ific - 10];
            int size = sizes[ific - 10];

            //
            // Planetary perturbations.
            // 
            int iv = ((ific - 1) % 3) + 1;

            for (int i = 0; i < size; i++, tab++) {
                // 410   read (nulog,1003,end=480,err=700) ipla,pha,x,per
                ipla[0] = 0;
                ipla[1] = tab->i[0], ipla[2] = tab->i[1], ipla[3] = tab->i[2], ipla[4] = tab->i[3], ipla[5] = tab->i[4];
                ipla[6] = tab->i[5], ipla[7] = tab->i[6], ipla[8] = tab->i[7], ipla[9] = tab->i[8], ipla[10] = tab->i[9];
                ipla[11] = tab->i[10];

                double pha = tab->B[0], x = tab->B[1], per = tab->B[2];

                if (ific >= 13 && ific <= 15)
                    x *= t[2];
                if (ific >= 19 && ific <= 21)
                    x *= t[2];

                double y = pha * deg;

                if (ific >= 16) {
                    for (int k = 1; k <= 2; k++) {
                        for (int i = 1; i <= 4; i++)
                            y += ipla[i + 7] * del[i][k] * t[k];
                        for (int i = 1; i <= 7; i++)
                            y += ipla[i] * p[i][k] * t[k];
                    }
                }
                else {
                    for (int k = 1; k <= 2; k++) {
                        y += (ipla[9] * del[1][k] + ipla[10] * del[3][k] + ipla[11] * del[4][k]) * t[k];
                        for (int i = 1; i <= 8; i++)
                            y += ipla[i] * p[i][k] * t[k];
                    }
                }
                r[iv] += x * sin(y);
            }
        }
        else if (ific >= 22 && ific <= 27) {
            static const tELP82Table* tabs[6] = { elp82_22, elp82_23, elp82_24, elp82_25, elp82_26, elp82_27 };
            static const int sizes[6] = {
                sizeof(elp82_22) / sizeof(tELP82Table), sizeof(elp82_23) / sizeof(tELP82Table), sizeof(elp82_24) / sizeof(tELP82Table),
                sizeof(elp82_25) / sizeof(tELP82Table), sizeof(elp82_26) / sizeof(tELP82Table), sizeof(elp82_27) / sizeof(tELP82Table)
            };

            const tELP82Table* tab = tabs[ific - 22];
            int size = sizes[ific - 22];

            //
            // Figures - Tides - Relativity - Solar eccentricity.
            // 
            // EARTH FIGURE PERTURBATIONS.LONGITUDE
            //    0  0  0  0  1 270.00000   0.00003     0.075

            int iv = ((ific - 1) % 3) + 1;

            for (int i = 0; i < size; i++, tab++) {
                // 310   read (nulog,1002,end=330,err=700) iz,ilu,pha,x,per
                // 1002  format (5i3,1x,f9.5,1x,f9.5,1x,f9.3)

                int iz = tab->i[0];
                ilu[0] = 0, ilu[1] = tab->i[1], ilu[2] = tab->i[2], ilu[3] = tab->i[3], ilu[4] = tab->i[4];
                double pha = tab->B[0], x = tab->B[1], per = tab->B[3];

                if (ific >= 25 && ific <= 27)
                    x *= t[2];

                double y = pha * deg;
                for (int k = 1; k <= 2; k++) {
                    y += iz * zeta[k] * t[k];
                    for (int i = 1; i <= 4; i++)
                        y += ilu[i] * del[i][k] * t[k];
                }

                r[iv] += x * sin(y);
            }
        }
        else if (ific >= 28 && ific <= 30) {
            static const tELP82Table* tabs[3] = { elp82_28, elp82_29, elp82_30 };
            static const int sizes[3] = {
                sizeof(elp82_28) / sizeof(tELP82Table), sizeof(elp82_29) / sizeof(tELP82Table), sizeof(elp82_30) / sizeof(tELP82Table)
            };

            const tELP82Table* tab = tabs[ific - 28];
            int size = sizes[ific - 28];

            //
            // Figures - Tides - Relativity - Solar eccentricity.
            // 
            // EARTH FIGURE PERTURBATIONS.LONGITUDE
            //    0  0  0  0  1 270.00000   0.00003     0.075

            int iv = ((ific - 1) % 3) + 1;

            for (int i = 0; i < size; i++, tab++) {
                // 310   read (nulog,1002,end=330,err=700) iz,ilu,pha,x,per
                // 1002  format (5i3,1x,f9.5,1x,f9.5,1x,f9.3)

                int iz = tab->i[0];
                ilu[1] = tab->i[1], ilu[2] = tab->i[2], ilu[3] = tab->i[3], ilu[4] = tab->i[4];
                double pha = tab->B[0], x = tab->B[1], per = tab->B[3];

                double y = pha * deg;
                for (int k = 1; k <= 2; k++) {
                    y += iz * zeta[k] * t[k];
                    for (int i = 1; i <= 4; i++)
                        y += ilu[i] * del[i][k] * t[k];
                }

                r[iv] += x * sin(y);
            }
        }
        else if (ific >= 31 && ific <= 36) {
            static const tELP82Table* tabs[6] = { elp82_31, elp82_32, elp82_33, elp82_34, elp82_35, elp82_36 };
            static const int sizes[6] = {
                sizeof(elp82_31) / sizeof(tELP82Table), sizeof(elp82_32) / sizeof(tELP82Table), sizeof(elp82_33) / sizeof(tELP82Table),
                sizeof(elp82_34) / sizeof(tELP82Table), sizeof(elp82_35) / sizeof(tELP82Table), sizeof(elp82_36) / sizeof(tELP82Table)
            };

            const tELP82Table* tab = tabs[ific - 31];
            int size = sizes[ific - 31];

            //
            // Figures - Tides - Relativity - Solar eccentricity.
            // 
            // EARTH FIGURE PERTURBATIONS.LONGITUDE
            //    0  0  0  0  1 270.00000   0.00003     0.075

            int iv = ((ific - 1) % 3) + 1;

            for (int i = 0; i < size; i++, tab++) {
                // 310   read (nulog,1002,end=330,err=700) iz,ilu,pha,x,per
                // 1002  format (5i3,1x,f9.5,1x,f9.5,1x,f9.3)

                int iz = tab->i[0];
                ilu[0] = 0, ilu[1] = tab->i[1], ilu[2] = tab->i[2], ilu[3] = tab->i[3], ilu[4] = tab->i[4];
                double pha = tab->B[0], x = tab->B[1], per = tab->B[3];

                if (ific >= 34 && ific <= 36)
                    x *= t[3];

                double y = pha * deg;
                for (int k = 1; k <= 2; k++) {
                    y += iz * zeta[k] * t[k];
                    for (int i = 1; i <= 4; i++)
                        y += ilu[i] * del[i][k] * t[k];
                }
                r[iv] += x * sin(y);
            }
        }
    }

    //
    // Change of coordinates.
    //
    r[1] = r[1] / rad + w[1][1] + w[1][2] * t[2] + w[1][3] * t[3] + w[1][4] * t[4] + w[1][5] * t[5];
    r[2] = r[2] / rad;
    r[3] = r[3] * a0 / ath * 1000 / AU;

    double rh = r[3] * cos(r[2]);
    double x3 = r[3] * sin(r[2]);
    double x1 = rh * cos(r[1]);
    double x2 = rh * sin(r[1]);

    double pw = (p1 + p2 * t[2] + p3 * t[3] + p4 * t[4] + p5 * t[5]) * t[2];
    double qw = (q1 + q2 * t[2] + q3 * t[3] + q4 * t[4] + q5 * t[5]) * t[2];
    double pwq = pw * pw;
    double qwq = qw * qw;
    double pwqw = 2.0 * pw * qw;
    double pw2 = 1 - 2.0 * pwq;
    double qw2 = 1 - 2.0 * qwq;
    double h = 1 - pwq - qwq;
    double ra = 2.0 * (h > 0 ? sqrt(h) : 0);
    pw = pw * ra;
    qw = qw * ra;

    xyz->X[0] = (pw2 * x1 + pwqw * x2 + pw * x3);
    xyz->X[1] = (pwqw * x1 + qw2 * x2 - qw * x3);
    xyz->X[2] = (-pw * x1 + qw * x2 + (pw2 + qw2 - 1.0) * x3);
	return 0;
}