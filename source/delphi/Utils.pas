unit Utils;

(*
    Newton 1.0
    Copyright (C) 2004  Ing. David Motl

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

uses Windows, Classes, SysUtils, Controls, Math, ShellAPI;

type TCompareFunc = function(i,j: integer): boolean of object;
     TSwapFunc = procedure(i,j: integer) of object;

Function  StrToBool(Str:String):boolean;
Function  StrToBoolDef(Str:String; ADef:boolean):boolean;
Function  TryStrToBool(Str:String; var AVal:boolean):boolean;
Function  BoolToStr(X:boolean):String;
Function  ifThen(C,A,B:boolean):boolean; overload;
Function  CheckDec(S:String):String;
Function  SetDec(S:String):String;
Function  DelWS(S:String):String;
procedure QuickSort(min,max: integer; Compare: TCompareFunc; Swap: TSwapFunc);
function  Fetch(var AInput: string; const ADelim: string = ' '; const ADelete: { do not localize }
              Boolean = true): string;
Function  C_To_Byte(S1:String):integer;
Function  StrToDec(X:String):integer;
Function  DecToStr(AX:double):String;
Function  RaToStr(AX:double):String;
Function  DecToStr2(AX:double):String;
Function  RaToStr2(AX:double):String;
Function  CheckFileName(S:String):String;

Function  NameToCons(S1:String):String;
          { Extrahuje jmeno souhvezdi ze jmena hvezdy }
Function  NameCompare(S1,S2:String):integer;
          { Porovnej jmena promennych (muze obsahovat souhvezdi) }
Function  ConsCompare(C1,C2:String):integer;
          { Porovnej jmena souhvezdi }

procedure LatinToWin(P:pointer; pocet: integer); overload;
Function  LatinToWin(S:String):String; overload;
          { Prekoduje znaky ze sady Latin 2 do Windows }

Procedure ExecuteApp(Path:String; Params:String='');
          { Spusti jinou aplikaci }

Function  AzToStr(Az:double):String;
          // Textove vyjadreni azimutu
Function  StrToAz(S:String):double;
          // Retezec na azimut

Function  TzToStr(Tz:integer):String;
          // Prevod casove zony na retezec
Function  TryStrToTz(Str:String; var AVal:integer):boolean;
Function  StrToTz(Str:String):integer;
          // Prevod retezce na casovou zonu

Function  DOWToStr(DOW:array of boolean):String;
          // Day of weeks
Function  LocalDateTimeToDOW(DT:TDateTime):word;
          // Day of week from a local time

Function  SystemTimeZone:integer;
          // Get time zone info from the system
          // Returns UTC bias in minutes
Function  ToLocalTime(JD:double; TimeZoneX:integer):TDateTime;
          // Convert Julian date in UT to local time
          // TimeZoneX = UTC bias in minutes, 9999 = use system time zone
Function  FromLocalTime(DT:TDateTime; TimeZoneX:integer):double;
          // Convert local time to Julian date in UTC
          // TimeZoneX = UTC bias in minutes, 9999 = use system time zone

implementation

Uses juldat;

{*******************************
  CONVERSION UTILITIES
*******************************}

Function BoolToStr;
begin
 if X then Result:='A' else Result:='N';
end;

Function TryStrToBool;
var S:String;
begin
 S:=UpperCase(Str);
 if (S='ANO') or (S='YES') or (S='TRUE') or (S='A') or (S='Y') or (S='T') then begin
   AVal:=True;
   Result:=True;
 end else
 if (S='NE') or (S='NO') or (S='FALSE') or (S='N') or (S='F') then begin
   AVal:=False;
   Result:=True;
 end else
   Result:=False;
end;

Function StrToBoolDef;
begin
 if not TryStrToBool(Str, Result) then
   Result:=ADef;
end;

Function StrToBool;
begin
 if not TryStrToBool(Str, Result) then
   raise Exception.Create('The string is not valid logic value');
end;

Function ifThen(C,A,B:boolean):boolean;
begin
 if C then Result:=A else Result:=B;
end;

procedure QuickSort;
{ Quick sort }
var i,j,l,r,Aux:integer;

  procedure DoSort;
  var xi, xr: integer;
  begin
    i:=l; j:=r;
    Aux:=(l+r) div 2;
    repeat
      while (i<=r) and Compare(i, Aux) do inc(i);
      while (j>=l) and Compare(Aux, j) do dec(j);
      if i<=j then begin
	if i<>j then begin
	  Swap(i, j);
	  if i=Aux then Aux:=j else
	  if j=Aux then Aux:=i; 
	end;
	inc(i); dec(j); 
      end;
    until i>j;
    xi:=i; xr:=r;
    if l<j then begin
      r:=j;
      DoSort;
    end;
    if xi<xr then begin
      l:=xi;
      r:=xr;
      DoSort;
    end;
  end;

begin
 if Max>Min then begin
   l:=min; r:=max;
   DoSort;
 end;
end;

Function CheckDec;
begin
 if DecimalSeparator=',' then
   while (pos('.',S)>0) do S[pos('.',S)]:=','
 else
   while (pos(',',S)>0) do S[pos(',',S)]:='.';
 Result:=S;
end;

Function SetDec;
begin
 while (pos(':',S)>0) do delete(S,pos(':',S),1);
 while (pos(',',S)>0) do S[pos(',',S)]:='.';
 Result:=S;
end;

Function DelWS;
var i:integer;
begin
 Result:='';
 for i:=1 to Length(S) do begin
   if (S[i] in [#33..#127]) then Result:=Result+S[i];
 end;
end;

function Fetch;
var
  i, l, iPos: Integer;
begin
 i:=1; l:=Length(ADelim); iPos:=0;
 while (i<=l)and(iPos=0) do begin
   if ADelim[i]=#0 then iPos := Pos(ADelim[i], AInput)
                   else iPos := AnsiPos(ADelim[i], AInput);
   inc(i);
 end;
 if iPos=0 then begin
   Result:=AInput;
   if ADelete then
     AInput := '';
 end else begin
   Result := Copy(AInput, 1, iPos - 1);
   if ADelete then
     Delete(AInput, 1, iPos + Length(ADelim) - 1);
 end;
end;

Function NameToCons;
begin
 Result:='OTHER';
 if (Length(S1)>=5) and ((S1[Length(S1)-3]=' ')or(S1[Length(S1)-3]=':')) then begin
   if C_To_Byte(copy(S1,Length(S1)-2,3))<>255 then
     Result:=copy(S1,Length(S1)-2,3)
 end;
end;

Function G_To_Byte(S1:String):integer;
begin
  Result:=0;
  if Length(s1)>0 then begin if s1[1]=' ' then s1:=s1[2]+s1[3]; if s1[1]=' ' then s1:=s1[2]; end;
  if Length(s1)=1 then s1:=s1+' '; if length(s1)=2 then s1:=s1+' ';

  // BRKA
  if s1='Alp' then Result:=1;  if s1='Bet' then Result:=2;  if s1='Gam' then Result:=3;  if s1='Del' then Result:=4;
  if s1='Eps' then Result:=5;  if s1='Zet' then Result:=6;  if s1='Eta' then Result:=7;  if s1='The' then Result:=8;
  if s1='Iot' then Result:=9;  if s1='Kap' then Result:=10; if s1='Lam' then Result:=11; if s1='Mu ' then Result:=12;
  if s1='Nu ' then Result:=13; if s1='Xi ' then Result:=14; if s1='Omi' then Result:=15; if s1='Pi ' then Result:=16;
  if s1='Rho' then Result:=17; if s1='Sig' then Result:=18; if s1='Tau' then Result:=19; if s1='Ups' then Result:=20;
  if s1='Phi' then Result:=21; if s1='Chi' then Result:=22; if s1='Psi' then Result:=23; if s1='Ome' then Result:=24;

  // GSVC
  if s1='alf' then Result:=1;  if s1='bet' then Result:=2;  if s1='gam' then Result:=3;  if s1='del' then Result:=4;
  if s1='eps' then Result:=5;  if s1='zet' then Result:=6;  if s1='eta' then Result:=7;  if s1='tet' then Result:=8;
  if s1='iot' then Result:=9;  if s1='kap' then Result:=10; if s1='lam' then Result:=11; if s1='mu.' then Result:=12;
  if s1='nu.' then Result:=13; if s1='ksi' then Result:=14; if s1='omi' then Result:=15; if s1='pi.' then Result:=16;
  if s1='rho' then Result:=17; if s1='sig' then Result:=18; if s1='tau' then Result:=19; if s1='ups' then Result:=20;
  if s1='phi' then Result:=21; if s1='khi' then Result:=22; if s1='psi' then Result:=23; if s1='ome' then Result:=24;

  // Exceptions - BRNO
  if s1='alp' then Result:=1;  if s1='dze' then Result:=6;  if s1='the' then Result:=8;  if s1='mu ' then Result:=12;
  if s1='nu ' then Result:=13; if s1='xi ' then Result:=14; if s1='pi ' then Result:=16; if s1='chi' then Result:=22;
end;

Function P_To_Byte(S1:String):integer;
var i,j:integer;
begin
  Result:=MaxInt;
  if length(s1)=1 then begin
    if (s1[1]>='R')and(s1[1]<='Z') then begin
      Result:=ord(s1[1]) - ord('R');                                          // R, S .. Z --> 0 .. 9
    end else
    if (s1[1]>='a')and(s1[1]<='z') then begin
      Result:=(ord(s1[1]) - ord('a'))*10 + 910000;                            // a, b .. z --> 910000 .. 910090
    end else
    if (s1[1]>='A')and(s1[1]<='Q') then begin
      Result:=(ord(s1[1]) - ord('A'))*10 + 920000;                            // A, B .. Q --> 920000 .. 920090
    end;
  end else
  if length(s1)=2 then begin
    if (s1[1]>='R')and(s1[1]<='Z')and(s1[2]>='R')and(s1[2]<='Z')and(s1[2]>=s1[1]) then begin
      i:=ord(s1[1]) - ord('R'); j:=ord(s1[2]) - ord(s1[1]);                   // RR, RS .. ZZ --> 10 .. 54
      Result:=((i*(19-i)) div 2) + j + 10;
    end else
    if (s1[1]>='A')and(s1[1]<='Q')and(s1[2]>='A')and(s1[2]<='Z')and(s1[2]>=s1[1])and(s1[1]<>'J')and(s1[2]<>'J') then begin
      i:=ord(s1[1]) - ord('A'); if s1[1]>'J' then dec(i);                     // AA, AB .. QZ --> 55 .. 334
      j:=ord(s1[2]) - ord(s1[1]); if s1[2]>'J' then dec(j);
      Result:=((i*(51-i)) div 2) + j + 55;
    end else
    if (s1[1]>='a')and(s1[1]<='z')and(s1[2]>='1')and(s1[2]<='9') then begin
      Result:=(ord(s1[1]) - ord('a'))*10 + (ord(s1[2]) - ord('0')) + 910000;  // a1, a2 .. z9 --> 910001 .. 910099
    end else
    if (s1[1]>='A')and(s1[1]<='Q')and(s1[2]>='1')and(s1[2]<='9') then begin
      Result:=(ord(s1[1]) - ord('A'))*10 + (ord(s1[2]) - ord('0')) + 920000;  // A1, A2 .. Z9 --> 920001 .. 920099
    end else
    if G_To_Byte(s1)>0 then begin
      Result:=(G_To_Byte(s1)*10) + 800000;                                    // Mu, Nu, Pi   --> 800010 .. 800240
    end;
  end else
  if length(s1)=3 then begin
    if G_To_Byte(s1)>0 then begin
      Result:=(G_To_Byte(s1)*10) + 800000;                                    // alf, bet .. zet  --> 800010 .. 800240
    end else
    if (G_To_Byte(copy(s1,1,2))>0)and(s1[3]>='1')and(s1[3]<='9') then begin
      Result:=(G_To_Byte(copy(s1,1,2))*10) + (ord(s1[3]) - ord('0')) + 800000;// mu1, mu2 .. pi9  --> 800011 .. 800249
    end;
  end else
  if length(s1)=4 then begin
    if (G_To_Byte(copy(s1,1,3))>0)and(s1[4]>='1')and(s1[4]<='9') then begin
      Result:=(G_To_Byte(copy(s1,1,3))*10) + (ord(s1[4]) - ord('0')) + 800000;// alf1, alf2 .. zet9  --> 800011 .. 800249
    end;
    if (S1[1]='V')and(TryStrToInt(copy(S1,2,Length(S1)-1),i))and(i>=335) then begin
      Result:=i;                                                              // V335 .. V999          --> 335 .. 999
    end;
  end;
  if (length(S1)>4) then begin
    if (S1[1]='V')and(length(S1)<=6)and(TryStrToInt(copy(S1,2,Length(S1)-1),i))and(i>=335) then begin
      Result:=i;                                                              // V0355 .. V99999       --> 335 .. 99999
    end;
  end;
end;

Function C_To_Byte(S1:String):integer;
begin
Result:=255;
if s1='And' then Result:=1;
if s1='Ant' then Result:=2;
if s1='Aps' then Result:=3;
if s1='Aqr' then Result:=4;
if s1='Aql' then Result:=5;
if s1='Ara' then Result:=6;
if s1='Ari' then Result:=7;
if s1='Aur' then Result:=8;
if s1='Boo' then Result:=9;
if s1='Cae' then Result:=10;
if s1='Cam' then Result:=11;
if s1='Cnc' then Result:=12;
if s1='CVn' then Result:=13;
if s1='CMa' then Result:=14;
if s1='CMi' then Result:=15;
if s1='Cap' then Result:=16;
if s1='Car' then Result:=17;
if s1='Cas' then Result:=18;
if s1='Cen' then Result:=19;
if s1='Cep' then Result:=20;
if s1='Cet' then Result:=21;
if s1='Cha' then Result:=22;
if s1='Cir' then Result:=23;
if s1='Col' then Result:=24;
if s1='Com' then Result:=25;
if s1='CrA' then Result:=26;
if s1='CrB' then Result:=27;
if s1='Crv' then Result:=28;
if s1='Crt' then Result:=29;
if s1='Cru' then Result:=30;
if s1='Cyg' then Result:=31;
if s1='Del' then Result:=32;
if s1='Dor' then Result:=33;
if s1='Dra' then Result:=34;
if s1='Equ' then Result:=35;
if s1='Eri' then Result:=36;
if s1='For' then Result:=37;
if s1='Gem' then Result:=38;
if s1='Gru' then Result:=39;
if s1='Her' then Result:=40;
if s1='Hor' then Result:=41;
if s1='Hya' then Result:=42;
if s1='Hyi' then Result:=43;
if s1='Ind' then Result:=44;
if s1='Lac' then Result:=45;
if s1='Leo' then Result:=46;
if s1='LMi' then Result:=47;
if s1='Lep' then Result:=48;
if s1='Lib' then Result:=49;
if s1='Lup' then Result:=50;
if s1='Lyn' then Result:=51;
if s1='Lyr' then Result:=52;
if s1='Men' then Result:=53;
if s1='Mic' then Result:=54;
if s1='Mon' then Result:=55;
if s1='Mus' then Result:=56;
if s1='Nor' then Result:=57;
if s1='Oct' then Result:=58;
if s1='Oph' then Result:=59;
if s1='Ori' then Result:=60;
if s1='Pav' then Result:=61;
if s1='Peg' then Result:=62;
if s1='Per' then Result:=63;
if s1='Phe' then Result:=64;
if s1='Pic' then Result:=65;
if s1='Psc' then Result:=66;
if s1='PsA' then Result:=67;
if s1='Pup' then Result:=68;
if s1='Pyx' then Result:=69;
if s1='Ret' then Result:=70;
if s1='Sge' then Result:=71;
if s1='Sgr' then Result:=72;
if s1='Sco' then Result:=73;
if s1='Scl' then Result:=74;
if s1='Sct' then Result:=75;
if s1='Ser' then Result:=76;
if s1='Sex' then Result:=77;
if s1='Tau' then Result:=78;
if s1='Tel' then Result:=79;
if s1='Tri' then Result:=80;
if s1='TrA' then Result:=81;
if s1='Tuc' then Result:=82;
if s1='UMa' then Result:=83;
if s1='UMi' then Result:=84;
if s1='Vel' then Result:=85;
if s1='Vir' then Result:=86;
if s1='Vol' then Result:=87;
if s1='Vul' then Result:=88;
end;

Function ConsCompare;
begin
 Result:=C_To_Byte(C1) - C_To_Byte(C2);
end;

Function NameCompare;
var i,C1,C2:integer; Aux1,Aux2:String; Sek1,Sek2:Boolean;
begin
 { Porovnej souhvezdi }
 C1:=C_To_Byte(NameToCons(S1));
 C2:=C_To_Byte(NameToCons(S2));
 Result:=C1 - C2;
 if Result=0 then begin
   { Odstran ze jmena oznaceni sekundarniho minima }
   i:=pos(':',S1);
   Sek1:=(i>0);
   if Sek1 then
     S1[i]:=' ';
   i:=pos(':',S2);
   Sek2:=(i>0);
   if Sek2 then
     S2[i]:=' ';
   { Porovnej jmeno - prvne zkusime standardizovane jmeno }
   if C1<>255 then Aux1:=copy(S1,1,Length(S1)-3) else Aux1:=S1;
   Aux1:=DelWS(Aux1);
   if C2<>255 then Aux2:=copy(S2,1,Length(S2)-3) else Aux2:=S2;
   Aux2:=DelWS(Aux2);
   Result:=P_To_Byte(Aux1) - P_To_Byte(Aux2);
   if (Result=0) then begin
     Result:=CompareStr(Aux1,Aux2);
   end;
   if Result=0 then begin
     { Primarni slozka prvni, sekundarni slozka druha }
     Result:=ord(Sek1)-ord(Sek2);
   end;
 end;
end;
    
Function StrToDec;
var Aux:String; H,M,S,Sgn:integer;
begin
 Aux:=Fetch(X,': .');
 H:=StrToIntDef(Aux,0);
 if H>=0 then Sgn:=1 else Sgn:=-1; H:=abs(H);
 Aux:=Fetch(X,': .');
 M:=StrToIntDef(Aux,0);
 S:=StrToIntDef(X,0);
 Result:=Sgn*(H*3600+M*60+S);
end;

Function DecToStr;
var H,M,S:word; X:integer;
begin
 X:=round(AX*3600);
 if X>=0 then begin
   H:=(X div 3600);
   M:=(X div 60) mod 60;
   S:=(X mod 60);
   Result:=Format('+%.2d:%.2d:%.2d',[H,M,S]);
 end else begin
   H:=(-X div 3600);
   M:=(-X div 60) mod 60;
   S:=(-X mod 60);
   Result:=Format('-%.2d:%.2d:%.2d',[H,M,S]);
 end;
end;

Function RaToStr;
var H,M,S:word; X:integer;
begin
 X:=round(AX*3600);
 H:=(X div 3600);
 M:=(X div 60) mod 60;
 S:=(X mod 60);
 Result:=Format('%.2d:%.2d:%.2d',[H,M,S]);
end;

Function RaToStr2;
var H,M:word; X:integer;
begin
 X:=round(AX*60);
 H:=(X div 60);
 M:=(X mod 60);
 Result:=Format('%d:%.2d',[H,M]);
end;

Function DecToStr2;
var H,M:word; X:integer;
begin
 X:=round(AX*60);
 if X>=0 then begin
   H:=(X div 60);
   M:=(X mod 60);
   Result:=Format('+%d:%.2d',[H,M]);
 end else begin
   H:=(-X div 60);
   M:=(-X mod 60);
   Result:=Format('-%d:%.2d',[H,M]);
 end;
end;

const
 LatinTo1250: array[#128..#255] of byte = (
  $c7,$fc,$e9,$e2,  $e4,$f9,$e6,$e7,  $b4,$eb,$d5,$f5,  $ee,$9f,$c4,$c6,
  $c9,$c5,$e5,$f4,  $f6,$bc,$be,$8c,  $9c,$d6,$dc,$8d,  $9d,$a4,$d7,$e8,
  $e1,$ed,$f3,$fa,  $a6,$b9,$8e,$9e,  $ca,$ea,$20,$9f,  $c8,$ba,$20,$20,
  $20,$20,$20,$20,  $20,$c1,$c2,$cc,  $aa,$20,$20,$20,  $20,$af,$bf,$20,

  $20,$20,$20,$20,  $20,$20,$c3,$e3,  $20,$20,$20,$20,  $20,$20,$20,$20,
  $f0,$d0,$cf,$cb,  $Ef,$d2,$cd,$ce,  $ec,$20,$20,$20,  $20,$de,$d9,$20,
  $d3,$df,$d4,$d1,  $f1,$f2,$8a,$9a,  $c0,$da,$e0,$db,  $fd,$dd,$fe,$20,
  $20,$20,$20,$20,  $20,$20,$20,$20,  $20,$20,$20,$fb,  $d8,$f8,$20,$20);

procedure LatinToWin(P:pointer; pocet: integer);
var i: integer;
begin
 for i:= 0 to Pocet - 1 do
   if (PByteArray(P)[i]>=128) then
     PByteArray(P)[i] := ord(LatinTo1250[char(PByteArray(P)[i])]);
end;

Function LatinToWin(S:String):String;
begin
 if Length(S)>0 then LatinToWin(@S[1],Length(S));
 Result:=S;
end;

Procedure ExecuteApp;
begin
 ShellExecute(0,'open',PChar(Path),PChar(Params),Nil,SW_SHOWDEFAULT);
end;

Function CheckFileName;
var i:integer; ch:char;
begin
 Result:='';
 for i:=1 to Length(S) do begin
   ch:=S[i];
   if (ch>=' ')and not (ch in ['/','\','*','?','"','<','>','|',':']) then
     Result:=Result+ch
   else
     Result:=Result+'_';
 end;
 Result:=trim(Result);
end;

Function AzToStr;
begin
 while (az<0) do az:=az+360; while (az>=360) do az:=az-360;
 if (az< 11.25) then Result:='N' else
 if (az< 33.75) then Result:='NNE' else
 if (az< 56.25) then Result:='NE' else
 if (az< 78.75) then Result:='ENE' else
 if (az<101.25) then Result:='E' else
 if (az<123.75) then Result:='ESE' else
 if (az<146.25) then Result:='SE' else
 if (az<168.75) then Result:='SSE' else
 if (az<191.25) then Result:='S' else
 if (az<213.75) then Result:='SSW' else
 if (az<236.25) then Result:='SW' else
 if (az<258.75) then Result:='WSW' else
 if (az<281.25) then Result:='W' else
 if (az<303.75) then Result:='WNW' else
 if (az<326.25) then Result:='NW' else
 if (az<348.75) then Result:='NNW' else
                     Result:='N';
end;

Function StrToAz;
var X:double;
begin
 if TryStrToFloat(S, X) then Result:=X
 else if SameText(S, 'N') then Result:=0
 else if SameText(S, 'NNE') then Result:=22.5
 else if SameText(S, 'NE') then Result:=45
 else if SameText(S, 'ENE') then Result:=67.5
 else if SameText(S, 'E') then Result:=90
 else if SameText(S, 'ESE') then Result:=112.5
 else if SameText(S, 'SE') then Result:=135
 else if SameText(S, 'SSE') then Result:=157.5
 else if SameText(S, 'S') then Result:=180
 else if SameText(S, 'SSW') then Result:=202.5
 else if SameText(S, 'SW') then Result:=225
 else if SameText(S, 'WSW') then Result:=247.5
 else if SameText(S, 'W') then Result:=270
 else if SameText(S, 'WNW') then Result:=292.5
 else if SameText(S, 'NW') then Result:=315
 else if SameText(S, 'NNW') then Result:=337.5
 else Result:=0;
end;

Function TzToStr;
begin
 if (Tz=0) then
   Result:='UTC+0'
 else if (Tz>0) then
   Result:=Format('UTC+%.02d:%.02d', [Tz div 60, Tz mod 60])
 else
   Result:=Format('UTC-%.02d:%.02d', [(-Tz) div 60, (-Tz) mod 60]);
end;

Function TryStrToTz;
var S:String;
    X, H, M:integer;
begin
 Result:=false;
 if Length(Str)>=3 then begin
   S:=Trim(Uppercase(Str));
   X:=pos('UTC', S);
   if (X=1) then begin
     S:=copy(S, 4, Length(S)-3);
     if (Length(S)=0) then begin
       AVal:=0;
       Result:=true;
     end else if (S[1]='+') or (S[1]='-') then begin
       X:=pos(':', S);
       if (X>0) then begin
         if TryStrToInt(copy(S, 2, X-2), H) and TryStrToInt(copy(S, X+1, Length(S)-X), M) then begin
           AVal:=ifthen(S[1]='-', -1, +1) * (H*60 + M);
           Result:=true;
         end;
       end else begin
         if TryStrToInt(copy(S, 2, X-2), H) then begin
           AVal:=ifthen(S[1]='-', -1, +1) * (H*60);
           Result:=true;
         end;
       end;
     end;
   end;
 end;
end;

Function StrToTz;
begin
 if not TryStrToTz(Str, Result) then
   raise Exception.Create('The string is not valid time zone.');
end;

Function DOWToStr;
var i:integer;
begin
 Result:='';
 for i:=1 to 7 do begin
   if DOW[i-1] then begin
      if Length(Result)>0 then
        Result:=Result+', ';
      Result:=Result+ShortDayNames[i];
   end;
 end;
end;

Function SystemTimeZone;
var tzinfo:TIME_ZONE_INFORMATION;
begin
  if GetTimeZoneInformation(tzinfo)<>0 then
    Result:=-(tzinfo.Bias + tzinfo.StandardBias)
  else
    Result:=0;
end;

Function ToLocalTime;
var Bias:double; UniversalTime,LocalTime:SYSTEMTIME;
begin
 if (TimeZoneX <= -1440) or (TimeZoneX >= 1440) then begin
   // Use Win API
   DateTimeToSystemTime(JDToDateTime(JD), UniversalTime);
   if SystemTimeToTzSpecificLocalTime(NIL, UniversalTime, LocalTime) then
     Result:=SystemTimeToDateTime(LocalTime)
   else
     Result:=JDToDateTime(JD);
 end
 else begin
   // Fixed bias
   Bias:=TimeZoneX/24.0/60.0;
   Result:=JDToDateTime(JD-bias);
 end;
end;

Procedure AdjustSystemTime(var t:SYSTEMTIME; bias:Integer);
begin
  if bias <> 0 then
      DateTimeToSystemTime(SystemTimeToDateTime(t)+(bias/1440.0),t);
end;

Function CompareSystemTimes(const t1:SYSTEMTIME; const t2:SYSTEMTIME):Integer;
var f1, f2:FILETIME;
begin
  SystemTimeToFileTime(t1, f1);
  SystemTimeToFileTime(t2, f2);
  Result:=CompareFileTime(f1, f2);
end;

// Convert UTC to local time without XP-specific Win32 functions
Function LocalTimeToSystemTime(const LocalTime:SYSTEMTIME; var UniversalTime:SYSTEMTIME):BOOL;
var TZ_INFO:TIME_ZONE_INFORMATION; aux:SYSTEMTIME;
begin
  GetTimeZoneInformation(TZ_INFO);
  // UTC = local time + bias
  if (TZ_INFO.StandardDate.wMonth <> 0) and (TZ_INFO.DaylightDate.wMonth <> 0) then begin
    // Daylight saving observed
    UniversalTime:=LocalTime;
    AdjustSystemTime(UniversalTime, TZ_INFO.Bias + TZ_INFO.StandardBias);
    if (not SystemTimeToTzSpecificLocalTime(@TZ_INFO,UniversalTime,aux)) or (CompareSystemTimes(aux,LocalTime) <> 0) then begin
      UniversalTime:=LocalTime;
      AdjustSystemTime(UniversalTime, TZ_INFO.Bias + TZ_INFO.DaylightBias);
    end;
  end else begin
    // No daylight saving
    UniversalTime := LocalTime;
    AdjustSystemTime(UniversalTime, TZ_INFO.Bias);
  end;
end;

Function FromLocalTime;
var Bias:double; UniversalTime,LocalTime:SYSTEMTIME;
begin
 if (TimeZoneX <= -1440) or (TimeZoneX >= 1440) then begin
   // Use Win API
   DateTimeToSystemTime(DT, LocalTime);
   if LocalTimeToSystemTime(LocalTime, UniversalTime) then
      Dt:=SystemTimeToDateTime(UniversalTime);
   Result:=DateTimeToJD(DT);
 end
 else begin
   // Fixed bias
   Bias:=TimeZoneX/24.0/60.0;
   Result:=DateTimeToJD(DT)+bias;
 end;
end;

Function LocalDateTimeToDOW;
var Y,M,D,DOW:word;
begin
 DecodeDateFully(DT, Y, M, D, DOW);
 Result:=DOW;
end;

end.

