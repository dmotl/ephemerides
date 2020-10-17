unit Tisk;

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

{ Sloupce a strany se cisluji od 1, veskere pozice jsou v setinach milimetru }

uses
  SysUtils, WinTypes, Classes, Graphics, ExtCtrls, Math, Printers;

type
  TPageSize = (psA3, psA4, psA5);
  { Velikost papiru }
  TPageOrientation = Printers.TPrinterOrientation;
  { Orientace papiru }
  TMoveOrigin = (moveLT, moveLM, moveLB, moveCT, moveCM, moveCB, moveRT, moveRM, moveRB);
  { Vychozi bod pro prikaz Move }
  TPrintAlign = (alignLeft, alignCenter, alignRight);
  { Zarovnavani textu }
  TLineOrientation = (loHorizontal, loVertical);
  { Orientace cary }

  TPrintEngine = class;

  TPrintBox = class(TObject)        { Zakladni trida pro box }
    R   :TRect;                     { Rozmery boxu }
    Constructor Create(ARect:TRect);
    Procedure   Print(E:TPrintEngine; ARect:TRect; ACanvas:TCanvas); virtual;
                { Tiskne obsah boxu na Canvas }
    Function    RectToGlob(APar,ARect:TRect):TRect;
                { Prepocet lokalnich rozmeru na rozmery na papire }
    Function    RectToCanv(E:TPrintEngine; ARect:TRect):TRect;
                { Prepocet rozmeru v 0.01mm na pixely }
    Function    PtToGlob(APar:TRect; AP:TPoint):TPoint;
                { Prepocet lokalnich souradnic na souradnice na papire }
    Function    PtToCanv(E:TPrintEngine; AP:TPoint):TPoint;
                { Prepocet souradnic na pixely }
  end;

  TWriteBox = class(TPrintBox)     { Box s textem }
    A:TPrintAlign;                 { Zarovnani textu }
    Text:String;                   { Text }
    Font:TFont;                    { Pismo }
    Constructor Create(ARect:TRect; AText:String; AAlign:TPrintAlign; AFont:TFont);
    Destructor  Destroy; override;
    Procedure   Print(E:TPrintEngine; ARect:TRect; ACanvas:TCanvas); override;
  end;

  TTextBox = class(TWriteBox)      { Text, ktery muze mit specialni znaky }
    Procedure   Print(E:TPrintEngine; ARect:TRect; ACanvas:TCanvas); override;
  end;

  TLineBox   = class(TPrintBox)    { Cara }
    Width:integer;                 { Sirka v 0.01mm }
    Orient:TLineOrientation;       { Svisla, vodorovna }
    Pen:TPen;                      { Pero }
    Constructor Create(ARect:TRect; AWidth:integer; APen:TPen; AOrient:TLineOrientation);
    Destructor  Destroy; override;
    Procedure   Print(E:TPrintEngine; ARect:TRect; ACanvas:TCanvas); override;
  end;

  TRectangleBox = class(TPrintBox) { Obdelnik }
    Brush : TBrush;                { Vypln }
    Pen   : TPen;                  { Okraj }
    Constructor Create(ARect:TRect; AFilled:boolean; ABrush:TBrush; APen:TPen);
    Destructor  Destroy; override;
    Procedure   Print(E:TPrintEngine; ARect:TRect; ACanvas:TCanvas); override;
  end;

  TEllipseBox = class(TPrintBox) { Elipsa }
    Brush : TBrush;                { Vypln }
    Pen   : TPen;                  { Okraj }
    Constructor Create(ARect:TRect; AFilled:boolean; ABrush:TBrush; APen:TPen);
    Destructor  Destroy; override;
    Procedure   Print(E:TPrintEngine; ARect:TRect; ACanvas:TCanvas); override;
  end;

  TParentBox = class(TPrintBox)    { Box, ktery muze vlastnit dalsi boxy }
    P:TParentBox;                  { Nadrizeny box }
    F:TList;                       { Seznam podrizenych boxu }
    W, H:integer;                  { Sirka a vyska }
    Constructor Create(AParent:TParentBox; ARect:TRect);
    Destructor  Destroy; override;
    Procedure   Print(E:TPrintEngine; ARect:TRect; ACanvas:TCanvas); override;
  end;

  TFrameBox = class(TParentBox)    { Vymezena oblast na papire, do ktere se tiskne }
    A:TPrintAlign;                 { Zarovnani textu }
    Constructor Create(AParent:TParentBox; ARect:TRect; AAlign:TPrintAlign);
  end;

  TPrintHeader = class(TObject)    { *** Hlavicka *** }
   public
     Visible : boolean;            { Je viditelna ? }
     Owner   : TPrintEngine;       { Reference na E }
     LeftText, CenterText, RightText : String; { Texty, viz makra }
     Height  : integer; // Vyska hlavicky
     Spacing : integer; // Mezera mezi hlavickou a telem
     R       : TRect;   // Vyrez, do ktereho se vypisuje hlavicka
     Font    : TFont;   // Pismo
     Constructor Create;
     Destructor  Destroy; override;
     Procedure   Call(E:TPrintEngine); virtual;
  end;

  TPrintFooter = class(TPrintHeader)          { *** Paticka *** }
     Constructor Create;
  end;

  TPrintBody   = class(TObject)              { *** Telo *** }
     R      : TRect;       // Vyrez, do ktereho se vypisuje telo stranky
     Columns: byte;        // Pocet sloupcu na strance
     Spacing: integer;     // Mezera mezi sloupci
     Constructor Create;
  end;

  TFooterBox = class(TFrameBox);
  THeaderBox = class(TFrameBox);
  TColumnBox = class(TFrameBox);

  TPageBox = class(TParentBox)     { Hlavni box ve kterem je obsah stranky }
    Procedure   FirstColumn(E:TPrintEngine);
                // Nastavi FBox na prvni sloupec
    Procedure   NextColumn(E:TPrintEngine);
                // Nastavi FBox na nasledujici sloupec
  end;

  TTable       = class(TObject)     { Objekt, ktery udrzuje kontext tabulky }
    Parent: TTable;                // Nadrizena tabulka
    Align : TPrintAlign;           // Zarovnani tabulky v boxu
    XPad, YPad: integer;           // Vypln uvnitr bunek na bocich a nahore/dole
    Cols : TList;                  // Definice sloupcu
    RowHeight : integer;           // Vyska aktualniho radku
    TabWidth  : integer;           // Sirka cele tabulky
    Row, Col : integer;            // Cislo aktualniho radku a sloupce
    InRow, InCell : boolean;       // TRUE, pokud je uvnitr radku, bunky
    GridColor:TColor;              // Barva mrizky
    Constructor Create(AParent:TTable);
    Destructor  Destroy; override;
  end;

  TTableColumn = class(TObject)        { Sloupec tabulky }
    Divider   : boolean;            // TRUE, kdyz je to svisly oddelovac
    CellWidth : integer;
    Align     : TPrintAlign;
    TextWidth : integer;
  end;

  TPrintEngine = class(TComponent)     { *** TISKOVY STROJ *** }
   protected
    FP,FC      : integer;       // Aktualni tiskova stranka, cislo aktualniho sloupce
    FX,FY      : integer;       // Aktualni pozice uvnitr boxu
    FUseFont   : integer;       // Pouzivany font
    FPages     : TList;         // Stranky
    FPage      : TPageBox;      // Aktualni stranka
    FBox       : TFrameBox;     // Aktalni frame
    FTable     : TTable;        // Aktualni tabulka
    FHandle    : HDC;           // Kontext zarizeni
    FPSize     : TPageSize;     // Velikost stranky
    FPOrient   : TPageOrientation;   // Orientace stranky
    FTopMargin, FBottomMargin, FLeftMargin, FRightMargin : integer; // Okraje zrcadla
    FHeader    : TPrintHeader;  // Nastaveni hlavicky
    FFooter    : TPrintFooter;  // Nastaveni paticky
    FBody      : TPrintBody;    // Nastaveni tela
    FWidth, FHeight : integer;  // Velikost stranky vcetne okraju
    ScaleX, ScaleY : double;    // Prepocitaci konstanty (meritko)
    OffsetX, OffsetY : double;  // Prepocitaci konstanty (posun)
    FFont      : TFont;         // Pismo
    FBrush     : TBrush;        // Stetec
    FPen       : TPen;          // Pero
    FReplText  : TStrings;      // Automaticke texty
    FTitle     : String;        // Titulek v Print Manageru
    Procedure   PageBegin(EmptyPage:boolean);
    Procedure   PageEnd;
    Function    GetPageCount:integer;
    Function    GetAlign:TPrintAlign;
    Procedure   SetAlign(A:TPrintAlign);
    Function    GetFrameHeight:integer;
    Function    GetFrameWidth:integer;
    Function    AutoText(AText:String):String;
   public
    property    Header:TPrintHeader read FHeader;
                { Hlavicka }
    property    Footer:TPrintFooter read FFooter;
                { Pata }
    property    Body:TPrintBody read FBody;
                { Telo }
    property    Font:TFont read FFont;
                { Aktualni font }
    property    Brush:TBrush read FBrush;
                { Aktualni stetec }
    property    Pen:TPen read FPen;
                { Aktualni pero }
    property    PSize:TPageSize read FPSize write FPSize;
                { Velikost papiru }
    property    PosY:integer read FY;
    property    PosX:integer read FX;
                { Aktualni pozice kurzoru }            
    property    POrient:TPageOrientation read FPOrient write FPOrient;
                { Orientace papiru }
    property    Align:TPrintAlign read GetAlign write SetAlign;
                { Zarovnavani textu }
    property    TopMargin:integer read FTopMargin write FTopMargin;
                { Horni okraj }
    property    LeftMargin:integer read FLeftMargin write FLeftMargin;
                { Levy okraj }
    property    RightMargin:integer read FRightMargin write FRightMargin;
                { Pravy okraj }
    property    BottomMargin:integer read FBottomMargin write FBottomMargin;
                { Dolni okraj }
    property    Table:TTable read FTable;
                { Aktualni tabulka }
    property    FrameHeight:integer read GetFrameHeight;
                { Vyska oblasti, do ktere se tiskne }
    property    FrameWidth:integer read GetFrameWidth;
                { Sirka oblasti, do ktere se tiskne }
    property    Title:String read FTitle write FTitle;
                { Napis, ktery se zobrazuje v tiskovem manazeru }
    Constructor Create(AOwner:TComponent); override;
    Destructor  Destroy; override;
    Procedure   Preview(APage:integer; AImage:TImage);
                { Vytisknout stranku do AImage pro nahled }
    Procedure   Print(AStart, AStop:integer);
                { Vytisknout stranky AStart-AStop vcetne na tiskarnu }
    Function    GetLineHeight:integer;
                { Vypocita vysku textoveho radku }
    Function    GetTextWidth(AText:String):integer;
                { Vypocita sirkou potrebnou pro zobrazeni textu }
    Function    GetTextRect(AText:String):TSize;
                { Vypocita obdelnik potrebny pro zobrazeni textu }
    Function    IsSpace(AVal:integer):boolean;
                { Vraci TRUE, je-li pred koncem stranky jeste misto alespon AVal }
    Procedure   ReplaceDef(AName,AReplaceWith:String);
                { Definice specialnich retezcu, ktere se nahrazuji v textu }
    Function    GetBodyWidth:integer;
                { Vraci sirku cele stranky bez okraju }
    Procedure   GetPageSize(var AWidth,AHeight:integer);
                { Vraci rozmer cele stranky }
    { Dokument }
    Procedure   DocClear;
                { Vse vymazat a inicializovat }
    Procedure   DocBegin;
                { Zacatek dokumentu }
    Procedure   DocEnd;
                { Konec dokumentu }
    { Sloupce a stranky }
    Procedure   NewColumn;
                { Prejit na novy sloupec }
    Procedure   NewPage;
                { Prejit na novou stranku }
    Procedure   NewDoublePage;
                { Prejit na novou dvojstranku }
    Procedure   NewColumnCond(AReqSpace:integer);
                { Prejit na novy sloupec, pokud je mene mista nez AReqSpace }
    Procedure   NewPageCond(AReqSpace:integer);
                { Prejit na novou stranku, pokud je mene mista nez AReqSpace }
    Procedure   NewDoublePageCond(AReqSpace:integer);
                { Prejit na novou dvojstranku, pokud je mene mista nez AReqSpace }
    property    PageCount:integer read GetPageCount;
                { Vraci pocet stranek }
    { Texty }
    Procedure   Write(AText:String);
                { Vytisknout text }
    Procedure   Writeln(AText:String='');
                { Vytisknout text a prejit na dalsi radek }
    Procedure   Text(AText:String);
                { Vytisknout text, nahradit ridici sekvence }
    Procedure   Textln(AText:String='');
                { Vytisknout text, nahradit ridici sekvence a prejit na dalsi radek }
    Procedure   Par(AStr:String);
                { Vytisknout odstavec se zalamovanim radku }
    Procedure   CursorReturn;
                { Navrat kurzoru na levy okraj }
    Procedure   LineFeed(AHowMany:integer=1);
                { Posun kurzoru o zadany pocet radku }
    { Kurzor }
    Procedure   Move(AOrigin:TMoveOrigin; AX:integer=0; AY:integer=0);
                { Nastavit pozici kurzoru, Origin je vychozi bod, AX a AY jsou posuny
                  (doprava a dolu kladne, doleva a nahoru zaporne) }
    Procedure   Shift(ADX,ADY:integer);
                { Posun kurzoru vuci soucasne pozici }
    { Ramy }
    Procedure   FrameBegin(AWidth,AHeight:integer);
                { Vytvor novou oblast o sirce AWidth a vysce AHeight }
    Procedure   FrameEnd;
                { Ukonci oblast a vrat se o uroven zpet }
    { Kresleni }
    Procedure   HLine(ALength,AWidth:integer);
                { Vodorovna cara o delce ALength a tloustce AWidth }
    Procedure   VLine(ALength,AWidth:integer);
                { Svisla cara o delce ALength a tloustce AWidth }
    Procedure   Rectangle(AWidth,AHeight:integer; AFilled:boolean=false);
                { Obdelnik }
    Procedure   Ellipse(AWidth,AHeight:integer; AFilled:boolean=false);
                { Elipsa }
    { Tabulky }
    Function    TableBegin(AAlign:TPrintAlign=alignLeft; HPad:integer=150; VPad:integer=100):TTable;
                { Zacit novou tabulku (zarovnani, mezery mezi bunkami) }
    Procedure   TableEnd;
                { Ukoncit tabulku }
    Function    TableAddCol(AWidth:integer; AAlign:TPrintAlign=alignLeft):TTableColumn;
                { Pridej novy sloupec do tabulky }
    Function    TableAddDiv(AWidth:integer):TTableColumn;
                { Pridej svisly oddelovac mezi sloupci }
    Procedure   TableLine(AWidth:integer);
                { Pridej vodorovny oddelovac mezi radky }
    Procedure   TableRowBegin(AHeight:integer=0);
                { Zacatek radku tabulky }
    Procedure   TableRowEnd;
                { Konec radku tabulky }
    Procedure   TableCellBegin(AColSpan:byte=0);
                { Zacatek bunky tabulky }
    Procedure   TableCellEnd;
                { Konec bunky tabulky }
 end;

