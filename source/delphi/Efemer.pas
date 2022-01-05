unit Efemer;

interface

Uses Classes, Math, SysUtils, Utils, Juldat, Katalog, Tisk, StrUtils;

type TEphemRec = class(TObject)
       Katalog, Cons, ShrtName, LongName, Typ, Remarks, MinTyp : String;
       RA, DEC, M0, P, Mag1, Mag2, JD, ObjA, Objh, SunA, Sunh : double;
       Lon, Lat, Twilight : double;
       MoonA, Moonh, MoonP, MoonD : double;
       Epoch, Pts, KIndex : integer;
       Constructor Create(ARec:TKatZaznam; AJD:double; AEpoch:integer;
         ALon, ALat, ATwilight, ATZBias:double);
       Constructor CreateCopy(AOrig:TEphemRec);
       Procedure GetInfo(L:TStrings);
     end;

     TOnProc = procedure(CustomData:TEphemRec) of object;

Procedure Ephemeride(ARec:TKatZaznam; AJD1, AJD2:double; Lon, Lat, Twilight:double;
  TimeZoneX:integer; FTime, FNight:boolean; TimeFrom, TimeTo:double; FAzimuth:boolean;
  AzFrom, AzTo:double; FAltitude:boolean; AltFrom, AltTo:double;
  FObjMoon:boolean; ObjMoon:double; OnProc:TOnProc);

implementation

Uses DSun, DMoon;

Constructor TEphemRec.Create;
var MoonRA, MoonDec, SunRA, SunDec:double;
begin
  JD      := AJD;
  Epoch   := AEpoch;
  Lon     := ALon;
  Lat     := ALat;
  Twilight:= ATwilight;
  ShrtName:= ARec.ShrtName;
  LongName:= ARec.LongName;
  Cons    := ARec.Cons;
  MinTyp  := ARec.MinTyp;
  RA      := ARec.RA;
  Dec     := ARec.Dec;
  M0      := ARec.M0;
  P       := ARec.Per;
  Mag1    := ARec.Mag1;
  Mag2    := ARec.Mag2;
  Pts     := ARec.Rating;
  Katalog := ARec.Katalog;
  KIndex  := ARec.KIndex;
  Remarks := ARec.Remarks;
  Typ     := ARec.VarTypCaption;
  RaDeToAzAlt(RA,Dec,AJD,ALon,ALat,ObjA,Objh);
  SunRADec(AJD,SunRA,SunDec);
  RaDeToAzAlt(SunRA,SunDec,JD,ALon,ALat,SunA,Sunh);
  MoonRADecPhase(AJD,MoonRA,MoonDec,MoonP);
  RaDeToAzAlt(MoonRA,MoonDec,JD,ALon,ALat,MoonA,Moonh);
  MoonD   :=RaDeDistance(RA,Dec,MoonRA,MoonDec);
end;

Constructor TEphemRec.CreateCopy;
begin
  JD      := AOrig.JD;
  Epoch   := AOrig.Epoch;
  Lon     := AOrig.Lon;
  Lat     := AOrig.Lat;
  Twilight:= AOrig.Twilight;
  ShrtName:= AOrig.ShrtName;
  LongName:= AOrig.LongName;
  Cons    := AOrig.Cons;
  MinTyp  := AOrig.MinTyp;
  RA      := AOrig.RA;
  Dec     := AOrig.Dec;
  M0      := AOrig.M0;
  P       := AOrig.P;
  Mag1    := AOrig.Mag1;
  Mag2    := AOrig.Mag2;
  Pts     := AOrig.Pts;
  Katalog := AOrig.Katalog;
  KIndex  := AOrig.KIndex;
  Remarks := AOrig.Remarks;
  Typ     := AOrig.Typ;
  ObjA    := AOrig.ObjA;
  Objh    := AOrig.Objh;
  SunA    := AOrig.SunA;
  Sunh    := AOrig.Sunh;
  MoonA   := AOrig.MoonA;
  Moonh   := AOrig.Moonh;
  MoonP   := AOrig.MoonP;
  MoonD   := AOrig.MoonD;
end;

Procedure Ephemeride;
var ok:boolean;
    E0,E1,E:integer;
    JD, F, F0, F1:double;
    Data:TEphemRec;
begin
 if (ARec.M0>0) and (ARec.Per>0.00001) then begin
   E0:=floor((JDHel(AJD1,ARec.RA,ARec.DEC)-ARec.M0)/ARec.Per);
   E1:=ceil((JDHel(AJD2,ARec.RA,ARec.DEC)-ARec.M0)/ARec.Per);
   for E:=E0 to E1 do begin
     JD:=JDGeo(E*ARec.Per+ARec.M0,ARec.RA,ARec.DEC);
     if (JD>AJD1)and(JD<AJD2) then begin
       { Time (absolute) }
       ok:=true;
       if FTime and not FNight then begin
         F0:=TimeFrom/24;
         F1:=TimeTo/24;
         F:=frac(JD+0.5);
         if (F0<=F1)and((F<F0)or(F>=F1)) then ok:=false;
         if (F1<F0)and((F>=F1)and(F<F0)) then ok:=false;
       end;
       if not ok then
         continue;

       Data:=TEphemRec.Create(ARec, JD, E, Lon, Lat, Twilight, TimeZoneX);
       { Time (nighttime) }
       if ok and FTime and FNight then begin
         if Data.Sunh > -Twilight then ok:=false;
       end;
       { Altitude }
       if ok and FAltitude then begin
         if (Data.Objh<AltFrom)or(Data.Objh>AltTo) then ok:=false;
       end;
       { Azimuth }
       if ok and FAzimuth then begin
         if (AzFrom<=AzTo)and((Data.ObjA<AzFrom)or(Data.ObjA>=AzTo)) then ok:=false;
         if (AzTo<AzFrom)and((Data.ObjA>=AzTo)and(Data.ObjA<AzFrom)) then ok:=false;
       end;
       { Object-Moon distance }
       if ok and FObjMoon then begin
         if (Data.MoonD<ObjMoon) then ok:=false;
       end;
       if ok then
         OnProc(Data);
       Data.Free;
     end;
   end;
 end;
