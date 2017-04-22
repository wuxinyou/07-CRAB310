object Form1: TForm1
  Left = 56
  Top = 94
  BorderStyle = bsSingle
  Caption = 'MainForm'
  ClientHeight = 559
  ClientWidth = 853
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Button3: TButton
    Left = 736
    Top = 68
    Width = 105
    Height = 25
    Caption = 'GetCurBuf'
    TabOrder = 0
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 768
    Top = 224
    Width = 1
    Height = 65
    Caption = 'Button4'
    TabOrder = 1
  end
  object Button5: TButton
    Left = 744
    Top = 520
    Width = 97
    Height = 25
    Caption = 'Exit'
    TabOrder = 2
    OnClick = Button5Click
  end
  object btEnumVideoCodec: TButton
    Left = 737
    Top = 244
    Width = 105
    Height = 25
    Caption = 'CodecSetting'
    TabOrder = 3
    OnClick = btEnumVideoCodecClick
  end
  object btSnap: TButton
    Left = 736
    Top = 103
    Width = 105
    Height = 25
    Caption = 'Snap'
    TabOrder = 4
    OnClick = btSnapClick
  end
  object btCapture: TButton
    Left = 736
    Top = 275
    Width = 105
    Height = 25
    Caption = 'Record'
    TabOrder = 5
    OnClick = btCaptureClick
  end
  object btFreezeCap: TButton
    Left = 736
    Top = 309
    Width = 105
    Height = 25
    Caption = 'Pause Rec'
    TabOrder = 6
    OnClick = btFreezeCapClick
  end
  object btSetOSD: TButton
    Left = 737
    Top = 208
    Width = 105
    Height = 25
    Caption = 'OsdSetting'
    TabOrder = 7
    OnClick = btSetOSDClick
  end
  object btEnableRawCall: TButton
    Left = 736
    Top = 137
    Width = 105
    Height = 25
    Caption = 'StartCallBack'
    TabOrder = 8
    OnClick = btEnableRawCallClick
  end
  object btCallBackSnap: TButton
    Left = 736
    Top = 172
    Width = 105
    Height = 25
    Caption = 'CallBackSnap'
    TabOrder = 9
    OnClick = btCallBackSnapClick
  end
  object CheckBox1: TCheckBox
    Left = 736
    Top = 376
    Width = 113
    Height = 25
    Caption = 'Enable time Snap'
    TabOrder = 10
    OnClick = CheckBox1Click
  end
  object GroupBox1: TGroupBox
    Left = 728
    Top = 0
    Width = 97
    Height = 65
    Caption = 'Cur Channel No'
    TabOrder = 11
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 60
      Height = 13
      AutoSize = False
      Caption = 'Cur No:'
    end
  end
  object GroupBox2: TGroupBox
    Left = 736
    Top = 408
    Width = 113
    Height = 105
    Caption = 'Preview Mode'
    TabOrder = 12
    object VMR7Mode: TRadioButton
      Left = 16
      Top = 16
      Width = 81
      Height = 25
      Caption = 'VMR7 Mode'
      TabOrder = 0
      OnClick = VMR7ModeClick
    end
    object OffScreamMode: TRadioButton
      Left = 16
      Top = 40
      Width = 81
      Height = 25
      Caption = 'OffScream'
      TabOrder = 1
      OnClick = OffScreamModeClick
    end
  end
  object VMR9Mode: TRadioButton
    Left = 752
    Top = 472
    Width = 81
    Height = 25
    Caption = 'VMR9 Mode'
    TabOrder = 13
    OnClick = VMR9ModeClick
  end
  object btZoom: TButton
    Left = 736
    Top = 344
    Width = 105
    Height = 25
    Caption = 'DigitalZoom'
    TabOrder = 14
    OnClick = btZoomClick
  end
  object MainMenu1: TMainMenu
    Left = 570
    Top = 15
    object N2: TMenuItem
      Caption = 'VideoSize'
      object Menu768: TMenuItem
        Caption = '768*576'
        OnClick = Menu768Click
      end
      object D1Menu: TMenuItem
        Caption = 'D1'
        OnClick = D1MenuClick
      end
      object CIFMenu: TMenuItem
        Caption = 'CIF'
        OnClick = CIFMenuClick
      end
    end
    object VideoStandMenu: TMenuItem
      Caption = 'VideoStandard'
      object PalMenu: TMenuItem
        Caption = 'PAL'
        OnClick = PalMenuClick
      end
      object NtscMenu: TMenuItem
        Caption = 'NTSC'
        OnClick = NtscMenuClick
      end
    end
    object VideoSourceMenu: TMenuItem
      Caption = 'VideoSource'
      object AV1Menu: TMenuItem
        Caption = 'AV1'
        OnClick = AV1MenuClick
      end
      object av2Menu: TMenuItem
        Caption = 'AV2'
        OnClick = av2MenuClick
      end
      object SVIDEOMenu: TMenuItem
        Caption = 'SVIDEO'
        OnClick = SVIDEOMenuClick
      end
    end
    object DeinterlaceMenu: TMenuItem
      Caption = 'Deinterlace'
      object DeinterLow: TMenuItem
        Caption = 'Default'
        OnClick = DeinterLowClick
      end
      object DeinterBlend: TMenuItem
        Caption = 'Standard'
        OnClick = DeinterBlendClick
      end
      object DeinterBob: TMenuItem
        Caption = 'Good'
        OnClick = DeinterBobClick
      end
      object DeinterCancel: TMenuItem
        Caption = 'Cancel'
        OnClick = DeinterCancelClick
      end
    end
    object Imageenhancement1: TMenuItem
      Caption = 'VideoAlgorithm'
      OnClick = Imageenhancement1Click
    end
    object VideoEffect: TMenuItem
      Caption = 'VideoEffects'
      object VideoFlipMenu: TMenuItem
        Caption = 'FilpVideo'
        OnClick = VideoFlipMenuClick
      end
      object VideoMirrMenu: TMenuItem
        Caption = 'MirroVideo'
        OnClick = VideoMirrMenuClick
      end
    end
    object N1: TMenuItem
      Caption = 'ColorPropertySet'
      OnClick = N1Click
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 568
    Top = 432
  end
end