implementation

Constructor TPrintHeader.Create;
{ Inicializace objektu s nastavenim hlavicky }
begin
 inherited;
 Height:=350;
 Spacing:=350;
 Font:=TFont.Create;
end;

Destructor TPrintHeader.Destroy;
begin
 Font.Free;
 inherited;
end;

Procedure TPrintHeader.Call;
{ Vola prikazy pro tisk hlavicky }
var BakF:TFont;
begin
 BakF:=TFont.Create;
 BakF.Assign(E.Font);
 try
   E.Font.Assign(Font);
   E.Move(moveLT);
   if Length(LeftText)>0 then begin
     E.Align:=alignLeft;
     E.Text(LeftText);
   end;
   if Length(CenterText)>0 then begin
     E.Align:=alignCenter;
     E.Text(CenterText);
   end;
   if Length(RightText)>0 then begin
     E.Align:=alignRight;
     E.Text(RightText);
   end;
 finally
   E.Font.Assign(BakF);
   BakF.Free;
 end;
end;

Constructor TPrintBody.Create;
{ Inicializace objektu s nastavenim tela }
begin
 inherited;
 Columns:=1;
 Spacing:=1000;
end;

Constructor TPrintFooter.Create;
{ Inicializace objektu s nastaveni paty }
begin
 inherited;
 Visible:=true;
 CenterText:='Strana ##/#*';
