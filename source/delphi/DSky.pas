unit DSky;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Planety, Efemer, ExtCtrls, Math, SkyDisp;

type
  TSkyDlg = class(TForm)
    Button1: TButton;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
  private
    Sky:TSkyEqDisplay;
  public
    Procedure Execute(ACaption:String; JD,RA,DEC:double);
  end;

var
  SkyDlg: TSkyDlg;

implementation

{$R *.dfm}

procedure TSkyDlg.Execute;
begin
 Sky.SetParams(JD,RA,DEC,45,60);
 Caption:=ACaption+' - sky chart';
 ShowModal;
end;

procedure TSkyDlg.FormCreate(Sender: TObject);
begin
 Sky:=TSkyEqDisplay.Create(NIL);
 Sky.Left:=8; Sky.Top:=8;
 Sky.Width:=ClientWidth-16; Sky.Height:=Button1.Top-16;
 Sky.Parent:=Self;
end;

procedure TSkyDlg.FormDestroy(Sender: TObject);
begin
 Sky.Parent:=NIL;
 Sky.Free;
end;

end.
