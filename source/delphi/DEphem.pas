unit DEphem;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls, Buttons, CheckLst, Katalog, Efemer,
  Utils, JulDat, StrUtils, ImgList, ToolWin, Menus, IniFile, Tisk, DNahled,
  Math, DInfo, DSun, DMoon, DSky, DSetup, Clipbrd, Spin, DAbout, DConst, Export,
  Config, Printers;

type
  TFilter = record
    DateFrom, DateTo:TDateTime;   // Local time
    JDMin, JDMax:double;          // UTC
    Location:String; Lat, Lon, Twilight:double;
    FRA, FDec, FMag, FPts, FTime, FNight, FAlt, FAz, FDOW, FCon, FTyp, FObjMoon:boolean;
    TimeFrom, TimeTo, AltFrom, AltTo, AzFrom, AzTo, ObjMoon:double;
    RaFrom, RaTo, DecFrom, DecTo, MagFrom, MagTo:double;
    PtsFrom, PtsTo:integer;
    DOW:array[1..7] of boolean;
    Cons, Types:String;
  end;

  TMainForm = class(TForm)
    Sort1Menu: TPopupMenu;
    Seaditpodlenzvu1: TMenuItem;
    Seaditpodleasu1: TMenuItem;
    Seaditpodleazimutu1: TMenuItem;
    Seaditpodlevky1: TMenuItem;
    Seaditpodlerektascenze1: TMenuItem;
    Seaditpodledeklinace1: TMenuItem;
    Seaditpodletypu1: TMenuItem;
    Seaditpodlejasnosti1: TMenuItem;
    SeaditpodleKatalogu1: TMenuItem;
    Seaditpodlebed1: TMenuItem;
    ImageList: TImageList;
    Pages: TPageControl;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    Panel2: TPanel;
    List: TListView;
    ToolBar1: TToolBar;
    RunBtn: TToolButton;
    SortBtn: TToolButton;
    DelBtn: TToolButton;
    InfoBtn: TToolButton;
    ToolButton2: TToolButton;
    PrintBtn: TToolButton;
    ToolButton4: TToolButton;
    SunBtn: TToolButton;
    MoonBtn: TToolButton;
    Panel1: TPanel;
    Label2: TLabel;
    Label1: TLabel;
    Cats: TCheckListBox;
    Date: TDateTimePicker;
    Panel3: TPanel;
    List2: TListView;
    ToolBar2: TToolBar;
    Run2Btn: TToolButton;
    Info2Btn: TToolButton;
    ToolButton7: TToolButton;
    Print2Btn: TToolButton;
    ToolButton9: TToolButton;
    Sun2Btn: TToolButton;
    Moon2Btn: TToolButton;
    Panel4: TPanel;
    Label26: TLabel;
    Label27: TLabel;
    Label28: TLabel;
    Label29: TLabel;
    DTStart: TDateTimePicker;
    DTEnd: TDateTimePicker;
    Cats2: TComboBox;
    Cons2: TComboBox;
    Star2: TListBox;
    Sort2Btn: TToolButton;
    Sort2Menu: TPopupMenu;
    MenuItem1: TMenuItem;
    MenuItem2: TMenuItem;
    MenuItem3: TMenuItem;
    MenuItem4: TMenuItem;
    SkyBtn: TToolButton;
    Sky2Btn: TToolButton;
    ToolButton1: TToolButton;
    HelpBtn: TToolButton;
    ToolButton3: TToolButton;
    Help2Btn: TToolButton;
    ToolButton5: TToolButton;
    ToolButton6: TToolButton;
    Find2Btn: TToolButton;
    FindDialog: TFindDialog;
    FindBtn: TToolButton;
    SaveBtn: TToolButton;
    CopyBtn: TToolButton;
    Save2Btn: TToolButton;
    Copy2Btn: TToolButton;
    SaveDialog: TSaveDialog;
    Label3: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label33: TLabel;
    Label34: TLabel;
    Label35: TLabel;
    MagF: TCheckBox;
    MinF: TCheckBox;
    AltF: TCheckBox;
    RAF: TCheckBox;
    DecF: TCheckBox;
    PTSF: TCheckBox;
    Mag1SB: TSpinButton;
    Mag1: TEdit;
    Mag2: TEdit;
    Mag2SB: TSpinButton;
    Min1: TEdit;
    Min1SB: TSpinButton;
    Min2: TEdit;
    Min2SB: TSpinButton;
    Alt1: TEdit;
    Alt1SB: TSpinButton;
    Alt2: TEdit;
    Alt2SB: TSpinButton;
    RA1: TEdit;
    Ra1SB: TSpinButton;
    RA2: TEdit;
    Ra2SB: TSpinButton;
    Dec1: TEdit;
    Dec1SB: TSpinButton;
    Dec2: TEdit;
    Dec2SB: TSpinButton;
    Pts2SB: TSpinButton;
    Pts2: TEdit;
    Pts1SB: TSpinButton;
    Pts1: TEdit;
    AZF: TCheckBox;
    Az1: TEdit;
    Az1SB: TSpinButton;
    Az2: TEdit;
    Az2SB: TSpinButton;
    Label39: TLabel;
    Label32: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    Label18: TLabel;
    Label22: TLabel;
    TimeF: TCheckBox;
    VysF: TCheckBox;
    Time2SB: TSpinButton;
    Time2: TEdit;
    Time1SB: TSpinButton;
    Time1: TEdit;
    Vys1: TEdit;
    Vys1SB: TSpinButton;
    Vys2: TEdit;
    Vys2SB: TSpinButton;
    AziF: TCheckBox;
    Label36: TLabel;
    Azi1: TEdit;
    Azi1SB: TSpinButton;
    Label37: TLabel;
    Azi2: TEdit;
    Azi2SB: TSpinButton;
    Label38: TLabel;
    Label40: TLabel;
    HelpMenu: TPopupMenu;
    MHelpEn: TMenuItem;
    MHelpCs: TMenuItem;
    N1: TMenuItem;
    MAbout: TMenuItem;
    Del2Btn: TToolButton;
    SetupBtn: TToolButton;
    ToolButton8: TToolButton;
    FNight: TCheckBox;
    FNight2: TCheckBox;
    Label30: TLabel;
    Label31: TLabel;
    MenuItem5: TMenuItem;
    DOWF: TCheckBox;
    Mon: TCheckBox;
    Tue: TCheckBox;
    Wed: TCheckBox;
    Thu: TCheckBox;
    Fri: TCheckBox;
    Sat: TCheckBox;
    Sun: TCheckBox;
    ListMenu: TPopupMenu;
    Resize: TMenuItem;
    ConF: TCheckBox;
    Con: TEdit;
    ConBtn: TButton;
    StatusBar1: TStatusBar;
    TypF: TCheckBox;
    Typ: TEdit;
    TypBtn: TButton;
    CatalogMenu: TPopupMenu;
    CatalogMenuSelectAll: TMenuItem;
    CatalogMenuClear: TMenuItem;
    Sortbyminimumtype1: TMenuItem;
    Sortbylunarillumination1: TMenuItem;
    Sortbylunardistance1: TMenuItem;
    SortbyObjMoondistance1: TMenuItem;
    Sortbyremarks1: TMenuItem;
    OMF: TCheckBox;
    Label41: TLabel;
    Om1: TEdit;
    Label42: TLabel;
    Om1SB: TSpinButton;
    N2: TMenuItem;
    Copytoclipboard1: TMenuItem;
    CopyJD: TMenuItem;
    CopyName: TMenuItem;
    ObjMF: TCheckBox;
    Label43: TLabel;
    ObjM1: TEdit;
    ObjM1SB: TSpinButton;
    Label44: TLabel;
    CopyUTC: TMenuItem;
    CopyLocT: TMenuItem;
    procedure CloseBtnClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure RunBtnClick(Sender: TObject);
    procedure ListCustomDrawItem(Sender: TCustomListView; Item: TListItem;
      State: TCustomDrawState; var DefaultDraw: Boolean);
    procedure ListCompare(Sender: TObject; Item1, Item2: TListItem;
      Data: Integer; var Compare: Integer);
    procedure SortChange(Sender: TObject);
    procedure Sort2Change(Sender: TObject);
    procedure ListColumnClick(Sender: TObject; Column: TListColumn);
    procedure Min2Change(Sender: TObject);
    procedure Alt2Change(Sender: TObject);
    procedure ListSelectItem(Sender: TObject; Item: TListItem;
      Selected: Boolean);
    procedure InfoBtnClick(Sender: TObject);
    procedure ListKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure DelBtnClick(Sender: TObject);
    procedure PrintBtnClick(Sender: TObject);
    procedure PopupClick(Sender: TObject);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure FormDestroy(Sender: TObject);
    procedure SunBtnClick(Sender: TObject);
    procedure MoonBtnClick(Sender: TObject);
    procedure Run2BtnClick(Sender: TObject);
    procedure Cats2Change(Sender: TObject);
    procedure Cons2Change(Sender: TObject);
    procedure Time1Change(Sender: TObject);
    procedure Vys1Change(Sender: TObject);
    procedure PagesChange(Sender: TObject);
    procedure Star2Click(Sender: TObject);
    procedure List2Compare(Sender: TObject; Item1, Item2: TListItem;
      Data: Integer; var Compare: Integer);
    procedure List2ColumnClick(Sender: TObject; Column: TListColumn);
    procedure MenuItem4Click(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure Sun2BtnClick(Sender: TObject);
    procedure Moon2BtnClick(Sender: TObject);
    procedure SkyBtnClick(Sender: TObject);
    procedure Sky2BtnClick(Sender: TObject);
    procedure HelpBtnClick(Sender: TObject);
    procedure ObserverBtnClick(Sender: TObject);
    procedure MagDownClick(Sender: TObject);
    procedure MagUpClick(Sender: TObject);
    procedure Mag1Exit(Sender: TObject);
    procedure MinDownClick(Sender: TObject);
    procedure MinUpClick(Sender: TObject);
    procedure Min2Exit(Sender: TObject);
    procedure AltDownClick(Sender: TObject);
    procedure AltUpClick(Sender: TObject);
    procedure Alt2Exit(Sender: TObject);
    procedure Print2BtnClick(Sender: TObject);
    procedure Find2BtnClick(Sender: TObject);
    procedure FindBtnClick(Sender: TObject);
    procedure List2KeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure SaveBtnClick(Sender: TObject);
    procedure CopyBtnClick(Sender: TObject);
    procedure Save2BtnClick(Sender: TObject);
    procedure Copy2BtnClick(Sender: TObject);
    procedure AzDownClick(Sender: TObject);
    procedure AzUpClick(Sender: TObject);
    procedure AzExit(Sender: TObject);
    procedure AZFClick(Sender: TObject);
    procedure AziFClick(Sender: TObject);
    procedure MAboutClick(Sender: TObject);
    procedure Del2BtnClick(Sender: TObject);
    procedure FNightClick(Sender: TObject);
    procedure FNight2Click(Sender: TObject);
    procedure UpdateControls(Sender:TObject);
    procedure DOWFClick(Sender: TObject);
    procedure ResizeClick(Sender: TObject);
    procedure ListMenuPopup(Sender: TObject);
    procedure ConBtnClick(Sender: TObject);
    procedure TypBtnClick(Sender: TObject);
    procedure StatusBar1Resize(Sender: TObject);
    procedure CatalogMenuSelectAllClick(Sender: TObject);
    procedure CatalogMenuClearClick(Sender: TObject);
    procedure CatalogMenuPopup(Sender: TObject);
    procedure Sort1MenuPopup(Sender: TObject);
    procedure Sort2MenuPopup(Sender: TObject);
    procedure Om1SBDownClick(Sender: TObject);
    procedure Om1SBUpClick(Sender: TObject);
    procedure Om1Exit(Sender: TObject);
    procedure OMFClick(Sender: TObject);
    procedure CopyJDClick(Sender: TObject);
    procedure CopyNameClick(Sender: TObject);
    procedure ObjMFClick(Sender: TObject);
    procedure ObjM1Exit(Sender: TObject);
    procedure ObjM1SBDownClick(Sender: TObject);
    procedure ObjM1SBUpClick(Sender: TObject);
    procedure CopyUTCClick(Sender: TObject);
    procedure CopyLocTClick(Sender: TObject);
  private
    Updating, FirstRun, AutoSize, AfterStart, KeepDate:boolean;
    Sort, Sort2, X, StartR, StartC: integer;
    Ini:TIniFile;
    Kat1,Kat2:TKatalog;
    StarName, StarCat, LastCat, LastStar, LastCons:String;
    LastDir:String;
    LastFormat:integer;
    FFilter1, FFilter2:TFilter;
    Records1, Variables1, Records2:integer;
    StatStrWidth:integer;
    Procedure Proc1(ARec:TEphemRec);
    Procedure Proc2(ARec:TEphemRec);
    procedure Find1(Sender: TObject);
    procedure Find2(Sender: TObject);
    Procedure LoadKonfig;
    Procedure SaveKonfig;
    Procedure Print1(P:TPrintEngine);
    Procedure Print2(P:TPrintEngine);
    Procedure Export1(E:TExportEngine);
    Procedure Export2(E:TExportEngine);
    function  NasHelp(Command: Word; Data: Longint; var CallHelp: Boolean): Boolean;
    procedure WMHelp(var Message: TWMHelp); message WM_HELP;
    Procedure UpdateFilter(var Filter:TFilter);
    Procedure UpdateStatus;
    Procedure UpdateColumnWidths(AList:TListView);
    Procedure Split(AStr:String; AList:TStrings);
    Function  CountUniqueRecords(AList:TListItems):integer;
  public
    Obs:String;             // Nazev pozorovaciho stanoviste
    Lon, Lat:double;        // Vybraná poloha pozorovatele a casova zona
    TimeZoneX:integer;       // Time zone (9999 = Auto)
    Twilight:double;        // Altitude of sun at twilight end (positive number in degrees)
    Procedure Print(P:TPrintEngine);
  end;

var
  MainForm: TMainForm;

const SDayNames:array[1..7] of String = ('Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat');
      LDayNames:array[1..7] of String = ('Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday');
      SMonNames:array[1..12] of String = ('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec');
      LMonNames:array[1..12] of String = ('January', 'February', 'March', 'April', 'May', 'June', 'July', 'August',
                                          'September', 'October', 'November', 'December');


implementation

{$R *.dfm}

procedure TMainForm.FormCreate(Sender: TObject);
var d, m, y:word;
var i:integer;
begin
 Updating:=false;
 KeepDate:=false;
 DecimalSeparator:='.';
 Application.OnHelp:=NasHelp;
 Pages.ActivePage:=TabSheet1;
 Date.DateTime:=Now;
 DTStart.DateTime:=Now;
 Lon:=16.6667; Lat:=49.2167; Obs:='Brno';
 TimeZoneX:=9999;
 for i:=1 to 7 do begin
   ShortDayNames[i]:=SDayNames[i];
   LongDayNames[i]:=LDayNames[i];
 end;
 for i:=1 to 12 do begin
   ShortMonthNames[i]:=SMonNames[i];
   LongMonthNames[i]:=LMonNames[i];
 end;
 Twilight:=12;
 FirstRun:=true;
 AutoSize:=false;
 StarName:='';
 DecodeDate(Now, y, m, d);
 m:=m+4;
 if m>12 then begin y:=y+1; m:=m-12; end;
 DTEnd.DateTime:=EncodeDate(y, m, 1)-1;
 Kat1:=TKatalog.Create();
 Kat2:=TKatalog.Create();
 Ini:=TIniFile.Create;
 Kat1.CatList(Cats.Items,'');
 for i:=0 to Cats.Items.Count-1 do Cats.Checked[i]:=true;
 Kat2.CatList(Cats2.Items,'');
 MHelpEn.Visible:=FileExists('help-en.chm');
 MHelpCs.Visible:=FileExists('help-cs.chm');
 StatusBar1.Panels[0].Text:='Version ' + MyVersion;
 StatStrWidth:=0;
 Records1:=0;
 Records2:=0;
 Variables1:=0;
 AfterStart:=true;
end;

procedure TMainForm.CloseBtnClick(Sender: TObject);
begin
 Close;
end;

Procedure TMainForm.Proc1;
begin
 with List.Items.Add do begin
   Caption:=ARec.LongName;
   SubItems.Add(UpperCase(ARec.MinTyp));
   SubItems.Add(FormatDateTime('yyyy-mm-dd', floor(JDToDateTime(ARec.JD))));
   SubItems.Add(Format('%.1f',[round(frac(ARec.JD+0.5)*24*2)/2]));
   SubItems.Add(AzToStr(ARec.ObjA));
   SubItems.Add(Format('%.0f',[ARec.Objh]));
   SubItems.Add(RaToStr2(ARec.RA));
   SubItems.Add(Format('%.1f',[ARec.DEC]));
   SubItems.Add(ARec.Typ);
   SubItems.Add(
     ifthen(ARec.mag1>-9,Format('%.1f',[ARec.Mag1]),'??')+'-'+
     ifthen(ARec.mag2>-9,Format('%.1f',[ARec.Mag2]),'??'));
   SubItems.Add(ARec.Katalog);
   SubItems.Add(IntToStr(ARec.Pts));
   SubItems.Add(Format('%.0f°',[ARec.MoonD]));
   SubItems.Add(ARec.Remarks);
   Data:=TEphemRec.CreateCopy(ARec);
 end;
end;

procedure TMainForm.RunBtnClick(Sender: TObject);
var i,j:integer;
    F,F0,F1:double;
    C:String;
    ok, found:boolean;
    O:TKatZaznam;
    Cons, Types, VT:TStringList;
begin
 List.Items.BeginUpdate;
 Screen.Cursor:=crHourGlass;
 Cons:=TStringList.Create;
 Types:=TStringList.Create;
 Updating:=true;
 Records1:=0; Variables1:=0;
 try
   X:=0;
   List.Clear;
   FFilter1.DateFrom:=int(Date.Date);
   FFilter1.DateTo:=FFilter1.DateFrom+1;
   FFilter1.JDMin:=FromLocalTime(int(Date.Date)+0.5, TimeZoneX);  // Noon, current day
   FFilter1.JDMax:=FromLocalTime(int(Date.Date)+1.5, TimeZoneX);  // Noon, next day
   UpdateFilter(FFilter1);
   { Load catalogue files }
   Kat1.Clear;
   for i:=0 to Cats.Items.Count-1 do if Cats.Checked[i] then
     Kat1.Load(Cats.Items[i]);
   { Make list of constellations }
   if FFilter1.FCon then
     Split(FFilter1.Cons, Cons);
   if FFilter1.FTyp then
     Split(FFilter1.Types, Types);
   for j:=0 to Kat1.Data.Count-1 do begin
     { Object filter }
     O:=TKatZaznam(Kat1.Data.Objects[j]);
     ok:=true;
     if ok and FFilter1.FCon then begin
       C:=O.Cons;
       if Cons.IndexOf(C)<0 then
         ok:=false;
     end;
     if ok and FFilter1.FTyp then begin
       found:=false;
       VT:=O.VarTypList;
       try
         if (VT.Count=0) and (Types.IndexOf('Unknown')>=0) then
           found:=true
         else for i:=0 to VT.Count-1 do
           if Types.indexOf(VT[i])>=0 then begin
             found:=true;
             break;
           end;
       finally
         VT.Free;
       end;
       if not found then
         ok:=false;
     end;
     if ok and FFilter1.FRA then begin
       F :=O.RA;
       F0:=FFilter1.RaFrom;
       F1:=FFilter1.RaTo;
       if (F0<=F1)and((F<F0)or(F>=F1)) then ok:=false;
       if (F1<F0)and((F>=F1)and(F<F0)) then ok:=false;
     end;
     if ok and FFilter1.FDec then begin
       F :=O.Dec;
       if (F<FFilter1.DecFrom)or(F>FFilter1.DecTo) then ok:=false;
     end;
     if ok and FFilter1.FMag then begin
       F :=O.Mag2;
       if (F>99)or(F<-99) then
         F:=O.Mag1;
       if (F<FFilter1.MagFrom)or(F>FFilter1.MagTo) then ok:=false;
     end;
     if ok and FFilter1.FPts then begin
       i :=O.Rating;
       if (i<FFilter1.PtsFrom)or(i>FFilter1.PtsTo) then ok:=false;
     end;
     if ok then begin
       { Make ephemerides }
       Ephemeride(O, FFilter1.JDMin, FFilter1.JDMax,
         Lon, Lat, Twilight, TimeZoneX, FFilter1.FTime, FFilter1.FNight, FFilter1.TimeFrom,
         FFilter1.TimeTo, FFilter1.FAz, FFilter1.AzFrom, FFilter1.AzTo, FFilter1.FAlt,
         FFilter1.AltFrom, FFilter1.AltTo, FFilter1.FObjMoon, FFilter1.ObjMoon, Proc1);
     end;
   end;
   { Sort items }
   if List.Items.Count>1 then
     List.AlphaSort;
   { Autosize columns }
   if AutoSize then
     UpdateColumnWidths(List);
   { Update statistics }
   Records1:=List.Items.Count;
   Variables1:=CountUniqueRecords(List.Items);
 finally
   List.Items.EndUpdate;
   Cons.Free;
   Types.Free;
   if List.Items.Count>0 then List.Selected:=List.Items[0];
   Screen.Cursor:=crDefault;
   Updating:=false;
   AfterStart:=false;
   UpdateStatus;
   UpdateControls(Sender);
 end;
end;

procedure TMainForm.ListCustomDrawItem(Sender: TCustomListView;
  Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
begin
 if not odd(Item.Index) then with Sender.Canvas do begin
   Brush.Color:=$EEEEEE;
 end;
end;

procedure TMainForm.ListCompare(Sender: TObject; Item1, Item2: TListItem;
  Data: Integer; var Compare: Integer);
var Value1, Value2:double;
begin
 case Sort of
   3: begin
        Value1:=ifthen(SameText(TEphemRec(Item1.Data).MinTyp,'P'),0,1);
        Value2:=ifthen(SameText(TEphemRec(Item2.Data).MinTyp,'P'),0,1);
      end;
   4..5: begin
        Value1:=TEphemRec(Item1.Data).JD;
        Value2:=TEphemRec(Item2.Data).JD;
      end;
   6: begin
        Value1:=TEphemRec(Item1.Data).ObjA;
        Value2:=TEphemRec(Item2.Data).ObjA;
      end;
   7: begin
        Value1:=-TEphemRec(Item1.Data).Objh;
        Value2:=-TEphemRec(Item2.Data).Objh;
      end;
   8: begin
        Value1:=TEphemRec(Item1.Data).RA;
        Value2:=TEphemRec(Item2.Data).RA;
      end;
   9: begin
        Value1:=TEphemRec(Item1.Data).DEC;
        Value2:=TEphemRec(Item2.Data).DEC;
      end;
   10: begin
        Value1:=CompareStr(TEphemRec(Item1.Data).Typ,TEphemRec(Item2.Data).Typ);
        Value2:=0;
      end;
   11: begin
        Value1:=TEphemRec(Item1.Data).Mag2;
        Value2:=TEphemRec(Item2.Data).Mag2;
      end;
   12: begin
        Value1:=CompareStr(TEphemRec(Item1.Data).Katalog,TEphemRec(Item2.Data).Katalog);
        Value2:=0;
       end;
   13: begin
        Value1:=TEphemRec(Item1.Data).Pts;
        Value2:=TEphemRec(Item2.Data).Pts;
       end;
   14: begin
        Value1:=-TEphemRec(Item1.Data).MoonD;
        Value2:=-TEphemRec(Item2.Data).MoonD;
      end;
   15: begin
        Value1:=CompareStr(TEphemRec(Item1.Data).Remarks,TEphemRec(Item2.Data).Remarks);
        Value2:=0;
      end;
   else begin
        Value1:=0;
        Value2:=0;
      end;
 end;
 if Value1=Value2 then begin
   Value1:=ConsCompare(TEphemRec(Item1.Data).Cons, TEphemRec(Item2.Data).Cons);
   Value2:=0;
 end;
 if Value1=Value2 then begin
   Value1:=NameCompare(TEphemRec(Item1.Data).ShrtName, TEphemRec(Item2.Data).ShrtName);
   Value2:=0;
 end;
 if Value1=Value2 then begin
    Value1:=ifthen(SameText(TEphemRec(Item1.Data).MinTyp,'P'),0,1);
    Value2:=ifthen(SameText(TEphemRec(Item2.Data).MinTyp,'P'),0,1);
 end;
 if Value1=Value2 then begin
   Value1:=CompareStr(TEphemRec(Item1.Data).Katalog,TEphemRec(Item2.Data).Katalog);
   Value2:=0;
 end;
 if Value1=Value2 then begin
   Value1:=TEphemRec(Item1.Data).KIndex;
   Value2:=TEphemRec(Item2.Data).KIndex;
 end;
 if (Value1<Value2) then Compare:=-1
 else if (Value1>Value2) then Compare:=1
 else Compare:=0;
end;

procedure TMainForm.Sort1MenuPopup(Sender: TObject);
begin
 case Sort of
   3: begin
        Sortbyminimumtype1.Checked:=True;
      end;
   4..5: begin
        Seaditpodleasu1.Checked:=True;
      end;
   6: begin
        Seaditpodleazimutu1.Checked:=True;
      end;
   7: begin
        Seaditpodlevky1.Checked:=True;
      end;
   8: begin
        Seaditpodlerektascenze1.Checked:=True
      end;
   9: begin
        Seaditpodledeklinace1.Checked:=True;
      end;
   10: begin
        Seaditpodletypu1.Checked:=True;
      end;
   11: begin
        Seaditpodlejasnosti1.Checked:=True;
      end;
   12: begin
        SeaditpodleKatalogu1.Checked:=True;
       end;
   13: begin
        Seaditpodlebed1.Checked:=True;
       end;
   14: begin
        SortbyObjMoondistance1.Checked:=True;
      end;
   15: begin
        SortByRemarks1.Checked:=True;
      end;
   else begin
        Seaditpodlenzvu1.Checked:=True;
      end;
 end;
end;



procedure TMainForm.SortChange(Sender: TObject);
begin
 List.AlphaSort;
 if Assigned(List.Selected) then List.Selected.MakeVisible(false);
end;

procedure TMainForm.ListColumnClick(Sender: TObject; Column: TListColumn);
begin
 Sort:=Column.Index + 2;
 SortChange(Sender);
end;

procedure TMainForm.Min2Change(Sender: TObject);
begin
 if not Updating then begin
   Updating:=true;
   if (Sender<>MinF) then MINF.Checked:=true;
   TimeF.Checked:=MinF.Checked;
   Time1.Text   :=Min1.Text;
   Time2.Text   :=Min2.Text;
   FNight2.Checked:=FNight.Checked;
   Updating:=false;
   UpdateControls(Sender);
 end;
end;

procedure TMainForm.FNightClick(Sender: TObject);
begin
 if not Updating then begin
   Updating:=true;
   if (Sender<>FNight) then FNight.Checked:=true;
   FNight2.Checked:=FNight.Checked;
   Updating:=false;
   UpdateControls(Sender);
 end;
end;

procedure TMainForm.Alt2Change(Sender: TObject);
begin
 if not Updating then begin
   Updating:=true;
   if (Sender<>AltF) then ALTF.Checked:=true;
   VysF.Checked:=AltF.Checked;
   Vys1.Text   :=Alt1.Text;
   Vys2.Text   :=Alt2.Text;
   Updating:=false;
   UpdateControls(Sender);
 end;
end;

procedure TMainForm.Cats2Change(Sender: TObject);
begin
 LastCat:=Cats2.Text;
 Kat2.Clear;
 Kat2.Load(Cats2.Text);
 Cons2.ItemIndex:=Kat2.ConsList(Cons2.Items, LastCons);
 Cons2Change(NIL);
 UpdateControls(Sender);
end;

procedure TMainForm.Cons2Change(Sender: TObject);
begin
 LastCons:=Cons2.Text;
 Star2.ItemIndex:=Kat2.StarList(Star2.Items, Cons2.Text, LastStar);
 Star2Click(NIL);
end;

procedure TMainForm.Time1Change(Sender: TObject);
begin
 if not Updating then begin
   Updating:=true;
   if (Sender<>TimeF) then TimeF.Checked:=true;
   MinF.Checked:=TimeF.Checked;
   Min1.Text  :=Time1.Text;
   Min2.Text  :=Time2.Text;
   FNight.Checked:=FNight2.Checked;
   Updating:=false;
   UpdateControls(Sender);
 end;
end;

procedure TMainForm.DOWFClick(Sender: TObject);
begin
 if not Updating then begin
   UpdateControls(Sender);
 end;
end;

procedure TMainForm.FNight2Click(Sender: TObject);
begin
 if not Updating then begin
   Updating:=true;
   if (Sender<>FNight2) then FNight2.Checked:=true;
   FNight.Checked:=FNight2.Checked;
   Updating:=false;
   UpdateControls(Sender);
 end;
end;

procedure TMainForm.Vys1Change(Sender: TObject);
begin
 if not Updating then begin
   Updating:=true;
   if (Sender<>VysF) then VysF.Checked:=true;
   AltF.Checked:=VysF.Checked;
   Alt1.Text   :=Vys1.Text;
   Alt2.Text   :=Vys2.Text;
   Updating:=false;
   UpdateControls(Sender);
 end;
end;

procedure TMainForm.AzDownClick(Sender: TObject);
var X:double;
begin
 if Assigned(TSpinButton(Sender).FocusControl) then begin
   X:=StrToAz(TEdit(TSpinButton(Sender).FocusControl).Text);
   X:=X-45; if X<0 then X:=X+360;
   TEdit(TSpinButton(Sender).FocusControl).Text:=Format('%.0f', [X]);
 end;
end;

procedure TMainForm.AzUpClick(Sender: TObject);
var X:double;
begin
 if Assigned(TSpinButton(Sender).FocusControl) then begin
   X:=StrToAz(TEdit(TSpinButton(Sender).FocusControl).Text);
   X:=X+45; if (X>=360) then X:=X-360;
   TEdit(TSpinButton(Sender).FocusControl).Text:=Format('%.0f',[X]);
 end;
end;

procedure TMainForm.AzExit(Sender: TObject);
begin
 TEdit(Sender).Text:=Format('%.0f', [StrToAz(TEdit(Sender).Text)]);
end;

procedure TMainForm.AZFClick(Sender: TObject);
begin
 if not Updating then begin
   Updating:=true;
   if (Sender<>AZF) then AZF.Checked:=true;
   AziF.Checked:=AZF.Checked;
   Azi1.Text   :=Az1.Text;
   Azi2.Text   :=Az2.Text;
   Updating:=false;
 end;
 UpdateControls(Sender);
end;

procedure TMainForm.AziFClick(Sender: TObject);
begin
 if not Updating then begin
   Updating:=true;
   if (Sender<>AziF) then AziF.Checked:=true;
   AzF.Checked:=AZiF.Checked;
   Az1.Text   :=Azi1.Text;
   Az2.Text   :=Azi2.Text;
   Updating:=false;
   UpdateControls(Sender);
 end;
end;

procedure TMainForm.ListSelectItem(Sender: TObject; Item: TListItem;
  Selected: Boolean);
begin
 if Selected and (InfoBox.Visible) then begin
   if Sender=List then
     InfoBox.ShowInfo(Kat1,Item.Data)
   else
     InfoBox.ShowInfo(Kat2,Item.Data);
   SetFocus;
 end;
 UpdateControls(Sender);
end;

procedure TMainForm.InfoBtnClick(Sender: TObject);
begin
 if (Pages.ActivePage=TabSheet1) and Assigned(List.Selected) then
   InfoBox.ShowInfo(Kat1,List.Selected.Data);
 if (Pages.ActivePage=TabSheet2) and Assigned(List2.Selected) then
   InfoBox.ShowInfo(Kat2,List2.Selected.Data);
end;

procedure TMainForm.ListKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
 if (Key=VK_DELETE) then begin DelBtnClick(Sender); Key:=0; end;
 if (Key=ord('F')) and (ssCtrl in Shift) then begin FindBtnClick(Sender); Key:=0; end;
 if (Key=ord('P')) and (ssCtrl in Shift) then begin PrintBtnClick(Sender); Key:=0; end;
end;

procedure TMainForm.DelBtnClick(Sender: TObject);
var Aux, S, Next:TListItem;
begin
 List.Items.BeginUpdate;
 try
   Aux:=nil;
   S:=List.Selected;
   while Assigned(S) do begin
     Aux:=List.GetNextItem(List.Selected,sdAll,[]);
     Next:=List.GetNextItem(S,sdAll,[isSelected]);
     S.Delete;
     S:=Next;
   end;
   if Assigned(Aux) then
     List.Selected:=Aux
   else if List.Items.Count>0 then
     List.Selected:=List.Items[List.Items.Count-1];
 finally
   List.Items.EndUpdate;
 end;
end;

procedure TMainForm.Del2BtnClick(Sender: TObject);
var Aux, S, Next:TListItem;
begin
 List2.Items.BeginUpdate;
 try
   Aux:=nil;
   S:=List2.Selected;
   while Assigned(S) do begin
     Aux:=List2.GetNextItem(List2.Selected,sdAll,[]);
     Next:=List2.GetNextItem(S,sdAll,[isSelected]);
     S.Delete;
     S:=Next;
   end;
   if Assigned(Aux) then
     List2.Selected:=Aux
   else if List2.Items.Count>0 then
     List2.Selected:=List2.Items[List2.Items.Count-1];
 finally
   List2.Items.EndUpdate;
 end;
end;

procedure TMainForm.PrintBtnClick(Sender: TObject);
begin
 if List.Items.Count=0 then
   raise Exception.Create('Cannot print an empty table.');
 NahledDlg.Execute;
end;

procedure TMainForm.PopupClick(Sender: TObject);
begin
 Sort:=TMenuItem(Sender).Tag;
 SortChange(Sender);
end;

procedure TMainForm.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
begin
 SaveKonfig;
end;

Procedure TMainForm.LoadKonfig;
var i,w,y,m,d,y1,m1,d1,y2,m2,d2:integer; dt,dt1,dt2:TDateTime;
begin
 Updating:=true;
 try
   FirstRun:=not Ini.Load(ExtractFilePath(Application.ExeName)+'ephem.ini');
   Ini.OpenSec('EPHEM', true);
   if not FirstRun then begin
     { Main window position and size }
     Top   :=Ini.ReadInt('Main_Top');
     Left  :=Ini.ReadInt('Main_Left');
     Width :=Ini.ReadInt('Main_Width', 800);
     Height:=Ini.ReadInt('Main_Height', 550);
     { Info window position and size }
     InfoBox.Top   :=Ini.ReadInt('Info_Top');
     InfoBox.Left  :=Ini.ReadInt('Info_Left');
     InfoBox.Width :=Ini.ReadInt('Info_Width', 800);
     InfoBox.Height:=Ini.ReadInt('Info_Height', 550);
   end;
   { Date and time }
   KeepDate:=Ini.ReadBool('KeepDate');
   if KeepDate then begin
     y:=Ini.ReadInt('Date_Year');
     m:=Ini.ReadInt('Date_Month');
     d:=Ini.ReadInt('Date_Day');
     try
       dt:=EncodeDate(y, m, d);
       Date.DateTime:=dt;
     except
     end;
     y1:=Ini.ReadInt('StartDate_Year');
     m1:=Ini.ReadInt('StartDate_Month');
     d1:=Ini.ReadInt('StartDate_Day');
     y2:=Ini.ReadInt('EndDate_Year');
     m2:=Ini.ReadInt('EndDate_Month');
     d2:=Ini.ReadInt('EndDate_Day');
     try
       dt1:=EncodeDate(y1, m1, d1);
       dt2:=EncodeDate(y2, m2, d2);
       DTStart.DateTime:=dt1;
       DTEnd.DateTime:=dt2;
     except
     end;
   end;
   { Active page }
   Pages.ActivePageIndex:=Ini.ReadInt('Main_Page', 0);
   { Infobox active page }
   InfoBox.PageControl1.ActivePageIndex:=Ini.ReadInt('Info_API', 0);
   { Observer's location }
   Obs:=Ini.ReadStr('Obs', 'Brno');
   Lon:=Ini.ReadDouble('Lon', 16.6667);
   Lat:=Ini.ReadDouble('Lat', 49.2167);
   TimeZoneX:=Ini.ReadInt('TimeZone', 9999);
   Twilight:=Ini.ReadDouble('Twilight', 12);
   { Selected catalogs }
   with Cats do for i:=0 to Count-1 do
     Checked[i]:=Ini.ReadBool(Items[i], true);
   Cats2.ItemIndex:=Cats2.Items.IndexOf(Ini.ReadStr('Catalogue', LastCat));
   if (Cats2.ItemIndex<0) and (Cats2.Items.Count>0) then
     Cats2.ItemIndex:=0;
   Cats2Change(NIL);
   Cons2.ItemIndex:=Cons2.Items.IndexOf(Ini.ReadStr('Const', LastCons));
   if (Cons2.ItemIndex<0) and (Cons2.Items.Count>0) then
     Cons2.ItemIndex:=0;
   Cons2Change(NIL);
   Star2.ItemIndex:=Star2.Items.IndexOf(Ini.ReadStr('Star', LastStar));
   if (Star2.ItemIndex<0) and (Star2.Items.Count>0) then
     Star2.ItemIndex:=0;
   Star2Click(NIL);
   { Filters }
   MagF.Checked:=Ini.ReadBool('MagF');
   Mag1.Text   :=Format('%.1f',[min(99,max(0,Ini.ReadDouble('Mag1',0)))]);
   Mag2.Text   :=Format('%.1f',[min(99,max(0,Ini.ReadDouble('Mag2',99)))]);
   MinF.Checked:=Ini.ReadBool('MinF', True);
   FNight.Checked:=Ini.ReadBool('Night', True);
   FNight2.Checked:=FNight.Checked;
   TimeF.Checked:=MinF.Checked;
   Min1.Text   :=Format('%.1f',[min(24,max(0,Ini.ReadDouble('Min1',20)))]);
   Time1.Text  :=Min1.Text;
   Min2.Text   :=Format('%.1f',[min(24,max(0,Ini.ReadDouble('Min2',4)))]);
   Time2.Text  :=Min2.Text;
   AltF.Checked:=Ini.ReadBool('AltF', true);
   VysF.Checked:=AltF.Checked;
   Alt1.Text   :=IntToStr(min(90,max(-90,Ini.ReadInt('Alt1',15))));
   Vys1.Text   :=Alt1.Text;
   Alt2.Text   :=IntToStr(min(90,max(-90,Ini.ReadInt('Alt2',90))));
   Vys2.Text   :=Alt2.Text;
   RAF.Checked :=Ini.ReadBool('RAF');
   RA1.Text    :=Format('%.1f',[min(24,max(0,Ini.ReadDouble('RA1',0)))]);
   RA2.Text    :=Format('%.1f',[min(24,max(0,Ini.ReadDouble('RA2',24)))]);
   DecF.Checked:=Ini.ReadBool('DecF');
   Dec1.Text   :=IntToStr(min(90,max(-90,Ini.ReadInt('Dec1',-90))));
   Dec2.Text   :=IntToStr(min(90,max(-90,Ini.ReadInt('Dec2',90))));
   PtsF.Checked:=Ini.ReadBool('PtsF');
   Pts1.Text   :=IntToStr(min(99,max(0,Ini.ReadInt('Pts1',1))));
   Pts2.Text   :=IntToStr(min(99,max(0,Ini.ReadInt('Pts2',10))));
   ConF.Checked:=Ini.ReadBool('ConF');
   Con.Text    :=Ini.ReadStr('Cons');
   TypF.Checked:=Ini.ReadBool('TypF');
   Typ.Text    :=Ini.ReadStr('Types');
   AZF.Checked :=Ini.ReadBool('AZF');
   AziF.Checked:=AzF.Checked;
   AZ1.Text    :=Format('%.0f',[min(360,max(0,Ini.ReadDouble('AZ1',0)))]);
   Azi1.Text   :=Az1.Text;
   AZ2.Text    :=Format('%.0f',[min(360,max(0,Ini.ReadDouble('AZ2',360)))]);
   Azi2.Text   :=Az2.Text;
   DOWF.Checked:=Ini.ReadBool('DOW');
   Mon.Checked :=Ini.ReadBool('Monday');
   Tue.Checked :=Ini.ReadBool('Tuesday');
   Wed.Checked :=Ini.ReadBool('Wednesday');
   Thu.Checked :=Ini.ReadBool('Thursday');
   Fri.Checked :=Ini.ReadBool('Friday');
   Sat.Checked :=Ini.ReadBool('Saturday');
   Sun.Checked :=Ini.ReadBool('Sunday');
   OMF.Checked :=Ini.ReadBool('OMF');
   OM1.Text    :=Format('%.0f',[min(180,max(0,Ini.ReadDouble('OM1',0)))]);
   ObjMF.Checked:=OMF.Checked;
   ObjM1.Text  :=OM1.Text;
   { Directories }
   LastDir    :=Ini.ReadStr('LastDir', ExtractFileDir(Application.ExeName));
   SaveDialog.InitialDir := LastDir;
   LastFormat :=Ini.ReadInt('LastFormat');
   SaveDialog.FilterIndex:= LastFormat;
   { Sort modes }
   Sort       :=Ini.ReadInt('Sort');
   Sort2      :=Ini.ReadInt('Sort2');
   { Column widths }
   Ini.OpenSec('List1', true);
   W:=Ini.ReadInt('Column1.Width') + Ini.ReadInt('Column2.Width');
   if W>0 then
     List.Columns[0].Width:=W;
   for i:=1 to List.Columns.Count-1 do begin
     W:=Ini.ReadInt(Format('Column%d.Width', [i+2]));
     if W>0 then
       List.Columns[i].Width:=W;
   end;
   Ini.OpenSec('List2', true);
   for i:=0 to List2.Columns.Count-1 do begin
     W:=Ini.ReadInt(Format('Column%d.Width', [i+1]));
     if W>0 then
       List2.Columns[i].Width:=W;
   end;
 finally
   Updating:=false;
 end;
end;

Procedure TMainForm.SaveKonfig;
var i:integer; y,m,d:word;
begin
 Ini.Clear;
 Ini.OpenSec('EPHEM',true);
 { Main window position and size }
 Ini.WriteInt('Main_Top',Top);
 Ini.WriteInt('Main_Left',Left);
 Ini.WriteInt('Main_Width',Width);
 Ini.WriteInt('Main_Height',Height);
 { Active page }
 Ini.WriteInt('Main_Page', Pages.ActivePageIndex);
 { Info window position and size }
 Ini.WriteInt('Info_Top',InfoBox.Top);
 Ini.WriteInt('Info_Left',InfoBox.Left);
 Ini.WriteInt('Info_Width',InfoBox.Width);
 Ini.WriteInt('Info_Height',InfoBox.Height);
 { Info active page }
 Ini.WriteInt('Info_API', InfoBox.PageControl1.ActivePageIndex);
 { Date and time }
 Ini.WriteBool('KeepDate', KeepDate);
 DecodeDate(Date.DateTime, y, m, d);
 Ini.WriteInt('Date_Year', y);
 Ini.WriteInt('Date_Month', m);
 Ini.WriteInt('Date_Day', d);
 DecodeDate(DTStart.DateTime, y, m, d);
 Ini.WriteInt('StartDate_Year', y);
 Ini.WriteInt('StartDate_Month', m);
 Ini.WriteInt('StartDate_Day', d);
 DecodeDate(DTEnd.DateTime, y, m, d);
 Ini.WriteInt('EndDate_Year', y);
 Ini.WriteInt('EndDate_Month', m);
 Ini.WriteInt('EndDate_Day', d);
 { Observer's location }
 Ini.WriteStr('Obs',Obs);
 Ini.WriteDouble('Lon',Lon,4);
 Ini.WriteDouble('Lat',Lat,4);
 Ini.WriteInt('TimeZone', TimeZoneX);
 Ini.WriteDouble('Twilight', Twilight, 0);
 { Selected catalogs }
 with Cats do for i:=0 to Count-1 do
   Ini.WriteBool(Items[i], Checked[i]);
 Ini.WriteStr('Catalogue', Cats2.Text);
 Ini.WriteStr('Const', Cons2.Text);
 if Star2.ItemIndex>=0 then
   Ini.WriteStr('Star', Star2.Items[Star2.ItemIndex]);
 { Filters }
 Ini.WriteBool('MagF',MagF.Checked);
 Ini.WriteStr ('Mag1',Mag1.Text);
 Ini.WriteStr ('Mag2',Mag2.Text);
 Ini.WriteBool('MinF',MinF.Checked);
 Ini.WriteStr ('Min1',Min1.Text);
 Ini.WriteStr ('Min2',Min2.Text);
 Ini.WriteBool('Night',FNight.Checked);
 Ini.WriteBool('AltF',AltF.Checked);
 Ini.WriteStr ('Alt1',Alt1.Text);
 Ini.WriteStr ('Alt2',Alt2.Text);
 Ini.WriteBool('RAF',RAF.Checked);
 Ini.WriteStr ('RA1',RA1.Text);
 Ini.WriteStr ('RA2',RA2.Text);
 Ini.WriteBool('DecF',DecF.Checked);
 Ini.WriteStr ('Dec1',Dec1.Text);
 Ini.WriteStr ('Dec2',Dec2.Text);
 Ini.WriteBool('PtsF',PtsF.Checked);
 Ini.WriteStr ('Pts1',Pts1.Text);
 Ini.WriteStr ('Pts2',Pts2.Text);
 Ini.WriteBool('ConF', ConF.Checked);
 Ini.WriteStr ('Cons', Con.Text);
 Ini.WriteBool('TypF', TypF.Checked);
 Ini.WriteStr ('Types', Typ.Text);
 Ini.WriteBool('AzF',AzF.Checked);
 Ini.WriteStr ('Az1',Az1.Text);
 Ini.WriteStr ('Az2',Az2.Text);
 Ini.WriteBool('DOW',DOWF.Checked);
 Ini.WriteBool('Monday',Mon.Checked);
 Ini.WriteBool('Tuesday',Tue.Checked);
 Ini.WriteBool('Wednesday',Wed.Checked);
 Ini.WriteBool('Thursday',Thu.Checked);
 Ini.WriteBool('Friday',Fri.Checked);
 Ini.WriteBool('Saturday',Sat.Checked);
 Ini.WriteBool('Sunday',Sun.Checked);
 Ini.WriteBool('OMF',OMF.Checked);
 Ini.WriteStr ('OM1',OM1.Text);
 { Directories }
 Ini.WriteStr('LastDir',LastDir);
 Ini.WriteInt('LastFormat', LastFormat);
 { Sort mode }
 Ini.WriteInt('Sort', Sort);
 Ini.WriteInt('Sort2', Sort2);
 { Column widths }
 Ini.OpenSec('List1', true);
 Ini.WriteInt('Column1.Width', List.Columns[0].Width);
 Ini.WriteInt('Column2.Width', 0);
 for i:=1 to List.Columns.Count-1 do
   Ini.WriteInt(Format('Column%d.Width', [i+2]), List.Columns[i].Width);
 Ini.OpenSec('List2', true);
 for i:=0 to List2.Columns.Count-1 do
   Ini.WriteInt(Format('Column%d.Width', [i+1]),List2.Columns[i].Width);
 Ini.Save;
end;

procedure TMainForm.FormDestroy(Sender: TObject);
begin
 Ini.Free;
end;

Procedure TMainForm.Print1;
var i:integer;

 Procedure Description;
 var C:String; JD,TSet,TRise,TStart,TEnd,Phase:double;
 begin
   // Popis filtru
   P.LineFeed;
   with FFilter1 do begin
     JD:=FromLocalTime(ceil(DateFrom), TimeZoneX);
     P.Writeln(Format('Search period from %s UT to %s UT', [FormatDateTime('dddd, dd mmmm yyyy h:nn', JDToDateTime(JDMin)),
       FormatDateTime('dddd, dd mmmm yyyy h:nn', JDToDateTime(JDMax))]));
     P.Writeln(Format('Observing site: %s, %.4f %s, %.4f %s', [Location,
       Lon, ifthen(Lon>=0,'E','W'), Lat, ifthen(Lat>=0,'N','S')]));
     SunTwilight(JD,Lon,Lat,Twilight,TimeZoneX,TSet,TRise,TEnd,TStart);
     if (tend>0) and (tstart>0) then begin
       P.Writeln(Format('Twilight ends at %s UT and starts at %s UT (Solar elevation angle below -%.0f deg.)', [
         FormatDateTime('h:nn',JDToDateTime(tend)), FormatDateTime('h:nn',JDToDateTime(tstart)), Twilight]));
     end;
     Phase:=MoonPhase(JD);
     MoonRiseSet(JD,Lon,Lat,TimeZoneX,TRise,TSet);
     C:=Format('Lunar phase: %s, illumination of disk: %s',[FormatLunarPhase(Phase), FormatLunarIllumination(Phase)]);
     if (trise>0) and (trise>=JDMin) and (trise<=JDMax) then
         C:=C+', rises at '+FormatDateTime('h:nn',JDToDateTime(trise))+' UT';
     if (tset>0) and (tset>=JDMin) and (tset<=JDMax) then
         C:=C+', sets at '+FormatDateTime('h:nn',JDToDateTime(tset))+' UT';
     P.Writeln(C);
     if FTime then begin
       if not FNight then
         P.Writeln(Format('Time of minimum from %.1f to %.1f UT', [TimeFrom, TimeTo]))
       else
         P.Writeln(Format('Time of minimum during nighttime (see twilight start and end above)', [Twilight]));
     end;
     if FAlt then
       P.Writeln(Format('Altitude from %.0f to %.0f deg.', [AltFrom, AltTo]));
     if FAz then
       P.Writeln(Format('Azimuth from %.0f to %.0f deg.', [AzFrom, AzTo]));
     if FRA then
       P.Writeln(Format('Right ascension from %.1f to %.1f hr.', [RaFrom, RaTo]));
     if FDec then
       P.Writeln(Format('Declination from %.0f to %.0f deg.', [DecFrom, DecTo]));
     if FMag then
       P.Writeln(Format('Brightness in minimum from %.1f to %.1f mag', [MagFrom, MagTo]));
     if FPts then
       P.Writeln(Format('Rating from %d to %d pts.', [PtsFrom, PtsTo]));
     if FCon then
       P.Writeln(Format('Constellations: %s', [Cons]));
     if FTyp then
       P.Writeln(Format('Variablity types: %s', [Types]));
     if FObjMoon then
       P.Writeln(Format('Object-Moon distance from %.0f deg.', [ObjMoon]));
   end;
   // Pocet nalezenych zaznamu
   P.LineFeed;
   if Records1>1 then begin
     if Variables1=1 then C:='1 variable star' else C:=Format('%d variable stars',[Variables1]);
     P.Writeln(Format('%d records found (%s)', [Records1,C]));
   end else if Records1=1 then
     P.Writeln('1 record found (1 variable star)')
   else
     P.Writeln('No records found');
   P.LineFeed;
 end;

 Procedure TableHeader;
 begin
   P.TableBegin(alignLeft, 150, 50);
   P.TableLine(10);
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('GSC 99999.999999')); { Promenna }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('9999-99-99m'), alignCenter); { Date of minimum }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('Timem'), alignCenter); { Time of minimum }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('Az.mm'), alignCenter); { Azimut }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('Alt.mm'), alignCenter); { Vyska }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('XX:XX:XX'), alignCenter); { R.A. }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('+XX:XX:XX'), alignCenter); { Dec. }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('EW/KW/RS P=XX.X dmmm')); { Typ }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('1X.X-1X.Xm'), alignCenter); { Jasnost }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('BRKA (H)mm'), alignCenter); { Katalog }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('Rat.m'), alignCenter); { Body }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('Obj-Moonm'), alignCenter); { Mesic faze }
   P.TableAddDiv(10);
   P.TableLine(10);
   { Zahlavi tabulky }
   P.Font.Style:=[fsBold];
   P.TableRowBegin;
   P.TableCellBegin; P.Write('Name');
   P.TableCellBegin; P.Write('Date');
   P.TableCellBegin; P.Write('UT');
   P.TableCellBegin; P.Write('Az.');
   P.TableCellBegin; P.Write('Alt.');
   P.TableCellBegin; P.Write('R.A.');
   P.TableCellBegin; P.Write('Dec.');
   P.TableCellBegin; P.Write('Type');
   P.TableCellBegin; P.Write('Mag.');
   P.TableCellBegin; P.Write('Catalogue');
   P.TableCellBegin; P.Write('Rat.');
   P.TableCellBegin; P.Write('Obj-Moon');
   P.TableRowEnd;
   P.TableLine(10);
   { Data tabulky }
   P.Font.Style:=[];
 end;

  Procedure TableRow(R:TEphemRec);
  begin
   P.TableCellBegin;
   P.Write(R.LongName);
   P.TableCellBegin;
   P.Write(FormatDateTime('yyyy-mm-dd',JDToDateTime(R.JD)));
   P.TableCellBegin;
   P.Write(Format('%.1f',[round(frac(R.JD+0.5)*24*2)/2]));
   P.TableCellBegin;
   P.Write(AzToStr(R.ObjA));
   P.TableCellBegin;
   P.Write(Format('%.0f',[R.Objh]));
   P.TableCellBegin;
   P.Write(RaToStr(R.RA));
   P.TableCellBegin;
   P.Write(DecToStr(R.DEC));
   P.TableCellBegin;
   P.Write(R.Typ);
   P.TableCellBegin;
   P.Write(
     ifthen(R.mag1>-9,Format('%.1f',[R.Mag1]),'??')+'-'+
     ifthen(R.mag2>-9,Format('%.1f',[R.Mag2]),'??'));
   P.TableCellBegin;
   P.Write(R.Katalog);
   P.TableCellBegin;
   P.Write(IntToStr(R.Pts));
   P.TableCellBegin;
   P.Write(Format('%.0f°',[R.MoonD]));
  end;

