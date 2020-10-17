unit IniFile;
interface
{
Spolecna unita pro cely program. Zajistuje cteni, ukladani a modifikaci parametru
textoveho konfiguracniho souboru.

Navratovy kod urcuje pripadnou chybu.

Chyby nedulezite
0  = Bez chyby
1  = Pri zapisu vytvorena nova polozka, protoze dosud neexistovala
2  = Pri zapisu vytvorena nova sekce, protoze dosud neexistovala
4  = Pri zapisu vytvoren novy soubor, protoze dosud neexistoval

Chyby dulezite
8  = Polozka nenalezena (Klic, Sekce)
16 = Polozka nalezena, ale je v jinem formatu ( napr. ocekava se Integer a je tam String )
32 = Soubor neexistuje
64 = Nepovedlo se ulozit soubor ( Fatalni !)

}

Uses Classes, SysUtils, StrUtils, Windows, Math;

Type TIniFile=Class(TStringList)
  Private
   Procedure Rozloz(Rad:Integer;out Sekce:boolean; out Klic,Hodnota,Poznamka:String);
             { Vrati jednotlive polozky radku }
   Function  Spoj(Sekce:boolean; Klic, Hodnota, Poznamka:String):String;
             { Ulozi jednotlive komponenty radku }
   Function  HledejKey(Key:String; out ARow:integer; out AValue,AMemo:String):Boolean;
             { Hleda klic v aktivni sekci }
   Function  HledejStr(Str:String; out ARow:integer; out AValue,AMemo:String):Boolean;
             { Hleda retezec v aktivni sekci }
   Function  HledejSec(Key:String; OdR, DoR:Integer; out ARow:integer):boolean;
             { Hleda sekci. Vraci cislo radku nebo -1 pokud neni }
   Function  StrToText(Hodnota:String):String;
             { Pokud retezec obsahuje ridici znaky, zakoduje se }
  Public
   MyFile:String;      { Jmeno prave zpracovavaneho souboru }
   SecName:String;     { Jmeno prave aktivni sekce }
   SecBegin,SecEnd:Integer; {Zacatek a konec aktivni sekce}
   Error:Boolean;      { True, pokud je zavazna chyba }
   ErrCode:Byte;       { Cislo chyby }
   TimeStamp:Boolean;  { Jestli do poznamky ukladat datum a cas modifikace }
   BakFile:Boolean;    { Jestli delat zalozni kopie souboru }

   { SOUBOR }
   Function Load(FileName:String):Boolean; overload;
   {# Otevreni souboru, nacteni obsahu, prvni sekce se nastavi jako aktivni }
   Function Load(F:TStream):Boolean; overload;
   {# Otevreni souboru, nacteni obsahu, prvni sekce se nastavi jako aktivni }
   Function ReLoad:Boolean;
   {# Otevreni souboru, nacteni obsahu, prvni sekce se nastavi jako aktivni }
   Function Save:Boolean; overload;
   {# Ulozeni souboru }
   Function Save(F:TStream):Boolean; overload;
   {# Ulozeni souboru }
   Function SaveAs(FileName:String):Boolean;
   {# Ulozi soubor pod novym jmenem }
   Procedure Clear; override;
   {# Kompletni vymaz vsech klicu i hodnot v pameti }

   { SEKCE }
   Function OpenSec(Sekce:String; AutoCreate:Boolean=false; Poznamka:String=''):Boolean;
   {# Nastavit aktivni sekci, vytvoreni nove sekce }
   Procedure ClearSec;
   {# Vymaze obsah sekce }
   Procedure DeleteSec;
   {# Vymaze celou aktivni sekci }
   Procedure ListSec(Seznam:TStrings);
   {# Vrati seznam vsech sekci }
   Procedure ReadSec(Lines:TStrings; Comments:TStrings=NIL);
   {# Cteni cele aktivni sekce jako seznam retezcu }
   Procedure WriteSec(Lines:TStrings; Comments:TStrings=NIL);
   {# Zapis cele aktivni sekce jako seznam retezcu }

   { HODNOTY - vzdy plati pro aktivni sekci (pri otevreni souboru je to prvni) }
   Function  Read(Klic:String; out Hodnota,Poznamka:String):boolean;
   {# Interni cteni hodnoty klice. Vraci true, pokud je definovana }
   Function ReadStr(Klic:String; Default:String=''):String;
   {# Cteni textove hodnoty }
   Function ReadInt(Klic:String; Default:integer=0):integer;
   {# Cteni ciselne hodnoty }
   Function ReadBool(Klic:String; Default:boolean=false):Boolean;
   {# Cteni logicke hodnoty }
   Function ReadDouble(Klic:String; Default:double=0.0):Double;
   {# Cteni realne hodnoty }
   Procedure Write(Klic,Hodnota:String; Poznamka:String='');
   {# Cteni hodnoty }
   Procedure WriteStr(Klic:String; Hodnota:String; Poznamka:String='');
   {# Modifikace texove hodnoty }
   Procedure WriteInt(Klic:String; Cislo:Integer; Poznamka:String='');
   {# Modifikace konkretni ciselne hodnoty. }
   Procedure WriteBool(Klic:String; Bool:Boolean; Poznamka:String='');
   {# Modifikace konkretni logicke hodnoty }
   Procedure WriteDouble(Klic:String; Hodnota:Double; Prec:byte=2; Poznamka:String='');
   {# Modifikace konkretni znakove hodnoty na Prec desetinnych mist }
   Procedure DeleteStr(Str:String);
   {# Vymaze radek s klicem Str nebo retezcem Str }
   Procedure InsertStr(AValue:String; AMemo:String='');
   {# Vlozi radek s retezcem AValue }
   Procedure WriteMemo(AMemo:String);
   {# Zapis radek s poznamkou AMemo }
   Function  Exists(Str:String):boolean;
   {# Vraci TRUE, pokud klic Str nebo retezec Str je definovan v aktivni sekci }
 end;

implementation

{ ******************************************************** }
{ *** INTERNI FUNKCE PRO PRACI S INI SOUBORY               }
{ ******************************************************** }

Function TIniFile.StrToText;
var Str:String; Quot:boolean; i:integer; ch:char;
begin
 { Testuje se, zda retezec obsahuje ridici znaky }
 Str:=''; Quot:=false;
 for i:=1 to Length(Hodnota) do begin
   Quot:=Quot or (Hodnota[i] in [#0..#31,'#','"']);
   if Quot then break;
 end;
 if Quot then begin
   { Je-li nutne zakodovani, provede se prevod }
   for i:=1 to Length(Hodnota) do begin
     ch:=Hodnota[i];
     if (ch=#13) then
     else if (ch=#10) then Str:=Str+'\n'
     else if (ch=#9)  then Str:=Str+'\t'
     else if (ch<#32) then Str:=Str+'\'+Format('%.3d',[ord(ch)])
     else if (ch='\') then Str:=Str+'\\'
     else if (ch='"') then Str:=Str+'\"'
     else Str:=Str+ch;
   end;
   Result:='"'+Str+'"';
 end else
   Result:=Hodnota;
end;

Procedure TIniFile.Rozloz;
{ Vrati jednotlive polozky radku Rad }
var l:String; i,St,Spec:integer; ch:char; Quot,Key:boolean;
begin
Klic:=''; Hodnota:=''; Poznamka:=''; Sekce:=false; Spec:=0;
St:=0; Quot:=false; Key:=false;
if (Rad>=0)and(Rad<Count) then begin
  l:=Strings[Rad];
  { Rozloz na Klic, Hodnotu a Poznamku }
  for i:=1 to length(l) do begin
     ch:=l[i];
     case St of
       0: begin   { Pocatecni znaky }
           if ch<#33 then
           else if ch='[' then begin Sekce:=true; St:=8 end
           else if ch='#' then St:=6
           else begin
             Klic:=Klic+ch;       { Prvni znak klice }
             St:=1;
           end;
          end;
       1: begin   { Znaky klice }
           if ch<#33 then
           else if ch='=' then begin Key:=true; St:=2; end
           else if ch='#' then St:=7
           else begin
             Klic:=Klic+ch;
             St:=1;
           end;
          end;
       2: begin  { Znaky mezi rovnitkem a hodnotou }
           if ch<#33 then
           else if ch='"' then begin Quot:=true; St:=4 end
           else if ch='#' then St:=7
           else begin
             Hodnota:=Hodnota+ch;  { Prvni znak hodnoty }
             St:=3;
           end;
          end;
       3: begin  { Znaky hodnoty neuzavrene do uvozovek }
           if ch<#32 then
           else if ch='#' then St:=7
           else Hodnota:=Hodnota+ch;
          end;
       4: begin  { Znaky hodnoty uzavrene do uvozovek }
           if ch='\' then St:=5
           else if ch='"' then St:=6
           else Hodnota:=Hodnota+ch;
          end;
       5: begin { Specialni znaky hodnoty uzavrene do uvozovek }
           St:=4;
           if ch='n' then Hodnota:=Hodnota+#13#10
           else if ch='t' then Hodnota:=Hodnota+#9
           else if ch='\' then Hodnota:=Hodnota+'\'
           else if ch='"' then Hodnota:=Hodnota+'"'
           else if (ch>='0')and(ch<='2') then begin Spec:=ord(ch)-ord('0'); St:=10 end
           else Hodnota:=Hodnota+ch;
          end;
       6: begin { Cekani, jestli nebude poznamka }
           if ch='#' then St:=7
          end;
       7: begin { Cekani, nez zacne text poznamky }
           if ch<#33 then
           else begin
             Poznamka:=Poznamka+ch;   { Prvni znak poznamky }
             St:=9;
           end;
          end;
       8: begin { Znaky sekce }
           if ch=']' then begin St:=6 end
           else if ch>=#32 then Klic:=Klic+ch;
          end;
       9: begin { Poznamka }
           if ch<#32 then
           else Poznamka:=Poznamka+ch;
          end;
      10: begin { Druhy znak specialniho kodu }
           if (ch>='0')or(ch<'9') then begin Spec:=Spec*10+(ord(ch)-ord('0')); St:=11 end
           else begin Hodnota:=Hodnota+ch; St:=4; end;
          end;
      11: begin { Posledni znak specialniho kodu }
           if (ch>='0')or(ch<'9') then begin
             Spec:=Spec*10+(ord(ch)-ord('0'));
             Hodnota:=Hodnota+chr(Spec mod 256);     { Zapis znak }
             St:=4;
           end
           else begin Hodnota:=Hodnota+ch; St:=4; end;
          end;
     end;
  end;
  Klic:=trim(Klic);
  if not Quot then Hodnota:=trim(Hodnota);
  if not Key and not Sekce then begin Hodnota:=Klic; Klic:=''; end;   { Retezec bez klice }
  Poznamka:=trim(Poznamka);
  Error:=False;
  ErrCode:=0;
end else begin
  { Je pozadovan zaznam, ktery je jiz za tabulkou, ohlasime chybu }
  Error:=True;
  ErrCode:=8;
end;
end;

Function TIniFile.Spoj;
var i:integer;
begin
 if Sekce then begin
   Result:='['+trim(Klic)+']';
 end else
 if Klic='' then begin
   Result:=trim(Hodnota);
 end else begin
   Result:=trim(Klic)+' = '+trim(Hodnota);
 end;
 if Length(Poznamka)>0 then begin
   if Length(Result)>0 then begin
     for i:=Length(Result) to 30 do Result:=Result+' ';
     Result:=Result+' # '+trim(Poznamka);
   end else
     Result:='# '+trim(Poznamka);
 end;
end;

Function TIniFile.HledejKey;
{ Hleda klic v aktivni sekci. Vraci TRUE, pokud nalezl a v ARow cislo radku }
var kl,ho,po:String; Sec:boolean; odr,dor,n:Integer;
begin
 { Inicializace a kontrola rozsahu }
 Result:=false;
 OdR:=max(0,SecBegin+1);
 DoR:=min(Count-1,SecEnd);
 ARow:=OdR; AValue:=''; AMemo:='';
 for n:=OdR to DoR do begin
   { Hleda se od OdR do DoR radek s klicem Key }
   Rozloz(n,sec,kl,ho,po);
   if not sec and (UpperCase(Key)=UpperCase(kl)) then begin
     Result:=true;
     ARow:=n;
     AValue:=ho;
     AMemo:=po;
     break;
   end;
 end;
end;

Function TIniFile.HledejStr;
{ Hleda retezec v aktivni sekci. Vraci TRUE, pokud nalezl a v ARow cislo radku }
var kl,ho,po:String; Sec:boolean; odr,dor,n:Integer;
begin
 { Inicializace a kontrola rozsahu }
 Result:=false;
 OdR:=max(0,SecBegin+1);
 DoR:=min(Count-1,SecEnd);
 ARow:=OdR; AValue:=''; AMemo:='';
 for n:=OdR to DoR do begin
   { Hleda se od OdR do DoR radek s klicem Key }
   Rozloz(n,sec,kl,ho,po);
   if not sec and (Uppercase(Str)=Uppercase(Ho)) then begin
     Result:=true;
     ARow:=n;
     AValue:=ho;
     AMemo:=po;
     break;
   end;
 end;
end;

Function TIniFile.HledejSec;
{ Hleda vyskyt sekce v zadanem rozmezi }
var kl,ho,po:String; sec:boolean; n:Integer;
begin
 Result:=false;
 OdR:=max(0,OdR);
 DoR:=min(Count-1,DoR);
 ARow:=OdR;
 For n:=OdR to DoR do begin
   { Hleda se od OdR do DoR sekce s nazvem Key nebo prvni sekce, je-li Key='' }
   Rozloz(n,sec,kl,ho,po);
   if Sec and ((UpperCase(Key)=UpperCase(Kl))or(Key='')) then begin
     Result:=true;
     ARow:=n;
     break;
   end;
 end;
end;

Function TIniFile.Read;
{ Cteni hodnoty }
var x:Integer;
begin
 if (Length(Klic)>0)and(SecBegin>=0)and(SecEnd>=SecBegin) and HledejKey(Klic,x,Hodnota,Poznamka) then begin
   Result:=true;
   Error:=False;
   ErrCode:=0;
 end else begin
   Result:=false;
   Error:=True;
   ErrCode:=8;
 end;
end;

Procedure TIniFile.Write;
{ Modifikace hodnoty }
var x:Integer;
    h,p:String;
begin
 if Length(Klic)>0 then begin
   if (SecBegin>=0)and(SecEnd>=SecBegin) then begin
     if HledejKey(Klic,x,h,p) then begin
       { Ano, polozka existuje, modifikujeme }
       if Length(Poznamka)=0 then Poznamka:=p;
       Put(x,Spoj(false,Klic,Hodnota,Poznamka));
     end else begin
       { Musi se vlozit polozka nova }
       x:=SecEnd;
       while (x>SecBegin) and (Strings[x]='') do dec(x);
       Insert(x+1,Spoj(false,Klic,Hodnota,Poznamka));
       Inc(SecEnd);
     end;
     ErrCode:=0;
     Error:=false;
   end else begin
     Error:=True;
     ErrCode:=8;
   end;
 end;
end;

{ ******************************************************** }
{ *** FUNKCE PRO CTENI A ZAPIS DO SOUBORU                  }
{ ******************************************************** }

Function TIniFile.ReLoad:Boolean;
{ Otevreni souboru, nacteni obsahu, prvni sekce se nastavi jako aktivni }
begin
 Try
   LoadFromFile(MyFile);
   CaseSensitive:=False;
   Sorted:=False;
   OpenSec('');
   Error:=False;
   ErrCode:=0;
   Result:=True;
 except
   Result:=False;
   Error:=True;
   ErrCode:=32;
 end;
end;

Function TIniFile.Load(FileName:String):Boolean;
{ Otevreni souboru, nacteni obsahu, prvni sekce se nastavi jako aktivni }
begin
 MyFile:=FileName;
 Result:=Reload;
end;

Function TIniFile.Load(F:TStream):Boolean;
{ Otevreni souboru, nacteni obsahu, prvni sekce se nastavi jako aktivni }
begin
 Try
   MyFile:='';
   LoadFromStream(F);
   CaseSensitive:=False;
   Sorted:=False;
   OpenSec('');
   Error:=False;
   ErrCode:=0;
   Result:=True;
 except
   Result:=False;
   Error:=True;
   ErrCode:=32;
 end;
end;

Function TIniFile.Save:Boolean;
{ Ulozeni souboru }
begin
 if BakFile then begin
   try
     { Pokud je to povoleno, z puvodniho souboru se udela old }
     CopyFile(PChar(MyFile),PChar(MyFile+'.Old'),false);
   Except
   end;
 end;
 Try
   SaveToFile(MyFile);
   Error:=False;
   ErrCode:=0;
   Result:=True;
 Except
   ErrCode:=64;
   Error:=True;
   Result:=False;
 end;
end;

Function TIniFile.Save(F:TStream):Boolean;
{ Ulozeni souboru }
begin
 Try
   MyFile:=''; 
   SaveToStream(F);
   Error:=False;
   ErrCode:=0;
   Result:=True;
 Except
   ErrCode:=64;
   Error:=True;
   Result:=False;
 end;
end;

Function TIniFile.SaveAs(FileName:String):Boolean;
{ Ulozi soubor pod novym jmenem }
begin
 MyFile:=FileName;
 Result:=Save;
end;

{ ******************************************************** }
{ *** FUNKCE PRO PRACI S OBSAHEM SOUBORU                   }
{ ******************************************************** }

Procedure TIniFile.Clear;
{ Kompletni vymaz vsech klicu i hodnot v pameti }
begin
 inherited Clear;
 SecName:='';
 SecBegin:=0;
 SecEnd:=0;
end;

{ ******************************************************** }
{ *** FUNKCE PRO PRACI S AKTIVNI SEKCI                     }
{ ******************************************************** }

Function TIniFile.OpenSec;
{ Nastavit aktivni sekci }
var r,x:Integer; kl,ho,po:String; Sec:boolean;
begin
{ Inicializace promennych }
SecName:=Sekce;
SecBegin:=0;
SecEnd:=Count-1;
r:=8;
{ Hledej zacatek sekce }
if SecEnd>=SecBegin then begin
  { Kdyz soubor neni prazdny }
  if Length(Sekce)>0 then begin
    { Hledej sekci se zadanym jmenem }
    if HledejSec(Sekce,SecBegin,SecEnd,SecBegin) then r:=0;
  end else begin
    { Hledej prvni sekci }
    if HledejSec('',SecBegin,SecEnd,SecBegin) then r:=0;
  end;
end;
if r=0 then begin
  { Kdyz nasel sekci, hleda jeji konec }
  if (HledejSec('',SecBegin+1,SecEnd,x)) then SecEnd:=x-1;
  if Sekce='' then begin
    { Nebylo-li jmeno sekce zadano, tak zrovna jeji jmeno vyplnime }
    Rozloz(SecBegin,Sec,kl,ho,po);
    if sec then SecName:=Kl;
  end;
  ErrCode:=0;
  Error:=false;
end else
if AutoCreate and (length(SecName)>0) then begin
  { Kdyz sekce neexistuje, zkusime ji vytvorit }
  if Count>0 then Add('');
  Add(Spoj(true,Sekce,'',Poznamka));
  SecName:=Sekce;
  SecBegin:=Count-1;
  SecEnd:=Count-1;
  ErrCode:=0;
  Error:=false;
end else begin
  SecName:='';
  SecBegin:=-1;
  SecEnd:=-1;
  ErrCode:=8;
  Error:=true;
end;
Result:=r=0;
end;

Procedure TIniFile.DeleteSec;
{ Vymaze celou aktivni sekci }
var i:Integer;
begin
 if (SecBegin>=0)and(SecEnd>=SecBegin) then begin
   { Vymazou se radky sekce z pameti }
   for i:=SecBegin to SecEnd do delete(SecBegin);
   { Zrusi se aktivni sekce }
   SecName:='';
   SecBegin:=-1;
   SecEnd:=-1;
   ErrCode:=0;
   Error:=false;
 end else begin
   Error:=true;
   ErrCode:=8;
 end;
end;

Procedure TIniFile.ClearSec;
{ Vymaze obsah aktivni sekce }
var i:Integer;
begin
 if (SecBegin>=0)and(SecEnd>=SecBegin) then begin
   { Vymazou se radky sekce z pameti }
   for i:=SecBegin+1 to SecEnd do delete(SecBegin+1);
   { Zrusi se aktivni sekce }
   SecEnd:=SecBegin;
   ErrCode:=0;
   Error:=false;
 end else begin
   Error:=true;
   ErrCode:=8;
 end;
end;

Procedure TIniFile.ListSec;
{ Vrati seznam vsech sekci v souboru }
var a:Integer; sec:boolean; k,h,p:String;
begin
 Seznam.BeginUpdate;
 Seznam.Clear;
 for a:=0 to Count-1 do begin
   rozloz(a,sec,k,h,p);
   if sec then Seznam.Add(k);
 end;
 Seznam.EndUpdate;
end;

Procedure TIniFile.ReadSec;
{ Vraci cely obsah sekce }
var i:integer; sec:boolean; k,h,p:String;
begin
 if (SecBegin>=0)and(SecEnd>=SecBegin) then begin
   if Assigned(Lines) then Lines.BeginUpdate;
   if Assigned(Lines) then Lines.Clear;
   if Assigned(Comments) then Comments.BeginUpdate;
   if Assigned(Comments) then Comments.Clear;
   for i:=SecBegin+1 to SecEnd do begin
     rozloz(i,sec,k,h,p);
     if (not sec) and (Length(h)>0)or(Length(k)>0) then begin
       { Uklada dvojice klic=hodnota nebo jen klic }
       if Assigned(Lines) then begin
         if (Length(k)>0) then lines.Add(k+'='+h) else lines.Add(h);
       end;
       if Assigned(Comments) then Comments.Add(ifthen(Length(p)>0,p,' '));
     end;
   end;
   if Assigned(Lines) then Lines.EndUpdate;
   if Assigned(Comments) then Comments.EndUpdate;
   ErrCode:=0;
   Error:=false;
 end else begin
   Error:=true;
   ErrCode:=8;
 end;
end;

Procedure TIniFile.WriteSec;
{ Uklada cely obsah sekce }
var i:integer;
begin
 if (SecBegin>=0)and(SecEnd>=SecBegin) then begin
   { Zrusit stavajici obsah sekce }
   for i:=SecBegin+1 to SecEnd do delete(SecBegin+1);
   SecEnd:=SecBegin;
   { Vsechny retezce z lines prepsat do pameti }
   for i:=0 to lines.Count-1 do begin
     if Assigned(Comments) and (i<Comments.Count) then
       Insert(SecEnd+1,spoj(false,'',lines[i],comments[i]))
     else
       Insert(SecEnd+1,spoj(false,'',lines[i],''));
     inc(SecEnd);   
   end;
   Insert(SecEnd+1,'');
   Inc(SecEnd);
   ErrCode:=0;
   Error:=false;
 end else begin
   Error:=true;
   ErrCode:=8;
 end;
end;

{ ******************************************************** }
{ *** FUNKCE PRO PRACI S HODNOTAMI                         }
{ ******************************************************** }

Function TIniFile.ReadStr;
{ Cteni textove hodnoty }
var p:String;
begin
 if not Read(Klic,Result,p) then Result:=Default;
end;

Procedure TIniFile.WriteStr;
{ Modifikace textove hodnoty }
begin
 Write(Klic,StrToText(Hodnota),Poznamka);
end;

Function TIniFile.ReadInt;
{ Cteni celociselne hodnoty }
var h,p:String;
begin
 if Read(Klic,h,p) then begin
   Result:=StrToIntDef(h,Default);
 end else begin
   Result:=Default;
 end;
end;

Procedure TIniFile.WriteInt;
{ Modifikace celociselne hodnoty. }
begin
 Write(Klic,IntToStr(Cislo),Poznamka);
end;

Function TIniFile.ReadBool;
{ Cteni logicke hodnoty:
  ANO, A, TRUE, T, ON, <>0  => true
  NE, N, FALSE, F, OFF   0  => false }
var h,p:String; v:integer;
begin
 if Read(Klic,h,p) then begin
   h:=UpperCase(h);
   Result:= (h='ON') or (Copy(h,1,1)='A') or (Copy(h,1,1)='T') or
            (TryStrToInt(h,v) and (v>0));
 end else begin
   Result:=Default;
 end;
end;

Procedure TIniFile.WriteBool;
{ Modifikace logicke hodnoty }
begin
 Write(Klic,ifthen(bool,'ON','OFF'),Poznamka);
end;

Function TIniFile.ReadDouble;
{ Cteni realne hodnoty }
var h,p:String;
begin
 if Read(Klic,h,p) then begin
   Result:=StrToFloatDef(h,Default);
 end else begin
   Result:=Default;
 end;
end;

Procedure TIniFile.WriteDouble;
{ Modifikace konkretni znakove hodnoty na Prec desetinnych mist }
begin
 Write(Klic,Format('%.*f',[Prec,Hodnota]),Poznamka);
end;

Procedure TIniFile.DeleteStr;
{ Vymaze radek s hodnotou }
var x:Integer; h,p:String;
begin
 if Length(Str)>0 then begin
   ErrCode:=8;
   if (SecBegin>=0)and(SecEnd>=SecBegin) then begin
     if HledejKey(Str,x,h,p) then begin
       delete(x);
       ErrCode:=0;
       Dec(SecEnd);
     end else
     if HledejStr(Str,x,h,p) then begin
       delete(x);
       ErrCode:=0;
       Dec(SecEnd);
     end;
   end;
   Error:=ErrCode>0;
 end;  
end;

Procedure TIniFile.InsertStr;
var x:Integer;
    h,p:String;
begin
 if Length(AValue)>0 then begin
   if (SecBegin>=0)and(SecEnd>=SecBegin) then begin
     if HledejKey(AValue,x,h,p) then begin
       { Ano, polozka existuje, modifikujeme }
       if Length(AMemo)=0 then AMemo:=p;
       Put(x,Spoj(false,'',AValue,AMemo));
     end else
     if HledejStr(AValue,x,h,p) then begin
       { Ano, polozka existuje, modifikujeme }
       if Length(AMemo)=0 then AMemo:=p;
       Put(x,Spoj(false,'',AValue,AMemo));
     end else begin
       { Musi se vlozit polozka nova }
       x:=SecEnd;
       while (x>SecBegin) and (Strings[x]='') do dec(x);
       Insert(x+1,Spoj(false,'',AValue,AMemo));
       Inc(SecEnd);
     end;
     ErrCode:=0;
     Error:=false;
   end else begin
     Error:=True;
     ErrCode:=8;
   end;
 end;
end;

Function TIniFile.Exists;
var x:Integer;
    h,p:String;
begin
 if (SecBegin>=0)and(SecEnd>=SecBegin) then begin
   Result:=HledejKey(Str,x,h,p) or HledejStr(Str,x,h,p);
   ErrCode:=0;
   Error:=false;
 end else begin
   Result:=false;
   Error:=True;
   ErrCode:=8;
 end;
end;

Procedure TIniFile.WriteMemo;
{ Zapis radku s poznamkou }
var l:String; 
begin
 if Length(AMemo)>0 then begin
   l:=spoj(false,'','',AMemo);
   if SecEnd>=Count then Add(l) else insert(SecEnd+1,l);
   Inc(SecEnd);
   ErrCode:=0;
   Error:=false;
 end;
end;

end.
