unit Export;

interface

Uses Classes, Math, SysUtils, Tisk;

type
  TExportEngine = class(TObject)
   protected
    FInDocument   : boolean;
    FInParagraph  : boolean;
    FInSection    : boolean;
    FInTable      : boolean;
    FInTableHeader: boolean;
    FInTableRow   : boolean;
    FInTableCell  : boolean;
    FCols, FRow   : TStringList;
    FData         : TList;
    FStr          : String;
    FResult       : PString;

    Procedure OnParagraph(AText:String); virtual; abstract;
    Procedure OnTitle(ATitle:String); virtual; abstract;
    Procedure OnTable(ACols:TStringList; AData:TList); virtual; abstract;

    Procedure OnWrite(AText:String);
    Procedure OnWriteLn(AText:String);

   public
    Constructor Create(var AResult:PString);
    Destructor  Destroy; override;

    { Odstavce }
    Procedure   ParBegin;
                { Zacatek dokumentu }
    Procedure   ParEnd;
                { Konec dokumentu }

    { Nadpisy }
    Procedure   SectBegin;
                { Zacatek dokumentu }
    Procedure   SectEnd;
                { Konec dokumentu }

    { Tabulky }
    Procedure   TableBegin;
                { Zacit novou tabulku (zarovnani, mezery mezi bunkami) }
    Procedure   TableEnd;
                { Ukoncit tabulku }
    Procedure   TableAddCol(AName:String; AAlign:TPrintAlign=alignLeft);
                { Pridej novy sloupec do tabulky }
    Procedure   TableRowBegin;
                { Zacatek radku tabulky }
    Procedure   TableRowEnd;
                { Konec radku tabulky }
    Procedure   TableCellBegin;
                { Zacatek bunky tabulky }
    Procedure   TableCellEnd;
                { Konec bunky tabulky }

    { Texty }
    Procedure   Write(AText:String);
                { Vytisknout text }
  end;

  TTextExport = class(TExportEngine)
   protected
    Procedure OnParagraph(AText:String); override;
    Procedure OnTitle(ATitle:String); override;
    Procedure OnTable(ACols:TStringList; AData:TList); override;
  end;

  TClipboardExport = class(TExportEngine)
   protected
    Procedure OnParagraph(AText:String); override;
    Procedure OnTitle(ATitle:String); override;
    Procedure OnTable(ACols:TStringList; AData:TList); override;
  end;

  TCSVExport = class(TExportEngine)
   protected
    Procedure OnParagraph(AText:String); override;
    Procedure OnTitle(ATitle:String); override;
    Procedure OnTable(ACols:TStringList; AData:TList); override;
   private
    Function Encode(Str:String):String;
  end;

  THTMLExport = class(TExportEngine)
   public
    Constructor Create(ATitle:String; var AResult:PString);
    Destructor  Destroy; override;
   protected
    Procedure OnParagraph(AText:String); override;
    Procedure OnTitle(ATitle:String); override;
    Procedure OnTable(ACols:TStringList; AData:TList); override;
   private
    Function Encode(Str:String):String;
  end;

  TExportFormat = (xfTXT, xfCSV, xfHTML, xfClipboard);

Function CreateExportEngine(AFormat:TExportFormat; ATitle:String; AResult:PString):TExportEngine;

implementation

(*************************   EXPORT BASE CLASS ******************************)

Constructor TExportEngine.Create;
begin
 inherited Create;
 FCols := TStringList.Create;
 FRow  := TStringList.Create;
 FData := TList.Create;
 FResult := AResult;
end;

Destructor TExportEngine.Destroy;
begin
 TableEnd;
 SectEnd;
 ParEnd;
 FCols.Free;
 FData.Free;
 FRow.Free;
 inherited;
end;

Procedure TExportEngine.ParBegin;
begin
 ParEnd;
 SectEnd;
 TableEnd;
 FStr:='';
 FInParagraph:=true;
end;

Procedure TExportEngine.ParEnd;
begin
 if FInParagraph then begin
   OnParagraph(trim(FStr));
   FInParagraph:=false;
 end;
end;

Procedure TExportEngine.SectBegin;
begin
 ParEnd;
 SectEnd;
 TableEnd;
 FStr:='';
 FInSection:=true;
end;

Procedure TExportEngine.SectEnd;
begin
 if FInSection then begin
   OnTitle(trim(FStr));
   FInSection:=false;
 end;
end;

Procedure TExportEngine.TableBegin;
begin
 ParEnd;
 SectEnd;
 TableEnd;
 FCols.Clear;
 FInTable:=true;
 FInTableHeader:=true;
end;

Procedure TExportEngine.TableEnd;
begin
 TableCellEnd;
 TableRowEnd;
 if FInTable then begin
   OnTable(FCols, FData);
   FInTable:=false;
 end;
end;

Procedure TExportEngine.TableAddCol;
begin
 if FInTable and FInTableHeader then begin
   AName:=trim(AName);
   if Length(AName)>0 then
     FCols.Add(AName)
   else
     FCols.Add(' ');
 end;    
end;

