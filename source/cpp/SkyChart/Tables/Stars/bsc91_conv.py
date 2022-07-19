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
# py bsc91_conv.py <clines.txt> <clines.h>
#

import sys, os

#  15 21Alp AndBD+28    4    358 73765   1I     94  Alp And  000313.0+283218000823.3+290526111.73-32.84 2.06  -0.11 -0.46 -0.10   B8IVpMnHg         v+0.136-0.163 +.032-012SBO    56  8.5  81.5      *
#   1-  4  I4     ---     HR       [1/9110]+ Harvard Revised Number
#                                    = Bright Star Number
#   26- 31  I6     ---     HD       [1/225300]? Henry Draper Catalog Number
#  76- 77  I2     h       RAh      ?Hours RA, equinox J2000, epoch 2000.0 (1)
#  78- 79  I2     min     RAm      ?Minutes RA, equinox J2000, epoch 2000.0 (1)
#  80- 83  F4.1   s       RAs      ?Seconds RA, equinox J2000, epoch 2000.0 (1)
#      84  A1     ---     DE-      ?Sign Dec, equinox J2000, epoch 2000.0 (1)
#  85- 86  I2     deg     DEd      ?Degrees Dec, equinox J2000, epoch 2000.0 (1)
#  87- 88  I2     arcmin  DEm      ?Minutes Dec, equinox J2000, epoch 2000.0 (1)
#  89- 90  I2     arcsec  DEs      ?Seconds Dec, equinox J2000, epoch 2000.0 (1)
# 103-107  F5.2   mag     Vmag     ?Visual magnitude (1)
#     108  A1     ---   n_Vmag    *[ HR] Visual magnitude code


def bsc91_conv(catalog_file, target_file):

    out = []
    with open(catalog_file, "r") as f:
	    const = ""
	    lines = f.readlines()
	    for line in lines:
	        try:
	          if line[83] == "+" or line[83] == "-":
	            bs_num = line[0:4].strip()
	            hd_num = line[25:31].strip()
	            ra_hours = int(line[75:77])
	            ra_minutes = int(line[77:79])
	            ra_seconds = float(line[79:83])
	            de_sign = -1 if line[83] == "-" else +1
	            de_degrees = int(line[84:86])
	            de_minutes = int(line[86:88])
	            de_seconds = int(line[88:90])
	            v_mag = float(line[102:107])
	            ra_out = int(ra_hours * 36000 + ra_minutes * 600 + ra_seconds * 10 + 0.5)
	            de_out = de_sign * (de_degrees * 3600 + de_minutes * 60 + de_seconds)
	            mag_out = int(v_mag * 100 + 0.5)
	            out.append((bs_num, hd_num, ra_out, de_out, mag_out))
	        except:
	            print("Error in line: " + line)

    with open(target_file, "w") as f:
       if len(out) > 0:
           _, filename = os.path.split(catalog_file)
           f.write("/**********************************************************************\n")
           f.write(" * This file has been automatically generated, please do not edit it!\n")
           f.write(" * Source file: " + filename + "\n")
           f.write(" *********************************************************************/\n")
           f.write("#ifndef BSC91_DEFS_DEFINED\n")
           f.write("  #define BSC91_DEFS_DEFINED\n")
           f.write("  typedef struct tBSC91Table { int bs_id, hd_id, ra, dec, vmag; } tBSC91Table;\n")
           f.write("#endif\n\n")
           f.write("#include \"constellation_names.h\"\n\n")

           n = len(out)
           f.write("static const tBSC91Table bsc91_table[{n}]".format(n=n) + " = {\n")
           for (bs, hd, ra, dec, vmag) in out:
                str = "\t{ "
                str = str + "{A}, {B}, {C}, {D}, {E}".format(A=bs, B=hd, C=ra, D=dec, E=vmag)
                str = str + " }, \n"
                f.write(str)
           f.write("\t};\n\n")

    return 0

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Syntax: python bsc91_conv <catalog file> <output file>")
        exit()

    sys.exit(bsc91_conv(sys.argv[1], sys.argv[2]))