begin
 P.DocClear;
 P.Header.Visible:=true;
 P.Header.Font.Size:=10; P.Header.Font.Style:=[fsBold];
 P.Header.LeftText:=FormatDateTime('yyyy-mm-dd', FFilter1.DateFrom);
 P.Header.CenterText:='';
 P.Header.RightText:='Page ##/#*';
 P.Header.Height:=round(P.GetLineHeight*1.5);
 P.Footer.Visible:=false;
 P.DocBegin;
 P.Font.Size:=12; P.Font.Style:=[fsBold];
 P.Writeln('Daily ephemerides for '+FormatDateTime('dd mmmm yyyy', FFilter1.DateFrom));
 P.Font.Size:=8; P.Font.Style:=[];
 Description;
 TableHeader;
 with List.Items do for i:=0 to Count-1 do begin
   if not P.IsSpace(P.Table.RowHeight+100) then begin
     P.TableEnd;
     P.NewPage;
     TableHeader;
   end;
   P.TableRowBegin;
   TableRow(List.Items[i].Data);
   P.TableRowEnd;
   P.TableLine(10);
 end;
 P.TableLine(10);
 P.TableEnd;
 P.DocEnd;
end;

procedure TMainForm.SunBtnClick(Sender: TObject);
begin
 SunDlg.Execute(FromLocalTime(ceil(FFilter1.DateFrom),TimeZoneX),Lon,Lat,Twilight,TimeZoneX);
