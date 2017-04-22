object ColorProperty: TColorProperty
  Left = 264
  Top = 302
  BorderStyle = bsDialog
  Caption = 'ColorSetting'
  ClientHeight = 285
  ClientWidth = 397
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object OKBtn: TButton
    Left = 39
    Top = 252
    Width = 81
    Height = 29
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
    OnClick = OKBtnClick
  end
  object CancelBtn: TButton
    Left = 271
    Top = 252
    Width = 81
    Height = 29
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
    OnClick = CancelBtnClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 377
    Height = 233
    Caption = 'ColorPropertySetting'
    TabOrder = 2
    object Label1: TLabel
      Left = 8
      Top = 32
      Width = 49
      Height = 13
      Caption = 'Brightness'
    end
    object Label2: TLabel
      Left = 8
      Top = 64
      Width = 40
      Height = 13
      Caption = 'Contract'
    end
    object Label3: TLabel
      Left = 8
      Top = 96
      Width = 20
      Height = 13
      Caption = 'Hue'
    end
    object Label4: TLabel
      Left = 8
      Top = 128
      Width = 48
      Height = 13
      Caption = 'Saturation'
    end
    object Label5: TLabel
      Left = 8
      Top = 160
      Width = 62
      Height = 13
      Caption = 'Sharpness'#65306
    end
    object BrightVal: TLabel
      Left = 336
      Top = 32
      Width = 18
      Height = 13
      Caption = '128'
    end
    object ContrastVal: TLabel
      Left = 336
      Top = 64
      Width = 12
      Height = 13
      Caption = '68'
    end
    object HueVal: TLabel
      Left = 336
      Top = 96
      Width = 6
      Height = 13
      Caption = '0'
    end
    object SaturationVal: TLabel
      Left = 336
      Top = 128
      Width = 12
      Height = 13
      Caption = '64'
    end
    object SharpVal: TLabel
      Left = 336
      Top = 160
      Width = 6
      Height = 13
      Caption = '5'
    end
    object ScrollBarBright: TScrollBar
      Left = 72
      Top = 32
      Width = 257
      Height = 17
      Max = 255
      PageSize = 0
      Position = 128
      TabOrder = 0
      OnChange = ScrollBarBrightChange
    end
    object ScrollBarContrast: TScrollBar
      Left = 72
      Top = 64
      Width = 257
      Height = 17
      PageSize = 0
      Position = 68
      TabOrder = 1
      OnChange = ScrollBarContrastChange
    end
    object ScrollBarHue: TScrollBar
      Left = 72
      Top = 96
      Width = 257
      Height = 17
      PageSize = 0
      TabOrder = 2
      OnChange = ScrollBarHueChange
    end
    object ScrollBarSaturation: TScrollBar
      Left = 72
      Top = 128
      Width = 257
      Height = 17
      PageSize = 0
      Position = 64
      TabOrder = 3
      OnChange = ScrollBarSaturationChange
    end
    object ScrollBarSharp: TScrollBar
      Left = 72
      Top = 160
      Width = 257
      Height = 17
      PageSize = 0
      Position = 5
      TabOrder = 4
      OnChange = ScrollBarSharpChange
    end
  end
  object DefColor: TButton
    Left = 152
    Top = 204
    Width = 81
    Height = 29
    Caption = 'Default'
    TabOrder = 3
    OnClick = DefColorClick
  end
end