end;

Constructor TTable.Create;
{ Inicializace promennych nove tabulky }
begin
 inherited Create;
 Parent:=AParent;
 Cols:=TList.Create;
 GridColor:=clBlack;
 InRow:=false;
 InCell:=false;
end;

Destructor TTable.Destroy;
var i:integer;
begin
 with Cols do for i:=0 to Count-1 do TObject(Cols[i]).Free;
 Cols.Free;
 inherited;
end;

Constructor TPrintBox.Create;
begin
 inherited Create;
 R:=ARect;
end;

Procedure TPrintBox.Print;
{ Odpoznamkovat proladeni - zobrazuje okraje vsech boxu }
//var Aux:TColor;
begin
{ ARect:=RectToCanv(E,RectToGlob(ARect,R));
 Aux:=ACanvas.Pen.Color;
 ACanvas.Pen.Color:=clSilver;
 ACanvas.MoveTo(ARect.Left,ARect.Top);
 ACanvas.LineTo(ARect.Right,ARect.Top);
 ACanvas.LineTo(ARect.Right,ARect.Bottom);
 ACanvas.LineTo(ARect.Left,ARect.Bottom);
 ACanvas.LineTo(ARect.Left,ARect.Top);
 ACanvas.Pen.Color:=Aux;
}end;

Function TPrintBox.RectToGlob;
{ Prepocet rozmeru z lokalnich na globalni }
begin
 Result:=Rect(min(ARect.Left+APar.Left,APar.Right),
              min(ARect.Top+APar.Top,APar.Bottom),
              min(ARect.Right+APar.Left,APar.Right),
              min(ARect.Bottom+APar.Top,APar.Bottom));
end;

Function TPrintBox.RectToCanv;
{ Prepocet rozmeru v 0.01mm na pixely }
begin
 Result:=Rect(round(ARect.Left*E.ScaleX+E.OffsetX),
              round(ARect.Top*E.ScaleY+E.OffsetY),
              round(ARect.Right*E.ScaleX+E.OffsetX),
              round(ARect.Bottom*E.ScaleY+E.OffsetY));
end;

Function TPrintBox.PtToGlob;
{ Prepocet souradni z lokalnich na globalni }
begin
 Result:=Point(min(APar.Left+AP.X,APar.Right),
              min(APar.Top+AP.Y,APar.Bottom));
end;

Function TPrintBox.PtToCanv;
{ Prepocet rozmeru v 0.01mm na pixely }
begin
 Result:=Point(round(AP.X*E.ScaleX+E.OffsetX),
               round(AP.Y*E.ScaleY+E.OffsetY));
end;

Constructor TWriteBox.Create;
{ Novy box s textem }
begin
 inherited Create(ARect);
 A:=AAlign;
 Text:=AText;
 Font:=TFont.Create;
 Font.Assign(AFont);
end;

Procedure TWriteBox.Print;
{ Tisk textu }
var X,Y:TRect;
begin
 ACanvas.Font.Assign(Font);
 ACanvas.Brush.Style:=bsClear;
 X:=RectToCanv(E,RectToGlob(ARect,R));
 Y:=RectToCanv(E,ARect);
 { Podminky resi rozdily mezi sirkou textu na tikarne a na obrazovce }
 if A=alignCenter then X.Left:=(Y.Right+Y.Left-ACanvas.TextWidth(Text)) div 2
 else if A=alignRight then X.Left:=Y.Right-ACanvas.TextWidth(Text);
 ACanvas.TextRect(Y,X.Left,X.Top,Text);
