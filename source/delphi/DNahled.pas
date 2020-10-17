unit DNahled;

(*
    Protokoly 2.4
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

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls, Forms,
  ExtCtrls, StdCtrls, Buttons, Math, Dialogs, Tisk;

type
  TNahledDlg = class(TForm)
    ScrollBox: TScrollBox;
    Panel2: TPanel;
    StornoBtn: TBitBtn;
    TiskBtn: TBitBtn;
    PrevBtn: TBitBtn;
    NextBtn: TBitBtn;
    Image1: TImage;
    PrintDlg: TPrintDialog;
    procedure FormCreate(Sender: TObject);
    procedure PrevBtnClick(Sender: TObject);
    procedure NextBtnClick(Sender: TObject);
    procedure FormKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure Panel2Resize(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure TiskBtnClick(Sender: TObject);
  private
    ActPage: integer;
    PE     : TPrintEngine;
    Procedure UpdatePage;
  public  
    Procedure Execute;
  end;

var
  NahledDlg : TNahledDlg;

implementation

{$R *.DFM}

Uses DEphem;

Procedure TNahledDlg.Execute;
begin
 MainForm.Print(PE);
 ActPage:=1;
 UpdatePage;
 ShowModal;
end;

Procedure TNahledDlg.UpdatePage;
begin
 PE.Preview(ActPage,Image1);
 TiskBtn.Enabled:=PE.PageCount>0;
 PrevBtn.Enabled:=ActPage>1;
 NextBtn.Enabled:=ActPage<PE.PageCount;
 Caption:=Format('Print preview (page %d of %d)',[ActPage, PE.PageCount]);
end;

procedure TNahledDlg.FormCreate(Sender: TObject);
begin
 SetClassLong(Handle, GCL_HICON, LoadIcon(HInstance, 'MAINICON'));
 Width:=round(Screen.WorkAreaWidth*0.9);
 Height:=round(Screen.WorkAreaHeight*0.9);
 PE:=TPrintEngine.Create(NIL);
 Panel2Resize(NIL);
end;

procedure TNahledDlg.PrevBtnClick(Sender: TObject);
begin
 ActPage:=max(1,ActPage-1);
 UpdatePage;
end;

procedure TNahledDlg.NextBtnClick(Sender: TObject);
begin
 ActPage:=min(PE.PageCount,ActPage+1);
 UpdatePage;
end;

procedure TNahledDlg.FormKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
 if (Key=VK_PRIOR)and(PrevBtn.Enabled) then begin PrevBtnClick(Sender); Key:=0; end;
 if (Key=VK_NEXT)and(NextBtn.Enabled) then begin NextBtnClick(Sender); Key:=0; end;
end;

procedure TNahledDlg.Panel2Resize(Sender: TObject);
var X:integer;
begin
 X:=Panel2.ClientWidth div 2;
 TiskBtn.Left:=X-4-TiskBtn.Width;
 PrevBtn.Left:=TiskBtn.Left-8-PrevBtn.Width;
 StornoBtn.Left:=X+4;
 NextBtn.Left:=StornoBtn.Left+8+StornoBtn.Width; 
end;

procedure TNahledDlg.FormDestroy(Sender: TObject);
begin
 PE.Free;
end;

procedure TNahledDlg.TiskBtnClick(Sender: TObject);
{ Zahajeni tisku protokolu }
var Start,Stop:integer;
begin
 PrintDlg.FromPage:= 1;
 PrintDlg.MinPage := 1;
 PrintDlg.ToPage  := PE.PageCount;
 PrintDlg.MaxPage := PE.PageCount;
 { Dialog pro nastaveni tiskarny }
 if PrintDlg.Execute then begin
   with PrintDlg do begin
     if PrintRange = prAllPages then begin
       Start := MinPage - 1;
       Stop := MaxPage - 1;
     end else begin
       Start := FromPage - 1;
       Stop := ToPage - 1;
     end;
   end;
   { Vytisknout pozadovane stranky }
   Screen.Cursor:=crHourGlass;
   try
     PE.Print(Start,Stop);
   finally
     Screen.Cursor:=crDefault;
   end;
   ModalResult:=mrOK;
 end;
end;

end.



