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

int elp82b(int ibody, double tjd, tELP82_Rect* xyz)
{

	double w[4][6], eart[6], peri[6], p[9][3], del[5][6], zeta[3];
	double r[4], t[6], pre[4], coef[8], ilu[5], ipla[12];

	double ideb = 0;

    xyz->X[0] = xyz->X[1] = xyz->X[3] = 0;

    double cpi = 3.141592653589793;
    double cpi2 = 2.0 * cpi;
    double pis2 = 0.5 * cpi;
    double rad = 648000.0 / cpi;
    double deg = cpi / 180.0;
    double c1 = 60;
    double c2 = 3600;
    double ath = 384747.9806743165;
    double a0 = 384747.9806448954;
    double am = 0.074801329518;
    double alfa = 0.002571881335;
    double dtasm = 2.0 * alfa / (3.0 * am);

    //
    // Lunar arguments.
    //

    w[1][1] = (218 + 18 / c1 + 59.95571 / c2) * deg;
    w[2][1] = (83 + 21 / c1 + 11.67475 / c2) * deg;
    w[3][1] = (125 + 2 / c1 + 40.39816 / c2) * deg;
    eart[1] = (100 + 27 / c1 + 59.22059 / c2) * deg;
    peri[1] = (102 + 56 / c1 + 14.42753 / c2) * deg;
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
    p[1][1] = (252 + 15 / c1 + 3.25986 / c2) * deg;
    p[2][1] = (181 + 58 / c1 + 47.28305 / c2) * deg;
    p[3][1] = eart[1];
    p[4][1] = (355 + 25 / c1 + 59.78866 / c2) * deg;
    p[5][1] = (34 + 21 / c1 + 5.34212 / c2) * deg;
    p[6][1] = (50 + 4 / c1 + 38.89694 / c2) * deg;
    p[7][1] = (314 + 3 / c1 + 18.01841 / c2) * deg;
    p[8][1] = (304 + 20 / c1 + 55.19575 / c2) * deg;
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

    double delnu = +0.55604 / rad / w[1][2];
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

    del[1][1] = del[1][1] + cpi;
    zeta[1] = w[1][1];
    zeta[2] = w[1][2] + preces;

    //
    // Precession matrix.
    // 
       
    double p1 = 0.10180391e-4;
    double p2 = 0.47020439e-6;
    double p3 = -0.5417367e-9;
    double p4 = -0.2507948e-11;
    double p5 = 0.463486e-14;

    double q1 = -0.113469002e-3;
    double q2 = 0.12372674e-6;
    double q3 = 0.1265417e-8;
    double q4 = -0.1371808e-11;
    double q5 = -0.320334e-14;

    t[1] = 1.0;

    t[2] = (tjd - 2451545.0) / 36525.0;
    t[3] = t[2] * t[2];
    t[4] = t[3] * t[2];
    t[5] = t[4] * t[2];

    pre[1] = pre[2] = pre[3] = 0;
    int ierr = 0;

    for (int ific = 1; ific <= 36; ific++) {
        if (ific >= 1 && ific <= 3) {
            // 
            // Main problem
            //
            // MAIN PROBLEM. LONGITUDE(SINE)
            // 0  0  0  2 - 411.60287      168.48 - 18433.81 - 121.62        0.40 - 0.18        0.00
            // 
            //read(nulog, 1000, end = 600, err = 700) a

            int iv = ((ific - 1) % 3) + 1;

            while (1) {
                // 210: read(nulog, 1001, end = 230, err = 700) ilu, coef
                // 1001  format (4i3,2x,f13.5,6(2x,f10.2))
                double tgv = coef[2] + dtasm * coef[6];
                if (ific == 3)
                    coef[1] -= 2.0 * coef[1] * delnu / 3.0;
                double x = coef[1] + tgv * (delnp - am * delnu) + coef[3] * delg + coef[4] * dele + coef[5] * delep;
                double y = 0;

                for (int k = 1; k <= 5; k++) {
                    for (int i = 1; i <= 4; i++)
                        y += ilu[i] * del[i][k] * t[k];
                }

                if (iv == 3)
                    y += pis2;

                y = fmod(y, cpi2);

                r[iv] = r[iv] + x * sin(y);
            }
        }
        else if (ific >= 4 && ific <= 9) {
            //
            // Figures - Tides - Relativity - Solar eccentricity.
            // 
            // EARTH FIGURE PERTURBATIONS.LONGITUDE
            //    0  0  0  0  1 270.00000   0.00003     0.075

            int iv = ((ific - 1) % 3) + 1;

            while (1) {
                // 310   read (nulog,1002,end=330,err=700) iz,ilu,pha,x,per
                double iz = 0, pha = 0, x = 0, per = 0;

                if (ific >= 7 && ific <= 9)
                    x *= t[2];
                if (ific >= 25 && ific <= 27)
                    x *= t[2];
                if (ific >= 34 && ific <= 36)
                    x *= t[3];

                double y = pha * deg;
                for (int k = 1; k <= 2; k++) {
                    y += iz * zeta[k] * t[k];
                    for (int i = 1; i <= 4; i++)
                        y += ilu[i] * del[i][k] * t[k];
                }

                y = fmod(y, cpi2);

                r[iv] += x * sin(y);
            }
        }
        else if (ific >= 10 && ific <= 21) {
            //
            // Planetary perturbations.
            // 
            int iv = ((ific - 1) % 3) + 1;

            while (1) {
                // 410   read (nulog,1003,end=480,err=700) ipla,pha,x,per
                double pha = 0, x = 0, per = 0;

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
                y = fmod(y, cpi2);
                r[iv] = r[iv] + x * sin(y);
            }
        }
    }

    //
    // Change of coordinates.
    //
    r[1] = r[2] / rad + w[1][1] + w[1][2] * t[2] + w[1][3] * t[3] + w[1][4] * t[4] + w[1][5] * t[5];
    r[2] = r[2] / rad;
    r[3] = r[3] * a0 / ath;
    double x1 = r[3] * cos(r[2]);
    double x2 = x1 * sin(r[1]);
    x1 = x1 * cos(r[1]);
    double x3 = r[3] * sin(r[2]);
    double pw = (p1 + p2 * t[2] + p3 * t[3] + p4 * t[4] + p5 * t[5]) * t[2];
    double qw = (q1 + q2 * t[2] + q3 * t[3] + q4 * t[4] + q5 * t[5]) * t[2];
    double ra = 2.0 * sqrt(1 - pw * pw - qw * qw);
    double pwqw = 2.0 * pw * qw;
    double pw2 = 1 - 2.0 * pw * pw;
    double qw2 = 1 - 2.0 * qw * qw;
    pw = pw * ra;
    qw = qw * ra;
    xyz->X[0] = pw2 * x1 + pwqw * x2 + pw * x3;
    xyz->X[1] = pwqw * x1 + qw2 * x2 - qw * x3;
    xyz->X[2] = -pw * x1 + qw * x2 + (pw2 + qw2 - 1) * x3;
	return 0;
}