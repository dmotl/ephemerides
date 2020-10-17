unit SkyDisp;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs, Math,
  Planety;

type
  TSkyEqDisplay = class(TGraphicControl)
   protected
     FBorder,FStars,FBorders,FOutlines,FPlanets,FCrossHair,FMilkyWay:boolean;
     Icons{,Buf}:TBitmap;
     centerX,centerY,widthX,heightY:integer;
     r,xps,xpc,yps,ypc:double;
     FJD,FCenterRA,FCenterDE,FField,FMagLimit:double;
     PlanetObj:TPlanets;
     Function  adxy(alfa,delta:double; var x,y:integer):boolean;
     Function  xyzxy(x0,y0,z0:double; var x,y:integer):boolean;
     Procedure Draw;
     Procedure Paint; override;
     Procedure DrawStars;
     Procedure DrawBorders;
     Procedure DrawOutLines;
     Procedure DrawMilkyWay;
     Procedure DrawPlanets;
     Procedure DrawBorder;
     Procedure DrawCrossHair;
   public
     Constructor Create(AOwner: TComponent); override;
     Destructor  Destroy; override;
     property    Stars:boolean read FStars write FStars;
     property    Borders:boolean read FBorders write FBorders;
     property    Border:boolean read FBorder write FBorder;
     property    MilkyWay:boolean read FMilkyWay write FMilkyWay;
     property    CrossHair:boolean read FCrossHair write FCrossHair;
     property    Outlines:boolean read FOutlines write FOutlines;
     property    Planets:boolean read FPlanets write FPlanets;
     Procedure   SetParams(AJD,ARA,ADEC,AField,AMagLimit:double);
  end;

procedure Register;

implementation

procedure Register;
begin
  RegisterComponents('Astro', [TSkyEqDisplay]);
end;

{$R sky.res}

Constructor TSkyEqDisplay.Create;
begin
 inherited;
 ControlStyle := ControlStyle + [csReplicatable, csOpaque];
 FStars:=true; FOutlines:=true; FPlanets:=true; FBorders:=true;
 FCrossHair:=true; FBorder:=true; FMilkyWay:=true;
 Icons:=TBitmap.Create; Icons.LoadFromResourceName(HInstance,'PLANETS');
 Icons.TransparentMode:=tmAuto; Icons.Transparent:=true;
 PlanetObj:=TPlanets.Create;
 Width := 128;
 Height:= 128;
 FCenterRA:= 0; FCenterDE:=0; FField:=1; FMagLimit:=40;
end;

Destructor TSkyEqDisplay.Destroy;
begin
 PlanetObj.Free;
 Icons.Free;
 inherited;
end;

Procedure TSkyEqDisplay.Paint;
begin
 Canvas.Brush.Color:=clBlack;
 Canvas.Brush.Style:=bsSolid;
 Canvas.Pen.Style:=psClear;
 Canvas.FillRect(Rect(0,0,Width,Height));
 if Borders then DrawBorders;
 if Outlines then DrawOutlines;
 if MilkyWay then DrawMilkyWay;
 if Stars then DrawStars;
 if Planets then DrawPlanets;
 if FBorder then DrawBorder;
 if FCrossHair then DrawCrossHair;
end;

Procedure TSkyEqDisplay.SetParams;
begin
 FJD:=AJD; PlanetObj.SetJD(FJD);
 FCenterRA:=ARA; FCenterDE:=ADEC; FField:=AField; FMagLimit:=AMagLimit;
 draw;
 invalidate;
end;

Procedure TSkyEqDisplay.Draw;
begin
 xps:=sin((6-FCenterRA)*pi/12);
 xpc:=cos((6-FCenterRA)*pi/12);
 yps:=sin((FCenterDE-90)*pi/180);
 ypc:=cos((FCenterDE-90)*pi/180);
 r:=(min(Width,Height) div 2)*180/FField; widthX:=width; heightY:=height;
 CenterX:=Width div 2; CenterY:=Height div 2;
end;

Function TSkyEqDisplay.xyzxy; {Prevod souradnic, zobrazeni na kouli}
var x1,y1,y2:double;
begin
 x1:=(x0*xpc)+(y0*xps); y1:=(x0*xps)-(y0*xpc); y2:=(y1*ypc)+(z0*yps);
 x:=CenterX+round(x1*r); y:=CenterY+round(y2*r); Result:=(y1*yps)<=(z0*ypc);
