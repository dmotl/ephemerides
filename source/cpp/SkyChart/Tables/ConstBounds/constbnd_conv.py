# constbnd_conv.py (Ephemerides)
# Convert constellation boundary tables to C source code
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
# py constbnd_conv.py <constbnd.dat> <constellation_names.txt> <constbnd.h>
#

import sys, os

# 2.51667 +50.50000 And  Per

def constbnd_conv(constbnd_file, const_names_file, target_file):
    out = []
    header = 1
    with open(constbnd_file, "r") as f:
        iv = 0
        lines = f.readlines()
        for line in lines:
          try:
            if line[2] == "." and line[8] == " " and (line[9] == "+" or line[9] == "-") and line[12] == "." and line[18] == " ":
                ra = float(line[0:8].strip())
                ra = round(ra * 60 * 60)
                dec = float(line[9:18].strip())
                dec = round(dec * 60 * 60)
                cons = line[19:23].strip()
                if cons == "Cra":
                   cons = "Crt"
                out.append((ra, dec, cons))
          except:
            print("Error in line: " + line)

    with open(target_file, "w") as f:
       if len(out) > 0:
           _, filename = os.path.split(constbnd_file)
           f.write("/**********************************************************************\n")
           f.write(" * This file has been automatically generated, please do not edit it!\n")
           f.write(" * Source file: " + filename + "\n")
           f.write(" *********************************************************************/\n")
           f.write("#ifndef CONSTBND_DEFS_DEFINED\n")
           f.write("  #define CONSTBND_DEFS_DEFINED\n")
           f.write("  typedef struct tConstBoundariesTable { int ra,dec,cons; } tConstBoundariesTable;\n")
           f.write("#endif\n\n")
           f.write("#include \"constellation_names.h\"\n\n")

           n = len(out)
           f.write("static const tConstBoundariesTable constbnd[{n}]".format(n=n) + " = {\n")
           for (ra,dec,cons) in out:
                str = "\t{ "
                str = str + "{A}, {B}, {C}".format(A=ra, B=dec, C=cons)
                str = str + " }, \n"
                f.write(str)
           f.write("\t};\n\n")

    return 0

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("Syntax: python constbnd_conv.py <constbnd file> <const names files> <target file>")
        exit()

    sys.exit(constbnd_conv(sys.argv[1], sys.argv[2], sys.argv[3]))
