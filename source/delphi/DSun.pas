unit DSun;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Planety, JulDat, Efemer, ExtCtrls, Math;

type
  TSunDlg = class(TForm)
    Button1: TButton;
    Label1: TLabel;
    Label2: TLabel;
    SunRise: TLabel;
    SunSet: TLabel;
    Image1: TImage;
    Label3: TLabel;
    Label4: TLabel;
    Svitani: TLabel;
    Soumrak: TLabel;
    Label5: TLabel;
  public
    Procedure Execute(JD,ALon,ALat,ATwilight:double; TimeZoneX:integer);
  end;

var
  SunDlg: TSunDlg;

Procedure SunRADec(JD:double; var RA,Dec:double);
Procedure SunTwilight(JD,ALon,ALat,ATwilight:double; TimeZoneX:integer; var TSet,TRise,TEnd,TStart:double);

implementation

{$R *.dfm}

Uses Utils;

Procedure SunRaDec;
var Pl:TPlanets;
begin
 Pl:=TPlanets.Create;
 with Pl do try
   SetJD(JD);
   RA:=alfas*12/pi;
   Dec:=deltas*180/pi;
 finally
   Pl.Free;
 end;
end;

Procedure SunTwilight(JD,ALon,ALat,ATwilight:double; TimeZoneX:integer; var TSet,TRise,TEnd,TStart:double);
var RA,Dec,JD1:double; cond:RiseSetCond;
begin
 JD:=FromLocalTime(floor(ToLocalTime(JD,TimeZoneX))+0.5,TimeZoneX);
 SunRADec(JD+1,RA,Dec);
 JD1:=RaDeToRise(RA,Dec,jd+1,alon,alat,-0.8,rtNearest,cond);
 if JD1>0 then begin
   SunRADec(JD1,RA,Dec);
   trise:=RaDeToRise(RA,Dec,JD1,alon,alat,-0.8,rtNearest,cond);
   tstart:=RaDeToRise(RA,Dec,JD1,alon,alat,-ATwilight,rtNearest,cond);
 end else begin
   trise:=0;
   tstart:=0;
 end;
 SunRADec(JD+1,RA,Dec);
 JD1:=RaDeToSet(RA,Dec,jd,alon,alat,-0.8,rtNearest,cond);
 if JD1>0 then begin
   SunRADec(JD1,RA,Dec);
   tset:=RaDeToSet(RA,Dec,JD1,alon,alat,-0.8,rtNearest,cond);
   tend:=RaDeToSet(RA,Dec,JD1,alon,alat,-ATwilight,rtNearest,cond);
 end else begin
   tset:=0;
   tend:=0;
 end;
end;

Procedure TSunDlg.Execute;
var trise,tset,tstart,tend:double;
begin
 SunTwilight(JD,ALon,ALat,ATwilight,TimeZoneX,TSet,TRise,TEnd,TStart);
 if trise>0 then
   SunRise.Caption:=FormatDateTime('yyyy-mm-dd h:nn',JDToDateTime(trise))
 else
   SunRise.Caption:='***';
 if tstart>0 then
   Svitani.Caption:=FormatDateTime('yyyy-mm-dd h:nn',JDToDateTime(tstart))
 else
   Svitani.Caption:='***';
 if tset>0 then
   SunSet.Caption:=FormatDateTime('yyyy-mm-dd h:nn',JDToDateTime(tset))
 else
   SunSet.Caption:='***';
 if tend>0 then
   Soumrak.Caption:=FormatDateTime('yyyy-mm-dd h:nn',JDToDateTime(tend))
 else
   Soumrak.Caption:='***';
 Label5.Caption:=Format('*) Solar elevation angle lower than -%.0f°', [ATwilight]);
 ShowModal;
end;

end.
