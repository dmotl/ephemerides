unit juldat;

(*
    Protokoly 2.5
    Copyright (C) 2002  Ing. David Motl

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*)

interface

Uses SysUtils, Math;

type RiseSetType = (rtNearest, rtBefore, rtAfter);
     RiseSetCond = (rcOK, rcAlwaysAbove, rcAlwaysBelow);

Function  JDToDateTime(JD:double):TDateTime;
          // Prevede JD na datum a cas
Function  DateTimeToJD(DT:TDateTime):double;
          // Prevede datum a cas na JD

Function  HelCorr(ARA,ADE,AJDgeo:double):double;
          { Vraci velikost heliocentricke korekce
            ARA - rektascenze v hodinach;
            ADE - deklinace ve stupnich;
            AJDgeo - geocentricke jd
            -----------------------------------
            JDHel = JDGeo + HelCorr
          }
Function  JDhel(JD,RA,DE:double):double;
          // Prevod na heliocentricke JD
Function  JDgeo(JD,RA,DE:double):double;
          // Prevod na geocentricke JD
Procedure RaDeToAzAlt(Ra,De,Jd,Lon,Lat:double; var Az,Alt:double);
          // Azimut a vyska objektu nad obzorem
Function  RaDeToTransit(Ra,De:double; jd,lon,lat:double; typ:RiseSetType):double;
          // Prochod objektu svetovym polednikem
Function  RaDeToRise(Ra,De:double; jd,lon,lat,alt:double; typ:RiseSetType; var cond:RiseSetCond):double;
          // Vychod objektu (alt = vyska nad obzorem)
Function  RaDeToSet(Ra,De:double; jd,lon,lat,alt:double; typ:RiseSetType; var cond:RiseSetCond):double;
          // Vychod objektu (alt = vyska nad obzorem)
Function  AirMass(jd, ra, dec, lon, lat:double):double;
          // Computes air-mass coefficient
Function  RaDeDistance(Ra1,De1:double; Ra2,De2:double):double;
          // Angular distance of two objects

implementation

Function JDToDateTime;
begin
 if JD<2000000 then JD:=JD+2400000;
 Result:=JD-2415018.5;
end;

Function DateTimeToJD;
begin
 Result:=2415018.5+DT;
end;

Function ArcSin(x:real):real;
{ Arkus sinus (radiany) }
begin
 ArcSin := ArcTan (x/sqrt (1-sqr (x)))
end;

