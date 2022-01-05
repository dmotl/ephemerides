unit DMoon;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Planety, Juldat, Efemer, ExtCtrls, Math;

type
  TMoonDlg = class(TForm)
    Button1: TButton;
    PaintBox1: TPaintBox;
    Label1: TLabel;
    Label2: TLabel;
    MoonRise: TLabel;
    MoonSet: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    FQ: TLabel;
    NM: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    LQ: TLabel;
    FM: TLabel;
    Label5: TLabel;
    MoonA: TLabel;
    Label9: TLabel;
    MoonD: TLabel;
    Label6: TLabel;
    MoonP: TLabel;
    Label10: TLabel;
    MoonI: TLabel;
    procedure PaintBox1Paint(Sender: TObject);
  private
    Phase:double;
  public
    Procedure Execute(JD,Lon,Lat:double; TimeZoneX:integer);
  end;

var
  MoonDlg: TMoonDlg;

Procedure MoonRaDecPhase(JD:double; var RA,Dec,Phase:double);
Procedure MoonRiseSet(JD,Lon,Lat:double; TimeZoneX:integer; var TRise,TSet:double);
Function MoonPhase(JD:double):double;
Function FormatLunarPhase(Phase:double):String;
Function FormatLunarIllumination(Phase:double):String;

implementation

Uses Utils;

{$R *.dfm}

Procedure MoonRaDecPhase(JD:double; var RA,Dec,Phase:double);
var Pl:TPlanets;
begin
 Pl:=TPlanets.Create;
 with Pl do try
   SetJD(JD);
   RA:=alfam/pi*12;
   Dec:=deltam/pi*180;
   Phase:=phasem;
 finally
   Pl.Free;
 end;
end;

Function MoonPhase;
var Pl:TPlanets;
begin
 Pl:=TPlanets.Create;
 with Pl do try
   SetJD(JD);
   Result:=phasem;
 finally
   Pl.Free;
 end;
end;

Procedure MoonRiseSet(JD,Lon,Lat:double; TimeZoneX:integer; var TRise,TSet:double);
var Ra,Dec,Phase,JD1,JD2:double; cond:RiseSetCond;
begin
 JD:=FromLocalTime(floor(ToLocalTime(JD,TimeZoneX))+0.5,TimeZoneX);
 MoonRaDecPhase(JD,RA,Dec,Phase);
 JD1:=RaDeToRise(RA,Dec,jd,lon,lat,0,rtNearest,cond);
 if JD1 > 0 then begin
   MoonRaDecPhase(JD1,RA,Dec,Phase);
   JD2:=RaDeToRise(RA,Dec,JD1,lon,lat,0,rtNearest,cond);
   if JD2 > 0 then begin
     MoonRaDecPhase(JD2,RA,Dec,Phase);
     trise:=RaDeToRise(RA,Dec,JD2,lon,lat,0,rtNearest,cond);
   end else
     trise:=0;
 end else
   trise:=0;
 MoonRaDecPhase(JD,RA,Dec,Phase);
 JD1:=RaDeToSet(Ra,Dec,jd,lon,lat,0,rtNearest,cond);
 if JD1 > 0 then begin
   MoonRaDecPhase(JD1,RA,Dec,Phase);
   JD2:=RaDeToSet(Ra,Dec,JD1,lon,lat,0,rtNearest,cond);
   if JD2 > 0 then begin
     MoonRaDecPhase(JD2,RA,Dec,Phase);
     tset:=RaDeToSet(RA,Dec,JD2,lon,lat,0,rtNearest,cond);
   end else
     tset:=0;
 end else
   tset:=0;
end;

Function FormatLunarPhase;
var age:integer;
begin
 Age:=round(Phase*29.531/360.0);
 if (Phase < 18.0) or (Phase > 360.0 - 18.0) then begin
   if Age=1 then
     Result:=Format('%d day (%s)', [Age, 'new moon'])
   else
     Result:=Format('%d days (%s)', [Age, 'new moon']);
 end else if (Phase < 90.0 - 12.0) then
   Result:=Format('%d days (%s)', [Age, 'waxing crescent'])
 else if (Phase < 90.0 + 12.0) then
   Result:=Format('%d days (%s)', [Age, 'first quarter'])
 else if (Phase < 180.0 - 18.0) then
   Result:=Format('%d days (%s)', [Age, 'waxing gibbous'])
 else if (Phase < 180.0 + 18.0) then
   Result:=Format('%d days (%s)', [Age, 'full moon'])
 else if (Phase < 270.0 - 12.0) then
   Result:=Format('%d days (%s)', [Age, 'waning gibbous'])
 else if (Phase < 270.0 + 12.0) then
   Result:=Format('%d days (%s)', [Age, 'third quarter'])
 else
   Result:=Format('%d days (%s)', [Age, 'waning crescent']);
end;

