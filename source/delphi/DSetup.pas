unit DSetup;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Planety, Efemer, ExtCtrls, Locations, DLoc, Spin, Utils;

type
  TSetupDlg = class(TForm)
    SaveBtn: TButton;
    CancelBtn: TButton;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label5: TLabel;
    LonEdit: TEdit;
    LatEdit: TEdit;
    BrowseBtn: TButton;
    NameEdit: TComboBox;
    Image1: TImage;
    Advanced: TButton;
    Label3: TLabel;
    TZEdit: TComboBox;
    Start: TRadioGroup;
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure NameEditSelect(Sender: TObject);
    procedure BrowseBtnClick(Sender: TObject);
    procedure AdvancedClick(Sender: TObject);
  public
    Loc:TLocations;
    Twilight:integer;
    Function Execute(var AName:String; var ALon,ALat,ATwilight:double; var ATimeZone:integer; var AKeepDate:boolean):boolean;
  private
    Function GetSelectedTimeZone:integer;
    Procedure SelectTimeZone(Tz:integer);
  end;

var
  SetupDlg: TSetupDlg;

implementation

uses DOptions;

{$R *.dfm}

procedure TSetupDlg.FormCreate(Sender: TObject);
begin
 Loc:=TLocations.Create;
end;

procedure TSetupDlg.FormDestroy(Sender: TObject);
begin
 Loc.Free;
end;

Function TSetupDlg.Execute;
begin
 Loc.Load('locations.ini');
 NameEdit.Items.BeginUpdate;
 try
   NameEdit.Items.Clear;
   Loc.MakeList(NameEdit.Items);
 finally
   NameEdit.Items.EndUpdate;
 end;
 NameEdit.Text:=AName;
 LonEdit.Text:=Format('%.4f',[ALon]);
 LatEdit.Text:=Format('%.4f',[ALat]);
 Twilight:=Round(ATwilight);
 SelectTimeZone(ATimeZone);
 if AKeepDate then
   Start.ItemIndex:=1;
 if ShowModal=mrOK then begin
   ALon:=StrToFloat(LonEdit.Text);
   ALat:=StrToFloat(LatEdit.Text);
   ATimeZone:=GetSelectedTimeZone();
   ATwilight:=Twilight;
   AName:=NameEdit.Text;
   AKeepDate:=Start.ItemIndex<>0;
   Result:=true;
 end else
   Result:=false;
end;

procedure TSetupDlg.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
var X:double;
begin
 CanClose:=true;
 if (ModalResult=mrOK) then begin
   if not TryStrToFloat(LonEdit.Text, X) then
     raise Exception.Create('Invalid format of longitude. Use decimal format (e.g. 16.6667).');
   if not TryStrToFloat(LatEdit.Text, X) then
     raise Exception.Create('Invalid format of latitude. Use decimal format (e.g. 49.2167).');
 end;
end;

procedure TSetupDlg.NameEditSelect(Sender: TObject);
var Index:integer; It:TLocation;
begin
 Index:=NameEdit.ItemIndex;
 if (index>=0) then begin
   It:=Loc.GetData(NameEdit.Items[index]);
   if (It<>NIL) then begin
     LonEdit.Text:=Format('%.4f',[It.Lon]);
     LatEdit.Text:=Format('%.4f',[It.Lat]);
     SelectTimeZone(It.Bias);
   end;
 end;
end;

procedure TSetupDlg.BrowseBtnClick(Sender: TObject);
begin
 LocTable.Execute();
 Loc.Load('locations.ini');
 NameEdit.Items.BeginUpdate;
 try
   NameEdit.Items.Clear;
   Loc.MakeList(NameEdit.Items);
 finally
   NameEdit.Items.EndUpdate;
 end;
end;

procedure TSetupDlg.AdvancedClick(Sender: TObject);
begin
 OptionsDlg.Execute(Twilight);
end;

Function TSetupDlg.GetSelectedTimeZone;
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

Procedure TSetupDlg.SelectTimeZone;
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