Procedure Coords(ra,de:real; var la,be:real);
{ Prevede souradnice ra,de (rovnikove) na la, be (ekliptikalni) }
var eps:real;
begin
  eps:=(23+26/60)/180*pi;  { Sklon ekliptiky 23°26' }
  { Prevod na radiany }
  ra:=ra/12*pi;
  de:=de/180*pi;
  while ra<0 do ra:=ra+2*pi;     { Do intervalu 0..2pi }
  while ra>=2*pi do ra:=ra-2*pi;
  { Vylouceni singularit }
  if de=pi/2 then begin
    la:=pi/2; be:=pi/2-eps;
  end else
  if de=-pi/2 then begin
    la:=3*pi/2; be:=eps-pi/2;
  end else
  if ra=pi/2 then begin
    la:=pi/2; be:=de-eps;
  end else
  if ra=3*pi/2 then begin
    la:=3*pi/2; be:=de+eps;
  end else begin
  { Normalni vypocet }
  be:=arcsin(cos(eps)*sin(de)-sin(eps)*cos(de)*sin(ra));
  la:=arctan((sin(eps)*sin(de)+cos(eps)*cos(de)*sin(ra))/(cos(de)*cos(ra)));
  if cos(ra)<0 then la:=la+pi; { Do spravneho kvadrantu }
  end;
end;

Procedure Sun(JD:real; var rs,las:real);
{ Vypocet ekl. delky slunce a vzdalenosti zeme - slunce }
var t,vt,Ls,Ms,M5,M4,M2,Lm:real;
begin
t:=jd-2451545;
vt:=1+(t/36525);
Ls:=(0.779072 + 0.00273790931*t)*2*pi;
ms:=(0.993126 + 0.00273777850*t)*2*pi;
M5:=(0.056531 + 0.00023080893*t)*2*pi;
M4:=(0.053856 + 0.00145561327*t)*2*pi;
M2:=(0.140023 + 0.00445036173*t)*2*pi;
Lm:=(0.606434 + 0.03660110129*t)*2*pi;
las:=Ls*3600*180/pi+6910*sin(ms)
      +  72*sin(2*ms)
      -17*vt*sin(ms)
      -   7*cos(ms-m5)
      +   6*sin(lm-ls)
      +   5*sin(4*ms+8*m4+3*m5)
      -   5*cos(2*ms-2*m2)
      -   4*sin(ms-m2)
      +   4*cos(4*ms-8*m4+3*m5)
      +   3*sin(2*ms-2*m2)
      -   3*sin(m5)
      -   3*sin(2*ms-2*m5);
las:=las/3600/180*pi;     { Ekl. delka slunce v radianech }
rs:=1.00014-0.01675*cos(ms)-0.00014*cos(2*ms); { vzdalenost slunce v AU }
end;

Function HelCorr;
var la, be     : real;      { Ekliptikalni souradnice objektu }
    rs, las    : real;      { Souradnice a vzdalenost slunce }
begin
 if ajdgeo<2000000 then ajdgeo:=ajdgeo+2400000;
 Coords(ara,ade,la,be);
 Sun(ajdgeo,rs,las);
 Result:=-0.00577552*rs*cos(be)*cos(la-las);
end;

Function JDhel;
begin
 Result:=JD+HelCorr(RA,DE,JD);
end;

Function JDgeo;
begin
 Result:=JD-HelCorr(RA,DE,JD);
end;

Function siderealtime(jd:double):double;
// Computes Greenwich mean sidereal time in hours
var jd0, t3, s0, s1:double;
begin
 // JD at 0h UT
 jd0:=floor(jd) + 0.5;
 // Julian centuries
 t3:=(jd0 - 2451545.0)/36525.0;
 // Mean sidereal time for 0h UT
 s0:=6.697374558 + 2400.05133691*t3 + 0.0000258622*t3*t3 - 0.0000000017*t3*t3*t3;
 // Mean sidereal time
 s1:=s0/24.0 + 1.0027379093*(jd-jd0);
 Result:=24.0*(s1-floor(s1));
end;

Procedure RaDeToAzAlt;
var ha:double;
begin
 ha := siderealtime(JD) + (lon/15) - ra;
 de := de/180*pi;
 lat:= lat/180*pi;
 ha := ha/12*pi;
 alt:= arcsin(sin(de)*sin(lat)+cos(de)*cos(ha)*cos(lat));
 az := 3*pi/2-arctan2(cos(de)*cos(ha)*sin(lat)-sin(de)*cos(lat),cos(de)*sin(ha));
 if az > 2*pi then az:=az - 2*pi;
 az := az*180/pi;
 alt:= alt*180/pi;
end;

Function RaDeToTransit;
var ha,TTrans:double;
begin
 ha     := siderealtime(JD) + (lon/15) - ra;
 TTrans := -ha/24;
 TTrans := TTrans - floor(TTrans);
 if (typ=rtNearest) and (TTrans > 0.5) then
   TTrans := TTrans - 1.0
 else if (typ=rtBefore) and (TTrans > 0.0) then
   TTrans := TTrans - 1.0;
 Result := JD + TTrans/1.0027379093;
end;

Function RaDeToRise;
var x,ha,TRise:double;
begin
 Result:=0; cond:=rcOK;
 if lat=90 then begin
   // Terrestrial north pole: Stars with dec>=0 are above horizon, dec<0 below horizon
   if de<0 then cond:=rcAlwaysBelow else cond:=rcAlwaysAbove;
 end else if lat=-90 then begin
   // Terrestrial south pole: Stars with dec>0 are below horizon, dec<=0 above horizon
   if de>0 then cond:=rcAlwaysBelow else cond:=rcAlwaysAbove;
 end else if de=90 then begin
   // Celestial north pole: For observers with lat>=0 star is above horizon, lat<0 below horizon
   if lat<0 then cond:=rcAlwaysBelow else cond:=rcAlwaysAbove;
 end else if de=-90 then begin
   // Celestial south pole: For observers with lat>0 star is below horizon, lat<=0 above horizon
   if lat<0 then cond:=rcAlwaysBelow else cond:=rcAlwaysAbove;
 end else begin
   x:=(sin(alt/180*pi)-sin(lat/180*pi)*sin(de/180*pi))/cos(lat/180*pi)/cos(de/180*pi);
   if x>=1 then begin
     // Star is always below horizon
     cond:=rcAlwaysBelow;
   end else if x<=-1 then begin
     // Star is always above horizon
     cond:=rcAlwaysAbove;
   end else begin
     // Star rises and sets
     ha    := siderealtime(JD) + (lon/15) - ra;
     TRise := -ha/24 - arccos(x)/pi/2;
     TRise := TRise - floor(TRise);
     if (typ=rtNearest) and (TRise > 0.5) then
       TRise := TRise - 1.0
     else if (typ=rtBefore) and (TRise > 0.0) then
       TRise := TRise - 1.0;
     Result := JD + (TRise)/1.0027379093;
   end;
 end;
end;

Function RaDeToSet;
var x,ha,TSet:double;
begin
 Result:=0; cond:=rcOK;
 if lat=90 then begin
   // Terrestrial north pole: Stars with dec>=0 are above horizon, dec<0 below horizon
   if de<0 then cond:=rcAlwaysBelow else cond:=rcAlwaysAbove;
 end else if lat=-90 then begin
   // Terrestrial south pole: Stars with dec>0 are below horizon, dec<=0 above horizon
   if de>0 then cond:=rcAlwaysBelow else cond:=rcAlwaysAbove;
 end else if de=90 then begin
   // Celestial north pole: For observers with lat>=0 star is above horizon, lat<0 below horizon
   if lat<0 then cond:=rcAlwaysBelow else cond:=rcAlwaysAbove;
 end else if de=-90 then begin
   // Celestial south pole: For observers with lat>0 star is below horizon, lat<=0 above horizon
   if lat<0 then cond:=rcAlwaysBelow else cond:=rcAlwaysAbove;
 end else begin
   x:=(sin(alt/180*pi)-sin(lat/180*pi)*sin(de/180*pi))/cos(lat/180*pi)/cos(de/180*pi);
   if x>=1 then begin
     // Star is always below horizon
     cond:=rcAlwaysBelow;
   end else if x<=-1 then begin
     // Star is always above horizon
     cond:=rcAlwaysAbove;
   end else begin
     // Star rises and sets
     ha    := siderealtime(JD) + (lon/15) - ra;
     TSet  := -ha/24 + arccos(x)/pi/2;
     TSet  := TSet - floor(TSet);
     if (typ=rtNearest) and (TSet > 0.5) then
       TSet := TSet - 1.0
     else if (typ=rtBefore) and (TSet > 0.0) then
       TSet := TSet - 1.0;
     Result := JD + TSet/1.0027379093;
   end;
 end;
end;

Function AirMass(jd, ra, dec, lon, lat:double):double;
var lmst, ha, z, secz:double;
begin
	// Local mean sidereal time
	lmst:= siderealtime(jd) + (lon/15);
	// Hour angle
	ha  := lmst - ra;
	// sec of zenital distance
	lat := lat/180.0*PI;
	dec := dec/180.0*PI;
	ha  := ha/12.0*PI;
	z   := sin(lat)*sin(dec) + cos(lat)*cos(dec)*cos(ha);
	// Is the star above the horizon?
	if (z>=0.05) then begin
		secz := 1.0/z;
		// Air mass coefficient
    Result:=secz - 0.0018167*(secz-1) - 0.002875*(secz-1)*(secz-1) - 0.0008083*(secz-1)*(secz-1)*(secz-1);
	end else begin
    Result:=-1.0;
  end;
end;

// Angular distance of two objects
Function RaDeDistance;
var cosd:double;
begin
 ra1:=ra1/12*pi;
 de1:=de1/180*pi;
 ra2:=ra2/12*pi;
 de2:=de2/180*pi;
 cosd:=sin(de1)*sin(de2) + cos(de1)*cos(de2)*cos(ra1-ra2);
 Result:=arccos(cosd)/pi*180;
end;

end.