end;

Procedure TTextBox.Print;
{ Tisk textu se specialnimi znaky, napriklad cislem stranky }
var i:integer; ok:boolean; X,Y:TRect;
begin
 { Zpracovat specialni retezece }
 repeat
   ok:=false;
   i:=pos('##',Text);
   if i>0 then begin Delete(Text,i,2); Insert(IntToStr(E.FP),Text,i); ok:=true; end;
   i:=pos('#*',Text);
   if i>0 then begin Delete(Text,i,2); Insert(IntToStr(E.PageCount),Text,i); ok:=true; end;
 until not ok;
 ACanvas.Font.Assign(Font);
 ACanvas.Brush.Style:=bsClear;
 X:=RectToCanv(E,RectToGlob(ARect,R));
 Y:=RectToCanv(E,ARect);
 { Podminky resi rozdily mezi sirkou textu na tikarne a na obrazovce }
 if A=alignCenter then X.Left:=(Y.Right+Y.Left-ACanvas.TextWidth(Text)) div 2
 else if A=alignRight then X.Left:=Y.Right-ACanvas.TextWidth(Text);
 ACanvas.TextRect(Y,X.Left,X.Top,Text);
end;

Destructor TWriteBox.Destroy;
begin
 Font.Free;
 inherited;
end;

Constructor TLineBox.Create;
begin
 inherited Create(ARect);
 Pen:=TPen.Create;
 Pen.Assign(APen);
 Orient:=AOrient;
 Width :=AWidth;
end;

Destructor TLineBox.Destroy;
begin
 Pen.Free;
 inherited;
end;

Procedure TLineBox.Print;
{ Tisk cary }
var W:integer;
begin
 if Orient=loHorizontal then begin
   { Vodorovna cara }
   W:=max(1,round(Width*E.ScaleY));  { Vypocet sirky cary v pixelech }
   ARect:=RectToCanv(E,RectToGlob(ARect,R));
   ACanvas.Pen.Assign(Pen);
   ACanvas.Pen.Width:=W;
   ACanvas.MoveTo(ARect.Left,ARect.Top);
   ACanvas.LineTo(ARect.Right,ARect.Top);
 end else begin
   { Svisla cara }
   W:=max(1,round(Width*E.ScaleX));  { Vypocet sirky cary v pixelech }
   ARect:=RectToCanv(E,RectToGlob(ARect,R));
   ACanvas.Pen.Assign(Pen);
   ACanvas.Pen.Width:=W;
   ACanvas.MoveTo(ARect.Left,ARect.Top);
   ACanvas.LineTo(ARect.Left,ARect.Bottom);
 end;
end;

Constructor TFrameBox.Create;
begin
 inherited Create(AParent,ARect);
 A:=AAlign;
end;

Constructor TRectangleBox.Create;
begin
 inherited Create(ARect);
 Brush:=TBrush.Create;
 Brush.Assign(ABrush);
 if AFilled then Brush.Style:=bsSolid
            else Brush.Style:=bsClear;
 Pen:=TPen.Create;
 Pen.Assign(APen);
end;

Destructor TRectangleBox.Destroy;
begin
 Brush.Free;
 Pen.Free;
 inherited;
end;

Procedure TRectangleBox.Print;
{ Tisk obdelniku }
var AuxB:TBrush; AuxP:TPen;
begin
 ARect:=RectToCanv(E,RectToGlob(ARect,R));
 AuxB:=TBrush.Create; AuxB.Assign(Acanvas.Brush);
 AuxP:=TPen.Create;   AuxP.Assign(Acanvas.Pen);
 ACanvas.Brush.Assign(Brush);
 ACanvas.Pen.Assign(Pen);
 ACanvas.Pen.Width:=max(1,round(ACanvas.Pen.Width*E.ScaleX)); 
 ACanvas.Rectangle(ARect);
 ACanvas.Brush.Assign(AuxB); AuxB.Free;
 ACanvas.Pen.Assign(AuxP); AuxP.Free;
end;

Constructor TEllipseBox.Create;
begin
 inherited Create(ARect);
 Brush:=TBrush.Create;
 Brush.Assign(ABrush);
 if AFilled then Brush.Style:=bsSolid
            else Brush.Style:=bsClear;
 Pen:=TPen.Create;
 Pen.Assign(APen);
end;

Destructor TEllipseBox.Destroy;
begin
 Brush.Free;
 Pen.Free;
 inherited;
end;

Procedure TEllipseBox.Print;
{ Tisk obdelniku }
var AuxB:TBrush; AuxP:TPen; CX,CY,RD:integer;
begin
 ARect:=RectToCanv(E,RectToGlob(ARect,R));
 AuxB:=TBrush.Create; AuxB.Assign(Acanvas.Brush);
 AuxP:=TPen.Create;   AuxP.Assign(Acanvas.Pen);
 ACanvas.Brush.Assign(Brush);
 ACanvas.Pen.Assign(Pen);
 ACanvas.Pen.Width:=max(1,round(ACanvas.Pen.Width*E.ScaleX));
 if abs(R.Right-R.Left)-abs(R.Bottom-R.Top)<1 then begin
   { Pokud je to kruznice, pak se prepocitaji souradnice, aby zobrazovala skutecne kulata }
   CX:=round(abs(ARect.Left+ARect.Right)/2);
   CY:=round(abs(ARect.Bottom+ARect.Top)/2);
   RD:=round((R.Right-R.Left)/4*E.ScaleX+(R.Bottom-R.Top)/4*E.ScaleY);
   ARect:=Rect(CX-RD,CY-RD,CX+RD-1,CY+RD-1);
 end;
 ACanvas.Ellipse(ARect);
 ACanvas.Brush.Assign(AuxB); AuxB.Free;
 ACanvas.Pen.Assign(AuxP); AuxP.Free;
end;

Constructor TParentBox.Create;
begin
 inherited Create(ARect);
 W:=R.Right-R.Left;
 H:=R.Bottom-R.Top;
 P:=AParent;
 F:=TList.Create;
end;

Procedure TParentBox.Print;
var i:integer; Q:TRect;
begin
 inherited;
 Q:=RectToGlob(ARect,R);
 for i:=0 to F.Count-1 do TPrintBox(F[i]).Print(E,Q,ACanvas);
end;

Destructor TParentBox.Destroy;
var i:integer;
begin
 with F do for i:=0 to Count-1 do TObject(F[i]).Free;
 F.Free;
 inherited;
end;

Procedure TPageBox.FirstColumn;
begin
 E.FC:=0;
 NextColumn(E);
end;

