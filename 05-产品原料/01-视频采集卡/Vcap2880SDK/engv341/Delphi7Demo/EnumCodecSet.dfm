object EnumCodecFrm: TEnumCodecFrm
  Left = 735
  Top = 118
  Width = 433
  Height = 402
  Caption = 'EnumCodecSet'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 168
    Top = 324
    Width = 71
    Height = 28
    Caption = 'OK'
    TabOrder = 0
    OnClick = Button1Click
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 16
    Width = 393
    Height = 97
    Caption = 'Enum the system codec'
    TabOrder = 1
    object Label3: TLabel
      Left = 5
      Top = 36
      Width = 61
      Height = 13
      Caption = 'Video Codec'
    end
    object Label2: TLabel
      Left = 5
      Top = 60
      Width = 84
      Height = 21
      AutoSize = False
      Caption = 'Audio Codec'
    end
    object cbbVideoCodec: TComboBox
      Left = 108
      Top = 28
      Width = 269
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      OnChange = cbbVideoCodecChange
    end
    object cbbAudioCodec: TComboBox
      Left = 110
      Top = 61
      Width = 267
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      OnChange = cbbAudioCodecChange
    end
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 120
    Width = 393
    Height = 97
    Caption = 'Save Path setting'
    TabOrder = 2
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 121
      Height = 13
      AutoSize = False
      Caption = 'Video Save Path'#65306
    end
    object Label4: TLabel
      Left = 8
      Top = 48
      Width = 113
      Height = 13
      AutoSize = False
      Caption = 'Picture Save Path'#65306
    end
    object TxtRecPath: TEdit
      Left = 128
      Top = 24
      Width = 193
      Height = 21
      TabOrder = 0
      Text = 'D:\Video'
    end
    object btnRecPath: TButton
      Left = 328
      Top = 24
      Width = 49
      Height = 25
      Caption = 'Brower'
      TabOrder = 1
      OnClick = btnRecPathClick
    end
    object TxtPicPath: TEdit
      Left = 128
      Top = 56
      Width = 193
      Height = 21
      TabOrder = 2
      Text = 'D:\Pic'
    end
    object btPicPath: TButton
      Left = 328
      Top = 56
      Width = 49
      Height = 25
      Caption = 'Brower'
      TabOrder = 3
      OnClick = btPicPathClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 16
    Top = 224
    Width = 393
    Height = 81
    Caption = 'Video Codec Setting'
    TabOrder = 3
    object rbXvid: TRadioButton
      Left = 16
      Top = 32
      Width = 73
      Height = 25
      Caption = 'Xvid Codec'
      TabOrder = 0
      OnClick = rbXvidClick
    end
    object rbDivx: TRadioButton
      Left = 136
      Top = 32
      Width = 89
      Height = 25
      Caption = 'Divx Codec'
      TabOrder = 1
      OnClick = rbDivxClick
    end
    object rbX264: TRadioButton
      Left = 272
      Top = 32
      Width = 97
      Height = 33
      Caption = 'H264 Codec'
      TabOrder = 2
      OnClick = rbX264Click
    end
  end
end