end;

procedure TMainForm.MoonBtnClick(Sender: TObject);
begin
 MoonDlg.Execute(FromLocalTime(ceil(FFilter1.DateFrom),TimeZoneX),Lon,Lat,TimeZoneX);
end;

procedure TMainForm.PagesChange(Sender: TObject);
begin
 if Pages.ActivePage=TabSheet2 then begin
   Kat2.Clear;
   Kat2.Load(Cats2.Name);
   Cats2Change(Sender);
 end;
 UpdateStatus;
end;

Procedure TMainForm.Proc2;
var DOW:word;
begin
 DOW:=LocalDateTimeToDOW(ToLocalTime(ARec.JD,TimeZoneX));
 if (not FFilter2.FDOW or FFilter2.DOW[DOW]) then begin
   with List2.Items.Add do begin
     Caption:=FormatDateTime('yyyy-mm-dd', JDToDateTime(ARec.JD));
     SubItems.Add(Format('%.1f',[round(frac(ARec.JD+0.5)*24*2)/2]));
     SubItems.Add(Format('%s/%s', [ShortDayNames[DOW], ShortDayNames[((DOW+7) mod 7)+1]]));
     SubItems.Add(Format('%.3f',[ARec.JD]));
     SubItems.Add(Format('%d',[ARec.Epoch]));
     SubItems.Add(UpperCase(ARec.MinTyp));
     SubItems.Add(AzToStr(ARec.ObjA));
     SubItems.Add(Format('%.0f',[ARec.Objh]));
     SubItems.Add(Format('%.0f%%%s',[0.5*(1.0-cos(ARec.MoonP/180*pi))*100.0, ifthen(ARec.MoonP<180,'+','-')]));
     SubItems.Add(Format('%.0f°',[ARec.MoonD]));
     Data:=TEphemRec.CreateCopy(ARec);
   end;
 end;
