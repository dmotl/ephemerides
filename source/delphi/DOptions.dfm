object OptionsDlg: TOptionsDlg
  Left = 266
  Top = 251
  BorderStyle = bsDialog
  Caption = 'Geographical position'
  ClientHeight = 119
  ClientWidth = 288
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object SaveBtn: TButton
    Left = 192
    Top = 88
    Width = 89
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object CancelBtn: TButton
    Left = 96
    Top = 88
    Width = 89
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 0
    Width = 273
    Height = 73
    Caption = 'Twilight'
    TabOrder = 2
    object Label6: TLabel
      Left = 8
      Top = 22
      Width = 203
      Height = 13
      Caption = 'The nighttime is when the Sun is more than'
    end
    object Label7: TLabel
      Left = 136
      Top = 46
      Width = 127
      Height = 13
      Caption = 'degrees below the horizon.'
    end
    object Twilight: TSpinEdit
      Left = 64
      Top = 40
      Width = 65
      Height = 22
      MaxLength = 2
      MaxValue = 90
      MinValue = 0
      TabOrder = 0
      Value = 0
    end
  end
end
