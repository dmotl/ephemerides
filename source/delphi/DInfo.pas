unit DInfo;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, Katalog, Efemer, ComCtrls, Math;

type
  TInfoBox = class(TForm)
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    IGrid: TStringGrid;
    TabSheet2: TTabSheet;
    EGrid: TStringGrid;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormResize(Sender: TObject);
  public
    Data:TStringList;
    Procedure ShowInfo(AKat:TKatalog; AEf:TEphemRec);
  end;

var
  InfoBox: TInfoBox;

implementation

{$R *.dfm}

Procedure TInfoBox.ShowInfo;
var i:integer; Name,Value:String; It:TKatZaznam;
begin
 if Assigned(AEf) and AKat.Search(AEf.LongName, It) then begin
   Caption:=It.LongName;
   It.GetInfo(Data);
   IGrid.RowCount:=Data.Count;
   for i:=0 to Data.Count-1 do begin
     Name:=Data.Names[i]; Value:=Data.Values[Name];
     IGrid.Cells[0,i]:=Name;
     IGrid.Cells[1,i]:=Value;
   end;
   AEf.GetInfo(Data);
   EGrid.RowCount:=Data.Count;
   for i:=0 to Data.Count-1 do begin
     Name:=Data.Names[i]; Value:=Data.Values[Name];
     EGrid.Cells[0,i]:=Name;
     EGrid.Cells[1,i]:=Value;
   end;
 end else begin
   Caption:='';
   IGrid.RowCount:=1;
   IGrid.Cells[0,0]:='';
   IGrid.Cells[1,0]:='';
   EGrid.RowCount:=1;
   EGrid.Cells[0,0]:='';
   EGrid.Cells[1,0]:='';
 end;
 FormResize(NIL);
 Show;
end;

procedure TInfoBox.FormCreate(Sender: TObject);
begin
 Data:=TStringList.Create;
end;

procedure TInfoBox.FormDestroy(Sender: TObject);
begin
 Data.Free;
end;

procedure TInfoBox.FormResize(Sender: TObject);
var i,w1,w2:integer; 
begin
 w1:=80; w2:=80;
 for i:=0 to IGrid.RowCount-1 do begin
   w1:=max(w1,IGrid.Canvas.TextWidth(IGrid.Cells[0,i])+6);
   w2:=max(w2,IGrid.Canvas.TextWidth(IGrid.Cells[1,i])+6);
 end;
 for i:=0 to EGrid.RowCount-1 do begin
   w1:=max(w1,EGrid.Canvas.TextWidth(EGrid.Cells[0,i])+6);
   w2:=max(w2,EGrid.Canvas.TextWidth(EGrid.Cells[1,i])+6);
 end;
 IGrid.ColWidths[0]:=w1;
 IGrid.ColWidths[1]:=IGrid.ClientWidth-w1-2;
 EGrid.ColWidths[0]:=w1;
 EGrid.ColWidths[1]:=EGrid.ClientWidth-w1-2;
end;

end.