Procedure TPageBox.NextColumn;
var i,j:integer;
begin
 E.FC:=E.FC+1;
 j:=1;
 E.FBox:=NIL;
 for i:=0 to F.Count-1 do
   if (TObject(F[i]) is TColumnBox) then begin
     if (j=E.FC) then begin E.FBox:=F[i]; break; end;
     j:=j+1;
   end;
end;

Constructor TPrintEngine.Create;
{ Inicializace promennych tiskoveho stroje }
begin
 inherited;
 FPages:=TList.Create;
 FReplText:=TStringList.Create;
 FHeader:=TPrintHeader.Create;
 FFooter:=TPrintFooter.Create;
 FBody  :=TPrintBody.Create;
 FBox   :=NIL;
 FHandle:=CreateCompatibleDC(0);
 FUseFont:=-1;
 FFont  :=TFont.Create;
 FBrush :=TBrush.Create;
 FPen   :=TPen.Create;
 SelectObject(FHandle,FFont.Handle);
 SelectObject(FHandle,FBrush.Handle);
 SelectObject(FHandle,FPen.Handle);
 FPSize:=psA4;
 FPOrient:=poPortrait;
 FTopMargin:=2000;
 FBottomMargin:=2000;
 FLeftMargin:=2000;
 FRightMargin:=2000;
 DocClear;
end;

Destructor TPrintEngine.Destroy;
var i:integer;
begin
 with FPages do for i:=0 to Count-1 do TObject(FPages[i]).Free;
 FPages.Free;
 FHeader.Free;
 FBody.Free;
 FFooter.Free;
 FFont.Free;
 FBrush.Free;
 FPen.Free;
 DeleteDC(FHandle);
 FReplText.Free;
 inherited;
end;

Procedure TPrintEngine.GetPageSize;
{ Pocita sirku papiru }
begin
 if FPSize=psA3 then begin
   if FPOrient=poPortrait then begin
     AWidth:=29700; AHeight:=42000;
   end else begin
     AWidth:=42000; AHeight:=29700;
   end;
 end else
 if FPSize=psA5 then begin
   if FPOrient=poPortrait then begin
     AWidth:=14850; AHeight:=21000;
   end else begin
     AWidth:=21000; AHeight:=14850;
   end;
 end else begin
   if FPOrient=poPortrait then begin
     AWidth:=21000; AHeight:=29700;
   end else begin
     AWidth:=29700; AHeight:=21000;
   end;
 end;
end;

Procedure TPrintEngine.DocClear;
{ Inicializace promennych na zacatku dokumentu }
var i,PPIX,PPIY:integer;
begin
 FBox:=NIL;
 FPage:=NIL;
 with FPages do for i:=0 to Count-1 do TObject(FPages[i]).Free;
 FPages.Clear;
 FP:=1;
 GetPageSize(FWidth,FHeight);
 FLeftMargin  :=max(0,FLeftMargin);
 FRightMargin :=max(0,FRightMargin);
 FTopMargin   :=max(0,FTopMargin);
 FBottomMargin:=max(0,FBottomMargin);
 FBody.R:=Rect(FLeftMargin,FTopMargin,FWidth-FRightMargin,FHeight-FBottomMargin);
 if FHeader.Visible then begin
   FHeader.R  :=Rect(FLeftMargin,FTopMargin,FWidth-FRightMargin,FTopMargin+FHeader.Height);
   FBody.R.Top:=FHeader.R.Bottom+FHeader.Spacing;
 end;
 if FFooter.Visible then begin
   FFooter.R     :=Rect(FLeftMargin,FHeight-FBottomMargin-FFooter.Height,FWidth-FRightMargin,FHeight-FBottomMargin);
   FBody.R.Bottom:=FFooter.R.Top-FFooter.Spacing;
 end;
 PPIX:=GetDeviceCaps(FHandle,LOGPIXELSY);
 PPIY:=GetDeviceCaps(FHandle,LOGPIXELSX);
 ScaleX:=PPIX/100/25.4;
 ScaleY:=PPIY/100/25.4;
 OffsetX:=0;
 OffsetY:=0;
end;

Function TPrintEngine.GetBodyWidth;
{ Vypocet sirky stranky bez okraju }
var W,H:integer;
begin
 GetPageSize(W,H);
 Result:=W-FRightMargin-FLeftMargin;
end;

Procedure TPrintEngine.NewPage;
{ Prechod na novou stranku }
begin
 if Assigned(FBox) then PageEnd;
 FP:=FP+1;
 PageBegin(false);
end;

Procedure TPrintEngine.NewColumn;
{ Prechod na dalsi sloupec }
begin
 if Assigned(FPage) then FPage.NextColumn(Self);
 if (FBox=NIL) then NewPage;  { Odstrankuj, pokud byl posledni sloupec }
 FX:=0;
 FY:=0;
end;

Procedure TPrintEngine.NewDoublePage;
{ Prechod na novou dvojstranku }
begin
 if Assigned(FBox) then PageEnd;
 FP:=FP+1;
 if not odd(FP) then begin
   PageBegin(true);
   if Assigned(FBox) then PageEnd;
   FP:=FP+1;
 end;
 PageBegin(false);
end;

Function TPrintEngine.IsSpace;
{ TRUE, pokud je v oblasti jeste misto alespon AVal }
begin
 Result:=FBox.R.Top+FY+AVal<=FBox.R.Bottom;
end;

Procedure TPrintEngine.NewPageCond;
{ Prechod na novou stranku, je-li misto mensi nez AReqSpace }
begin
 if not IsSpace(AReqSpace) then NewPage;
end;

Procedure TPrintEngine.NewColumnCond;
{ Prechod na novy sloupec, je-li misto mensi nez AReqSpace }
begin
 if not IsSpace(AReqSpace) then NewPage;
end;

Procedure TPrintEngine.NewDoublePageCond;
{ Prechod na novou dvojstranku }
begin
 if not IsSpace(AReqSpace) then NewDoublePage;
end;

Procedure TPrintEngine.DocBegin;
{ Vola se na zacatku dokumentu }
begin
 DocClear;
 PageBegin(false);
end;

Procedure TPrintEngine.DocEnd;
{ Volat na konci dokumentu }
begin
 PageEnd;
end;

