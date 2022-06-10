# constellation_names_conv.py (Ephemerides)
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
# py constellation_names_conv.py <constellation_names.txt> <constellation_names>
#

import sys, os

#And  Andromeda

def constellation_names_conv(source_file, target_file):
    out = []
    header = 1
    with open(source_file, "r") as f:
        iv = 0
        lines = f.readlines()
        for line in lines:
          try:
            if line[4] == " " and line[0] >= "A" and line[0] <= "Z" and line[5] >= "A" and line[5] <= "Z":
                abbr = line[0:4].strip()
                name = line[5:].strip()
                out.append((abbr, name))
          except:
            print("Error in line: " + line)

    prefix, file_extension = os.path.splitext(target_file)
    h_file = prefix + ".h"

    with open(h_file, "w") as f:
       _, filename = os.path.split(source_file)
       f.write("/**********************************************************************\n")
       f.write(" * This file has been automatically generated, please do not edit it!\n")
       f.write(" * Source file: " + filename + "\n")
       f.write(" *********************************************************************/\n")
       f.write("#ifndef CONSTELLATION_NAMES_DEFINED\n")
       f.write("#define CONSTELLATION_NAMES_DEFINED\n\n")

       f.write("/* Constellations */\ntypedef enum tConstellation\n{\n")
       f.write("\t/* Undefined constellation */\n\tNone,\n\n")

       n = len(out)
       for (x, i) in zip(out, range(n)):
            f.write("\t/* {B} */\n\t{A},\n\n".format(A=x[0], B=x[1]))

       f.write("\t/* An item after the last constellation */\n\tEndOfConstellations\n")
       f.write("} tConstellation;\n\n")

       f.write("#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n")
       f.write("\tconst char *get_constellation_abbreviation(tConstellation cons);\n\n")
       f.write("\tconst char *get_constellation_name(tConstellation cons);\n\n")
       f.write("#ifdef __cplusplus\n}\n#endif\n\n")

       f.write("#endif\n")

    c_file = prefix + ".c"

    with open(c_file, "w") as f:
       _, filename = os.path.split(source_file)
       f.write("/**********************************************************************\n")
       f.write(" * This file has been automatically generated, please do not edit it!\n")
       f.write(" * Source file: " + filename + "\n")
       f.write(" *********************************************************************/\n")
       f.write("#include \"constellation_names.h\"\n")

       n = len(out)
       f.write("/* Constellation names */\nstatic const struct { char *abbr, *name; } ")
       f.write("constellation_names[{A}]".format(A=n + 1))
       f.write(" = {\n\t{ \"\", \"\" },\n")

       for (x, i) in zip(out, range(n)):
            str = "\t{ "
            str = str + "\"{A}\", \"{B}\"".format(A=x[0], B=x[1])
            str = str + "},\n"
            f.write(str)

       f.write("};\n\n")

       f.write("#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n")
       f.write("\tconst char *get_constellation_abbreviation(tConstellation cons) { if (cons > 0 && cons < EndOfConstellations) return constellation_names[cons].abbr; else return 0; }\n\n")
       f.write("\tconst char *get_constellation_name(tConstellation cons) { if (cons > 0 && cons < EndOfConstellations) return constellation_names[cons].name; else return 0; }\n\n")
       f.write("#ifdef __cplusplus\n}\n#endif\n\n")

    return 0

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Syntax: python constellation_names_conv.py <constbnd file> <target base name>")
        exit()

    sys.exit(constellation_names_conv(sys.argv[1], sys.argv[2]))
