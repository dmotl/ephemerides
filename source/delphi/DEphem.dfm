object MainForm: TMainForm
  Left = 40
  Top = 164
  Width = 912
  Height = 646
  Caption = 'Ephemerides of eclipsing binary stars'
  Color = clBtnFace
  Constraints.MinHeight = 580
  Constraints.MinWidth = 786
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Pages: TPageControl
    Left = 0
    Top = 0
    Width = 904
    Height = 600
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 0
    OnChange = PagesChange
    object TabSheet1: TTabSheet
      Caption = 'Daily ephemerides'
      object Panel2: TPanel
        Left = 192
        Top = 0
        Width = 704
        Height = 572
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object List: TListView
          Left = 0
          Top = 36
          Width = 704
          Height = 536
          Align = alClient
          Columns = <
            item
              Caption = 'Name'
              MaxWidth = 600
              MinWidth = 32
              Width = 170
            end
            item
              Caption = 'PS'
              MinWidth = 28
              Width = 28
            end
            item
              Alignment = taCenter
              Caption = 'Date'
              MaxWidth = 400
              Width = 70
            end
            item
              Alignment = taCenter
              Caption = 'UT'
              MaxWidth = 400
              Width = 37
            end
            item
              Alignment = taCenter
              Caption = 'Az.'
              MaxWidth = 400
              MinWidth = 32
              Width = 44
            end
            item
              Alignment = taCenter
              Caption = 'Alt.'
              MaxWidth = 400
              MinWidth = 32
              Width = 40
            end
            item
              Alignment = taCenter
              Caption = 'R.A.'
              MaxWidth = 400
              MinWidth = 32
              Width = 42
            end
            item
              Alignment = taCenter
              Caption = 'DEC.'
              MaxWidth = 400
              MinWidth = 32
              Width = 42
            end
            item
              Alignment = taCenter
              Caption = 'Type'
              MaxWidth = 400
              MinWidth = 32
              Width = 80
            end
            item
              Alignment = taCenter
              Caption = 'Mag'
              MaxWidth = 400
              MinWidth = 32
              Width = 64
            end
            item
              Alignment = taCenter
              Caption = 'Catalogue'
              MaxWidth = 400
              MinWidth = 32
              Width = 74
            end
            item
              Alignment = taCenter
              Caption = 'Pts.'
              MaxWidth = 400
              MinWidth = 32
              Width = 40
            end
            item
              Alignment = taCenter
              Caption = 'Obj-Moon'
              MaxWidth = 400
              MinWidth = 32
              Width = 64
            end
            item
              Caption = 'Remarks'
              MaxWidth = 400
              MinWidth = 32
              Width = 144
            end>
          HideSelection = False
          MultiSelect = True
          ReadOnly = True
          RowSelect = True
          PopupMenu = ListMenu
          SortType = stData
          TabOrder = 0
          ViewStyle = vsReport
          OnColumnClick = ListColumnClick
          OnCompare = ListCompare
          OnCustomDrawItem = ListCustomDrawItem
          OnDblClick = InfoBtnClick
          OnKeyDown = ListKeyDown
          OnSelectItem = ListSelectItem
        end
        object ToolBar1: TToolBar
          Left = 0
          Top = 0
          Width = 704
          Height = 36
          AutoSize = True
          ButtonHeight = 36
          ButtonWidth = 42
          Caption = 'ToolBar1'
          EdgeBorders = []
          EdgeInner = esNone
          EdgeOuter = esNone
          Flat = True
          Images = ImageList
          ShowCaptions = True
          TabOrder = 1
          Wrapable = False
          object RunBtn: TToolButton
            Left = 0
            Top = 0
            Hint = 'Compute ephemerides matching specified conditions'
            Caption = 'Update'
            ImageIndex = 7
            ParentShowHint = False
            ShowHint = True
            OnClick = RunBtnClick
          end
          object SortBtn: TToolButton
            Left = 42
            Top = 0
            Hint = 'Sort found minima by...'
            Caption = 'Sort'
            DropdownMenu = Sort1Menu
            ImageIndex = 3
            ParentShowHint = False
            ShowHint = True
          end
          object DelBtn: TToolButton
            Left = 84
            Top = 0
            Hint = 'Delete selected minimum from the table'
            Caption = 'Delete'
            ImageIndex = 2
            ParentShowHint = False
            ShowHint = True
            OnClick = DelBtnClick
          end
          object InfoBtn: TToolButton
            Left = 126
            Top = 0
            Hint = 'Show detailed information on selected minimum'
            Caption = 'Details'
            ImageIndex = 4
            ParentShowHint = False
            ShowHint = True
            OnClick = InfoBtnClick
          end
          object FindBtn: TToolButton
            Left = 168
            Top = 0
            Hint = 'Find a string'
            Caption = 'Find'
            ImageIndex = 11
            ParentShowHint = False
            ShowHint = True
            OnClick = FindBtnClick
          end
          object ToolButton2: TToolButton
            Left = 210
            Top = 0
            Width = 8
            Caption = 'ToolButton2'
            ImageIndex = 1
            Style = tbsSeparator
          end
          object PrintBtn: TToolButton
            Left = 218
            Top = 0
            Hint = 'Print ephemerides on printer'
            Caption = 'Print'
            ImageIndex = 1
            ParentShowHint = False
            ShowHint = True
            OnClick = PrintBtnClick
          end
          object SaveBtn: TToolButton
            Left = 260
            Top = 0
            Hint = 'Save ephemerides to file'
            Caption = 'Save'
            ImageIndex = 13
            ParentShowHint = False
            ShowHint = True
            OnClick = SaveBtnClick
          end
          object CopyBtn: TToolButton
            Left = 302
            Top = 0
            Hint = 'Copy ephemerides to clipboard'
            Caption = 'Copy'
            ImageIndex = 12
            ParentShowHint = False
            ShowHint = True
            OnClick = CopyBtnClick
          end
          object ToolButton4: TToolButton
            Left = 344
            Top = 0
            Width = 8
            Caption = 'ToolButton4'
            ImageIndex = 7
            Style = tbsSeparator
          end
          object SunBtn: TToolButton
            Left = 352
            Top = 0
            Hint = 'Show solar data for selected night'
            Caption = 'Sun'
            ImageIndex = 5
            ParentShowHint = False
            ShowHint = True
            OnClick = SunBtnClick
          end
          object MoonBtn: TToolButton
            Left = 394
            Top = 0
            Hint = 'Show lunar data for selected night'
            Caption = 'Moon'
            ImageIndex = 6
            ParentShowHint = False
            ShowHint = True
            OnClick = MoonBtnClick
          end
          object SkyBtn: TToolButton
            Left = 436
            Top = 0
            Hint = 'Show the location of the selected variable star'
            Caption = 'Chart'
            ImageIndex = 8
            ParentShowHint = False
            ShowHint = True
            OnClick = SkyBtnClick
          end
          object ToolButton5: TToolButton
            Left = 478
            Top = 0
            Width = 8
            Caption = 'ToolButton5'
            ImageIndex = 10
            Style = tbsSeparator
          end
          object SetupBtn: TToolButton
            Left = 486
            Top = 0
            Hint = 'Edit user preferences'
            Caption = 'Setup'
            ImageIndex = 14
            OnClick = ObserverBtnClick
          end
          object ToolButton1: TToolButton
            Left = 528
            Top = 0
            Width = 8
            Caption = 'ToolButton1'
            ImageIndex = 9
            Style = tbsSeparator
          end
          object HelpBtn: TToolButton
            Left = 536
            Top = 0
            Hint = 'Open electronic help'
            Caption = 'Help'
            DropdownMenu = HelpMenu
            ImageIndex = 9
            ParentShowHint = False
            ShowHint = True
          end
        end
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 192
        Height = 572
        Align = alLeft
        BevelOuter = bvNone
        TabOrder = 1
        DesignSize = (
          192
          572)
        object Label2: TLabel
          Left = 8
          Top = 48
          Width = 64
          Height = 13
          Caption = 'Catalogues'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label1: TLabel
          Left = 8
          Top = 8
          Width = 162
          Height = 13
          Caption = 'Date (local, before midnight)'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label3: TLabel
          Left = 99
          Top = 253
          Width = 9
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'to'
        end
        object Label6: TLabel
          Left = 24
          Top = 253
          Width = 20
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'from'
        end
        object Label7: TLabel
          Left = 162
          Top = 253
          Width = 20
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'mag'
        end
        object Label4: TLabel
          Left = 99
          Top = 141
          Width = 9
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'to'
        end
        object Label5: TLabel
          Left = 24
          Top = 141
          Width = 20
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'from'
        end
        object Label8: TLabel
          Left = 162
          Top = 141
          Width = 9
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'hr'
        end
        object Label9: TLabel
          Left = 99
          Top = 205
          Width = 9
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'to'
        end
        object Label10: TLabel
          Left = 24
          Top = 205
          Width = 20
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'from'
        end
        object Label11: TLabel
          Left = 162
          Top = 205
          Width = 18
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'deg'
        end
        object Label12: TLabel
          Left = 99
          Top = 349
          Width = 9
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'to'
        end
        object Label13: TLabel
          Left = 24
          Top = 349
          Width = 20
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'from'
        end
        object Label14: TLabel
          Left = 162
          Top = 349
          Width = 9
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'hr'
        end
        object Label15: TLabel
          Left = 99
          Top = 397
          Width = 9
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'to'
        end
        object Label16: TLabel
          Left = 24
          Top = 397
          Width = 20
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'from'
        end
        object Label17: TLabel
          Left = 162
          Top = 397
          Width = 18
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'deg'
        end
        object Label19: TLabel
          Left = 99
          Top = 301
          Width = 9
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'to'
        end
        object Label20: TLabel
          Left = 24
          Top = 301
          Width = 20
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'from'
        end
        object Label21: TLabel
          Left = 162
          Top = 301
          Width = 14
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'pts'
        end
        object Label33: TLabel
          Left = 24
          Top = 541
          Width = 20
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'from'
        end
        object Label34: TLabel
          Left = 99
          Top = 541
          Width = 9
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'to'
        end
        object Label35: TLabel
          Left = 162
          Top = 541
          Width = 18
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'deg'
        end
        object Label39: TLabel
          Left = 8
          Top = 105
          Width = 35
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Filters'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Cats: TCheckListBox
          Left = 8
          Top = 64
          Width = 177
          Height = 41
          Hint = 'Check catalogue files, which you want to use'
          Anchors = [akLeft, akTop, akBottom]
          ItemHeight = 13
          ParentShowHint = False
          PopupMenu = CatalogMenu
          ShowHint = True
          TabOrder = 1
        end
        object Date: TDateTimePicker
          Left = 8
          Top = 24
          Width = 177
          Height = 21
          Hint = 'Enter date of observation (before midnight)'
          Date = 38166.918542002300000000
          Time = 38166.918542002300000000
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
        end
        object MagF: TCheckBox
          Left = 8
          Top = 233
          Width = 177
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Brightness in minimum'
          TabOrder = 13
          OnClick = UpdateControls
        end
        object MinF: TCheckBox
          Left = 8
          Top = 121
          Width = 177
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Time of minimum (UT)'
          Checked = True
          State = cbChecked
          TabOrder = 2
          OnClick = Min2Change
        end
        object AltF: TCheckBox
          Left = 8
          Top = 185
          Width = 177
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Altitude'
          Checked = True
          State = cbChecked
          TabOrder = 8
          OnClick = Alt2Change
        end
        object RAF: TCheckBox
          Left = 8
          Top = 329
          Width = 177
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Right ascension'
          TabOrder = 23
          OnClick = UpdateControls
        end
        object DecF: TCheckBox
          Left = 8
          Top = 377
          Width = 177
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Declination'
          TabOrder = 28
          OnClick = UpdateControls
        end
        object PTSF: TCheckBox
          Left = 8
          Top = 281
          Width = 177
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Rating (points]'
          TabOrder = 18
          OnClick = UpdateControls
        end
        object Mag1SB: TSpinButton
          Left = 80
          Top = 249
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Mag1
          TabOrder = 15
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = MagDownClick
          OnUpClick = MagUpClick
        end
        object Mag1: TEdit
          Left = 48
          Top = 249
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 2
          TabOrder = 14
          OnExit = Mag1Exit
        end
        object Mag2: TEdit
          Left = 112
          Top = 249
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 2
          TabOrder = 16
          OnExit = Mag1Exit
        end
        object Mag2SB: TSpinButton
          Left = 144
          Top = 249
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Mag2
          TabOrder = 17
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = MagDownClick
          OnUpClick = MagUpClick
        end
        object Min1: TEdit
          Left = 48
          Top = 137
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 4
          TabOrder = 3
          OnChange = Min2Change
          OnExit = Min2Exit
        end
        object Min1SB: TSpinButton
          Left = 80
          Top = 137
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Min1
          TabOrder = 4
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = MinDownClick
          OnUpClick = MinUpClick
        end
        object Min2: TEdit
          Left = 112
          Top = 137
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 4
          TabOrder = 5
          OnChange = Min2Change
          OnExit = Min2Exit
        end
        object Min2SB: TSpinButton
          Left = 144
          Top = 137
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Min2
          TabOrder = 6
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = MinDownClick
          OnUpClick = MinUpClick
        end
        object Alt1: TEdit
          Left = 48
          Top = 201
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 3
          TabOrder = 9
          OnChange = Alt2Change
          OnExit = Alt2Exit
        end
        object Alt1SB: TSpinButton
          Left = 80
          Top = 201
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Alt1
          TabOrder = 10
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = AltDownClick
          OnUpClick = AltUpClick
        end
        object Alt2: TEdit
          Left = 112
          Top = 201
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 3
          TabOrder = 11
          OnChange = Alt2Change
          OnExit = Alt2Exit
        end
        object Alt2SB: TSpinButton
          Left = 144
          Top = 201
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Alt2
          TabOrder = 12
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = AltDownClick
          OnUpClick = AltUpClick
        end
        object RA1: TEdit
          Left = 48
          Top = 345
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 4
          TabOrder = 24
          OnExit = Min2Exit
        end
        object Ra1SB: TSpinButton
          Left = 80
          Top = 345
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = RA1
          TabOrder = 25
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = MinDownClick
          OnUpClick = MinUpClick
        end
        object RA2: TEdit
          Left = 112
          Top = 345
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 4
          TabOrder = 26
          OnExit = Min2Exit
        end
        object Ra2SB: TSpinButton
          Left = 144
          Top = 345
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = RA2
          TabOrder = 27
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = MinDownClick
          OnUpClick = MinUpClick
        end
        object Dec1: TEdit
          Left = 48
          Top = 393
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 3
          TabOrder = 29
          OnExit = Alt2Exit
        end
        object Dec1SB: TSpinButton
          Left = 80
          Top = 393
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Dec1
          TabOrder = 30
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = AltDownClick
          OnUpClick = AltUpClick
        end
        object Dec2: TEdit
          Left = 112
          Top = 393
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 3
          TabOrder = 31
          OnExit = Alt2Exit
        end
        object Dec2SB: TSpinButton
          Left = 144
          Top = 393
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Dec2
          TabOrder = 32
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = AltDownClick
          OnUpClick = AltUpClick
        end
        object Pts2SB: TSpinButton
          Left = 144
          Top = 297
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Pts2
          TabOrder = 22
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = MagDownClick
          OnUpClick = MagUpClick
        end
        object Pts2: TEdit
          Left = 112
          Top = 297
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 2
          TabOrder = 21
          OnExit = Mag1Exit
        end
        object Pts1SB: TSpinButton
          Left = 80
          Top = 297
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Pts1
          TabOrder = 20
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = MagDownClick
          OnUpClick = MagUpClick
        end
        object Pts1: TEdit
          Left = 48
          Top = 297
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 2
          TabOrder = 19
          OnExit = Mag1Exit
        end
        object AZF: TCheckBox
          Left = 8
          Top = 521
          Width = 177
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Azimuth (N->E->S->W)'
          Checked = True
          State = cbChecked
          TabOrder = 36
          OnClick = AZFClick
        end
        object Az1: TEdit
          Left = 48
          Top = 537
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 3
          TabOrder = 37
          OnChange = AZFClick
          OnExit = AzExit
        end
        object Az1SB: TSpinButton
          Left = 80
          Top = 537
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Az1
          TabOrder = 38
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = AzDownClick
          OnUpClick = AzUpClick
        end
        object Az2: TEdit
          Left = 112
          Top = 537
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 3
          TabOrder = 39
          OnChange = AZFClick
          OnExit = AzExit
        end
        object Az2SB: TSpinButton
          Left = 144
          Top = 537
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Az2
          TabOrder = 40
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = AzDownClick
          OnUpClick = AzUpClick
        end
        object FNight: TCheckBox
          Left = 24
          Top = 163
          Width = 153
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'during nighttime'
          Checked = True
          State = cbChecked
          TabOrder = 7
          OnClick = FNightClick
        end
        object ConF: TCheckBox
          Left = 8
          Top = 425
          Width = 177
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Constellations (space separated)'
          TabOrder = 33
          OnClick = UpdateControls
        end
        object Con: TEdit
          Left = 24
          Top = 441
          Width = 137
          Height = 21
          Anchors = [akLeft, akRight, akBottom]
          MaxLength = 512
          TabOrder = 34
        end
        object ConBtn: TButton
          Left = 160
          Top = 441
          Width = 25
          Height = 21
          Anchors = [akRight, akBottom]
          Caption = '...'
          TabOrder = 35
          OnClick = ConBtnClick
        end
        object TypF: TCheckBox
          Left = 8
          Top = 473
          Width = 177
          Height = 17
          Anchors = [akLeft, akBottom]
          Caption = 'Var. types (space separated)'
          TabOrder = 41
          OnClick = UpdateControls
        end
        object Typ: TEdit
          Left = 24
          Top = 489
          Width = 137
          Height = 21
          Anchors = [akLeft, akRight, akBottom]
          MaxLength = 512
          TabOrder = 42
        end
        object TypBtn: TButton
          Left = 159
          Top = 489
          Width = 25
          Height = 21
          Anchors = [akRight, akBottom]
          Caption = '...'
          TabOrder = 43
          OnClick = TypBtnClick
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Star ephemerides'
      ImageIndex = 1
      object Panel3: TPanel
        Left = 192
        Top = 0
        Width = 704
        Height = 572
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object List2: TListView
          Left = 0
          Top = 36
          Width = 704
          Height = 536
          Align = alClient
          Columns = <
            item
              Caption = 'Date'
              MaxWidth = 250
              MinWidth = 32
              Width = 70
            end
            item
              Alignment = taCenter
              Caption = 'UT'
              MaxWidth = 250
              MinWidth = 32
              Width = 37
            end
            item
              Alignment = taCenter
              Caption = 'Day of week'
              MaxWidth = 250
              MinWidth = 32
              Width = 74
            end
            item
              Alignment = taCenter
              Caption = 'Julian date'
              MaxWidth = 250
              MinWidth = 32
              Width = 80
            end
            item
              Alignment = taCenter
              Caption = 'Epoch'
              MaxWidth = 250
              MinWidth = 32
              Width = 64
            end
            item
              Caption = 'PS'
              MinWidth = 28
              Width = 28
            end
            item
              Alignment = taCenter
              Caption = 'Az.'
              MaxWidth = 250
              MinWidth = 32
              Width = 44
            end
            item
              Alignment = taCenter
              Caption = 'Alt.'
              MaxWidth = 250
              MinWidth = 32
              Width = 44
            end
            item
              Alignment = taCenter
              Caption = 'Moon'
              MaxWidth = 250
              MinWidth = 32
              Width = 60
            end
            item
              Alignment = taCenter
              Caption = 'Obj-Moon'
              MaxWidth = 250
              MinWidth = 32
              Width = 60
            end>
          HideSelection = False
          MultiSelect = True
          ReadOnly = True
          RowSelect = True
          PopupMenu = ListMenu
          SortType = stData
          TabOrder = 0
          ViewStyle = vsReport
          OnColumnClick = List2ColumnClick
          OnCompare = List2Compare
          OnCustomDrawItem = ListCustomDrawItem
          OnDblClick = InfoBtnClick
          OnKeyDown = List2KeyDown
          OnSelectItem = ListSelectItem
        end
        object ToolBar2: TToolBar
          Left = 0
          Top = 0
          Width = 704
          Height = 36
          AutoSize = True
          ButtonHeight = 36
          ButtonWidth = 42
          Caption = 'ToolBar1'
          EdgeBorders = []
          EdgeInner = esNone
          EdgeOuter = esNone
          Flat = True
          Images = ImageList
          ShowCaptions = True
          TabOrder = 1
          Wrapable = False
          object Run2Btn: TToolButton
            Left = 0
            Top = 0
            Hint = 'Compute ephemerides matching specified conditions'
            Caption = 'Update'
            ImageIndex = 7
            ParentShowHint = False
            ShowHint = True
            OnClick = Run2BtnClick
          end
          object Sort2Btn: TToolButton
            Left = 42
            Top = 0
            Hint = 'Sort found minima by...'
            Caption = 'Sort'
            DropdownMenu = Sort2Menu
            ImageIndex = 3
            ParentShowHint = False
            ShowHint = True
          end
          object Del2Btn: TToolButton
            Left = 84
            Top = 0
            Hint = 'Delete selected minimum from the table'
            Caption = 'Delete'
            ImageIndex = 2
            ParentShowHint = False
            ShowHint = True
            OnClick = Del2BtnClick
          end
          object Info2Btn: TToolButton
            Left = 126
            Top = 0
            Hint = 'Show detailed information on selected minimum'
            Caption = 'Details'
            ImageIndex = 4
            ParentShowHint = False
            ShowHint = True
            OnClick = InfoBtnClick
          end
          object Find2Btn: TToolButton
            Left = 168
            Top = 0
            Hint = 'Find a string'
            Caption = 'Find'
            ImageIndex = 11
            ParentShowHint = False
            ShowHint = True
            OnClick = Find2BtnClick
          end
          object ToolButton7: TToolButton
            Left = 210
            Top = 0
            Width = 8
            Caption = 'ToolButton2'
            ImageIndex = 1
            Style = tbsSeparator
          end
          object Print2Btn: TToolButton
            Left = 218
            Top = 0
            Hint = 'Print ephemerides on printer'
            Caption = 'Print'
            ImageIndex = 1
            ParentShowHint = False
            ShowHint = True
            OnClick = Print2BtnClick
          end
          object Save2Btn: TToolButton
            Left = 260
            Top = 0
            Hint = 'Save ephemerides to file'
            Caption = 'Save'
            ImageIndex = 13
            ParentShowHint = False
            ShowHint = True
            OnClick = Save2BtnClick
          end
          object Copy2Btn: TToolButton
            Left = 302
            Top = 0
            Hint = 'Copy ephemerides to clipboard'
            Caption = 'Copy'
            ImageIndex = 12
            ParentShowHint = False
            ShowHint = True
            OnClick = Copy2BtnClick
          end
          object ToolButton9: TToolButton
            Left = 344
            Top = 0
            Width = 8
            Caption = 'ToolButton4'
            ImageIndex = 7
            Style = tbsSeparator
          end
          object Sun2Btn: TToolButton
            Left = 352
            Top = 0
            Hint = 'Show solar data for selected night'
            Caption = 'Sun'
            ImageIndex = 5
            ParentShowHint = False
            ShowHint = True
            OnClick = Sun2BtnClick
          end
          object Moon2Btn: TToolButton
            Left = 394
            Top = 0
            Hint = 'Show lunar data for selected night'
            Caption = 'Moon'
            ImageIndex = 6
            ParentShowHint = False
            ShowHint = True
            OnClick = Moon2BtnClick
          end
          object Sky2Btn: TToolButton
            Left = 436
            Top = 0
            Hint = 'Show the location of the selected variable star'
            Caption = 'Chart'
            ImageIndex = 8
            ParentShowHint = False
            ShowHint = True
            OnClick = Sky2BtnClick
          end
          object ToolButton6: TToolButton
            Left = 478
            Top = 0
            Width = 8
            Caption = 'ToolButton6'
            ImageIndex = 10
            Style = tbsSeparator
          end
          object ToolButton8: TToolButton
            Left = 486
            Top = 0
            Caption = 'Setup'
            ImageIndex = 14
            OnClick = ObserverBtnClick
          end
          object ToolButton3: TToolButton
            Left = 528
            Top = 0
            Width = 8
            Caption = 'ToolButton3'
            ImageIndex = 9
            Style = tbsSeparator
          end
          object Help2Btn: TToolButton
            Left = 536
            Top = 0
            Hint = 'Open electronic help'
            Caption = 'Help'
            DropdownMenu = HelpMenu
            ImageIndex = 9
            ParentShowHint = False
            ShowHint = True
          end
        end
      end
      object Panel4: TPanel
        Left = 0
        Top = 0
        Width = 192
        Height = 572
        Align = alLeft
        BevelOuter = bvNone
        TabOrder = 1
        DesignSize = (
          192
          572)
        object Label26: TLabel
          Left = 8
          Top = 273
          Width = 162
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Date (local, before midnight)'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label27: TLabel
          Left = 8
          Top = 8
          Width = 58
          Height = 13
          Caption = 'Catalogue'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label28: TLabel
          Left = 8
          Top = 56
          Width = 74
          Height = 13
          Caption = 'Constellation'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label29: TLabel
          Left = 8
          Top = 104
          Width = 72
          Height = 13
          Caption = 'Variable star'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label32: TLabel
          Left = 162
          Top = 381
          Width = 9
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'hr'
        end
        object Label23: TLabel
          Left = 24
          Top = 501
          Width = 20
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'from'
        end
        object Label24: TLabel
          Left = 99
          Top = 501
          Width = 9
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'to'
        end
        object Label25: TLabel
          Left = 162
          Top = 501
          Width = 18
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'deg'
        end
        object Label18: TLabel
          Left = 24
          Top = 381
          Width = 20
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'from'
        end
        object Label22: TLabel
          Left = 99
          Top = 381
          Width = 9
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'to'
        end
        object Label36: TLabel
          Left = 24
          Top = 549
          Width = 20
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'from'
        end
        object Label37: TLabel
          Left = 99
          Top = 549
          Width = 9
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'to'
        end
        object Label38: TLabel
          Left = 162
          Top = 549
          Width = 18
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'deg'
        end
        object Label40: TLabel
          Left = 8
          Top = 341
          Width = 35
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Filters'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label30: TLabel
          Left = 8
          Top = 293
          Width = 36
          Height = 13
          Alignment = taRightJustify
          Anchors = [akLeft, akBottom]
          AutoSize = False
          Caption = 'from'
        end
        object Label31: TLabel
          Left = 8
          Top = 317
          Width = 36
          Height = 13
          Alignment = taRightJustify
          Anchors = [akLeft, akBottom]
          AutoSize = False
          Caption = 'to'
        end
        object DTStart: TDateTimePicker
          Left = 48
          Top = 289
          Width = 137
          Height = 21
          Hint = 'Po'#269#225'te'#269'n'#237' datum intervalu pro v'#253'po'#269'et minim'
          Anchors = [akLeft, akBottom]
          Date = 37843.740919444400000000
          Time = 37843.740919444400000000
          ParentShowHint = False
          ShowHint = True
          TabOrder = 3
        end
        object DTEnd: TDateTimePicker
          Left = 48
          Top = 313
          Width = 137
          Height = 21
          Hint = 'Koncov'#233' datum intervalu pro v'#253'po'#269'et minim'
          Anchors = [akLeft, akBottom]
          Date = 37843.740919444400000000
          Time = 37843.740919444400000000
          ParentShowHint = False
          ShowHint = True
          TabOrder = 4
        end
        object Cats2: TComboBox
          Left = 8
          Top = 24
          Width = 177
          Height = 21
          Hint = 'Vyberte katalog'
          Style = csDropDownList
          ItemHeight = 13
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          OnChange = Cats2Change
        end
        object Cons2: TComboBox
          Left = 8
          Top = 72
          Width = 177
          Height = 21
          Hint = 'Vyberte souhv'#283'zd'#237
          Style = csDropDownList
          ItemHeight = 13
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          OnChange = Cons2Change
        end
        object Star2: TListBox
          Left = 8
          Top = 120
          Width = 177
          Height = 144
          Hint = 'Vyberte hv'#283'zdu'
          Anchors = [akLeft, akTop, akBottom]
          ItemHeight = 13
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
          OnClick = Star2Click
        end
        object TimeF: TCheckBox
          Left = 8
          Top = 361
          Width = 128
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Time of minimum (UT)'
          Checked = True
          State = cbChecked
          TabOrder = 5
          OnClick = Time1Change
        end
        object VysF: TCheckBox
          Left = 8
          Top = 481
          Width = 128
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Altitude'
          Checked = True
          State = cbChecked
          TabOrder = 19
          OnClick = Vys1Change
        end
        object Time2SB: TSpinButton
          Left = 144
          Top = 377
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Time2
          TabOrder = 9
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = MinDownClick
          OnUpClick = MinUpClick
        end
        object Time2: TEdit
          Left = 112
          Top = 377
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 4
          TabOrder = 8
          Text = '99'
          OnChange = Time1Change
          OnExit = Min2Exit
        end
        object Time1SB: TSpinButton
          Left = 80
          Top = 377
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Time1
          TabOrder = 7
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = MinDownClick
          OnUpClick = MinUpClick
        end
        object Time1: TEdit
          Left = 48
          Top = 377
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 4
          TabOrder = 6
          Text = '0'
          OnChange = Time1Change
          OnExit = Min2Exit
        end
        object Vys1: TEdit
          Left = 48
          Top = 497
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 3
          TabOrder = 20
          Text = '0'
          OnChange = Vys1Change
          OnExit = Alt2Exit
        end
        object Vys1SB: TSpinButton
          Left = 80
          Top = 497
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Vys1
          TabOrder = 21
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = AltDownClick
          OnUpClick = AltUpClick
        end
        object Vys2: TEdit
          Left = 112
          Top = 497
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 3
          TabOrder = 22
          Text = '99'
          OnChange = Vys1Change
          OnExit = Alt2Exit
        end
        object Vys2SB: TSpinButton
          Left = 144
          Top = 497
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Vys2
          TabOrder = 23
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = AltDownClick
          OnUpClick = AltUpClick
        end
        object AziF: TCheckBox
          Left = 8
          Top = 529
          Width = 128
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Azimuth (N->E->S->W)'
          Checked = True
          State = cbChecked
          TabOrder = 24
          OnClick = AziFClick
        end
        object Azi1: TEdit
          Left = 48
          Top = 545
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 3
          TabOrder = 25
          OnChange = AziFClick
          OnExit = AzExit
        end
        object Azi1SB: TSpinButton
          Left = 80
          Top = 545
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Azi1
          TabOrder = 26
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = AzDownClick
          OnUpClick = AzUpClick
        end
        object Azi2: TEdit
          Left = 112
          Top = 545
          Width = 32
          Height = 21
          Anchors = [akLeft, akBottom]
          MaxLength = 3
          TabOrder = 27
          OnChange = AziFClick
          OnExit = AzExit
        end
        object Azi2SB: TSpinButton
          Left = 144
          Top = 545
          Width = 15
          Height = 21
          Anchors = [akLeft, akBottom]
          DownGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200420042
            0042000000420042004200420000004200420042000000000000004200420042
            0000004200420000000000000000000000420042000000420000000000000000
            000000000000004200000042004200420042004200420042004200420000}
          FocusControl = Azi2
          TabOrder = 28
          UpGlyph.Data = {
            BA000000424DBA00000000000000420000002800000009000000060000000100
            1000030000007800000000000000000000000000000000000000007C0000E003
            00001F0000000042004200420042004200420042004200420000004200000000
            0000000000000000000000420000004200420000000000000000000000420042
            0000004200420042000000000000004200420042000000420042004200420000
            004200420042004200000042004200420042004200420042004200420000}
          OnDownClick = AzDownClick
          OnUpClick = AzUpClick
        end
        object FNight2: TCheckBox
          Left = 24
          Top = 403
          Width = 153
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'during nighttime'
          Checked = True
          State = cbChecked
          TabOrder = 10
          OnClick = FNight2Click
        end
        object DOWF: TCheckBox
          Left = 8
          Top = 425
          Width = 128
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Day of week (evening)'
          Checked = True
          State = cbChecked
          TabOrder = 11
          OnClick = DOWFClick
        end
        object Mon: TCheckBox
          Left = 64
          Top = 443
          Width = 41
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Mo'
          TabOrder = 13
        end
        object Tue: TCheckBox
          Left = 104
          Top = 443
          Width = 41
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Tu'
          TabOrder = 14
        end
        object Wed: TCheckBox
          Left = 144
          Top = 443
          Width = 41
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'We'
          TabOrder = 15
        end
        object Thu: TCheckBox
          Left = 24
          Top = 459
          Width = 41
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Th'
          TabOrder = 16
        end
        object Fri: TCheckBox
          Left = 64
          Top = 459
          Width = 41
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Fr'
          TabOrder = 17
        end
        object Sat: TCheckBox
          Left = 104
          Top = 459
          Width = 41
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Sa'
          TabOrder = 18
        end
        object Sun: TCheckBox
          Left = 24
          Top = 443
          Width = 41
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = 'Su'
          TabOrder = 12
        end
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 600
    Width = 904
    Height = 19
    Panels = <
      item
        Width = 50
      end
      item
        Width = 50
      end>
    OnResize = StatusBar1Resize
  end
  object Sort1Menu: TPopupMenu
    OnPopup = Sort1MenuPopup
    Left = 304
    Top = 88
    object Seaditpodlenzvu1: TMenuItem
      Tag = 2
      Caption = 'Sort by variable name'
      Checked = True
      RadioItem = True
      OnClick = PopupClick
    end
    object Sortbyminimumtype1: TMenuItem
      Tag = 3
      Caption = 'Sort by minimum type'
      RadioItem = True
      OnClick = PopupClick
    end
    object Seaditpodleasu1: TMenuItem
      Tag = 4
      Caption = 'Sort by time of minimum'
      RadioItem = True
      OnClick = PopupClick
    end
    object Seaditpodleazimutu1: TMenuItem
      Tag = 6
      Caption = 'Sort by azimuth'
      RadioItem = True
      OnClick = PopupClick
    end
    object Seaditpodlevky1: TMenuItem
      Tag = 7
      Caption = 'Sort by altitude'
      RadioItem = True
      OnClick = PopupClick
    end
    object Seaditpodlerektascenze1: TMenuItem
      Tag = 8
      Caption = 'Sort by right ascension'
      RadioItem = True
      OnClick = PopupClick
    end
    object Seaditpodledeklinace1: TMenuItem
      Tag = 9
      Caption = 'Sort by declination'
      RadioItem = True
      OnClick = PopupClick
    end
    object Seaditpodletypu1: TMenuItem
      Tag = 10
      Caption = 'Sort by type'
      RadioItem = True
      OnClick = PopupClick
    end
    object Seaditpodlejasnosti1: TMenuItem
      Tag = 11
      Caption = 'Sort by brightness'
      RadioItem = True
      OnClick = PopupClick
    end
    object SeaditpodleKatalogu1: TMenuItem
      Tag = 12
      Caption = 'Sort by catalogue name'
      RadioItem = True
      OnClick = PopupClick
    end
    object Seaditpodlebed1: TMenuItem
      Tag = 13
      Caption = 'Sort by attractiveness'
      RadioItem = True
      OnClick = PopupClick
    end
    object SortbyObjMoondistance1: TMenuItem
      Tag = 14
      Caption = 'Sort by Obj-Moon distance'
      RadioItem = True
      OnClick = PopupClick
    end
    object Sortbyremarks1: TMenuItem
      Tag = 15
      Caption = 'Sort by remarks'
      RadioItem = True
      OnClick = PopupClick
    end
  end
  object ImageList: TImageList
    Left = 240
    Top = 88
    Bitmap = {
      494C01010F001300040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000005000000001002000000000000050
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000FFFF007B7B7B00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000FFFF00000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007B7B7B000000
      00007B7B7B007B7B7B0000000000000000000000000000000000000000000000
      000000000000C0C0C00080808000808080008080800080808000C0C0C0000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000FFFF007B7B7B00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000FFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BDBDBD000000
      0000BDBDBD00BDBDBD000000000000000000000000000000000000000000C0C0
      C000008080000080800080000000800000008000000080000000800000008000
      0000C0C0C0000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000FFFF007B7B7B00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000FFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BDBDBD00BDBD
      BD00BDBDBD00BDBDBD0000000000000000000000000000000000C0C0C0000080
      8000008080000080800000808000800000008000000080000000800000008000
      0000800000008080800000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000FFFF007B7B7B00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000FFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C0C000008000000080
      8000008080000080800000808000800000008000000080000000800000008000
      00000080000000800000C0C0C000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007B7B7B007B7B
      7B0000000000000000007B7B7B00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000800000008000000080
      0000008000000080000000808000800000008000000080000000800000000080
      0000008000000080000000800000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      00007B7B7B007B7B7B0000FFFF000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000C0C0C00000800000008000000080
      0000008080008000000080000000800000008000000080000000800000008000
      0000008000000080000000800000C0C0C0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      00007B7B7B0000FFFF0000FFFF000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000008080800000800000008080000080
      0000800000008000000080000000800000008000000080000000008000000080
      0000008080000080800000800000808080000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00000000000000
      0000FFFFFF00000000000000000000000000FFFFFF0000000000000000000000
      00000000FF0000000000000000007B7B7B0000000000FFFFFF00000000000000
      0000FFFFFF000000000000000000BDBDBD0000000000FF000000FF000000FF00
      00000000FF00FF000000FF000000000000008080800000800000008000008000
      0000800000008000000080000000800000008000000080000000008080000080
      8000008080000080000000800000808080000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      FF000000FF000000FF00000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      FF000000FF000000FF0000000000000000008080800080000000800000008000
      0000800000008000000080000000800000008000000080000000008080000080
      8000008080000080800000800000808080000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00000000000000
      00000000000000000000FFFFFF0000000000FFFFFF00000000000000FF000000
      FF000000FF000000FF000000FF000000000000000000FFFFFF00000000000000
      00000000000000000000FFFFFF0000000000FFFFFF00000000000000FF000000
      FF000000FF000000FF000000FF0000000000C0C0C00000800000800000008000
      0000800000008000000080000000800000008000000080000000008080000080
      8000008080000080800000800000808080000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF0000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF00C0C0C00080000000800000008000
      0000800000008000000080000000800000008000000000800000008000008000
      0000800000000080800000800000C0C0C0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00000000000000
      0000FFFFFF000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF00000000000000000000000000FFFFFF00000000000000
      0000FFFFFF000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000808000008000008000
      0000800000008000000080000000800000008000000000800000008000000080
      0000008000000080000000800000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0000000000FFFFFF00FFFFFF000000000000000000000000000000
      FF000000FF000000FF00000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0000000000FFFFFF00FFFFFF000000000000000000000000000000
      FF000000FF000000FF00000000000000000000000000C0C0C000008000000080
      0000800000008000000080000000800000008000000080000000008000000080
      00000080000000800000C0C0C000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF0000000000BDBD
      BD00FFFFFF0000000000FFFFFF000000000000000000000000007B7B7B000000
      FF000000FF000000FF00000000000000000000000000FFFFFF0000000000BDBD
      BD00FFFFFF0000000000FFFFFF000000000000000000000000007B7B7B000000
      FF000000FF000000FF0000000000000000000000000000000000C0C0C0000080
      0000008000000080000080000000800000008000000000800000008000000080
      000000800000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF000000000000000000000000000000FF000000FF000000FF000000
      FF000000FF0000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF000000000000000000000000000000FF000000FF000000FF000000
      FF000000FF00000000000000000000000000000000000000000000000000C0C0
      C000008000000080000000800000008000008000000000800000008000000080
      0000C0C0C0000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C0C0C000C0C0C000808080008080800080808000C0C0C0000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFFFF00FFFFFF000000000000000000000000000000
      FF00000084000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008484840000000000848484000000000000000000000000000000
      000000000000FFFFFF007B7B7B000000FF007B7B7B00FFFFFF00000000000000
      0000000000000000000000000000000000000000000084848400000000000000
      000000000000FFFFFF00FFFFFF00000000000000000000000000000000000000
      FF00000084000000FF0000000000008484000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000840000848484000000000000000000000000000000000000FF
      FF00FFFFFF0000FFFF000000FF000000FF000000FF0000FFFF00FFFFFF0000FF
      FF00000000000000000000000000000000008484840000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      FF00000084000000FF00008484000084840000000000FFFFFF00000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000008484840000000000008400000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000840000000000000000000000000000000000000000000000FFFF00FFFF
      FF0000FFFF00FFFFFF007B7B7B000000FF007B7B7B00FFFFFF0000FFFF00FFFF
      FF0000FFFF0000000000000000000000000000000000FFFFFF00000000000000
      0000FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      FF00000084000000FF00008484000084840000000000FFFFFF00000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000084848400000000000084
      0000008400000000000000000000000000000000000000000000000000000084
      0000000000000000000000000000000000000000000000FFFF00FFFFFF0000FF
      FF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FF
      FF00FFFFFF0000FFFF0000000000000000000000000000000000000000000000
      000000000000FFFFFF0000000000000000000000000000000000000000000000
      FF00000084000000FF00008484000000000000000000FFFFFF00000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000840000000000000000000000000000008400000000
      00000000000000000000000000000000000000000000FFFFFF0000FFFF00FFFF
      FF0000FFFF00FFFFFF0000FFFF000000FF0000FFFF00FFFFFF0000FFFF00FFFF
      FF0000FFFF00FFFFFF0000000000000000000000000084848400000000000000
      000000000000FFFFFF00000000000000000000000000000000000000FF000000
      FF000000FF000000FF000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000008400008484840000840000000000000000
      000000000000000000000000000000000000FFFFFF0000FFFF00FFFFFF0000FF
      FF00FFFFFF0000FFFF00FFFFFF000000FF007B7B7B0000FFFF00FFFFFF0000FF
      FF00FFFFFF0000FFFF00FFFFFF00000000000000000000000000848484000000
      0000FFFFFF000000000084848400000000000000000000000000000084000000
      8400000084000000840000008400000000000000000000000000FFFFFF000000
      00000000000000000000000000000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000848484000000000084848400000000000000
      00000000000000000000000000000000000000FFFF00FFFFFF0000FFFF00FFFF
      FF0000FFFF00FFFFFF0000FFFF000000FF000000FF00FFFFFF0000FFFF00FFFF
      FF0000FFFF00FFFFFF0000FFFF00000000000000000000000000000000000000
      0000000000008484840000000000000000000000000000848400008484000084
      8400000000000000000000000000000000000000000000000000FFFFFF000000
      00000000000000000000FFFFFF000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000008400008484840000840000000000000000
      000000000000000000000000000000000000FFFFFF0000FFFF00FFFFFF0000FF
      FF00FFFFFF0000FFFF00FFFFFF0000FFFF000000FF000000FF00FFFFFF0000FF
      FF00FFFFFF0000FFFF00FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000084840000848400008484000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      00000000000000000000FFFFFF000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000840000000000000000000000000000008400000000
      00000000000000000000000000000000000000FFFF00FFFFFF0000FFFF00FFFF
      FF007B7B7B007B7B7B0000FFFF00FFFFFF007B7B7B000000FF000000FF00FFFF
      FF0000FFFF00FFFFFF0000FFFF00000000000000000000000000000000000000
      0000000000000000000000000000008484000084840000848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000840000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF0000FFFF00FFFFFF0000FF
      FF000000FF000000FF00FFFFFF0000FFFF007B7B7B000000FF000000FF0000FF
      FF00FFFFFF0000FFFF00FFFFFF00000000000000000000000000000000000000
      0000000000000000000000848400008484000084840000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF000000000000000000000000000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000084000000000000000000000000000000000000000000000084
      00000000000000000000000000000000000000000000FFFFFF0000FFFF00FFFF
      FF000000FF000000FF007B7B7B00FFFFFF007B7B7B000000FF000000FF00FFFF
      FF0000FFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000084840000848400008484000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000084
      0000000000000000000000000000000000000000000000FFFF00FFFFFF0000FF
      FF00FFFFFF000000FF000000FF000000FF000000FF000000FF00FFFFFF0000FF
      FF00FFFFFF0000FFFF0000000000000000000000000000000000000000000000
      0000000000000000000000848400000000000000000000000000000000008484
      8400000000008484840000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000840000000000000000000000000000000000000000000000FFFF00FFFF
      FF0000FFFF00FFFFFF000000FF000000FF000000FF00FFFFFF0000FFFF00FFFF
      FF0000FFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008484
      8400000000008484840000000000000000000000000000000000000000000000
      0000FFFFFF000000000000000000000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008484
      84000000000084848400000000000000000000000000000000000000000000FF
      FF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FF
      FF00000000000000000000000000000000000000000000000000008484000000
      0000000000000000000000000000848484000000000000000000000000008484
      8400000000008484840000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000848484000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000008484000084
      8400000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084848400848484008484840084848400848484000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000FF000000FF000000FF000000FF0000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000FFFF000000000000000000000000000000
      0000000000007B7B7B0000000000000000000000000000000000000000000000
      000084848400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00848484008484
      8400848484000000000000000000000000000000000000840000008400000084
      0000008400000084000000840000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000000000000000000000000000000000000000000000FFFF00000000000000
      000000000000000000000000000000FFFF000000000000000000000000000000
      00007B7B7B0000FFFF000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00848484008484840000000000000000000000000000000000008400000084
      0000008400000084000000840000000000000000000000840000008400000084
      000000000000000000000000000000000000000000000000000000000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000000000000000000000000000000000000000000000FFFF000000
      000000000000000000000000000000FFFF000000000000000000000000007B7B
      7B0000FFFF000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008484840084848400000000000000000000000000000000000084
      0000008400000084000000840000000000000000000000840000008400000084
      0000008400000000000000000000000000000000000000000000FF000000FF00
      0000FF000000FF000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF000000FF00
      0000FF000000FF000000000000000000000000000000000000000000000000FF
      FF000000000000000000000000000000000000000000000000000000000000FF
      FF000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0084848400000000000000000000000000008400000084
      0000008400000084000000840000000000000000000000000000000000000084
      00000084000000840000000000000000000000000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FFFFFF00FFFFFF00FF000000FF000000FF00
      0000FF000000FF00000000000000000000000000000000000000000000000000
      0000000000000000000000FFFF0000FFFF0000FFFF0000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      0000FFFFFF00FFFFFF0084848400848484000000000000000000008400000084
      0000000000000084000000840000000000000000000000000000000000000000
      00000084000000840000000000000000000000000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FFFFFF00FFFFFF00FF000000FF000000FF00
      0000FF000000FF000000FF000000000000000000000000000000000000000000
      00000000000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00848484000000000000840000008400000084
      0000000000000000000000840000000000000000000000000000000000000000
      00000084000000840000008400000000000000000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FFFFFF00FFFFFF00FF000000FF000000FF00
      0000FF000000FF000000FF000000000000000000000000000000000000000000
      000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFFFF00000000000000000000840000008400000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000840000008400000000000000000000FF000000FF000000FF00
      0000FF000000FF000000FFFFFF00FFFFFF00FFFFFF00FF000000FF000000FF00
      0000FF000000FF000000FF0000000000000000FFFF0000FFFF0000FFFF000000
      000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF000000
      000000FFFF0000FFFF0000FFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00848484000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000840000008400000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000840000008400000000000000000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000000000000000000000000000000000000000
      000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00848484000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000840000008400000084
      0000000000000000000000000000000000000000000000000000000000000000
      00000084000000840000008400000000000000000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FFFFFF00FFFFFF00FF000000FF000000FF00
      0000FF000000FF00000000000000000000000000000000000000000000000000
      00000000000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00848484000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008400000084
      0000000000000000000000000000000000000000000000000000000000000000
      0000008400000084000000000000000000000000000000000000FF000000FF00
      0000FF000000FF000000FF000000FFFFFF00FFFFFF00FF000000FF000000FF00
      0000FF000000FF00000000000000000000000000000000000000000000007B7B
      7B00000000000000000000FFFF0000FFFF0000FFFF0000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00848484000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008400000084
      0000008400000000000000000000000000000000000000000000000000000084
      000000840000008400000000000000000000000000000000000000000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF00000000000000000000000000000000000000000000007B7B7B0000FF
      FF000000000000000000000000000000000000000000000000000000000000FF
      FF000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00848484008484840000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000084
      0000008400000084000000840000000000000000000000840000008400000084
      0000008400000000000000000000000000000000000000000000000000000000
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      000000000000000000000000000000000000000000007B7B7B0000FFFF000000
      000000000000000000000000000000FFFF000000000000000000000000000000
      000000FFFF000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008400000084000000840000008400000084000000840000008400000084
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000FF000000FF000000FF000000FF0000000000
      0000000000000000000000000000000000000000000000FFFF00000000000000
      000000000000000000000000000000FFFF000000000000000000000000000000
      00000000000000FFFF000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF0084848400848484000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000840000008400000084000000840000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000FFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007B7B7B00000000007B7B
      7B007B7B7B007B7B7B0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000BDBDBD007B7B7B00000000007B7B
      7B00000000000000000000000000000000000000000000000000000000007B7B
      7B00000000007B7B7B00000000000000000000000000BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00000000000000000000000000000000000000
      0000FFFFFF007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FF00
      0000FF000000FFFFFF00FF000000FF00000000000000000000007B7B7B007B7B
      7B00000000000000000000000000000000000000000000000000000000000000
      00007B7B7B0000000000000000000000000000000000BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00000000000000000000000000000000000000
      0000FFFFFF0000000000BDBDBD0000000000BDBDBD00000000007B7B7B000000
      0000000000000000000000000000000000000000000000000000FFFF0000FFFF
      0000FFFF0000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FF00
      0000FF000000FFFFFF00FF000000FF000000BDBDBD00BDBDBD007B7B7B000000
      0000000000007B7B7B0000000000000000000000000000000000000000007B7B
      7B0000000000000000007B7B7B007B7B7B000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF0000000000BDBDBD00000000007B7B7B00000000007B7B7B000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FF000000FF000000FFFFFF007B7B7B0000000000000000000000
      00007B7B7B000000000000000000000000000000000000000000000000000000
      0000000000007B7B7B007B7B7B000000000000000000FFFFFF00BDBDBD00FFFF
      FF00BDBDBD00FFFFFF00BDBDBD00FFFFFF00BDBDBD00FFFFFF00BDBDBD00FFFF
      FF00BDBDBD00FFFFFF00BDBDBD00000000000000000000000000000000000000
      0000FFFFFF0000000000BDBDBD0000000000BDBDBD00000000007B7B7B000000
      000000000000000000000000000000000000FFFF0000FFFF0000FFFF00000000
      000000FFFF00FFFFFF0000FFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FF000000FF000000FFFFFF007B7B7B0000000000000000007B7B
      7B00000000007B7B7B0000000000000000000000000000000000000000000000
      000000000000BDBDBD00000000007B7B7B0000000000BDBDBD00FFFFFF00BDBD
      BD00FFFFFF00BDBDBD00FFFFFF00BDBDBD00FFFFFF00BDBDBD00FFFFFF00BDBD
      BD00FFFFFF000000FF00FFFFFF00000000000000000000000000000000000000
      0000FFFFFF0000000000BDBDBD00000000007B7B7B00000000007B7B7B000000
      00000000000000000000000000000000000000000000FFFF00000000000000FF
      FF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000000000FFFFFF00FFFF
      FF00FF000000FF000000FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000007B7B
      7B007B7B7B00BDBDBD0000000000BDBDBD0000000000FFFFFF00BDBDBD00FFFF
      FF00BDBDBD00FFFFFF00BDBDBD00FFFFFF00BDBDBD00FFFFFF00BDBDBD00FFFF
      FF00BDBDBD00FFFFFF00BDBDBD00000000000000000000000000000000000000
      0000FFFFFF0000000000BDBDBD0000000000BDBDBD00000000007B7B7B000000
      000000000000000000000000000000000000000000000000000000FFFF00FFFF
      FF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000000000FFFF
      FF00FF000000FF000000FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000BDBDBD00000000007B7B7B000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF0000000000BDBDBD00000000007B7B7B00000000007B7B7B000000
      0000000000000000000000000000000000000000000000000000FFFFFF0000FF
      FF00FFFFFF0000FFFF00FFFFFF0000FFFF000000000000FFFF0000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000007B7B7B00000000000000
      00007B7B7B0000000000000000007B7B7B00000000007B7B7B00000000000000
      0000000000007B7B7B00BDBDBD00000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF0000000000BDBDBD0000000000BDBDBD00000000007B7B7B000000
      000000000000000000000000000000000000000000000000000000FFFF000000
      000000FFFF00FFFFFF0000000000FFFFFF0000FFFF0000000000000000000000
      0000000000000000000000000000000000007B7B7B0000000000000000000000
      00007B7B7B000000000000000000000000007B7B7B0000000000000000007B7B
      7B0000000000000000007B7B7B00BDBDBD000000000000000000000000000000
      0000FFFFFF0000000000000000000000000000000000FFFFFF0000000000FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF0000000000BDBDBD00000000007B7B7B00000000007B7B7B000000
      0000000000000000000000000000000000000000000000000000FFFFFF0000FF
      FF000000000000FFFF00FFFFFF0000000000FFFFFF0000FFFF0000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000007B7B7B007B7B
      7B007B7B7B007B7B7B007B7B7B0000000000000000007B7B7B00000000000000
      00007B7B7B000000000000000000000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      00007B7B7B00000000007B7B7B00000000007B7B7B00000000007B7B7B000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000FFFF00FFFFFF0000000000FFFFFF0000000000FFFF
      FF00FFFFFF00FFFFFF000000FF000000FF00000000007B7B7B007B7B7B000000
      000000000000000000007B7B7B007B7B7B000000000000000000000000007B7B
      7B00000000007B7B7B0000000000000000000000000000000000000000000000
      0000FFFFFF000000000000000000FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FF000000FF000000000000000000
      000000000000000000000000000000FFFF00FFFFFF000000000000000000FFFF
      FF00FFFFFF00FFFFFF000000FF000000FF0000000000BDBDBD00000000007B7B
      7B007B7B7B007B7B7B00000000007B7B7B000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00BDBDBD00BDBDBD00BDBDBD007B7B7B007B7B7B007B7B7B007B7B7B007B7B
      7B0000000000000000000000000000000000FF000000FF0000000000FF000000
      FF000000000000000000000000000000000000000000000000000000FF00FFFF
      FF000000FF000000FF00FFFFFF00FFFFFF007B7B7B00BDBDBD0000000000BDBD
      BD00000000007B7B7B00000000007B7B7B007B7B7B007B7B7B00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF0000000000BDBDBD00FFFFFF0000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000FF000000
      FF0000000000000000000000000000000000FFFFFF000000FF000000FF00FFFF
      FF000000FF000000FF00FFFFFF00FFFFFF0000000000BDBDBD00000000007B7B
      7B00BDBDBD007B7B7B00000000007B7B7B000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007B7B7B007B7B7B007B7B7B0000000000000000000000
      0000000000000000000000000000000000000000FF000000FF0000000000FF00
      0000FF000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF000000
      FF000000FF00FFFFFF000000FF000000FF00000000007B7B7B00BDBDBD000000
      000000000000000000007B7B7B007B7B7B000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF0000000000FF00
      0000FF000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF000000
      FF000000FF00FFFFFF000000FF000000FF00424D3E000000000000003E000000
      2800000040000000500000000100010000000000800200000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FC00FF00F81F0000FC00FF00E0070000
      FC00FF00C0030000FC00FF008001000000000000800100000000000000000000
      0000000000000000000000000000000000230023000000000001000100000000
      00000000000000000023002380010000006300638001000000C300C3C0030000
      01070107E007000003FF03FFF81F0000FFFDFFFFF862FFFFFFF8F83F80E007C1
      BFF9E00F01E007C11FF7C00701E007C1A3EF800331E107C1FDDF800331C10101
      FE3F0001C1810001FE3F0001C3070001FE3F0001FE170001FDDF0001CC378003
      FDEF00018877C107F3EF800300F7C107E3EF800301E3E38FF7F7C007C1E3E38F
      FFE3E00FC0E3E38FFFF7F83FC83FFFFFFFFFFF7FFC1FFFFFF81FDE79F00781FF
      F00FAE73E003C18FE007D6E7C001E187C003EE2F8001C1E38003FC1F81F0C9F3
      8001F80F03F88DF18001800807FD9FF98001100107FF9FF98001F01F07FF8FF1
      8003F83F07FFCFF3C003E47787FFC7E3E007CF6B83FFE187F00F9E75C1FFF00F
      F81FBE7BE0FFFC3FFFFFFEFFF9FFFFFF81FE8001E00FFFFF01E20000E00FC600
      07E00000E00F820003E00000E00F000003F00000E00F000023C00000E00F0000
      3FC00000E00F8000E3C00000A00B80002230E007C00780000020E007E00F8000
      0020E007E00FC8000062E007C0073C00001EE00FC0070E00001FE01FC007CE00
      001FE03FF83F2600007FE07FF83F260000000000000000000000000000000000
      000000000000}
  end
  object Sort2Menu: TPopupMenu
    OnPopup = Sort2MenuPopup
    Left = 304
    Top = 136
    object MenuItem1: TMenuItem
      Caption = 'Sort by date'
      Checked = True
      RadioItem = True
      OnClick = MenuItem4Click
    end
    object MenuItem2: TMenuItem
      Tag = 1
      Caption = 'Sort by time of minimum'
      RadioItem = True
      OnClick = MenuItem4Click
    end
    object MenuItem5: TMenuItem
      Tag = 2
      Caption = 'Sort by day of week'
      RadioItem = True
      OnClick = MenuItem4Click
    end
    object MenuItem3: TMenuItem
      Tag = 6
      Caption = 'Sort by azimuth'
      RadioItem = True
      OnClick = MenuItem4Click
    end
    object MenuItem4: TMenuItem
      Tag = 7
      Caption = 'Sort by altitude'
      RadioItem = True
      OnClick = MenuItem4Click
    end
    object Sortbylunarillumination1: TMenuItem
      Tag = 8
      Caption = 'Sort by lunar illumination'
      RadioItem = True
      OnClick = MenuItem4Click
    end
    object Sortbylunardistance1: TMenuItem
      Tag = 9
      Caption = 'Sort by Obj-Moon distance'
      RadioItem = True
      OnClick = MenuItem4Click
    end
  end
  object FindDialog: TFindDialog
    Left = 240
    Top = 184
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'txt'
    Filter = 'Text file|*.txt|CSV file|*.csv|HTML file|*.html;*.htm'
    Title = 'Save table of minima to file...'
    Left = 240
    Top = 136
  end
  object HelpMenu: TPopupMenu
    Left = 304
    Top = 184
    object MHelpEn: TMenuItem
      Caption = 'English electronic help'
      OnClick = HelpBtnClick
    end
    object MHelpCs: TMenuItem
      Tag = 2
      Caption = 'Czech electronic help'
      OnClick = HelpBtnClick
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object MAbout: TMenuItem
      Caption = 'About...'
      OnClick = MAboutClick
    end
  end
  object ListMenu: TPopupMenu
    OnPopup = ListMenuPopup
    Left = 304
    Top = 232
    object Resize: TMenuItem
      Caption = 'Adjust column widths'
      OnClick = ResizeClick
    end
  end
  object CatalogMenu: TPopupMenu
    OnPopup = CatalogMenuPopup
    Left = 308
    Top = 280
    object CatalogMenuSelectAll: TMenuItem
      Caption = 'Select all'
      OnClick = CatalogMenuSelectAllClick
    end
    object CatalogMenuClear: TMenuItem
      Caption = 'Clear selection'
      OnClick = CatalogMenuClearClick
    end
  end
end
