# vsop87_conv.py (Ephemerides)
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
# py vsop87_conv.py <source_file> <target_file>
#

import sys, os

def vsop87_conv(source_file, target_file):
    out = {}
    with open(source_file, "r") as f:
        lines = f.readlines()
        for line in lines:
          try:
            iv, ib, ic, it = line[1], line[2], line[3], line[4]
            if line[0] == ' ' and iv >= '0' and iv <= '5' and ib >= '1' and ib <= '9' and ic >= '1' and ic <= '6' and it >= '0' and it <= '5':
                A, B, C = line[79:97].strip(), line[97:111].strip(), line[111:131].strip()
                key = iv+ib+ic+it
                if key in out:
                    out[key].append((A, B, C))
                else:
                    out[key] = [(A, B, C)]
          except:
            print("Error in line: " + line)

    with open(target_file, "w") as f:
       if len(out.keys()) > 0:
            _, filename = os.path.split(source_file)
            f.write("/**********************************************************************\n")
            f.write(" * This file has been automatically generated, please do not edit it!\n")
            f.write(" * Source file: " + filename + "\n")
            f.write(" *********************************************************************/\n")
            f.write("#ifndef VSOP87_DEFS_DEFINED\n")
            f.write("  #define VSOP87_DEFS_DEFINED\n")
            f.write("  typedef struct tVSOP87Table { double A, B, C; } tVSOP87Table;\n")
            f.write("#endif\n\n")

       for key in out:
          rows = out[key]
          n = len(rows)
          f.write("static const tVSOP87Table vsop87_{key}[{n}]".format(key=key, n=n) + " = {\n")
          for row in rows:
            f.write("\t{ " + ("{A}, {B}, {C}".format(A=row[0], B=row[1], C=row[2])) + " },\n")
          f.write("\t};\n\n")

    return 0

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Syntax: python vsop87_conv.py <source file> <target file>")
        exit()

    sys.exit(vsop87_conv(sys.argv[1], sys.argv[2]))