end;

procedure TMainForm.Run2BtnClick(Sender: TObject);
var It:TKatZaznam; 
begin
 List.Items.BeginUpdate;
 Screen.Cursor:=crHourGlass;
 Records2:=0;
 try
   X:=0;
   List2.Clear;
   FFilter2.DateFrom:=int(DTStart.Date);
   FFilter2.DateTo:=int(DTEnd.Date);
   FFilter2.JDMin:=FromLocalTime(int(DTStart.Date)+0.5,TimeZoneX);   // Noon, first day
   FFilter2.JDMax:=FromLocalTime(int(DTEnd.Date)+0.5,TimeZoneX);     // Noon, last day
   UpdateFilter(FFilter2);
   if Star2.ItemIndex>=0 then
     if Kat2.Search(Star2.Items[Star2.ItemIndex], It) then begin
       StarName:=Star2.Items[Star2.ItemIndex];
       StarCat :=Kat2.CatName;
       Ephemeride(It, FFilter2.JDMin, FFilter2.JDMax, Lon, Lat, Twilight,
         TimeZoneX, FFilter2.FTime, FFilter2.FNight, FFilter2.TimeFrom, FFilter2.TimeTo,
         FFilter2.FAz, FFilter2.AzFrom, FFilter2.AzTo, FFilter2.FAlt,
         FFilter2.AltFrom, FFilter2.AltTo, FFilter2.FObjMoon, FFilter2.ObjMoon, Proc2);
     end;
   { Sort items }
   if List2.Items.Count>1 then
     List2.AlphaSort;
   { Update column widths }
   if AutoSize then
     UpdateColumnWidths(List2);
   { Update statistics }
   Records2:=List2.Items.Count;
 finally
   List.Items.EndUpdate;
   if List.Items.Count>0 then List.Selected:=List.Items[0];
   Screen.Cursor:=crDefault;
   AfterStart:=false;
   UpdateStatus;
   UpdateControls(Sender);
 end;
