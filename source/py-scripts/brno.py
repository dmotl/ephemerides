#! /usr/bin/env python
# -*- coding: utf-8 -*-
"""

brno.py
Read data from the BRNO catalogue, fill in missing information from GCVS
and write the catalogue file in the format expected by Ephemerides.
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
from gcvs import read_gcvs, read_nsv, read_crossid

#And;RT;p;1;136;1576;0.62892951;51463.24;23:11:10.11;+53:1:33.2;8.55;9.47;8.88;V;

#CONS NAME             PS RATING RA2000   DE2000  M0           PER          MAX      PRIM     SEK      BRANCH LD   SD   GSC         TYPE         N10    N
#And  RT               p  1      231110.1 +530133 54722.3598   0.62892951   8.55     9.47     9.47     V      2.6  0.0  03998.02167 EA           176    1555

def read_brno(filepath):
    out = []
    with open(filepath, 'r') as src:
        lines = src.readlines()
        for line in lines:
            out.append(line.split(";"))
    return out

def find_gcvs_data(cons, name, gcvs):
    if name[0]=="G" and len(name)==10:
        return None
    if len(name)==9 and name[0:4]=="NSV ":
        return None

    gcvs_name = None
    if len(name)==5 and name[0]=="V" and name[1]==" ":
        gcvs_name = "V{:04}".format(int(name[2:]))
    else:
        gcvs_name = name

    if gcvs_name=="u" and cons=="Her":
        gcvs_name = "u."
    elif gcvs_name=="chi" and cons=="Hya":
        gcvs_name = "khi 2"
    elif gcvs_name=="the" and cons=="Mic":
        gcvs_name = "tet 1"
    elif gcvs_name=="dze" and cons=="Phe":
        gcvs_name = "zet"
    elif gcvs_name=="mu." and cons=="Sco":
        gcvs_name = "mu. 1"

    for j in gcvs:
        if j[0] == cons and j[1] == gcvs_name:
            return j
    return None

def find_nsv_data(nsvid, nsv):
    nsv_name = "NSV {:05}".format(nsvid)
    for j in nsv:
        if j[0] == None and j[1] == nsv_name:
            return j;
    return None

def find_vtyp_ld(cons, name, gcvs, nsv):
    gcvs_data = find_gcvs_data(cons, name, gcvs)
    if gcvs_data and len(gcvs_data[4])>0:
        if len(gcvs_data[11])>0:
            ld  = int(gcvs_data[11])*float(gcvs_data[10])*24/100
            if ld<99.95:
                return (gcvs_data[4], "{:.1f}".format(ld))
            else:
                print name + " " + cons + " " + str(ld)
                return (gcvs_data[4], "{:.0f}".format(ld))
        else:
            #if "EA" in gcvs_data[4]:
            #    print("Missing LD for: " + name + " " + cons)
            return (gcvs_data[4], "")

    if len(name)>=5 and name[0:3]=="NSV":
        nsv_data = find_nsv_data(int(name[4:]), nsv)
        if nsv_data and len(nsv_data[4])>0:
            return (nsv_data[4], "")

    #print "Missing vtyp: " + name + " " + cons
    return ("", "")

def find_gsc(cons, name, crossid):
    if len(name)>=5 and name[0]=="G" and name[5]==".":
        sect = int(name[1:5])
        index = int(name[6:])
        return "{:04}.{:05}".format(sect,index)

    gcvs_data = find_gcvs_data(cons, name, crossid)
    if gcvs_data and len(gcvs_data[2])>0:
        return gcvs_data[2]

    if len(name)>=5 and name[0:3]=="NSV":
        nsv_data = find_nsv_data(int(name[4:]), crossid)
        if nsv_data and len(nsv_data[2])>0:
            return nsv_data[2]

    #print "Missing GSC: " + name + " " + cons
    return ""

def main(filepath1, filepath2, filepath3, filepath4, target):
    brno = read_brno(filepath1)
    gcvs = read_gcvs(filepath2)
    nsv  = read_nsv(filepath3)
    crossid = read_crossid(filepath4)

    format_str = " {:4} {:16} {:2} {:6} {:8} {:7} {:12} {:12} {:8} {:8} {:8} {:6} {:4} {:4} {:11} {:12} {:6} {:6}\n"

    with open(target, 'w') as out:
        str = format_str.format("CONS","NAME","PS","RATING","RA2000","DE2000","M0","PER","MAX","PRIM","SEK","BRANCH","LD","SD","GSC","TYPE","N10","N")
        out.write(str)
        for i in brno:
            if i[2]=='r' or i[2]=='R':
                continue

            (vtyp, ld) = find_vtyp_ld(i[0].strip(), i[1].strip(), gcvs, nsv)
            gsc = find_gsc(i[0].strip(), i[1].strip(), crossid)

            ra = i[8].split(":")
            ra = int(ra[0])*3600 + int(ra[1])*60 + float(ra[2])
            ra = int(round(ra*10))
            ra = "{:02}{:02}{:03}".format(ra//36000,(ra//600)%60,(ra%600))
            ra = ra[:6] + "." + ra[6:]
            dec = i[9].split(":")
            if dec[0][0]=='-':
                sign = '-'
                dec = int(dec[0][1:])*3600 + int(dec[1])*60 + float(dec[2])
            else:
                sign = '+'
                dec = int(dec[0][1:])*3600 + int(dec[1])*60 + float(dec[2])
            dec = int(round(dec))
            dec = "{}{:02}{:02}{:02}".format(sign,dec//3600,(dec//60)%60,(dec%60))
            k = [i[0], i[1], i[2], i[3], ra, dec, i[7], i[6], i[10], i[11], i[12], i[13], ld, "", gsc, vtyp, i[4], i[5]]
            str = format_str.format(*k)
            out.write(str)

if __name__ == '__main__':
    main("brno/eb_offpred.php", "gcvs/iii/iii.dat", "gcvs/nsv/nsv.dat", "gcvs/iv/crossid.dat", "brno.dat")
