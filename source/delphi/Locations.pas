unit Locations;

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

Uses SysUtils, Classes, Math;

type
     TLocation = class(TObject)
      private
       FLon, FLat:double;
       FBias:integer;
       Procedure SetLon(Value:double);
       Procedure SetLat(Value:double);
      public
       property Lon:double read FLon write SetLon;
       property Lat:double read FLat write SetLat;
       property Bias:integer read FBias write FBias;
     end;

     TLocations = class(TObject)
       Data:TStringList;
       Constructor Create;
       Destructor  Destroy; override;
       Procedure   Clear;
       Procedure   Load(AFileName:String);
       Procedure   Save(AFileName:String);
       Function    MakeList(L:TStrings; ASel:String=''):integer;
       Procedure   Add(Name:String; Lon, Lat:double);
       Procedure   Delete(Name:String);
       Procedure   Rename(OldName, NewName:String);
       Function    GetData(AName:String):TLocation;
       Function    Exists(AName:String):boolean;
     private
       Function    QuoteString(Str:String):String;
       Function    GetPart(Line:String; Part:integer):String;
     end;

implementation

Procedure TLocation.SetLon(Value:double);
begin
 Value:=Value/360.0+0.5;
 FLon:=360.0*(Value-floor(Value)-0.5);
end;

Procedure TLocation.SetLat(Value:double);
begin
  if (Value > 90) then
    FLat:=90
  else if (Value < -90) then
    FLat:=-90
  else
    FLat:=Value;
end;

Constructor TLocations.Create;
begin
 inherited;
 Data:=TStringList.Create;
end;

Destructor TLocations.Destroy;
var i:integer;
begin
 with Data do for i:=0 to Count-1 do Objects[i].Free;
 Data.Free;
 inherited;
end;

Procedure TLocations.Load;
{ Nacist udaje z katalogu }
var F:TextFile; It:TLocation; Lon, Lat, Bias, Line, Name:String;
begin
 Clear;
 if FileExists(AFileName) then begin
   { Nacist data ze souboru }
   AssignFile(F,AFileName);
   reset(F);
   while not eof(f) do begin
     readln(F,line);
     Name:=GetPart(line, 1);
     Lon:=GetPart(line, 2);
     Lat:=GetPart(line, 3);
     Bias:=GetPart(line, 4);
     if (Name<>'') and (Name<>'NAME') then begin
       It := TLocation.Create;
       It.Lon := StrToFloatDef(Lon, 0);
       It.Lat := StrToFloatDef(Lat, 0);
       It.Bias:= StrToIntDef(Bias, 9999);
       Data.AddObject(Name,It);
     end;
   end;
   CloseFile(f);
   Data.Sort;
 end;
end;

Procedure TLocations.Save;
{ Ulozit udaje do katalogu pozic }
var F:TextFile; i:integer; It:TLocation; line,ext,bakfile:String;
begin
 if AFileName<>'' then begin
   { Smazat puvodni soubor }
   Ext:=ExtractFileExt(AFileName);
   BakFile:=copy(AFileName, 1, Length(AFileName)-Length(Ext)) + '.old';
   if FileExists(BakFile) then
     DeleteFile(BakFile);
   if FileExists(AFileName) then
     RenameFile(AFileName, BakFile);
   { Ulozit data ze souboru }
   AssignFile(F,AFileName);
   rewrite(F);
   writeln(F, 'NAME, LONGITUDE, LATITUDE');
   for i:=0 to Data.Count-1 do begin
     It:=TLocation(Data.Objects[i]);
     if It.Bias=9999 then
       Line:=Format('%s, %.5f, %.3f', [QuoteString(Data[i]), It.Lon, It.Lat])
     else
       Line:=Format('%s, %.5f, %.3f, %d', [QuoteString(Data[i]), It.Lon, It.Lat, It.Bias]);
     writeln(F,line);
   end;
   CloseFile(f);
 end;
end;

Procedure TLocations.Clear;
{ Vymazat stavajici data }
var i:integer;
begin
 with Data do for i:=0 to Count-1 do Objects[i].Free;
 Data.Clear;
end;

Function TLocations.MakeList;
var i:integer;
begin
 L.BeginUpdate;
 L.Clear;
 try
   for i:=0 to Data.Count-1 do
     L.AddObject(Data[i], Data.Objects[i]);
 finally
   L.EndUpdate;
 end;
 Result:=L.IndexOf(ASel);
end;

Function TLocations.QuoteString;
var ch:char; i:integer;
begin
  Result:='"';
  for i:=1 to Length(Str) do begin
    ch:=Str[i];
    if (Str[i]='"') then
      Result:=Result+'\"'
    else if (Str[i]='\') then
      Result:=Result+'\\'
    else
      Result:=Result+ch;
  end;
  Result:=Result+'"';
end;

Function TLocations.GetPart;
var ch:char; i,j,state:integer;
begin
 state:=0; j:=1; Result:='';
 for i:=1 to Length(Line) do begin
   ch:=Line[i];
   case state of
   0: begin
        if (ch='"') then
          state:=1
        else if (ch>=' ') then begin
          if (Part=j) then
            Result:=ch;
          state:=4;
        end;  
      end;
   1: begin
        if (ch='\') then
          state:=2
        else if (ch='"') then
          state:=3
        else begin
          if (Part=j) then
            Result:=Result+ch;
        end;
      end;
   2: begin
        if (Part=j) then
          Result:=Result+ch;
        state:=1;
      end;
   3: begin
        if (ch=',') then begin
          j:=j+1;
          state:=0;
        end;
      end;
   4: begin
       if (ch=',') then begin
         j:=j+1;
         state:=0;
       end else begin
         if (Part=j) then
           Result:=Result+ch;
       end;
     end;
   end;
   if (j>Part) then
     break;
 end;
end;

Procedure TLocations.Add;
var It:TLocation;
begin
  if (Name<>'') then begin
    It:=TLocation.Create;
    It.Lon:=Lon;
    It.Lat:=Lat;
    Data.AddObject(Name, It);
    Data.Sort;
  end;
end;

Procedure TLocations.Delete;
var It:TLocation; i:integer;
begin
  for i:=0 to Data.Count-1 do begin
    if (Data[i]=Name) then begin
      It:=TLocation(Data.Objects[i]);
      Data.Delete(i);
      It.Free;
      break;
    end;
  end;
end;

Procedure TLocations.Rename;
var i:integer;
begin
 if (NewName<>'') then begin
   for i:=0 to Data.Count-1 do begin
     if (Data[i]=OldName) then begin
       Data[i]:=NewName;
       break;
     end;
   end;
   Data.Sort;
 end;
end;

Function TLocations.GetData;
var i:integer;
begin
 Result:=NIL;
 for i:=0 to Data.Count-1 do begin
   if (Data[i]=AName) then begin
     Result:=TLocation(Data.Objects[i]);
     break;
   end;
 end;
end;

Function TLocations.Exists;
begin
 Result:=Data.IndexOf(AName)>=0;
end;

end.