end;

function TSkyEqDisplay.adxy;   {Prevod souradnic, zobrazeni na kouli}
begin
 Result:=xyzxy(cos(delta)*cos(alfa),-cos(delta)*sin(alfa),sin(delta),x,y);
end;

Procedure TSkyEqDisplay.DrawStars;
type TStar = packed record a:word; d:SmallInt; x,y,z:SmallInt; m,c,g,s:byte; end;
var x,y,i,ResSize,rad:integer;
    Star:TStar;
    Res:HRSRC; HRes:HGLOBAL;
begin
 Res:=FindResource(HInstance,'STARS',RT_RCDATA);
 if (Res>0) then with Canvas do begin
   Pen.Color:=clWhite; Brush.Color:=clWhite; Brush.Style:=bsSolid;
   HRes:=LoadResource(HInstance,Res);
   ResSize:=SizeofResource(HInstance,Res);
   for i:=0 to (ResSize div sizeof(TStar))-1 do begin
     Move(PByteArray(HRes)^[i*sizeof(TStar)],Star,sizeof(TStar));
     if ((Star.m<=FMagLimit)or(Star.m>127))and(xyzxy(Star.x/32767,Star.y/32767,Star.z/32767,x,y))
        and (x>-10)and(y>-10)and(x<WidthX+10)and(y<HeightY+10) then begin
       rad:=trunc((FMagLimit-Star.m)/3);
       if (rad=0) then begin
         Pixels[x,y]:=clLtGray;
       end else
       if (rad<12) then begin
         if (rad>=1) then Pixels[x,y]:=clWhite;
         if (rad>=2) then begin Pixels[x,y+1]:=clWhite; Pixels[x+1,y]:=clWhite; end;
         if (rad>=3) then begin Pixels[x-1,y]:=clWhite; Pixels[x,y-1]:=clWhite; end;
         if (rad>=4) then begin Pixels[x+1,y+1]:=clWhite; Pixels[x-1,y-1]:=clWhite; end;
         if (rad>=5) then begin Pixels[x-1,y+1]:=clWhite; Pixels[x+1,y-1]:=clWhite; end;
         if (rad>=6) then begin Pixels[x+2,y]:=clWhite; Pixels[x-2,y]:=clWhite; end;
         if (rad>=7) then begin Pixels[x,y+2]:=clWhite; Pixels[x,y-2]:=clWhite; end;
         if (rad>=8) then begin Pixels[x-2,y+1]:=clWhite; Pixels[x+2,y-1]:=clWhite; end;
         if (rad>=9) then begin Pixels[x+1,y-2]:=clWhite; Pixels[x-2,y+2]:=clWhite; end;
         if (rad>=10) then begin Pixels[x-2,y-1]:=clWhite; Pixels[x+2,y+1]:=clWhite; end;
         if (rad>=11) then begin Pixels[x-1,y-2]:=clWhite; Pixels[x+2,y+2]:=clWhite; end;
       end else begin
         rad:=round(rad/4);
         Ellipse(x-rad,y-rad,x+rad+1,y+rad+1);
       end;
   //    if (stp.nazvy<5) then begin
   //    if (stp.nazvy>1)and(Star.g mod 32=1)or(stp.nazvy>2)and(Star.g mod 32>0) then outtextgr(x+2,y+2,Star.g mod 32);
   //    if (stp.nazvy>3)and(Star.c>0) then outtextxy(x-11,y-11,chr((Star.c div 10)+48)+chr((Star.c mod 10)+48));
       if (Star.m>FMagLimit)and(Star.m<=127) then exit;
     end;
   end;
 end;
end;

Procedure TSkyEqDisplay.DrawBorders;
type zaznam=packed record
              a1:Word; d1:SmallInt;   { RA, DE 2000 }
              x1,y1,z1:SmallInt; { x, y, z }
              a2:Word; d2:SmallInt;   { RA, DE 2000 }
              x2,y2,z2:SmallInt; { x, y, z }
          end;
