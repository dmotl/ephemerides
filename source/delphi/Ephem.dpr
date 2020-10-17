program Ephem;

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

uses
  Forms,
  DEphem in 'DEphem.pas' {MainForm},
  Katalog in 'Katalog.pas',
  Efemer in 'Efemer.pas',
  DInfo in 'DInfo.pas' {InfoBox},
  IniFile in 'IniFile.pas',
  DNahled in 'DNahled.pas' {NahledDlg},
  PLANETY in 'Planety.pas',
  DSky in 'DSky.pas' {SkyDlg},
  DConst in 'DConst.pas' {ConstDlg},
  DMoon in 'DMoon.pas' {MoonDlg},
  DSun in 'DSun.pas' {SunDlg},
  DAbout in 'DAbout.pas' {AboutBox},
  Config in 'Config.pas',
  Locations in 'Locations.pas',
  DLoc in 'DLoc.pas' {LocTable},
  Export in 'Export.pas',
  Tisk in 'Tisk.pas',
  juldat in 'juldat.pas',
  DOptions in 'DOptions.pas' {OptionsDlg},
  Utils in 'Utils.pas',
  DSetup in 'DSetup.pas' {SetupDlg};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.CreateForm(TInfoBox, InfoBox);
  Application.CreateForm(TNahledDlg, NahledDlg);
  Application.CreateForm(TSkyDlg, SkyDlg);
  Application.CreateForm(TConstDlg, ConstDlg);
  Application.CreateForm(TMoonDlg, MoonDlg);
  Application.CreateForm(TSunDlg, SunDlg);
  Application.CreateForm(TAboutBox, AboutBox);
  Application.CreateForm(TLocTable, LocTable);
  Application.CreateForm(TOptionsDlg, OptionsDlg);
  Application.CreateForm(TSetupDlg, SetupDlg);
  Application.Run;
end.