end;

Procedure TMainForm.Print2;
var i:integer;

 Procedure Description;
 begin
   // Popis filtru
   P.LineFeed;
   with FFilter2 do begin
     P.Writeln(Format('Search period from %s UT to %s UT', [FormatDateTime('dddd, dd mmmm yyyy h:nn', JDToDateTime(JDMin)),
       FormatDateTime('dddd, dd mmmm yyyy h:nn', JDToDateTime(JDMax))]));
     P.Writeln(Format('Observing site: %s, %.4f %s, %.4f %s', [Location,
       Lon, ifthen(Lon>=0,'E','W'), Lat, ifthen(Lat>=0,'N','S')]));
     if FTime then begin
       if not FNight then
         P.Writeln(Format('Time of minimum from %.1f to %.1f UT', [TimeFrom, TimeTo]))
       else
         P.Writeln(Format('Time of minimum during nighttime (Solar elevation below -%.0f deg.)', [Twilight]));
     end;
     if FDOW then
       P.Writeln(Format('Days of week: %s', [DOWToStr(DOW)]));
     if FAlt then
       P.Writeln(Format('Altitude from %.0f to %.0f deg.', [AltFrom, AltTo]));
     if FAz then
       P.Writeln(Format('Azimuth from %.0f to %.0f deg.', [AzFrom, AzTo]));
     if FObjMoon then
       P.Writeln(Format('Object-Moon distance from %.0f deg.', [ObjMoon]));
   end;
   // Pocet nalezenych zaznamu
   P.LineFeed;
   if Records2>1 then
     P.Writeln(Format('%d records found', [Records2]))
   else if Records2=1 then
     P.Writeln('1 record found (1 variable star)')
   else
     P.Writeln('No records found');
   P.LineFeed;
 end;

 Procedure TableHeader;
 begin
   P.TableBegin(alignLeft, 150, 50);
   P.TableLine(10);
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('9999-99-99m'), alignCenter); { Datum }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('Timem'), alignCenter); { Cas }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('Day of weeknn'), alignCenter); { Den v tydnu }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('2499999.999n'), alignCenter); { JD }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('Epochm'), alignCenter); { Epocha }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('PSm'), alignCenter); { Typ minima }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('Az.mm'), alignCenter); { Azimut }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('Alt.mm'), alignCenter); { Vyska }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('100%+'), alignCenter); { Mesic faze }
   P.TableAddDiv(10);
   P.TableAddCol(P.GetTextWidth('Obj-Moonm'), alignCenter); { Mesic vzdalenost }
   P.TableAddDiv(10);
   P.TableLine(10);
   { Zahlavi tabulky }
   P.Font.Style:=[fsBold];
   P.TableRowBegin;
   P.TableCellBegin; P.Write('Date');
   P.TableCellBegin; P.Write('UT');
   P.TableCellBegin; P.Write('Day of week');
   P.TableCellBegin; P.Write('Julian date');
   P.TableCellBegin; P.Write('Epoch');
   P.TableCellBegin; P.Write('PS');
   P.TableCellBegin; P.Write('Az.');
   P.TableCellBegin; P.Write('Alt.');
   P.TableCellBegin; P.Write('Moon');
   P.TableCellBegin; P.Write('Obj-Moon');
   P.TableRowEnd;
   P.TableLine(10);
   { Data tabulky }
   P.Font.Style:=[];
 end;

  Procedure TableRow(R:TEphemRec);
  var DOW:word;
  begin
   P.TableCellBegin;
   P.Write(FormatDateTime('yyyy-mm-dd', JDToDateTime(R.JD)));
   P.TableCellBegin;
   P.Write(Format('%.1f',[round(frac(R.JD+0.5)*24*2)/2]));
   P.TableCellBegin;
   DOW:=LocalDateTimeToDOW(ToLocalTime(R.JD,TimeZoneX));
   P.Write(Format('%s/%s', [ShortDayNames[DOW], ShortDayNames[((DOW+7) mod 7)+1]]));
   P.TableCellBegin;
   P.Write(Format('%.3f',[R.JD]));
   P.TableCellBegin;
   P.Write(Format('%d',[R.Epoch]));
   P.TableCellBegin;
   P.Write(UpperCase(R.MinTyp));
   P.TableCellBegin;
   P.Write(AzToStr(R.ObjA));
   P.TableCellBegin;
   P.Write(Format('%.0f',[R.Objh]));
   P.TableCellBegin;
   P.Write(Format('%.0f%%%s',[0.5*(1.0-cos(R.MoonP/180*pi))*100.0, ifthen(R.MoonP<180,'+','-')]));
   P.TableCellBegin;
   P.Write(Format('%.0f°',[R.MoonD]));
  end;

begin
 P.DocClear;
 P.Header.Visible:=true;
 P.Header.Font.Size:=10; P.Header.Font.Style:=[fsBold];
 P.Header.LeftText:=StarName+' ('+StarCat+')';
 P.Header.CenterText:='';
 P.Header.RightText:='Page ##/#*';
 P.Header.Height:=round(P.GetLineHeight*1.5);
 P.Footer.Visible:=false;
 P.DocBegin;
 P.Font.Size:=12; P.Font.Style:=[fsBold];
 P.Writeln('Star ephemerides for '+StarName+' ('+StarCat+')');
 P.Font.Size:=8; P.Font.Style:=[];
 Description;
 TableHeader;
 with List2.Items do for i:=0 to Count-1 do begin
   if not P.IsSpace(P.Table.RowHeight+100) then begin
     P.TableEnd;
     P.NewPage;
     TableHeader;
   end;
   P.TableRowBegin;
   TableRow(TEphemRec(List2.Items[i].Data));
   P.TableRowEnd;
   P.TableLine(10);
 end;
 P.TableLine(10);
 P.TableEnd;
 P.DocEnd;
end;

Procedure TMainForm.Print;
begin
 if Pages.ActivePage=TabSheet1 then Print1(P)
 else Print2(P);
end;

procedure TMainForm.Star2Click(Sender: TObject);
begin
 if Star2.ItemIndex>=0 then
   LastStar:=Star2.Items[Star2.ItemIndex]
 else
   LastStar:='';
 UpdateControls(Sender);
end;

procedure TMainForm.List2Compare(Sender: TObject; Item1, Item2: TListItem;
  Data: Integer; var Compare: Integer);
var Value1, Value2:double;
begin
 case Sort2 of
   1: begin
       Value1:=frac(ToLocalTime(TEphemRec(Item1.Data).JD, TimeZoneX));
       Value2:=frac(ToLocalTime(TEphemRec(Item2.Data).JD, TimeZoneX));
      end;
   2: begin
       Value1:=LocalDateTimeToDOW(ToLocalTime(TEphemRec(Item1.Data).JD, TimeZoneX));
       Value2:=LocalDateTimeToDOW(ToLocalTime(TEphemRec(Item2.Data).JD, TimeZoneX));
      end;
   6: begin
       Value1:=TEphemRec(Item1.Data).ObjA;
       Value2:=TEphemRec(Item2.Data).ObjA;
      end;
   7: begin
       Value1:=-TEphemRec(Item1.Data).Objh;
       Value2:=-TEphemRec(Item2.Data).Objh;
      end;
   8: begin
       Value1:=1.0-cos(TEphemRec(Item1.Data).MoonP/180*pi);
       Value2:=1.0-cos(TEphemRec(Item2.Data).MoonP/180*pi);
      end;
   9: begin
       Value1:=-TEphemRec(Item1.Data).MoonD;
       Value2:=-TEphemRec(Item2.Data).MoonD;
      end;
   else begin
       Value1:=TEphemRec(Item1.Data).JD;
       Value2:=TEphemRec(Item2.Data).JD;
   end;
 end;
 if (Value1<Value2) then Compare:=-1
 else if (Value1>Value2) then Compare:=1
 else Compare:=0;
end;

procedure TMainForm.Sort2MenuPopup(Sender: TObject);
begin
 case Sort2 of
   1: begin
       MenuItem2.Checked:=True;
      end;
   2: begin
       MenuItem5.Checked:=True;
      end;
   6: begin
       MenuItem3.Checked:=True;
      end;
   7: begin
       MenuItem4.Checked:=True;
      end;
   8: begin
       Sortbylunarillumination1.Checked:=True;
      end;
   9: begin
       Sortbylunardistance1.Checked:=True;
      end;
   else begin
       MenuItem1.Checked:=True;
      end;
 end;
end;

procedure TMainForm.List2ColumnClick(Sender: TObject; Column: TListColumn);
begin
 Sort2:=Column.Index;
 Sort2Change(Sender);
end;

Procedure TMainForm.Sort2Change(Sender:TObject);
begin
 List2.AlphaSort;
 if Assigned(List2.Selected) then List2.Selected.MakeVisible(false);
end;

procedure TMainForm.MenuItem4Click(Sender: TObject);
begin
 Sort2:=TMenuItem(Sender).Tag;
 Sort2Change(Sender);
end;

procedure TMainForm.FormActivate(Sender: TObject);
begin
 OnActivate:=NIL;
 LoadKonfig;
 UpdateStatus;
 UpdateControls(Sender);
 if FirstRun then begin
   SetupDlg.Execute(Obs, Lon, Lat, Twilight, TimeZoneX, KeepDate);
   SaveKonfig;
   UpdateStatus;
   UpdateControls(Sender);
 end;
end;

procedure TMainForm.Sun2BtnClick(Sender: TObject);
begin
 if Assigned(List2.Selected) then begin
   SunDlg.Execute(TEphemRec(List2.Selected.Data).JD,Lon,Lat,Twilight,TimeZoneX);
 end;
end;

procedure TMainForm.Moon2BtnClick(Sender: TObject);
begin
 if Assigned(List2.Selected) then begin
   MoonDlg.Execute(TEphemRec(List2.Selected.Data).JD,Lon,Lat,TimeZoneX);
 end;
end;

procedure TMainForm.SkyBtnClick(Sender: TObject);
var F:TEphemRec;
begin
 if Assigned(List.Selected) then begin
   F:=TEphemRec(List.Selected.Data);
   SkyDlg.Execute(F.LongName,F.JD,F.RA,F.DEC);
 end;
end;

procedure TMainForm.Sky2BtnClick(Sender: TObject);
var It:TKatZaznam; JD:double;
begin
 if (Star2.ItemIndex>=0) and Kat2.Search(Star2.Items[Star2.ItemIndex], It) then begin
   if Assigned(List2.Selected) then
       JD:=TEphemRec(List2.Selected.Data).JD
   else
       JD:=FromLocalTime(ceil(DTStart.Date),TimeZoneX);
   SkyDlg.Execute(It.LongName,JD,It.RA,It.DEC);
 end;
end;

procedure TMainForm.HelpBtnClick(Sender: TObject);
begin
 if (Sender=MHelpEn) then
   ExecuteApp('hh.exe','help-en.chm')
 else if (Sender=MHelpCs) then
   ExecuteApp('hh.exe','help-cs.chm');
end;

procedure TMainForm.WMHelp(var Message: TWMHelp);
{ Toto je prevzaty kod z jednotky Forms. Musel jsem to predefinovat kvuli nove
  napovede aby fungovala na F1. Vsechna okna musi mit v BorderIcons
  povoleno biHelp }

  function GetMenuHelpContext(Menu: TMenu): Integer;
  begin
    Result := 0;
    if Menu = nil then Exit;
    Result := Menu.GetHelpContext(Message.HelpInfo.iCtrlID, True);
    if Result = 0 then
      Result := Menu.GetHelpContext(Message.HelpInfo.hItemHandle, False);
  end;

  function ControlHasHelp(const Control: TWinControl) : Boolean;
  begin
    Result := false;
    if (Control.HelpType = htContext) and (Control.HelpContext <> 0)
      then Result := true
    else if (Control.HelpType = htKeyword) and (Control.HelpKeyword <> '') then
      Result := true;
  end;

  procedure GetHelpInfo(const Control: TWinControl; var HType: THelpType; var ContextID: Integer; var Keyword: String);
  begin
    if Control.HelpType = htContext then
    begin
      HType := htContext;
      ContextID := Control.HelpContext;
    end else
    begin
      HType := htKeyword;
      Keyword := Control.HelpKeyword;
    end;
  end;

var
  Control: TWinControl;
  ContextID: Integer;
  HType: THelpType;
  Keyword: String;
  Pt: TSmallPoint;
