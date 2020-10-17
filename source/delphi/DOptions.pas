unit DOptions;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, Spin;

type
  TOptionsDlg = class(TForm)
    SaveBtn: TButton;
    CancelBtn: TButton;
    GroupBox2: TGroupBox;
    Label6: TLabel;
    Twilight: TSpinEdit;
    Label7: TLabel;
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
  public
    Function Execute(var ATwilight:integer):boolean;
  end;

var
  OptionsDlg: TOptionsDlg;

implementation

{$R *.dfm}

Function TOptionsDlg.Execute;
begin
 Twilight.Value:=ATwilight;
 if ShowModal=mrOK then begin
   ATwilight:=Twilight.Value;
   Result:=true;
 end else
   Result:=false;
end;

procedure TOptionsDlg.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
begin
 CanClose:=true;
 if (ModalResult=mrOK) then begin
   try
     StrToInt(Twilight.Text);
   except
     CanClose:=false;
     raise Exception.Create('Invalid value of solar elevation angle.');
   end;
 end;
end;

end.

