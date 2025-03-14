unit Katalog;

(*
    Ephem 1.0
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

Uses Forms, Classes, SysUtils, Math, Utils;

type
     TKatZaznam = class(TObject)
       Constructor Create(ALine, AKatalog:String; AKIndex:integer);
       Function M0:double;
       Function Per:double;
       Function Mag1:double;
       Function Mag2:double;
       Function RA:double;
       Function DEC:double;
       Function Rating:integer;
       Function EclipseDepth:Double;
       Function Cons:String;
       Function ShrtName:String;
       Function LongName:String;
       Function MinTyp:String;
       Function VarTypShort:String;
       Function VarTypCaption:String;
       Function VarTypList:TStringList;
       Function Remarks:String;
       Function Katalog:String;
       Function KIndex:integer;
       Function RAStr:String;
       Function DecStr:String;
       Function M0Str:String;
       Function PerStr:String;
       Function MaxStr:String;
       Function PrimStr:String;
       Function SekStr:String;
       Function LDStr:String;
       Function SDStr:String;
       Function Source:String;
       Function Branch:String;
       Function Chart:String;
       Function Attractivity:String;
       Function GSC:String;
       Function Change:String;
       Function NObserv:String;
       Function NObserv10:String;
       Procedure GetInfo(L:TStrings);
     private
       FLine, FKatalog : String;
       FKIndex : integer;
     end;

     TKatalog = class(TObject)
       Data:TStringList;
       CatName, FileName, TempFile:String;
       Constructor Create;
       Destructor  Destroy; override;
       Procedure   Load(ACatName:String);
       Procedure   Clear;
       Function    Search(AName:String; out It):boolean;
       Function    CatList(L:TStrings; ASel:String=''):integer;
       Function    ConsList(L:TStrings; ASel:String=''):integer;
       Function    VarTypeList(L:TStrings; ASel:String=''):integer;
       Function    StarList(L:TStrings; ACon:String; ASel:String=''):integer;
     end;

implementation

(*
 BRKA 2005 Czech:
 NAZEV        TYP BODY RA2000   DE2000  M0          PER          MAX   PRIM  SEK   OB ZDROJ                 VD   MD   MAPA     ATRAKTIV   POZNAMKA        GSC         ZMENA
 RT And       09     1 231110.1 +530133 52186.5154  0.628933285  8.55  9.47  8.88  V  IBVS 5206;vyp         2.6  0.0  K1                                  03998.02167

 BRKA 2005 English:
 NAME         TYPE RATING RA2000   DE2000  M0          PER          MAX   PRIM  SEC   BRANCH LD   SD   SOURCE                CHART    ATRACTIV   NOTES           GSC         CHANGE
 RT And       09        1 231110.1 +530133 52186.5154  0.628933285  8.55  9.47  8.88  V      2.6  0.0  IBVS 5206;computed    K1                                  03998.02167

 var.astro.cz:
 CONS NAME             PS RATING RA2000   DE2000  M0           PER          MAX      PRIM     SEK      BRANCH LD   SD   GSC         TYPE         N10    N
 And  RT               p  1      231110.1 +530133 54722.3598   0.62892951   8.55     9.47     9.47     V      2.6  0.0  03998.02167 EA           176    1555
*)

Procedure Split(AStr:String; AList:TStrings);
var S:String; i,state:integer; ch:char;
begin
 S:='';
 State:=0;
 for i:=1 to Length(AStr) do begin
   ch:=AStr[i];
   case state of
     0: if ch>='A' then begin
          S:=ch;
          State:=1;
        end;
     1: if ch<'A' then begin
          AList.Add(S);
          S:='';
          State:=0;
        end else begin
          S:=S+ch;
        end;
   end;
 end;
 if Length(S)>0 then
   AList.Add(S);
end;

Constructor TKatalog.Create;
begin
 inherited;
 Data:=TStringList.Create;
end;

Destructor TKatalog.Destroy;
var i:integer;
begin
 with Data do for i:=0 to Count-1 do Objects[i].Free;
 Data.Free;
 inherited;
end;

Procedure TKatalog.Load;
{ Nacist udaje z katalogu }
var F:TextFile; It:TKatZaznam; line:String; index:integer;
begin
 if ACatName<>CatName then begin
   CatName :=AnsiUppercase(ACatName);
   FileName:=ExtractFilePath(paramstr(0))+CatName+'.dat';
   TempFile:=ExtractFilePath(paramstr(0))+CatName+'.$$$';
   if FileExists(FileName) then begin
     { Nacist data ze souboru }
     AssignFile(F,FileName);
     reset(F);
     index:=0;
     while not eof(f) do begin
       readln(F,line);
       inc(index);
       It:=TKatZaznam.Create(line, CatName, index);
       if (Length(It.Katalog)>0) and (Length(It.LongName)>0) and (It.M0>0) and (It.Per>0)
         and SameText(It.MinTyp,'P') or SameText(It.MinTyp,'S') then
         Data.AddObject(It.LongName, It)
       else
         It.Free;
     end;
     CloseFile(f);
   end;
 end;
end;

Constructor TKatZaznam.Create;
begin
 inherited Create;
 FLine:=ALine;
 FKatalog:=AKatalog;
 if (copy(Fline,1,1)=' ') and (copy(FLine,30,1)='.') and ((copy(FLine,33,1)='+') or (copy(FLine,33,1)='-')) then begin
   // BRKA 2005 czech format
   if copy(FLine,15,1)='H' then FKatalog:=FKatalog+' (H)';
   if copy(FLine,15,1)='C' then FKatalog:=FKatalog+' (C)';
 end;
 if (copy(FLine,1,1)=' ') and (copy(FLine,33,1)='.') and ((copy(FLine,36,1)='+') or (copy(FLine,36,1)='-')) then begin
   // BRKA 2005 english format
   if copy(FLine,15,1)='H' then FKatalog:=FKatalog+' (H)';
   if copy(FLine,15,1)='C' then FKatalog:=FKatalog+' (C)';
 end;
end;

Function TKatZaznam.Katalog;
begin
 Result:=FKatalog;
end;

Function TKatZaznam.KIndex;
begin
 Result:=FKIndex;
end;

Function TKatZaznam.M0Str;
begin
 if (copy(FLine,30,1)='.') then
   Result :=trim(copy(FLine,41,12))
 else if (copy(FLine,33,1)='.') then
   Result :=trim(copy(FLine,44,12))
 else if (copy(FLine,40,1)='.') then
   Result :=trim(copy(FLine,51,12))
 else
   Result:='';
end;

Function TKatZaznam.M0;
begin
 Result:=StrToFloatDef(CheckDec(M0Str), 0);
 if Result<2400000 then
   Result:=Result+2400000;
end;

Function TKatZaznam.PerStr;
begin
 if (copy(FLine,30,1)='.') then
   Result:=trim(copy(FLine,53,12))
 else if (copy(FLine,33,1)='.') then
   Result:=trim(copy(FLine,56,12))
 else if (copy(FLine,40,1)='.') then
   Result:=trim(copy(FLine,64,12))
 else
   Result:='';
end;

Function TKatZaznam.Per;
begin
 Result:=StrToFloatDef(CheckDec(PerStr), 0);
end;

Function TKatZaznam.MaxStr;
begin
 if (copy(FLine,30,1)='.') then
   Result:=trim(copy(FLine,66,5))
 else if (copy(FLine,33,1)='.') then
   Result:=trim(copy(FLine,69,5))
 else if (copy(FLine,40,1)='.') then
   Result:=trim(copy(FLine,77,8))
 else
   Result:= '';
end;

Function TKatZaznam.Mag1;
begin
 Result:=StrToFloatDef(CheckDec(MaxStr),-99);
end;

Function TKatZaznam.PrimStr;
begin
 if (copy(FLine,30,1)='.') then begin
   Result:=trim(copy(FLine,72,6))
 end else if (copy(FLine,33,1)='.') then begin
   Result:=trim(copy(FLine,75,6))
 end else if (copy(FLine,40,1)='.') then begin
   Result:=trim(copy(FLine,86,8))
 end else
   Result:= '';
end;

Function TKatZaznam.SekStr;
begin
 if (copy(FLine,30,1)='.') then begin
   Result:=trim(copy(FLine,78,6));
 end else if (copy(FLine,33,1)='.') then begin
   Result:=trim(copy(FLine,81,6));
 end else if (copy(FLine,40,1)='.') then begin
   Result:=trim(copy(FLine,95,8))
 end else
   Result:='';
end;

Function TKatZaznam.MinTyp;
begin
 if (copy(FLine,30,1)='.') or (copy(FLine,33,1)='.') then begin
   if (pos(':',copy(FLine,2,12))=0) then
     Result:='P'
   else
     Result:='S';
 end else if (copy(FLine,40,1)='.') then begin
   Result:=trim(copy(FLine,24,2));
 end else
   Result:='';
end;

Function TKatZaznam.Mag2;
begin
 if (copy(FLine,30,1)='.') or (copy(FLine,33,1)='.') then begin
   if (pos(':',copy(FLine,2,12))=0) then
     Result:=StrToFloatDef(CheckDec(PrimStr),-99)
   else
     Result:=StrToFloatDef(CheckDec(SekStr),-99);
 end else if (copy(FLine,40,1)='.') then begin
   if (trim(copy(FLine,24,2))='p') then
     Result:=StrToFloatDef(CheckDec(PrimStr),-99)
   else if (trim(copy(FLine,24,2))='s') then
     Result:=StrToFloatDef(CheckDec(SekStr),-99)
   else
     Result:=-99;
 end else
   Result:=-99;
end;

Function TKatZaznam.RAStr;
begin
 if (copy(FLine,30,1)='.') then
   Result:=trim(copy(FLine,24,8))
 else if (copy(FLine,33,1)='.') then
   Result:=trim(copy(FLine,27,8))
 else if (copy(FLine,40,1)='.') then
   Result:=trim(copy(FLine,34,8))
 else
   Result:= '';
end;

Function TKatZaznam.RA;
var Aux:String; H,M,S:double;
begin
 Aux:=RAStr;
 H:=StrToIntDef(copy(Aux,1,2),0);
 M:=StrToIntDef(copy(Aux,3,2),0);
 S:=StrToIntDef(copy(Aux,5,2),0);
 Result:=H+M/60+S/3600;
end;

Function TKatZaznam.DecStr;
begin
 if (copy(FLine,30,1)='.') then
   Result:=trim(copy(FLine,33,7))
 else if (copy(FLine,33,1)='.') then
   Result:=trim(copy(FLine,36,7))
 else if (copy(FLine,40,1)='.') then
   Result:=trim(copy(FLine,43,7))
 else
   Result:= '';
end;

Function TKatZaznam.Dec;
var Aux:String; H,M,S,Sgn:double;
begin
 Aux:=DecStr;
 if copy(Aux,1,1)='-' then Sgn:=-1 else Sgn:=1;
 H:=StrToIntDef(copy(Aux,2,2),0);
 M:=StrToIntDef(copy(Aux,4,2),0);
 S:=StrToIntDef(copy(Aux,6,2),0);
 Result:=Sgn*(H+M/60+S/3600);
end;

Function TKatZaznam.Rating;
var Aux:String;
begin
 if (copy(FLine,30,1)='.') then
   Aux :=trim(copy(FLine,19,4))
 else if (copy(FLine,33,1)='.') then
   Aux :=trim(copy(FLine,20,6))
 else if (copy(FLine,40,1)='.') then
   Aux :=trim(copy(FLine,27,6))
 else
   Aux := '';
 Result:=StrToIntDef(Aux,10);
end;

Function TKatZaznam.EclipseDepth:Double;
var M1, M2:Double;
begin
 M1:=Mag1;
 M2:=Mag2;
 if (M1>-99)and(M2>-99)and(M2>=M1) then
   Result:=M2-M1
 else
   Result:=-99;
end;

Function TKatZaznam.VarTypShort;
var Aux1:String;
begin
 Result:='';
 if (copy(FLine,30,1)='.') or (copy(FLine,33,1)='.') then begin
   if (copy(FLine,30,1)='.') then begin
     // BRKA 2005 Czech format
     Aux1 :=trim(copy(FLine,109,4));
   end else begin
     // BRKA 2005 English format
     Aux1 :=trim(copy(FLine,94,4));
   end;
   if Length(Aux1)>0 then begin
     if (pos('W',Aux1)=1) or (pos('EW',Aux1)=1) then
       Result:='EW'
     else if (pos('B',Aux1)=1) or (pos('EB',Aux1)=1) then
       Result:='EB'
     else
       Result:='EA'
   end;
 end else if (copy(FLine,40,1)='.') then begin
   // BRNO, Prosper, user-defined catalog files
   Aux1:=trim(copy(FLine,133,12));
   if (Length(Aux1)>0) and (Aux1[1]>='A') then
     Result:=Aux1;   // Typ
 end;
end;

Function TKatZaznam.VarTypList;
var Aux1:String;
begin
 Result:=TStringList.Create;
 if (copy(FLine,30,1)='.') or (copy(FLine,33,1)='.') then begin
   if (copy(FLine,30,1)='.') then begin
     // BRKA 2005 Czech format
     Aux1 :=trim(copy(FLine,109,4));
   end else begin
     // BRKA 2005 English format
     Aux1 :=trim(copy(FLine,94,4));
   end;
   if Length(Aux1)>0 then begin
     if (pos('W',Aux1)=1) or (pos('EW',Aux1)=1) then
       Result.Add('EW')
     else if (pos('B',Aux1)=1) or (pos('EB',Aux1)=1) then
       Result.Add('EB')
     else
       Result.Add('EA')
   end;
 end else if (copy(FLine,40,1)='.') then begin
   // BRNO, Prosper, user-defined catalog files
   Aux1:=trim(copy(FLine,133,12));
   if (Length(Aux1)>0) and (Aux1[1]>='A') then
     Split(Aux1,Result);
 end;
end;

Function TKatZaznam.VarTypCaption;
var Aux1,Aux2:String;
begin
 Result:='';
 if (copy(FLine,30,1)='.') or (copy(FLine,33,1)='.') then begin
   if (copy(FLine,30,1)='.') then begin
     // BRKA 2005 Czech format
     Aux1 :=trim(copy(FLine,109,4));
   end else begin
     // BRKA 2005 English format
     Aux1 :=trim(copy(FLine,94,4));
   end;
   if Length(Aux1)>0 then begin
     if (pos('W',Aux1)=1) or (pos('EW',Aux1)=1) then
       Result:='EW P='+Format('%.1f d',[Per])
     else if (pos('B',Aux1)=1) or (pos('EB',Aux1)=1) then
       Result:='EB P='+Format('%.1f d',[Per])
     else
       Result:='EA D='+Format('%s h',[Aux1])
   end;
 end else if (copy(FLine,40,1)='.') then begin
   // BRNO, Prosper, user-defined catalog files
   Aux1 :=trim(copy(FLine,133,12));   // Typ
   Aux2 :=trim(copy(FLine,111,4));    // LD
   if Length(Aux1)>0 then begin
     if (pos('EA',Aux1)>0) then begin
       // Print D for Algolids
       if (Length(Aux2)>0) then
         Result:=Format('%s D=%s h',[Aux1,Aux2])
       else
         Result:=Aux1;
     end else
       // Print P for all other types
       if (Per<9.95) then
         Result:=Format('%s P=%.1f d',[Aux1,Per])
       else
         Result:=Format('%s P=%.0f d',[Aux1,Per]);
   end;
 end;
end;

Function TKatZaznam.ShrtName;
begin
 Result:= '';
 if (copy(FLine,30,1)='.') or (copy(FLine,33,1)='.') then begin
   Result:=trim(copy(FLine,2,12));
   if (Length(Result)>=5) and ((Result[Length(Result)-3]=' ')or(Result[Length(Result)-3]=':')) then begin
     if C_To_Byte(copy(Result,Length(Result)-2,3))<>255 then
       Result:=trim(copy(Result,1,Length(Result)-3));
     if (Result[Length(Result)]=':') then
       Result:=trim(copy(Result,1,Length(Result)-1));
   end;
 end else if (copy(FLine,40,1)='.') and ((trim(copy(FLine,24,2))='p')or(trim(copy(FLine,24,2))='s')) then begin
   Result:=trim(copy(FLine,7,16))
 end;
end;

Function TKatZaznam.LongName;
begin
 Result:= '';
 if (copy(FLine,30,1)='.') or (copy(FLine,33,1)='.') then
   Result:=trim(copy(FLine,2,12))
 else if (copy(FLine,40,1)='.') and (trim(copy(FLine,24,2))='p') then
   Result:=trim(copy(FLine,7,16))+' '+trim(copy(FLine,2,4))
 else if (copy(FLine,40,1)='.') and (trim(copy(FLine,24,2))='s') then
   Result:=trim(copy(FLine,7,16))+':'+trim(copy(FLine,2,4))
end;

Function TKatZaznam.Cons;
var Aux:String;
begin
 Result:='OTHER';
 if (copy(FLine,30,1)='.') or (copy(FLine,33,1)='.') then begin
   Aux:=trim(copy(FLine,2,12));
   if (Length(Aux)>=5) and ((Aux[Length(Aux)-3]=' ')or(Aux[Length(Aux)-3]=':')) then begin
     if C_To_Byte(copy(Aux,Length(Aux)-2,3))<>255 then
       Result:=copy(Aux,Length(Aux)-2,3)
   end;
 end else if (copy(FLine,40,1)='.') then begin
   if C_To_Byte(copy(FLine,2,3))<>255 then
     Result:=copy(FLine,2,3);
 end;
end;

Function TKatZaznam.Remarks;
var Aux:String;
begin
 if (copy(FLine,30,1)='.') then
   Aux :=LatinToWin(trim(copy(FLine,139,15)))
 else if (copy(FLine,33,1)='.') then
   Aux :=trim(copy(FLine,146,15))
 else
   Aux := '';
 Result:=Aux;
end;

Function TKatZaznam.LDStr;
begin
 if (copy(FLine,30,1)='.') then
   Result:=trim(copy(FLine,109,4))
 else if (copy(FLine,33,1)='.') then
   Result:=trim(copy(FLine,94,4))
 else if (copy(FLine,40,1)='.') then
   Result:=trim(copy(FLine,111,4))
 else
   Result:= '';
end;

Function TKatZaznam.SDStr;
begin
 if (copy(FLine,30,1)='.') then
   Result:=trim(copy(FLine,114,4))
 else if (copy(FLine,33,1)='.') then
   Result:=trim(copy(FLine,99,4))
 else if (copy(FLine,40,1)='.') then
   Result:=trim(copy(FLine,116,4))
 else
   Result:= '';
end;

Function TKatZaznam.Source;
begin
 if (copy(FLine,30,1)='.') then
   Result:=trim(copy(FLine,87,21))
 else if (copy(FLine,33,1)='.') then
   Result:=trim(copy(FLine,104,21))
 else
   Result:= '';
end;

Function TKatZaznam.Branch;
begin
 if (copy(FLine,30,1)='.') then
   Result:=trim(copy(FLine,84,2))
 else if (copy(FLine,33,1)='.') then
   Result:=trim(copy(FLine,87,6))
 else if (copy(FLine,40,1)='.') then
   Result:=trim(copy(FLine,104,6))
 else
   Result:= '';
end;

Function TKatZaznam.Chart;
begin
 if (copy(FLine,30,1)='.') then
   Result:=trim(copy(FLine,119,4))
 else if (copy(FLine,33,1)='.') then
   Result:=trim(copy(FLine,126,8))
 else
   Result:= '';
end;

Function TKatZaznam.Attractivity;
begin
 if (copy(FLine,30,1)='.') then
   Result:=trim(copy(FLine,128,10))
 else if (copy(FLine,33,1)='.') then
   Result:=trim(copy(FLine,135,10))
 else
   Result:= '';
end;

Function TKatZaznam.GSC;
begin
 if (copy(FLine,30,1)='.') then
   Result:=trim(copy(FLine,155,11))
 else if (copy(FLine,33,1)='.') then
   Result:=trim(copy(FLine,162,11))
 else if (copy(FLine,40,1)='.') then
   Result:=trim(copy(FLine,121,11))
 else
   Result:= '';
end;

Function TKatZaznam.Change;
begin
 if (copy(FLine,30,1)='.') then
   Result:=trim(copy(FLine,167,5))
 else if (copy(FLine,33,1)='.') then
   Result:=trim(copy(FLine,174,6))
 else
   Result:= '';
end;

Function TKatZaznam.NObserv;
begin
 if (copy(FLine,40,1)='.') then
   Result:=trim(copy(FLine,153,6))
 else
   Result:='';
end;

Function TKatZaznam.NObserv10;
begin
 if (copy(FLine,40,1)='.') then
   Result:=trim(copy(FLine,146,6))
 else
   Result:='';
end;

Procedure TKatalog.Clear;
{ Vymazat stavajici data }
var i:integer;
begin
 CatName :='';
 FileName:='';
 TempFile:='';
 with Data do for i:=0 to Count-1 do Objects[i].Free;
 Data.Clear;
end;

function CustomSortByCons(List: TStringList; Index1, Index2: Integer):Integer;
{ Porovnani souhvezdi - aby se souhvezdi radila ve spravnem poradi }
begin
 Result:=ConsCompare(List[Index1],List[Index2]);
end;

function CustomSortByName(List: TStringList; Index1, Index2: Integer):Integer;
{ Porovnani jmen promennych - aby se promenne radily ve spravnem poradi }
begin
 Result:=NameCompare(List[Index1],List[Index2]);
end;

Function TKatalog.ConsList;
{ Vraci seznam souhvezdi }
var i:integer; other:boolean; C:String; List:TStringList;
begin
 List:=TStringList.Create;
 try
   other:=false;
   for i:=0 to Data.Count-1 do begin
     C:=TKatZaznam(Data.Objects[i]).Cons;
     if (C_To_Byte(C)<>255) and (List.IndexOf(C)<0) then List.Add(C);
     other:=other or (C_To_Byte(C)=255);
   end;
   List.CustomSort(CustomSortByCons);
   Result:=List.IndexOf(ASel);
   if (Data.Count>0) and other then begin
     i:=List.Add('OTHER');
     if (Length(ASel)>0)and(Result<0) then Result:=i;
   end;
   L.BeginUpdate;
   L.Clear;
   L.AddStrings(List);
   L.EndUpdate;
 finally
   List.Free;
 end;
end;

Function TKatalog.VarTypeList;
{ Vraci seznam typu promennosti }
var i,j:integer; unknown:boolean; C,List:TStringList;
begin
 List:=TStringList.Create;
 try
   unknown:=false;
   for i:=0 to Data.Count-1 do begin
     C:=TKatZaznam(Data.Objects[i]).VarTypList;
     if C.Count=0 then
       unknown:=true
     else for j:=0 to C.Count-1 do
       if List.IndexOf(C[j])<0 then List.Add(C[j]);
     C.Free;
   end;
   List.Sort;
   Result:=List.IndexOf(ASel);
   if (Data.Count>0) and unknown then begin
     i:=List.Add('Unknown');
     if (Length(ASel)=0)and(Result<0) then Result:=i;
   end;
   L.BeginUpdate;
   L.Clear;
   L.AddStrings(List);
   L.EndUpdate;
 finally
   List.Free;
 end;
end;

Function TKatalog.StarList;
{ Vraci seznam hvezd v danem souhvezdi }
var i,Index,c:integer; J1,S,J:String; Sek,S1:boolean; List:TStringList;
begin
 Result:=-1;
 Sek:=pos(':',ASel)>0;
 if (Length(ASel)>=5)and((ASel[Length(ASel)-3]=' ')or(ASel[Length(ASel)-3]=':')) then
   J:=DelWS(copy(ASel,1,Length(ASel)-4))
 else
   J:=DelWS(ASel);
 C:=C_To_Byte(ACon);
 List:=TStringList.Create;
 try
   for i:=0 to Data.Count-1 do begin
     S:=Data[i];
     if C_To_Byte(NameToCons(S))=C then
       List.Add(S);
   end;
   List.CustomSort(CustomSortByName);
   L.BeginUpdate;
   try
     L.Clear;
     for i:=0 to List.Count-1 do begin
       S:=List[i];
       if (C<>255) then
         J1:=DelWS(copy(S,1,Length(S)-4))
       else
         J1:=DelWS(S);
       Index:=L.Add(S);
       S1:=pos(':',S)>0;
       if (J1=J)and(S1=Sek) then Result:=Index;
     end;
   finally
     L.EndUpdate;
   end;
 finally
   List.Free;
 end;
end;

Function TKatalog.CatList;
{ Seznam dostupnych katalogu }
var Res:integer; F:TSearchRec; C:String;
begin
 L.BeginUpdate;
 L.Clear;
 try
   Res:=FindFirst('*.dat',faAnyFile,F);
   while (Res=0) do begin
     C:=ExtractFileName(F.Name);
     L.Add(AnsiUppercase(copy(C,1,Length(C)-4)));
     Res:=FindNext(F);
   end;
 finally
   L.EndUpdate;
   FindClose(F);
 end;
 Result:=L.IndexOf(ASel);
end;

Function TKatalog.Search;
var Index:integer;
begin
 Index:=Data.IndexOf(AName);
 if Index>=0 then begin
   TObject(It):=Data.Objects[Index];
   Result:=true;
 end else begin
   TObject(It):=NIL;
   Result:=false;
 end;
end;

Procedure TKatZaznam.GetInfo;
begin
 L.BeginUpdate;
 L.Clear;
 L.Add('Name='+LongName);
 L.Add('Type='+VarTypShort);
 L.Add('Rating='+IntToStr(Rating));
 L.Add('N='+NObserv);
 L.Add('N10='+NObserv10);
 L.Add('RA2000='+RAStr);
 L.Add('DEC2000='+DecStr);
 L.Add('M0='+M0Str);
 L.Add('PER='+PerStr);
 L.Add('Max.='+MaxStr);
 L.Add('Prim.='+PrimStr);
 L.Add('Sec.='+SekStr);
 L.Add('Branch='+Branch);
 L.Add('LD='+LDStr);
 L.Add('SD='+SDStr);
 L.Add('Source='+Source);
 L.Add('Chart='+Chart);
 L.Add('Attr.='+Attractivity);
 L.Add('Remarks='+Remarks);
 L.Add('GSC='+GSC);
 L.Add('Change='+Change);
 L.EndUpdate;
end;

end.