var cnt,i,j,ResSize,x,y,x1,y1:integer;  {Pocet hranic, pocet car}
    a1,a2,dx:real;        {Hustota car}
    First:boolean;
    Res:HRSRC; HRes:HGLOBAL;
    z:zaznam;
begin
 Res:=FindResource(HInstance,'BORDERS',RT_RCDATA);
 {Buf.}Canvas.Pen.Color:=clGray;
 {Buf.}Canvas.Pen.Style:=psDot;
 if (Res>0) then begin
   HRes:=LoadResource(HInstance,Res);
   ResSize:=SizeofResource(HInstance,Res);
   for i:=0 to (ResSize div sizeof(zaznam))-1 do with {Buf.}Canvas do begin
     Move(PByteArray(HRes)^[i*sizeof(zaznam)],z,sizeof(zaznam));
     if z.a1>z.a2 then begin a1:=z.a1/65536*pi*2; a2:=(z.a2/65536+1)*pi*2; end
                  else begin a1:=z.a1/65536*pi*2; a2:=(z.a2/65536)*pi*2; end;
     cnt:=2+trunc(abs(a1-a2)*5); {12 minut}
     if cnt>2 then begin
       dx:=(a2-a1)/(cnt-1); { delka segmentu } First:=true;
       for j:=0 to cnt-1 do
         if First then begin
           if adxy((a1+j*dx),z.d1/32767*pi/2,x,y) and (x>-200)and(y>-200)and(x<WidthX+200)and(y<HeightY+200) then begin
             MoveTo(x,y);
             First:=false;
           end;
         end else
         if adxy((a1+j*dx),z.d2/32767*pi/2,x,y) and (x>-200)and(y>-200)and(x<WidthX+200)and(y<HeightY+200) then
           LineTo(x,y)
         else
           First:=true;
     end else
     if xyzxy(z.x1/32767,z.y1/32767,z.z1/32767,x1,y1)
       and (x1>-200)and(y1>-200)and(x1<WidthX+200)and(y1<HeightY+200)
       and xyzxy(z.x2/32767,z.y2/32767,z.z2/32767,x,y)
       and (x>-200)and(y>-200)and(x<WidthX+200)and(y<HeightY+200) then begin
         MoveTo(x1,y1);
         LineTo(x,y);
     end;
   end;
 end;
end;

Procedure TSkyEqDisplay.DrawOutlines;                 {Spojnice souhvezdi}
type zaznam=packed record
              s:byte;
              a1:Word; d1:SmallInt;   { RA, DE 2000 }
              x1,y1,z1:SmallInt; { x, y, z }
              a2:Word; d2:SmallInt;   { RA, DE 2000 }
              x2,y2,z2:SmallInt; { x, y, z }
          end;
var ResSize,x1,y1,x,y,i:integer;
    z:zaznam;
    Res:HRSRC; HRes:HGLOBAL;

begin
 Res:=FindResource(HInstance,'OUTLINES',RT_RCDATA);
 if (Res>0) then with {Buf.}Canvas do begin
   Pen.Color:=clGray;
   Pen.Style:=psSolid;
   HRes:=LoadResource(HInstance,Res);
   ResSize:=SizeofResource(HInstance,Res);
   for i:=0 to (ResSize div sizeof(zaznam))-1 do begin
     Move(PByteArray(HRes)^[i*sizeof(zaznam)],z,sizeof(zaznam));
     if xyzxy(z.x1/32767,z.y1/32767,z.z1/32767,x1,y1)
       and (x1>-200)and(y1>-200)and(x1<WidthX+200)and(y1<HeightY+200)
       and xyzxy(z.x2/32767,z.y2/32767,z.z2/32767,x,y)
       and (x>-200)and(y>-200)and(x<WidthX+200)and(y<HeightY+200) then begin
       MoveTo(x1,y1); LineTo(x,y);
     end;
   end;
 end;
end;

Procedure TSkyEqDisplay.DrawMilkyWay;                    {Mlecna draha}
type rcp=record a,d:SmallInt; end;
     TRecArray=array[0..65535] of rcp;
     PRecArray=^TRecArray;
var x,y,i:integer;
    rc:rcp;
    Res:HRSRC; HRes:HGLOBAL;
    len,bx,by:integer;