begin
 with Message.HelpInfo^ do
  begin
    if iContextType = HELPINFO_WINDOW then
    begin
      Control := FindControl(hItemHandle);
      while (Control <> nil) and ( not ControlHasHelp(Control)) do
        Control := Control.Parent;
      if Control = nil then Exit;
      GetHelpInfo(Control, HType, ContextID, Keyword);
      Pt := PointToSmallPoint(Control.ClientToScreen(Point(0, 0)));
    end
    else  { Message.HelpInfo.iContextType = HELPINFO_MENUITEM }
    begin
      HType := htContext;
      ContextID := GetMenuHelpContext(Menu);
      if ContextID = 0 then
        ContextID := GetMenuHelpContext(PopupMenu);
      Pt := PointToSmallPoint(ClientToScreen(Point(0,0)));
    end;
  end;
  if HType = htContext then begin
    Application.HelpCommand(HELP_FINDER, ContextID);
  end;
end;

function TMainForm.NasHelp(Command: Word; Data: Longint; var CallHelp: Boolean): Boolean;
{Místo jakéhokoliv PopUp helpu vyvolá klasické velké okno s tímtéž kontextem.}
begin
 if (Command=8) then begin
   ExecuteApp('hh.exe',Format('-mapid %d %s',[Data,'ephem.chm']));
   CallHelp:=false; Result:=true;
 end else
   Result:=false;
end;

procedure TMainForm.ObserverBtnClick(Sender: TObject);
begin
 SetupDlg.Execute(Obs,Lon,Lat,Twilight,TimeZoneX,KeepDate);
 SaveKonfig;
 UpdateStatus;
end;

procedure TMainForm.MagDownClick(Sender: TObject);
var X:Double;
begin
 if Assigned(TSpinButton(Sender).FocusControl) then begin
   X:=StrToFloatDef(TEdit(TSpinButton(Sender).FocusControl).Text,0);
   X:=max(0,X-0.5);
   TEdit(TSpinButton(Sender).FocusControl).Text:=Format('%.1f',[X]);
 end;
end;

procedure TMainForm.MagUpClick(Sender: TObject);
var X:Double;
begin
 if Assigned(TSpinButton(Sender).FocusControl) then begin
   X:=StrToFloatDef(TEdit(TSpinButton(Sender).FocusControl).Text,0);
   X:=min(99,X+0.5);
   TEdit(TSpinButton(Sender).FocusControl).Text:=Format('%.1f',[X]);
 end;
end;

procedure TMainForm.Mag1Exit(Sender: TObject);
begin
 TEdit(Sender).Text:=Format('%.1f',[min(99,max(0,StrToFloatDef(TEdit(Sender).Text,0)))]);
end;

procedure TMainForm.MinDownClick(Sender: TObject);
var X:double;
begin
 if Assigned(TSpinButton(Sender).FocusControl) then begin
   X:=StrToFloatDef(TEdit(TSpinButton(Sender).FocusControl).Text,0);
   X:=max(0,X-0.5);
   TEdit(TSpinButton(Sender).FocusControl).Text:=Format('%.1f',[X]);
 end;
end;

procedure TMainForm.MinUpClick(Sender: TObject);
var X:double;
begin
 if Assigned(TSpinButton(Sender).FocusControl) then begin
   X:=StrToFloatDef(TEdit(TSpinButton(Sender).FocusControl).Text,0);
   X:=min(24,X+0.5);
   TEdit(TSpinButton(Sender).FocusControl).Text:=Format('%.1f',[X]);
 end;
end;

procedure TMainForm.Min2Exit(Sender: TObject);
begin
 TEdit(Sender).Text:=Format('%.1f',[min(24,max(0,StrToFloatDef(TEdit(Sender).Text,0)))]);
end;

procedure TMainForm.AltDownClick(Sender: TObject);
var X:integer;
begin
 if Assigned(TSpinButton(Sender).FocusControl) then begin
   X:=StrToIntDef(TEdit(TSpinButton(Sender).FocusControl).Text,0);
   X:=max(-90,X-1);
   TEdit(TSpinButton(Sender).FocusControl).Text:=IntToStr(X);
 end;
end;

procedure TMainForm.AltUpClick(Sender: TObject);
var X:integer;
begin
 if Assigned(TSpinButton(Sender).FocusControl) then begin
   X:=StrToIntDef(TEdit(TSpinButton(Sender).FocusControl).Text,0);
   X:=min(90,X+1);
   TEdit(TSpinButton(Sender).FocusControl).Text:=IntToStr(X);
 end;
end;

procedure TMainForm.Alt2Exit(Sender: TObject);
begin
 TEdit(Sender).Text:=IntToStr(min(90,max(-90,StrToIntDef(TEdit(Sender).Text,0))));
end;

procedure TMainForm.Print2BtnClick(Sender: TObject);
begin
 if (Star2.ItemIndex<=0) and (List2.Items.Count=0) then
   raise Exception.Create('Cannot print an empty table.');
 NahledDlg.Execute;
end;

procedure TMainForm.Find2BtnClick(Sender: TObject);
begin
 with FindDialog do begin
   OnFind:=Find2;
   if Assigned(List2.Selected) then StartR:=List2.Selected.Index else StartR:=0;
   StartC:=-1;
   Execute;
 end
end;

procedure TMainForm.Find2(Sender: TObject);
{ Hledani textu v prehledu }
var C, R: Integer;
    Nenasel: boolean;
    CoHledat: String;
    Item:TListItem;

  Function Zkus(Item:TListItem; Index:integer):boolean;
  var KdeHledat:String;
  begin
   if Index<0 then
     KdeHledat:=Item.Caption
   else
     KdeHledat:=Item.SubItems[Index];
   if not (frMatchCase in FindDialog.Options) then
     KdeHledat:=AnsiUpperCase(KdeHledat);
   if (frWholeWord in FindDialog.Options) then
     Result:=CompareStr(CoHledat, KdeHledat)=0
   else
     Result:=(Pos(CoHledat, KdeHledat)>0);
  end;

  function Dalsi(var Item:TListItem; var Row, Col:integer):boolean;
  begin
   if frDown in FindDialog.Options then begin
     inc(Col);
     if Col>=Item.SubItems.Count then begin
       Col:=-1; inc(Row);
       if (Row>=List2.Items.Count) then Row:=0;
       Item:=List2.Items[Row];
     end;
     Result:=true;
   end else begin
     dec(Col);
     if Col<-1 then begin
       dec(Row);
       if (Row<0) then Row:=List2.Items.Count-1;
       Item:=List2.Items[Row];
       Col:=Item.SubItems.Count-1;
     end;
     Result:=true;
   end;
   if (Row=StartR) and (Col=StartC) then
     Result:=false;
  end;

begin
 CoHledat:=FindDialog.FindText;
 if not (frMatchCase in FindDialog.Options) then CoHledat:=AnsiUpperCase(CoHledat);
 C:=StartC; R:=StartR; Nenasel:=true; Item:=List2.Items[R];
 if (Item<>NIL) then begin
   while Nenasel and Dalsi(Item, R, C) do begin
      Nenasel:=not Zkus(Item, C);
   end;
   // Zkusit jeste startovni bunku
   if Nenasel then
     Nenasel:=not Zkus(Item, C);
 end;
 if Nenasel then
   MessageDlg(Format('Search string ''%s'' was not found.',[CoHledat]),mtInformation,[mbOK],0)
 else begin
   StartR:=R; StartC:=C;
   List2.Selected:=Item;
 end;
end;

procedure TMainForm.FindBtnClick(Sender: TObject);
begin
 with FindDialog do begin
   OnFind:=Find1;
   if Assigned(List.Selected) then StartR:=List.Selected.Index else StartR:=0;
   StartC:=-1;
   Execute;
 end
end;

procedure TMainForm.Find1(Sender: TObject);
{ Hledani textu v prehledu }
var C, R: Integer;
    Nenasel: boolean;
    CoHledat: String;
    Item:TListItem;

  Function Zkus(Item:TListItem; Index:integer):boolean;
  var KdeHledat:String;
  begin
   if Index<0 then
     KdeHledat:=Item.Caption
   else
     KdeHledat:=Item.SubItems[Index];
   if not (frMatchCase in FindDialog.Options) then
     KdeHledat:=AnsiUpperCase(KdeHledat);
   if (frWholeWord in FindDialog.Options) then
     Result:=CompareStr(CoHledat, KdeHledat)=0
   else
     Result:=(Pos(CoHledat, KdeHledat)>0);
  end;

  function Dalsi(var Item:TListItem; var Row, Col:integer):boolean;
  begin
   if frDown in FindDialog.Options then begin
     inc(Col);
     if Col>=Item.SubItems.Count then begin
       Col:=-1; inc(Row);
       if (Row>=List.Items.Count) then Row:=0;
       Item:=List.Items[Row];
     end;
     Result:=true;
   end else begin
     dec(Col);
     if Col<-1 then begin
       dec(Row);
       if (Row<0) then Row:=List.Items.Count-1;
       Item:=List.Items[Row];
       Col:=Item.SubItems.Count-1;
     end;
     Result:=true;
   end;
   if (Row=StartR) and (Col=StartC) then
     Result:=false;
  end;

begin
 CoHledat:=FindDialog.FindText;
 if not (frMatchCase in FindDialog.Options) then CoHledat:=AnsiUpperCase(CoHledat);
 C:=StartC; R:=StartR; Nenasel:=true; Item:=List.Items[R];
 if (Item<>NIL) then begin
   while Nenasel and Dalsi(Item, R, C) do begin
      Nenasel:=not Zkus(Item, C);
   end;
   // Zkusit jeste startovni bunku
   if Nenasel then
     Nenasel:=not Zkus(Item, C);
 end;
 if Nenasel then
   MessageDlg(Format('Search string ''%s'' was not found.',[FindDialog.FindText]),mtInformation,[mbOK],0)
 else begin
   StartR:=R; StartC:=C;
   List.Selected:=nil;
   if Assigned(Item) then begin
     List.Selected:=Item;
     Item.MakeVisible(false);
   end;
 end;
end;

procedure TMainForm.List2KeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
 if (Key=ord('F')) and (ssCtrl in Shift) then begin Find2BtnClick(Sender); Key:=0; end;
 if (Key=ord('P')) and (ssCtrl in Shift) then begin Print2BtnClick(Sender); Key:=0; end;
end;

procedure TMainForm.SaveBtnClick(Sender: TObject);
var ok:boolean;
    E:TExportEngine;
    F:TextFile;
    S, Title:String;
begin
 if List.Items.Count=0 then
   raise Exception.Create('Cannot export an empty table.');

 SaveDialog.InitialDir:=LastDir;
 SaveDialog.FileName:=CheckFileName(FormatDateTime('yyyy-mm-dd', FFilter1.DateFrom));
 if SaveDialog.Execute then begin
   LastDir:=ExtractFileDir(SaveDialog.FileName);
   LastFormat:=SaveDialog.FilterIndex;
   if FileExists(SaveDialog.FileName) then
     ok:=MessageDlg('File already exists. Do you want to replace it?', mtConfirmation, [mbYes, mbNo], 0)=mrYes
   else
     ok:=true;
   if ok then begin
     AssignFile(F, SaveDialog.FileName);
     Rewrite(F);
     try
       Title:='Daily ephemerides for '+FormatDateTime('dd mmmm yyyy', FFilter1.DateFrom);
       case (SaveDialog.FilterIndex) of
         1: E:=CreateExportEngine(xfTXT, Title, @S);
         2: E:=CreateExportEngine(xfCSV, Title, @S);
         3: E:=CreateExportEngine(xfHTML, Title, @S);
       else
         raise Exception.Create('Please, select a file format');
       end;
       try
         Export1(E);
       finally
         E.Free;
       end;
       Write(F, S);
     finally
       CloseFile(F);
     end;
   end;
 end;
end;

procedure TMainForm.CopyBtnClick(Sender: TObject);
var S, Title:String;
    E:TExportEngine;
begin
 if List.Items.Count=0 then
   raise Exception.Create('Cannot copy an empty table to the clipboard.');

 Title:='Daily ephemerides for '+FormatDateTime('dd mmmm yyyy', FFilter1.DateFrom);
 Clipboard.Open;
 try
   E:=CreateExportEngine(xfClipboard, Title, @S);
   try
     Export1(E);
   finally
     E.Free;
   end;
   Clipboard.Clear;
   Clipboard.AsText:=S;
 finally
   Clipboard.Close;
 end;
end;

Procedure TMainForm.Export1;
var i,j,col:integer; C:String; JD,TSet,TRise,TStart,TEnd,Phase:double;
begin
 // Nadpis
 E.SectBegin;
 E.Write('Daily ephemerides for '+FormatDateTime('dd mmmm yyyy', FFilter1.DateFrom));

 // Popis filtru
 E.ParBegin;
 with FFilter1 do begin
   JD:=FromLocalTime(ceil(DateFrom),TimeZoneX);
   E.Write(Format('Search period from %s UT to %s UT\n', [FormatDateTime('dddd, dd mmmm yyyy h:nn', JDToDateTime(JDMin)),
       FormatDateTime('dddd, dd mmmm yyyy h:nn', JDToDateTime(JDMax))]));
   E.Write(Format('Observing site: %s, %.4f %s, %.4f %s\n', [Location,
     Lon, ifthen(Lon>=0,'E','W'), Lat, ifthen(Lat>=0,'N','S')]));
   SunTwilight(JD,Lon,Lat,Twilight,TimeZoneX,TSet,TRise,TEnd,TStart);
   if (tend>0) and (tstart>0) then begin
     E.Write(Format('Twilight ends at %s UT and starts at %s UT (Solar elevation angle below -%.0f deg.)\n', [
       FormatDateTime('h:nn',JDToDateTime(tend)), FormatDateTime('h:nn',JDToDateTime(tstart)), Twilight]));
   end;
   Phase:=MoonPhase(JD);
   MoonRiseSet(JD,Lon,Lat,TimeZoneX,TRise,TSet);
   C:=Format('Lunar phase: %s, illumination of disk: %s',[FormatLunarPhase(Phase), FormatLunarIllumination(Phase)]);
   if (trise>0) and (trise>=JDMin) and (trise<=JDMax) then
       C:=C+', rises at '+FormatDateTime('h:nn',JDToDateTime(trise))+' UT';
   if (tset>0) and (tset>=JDMin) and (tset<=JDMax) then
       C:=C+', sets at '+FormatDateTime('h:nn',JDToDateTime(tset))+' UT';
   E.Write(C+'\n');
   if FTime then begin
     if not FNight then
       E.Write(Format('Time of minimum from %.1f to %.1f hr. UT\n', [TimeFrom, TimeTo]))
     else
       E.Write(Format('Time of minimum during nighttime (see twilight start and end above)\n', [Twilight]));
   end;
   if FAlt then
     E.Write(Format('Altitude from %.0f to %.0f deg.\n', [AltFrom, AltTo]));
   if FAz then
     E.Write(Format('Azimuth from %.0f to %.0f deg.\n', [AzFrom, AzTo]));
   if FRA then
     E.Write(Format('Right ascension from %.1f to %.1f hr.\n', [RaFrom, RaTo]));
   if FDec then
     E.Write(Format('Declination from %.0f to %.0f deg.\n', [DecFrom, DecTo]));
   if FMag then
     E.Write(Format('Brightness in minimum from %.1f to %.1f mag.\n', [MagFrom, MagTo]));
   if FPts then
     E.Write(Format('Rating from %d to %d pts.\n', [PtsFrom, PtsTo]));
   if FObjMoon then
     E.Write(Format('Moon-object distance from %1f deg.', [ObjMoon]));
 end;

 // Pocet nalezenych zaznamu
 E.ParBegin;
 if Records1>1 then begin
   if Variables1=1 then C:='1 variable star' else C:=Format('%d variable stars',[Variables1]);
   E.Write(Format('%d records found (%s)', [Records1,C]));
 end else if Records1=1 then
   E.Write('1 record found (1 variable star)')
 else
   E.Write('No records found');

 // Zahlavi tabulky
 E.TableBegin;
 for i:=0 to List.Columns.Count-1 do with List.Columns[i] do begin
   E.TableAddCol(Caption, alignCenter);
 end;

 // Radky tabulky
 col:=List.Columns.Count;
 for i:=0 to List.Items.Count-1 do with List.Items[i] do begin
   E.TableRowBegin;
   E.TableCellBegin;
   E.Write(Caption);
   for j:=0 to col-2 do begin
     E.TableCellBegin;
     E.Write(SubItems[j]);
   end;
 end;
