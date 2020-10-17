unit PhDisp;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs, Math;

type
  TPhaseDisplay = class(TGraphicControl)
   protected
     FPhase:integer;
     Procedure Paint; override;
     Procedure SetPhase(AValue:integer);
   public
     Constructor Create(AOwner: TComponent); override;
   published
     property    Phase:integer read FPhase write SetPhase;
  end;

procedure Register;

implementation

procedure Register;
begin
  RegisterComponents('Astro', [TPhaseDisplay]);
end;

Constructor TPhaseDisplay.Create;
begin
 inherited;
 ControlStyle := ControlStyle + [csReplicatable, csOpaque];
 Width := 128;
 Height:= 128;
 FPhase:= 0;
end;

Procedure TPhaseDisplay.Paint;
var r,x0,y0,x:integer;
begin
 Canvas.Brush.Color:=clBlack;
 Canvas.Brush.Style:=bsSolid;
 Canvas.FillRect(Rect(0,0,Width,Height));
 X0:=Width div 2; Y0:=Height div 2; r:=min(X0,Y0);
// Canvas.Draw(X0-r,Y0-r,Buf);
 Canvas.Pen.Color:=cldkGray;
 Canvas.Brush.Style:=bsClear;
 Canvas.Ellipse(X0-r,Y0-r,X0+r,Y0+r);
 Canvas.Brush.Style:=bsSolid;
 Canvas.Brush.Color:=clLtGray;
 x:=round(cos(FPhase/180*pi)*r);
 if (x=0)and(Phase<180) then begin
   Canvas.MoveTo(X0,Y0-r); Canvas.LineTo(X0,Y0+r);
   Canvas.FloodFill(X0+1,Y0,Canvas.Pen.Color,fsBorder);
 end else
 if (x=0)and(Phase>180) then begin
   Canvas.MoveTo(X0,Y0-r); Canvas.LineTo(X0,Y0+r);
   Canvas.FloodFill(X0-1,Y0,Canvas.Pen.Color,fsBorder);
 end else
 if (x>0)and(x<r)and(FPhase<180) then begin
   Canvas.Arc(X0-x-1,Y0-r,X0+x+1,Y0+r,X0,Y0+r,X0,Y0-r);
   if (x<r-1) then Canvas.FloodFill(X0+x+1,Y0,Canvas.Pen.Color,fsBorder);
 end else
 if (x<0)and(x>-r)and(FPhase<180) then begin
   Canvas.Arc(X0+x-1,Y0-r,X0-x+1,Y0+r,X0,Y0-r,X0,Y0+r);
   Canvas.FloodFill(X0+x,Y0,Canvas.Pen.Color,fsBorder);
 end else
 if (x>0)and(x<r)and(FPhase>180) then begin
   Canvas.Arc(X0-x-1,Y0-r,X0+x+1,Y0+r,X0,Y0-r,X0,Y0+r);
   if (x<r-1) then Canvas.FloodFill(X0-x-2,Y0,Canvas.Pen.Color,fsBorder);
 end else
 if (x<0)and(x>-r)and(FPhase>180) then begin
   Canvas.Arc(X0+x-1,Y0-r,X0-x+1,Y0+r,X0,Y0+r,X0,Y0-r);
   Canvas.FloodFill(X0-x-1,Y0,Canvas.Pen.Color,fsBorder);
 end else
 if (Phase>90)and(Phase<270) then begin
   Canvas.FloodFill(X0,Y0,Canvas.Pen.Color,fsBorder);
 end;
end;

Procedure TPhaseDisplay.SetPhase;
begin
 FPhase:=AValue;
 invalidate;
end;

end.