begin
 Res:=FindResource(HInstance,'MILKYWAY',RT_RCDATA);
 if (Res>0) then with {Buf.}Canvas do begin
   Pen.Color:=clBlue;
   HRes:=LoadResource(HInstance,Res);
   Len:=SizeofResource(HInstance,Res) div sizeof(rcp);
   Move(PRecArray(HRes)^[0],rc,sizeof(rcp));
   adxy(rc.a*pi/720,rc.d*pi/10800,bx,by);
   i:=1;
   while i<len do begin
     Move(PRecArray(HRes)^[i],rc,sizeof(rcp));
     inc(i);
     if rc.a=high(SmallInt) then begin
       Move(PRecArray(HRes)^[i],rc,sizeof(rcp));
       inc(i);
       adxy(rc.a*pi/720,rc.d*pi/10800,bx,by);
       Move(PRecArray(HRes)^[i],rc,sizeof(rcp));
       inc(i);
     end;
     if adxy(rc.a*pi/720,rc.d*pi/10800,x,y) then begin
       MoveTo(bx,by);
       LineTo(x,y);
     end;
     bx:=x;
     by:=y;
   end;
 end;
end;

Procedure TSkyEqDisplay.DrawPlanets;
var x,y:integer;

 Procedure DrawPlan(x,y,Index:integer);
 begin
   {Buf.}Canvas.CopyMode:=cmPatPaint;
   {Buf.}Canvas.CopyRect(Rect(x-4,y-7,x+4,y+7),Icons.Canvas,Rect(Index*8,0,Index*8+8,14));
 end;

begin
 {Buf.}Canvas.Brush.Color:=clBlack;
 with PlanetObj do begin
   if adxy(alfa1,delta1,x,y) and (x>-10)and(y>-10)and(x<WidthX+10)and(y<HeightY+10) then DrawPlan(x,y,0);
   if adxy(alfa2,delta2,x,y) and (x>-10)and(y>-10)and(x<WidthX+10)and(y<HeightY+10) then DrawPlan(x,y,1);
   if adxy(alfa4,delta4,x,y) and (x>-10)and(y>-10)and(x<WidthX+10)and(y<HeightY+10) then DrawPlan(x,y,2);
   if adxy(alfa5,delta5,x,y) and (x>-10)and(y>-10)and(x<WidthX+10)and(y<HeightY+10) then DrawPlan(x,y,3);
   if adxy(alfa6,delta6,x,y) and (x>-10)and(y>-10)and(x<WidthX+10)and(y<HeightY+10) then DrawPlan(x,y,4);
   if adxy(alfa7,delta7,x,y) and (x>-10)and(y>-10)and(x<WidthX+10)and(y<HeightY+10) then DrawPlan(x,y,5);
   if adxy(alfa8,delta8,x,y) and (x>-10)and(y>-10)and(x<WidthX+10)and(y<HeightY+10) then DrawPlan(x,y,6);
   if adxy(alfa9,delta9,x,y) and (x>-10)and(y>-10)and(x<WidthX+10)and(y<HeightY+10) then DrawPlan(x,y,7);
   if adxy(alfas,deltas,x,y) and (x>-10)and(y>-10)and(x<WidthX+10)and(y<HeightY+10) then DrawPlan(x,y,8);
   if adxy(alfam,deltam,x,y) and (x>-10)and(y>-10)and(x<WidthX+10)and(y<HeightY+10) then DrawPlan(x,y,9);
 end;
end;

Procedure TSkyEqDisplay.DrawCrossHair;
begin
 with Canvas do begin
   Pen.Color:=clWhite;
   MoveTo(CenterX-3,CenterY); LineTo(CenterX-10,CenterY);
   MoveTo(CenterX+3,CenterY); LineTo(CenterX+10,CenterY);
   MoveTo(CenterX,CenterY-3); LineTo(CenterX,CenterY-10);
   MoveTo(CenterX,CenterY+3); LineTo(CenterX,CenterY+10);
 end;
end;

Procedure TSkyEqDisplay.DrawBorder;
begin
with Canvas do begin
   Pen.Color:=clGray;
   MoveTo(0,Height-1);
   LineTo(0,0);
   LineTo(Width-1,0);
   LineTo(Width-1,Height-1);
   LineTo(1,Height-1);
 end;
end;

end.