Procedure TPrintEngine.PageBegin;
{ Zacina novou stranku - neni nutne volat po NewPage }
var X,W,i:integer;
begin
 { Zacit novou stranku }
 FPage:=TPageBox.Create(NIL,Rect(0,0,FWidth,FHeight));
 FPages.Add(FPage);
 { Nastavit hlavicku }
 if not EmptyPage and FHeader.Visible then begin
   FBox:=THeaderBox.Create(FPage,FHeader.R,alignLeft);
   FPage.F.Add(FBox);
   FX:=0; FY:=0; FHeader.Call(Self);
 end;
 if not EmptyPage and FFooter.Visible then begin
   FBox:=TFooterBox.Create(FPage,FFooter.R,alignLeft);
   FPage.F.Add(FBox);
   FX:=0; FY:=0; FFooter.Call(Self);
 end;
 if not EmptyPage then begin
   FBody.Columns:=max(1,FBody.Columns);
   W:=round(((FBody.R.Right-FBody.R.Left)-(FBody.Columns-1)*FBody.Spacing)/FBody.Columns);
   for i:=0 to FBody.Columns-1 do begin
     X:=FBody.R.Left+i*(W+FBody.Spacing);
     FBox:=TColumnBox.Create(FPage,Rect(X,FBody.R.Top,X+W,FBody.R.Bottom),alignLeft);
     FPage.F.Add(FBox);
   end;
 end;
 FPage.FirstColumn(Self);
 FX:=0;
 FY:=0;
end;

Function TPrintEngine.GetLineHeight;
{ Vypocet vysky textoveho radku }
var Pt:TSize;
begin
 SelectObject(FHandle,FFont.Handle);
 GetTextExtentPoint32(FHandle,'A',1,Pt);
 Result:=round(Pt.cy/ScaleY);
end;

Function TPrintEngine.GetTextWidth;
{ Vypocet sirky textu }
var Pt:TSize;
begin
 if Length(AText)>0 then begin
   SelectObject(FHandle,FFont.Handle);
   GetTextExtentPoint32(FHandle,@AText[1],Length(AText),Pt);
   Result:=round(Pt.cx/ScaleX);
 end else
   Result:=0;
end;

Function TPrintEngine.GetTextRect;
{ Vypocet rozmeru textu }
begin
 if Length(AText)>0 then begin
   SelectObject(FHandle,FFont.Handle);
   GetTextExtentPoint32(FHandle,@AText[1],Length(AText),Result);
   Result.cx:=round(Result.cx/ScaleX);
   Result.cy:=round(Result.cy/ScaleY);
 end else begin
   Result.cx:=0;
   Result.cy:=0;
 end; 
end;

Procedure TPrintEngine.PageEnd;
begin
end;

Procedure TPrintEngine.LineFeed;
{ Posunout kurzor o AHowMany radku }
begin
 FY:=FY+AHowMany*GetLineHeight;
end;

Procedure TPrintEngine.Move;
{ Nastavit kurzor na pozadovanou pozici }
begin
 case AOrigin of  { Podle vychoziho mista ... }
   moveLT: begin FX:=0+AX; FY:=0+AY; end;
   moveLM: begin FX:=0+AX; FY:=(FBox.H div 2)+AY; end;
   moveLB: begin FX:=0+AX; FY:=FBox.H+AY; end;
   moveCT: begin FX:=(FBox.W div 2)+AX; FY:=0+AY; end;
   moveCM: begin FX:=(FBox.W div 2)+AX; FY:=(FBox.H div 2)+AY; end;
   moveCB: begin FX:=(FBox.W div 2)+AX; FY:=FBox.H+AY; end;
   moveRT: begin FX:=FBox.W+AX; FY:=0+AY; end;
   moveRM: begin FX:=FBox.W+AX; FY:=(FBox.H div 2)+AY; end;
   moveRB: begin FX:=FBox.W+AX; FY:=FBox.H+AY; end;
 end;
end;

Procedure TPrintEngine.Shift;
{ Posunout kurzor vuci soucasne pozici }
begin
 FX:=FX+ADX;
 FY:=FY+ADY;
end;

Procedure TPrintEngine.CursorReturn;
{ Nastavit kurzor na pravy okraj }
begin
 FX:=0;
end;

Procedure TPrintEngine.FrameBegin;
{ Zanoreni do nove oblasti }
var Box:TFrameBox;
begin
 Box:=TFrameBox.Create(FBox,Rect(FX,FY,min(FX+AWidth,FBox.W),min(FY+AHeight,FBox.H)),FBox.A);
 FBox.F.Add(Box);
 FBox:=Box;
 FX:=0;  { Kurzor vzdy ukazuje lokalni pozici }
 FY:=0;
end;

Procedure TPrintEngine.FrameEnd;
{ Vynoreni ze stavajici oblasti }
begin
 if Assigned(FBox) then begin
   FX:=FBox.R.Right;
   FY:=FBox.R.Top;
   FBox:=TFrameBox(FBox.P);
 end;
end;

Procedure TPrintEngine.Write;
{ Tisk obycejneho textu bez prechodu na novy radek }
var Pt:TSize; X1,X2:integer; R:TRect;
begin
 if Length(AText)>0 then begin
   Pt:=GetTextRect(AText);
   X1:=FX; X2:=FBox.W;
   if FBox.A=alignCenter then X1:=max(X1,(X2+X1-Pt.cx) div 2) else
   if FBox.A=alignRight  then X1:=X2-Pt.cx;
   R:=Rect(X1,FY,X1+Pt.cx,FY+Pt.cy);
   R.Top:=max(0,min(FBox.H,R.Top));
   R.Left:=max(0,min(FBox.W,R.Left));
   R.Bottom:=max(0,min(FBox.H,R.Bottom));
   R.Right:=max(0,min(FBox.W,R.Right));
   FBox.F.Add(TWriteBox.Create(R,AText,FBox.A,FFont));
   FX:=FX+Pt.cx;
 end;
end;

Procedure TPrintEngine.Text;
{ Tisk obycejneho textu bez prechodu na novy radek }

  Procedure P(Str:String; NL:boolean);
  var Pt:TSize; X1,X2:integer; R:TRect;
  begin
   if Length(Str)>0 then begin
     Str:=AutoText(Str);
     Pt:=GetTextRect(Str);
     X1:=FX; X2:=FBox.W;
     if FBox.A=alignCenter then X1:=max(X1,(X2+X1-Pt.cx) div 2) else
     if FBox.A=alignRight  then X1:=X2-Pt.cx;
     R:=Rect(X1,FY,X1+Pt.cx,FY+Pt.cy);
     R.Top:=max(0,min(FBox.H,R.Top));
     R.Left:=max(0,min(FBox.W,R.Left));
     R.Bottom:=max(0,min(FBox.H,R.Bottom));
     R.Right:=max(0,min(FBox.W,R.Right));
     FBox.F.Add(TTextBox.Create(R,Str,FBox.A,FFont));
     FX:=FX+Pt.cx;
     if NL then begin
       LineFeed;
       CursorReturn;
     end;
   end;
  end;