end;

procedure TMainForm.Save2BtnClick(Sender: TObject);
var ok:boolean;
    F:TextFile;
    E:TExportEngine;
    S, Title:String;
begin
 if List2.Items.Count=0 then
   raise Exception.Create('Cannot export an empty table.');

 SaveDialog.InitialDir:=LastDir;
 SaveDialog.FileName:=CheckFileName(StarName);
 if SaveDialog.Execute then begin
   LastDir:=ExtractFileDir(SaveDialog.FileName);
   LastFormat:=SaveDialog.FilterIndex;
   if FileExists(SaveDialog.FileName) then
     ok:=MessageDlg('File already exists. Do you want to replace it?', mtConfirmation, [mbYes, mbNo], 0)=mrYes
   else
     ok:=true;
   if ok then begin
     AssignFile(F, SaveDialog.FileName);
     Rewrite(F);
     try
       Title:=Format('Star ephemerides for %s',[StarName]);
       case (SaveDialog.FilterIndex) of
         1: E:=CreateExportEngine(xfTXT, Title, @S);
         2: E:=CreateExportEngine(xfCSV, Title, @S);
         3: E:=CreateExportEngine(xfHTML, Title, @S);
       else
         raise Exception.Create('Please, select a file format');
       end;
       try
         Export2(E);
       finally
         E.Free;
       end;
       Write(F, S);
     finally
       CloseFile(F);
     end;
   end;
 end;
end;

procedure TMainForm.Copy2BtnClick(Sender: TObject);
var S, Title:String;
    E:TExportEngine;
begin
 if List2.Items.Count=0 then
   raise Exception.Create('Cannot copy an empty table to the clipboard.');

 Clipboard.Open;
 try
   Title:=Format('Star ephemerides for %s (%s)',[StarName, StarCat]);
   E:=CreateExportEngine(xfClipboard, Title, @S);
   try
     Export2(E);
   finally
     E.Free;
   end;
   Clipboard.Clear;
   Clipboard.AsText:=S;
 finally
   Clipboard.Close;
 end;
end;

Procedure TMainForm.Export2;
var i,j,col:integer;
begin
 // Nadpis
 E.SectBegin;
 E.Write(Format('Star ephemerides for %s (%s)',[StarName, StarCat]));

 // Popis filtru
 E.ParBegin;
 with FFilter2 do begin
   E.Write(Format('Search period from %s UT to %s UT\n', [FormatDateTime('dddd, dd mmmm yyyy h:nn', JDToDateTime(JDMin)),
       FormatDateTime('dddd, dd mmmm yyyy h:nn', JDToDateTime(JDMax))]));
   E.Write(Format('Observing site: %s, %.4f %s, %.4f %s\n', [Location,
     Lon, ifthen(Lon>=0,'E','W'), Lat, ifthen(Lat>=0,'N','S')]));
   if FTime then begin
     if not FNight then
       E.Write(Format('Time of minimum from %.1f to %.1f hr. UT\n', [TimeFrom, TimeTo]))
     else
       E.Write(Format('Time of minimum during nighttime (Solar elevation below -%.0f deg.)\n', [Twilight]));
   end;
   if FDOW then
     E.Write(Format('Days of week: %s\n', [DOWToStr(DOW)]));
   if FAlt then
     E.Write(Format('Altitude from %.0f to %.0f deg.\n', [AltFrom, AltTo]));
   if FAz then
     E.Write(Format('Azimuth from %.0f to %.0f deg.\n', [AzFrom, AzTo]));
 end;

 // Pocet nalezenych zaznamu
 E.ParBegin;
 if Records2>1 then
   E.Write(Format('%d records found', [Records2]))
 else if Records2=1 then
   E.Write('1 record found (1 variable star)')
 else
   E.Write('No records found');

 // Zahlavi tabulky
 E.TableBegin;
 for i:=0 to List2.Columns.Count-1 do with List2.Columns[i] do begin
   E.TableAddCol(Caption, alignCenter);
 end;

 // Radky tabulky
 col:=List2.Columns.Count;
 for i:=0 to List2.Items.Count-1 do with List2.Items[i] do begin
   E.TableRowBegin;
   E.TableCellBegin;
   E.Write(Caption);
   for j:=0 to col-2 do begin
     E.TableCellBegin;
     E.Write(SubItems[j]);
   end;
 end;
end;

procedure TMainForm.MAboutClick(Sender: TObject);
begin
 AboutBox.Execute;
end;

procedure TMainForm.UpdateFilter;
begin
 { Observatory }
 Filter.Location   := Obs;
 Filter.Lon        := Lon;
 Filter.Lat        := Lat;
 Filter.Twilight   := Twilight;

 { Time }
 if (Pages.ActivePage=TabSheet1) then begin
   Filter.FTime    := MinF.Checked;
   Filter.FNight   := FNight.Checked;
   Filter.TimeFrom := StrToFloat(Min1.Text);
   Filter.TimeTo   := StrToFloat(Min2.Text);
 end else begin
   Filter.FTime    := TimeF.Checked;
   Filter.FNight   := FNight2.Checked;
   Filter.TimeFrom := StrToFloat(Time1.Text);
   Filter.TimeTo   := StrToFloat(Time2.Text);
 end;

 { Days of week }
 if (Pages.ActivePage=TabSheet1) then begin
   Filter.FDOW     := false;
 end else begin
   Filter.FDOW     := DOWF.Checked;
   Filter.DOW[1]   := Sun.Checked;
   Filter.DOW[2]   := Mon.Checked;
   Filter.DOW[3]   := Tue.Checked;
   Filter.DOW[4]   := Wed.Checked;
   Filter.DOW[5]   := Thu.Checked;
   Filter.DOW[6]   := Fri.Checked;
   Filter.DOW[7]   := Sat.Checked;
 end;

 { Altitude }
 if (Pages.ActivePage=TabSheet1) then begin
   Filter.FAlt     := AltF.Checked;
   Filter.AltFrom  := StrToFloat(Alt1.Text);
   Filter.AltTo    := StrToFloat(Alt2.Text);
 end else begin
   Filter.FAlt     := VysF.Checked;
   Filter.AltFrom  := StrToFloat(Vys1.Text);
   Filter.AltTo    := StrToFloat(Vys2.Text);
 end;

 { Azimuth }
 if (Pages.ActivePage=TabSheet1) then begin
   Filter.FAz      := AzF.Checked;
   Filter.AzFrom   := StrToFloat(Az1.Text);
   Filter.AzTo     := StrToFloat(Az2.Text);
 end else begin
   Filter.FAz      := AziF.Checked;
   Filter.AzFrom   := StrToFloat(Azi1.Text);
   Filter.AzTo     := StrToFloat(Azi2.Text);
 end;

 { Magnitude }
 if (Pages.ActivePage=TabSheet1) then begin
   Filter.FMag     := MagF.Checked;
   Filter.MagFrom  := StrToFloat(Mag1.Text);
   Filter.MagTo    := StrToFloat(Mag2.Text);
 end else begin
   Filter.FMag     := false;
 end;

 { Attractivity }
 if (Pages.ActivePage=TabSheet1) then begin
   Filter.FPts     := PtsF.Checked;
   Filter.PtsFrom  := StrToInt(Pts1.Text);
   Filter.PtsTo    := StrToInt(Pts2.Text);
 end else begin
   Filter.FPts     := false;
 end;

 { Right ascension }
 if (Pages.ActivePage=TabSheet1) then begin
   Filter.FRA      := RaF.Checked;
   Filter.RaFrom   := StrToFloat(RA1.Text);
   Filter.RaTo     := StrToFloat(RA2.Text);
 end else begin
   Filter.FRA      := false;
 end;

 { Declination }
 if (Pages.ActivePage=TabSheet1) then begin
   Filter.FDec     := DecF.Checked;
   Filter.DecFrom  := StrToFloat(Dec1.Text);
   Filter.DecTo    := StrToFloat(Dec2.Text);
 end else begin
   Filter.FDec     := false;
 end;

 { Constellation }
 if (Pages.ActivePage=TabSheet1) then begin
   Filter.FCon     := ConF.Checked;
   Filter.Cons     := Con.Text;
 end else begin
   Filter.FCon     := false;
 end;

 { Variability type }
 if (Pages.ActivePage=TabSheet1) then begin
   Filter.FTyp     := TypF.Checked;
   Filter.Types    := Typ.Text;
 end else begin
   Filter.FTyp     := false;
 end;

 { Object-Moon distance }
 if (Pages.ActivePage=TabSheet1) then begin
   Filter.FObjMoon := OMF.Checked;
   Filter.ObjMoon  := StrToFloat(OM1.Text);
 end else begin
   Filter.FObjMoon := ObjMF.Checked;
   Filter.ObjMoon  := StrToFloat(ObjM1.Text);
 end;

end;

procedure TMainForm.UpdateControls;
var ok:boolean;
begin
 { Page 1 - Toolbar }
 ok:=List.Items.Count>0;
 SortBtn.Enabled:=ok;
 FindBtn.Enabled:=ok;
 PrintBtn.Enabled:=ok;
 SaveBtn.Enabled:=ok;
 CopyBtn.Enabled:=ok;
 SunBtn.Enabled:=ok;
 MoonBtn.Enabled:=ok;

 ok:=List.SelCount>=1;
 DelBtn.Enabled:=ok;

 ok:=List.SelCount=1;
 InfoBtn.Enabled:=ok;
 SkyBtn.Enabled:=ok;

 { Page 1 - Filters }
 ok:=MinF.Checked;
 FNight.Enabled:=ok;
 ok:=MinF.Checked and not FNight.Checked;
 Label5.Enabled:=ok;
 Min1.Enabled:=ok;
 Min1SB.Enabled:=ok;
 Label4.Enabled:=ok;
 Min2.Enabled:=ok;
 Min2SB.Enabled:=ok;
 Label8.Enabled:=ok;

 ok:=AltF.Checked;
 Label9.Enabled:=ok;
 Alt1.Enabled:=ok;
 Alt1SB.Enabled:=ok;
 Label10.Enabled:=ok;
 Alt2.Enabled:=ok;
 Alt2SB.Enabled:=ok;
 Label11.Enabled:=ok;

 ok:=MagF.Checked;
 Label6.Enabled:=ok;
 Mag1.Enabled:=ok;
 Mag1SB.Enabled:=ok;
 Label3.Enabled:=ok;
 Mag2.Enabled:=ok;
 Mag2SB.Enabled:=ok;
 Label7.Enabled:=ok;

 ok:=PtsF.Checked;
 Label19.Enabled:=ok;
 Pts1.Enabled:=ok;
 Pts1SB.Enabled:=ok;
 Label20.Enabled:=ok;
 Pts2.Enabled:=ok;
 Pts2SB.Enabled:=ok;
 Label21.Enabled:=ok;

 ok:=RaF.Checked;
 Label12.Enabled:=ok;
 Ra1.Enabled:=ok;
 Ra1SB.Enabled:=ok;
 Label13.Enabled:=ok;
 Ra2.Enabled:=ok;
 Ra2SB.Enabled:=ok;
 Label14.Enabled:=ok;

 ok:=DecF.Checked;
 Label15.Enabled:=ok;
 Dec1.Enabled:=ok;
 Dec1SB.Enabled:=ok;
 Label16.Enabled:=ok;
 Dec2.Enabled:=ok;
 Dec2SB.Enabled:=ok;
 Label17.Enabled:=ok;

 ok:=ConF.Checked;
 Con.Enabled:=ok;
 ConBtn.Enabled:=ok;

 ok:=TypF.Checked;
 Typ.Enabled:=ok;
 TypBtn.Enabled:=ok;

 ok:=AzF.Checked;
 Label33.Enabled:=ok;
 Az1.Enabled:=ok;
 Az1SB.Enabled:=ok;
 Label34.Enabled:=ok;
 Az2.Enabled:=ok;
 Az2SB.Enabled:=ok;
 Label35.Enabled:=ok;

 ok:=OMF.Checked;
 Label41.Enabled:=ok;
 OM1.Enabled:=ok;
 OM1SB.Enabled:=ok;
 Label42.Enabled:=ok;
 Label43.Enabled:=ok;
 ObjM1.Enabled:=ok;
 ObjM1SB.Enabled:=ok;
 Label44.Enabled:=ok;

 { Page 2 - Toolbar }
 Cons2.Enabled:=Cons2.Items.Count>0;
 Star2.Enabled:=Star2.Items.Count>0;

 ok:=Length(LastStar)>0;
 Run2Btn.Enabled:=ok;
 Sky2Btn.Enabled:=ok;

 ok:=List2.Items.Count>0;
 Sort2Btn.Enabled:=ok;
 Find2Btn.Enabled:=ok;
 Print2Btn.Enabled:=ok;
 Save2Btn.Enabled:=ok;
 Copy2Btn.Enabled:=ok;
 Sun2Btn.Enabled:=ok;
 Moon2Btn.Enabled:=ok;

 ok:=List2.SelCount>=1;
 Del2Btn.Enabled:=ok;

 ok:=List2.SelCount=1;
 Info2Btn.Enabled:=ok;

 { Page 2 - Filters }
 ok:=TimeF.Checked;
 FNight2.Enabled:=ok;
 ok:=TimeF.Checked and not FNight2.Checked;
 Label18.Enabled:=ok;
 Time1.Enabled:=ok;
 Time1SB.Enabled:=ok;
 Label22.Enabled:=ok;
 Time2.Enabled:=ok;
 Time2SB.Enabled:=ok;
 Label32.Enabled:=ok;

 ok:=DOWF.Checked;
 Mon.Enabled:=ok;
 Tue.Enabled:=ok;
 Wed.Enabled:=ok;
 Thu.Enabled:=ok;
 Fri.Enabled:=ok;
 Sat.Enabled:=ok;
 Sun.Enabled:=ok;

 ok:=VysF.Checked;
 Label23.Enabled:=ok;
 Vys1.Enabled:=ok;
 Vys1SB.Enabled:=ok;
 Label24.Enabled:=ok;
 Vys2.Enabled:=ok;
 Vys2SB.Enabled:=ok;
 Label25.Enabled:=ok;

 ok:=AziF.Checked;
 Label36.Enabled:=ok;
 Azi1.Enabled:=ok;
 Azi1SB.Enabled:=ok;
 Label37.Enabled:=ok;
 Azi2.Enabled:=ok;
 Azi2SB.Enabled:=ok;
 Label38.Enabled:=ok;
