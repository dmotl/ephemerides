# tests_conv.py (Ephemerides)
# Convert VSOP87 tables to C source code
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
# py tests_conv.py <source_file> <target_file>
#

import sys, os

#
#VSOP87E  URANUS      JD2122820.0  19/12/1099 12h TDB
#x -22.7959876638  au       y  19.5945850298  au       z    .1205430330  au
#

def tests_conv(source_file, target_file):
    out = {}
    with open(source_file, "r") as f:
        lines = f.readlines()
        for line in lines:
          try:
            if line[0:8] == " VSOP87A" or line[0:8] == " VSOP87C":
                body = line[10:22].strip().replace("-", "_")
                jd = line[24:33]
                version = line[7]
            elif line[0:3] == " x ":
                x, y, z = line[3:17], line[30:44], line[59:71]
            elif line[0:3] == " x'":
                xd, yd, zd = line[3:17], line[30:44], line[59:71]
                if body != None and jd != None:
                    key = (body + "_" + version)
                    if key in out:
                        out[key].append((jd, x, y, z, xd, yd, zd))
                    else:
                        out[key] = [(jd, x, y, z, xd, yd, zd)]
            else:
                body = None
                jd = None
                pass
          except:
            print("Error in line: " + line)

    with open(target_file, "w") as f:
       if len(out.keys()) > 0:
            _, filename = os.path.split(source_file)
            f.write("/**********************************************************************\n")
            f.write(" * This file has been automatically generated, please do not edit it!\n")
            f.write(" * Source file: " + filename + "\n")
            f.write(" *********************************************************************/\n")
            f.write("#ifndef VSOP87_TEST_DEFS_DEFINED\n")
            f.write("  #define VSOP87_TESTS_DEFS_DEFINED\n")
            f.write("  typedef struct tVSOP87TestXYZ { double jd; double X, Y, Z; double Xdot, Ydot, Zdot; } tVSOP87TestXYZ;\n")
            f.write("#endif\n\n")

       for key in out:
          rows = out[key]
          n = len(rows)
          f.write("static const tVSOP87TestXYZ vsop87_{key}[{n}]".format(key=key, n=n) + " = {\n")
          for row in rows:
            f.write("\t{ " + ("{JD}, {X}, {Y}, {Z}, {XD}, {YD}, {ZD}".format(JD=row[0], X=row[1], Y=row[2], Z=row[3], XD=row[4], YD=row[5], ZD=row[6])) + " },\n")
          f.write("\t};\n\n")

    return 0

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Syntax: python tests_conv.py <source file> <target file>")
        exit()

    sys.exit(tests_conv(sys.argv[1], sys.argv[2]))