end;

Procedure TEphemRec.GetInfo;
var JDRise, JDTrans, JDSet, XBefore, XMin, XAfter:double;
    Cond:RiseSetCond;
begin
 L.BeginUpdate;
 L.Clear;
 L.Add('Name='+LongName);
 L.Add('Epoch='+Format('%d',[Epoch]));
 L.Add('JD (geo)='+Format('%.4f',[JD]));
 L.Add('Date (geo)='+FormatDateTime('yyyy-mm-dd h:nn',JDToDateTime(JD)));
 L.Add('JD (hel)='+Format('%.4f',[JDHel(JD,RA,DEC)]));
 L.Add('Date (hel)='+FormatDateTime('yyyy-mm-dd h:nn',JDToDateTime(JDHel(JD,RA,DEC))));
 L.Add('Hel. corr.='+Format('%.4f',[HelCorr(RA,DEC,JD)]));
 L.Add('Azimuth='+Format('%.0f° (%s)',[ObjA,AzToStr(ObjA)]));
 L.Add('Altitude='+Format('%.0f°',[Objh]));
 if ObjH>=0 then
   JDRise:=RaDeToRise(Ra, Dec, JD, Lon, Lat, 0, rtBefore, cond)
 else
   JDRise:=RaDeToRise(Ra, Dec, JD, Lon, Lat, 0, rtAfter, cond);
 if Cond=rcOK then
   L.Add('Rises='+FormatDateTime('yyyy-mm-dd h:nn',JDToDateTime(JDRise)))
 else
   L.Add('Rises=*****');
 JDTrans:=RADeToTransit(Ra, Dec, JD, Lon, Lat, rtNearest);
 if (Dec>=Lat-90) and (Dec<=Lat+90) then
   L.Add('Transits='+FormatDateTime('yyyy-mm-dd h:nn',JDToDateTime(JDTrans)))
 else
   L.Add('Transits=*****');
 if ObjH>=0 then
   JDSet:=RaDeToSet(Ra, Dec, JD, Lon, Lat, 0, rtAfter, cond)
 else
   JDSet:=RaDeToSet(Ra, Dec, JD, Lon, Lat, 0, rtBefore, cond);
 if cond=rcOK then
   L.Add('Sets='+FormatDateTime('yyyy-mm-dd h:nn',JDToDateTime(JDSet)))
 else
   L.Add('Sets=*****');
 XBefore := AirMass(JD - 0.5/24.0, RA, Dec, Lon, Lat);
 if (XBefore>0) then
   L.Add('Airmass (JD-0:30)='+Format('%.3f', [XBefore]))
 else
   L.Add('Airmass (JD-0:30)=*****');
 XMin := AirMass(JD, RA, Dec, Lon, Lat);
 if (XMin>0) then
   L.Add('Airmass (JD)='+Format('%.3f', [XMin]))
 else
   L.Add('Airmass (JD)=*****');
 XAfter := AirMass(JD + 0.5/24.0, RA, Dec, Lon, Lat);
 if (XAfter>0) then
   L.Add('Airmass (JD+0:30)='+Format('%.3f', [XAfter]))
 else
   L.Add('Airmass (JD+0:30)=*****');

 // Solar data
 if (Sunh >= 0.0) then
   L.Add('Solar elevation='+Format('%.0f° (%s)', [Sunh, 'daytime']))
 else if (Sunh > -Twilight) then begin
   if (SunA <= 180) then
      L.Add('Solar elevation='+Format('%.0f° (%s)', [Sunh, 'dawn']))
   else
      L.Add('Solar elevation='+Format('%.0f° (%s)', [Sunh, 'dusk']))
 end else
   L.Add('Solar elevation='+Format('%.0f° (%s)', [Sunh, 'nighttime']));

 // Lunar data
 if (Moonh >= 0.0) then
   L.Add('Lunar elevation='+Format('%.0f° (%s)', [Moonh, 'above horizon']))
 else if (Moonh > -Twilight) then begin
   if (MoonA <= 180) then
      L.Add('Lunar elevation='+Format('%.0f° (%s)', [Moonh, 'rising']))
   else
      L.Add('Lunar elevation='+Format('%.0f° (%s)', [Moonh, 'setting']))
 end else
   L.Add('Lunar elevation='+Format('%.0f° (%s)', [Moonh, 'below horizon']));

 L.Add('Lunar phase='+FormatLunarPhase(MoonP));
 L.Add('Lunar illumination ='+FormatLunarIllumination(MoonP));
 L.Add('Obj-Moon distance='+Format('%.0f°', [MoonD]));
 L.EndUpdate;
end;

end.

