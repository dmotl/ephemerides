unit DAbout;
(*
    MuniWin (C-Munipack project)
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

uses Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls,
  Buttons, ExtCtrls, ShellAPI, Config;

type
  TAboutBox = class(TForm)
    Panel1: TPanel;
    ProductName: TLabel;
    Ver: TLabel;
    Memo1: TMemo;
    Label1: TLabel;
    OKBtn: TBitBtn;
    procedure Label1Click(Sender: TObject);
  public
    Procedure Execute;
  end;

var AboutBox:TAboutBox;

implementation

{$R *.DFM}

Procedure TAboutBox.Execute;
begin
 Ver.Caption:='Version '+MyVersion;
 ShowModal;
end;

procedure TAboutBox.Label1Click(Sender: TObject);
{ Otevreni webovych stranek projektu }
begin
 ShellExecute(Handle,'open',PChar(TEdit(Sender).Text),'','',0);
end;

end.