end;

Procedure TMainForm.UpdateStatus;
var Str:String; WndDC, MemDC:HDC; S:TSize; OldFont:HGDIOBJ; C:String;
begin
 // Pocet nalezenych zaznamu
 if not AfterStart then begin
   if Pages.ActivePage=TabSheet1 then begin
     if Records1>1 then begin
       if Variables1=1 then C:='1 variable star' else C:=Format('%d variable stars',[Variables1]);
       StatusBar1.Panels[0].Text:=Format('%d records found (%s)', [Records1,C]);
     end else begin
       if Records1=1 then
         StatusBar1.Panels[0].Text:='1 record found (1 variable star)'
       else
         StatusBar1.Panels[0].Text:='No records found';
     end;
   end else begin
     if Records2>1 then
       StatusBar1.Panels[0].Text:=Format('%d records found', [Records2])
     else
       StatusBar1.Panels[0].Text:=ifthen(Records2=1,'1 record found','No records found');
   end;
 end;
 // Umisteni pozorovatele
 Str:='Location: '+Obs;
 WndDC:=GetDC(StatusBar1.Handle);
 MemDC:=CreateCompatibleDC(WndDC);
 ReleaseDC(StatusBar1.Handle, WndDC);
 OldFont:=SelectObject(MemDC, StatusBar1.Font.Handle);
 GetTextExtentPoint32(MemDC, @Str[1], Length(Str), S);
 SelectObject(MemDC, OldFont);
 DeleteDC(MemDC);
 StatusBar1.Panels[1].Text := Str;
 StatStrWidth:=S.cx;
 StatusBar1Resize(NIL);
end;

procedure TMainForm.ResizeClick(Sender: TObject);
begin
 if Pages.ActivePageIndex=0 then
   UpdateColumnWidths(List)
 else
   UpdateColumnWidths(List2);
end;

procedure TMainForm.ListMenuPopup(Sender: TObject);
var ok:boolean;
begin
 if Pages.ActivePageIndex=0 then
   ok:=List.Items.Count>0
 else
   ok:=List2.Items.Count>0;
 Resize.Enabled:=ok;
end;

Procedure TMainForm.UpdateColumnWidths;
var w,b,col:integer; Str:String; WndDC, MemDC:HDC; S:TSize;
    OldFont:HGDIOBJ;
begin
 AList.Columns.BeginUpdate;
 AList.Items.BeginUpdate;
 WndDC:=GetDC(AList.Handle);
 MemDC:=CreateCompatibleDC(WndDC);
 ReleaseDC(AList.Handle, WndDC);
 OldFont:=SelectObject(MemDC, AList.Font.Handle);
 for Col:=0 to AList.Columns.Count-1 do begin
   Str:=AList.Column[Col].Caption;
   GetTextExtentPoint32(MemDC, @Str[1], Length(Str), S);
   W:=S.cx;
   for b:=0 to AList.Items.Count-1 do begin
     if Col=0 then
       Str:=AList.Items[b].Caption
     else
       Str:=AList.Items[b].SubItems[Col-1];
     GetTextExtentPoint32(MemDC, @Str[1], Length(Str), S);
     W:=max(W, S.cx);
   end;
   AList.Columns[Col].Width:=W + 16;
 end;
 SelectObject(MemDC, OldFont);
 DeleteDC(MemDC);
 AList.Columns.EndUpdate;
 AList.Items.EndUpdate;
end;

Procedure TMainForm.Split;
var S:String; i,state:integer; ch:char;
begin
 S:='';
 State:=0;
 for i:=1 to Length(AStr) do begin
   ch:=AStr[i];
   case state of
     0: if ch>='A' then begin
          S:=ch;
          State:=1;
        end;
     1: if ch<'A' then begin
          AList.Add(S);
          S:='';
          State:=0;
        end else begin
          S:=S+ch;
        end;
   end;
 end;
 if Length(S)>0 then
   AList.Add(S);
end;

procedure TMainForm.ConBtnClick(Sender: TObject);
var S:String; i:integer; C,D:TStringList;
begin
 S:=Con.Text;
 C:=TStringList.Create;
 D:=TStringList.Create;
 try
   Kat1.Clear;
   for i:=0 to Cats.Items.Count-1 do if Cats.Checked[i] then
     Kat1.Load(Cats.Items[i]);
   Kat1.ConsList(C);
   Split(Con.Text, D);
   if ConstDlg.Execute('Constellations', C, D) then begin
     D.Delimiter:=' ';
     Con.Text:=D.DelimitedText;
   end;
 finally
   C.Free;
   D.Free;
 end;
end;

procedure TMainForm.TypBtnClick(Sender: TObject);
var S:String; i:integer; C,D:TStringList;
begin
 S:=Con.Text;
 C:=TStringList.Create;
 D:=TStringList.Create;
 try
   Kat1.Clear;
   for i:=0 to Cats.Items.Count-1 do if Cats.Checked[i] then
     Kat1.Load(Cats.Items[i]);
   Kat1.VarTypeList(C);
   Split(Typ.Text, D);
   if ConstDlg.Execute('Variability types', C, D) then begin
     D.Delimiter:=' ';
     Typ.Text:=D.DelimitedText;
   end;
 finally
   C.Free;
   D.Free;
 end;
end;

procedure TMainForm.StatusBar1Resize;
begin
 StatusBar1.Panels[0].Width := Max(0, StatusBar1.Width - StatStrWidth - 32);
end;

Function TMainForm.CountUniqueRecords;
var S:TStringList; C:String; i:integer;
begin
 Result:=0;
 S:=TStringList.Create;
 try
   for i:=0 to AList.Count-1 do begin
     C:=AList[i].Caption;
     if S.IndexOf(C)<0 then begin
       S.Add(C);
       inc(Result);
     end;
   end;
 finally
   S.Free;
 end;
end;

procedure TMainForm.CatalogMenuSelectAllClick(Sender: TObject);
var i:integer;
begin
 for i:=0 to Cats.Items.Count-1 do Cats.Checked[i]:=true;
end;

procedure TMainForm.CatalogMenuClearClick(Sender: TObject);
var i:integer;
begin
 for i:=0 to Cats.Items.Count-1 do Cats.Checked[i]:=false;
end;

procedure TMainForm.CatalogMenuPopup(Sender: TObject);
var ok:boolean; i:integer;
begin
 ok:=false;
 if Pages.ActivePageIndex=0 then begin
   for i:=0 to Cats.Items.Count-1 do if not Cats.Checked[i] then begin ok:=true; break; end;
 end;
 CatalogMenuSelectAll.Enabled:=ok;

 ok:=false;
 if Pages.ActivePageIndex=0 then begin
   for i:=0 to Cats.Items.Count-1 do if Cats.Checked[i] then begin ok:=true; break; end;
 end;
 CatalogMenuClear.Enabled:=ok;
end;

procedure TMainForm.OMFClick(Sender: TObject);
begin
 if not Updating then begin
   Updating:=true;
   if (Sender<>OMF) then OMF.Checked:=true;
   ObjMF.Checked:=OMF.Checked;
   ObjM1.Text   :=OM1.Text;
   Updating:=false;
 end;
 UpdateControls(Sender);
end;

procedure TMainForm.Om1SBDownClick(Sender: TObject);
var X:double;
begin
 if Assigned(TSpinButton(Sender).FocusControl) then begin
   X:=StrToFloat(TEdit(TSpinButton(Sender).FocusControl).Text);
   X:=X-5; if X<0 then X:=0;
   TEdit(TSpinButton(Sender).FocusControl).Text:=Format('%.0f', [X]);
 end;
end;

procedure TMainForm.Om1SBUpClick(Sender: TObject);
var X:double;
begin
 if Assigned(TSpinButton(Sender).FocusControl) then begin
   X:=StrToFloat(TEdit(TSpinButton(Sender).FocusControl).Text);
   X:=X+5; if X>180 then X:=180;
   TEdit(TSpinButton(Sender).FocusControl).Text:=Format('%.0f', [X]);
 end;
end;

procedure TMainForm.Om1Exit(Sender: TObject);
begin
 TEdit(Sender).Text:=Format('%.0f', [StrToFloat(TEdit(Sender).Text)]);
end;

procedure TMainForm.ObjMFClick(Sender: TObject);
begin
 if not Updating then begin
   Updating:=true;
   if (Sender<>ObjMF) then ObjMF.Checked:=true;
   OMF.Checked:=ObjMF.Checked;
   OM1.Text   :=ObjM1.Text;
   Updating:=false;
 end;
 UpdateControls(Sender);
end;

procedure TMainForm.ObjM1SBDownClick(Sender: TObject);
var X:double;
begin
 if Assigned(TSpinButton(Sender).FocusControl) then begin
   X:=StrToFloat(TEdit(TSpinButton(Sender).FocusControl).Text);
   X:=X-5; if X<0 then X:=0;
   TEdit(TSpinButton(Sender).FocusControl).Text:=Format('%.0f', [X]);
 end;
end;

procedure TMainForm.ObjM1SBUpClick(Sender: TObject);
var X:double;
begin
 if Assigned(TSpinButton(Sender).FocusControl) then begin
   X:=StrToFloat(TEdit(TSpinButton(Sender).FocusControl).Text);
   X:=X+5; if X>180 then X:=180;
   TEdit(TSpinButton(Sender).FocusControl).Text:=Format('%.0f', [X]);
 end;
end;

procedure TMainForm.ObjM1Exit(Sender: TObject);
begin
 TEdit(Sender).Text:=Format('%.0f', [StrToFloat(TEdit(Sender).Text)]);
end;

procedure TMainForm.CopyJDClick(Sender: TObject);
var F:TEphemRec;
begin
 if (Pages.ActivePage=TabSheet1) and Assigned(List.Selected) then begin
   F:=TEphemRec(List.Selected.Data);
   Clipboard.Open;
   try
     Clipboard.Clear;
     Clipboard.AsText:=Format('%.4f',[F.JD]);
   finally
     Clipboard.Close;
   end;
 end;
 if (Pages.ActivePage=TabSheet2) and Assigned(List2.Selected) then begin
   F:=TEphemRec(List2.Selected.Data);
   Clipboard.Open;
   try
     Clipboard.Clear;
     Clipboard.AsText:=Format('%.4f',[F.JD]);
   finally
     Clipboard.Close;
   end;
 end;
end;

procedure TMainForm.CopyNameClick(Sender: TObject);
var F:TEphemRec;
begin
 if (Pages.ActivePage=TabSheet1) and Assigned(List.Selected) then begin
   F:=TEphemRec(List.Selected.Data);
   Clipboard.Open;
   try
     Clipboard.Clear;
     Clipboard.AsText:=F.LongName;
   finally
     Clipboard.Close;
   end;
 end;
 if (Pages.ActivePage=TabSheet2) and Assigned(List2.Selected) then begin
   F:=TEphemRec(List2.Selected.Data);
   Clipboard.Open;
   try
     Clipboard.Clear;
     Clipboard.AsText:=F.LongName;
   finally
     Clipboard.Close;
   end;
 end;
end;

procedure TMainForm.CopyUTCClick(Sender: TObject);
var F:TEphemRec;
begin
 if (Pages.ActivePage=TabSheet1) and Assigned(List.Selected) then begin
   F:=TEphemRec(List.Selected.Data);
   Clipboard.Open;
   try
     Clipboard.Clear;
     Clipboard.AsText:=FormatDateTime('yyyy-mm-dd h:nn',JDToDateTime(F.JD));
   finally
     Clipboard.Close;
   end;
 end;
 if (Pages.ActivePage=TabSheet2) and Assigned(List2.Selected) then begin
   F:=TEphemRec(List2.Selected.Data);
   Clipboard.Open;
   try
     Clipboard.Clear;
     Clipboard.AsText:=FormatDateTime('yyyy-mm-dd h:nn',JDToDateTime(F.JD));
   finally
     Clipboard.Close;
   end;
 end;
end;

procedure TMainForm.CopyLocTClick(Sender: TObject);
var F:TEphemRec;
begin
 if (Pages.ActivePage=TabSheet1) and Assigned(List.Selected) then begin
   F:=TEphemRec(List.Selected.Data);
   Clipboard.Open;
   try
     Clipboard.Clear;
     Clipboard.AsText:=FormatDateTime('yyyy-mm-dd h:nn',ToLocalTime(F.JD,TimeZoneX));
   finally
     Clipboard.Close;
   end;
 end;
 if (Pages.ActivePage=TabSheet2) and Assigned(List2.Selected) then begin
   F:=TEphemRec(List2.Selected.Data);
   Clipboard.Open;
   try
     Clipboard.Clear;
     Clipboard.AsText:=FormatDateTime('yyyy-mm-dd h:nn',ToLocalTime(F.JD,TimeZoneX));
   finally
     Clipboard.Close;
   end;
 end;
end;
end.

