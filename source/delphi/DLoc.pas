unit DLoc;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Locations, ComCtrls, ExtCtrls, Utils;

type
  TLocTable = class(TForm)
    SaveBtn: TButton;
    CancelBtn: TButton;
    Panel1: TPanel;
    List: TListView;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    NameEdit: TEdit;
    LonEdit: TEdit;
    LatEdit: TEdit;
    AddBtn: TButton;
    ReplaceBtn: TButton;
    DeleteBtn: TButton;
    Bevel1: TBevel;
    ClearBtn: TButton;
    Label4: TLabel;
    TZEdit: TComboBox;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure ListSelectItem(Sender: TObject; Item: TListItem;
      Selected: Boolean);
    procedure AddBtnClick(Sender: TObject);
    procedure DeleteBtnClick(Sender: TObject);
    procedure ReplaceBtnClick(Sender: TObject);
    procedure ListData(Sender: TObject; Item: TListItem);
    procedure ClearBtnClick(Sender: TObject);
  private
    Loc:TLocations;
    MyList:TStringList;
  public
    Function Execute:boolean;
    Procedure UpdateTable;
    Function GetSelectedTimeZone:integer;
    Procedure SelectTimeZone(Tz:integer);
  end;

var
  LocTable: TLocTable;

implementation

{$R *.dfm}

procedure TLocTable.FormCreate(Sender: TObject);
begin
 Loc:=TLocations.Create;
 MyList:=TStringList.Create;
end;

procedure TLocTable.FormDestroy(Sender: TObject);
begin
 Loc.Free;
 MyList.Free;
end;

Function TLocTable.Execute;
begin
  Result:=false;
  NameEdit.Text:='';
  LonEdit.Text:='';
  LatEdit.Text:='';
  Loc.Load('locations.ini');
  UpdateTable;
  if (List.Items.Count>0) then
    List.ItemIndex:=0;
  if (ShowModal()<>mrCancel) then begin
    Loc.Save('locations.ini');
    Result:=true;
  end;
end;

Procedure TLocTable.UpdateTable;
begin
 List.Items.BeginUpdate;
 List.SortType:=stNone;
 List.Clear;
 MyList.Clear;
 MyList.BeginUpdate;
 try
   Loc.MakeList(MyList);
   List.Items.Count:=MyList.Count;
 finally
   List.Items.EndUpdate;
   MyList.EndUpdate;
 end;
end;


procedure TLocTable.ListSelectItem(Sender: TObject; Item: TListItem; Selected: Boolean);
var Index:integer; It:TLocation;
begin
 if (Selected) then begin
   Index:=Item.Index;
   NameEdit.Text:=MyList[Index];
   It:=TLocation(MyList.Objects[Index]);
   if (It<>NIL) then begin
     LonEdit.Text:=Format('%.04f', [It.Lon]);
     LatEdit.Text:=Format('%.04f', [It.Lat]);
     SelectTimeZone(It.Bias);
   end else begin
     LonEdit.Text:='';
     LatEdit.Text:='';
     TZEdit.ItemIndex:=0;
   end;
   ReplaceBtn.Enabled:=true;
   DeleteBtn.Enabled:=true;
 end else begin
   NameEdit.Text:='';
   LonEdit.Text:='';
   LatEdit.Text:='';
   TZEdit.ItemIndex:=0;
   ReplaceBtn.Enabled:=false;
   DeleteBtn.Enabled:=false;
 end;
end;

procedure TLocTable.AddBtnClick(Sender: TObject);
var Lon, Lat:double; i, Index:integer;
begin
  if (NameEdit.Text='') then begin
    MessageDlg('Please, enter name of the location.',
      mtError, [mbOK], 0);
    NameEdit.SetFocus;
  end else
  if Loc.Exists(NameEdit.Text) then begin
    MessageDlg('Location with the same name already exists.',
      mtError, [mbOK], 0);
    NameEdit.SetFocus;
  end else
  if not TryStrToFloat(LonEdit.Text, Lon) then begin
    MessageDlg('Invalid format of longitude. Use decimal format (e.g. 16.6667).',
      mtError, [mbOK], 0);
    LonEdit.SetFocus;
  end else
  if not TryStrToFloat(LatEdit.Text, Lat) then begin
    MessageDlg('Invalid format of latitude. Use decimal format (e.g. 49.2167).',
      mtError, [mbOK], 0);
    LonEdit.SetFocus;
  end else begin
    Loc.Add(NameEdit.Text, Lon, Lat);
    UpdateTable;
    Index:=-1;
    for i:=0 to List.Items.Count-1 do begin
      if (List.Items[i].Caption=NameEdit.Text) then
        Index:=i;
    end;
    List.ItemIndex:=Index;
    if (Index>=0) then
      List.Items[Index].MakeVisible(false);
  end;