Procedure TExportEngine.TableRowBegin;
begin
 TableCellEnd;
 TableRowEnd;
 if FInTable then begin
    FRow.Clear;
    FInTableRow:=true;
 end;
end;

Procedure TExportEngine.TableRowEnd;
var Row:TStringList;
begin
 TableCellEnd;
 if FInTable and FInTableRow then begin
   Row:=TStringList.Create;
   Row.AddStrings(FRow);
   FData.Add(Row);
   FRow.Clear;
   FInTableRow:=true;
 end;
end;

Procedure TExportEngine.TableCellBegin;
begin
 TableCellEnd;
 if FInTable and FInTableRow then begin
   SetLength(FStr, 0);
   FInTableCell:=true;
 end;
end;

Procedure TExportEngine.TableCellEnd;
begin
 if FInTable and FInTableCell then begin
   FStr := trim(FStr);
   if Length(FStr)>0 then
     FRow.Add(FStr)
   else
     FRow.Add(' ');
   FInTableCell:=false;
 end;
end;

Procedure TExportEngine.Write;
begin
  FStr := FStr + AText;
end;

Procedure TExportEngine.OnWrite;
begin
 FResult^ := FResult^ + AText;
end;

Procedure TExportEngine.OnWriteLn;
begin
 FResult^ := FResult^ + AText + #13#10;
end;

(*************************   TEXT FORMAT ******************************)

Procedure TTextExport.OnParagraph;
var i:integer;
begin
 while Length(AText)>0 do begin
   i:=Pos('\n', AText);
   if (i>0) then begin
     OnWriteLn('    '+Trim(Copy(AText, 0, i-1)));
     AText:=Copy(AText, i+2, Length(AText)-i-2);
   end else begin
     OnWriteLn('    '+Trim(AText));
     AText:='';
   end;
 end;
 // Oddelovaci radek
 OnWriteLn(' ');
end;

Procedure TTextExport.OnTitle;
var len:integer;
    S:String;
begin
 // Text
 len:=Length(ATitle);
 OnWriteLn(ATitle);

 // Podtrzeni
 SetLength(S, len);
 FillChar(S[1], len, ord('='));
 OnWriteLn(S);

 // Oddelovaci radek
 OnWriteLn(' ');
end;

Procedure TTextExport.OnTable;
var w,s:array of integer;
    i,j,len,col:integer;
    Txt,Buf:String;
begin
 col:=ACols.Count;
 SetLength(w, col);
 SetLength(s, col);

 // Vypocitej delky poli
 for j:=0 to col-1 do
   w[j]:=Length(ACols[j]);
 for i:=0 to FData.Count-1 do begin
   for j:=0 to min(col-1, TStrings(AData[i]).Count) do
     w[j] := max(w[j], Length(TStrings(AData[i]).Strings[j]));
 end;
 // Vypocitej pocatecni pozice
 s[0]:=1;
 for i:=1 to col-1 do
   s[i] := s[i-1]+w[i-1]+1;
 // Celkova delka radku
 len:=s[col-1]+w[col-1];

 // Zahlavi tabulky
 SetLength(Txt, len);
 fillchar(Txt[1], len, ord(' '));
 for j:=0 to col-1 do begin
   Buf:=ACols[j];
   if Length(Buf)>0 then
     System.Move(Buf[1], Txt[s[j]], Length(Buf));
 end;
 OnWriteLn(Txt);

 // Oddelovaci radek
 fillchar(Txt[1], len, ord('-'));
 OnWriteLn(Txt);

 // Radky tabulky
 for i:=0 to AData.Count-1 do begin
   fillchar(Txt[1], len, ord(' '));
   for j:=0 to min(col-1, TStrings(AData[i]).Count) do begin
     Buf:=TStrings(AData[i]).Strings[j];
     if Length(Buf)>0 then
       System.Move(Buf[1], Txt[s[j]], Length(Buf));
   end;
   OnWriteLn(Txt);
 end;
 SetLength(w, 0);
 SetLength(s, 0);

 // Oddelovaci radek
 fillchar(Txt[1], len, ord('-'));
 OnWriteLn(Txt);
 OnWriteLn(' ');
end;

(*************************   CLIPBOARD FORMAT ******************************)

Procedure TClipboardExport.OnParagraph;
begin
end;

Procedure TClipboardExport.OnTitle;
begin
end;

Procedure TClipboardExport.OnTable;
var i,j,col:integer;
    Txt:String;
begin
 col:=ACols.Count;

 // Zahlavi tabulky
 Txt:='';
 for j:=0 to col-1 do begin
   if Length(Txt)>0 then Txt:=Txt+#9;
   Txt:=Txt+ACols[j];
 end;
 OnWriteLn(Txt);

 // Radky tabulky
 for i:=0 to AData.Count-1 do begin
   Txt:='';
   for j:=0 to min(col-1, TStrings(AData[i]).Count) do begin
     if Length(Txt)>0 then Txt:=Txt+#9;
     Txt:=Txt+TStrings(AData[i]).Strings[j];
   end;
   OnWriteLn(Txt);
 end;
end;

(************************   CSV FORMAT **************************)