var x:integer;
begin
 if Length(AText)>0 then begin
   x:=pos(#13,AText);
   while (x>0) do begin
     P(copy(AText,1,x-1),true);
     if copy(AText,x+1,1)=#10 then AText:=copy(AText,x+2,Length(AText)-x-1)
                              else AText:=copy(AText,x+1,Length(AText)-x);
     x:=pos(#13,AText);
   end;
   P(AText,false);
 end;
end;

Function TPrintEngine.AutoText;
{ Tisk textu se specialnimi znaky }
var St,i,index:integer; ch:char;
begin
 St:=0; Result:='';
 for i:=1 to Length(AText) do begin
   ch:=AText[i];
   if St=0 then begin
     if ch='#' then St:=1
     else Result:=Result+ch;
   end else begin
     Index:=FReplText.IndexOfname(ch);
     if Index>=0 then begin
       Result:=Result+FReplText.Values[ch];
     end else
       Result:=Result+'#'+ch;
     St:=0;
   end;
 end;
end;

Procedure TPrintEngine.Writeln;
{ Tisk obycejneho textu a prechod na dalsi radek }
begin
 Write(AText);
 LineFeed;
 CursorReturn;
end;

Procedure TPrintEngine.Textln;
{ Tisk textu se specialnimi znaky a prechod na dalsi radek }
begin
 Text(AText);
 LineFeed;
 CursorReturn;
end;

Function TPrintEngine.GetPageCount;
{ Vraci pocet stranek }
begin
 Result:=FPages.Count;
end;

Procedure TPrintEngine.Preview;
{ Vytisknout nahled stranky APage do AImage }
var i,PPIX,PPIY:integer;
begin
 { Nastavit velikost nahledu }
 PPIY:=GetDeviceCaps(AImage.Canvas.Handle,LOGPIXELSY);
 PPIX:=GetDeviceCaps(AImage.Canvas.Handle,LOGPIXELSX);
 ScaleX:=PPIX/100/25.4;
 ScaleY:=PPIY/100/25.4;
 OffsetX:=0;
 OffsetY:=0;
 if not Assigned(AImage.Picture.Bitmap) then
   AImage.Picture.Bitmap:=TBitmap.Create;
 with AImage.Picture.Bitmap do begin
   Width:=round(FWidth*ScaleX);
   Height:=round(FHeight*ScaleY);
 end;
 AImage.Width:=AImage.Picture.Bitmap.Width;
 AImage.Height:=AImage.Picture.Bitmap.Height;
 with AImage.Canvas do begin
   Brush.Style:=bsSolid;
   FillRect(Rect(0,0,AImage.Picture.Bitmap.Width,AImage.Picture.Bitmap.Height));
   Brush.Style:=bsClear;
 end;
 { Najit pozadovanou stranku }
 i:=max(0,min(FPages.Count-1,APage-1));
 FP:=i+1;
 TPrintBox(FPages[i]).Print(Self,Rect(0,0,FWidth,FHeight),AImage.Canvas);
end;

Procedure TPrintEngine.Print;
{ Vytisknout stranky AStart az AStop na tiskarnu }
var i,OFFX,OFFY,PPIX,PPIY:integer;
begin
 { Nastavit velikost nahledu }
 Printer.Title:=FTitle;
 Printer.Orientation:=FPOrient;
 Printer.BeginDoc;
 PPIX:=GetDeviceCaps(Printer.Canvas.Handle,LOGPIXELSX);
 PPIY:=GetDeviceCaps(Printer.Canvas.Handle,LOGPIXELSY);
 OFFX:=GetDeviceCaps(Printer.Canvas.Handle,PHYSICALOFFSETX);
 OFFY:=GetDeviceCaps(Printer.Canvas.Handle,PHYSICALOFFSETY);
 ScaleX:=PPIX/100/25.4;
 ScaleY:=PPIY/100/25.4;
 OffsetX:=-OFFX;
 OffsetY:=-OFFY;
 for i:=AStart to AStop do begin
   FP:=i+1;
   TPageBox(FPages[i]).Print(Self, Rect(0,0,FWidth,FHeight),Printer.Canvas);
   if i<>AStop then Printer.NewPage;
 end;
 Printer.EndDoc;
end;

Function TPrintEngine.TableBegin;
{ Zacatek tabulky }
begin
 FTable:=TTable.Create(FTable);
 FTable.Align:=AAlign;
 FTable.XPad:=HPad;
 FTable.YPad:=VPad;
 FTable.TabWidth:=0;
 Result:=FTable;
end;

Procedure TPrintEngine.TableEnd;
{ Ukoncit tabulku }
var T:TTable;
begin
 if Assigned(FTable) then begin
   if FTable.InCell then TableCellEnd;
   if FTable.InRow  then TableRowEnd;
   T:=FTable.Parent;
   FTable.Free;
   FTable:=T;
 end;
 CursorReturn;
end;

Function TPrintEngine.TableAddCol;
{ Novy sloupec v tabulce }
begin
 Result:=NIL;
 if Assigned(FTable) then begin
   Result:=TTableColumn.Create;
   Result.CellWidth:=AWidth;
   Result.Align:=AAlign;
   FTable.Cols.Add(Result);
   FTable.TabWidth:=FTable.TabWidth+AWidth+2*FTable.XPad;
 end;
end;

Function TPrintEngine.TableAddDiv;
{ Svisly oddelovat v tabulce }
begin
 Result:=NIL;
 if Assigned(FTable) then begin
   Result:=TTableColumn.Create;
   Result.Divider:=true;
   Result.CellWidth:=AWidth;
   FTable.Cols.Add(Result);
 end;
end;

Procedure TPrintEngine.TableLine;
{ Vodorovna cara mezi radky }
var Aux:TColor;
begin
 if Assigned(FTable) then with FTable do begin
   if FTable.InCell then TableCellEnd;
   if FTable.InRow  then TableRowEnd;
   Aux:=Pen.Color;
   Pen.Color:=GridColor;
   CursorReturn;
   if Align=alignCenter then Shift((FBox.W-TabWidth) div 2,0);
   if Align=alignRight  then Shift((FBox.W-TabWidth),0);
   HLine(TabWidth,AWidth);
   Pen.Color:=Aux;
 end;
end;

Procedure TPrintEngine.TableRowBegin;
{ Zacatek radku tabulky }
begin
 if Assigned(FTable) then with FTable do begin
   if InCell then TableCellEnd;
   if InRow then TableRowEnd;
   Col:=0;
   RowHeight:=max(AHeight,GetLineHeight);
   CursorReturn;
   if Align=alignCenter then Shift((FBox.W-TabWidth) div 2,0);
   if Align=alignRight  then Shift((FBox.W-TabWidth),0);
   InRow:=true;
 end;
end;

Procedure TPrintEngine.TableRowEnd;
{ Konec radku tabulky }
var i:integer; C:TTableColumn; Aux:TColor;
begin
 if Assigned(FTable) then with FTable do begin
   if InCell then TableCellEnd;
   if InRow then begin
     for i:=Col to Cols.Count-1 do begin
       C:=Cols[i];
       if C.Divider then begin
         Aux:=Pen.Color; Pen.Color:=GridColor;
         VLine(RowHeight+2*YPad,C.CellWidth);
         Pen.Color:=Aux;
       end else begin
         Shift(C.CellWidth+2*XPad,0);
       end;
     end;
     FY:=FY+RowHeight+YPad*2;
     InRow:=false;
   end;
 end;
end;

Procedure TPrintEngine.TableCellBegin;
{ Zacatek bunky }
var C:TTableColumn; ok:boolean; Aux:TColor; cs,cw:integer;
begin
 if Assigned(FTable) then with FTable do begin
   if InCell then TableCellEnd;
   if not InRow then TableRowBegin;
   ok:=false; C:=NIL;
   while (not ok)and(Col<Cols.Count) do begin
     C:=TTableColumn(Cols[Col]);
     if not C.Divider then begin
       { Je to normalni sloupec - cyklus konci uspesne }
       ok:=true;
     end else begin
       { Je to oddelovac - nakresli caru a pokracuj v cyklu }
       Aux:=Pen.Color; Pen.Color:=GridColor;
       VLine(RowHeight+2*YPad,C.CellWidth);
       Pen.Color:=Aux;
       Col:=Col+1;
     end;
   end;
   if ok then begin
     Shift(XPad,YPad);
     Self.Align:=C.Align;
     CS:=AColSpan; CW:=C.CellWidth;
     while (CS>0)and(Col<Cols.Count) do begin
       Col:=Col+1;
       C:=TTableColumn(Cols[Col]);
       if not C.Divider then begin
         CS:=CS-1;
         CW:=CW+C.CellWidth+2*XPad;
       end;
     end;
     FrameBegin(CW,RowHeight);
     InCell:=true;
   end;
 end;
end;

Procedure TPrintEngine.TableCellEnd;
{ Konec bunky }
begin
 if Assigned(FTable) then with FTable do begin
   if InCell then begin
     FrameEnd;
     Shift(XPad,-YPad);
     Col:=Col+1;
     InCell:=false;
   end;
 end;
end;

Procedure TPrintEngine.HLine;
{ Vodorovna cara }
var L:TLineBox; R:TRect;
begin
 R:=Rect(FX,FY,min(FX+ALength,FBox.W),min(FY,FBox.H));
 L:=TLineBox.Create(R,AWidth,Pen,loHorizontal);
 FBox.F.Add(L);
end;

Procedure TPrintEngine.VLine;
{ Svisla cara }
var L:TLineBox; R:TRect;
begin
 R:=Rect(FX,FY,min(FX,FBox.W),min(FY+ALength,FBox.H));
 L:=TLineBox.Create(R,AWidth,Pen,loVertical);
 FBox.F.Add(L);
end;

Procedure TPrintEngine.Rectangle;
{ Obdelnik }
var L:TRectangleBox; R:TRect;
begin
 R:=Rect(max(-AWidth,FX),max(0,FY),min(FX+AWidth,FBox.W),min(FY+AHeight,FBox.H));
 L:=TRectangleBox.Create(R,AFilled,FBrush,FPen);
 FBox.F.Add(L);
 FX:=L.R.Right;
end;

Procedure TPrintEngine.Ellipse;
{ Elipsa }
var L:TEllipseBox; R:TRect;
begin
 R:=Rect(FX-(AWidth div 2), FY-(AHeight div 2), FX+(AWidth div 2), FY+(AHeight div 2));
 L:=TEllipseBox.Create(R,AFilled,FBrush,FPen);
 FBox.F.Add(L);
end;

Procedure TPrintEngine.Par;
{ Zalamovani radku do odstavcu - znak ~ je nezalomitelna mezera }
var Head,Tail,i,W,MaxW:integer; Str,Text:String; AAlign:TPrintAlign;
begin
 MaxW:=FBox.W;
 AAlign:=FBox.A;
 { Text je Str bez specialnich znaku }
 Text:=AStr; while (pos('~',Text)>0) do Text[pos('~',Text)]:=' ';
 AStr:=AStr+' ';
 W:=GetTextWidth(Text);
 if W<=MaxW-FX then begin
   { Cely text se vleze na jeden radek, neni nutne nic delit }
   if AAlign=alignCenter then Shift((MaxW-FX-W) div 2,0) else
   if AAlign=alignRight  then Shift(MaxW-FX-W,0);
   Writeln(Text);
 end else begin
   Tail:=1; Head:=0;
   for i:=1 to Length(AStr) do begin
     if AStr[i]=' ' then begin
       { Na tomto znaku se da delit, zjistime, jak je to dlouhe }
       if GetTextWidth(copy(Text,Tail,i-Tail))>MaxW-FX then begin
         { Uz se nevleze na jeden radek, vytiskni co se vleze a posun Tail }
         if Head>Tail-1 then begin
           Str:=copy(Text,Tail,Head-Tail);
           W:=GetTextWidth(Str);
           if AAlign=alignCenter then Shift((MaxW-FX-W) div 2,0) else
           if AAlign=alignRight  then Shift(MaxW-FX-W,0);
           Writeln(Str);
           Tail:=Head+1;
         end else begin
           Str:=copy(Text,Tail,i-Tail);
           W:=GetTextWidth(Str);
           if AAlign=alignCenter then Shift((MaxW-FX-W) div 2,0) else
           if AAlign=alignRight  then Shift(MaxW-FX-W,0);
           Writeln(Str);
           Tail:=i+1;
           Head:=i;
         end;
       end else begin
         { Jeste se vejde na jeden radek, posun Head na zacatek slova }
         Head:=i;
       end;
     end;
   end;
   { Jeste se musi zpracovat co zbylo }
   if (Tail<Length(AStr)) then begin
     Str:=copy(Text,Tail,Length(AStr)-Tail+1);
     W:=GetTextWidth(Str);
     if AAlign=alignCenter then Shift((MaxW-FX-W) div 2,0) else
     if AAlign=alignRight  then Shift(MaxW-FX-W,0);
     Writeln(Str);
   end;
 end;
end;

Procedure TPrintEngine.ReplaceDef;
{ Prida novou definici specialniho znaku }
begin
 FReplText.Values[AName]:=AReplaceWith;
end;

procedure TPrintEngine.SetAlign;
{ Nastavi zpusob zarovnavani textu }
begin
 if Assigned(FBox) then FBox.A:=A;
end;

function TPrintEngine.GetAlign;
{ Vraci zpusob zarovnavani textu }
begin
 if Assigned(FBox) then Result:=FBox.A else Result:=alignLeft;
end;

Function TPrintEngine.GetFrameHeight;
{ Vyska aktualni oblasti }
begin
 Result:=FBox.H;
end;

Function TPrintEngine.GetFrameWidth;
{ Sirka aktualni oblasti }
begin
 Result:=FBox.W;
end;

end.
