# elp82_conv.py (Ephemerides)
# Convert ELP82 tables to C source code
#
# Copyright 2022 David Motl, dmotl@volny.cz
#
#  Redistribution and use in source and binary forms, with or without modification, are permitted
#  provided that the following conditions are met:
#
#  (1) Redistributions of source code must retain the above copyright notice, this list of conditions
#      and the following disclaimer.
#
#  (2) Redistributions in binary form must reproduce the above copyright notice, this list
#      of conditions and the following disclaimer in the documentation and/or other materials provided
#      with the distribution.
#
#  (3) Neither the name of the copyright holder nor the names of its contributors may be used
#      to endorse or promote products derived from this software without specific prior written
#      permission.
#
# Usage:
# py elp82_conv.py <source_file> <target_file>
#

import sys, os

# MAIN PROBLEM. LONGITUDE(SINE)
#  0  0  0  0   385000.52719    -7992.63      -11.06    21578.08       -4.53       11.39       -0.06
# EARTH FIGURE PERTURBATIONS. LONGITUDE
#  0  0  0  0  1 270.00000   0.00003     0.075
# PLANETARY PERTURBATIONS. TABLE 1. LONGITUDE
#  0  0  0  0  0  0  0  0  0  0  2 359.99831   0.00020     0.037
# MOON FIGURE PERTURBATIONS.LONGITUDE
#  0  0  0  0  1 303.96185   0.00004     0.075
# TIDAL EFFECTS.LONGITUDE
#  0  1  1 -1 -1 192.93665   0.00004     0.075
# RELATIVISTIC PERTURBATIONS.LONGITUDE
#  0  0  1 -1  0 179.93473   0.00006     0.082


def elp82_conv(source_file, target_file):
    out = {}
    header = 1
    with open(source_file, "r") as f:
        iv = 0
        lines = f.readlines()
        for line in lines:
          try:
            if header:
                if line.startswith("MAIN PROBLEM."):
                    iv = 1
                elif line.startswith("EARTH FIGURE PERTURBATIONS."):
                    iv = 4
                elif line.startswith("PLANETARY PERTURBATIONS. TABLE 1.") or line.startswith("PLANETARY PERTURBATIONS. TABLE1."):
                    iv = 10
                elif line.startswith("PLANETARY PERTURBATIONS. TABLE 2."):
                    iv = 16
                elif line.startswith("TIDAL EFFECTS."):
                    iv = 22
                elif line.startswith("MOON FIGURE PERTURBATIONS."):
                    iv = 28
                elif line.startswith("RELATIVISTIC PERTURBATIONS."):
                    iv = 31
                elif line.startswith("PLANETARY PERTURBATIONS(SOLAR ECCENTRICITY)."):
                    iv = 34

                if "LATITUDE/T" in line:
                    iv = iv + 3
                elif "LONGITUDE/T" in line:
                    iv = iv + 4
                elif "DISTANCE/T" in line:
                    iv = iv + 5
                elif "LATITUDE" in line:
                    iv = iv + 1
                elif "DISTANCE" in line:
                    iv = iv + 2
                header = 0
            else:
                if iv >= 1 and iv <= 3:
                    I1, I2, I3, I4, A, B1, B2, B3, B4, B5, B6 = line[0:3].strip(), line[3:6].strip(), line[6:9].strip(), line[9:12].strip(), \
                        line[12:27].strip(), line[27:39].strip(), line[39:51].strip(), line[51:63].strip(), line[63:75].strip(), \
                        line[75:87].strip(), line[87:99].strip()
                    key = iv
                    value = (I1, I2, I3, I4, A, B1, B2, B3, B4, B5, B6)
                    if key in out:
                        out[key].append(value)
                    else:
                        out[key] = [value]
                elif iv >= 10 and iv <= 21:
                    I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, B1, B2, B3 = line[0:3].strip(), line[3:6].strip(), line[6:9].strip(), \
                        line[9:12].strip(), line[12:15].strip(), line[15:18].strip(), line[18:21].strip(), line[21:24].strip(), \
                        line[24:27].strip(), line[27:30].strip(), line[30:33].strip(), line[33:43].strip(), line[43:53].strip(), \
                        line[53:63].strip()
                    key = iv
                    value = (I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, B1, B2, B3)
                    if key in out:
                        out[key].append(value)
                    else:
                        out[key] = [value]
                else:
                    I1, I2, I3, I4, I5, B1, B2, B3 = line[0:3].strip(), line[3:6].strip(), line[6:9].strip(), line[9:12].strip(), \
                        line[12:15].strip(), line[15:25].strip(), line[25:35].strip(), line[35:45].strip()
                    key = iv
                    value = (I1, I2, I3, I4, I5, B1, B2, B3)
                    if key in out:
                        out[key].append(value)
                    else:
                        out[key] = [value]
          except:
            print("Error in line: " + line)

    with open(target_file, "w") as f:
       if len(out.keys()) > 0:
            _, filename = os.path.split(source_file)
            f.write("/**********************************************************************\n")
            f.write(" * This file has been automatically generated, please do not edit it!\n")
            f.write(" * Source file: " + filename + "\n")
            f.write(" *********************************************************************/\n")
            f.write("#ifndef ELP82_DEFS_DEFINED\n")
            f.write("  #define ELP82_DEFS_DEFINED\n")
            f.write("  typedef struct tELP82Table { int i[11]; double A, B[6]; } tELP82Table;\n")
            f.write("#endif\n\n")

       for key in out:
          rows = out[key]
          n = len(rows)
          f.write("static const tELP82Table elp82_{key}[{n}]".format(key=key, n=n) + " = {\n")
          for row in rows:
            str = "\t{{ "
            if key >= 1 and key <= 3:
                str = str + "{A}, {B}, {C}, {D}".format(A=row[0], B=row[1], C=row[2], D=row[3])
                str = str + " }, "
                str = str + "{E}".format(E=row[4])
                str = str + ", { "
                str = str + "{F}, {G}, {H}, {I}, {J}, {K}".format(F=row[5], G=row[6], H=row[7], I=row[8], J=row[9], K=row[10])
            elif key >= 10 and key <= 21:
                str = str + "{A}, {B}, {C}, {D}, {E}, {F}, {G}, {H}, {I}, {J}, {K}".format(A=row[0], B=row[1], C=row[2], D=row[3], E=row[4], F=row[5], G=row[6], H=row[7], I=row[8], J=row[9], K=row[10])
                str = str + " }, "
                str = str + "0"
                str = str + ", { "
                str = str + "{F}, {G}, {H}".format(F=row[11], G=row[12], H=row[13])
            else:
                str = str + "{A}, {B}, {C}, {D}, {E}".format(A=row[0], B=row[1], C=row[2], D=row[3], E=row[4])
                str = str + " }, "
                str = str + "0"
                str = str + ", { "
                str = str + "{F}, {G}, {H}".format(F=row[5], G=row[6], H=row[7])
            str = str + " }},\n"
            f.write(str)
          f.write("\t};\n\n")

    return 0

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Syntax: python elp82_conv.py <source file> <target file>")
        exit()

    sys.exit(elp82_conv(sys.argv[1], sys.argv[2]))