end;

procedure TLocTable.DeleteBtnClick(Sender: TObject);
var Index:integer;
begin
 Index:=List.ItemIndex;
 if Index>=0 then begin
   Loc.Delete(List.Items[Index].Caption);
   NameEdit.Text:='';
   LonEdit.Text:='';
   LatEdit.Text:='';
   UpdateTable;
   if (Index<List.Items.Count) then begin
     List.ItemIndex:=Index;
     if (Index>=0) then
       List.Items[Index].MakeVisible(false);
   end else begin
     Index:=List.Items.Count-1;
     List.ItemIndex:=Index;
     if (Index>=0) then
       List.Items[Index].MakeVisible(false);
   end;
 end;
end;

procedure TLocTable.ClearBtnClick(Sender: TObject);
begin
 if (MessageDlg('Do you want to delete all items from the table?', mtConfirmation,
   [mbYes, mbNo, mbCancel], 0)=mrYes) then begin
   Loc.Clear;
   UpdateTable;
   NameEdit.Text:='';
   LonEdit.Text:='';
   LatEdit.Text:='';
 end;
end;

procedure TLocTable.ReplaceBtnClick(Sender: TObject);
var i, Index:integer; Lon, Lat:double;  It:TLocation;
begin
 Index:=List.ItemIndex;
 if (Index>=0) then begin
   if (NameEdit.Text='') then begin
     MessageDlg('Please, enter name of the location.',
       mtError, [mbOK], 0);
     NameEdit.SetFocus;
   end else begin
     It:=Loc.GetData(NameEdit.Text);
     if (It<>NIL) and (It<>MyList.Objects[Index]) then begin
       MessageDlg('Location with the same name already exists.',
         mtError, [mbOK], 0);
       NameEdit.SetFocus;
     end else
     if not TryStrToFloat(LonEdit.Text, Lon) then begin
       MessageDlg('Invalid format of longitude. Use decimal format (e.g. 16.6667).',
         mtError, [mbOK], 0);
        LonEdit.SetFocus;
     end else
     if not TryStrToFloat(LatEdit.Text, Lat) then begin
       MessageDlg('Invalid format of latitude. Use decimal format (e.g. 49.2167).',
         mtError, [mbOK], 0);
       LonEdit.SetFocus;
     end else begin
       if (MyList[Index]<>NameEdit.Text) then
         Loc.Rename(MyList[Index], NameEdit.Text);
       It:=Loc.GetData(NameEdit.Text);
       if (It<>NIL) then begin
         It.Lon:=Lon;
         It.Lat:=Lat;
         It.Bias:=GetSelectedTimeZone;
       end;
       UpdateTable();
       Index:=-1;
       for i:=0 to MyList.Count-1 do begin
         if (MyList[i]=NameEdit.Text) then
           Index:=i;
       end;
       List.ItemIndex:=Index;
       if (Index>=0) then
         List.Items[Index].MakeVisible(false);
     end;
   end;
 end;
end;

procedure TLocTable.ListData(Sender: TObject; Item: TListItem);
var Index:integer; It:TLocation;
begin
  Index:=Item.Index;
  Item.Caption:=MyList[Index];
  It:=TLocation(MyList.Objects[Index]);
  Item.SubItems.Capacity:=2;
  Item.SubItems.Add(Format('%.04f', [It.Lon]));
  Item.SubItems.Add(Format('%.04f', [It.Lat]));
  if (It.Bias<>9999) then
    Item.SubItems.Add(TzToStr(It.Bias));
end;

Function TLocTable.GetSelectedTimeZone;
var S:String; i:integer;
begin
 Result:=9999;
 if TZEdit.ItemIndex>0 then begin
   S:=TZEdit.Items[TZEdit.ItemIndex];
   i:=pos('UTC', S);
   if not TryStrToTz(copy(S, i, 9), Result) then
     Result:=0;
 end;
end;

Procedure TLocTable.SelectTimeZone;
var S:String; Index,i,j,k:integer;
begin
 Index:=0;
 for i:=1 to TZEdit.Items.Count-1 do begin
   S:=TZEdit.Items[i];
   j:=pos('UTC', S);
   if j>0 then if TryStrToTz(copy(S,j,9),k) then if k=tz then begin
     Index:=i;
     break;
   end;
 end;  
 TZEdit.ItemIndex:=Index;
end;

end.

