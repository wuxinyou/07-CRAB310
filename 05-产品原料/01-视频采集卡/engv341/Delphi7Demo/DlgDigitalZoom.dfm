object DlgZoom: TDlgZoom
  Left = 574
  Top = 274
  BorderStyle = bsDialog
  Caption = 'Dialog'
  ClientHeight = 255
  ClientWidth = 228
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object OKBtn: TButton
    Left = 31
    Top = 228
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
    OnClick = OKBtnClick
  end
  object CancelBtn: TButton
    Left = 135
    Top = 228
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
    OnClick = CancelBtnClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 209
    Height = 153
    Caption = 'Zoom rect setting'
    TabOrder = 2
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'ZoomTop'
    end
    object Label2: TLabel
      Left = 8
      Top = 55
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'ZoomLeft'
    end
    object Label3: TLabel
      Left = 8
      Top = 88
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'ZoomRight'
    end
    object Label4: TLabel
      Left = 8
      Top = 124
      Width = 65
      Height = 17
      AutoSize = False
      Caption = 'ZoomBottom'
    end
    object etZoomTop: TEdit
      Left = 72
      Top = 24
      Width = 89
      Height = 21
      TabOrder = 0
      Text = '20'
    end
    object etZoomLeft: TEdit
      Left = 72
      Top = 56
      Width = 81
      Height = 21
      TabOrder = 1
      Text = '20'
    end
    object etZoomRight: TEdit
      Left = 72
      Top = 88
      Width = 81
      Height = 21
      TabOrder = 2
      Text = '300'
    end
    object etZoomBot: TEdit
      Left = 72
      Top = 120
      Width = 81
      Height = 21
      TabOrder = 3
      Text = '300'
    end
  end
  object chkEnableZoom: TCheckBox
    Left = 8
    Top = 176
    Width = 209
    Height = 25
    Caption = 'EnableZoom'
    TabOrder = 3
  end
end
