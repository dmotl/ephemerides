# clines_conv.py (Ephemerides)
# Convert constellation lines to C source code
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
# py clines_conv.py <clines.txt> <clines.h>
#

import sys, os

def clines_conv(clines_file, hip2hd_file, target_file):

    hip2hd = {}
    with open(hip2hd_file, "r") as f:
        lines = f.readlines()
        for line in lines:
            try:
                line = line.split("=")
                hip = int(line[0])
                hd = int(line[1])
                hip2hd[hip] = hd
            except:
	            print("Error in line: " + line)

    print(hip2hd[116771])

    out = []
    with open(clines_file, "r") as f:
	    const = ""
	    lines = f.readlines()
	    for line in lines:
	      if line[0] != "#":
	        try:
	            const = line[0:3].strip()
	            stars = line[4:].split(" ")
	            nlines = int(stars[0])
	            for i in range(nlines):
	                hip_from = int(stars[1 + i*2].strip())
	                hd_from = hip2hd[hip_from]
	                hip_to   = int(stars[2 + i*2].strip())
	                hd_to = hip2hd[hip_to]
	                out.append((const, hd_from, hd_to))
	        except:
	            print("Error in line: " + line)
	            raise

    with open(target_file, "w") as f:
       if len(out) > 0:
           _, filename = os.path.split(clines_file)
           f.write("/**********************************************************************\n")
           f.write(" * This file has been automatically generated, please do not edit it!\n")
           f.write(" * Source file: " + filename + "\n")
           f.write(" *********************************************************************/\n")
           f.write("#ifndef CLINES_DEFS_DEFINED\n")
           f.write("  #define CLINES_DEFS_DEFINED\n")
           f.write("  typedef struct tConstLinesTable { int hd_start, hd_end, cons; } tConstLinesTable;\n")
           f.write("#endif\n\n")
           f.write("#include \"constellation_names.h\"\n\n")

           n = len(out)
           f.write("static const tConstLinesTable constlines[{n}]".format(n=n) + " = {\n")
           for (const, hd_from, hd_to) in out:
                str = "\t{ "
                str = str + "{A}, {B}, {C}".format(A=hd_from, B=hd_to, C=const)
                str = str + " }, \n"
                f.write(str)
           f.write("\t};\n\n")

    return 0

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("Syntax: python clines_conv.py <clines file> <hip2hd file> <output file>")
        exit()

    sys.exit(clines_conv(sys.argv[1], sys.argv[2], sys.argv[3]))
