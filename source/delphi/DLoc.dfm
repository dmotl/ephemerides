object LocTable: TLocTable
  Left = 273
  Top = 256
  Anchors = [akLeft, akTop, akRight, akBottom]
  BorderStyle = bsDialog
  Caption = 'Predefined locations'
  ClientHeight = 297
  ClientWidth = 464
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object SaveBtn: TButton
    Left = 152
    Top = 264
    Width = 89
    Height = 25
    Hint = 'Save changes and close the dialog'
    Caption = 'Save'
    Default = True
    ModalResult = 1
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
  end
  object CancelBtn: TButton
    Left = 248
    Top = 264
    Width = 89
    Height = 25
    Hint = 'Discard changes and close the dialog'
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 464
    Height = 257
    Align = alTop
    BevelOuter = bvNone
    Caption = 'Panel1'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 160
      Width = 41
      Height = 13
      Caption = 'Location'
    end
    object Label2: TLabel
      Left = 176
      Top = 160
      Width = 47
      Height = 13
      Caption = 'Longitude'
    end
    object Label3: TLabel
      Left = 272
      Top = 160
      Width = 38
      Height = 13
      Caption = 'Latitude'
    end
    object Bevel1: TBevel
      Left = 8
      Top = 247
      Width = 449
      Height = 2
    end
    object Label4: TLabel
      Left = 368
      Top = 160
      Width = 49
      Height = 13
      Caption = 'Time zone'
    end
    object List: TListView
      Left = 8
      Top = 8
      Width = 449
      Height = 145
      Columns = <
        item
          Caption = 'Location'
          Width = 148
        end
        item
          Caption = 'Longitude'
          Width = 88
        end
        item
          Caption = 'Latitude'
          Width = 88
        end
        item
          Caption = 'Time zone'
          Width = 88
        end>
      GridLines = True
      HideSelection = False
      OwnerData = True
      ReadOnly = True
      RowSelect = True
      SortType = stText
      TabOrder = 0
      ViewStyle = vsReport
      OnData = ListData
      OnSelectItem = ListSelectItem
    end
    object NameEdit: TEdit
      Left = 8
      Top = 176
      Width = 161
      Height = 21
      Hint = 'Enter name of a location'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
    end
    object LonEdit: TEdit
      Left = 176
      Top = 176
      Width = 89
      Height = 21
      Hint = 
        'Enter longitude of a location (dd.dddd, East positive, West nega' +
        'tive)'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
    end
    object LatEdit: TEdit
      Left = 272
      Top = 176
      Width = 89
      Height = 21
      Hint = 
        'Enter latitude of a location (dd.dddd, North positive, South neg' +
        'ative)'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
    end
    object AddBtn: TButton
      Left = 80
      Top = 208
      Width = 73
      Height = 25
      Hint = 'Insert new item to the table'
      Caption = 'Add'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
      OnClick = AddBtnClick
    end
    object ReplaceBtn: TButton
      Left = 160
      Top = 208
      Width = 73
      Height = 25
      Hint = 'Replace selected item'
      Cancel = True
      Caption = 'Replace'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
      OnClick = ReplaceBtnClick
    end
    object DeleteBtn: TButton
      Left = 240
      Top = 208
      Width = 73
      Height = 25
      Hint = 'Delete selected item'
      Cancel = True
      Caption = 'Delete'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 6
      OnClick = DeleteBtnClick
    end
    object ClearBtn: TButton
      Left = 320
      Top = 208
      Width = 73
      Height = 25
      Hint = 'Clear content of the table'
      Cancel = True
      Caption = 'Clear'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 7
      OnClick = ClearBtnClick
    end
  end
  object TZEdit: TComboBox
    Left = 368
    Top = 176
    Width = 89
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 3
    Text = 'From system'
    Items.Strings = (
      'From system'
      'UTC-12:00'
      'UTC-11:00'
      'UTC-10:00'
      'UTC-09:30'
      'UTC-09:00'
      'UTC-08:00'
      'UTC-07:00'
      'UTC-06:00'
      'UTC-05:00'
      'UTC-04:30'
      'UTC-04:00'
      'UTC-03:30'
      'UTC-03:00'
      'UTC-02:00'
      'UTC-01:00'
      'UTC'
      'UTC+01:00'
      'UTC+02:00'
      'UTC+03:00'
      'UTC+03:30'
      'UTC+04:00'
      'UTC+04:30'
      'UTC+05:00'
      'UTC+05:30'
      'UTC+05:45'
      'UTC+06:00'
      'UTC+06:30'
      'UTC+07:00'
      'UTC+08:00'
      'UTC+08:45'
      'UTC+09:00'
      'UTC+09:30'
      'UTC+10:00'
      'UTC+10:30'
      'UTC+11:00'
      'UTC+11:30'
      'UTC+12:00'
      'UTC+12:45'
      'UTC+13:00'
      'UTC+14:00')
  end
end
