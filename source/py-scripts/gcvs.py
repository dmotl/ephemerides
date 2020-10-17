#! /usr/bin/env python
# -*- coding: utf-8 -*-
"""

gcvs.py
Read data from the GCVS catalogue
Copyright 2014 David Motl, dmotl@volny.cz

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

"""

import os
import sys
import re

def read_gcvs(filepath):
    out = []
    with open(filepath, 'r') as src:
        lines = src.readlines()
        for line in lines:
            if len(line)>=128 and line[7]=='|' and line[19]=='|' and line[47]=='|':
                cons = line[14:17].strip()
                name = line[8:13].strip()
                ra   = line[20:28].strip()
                dec  = line[28:35].strip()
                vtyp = line[37:47].strip()
                mmax = line[48:57].strip()
                mpri = line[58:70].strip()
                msec = line[71:83].strip()
                band = line[84:86].strip()
                M0   = line[87:99].strip()
                Per  = line[106:123].strip()
                Mm   = line[127:130].strip()
                out.append((cons,name,ra,dec,vtyp,mmax,mpri,msec,band,M0,Per,Mm))
    return out

def read_nsv(filepath):
    out = []
    with open(filepath, 'r') as src:
        lines = src.readlines()
        for line in lines:
            if len(line)>=110 and line[8]=='|' and line[26]=='|' and line[44]=='|':
                num  = int(line[0:5])
                ra   = line[27:35].strip()
                dec  = line[35:42].strip()
                vtyp = line[45:50].strip()
                mmax = line[50:56].strip()
                mpri = line[58:66].strip()
                band = line[70:71].strip()
                out.append((None,"NSV {:05}".format(num),ra,dec,vtyp,mmax,mpri,band))
    return out

def read_crossid(filepath):
    crossid = []
    with open(filepath, 'r') as src:
        lines = src.readlines()
        for line in lines:
            if len(line)>5 and line[0:4]=="GSC " and line[36:39]!="NSV" and line[36]!=" ":
                cons = line[42:46].strip()
                name = line[36:42].strip()
                gsc  = line[5:16].strip()
                crossid.append((cons,name,gsc))
            elif len(line)>5 and line[0:4]=="GSC " and line[36:39]=="NSV":
                name = line[36:45]
                gsc  = line[5:16].strip()
                crossid.append((None,name,gsc))



    return crossid

def main(filepath, filepath2):
    nsv = read_nsv(filepath)
    cross_id = read_crossid(filepath2)

    types = []
    for i in nsv:
        if not (i[3] in types):
            types.append(i[3])
            print(i[3])

if __name__ == '__main__':
    main("gcvs/nsv/nsv.dat", "gcvs/iv/crossid.dat")
