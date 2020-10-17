unit DConst;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Planety, Efemer, ExtCtrls, Locations, DLoc, Spin, Utils,
  CheckLst;

type
  TConstDlg = class(TForm)
    FList: TCheckListBox;
    SaveBtn: TButton;
    CancelBtn: TButton;
    SelectAllBtn: TButton;
    ClearBtn: TButton;
    procedure ClearBtnClick(Sender: TObject);
    procedure SelectAllBtnClick(Sender: TObject);
  public
    Function Execute(ACaption:String; AList:TStrings; ASel:TStrings):boolean;
  end;

var
  ConstDlg: TConstDlg;

implementation

{$R *.dfm}

Function TConstDlg.Execute;
var i,index:integer;
begin
 Caption:=ACaption;
 FList.Items.BeginUpdate;
 try
   FList.Items.Clear;
   for i:=0 to AList.Count-1 do
     FList.Items.Add(AList[i])
 finally
   FList.Items.EndUpdate;
 end;
 for i:=0 to ASel.Count-1 do begin
   index:=FList.Items.IndexOf(ASel[i]);
   if index>=0 then
     FList.Checked[index]:=true;
 end;
 if ShowModal=mrOK then begin
   ASel.BeginUpdate;
   try
     ASel.Clear;
     for i:=0 to FList.Count-1 do if FList.Checked[i] then
       ASel.Add(FList.Items[i]);
   finally
     ASel.EndUpdate;
   end;
   Result:=true;
 end else
   Result:=false;
end;

procedure TConstDlg.ClearBtnClick(Sender: TObject);
var i:integer;
begin
 for i:=0 to FList.Count-1 do if FList.Checked[i] then
   FList.Checked[i]:=false;
end;

procedure TConstDlg.SelectAllBtnClick(Sender: TObject);
var i:integer;
begin
 for i:=0 to FList.Count-1 do if not FList.Checked[i] then
   FList.Checked[i]:=true;
end;

end.

