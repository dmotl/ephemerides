object ConstDlg: TConstDlg
  Left = 266
  Top = 251
  BorderStyle = bsDialog
  Caption = 'List of constellations'
  ClientHeight = 309
  ClientWidth = 432
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
  object FList: TCheckListBox
    Left = 8
    Top = 8
    Width = 417
    Height = 249
    Columns = 5
    ItemHeight = 13
    TabOrder = 0
  end
  object SaveBtn: TButton
    Left = 344
    Top = 272
    Width = 81
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 4
  end
  object CancelBtn: TButton
    Left = 256
    Top = 272
    Width = 81
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
  end
  object SelectAllBtn: TButton
    Left = 95
    Top = 272
    Width = 81
    Height = 25
    Caption = 'Select all'
    TabOrder = 1
    OnClick = SelectAllBtnClick
  end
  object ClearBtn: TButton
    Left = 8
    Top = 272
    Width = 81
    Height = 25
    Caption = 'Clear'
    TabOrder = 2
    OnClick = ClearBtnClick
  end
end
