object InfoBox: TInfoBox
  Left = 502
  Top = 164
  Width = 200
  Height = 374
  BorderStyle = bsSizeToolWin
  Caption = 'InfoBox'
  Color = clBtnFace
  Constraints.MinHeight = 250
  Constraints.MinWidth = 200
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 192
    Height = 347
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 0
    OnChange = FormResize
    object TabSheet1: TTabSheet
      Caption = 'Variable star'
      object IGrid: TStringGrid
        Left = 0
        Top = 0
        Width = 245
        Height = 425
        Align = alClient
        ColCount = 2
        DefaultColWidth = 128
        DefaultRowHeight = 16
        FixedRows = 0
        TabOrder = 0
        RowHeights = (
          16
          16
          16
          16
          16)
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Ephemeris'
      ImageIndex = 1
      object EGrid: TStringGrid
        Left = 0
        Top = 0
        Width = 184
        Height = 319
        Align = alClient
        ColCount = 2
        DefaultColWidth = 128
        DefaultRowHeight = 16
        FixedRows = 0
        TabOrder = 0
        RowHeights = (
          16
          16
          16
          16
          16)
      end
    end
  end
end