Procedure TCSVExport.OnParagraph;
var i:integer;
begin
 while Length(AText)>0 do begin
   i:=Pos('\n', AText);
   if (i>0) then begin
     OnWriteLn('# '+Trim(Copy(AText, 0, i-1)));
     AText:=Copy(AText, i+2, Length(AText)-i-2);
   end else begin
     OnWriteLn('# '+Trim(AText));
     AText:='';
   end;
 end;
 // Oddelovaci radek
 OnWriteLn('# ');
end;

Procedure TCSVExport.OnTitle;
var len:integer;
    S:String;
begin
 // Text
 len:=Length(ATitle);
 OnWriteLn('# '+ATitle);

 // Podtrzeni
 SetLength(S, len);
 FillChar(S[1], len, ord('='));
 OnWriteLn('# '+S);

 // Oddelovaci radek
 OnWriteLn('# ');
end;

Procedure TCSVExport.OnTable;
var i, j, col:integer;
    Buf, Txt:String;
begin
 col:=ACols.Count;

 // Zahlavi tabulky
 Txt:='';
 for j:=0 to col-1 do begin
   if Length(Txt)>0 then
     Txt:=Txt+',';
   Buf:=trim(ACols[j]);
   Txt:=Txt+'"'+Encode(Buf)+'"';
 end;
 OnWriteLn(Txt);

 // Radky tabulky
 for i:=0 to AData.Count-1 do begin
   Txt:='';
   for j:=0 to min(col-1, TStrings(AData[i]).Count) do begin
     if Length(Txt)>0 then
       Txt:=Txt+',';
     Buf:=trim(TStrings(AData[i]).Strings[j]);
     Txt:=Txt+'"'+Encode(Buf)+'"';
   end;
   OnWriteLn(Txt);
 end;
end;

Function TCSVExport.Encode;
var i:integer;
    ch:char;
begin
 Result:='';
 for i:=1 to Length(Str) do begin
   ch:=Str[i];
   if ch='"' then
     Result:=Result+'""'
   else
     Result:=Result+ch;
 end;
end;

(************************   HTML FORMAT **************************)

Constructor THTMLExport.Create(ATitle:String; var AResult:PString);
begin
 inherited Create(AResult);
 OnWriteLn('<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">');
 OnWriteLn('<html>');
 OnWriteLn('<head>');
 OnWriteLn('<title>'+ATitle+'</title>');
 OnWriteLn('<meta http-equiv="Content-Type" content="text/html; charset=Windows1250">');
 OnWriteLn('</head>');
 OnWriteLn('<body>');
end;

Destructor THTMLExport.Destroy;
begin
 ParEnd;
 SectEnd;
 TableEnd;
 OnWriteLn('</body>');
 OnWriteLn('</html>');
 inherited;
end;

Procedure THTMLExport.OnParagraph;
begin
 OnWriteLn('<p style="margin-left:32px">'+Encode(AText)+'</p>');
end;

Procedure THTMLExport.OnTitle;
begin
 OnWriteLn('<h1>'+Encode(ATitle)+'</h1>');
end;

Procedure THTMLExport.OnTable;
var i, j, col:integer;
    Buf, Txt:String;
begin
 col:=ACols.Count;

 OnWriteLn('<table>');

 // Zahlavi tabulky
 Txt:='';
 for j:=0 to col-1 do begin
   Buf:=trim(ACols[j]);
   if Length(Buf)>0 then
     Txt:=Txt+'<th>'+Encode(Buf)+'</th>'
   else
     Txt:=Txt+'<th>&nbsp;</th>'
 end;
 OnWriteLn('<tr>'+Txt+'</tr>');

 // Radky tabulky
 for i:=0 to AData.Count-1 do begin
   Txt:='';
   for j:=0 to min(col-1, TStrings(AData[i]).Count) do begin
     Buf:=trim(TStrings(AData[i]).Strings[j]);
     if Length(Buf)>0 then
       Txt:=Txt+'<td>'+Encode(Buf)+'</td>'
     else
       Txt:=Txt+'<td>&nbsp;</td>';
   end;
   OnWriteLn('<tr>'+Txt+'</tr>');
 end;

  OnWriteLn('</table>');
end;

Function THTMLExport.Encode;
var i, len:integer;
    ch:char;
begin
 Result:='';
 i:=1;  len:=Length(Str);
 while (i<=len) do begin
   ch:=Str[i];
   if ch='<' then
     Result:=Result+'&lt;'
   else if ch='&' then
     Result:=Result+'&amp;'
   else if (ch='\') then begin
     ch:=Str[i+1];
     if (ch='n') then
       Result:=Result+'<br>';
     i:=i+1;
   end else if ch>=' ' then
     Result:=Result+ch;
   i:=i+1;
 end;
end;

(************************   CLASS FACTORY **************************)

Function CreateExportEngine;
begin
 case AFormat of
   xfTXT: Result:=TTextExport.Create(AResult);
   xfCSV: Result:=TCSVExport.Create(AResult);
   xfHTML: Result:=THTMLExport.Create(ATitle, AResult);
   xfClipboard: Result:=TClipboardExport.Create(AResult);
 else
   raise Exception.Create('Unsupported format');
 end;
end;


end.

