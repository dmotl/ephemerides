object MoonDlg: TMoonDlg
  Left = 296
  Top = 184
  BorderStyle = bsDialog
  Caption = 'Lunar data'
  ClientHeight = 381
  ClientWidth = 389
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox1: TPaintBox
    Left = 16
    Top = 8
    Width = 153
    Height = 153
    OnPaint = PaintBox1Paint
  end
  object Label1: TLabel
    Left = 8
    Top = 184
    Width = 170
    Height = 20
    AutoSize = False
    Caption = 'Sets'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = False
  end
  object Label2: TLabel
    Left = 8
    Top = 240
    Width = 170
    Height = 20
    AutoSize = False
    Caption = 'Rises'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = False
  end
  object MoonRise: TLabel
    Left = 8
    Top = 264
    Width = 170
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
    Caption = '99. 99. 9999 99:99'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = False
  end
  object MoonSet: TLabel
    Left = 8
    Top = 208
    Width = 170
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
    Caption = '99. 99. 9999 99:99'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = False
  end
  object Label3: TLabel
    Left = 192
    Top = 184
    Width = 185
    Height = 16
    AutoSize = False
    Caption = 'New moon'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = False
  end
  object Label4: TLabel
    Left = 192
    Top = 224
    Width = 185
    Height = 16
    AutoSize = False
    Caption = 'First quarter'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = False
  end
  object FQ: TLabel
    Left = 192
    Top = 240
    Width = 185
    Height = 16
    Alignment = taRightJustify
    AutoSize = False
    Caption = '99. 99. 9999 99:99'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = False
  end
  object NM: TLabel
    Left = 192
    Top = 200
    Width = 185
    Height = 16
    Alignment = taRightJustify
    AutoSize = False
    Caption = '99. 99. 9999 99:99'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = False
  end
  object Label7: TLabel
    Left = 192
    Top = 264
    Width = 185
    Height = 16
    AutoSize = False
    Caption = 'Full moon'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = False
  end
  object Label8: TLabel
    Left = 192
    Top = 304
    Width = 185
    Height = 16
    AutoSize = False
    Caption = 'Last quarter'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = False
  end
  object LQ: TLabel
    Left = 192
    Top = 320
    Width = 185
    Height = 16
    Alignment = taRightJustify
    AutoSize = False
    Caption = '99. 99. 9999 99:99'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = False
  end
  object FM: TLabel
    Left = 192
    Top = 280
    Width = 185
    Height = 16
    Alignment = taRightJustify
    AutoSize = False
    Caption = '99. 99. 9999 99:99'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = False
  end
  object Label5: TLabel
    Left = 192
    Top = 8
    Width = 185
    Height = 16
    AutoSize = False
    Caption = 'Right ascension'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = False
  end
  object MoonA: TLabel
    Left = 192
    Top = 24
    Width = 185
    Height = 16
    Alignment = taRightJustify
    AutoSize = False
    Caption = '23h 59m'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = False
  end
  object Label9: TLabel
    Left = 192
    Top = 48
    Width = 185
    Height = 16
    AutoSize = False
    Caption = 'Declination'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = False
  end
  object MoonD: TLabel
    Left = 192
    Top = 64
    Width = 185
    Height = 16
    Alignment = taRightJustify
    AutoSize = False
    Caption = '99'#176' 99'#39
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = False
  end
  object Label6: TLabel
    Left = 192
    Top = 88
    Width = 185
    Height = 16
    AutoSize = False
    Caption = 'Phase'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = False
  end
  object MoonP: TLabel
    Left = 192
    Top = 104
    Width = 185
    Height = 16
    Alignment = taRightJustify
    AutoSize = False
    Caption = '27 days (waning gibbous)'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = False
  end
  object Label10: TLabel
    Left = 192
    Top = 128
    Width = 185
    Height = 16
    AutoSize = False
    Caption = 'Illumination'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = False
  end
  object MoonI: TLabel
    Left = 192
    Top = 144
    Width = 185
    Height = 16
    Alignment = taRightJustify
    AutoSize = False
    Caption = '100% (trend)'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = False
  end
  object Button1: TButton
    Left = 128
    Top = 344
    Width = 121
    Height = 25
    Cancel = True
    Caption = 'Close'
    Default = True
    ModalResult = 2
    TabOrder = 0
  end
end