Function FormatLunarIllumination(Phase:double):String;
var illum:double;
begin
 illum:=0.5*(1.0-cos(Phase/180*pi))*100.0;
 if (Phase < 180.0) then
   Result:=Format('%.0f%% (%s)', [illum, 'increasing'])
 else
   Result:=Format('%.0f%% (%s)', [illum, 'decreasing']);
end;

procedure TMoonDlg.Execute;
var Ra,Dec,trise,tset,jd0,jd1,jd2,jd3:double;
    a,d:integer;
    Pl:TPlanets;
begin
 JD:=FromLocalTime(floor(ToLocalTime(JD,TimeZoneX))+0.5,TimeZoneX);
 MoonRaDecPhase(JD,Ra,Dec,Phase);
 a:=round(Ra*60);
 MoonA.Caption:=Format('%dh %.2dm',[(a div 60),(a mod 60)]);
 d:=round(Dec*60);
 if d>=0 then
   MoonD.Caption:=Format('+%d° %.2d''',[(d div 60),(d mod 60)])
 else
   MoonD.Caption:=Format('-%d° %.2d''',[((-d) div 60),((-d) mod 60)]);

 MoonI.Caption:=FormatLunarIllumination(Phase);
 MoonP.Caption:=FormatLunarPhase(Phase);

 Pl:=TPlanets.Create;
 try
   Pl.SetJD(JD);
   Pl.FazeMesice(jd0,jd1,jd2,jd3);
   NM.Caption:=FormatDateTime('yyyy-mm-dd',JDToDateTime(jd0));
   FQ.Caption:=FormatDateTime('yyyy-mm-dd',JDToDateTime(jd1));
   FM.Caption:=FormatDateTime('yyyy-mm-dd',JDToDateTime(jd2));
   LQ.Caption:=FormatDateTime('yyyy-mm-dd',JDToDateTime(jd3));
 finally
   Pl.Free;
 end;

 MoonRiseSet(JD,Lon,Lat,TimeZoneX,TRise,TSet);
 if trise > 0 then
   MoonRise.Caption:=FormatDateTime('yyyy-mm-dd h:nn',JDToDateTime(trise))
 else
   MoonRise.Caption:='***';
 if tset > 0 then
   MoonSet.Caption:=FormatDateTime('yyyy-mm-dd h:nn',JDToDateTime(tset))
 else
   MoonSet.Caption:='***';

 PaintBox1.Invalidate;
 ShowModal;
end;

procedure TMoonDlg.PaintBox1Paint(Sender: TObject);
var r,x0,y0,x:integer;
begin
 with PaintBox1 do begin
   X0:=Width div 2; Y0:=Height div 2; r:=min(X0,Y0);
   Canvas.Pen.Color:=cldkGray;
   Canvas.Brush.Color:=clBlack;
   Canvas.Brush.Style:=bsSolid;
   Canvas.Ellipse(X0-r,Y0-r,X0+r,Y0+r);
   Canvas.Brush.Style:=bsSolid;
   Canvas.Brush.Color:=clWhite;
   x:=round(cos(Phase/180*pi)*r);
   if (x=0)and(Phase<180) then begin
     Canvas.MoveTo(X0,Y0-r); Canvas.LineTo(X0,Y0+r);
     Canvas.FloodFill(X0+1,Y0,Canvas.Pen.Color,fsBorder);
   end else
   if (x=0)and(Phase>180) then begin
     Canvas.MoveTo(X0,Y0-r); Canvas.LineTo(X0,Y0+r);
     Canvas.FloodFill(X0-1,Y0,Canvas.Pen.Color,fsBorder);
   end else
   if (x>0)and(x<r)and(Phase<180) then begin
     Canvas.Arc(X0-x-1,Y0-r,X0+x+1,Y0+r,X0,Y0+r,X0,Y0-r);
     if (x<r-1) then Canvas.FloodFill(X0+x+1,Y0,Canvas.Pen.Color,fsBorder);
   end else
   if (x<0)and(x>-r)and(Phase<180) then begin
     Canvas.Arc(X0+x-1,Y0-r,X0-x+1,Y0+r,X0,Y0-r,X0,Y0+r);
     Canvas.FloodFill(X0+x,Y0,Canvas.Pen.Color,fsBorder);
   end else
   if (x>0)and(x<r)and(Phase>180) then begin
     Canvas.Arc(X0-x-1,Y0-r,X0+x+1,Y0+r,X0,Y0-r,X0,Y0+r);
     if (x<r-1) then Canvas.FloodFill(X0-x-2,Y0,Canvas.Pen.Color,fsBorder);
   end else
   if (x<0)and(x>-r)and(Phase>180) then begin
     Canvas.Arc(X0+x-1,Y0-r,X0-x+1,Y0+r,X0,Y0+r,X0,Y0-r);
     Canvas.FloodFill(X0-x-1,Y0,Canvas.Pen.Color,fsBorder);
   end else
   if (Phase>90)and(Phase<270) then begin
     Canvas.FloodFill(X0,Y0,Canvas.Pen.Color,fsBorder);
   end;
 end;
end;

end.
