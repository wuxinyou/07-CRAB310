object ImagealgorithmFrm: TImagealgorithmFrm
  Left = 746
  Top = 201
  BorderStyle = bsDialog
  Caption = 'Image algorithm setting'
  ClientHeight = 271
  ClientWidth = 413
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 144
    Width = 73
    Height = 17
    AutoSize = False
    Caption = 'Brightness'
  end
  object Label2: TLabel
    Left = 8
    Top = 200
    Width = 89
    Height = 17
    AutoSize = False
    Caption = 'Contract'
  end
  object lblBrightValue: TLabel
    Left = 392
    Top = 144
    Width = 33
    Height = 13
    AutoSize = False
    Caption = '0'
  end
  object lblContrastValue: TLabel
    Left = 392
    Top = 200
    Width = 33
    Height = 13
    AutoSize = False
    Caption = '30'
  end
  object Label3: TLabel
    Left = 8
    Top = 32
    Width = 73
    Height = 17
    AutoSize = False
    Caption = 'Denoise'#65306
  end
  object Label4: TLabel
    Left = 8
    Top = 80
    Width = 97
    Height = 17
    AutoSize = False
    Caption = 'Sharpness'#65306
  end
  object lblSharpValue: TLabel
    Left = 392
    Top = 80
    Width = 33
    Height = 13
    AutoSize = False
    Caption = '0'
  end
  object lblDenoiseValue: TLabel
    Left = 392
    Top = 32
    Width = 33
    Height = 13
    AutoSize = False
    Caption = '0'
  end
  object scrlbrBright: TScrollBar
    Left = 104
    Top = 136
    Width = 273
    Height = 25
    PageSize = 0
    TabOrder = 0
    OnChange = scrlbrBrightChange
  end
  object scrlbrContrast: TScrollBar
    Left = 104
    Top = 192
    Width = 273
    Height = 25
    PageSize = 0
    TabOrder = 1
    OnChange = scrlbrContrastChange
  end
  object btnExit: TButton
    Left = 152
    Top = 240
    Width = 81
    Height = 25
    Caption = 'Exit'
    TabOrder = 2
    OnClick = btnExitClick
  end
  object scrlbrDenoise: TScrollBar
    Left = 104
    Top = 24
    Width = 265
    Height = 25
    PageSize = 0
    TabOrder = 3
    OnChange = scrlbrDenoiseChange
  end
  object scrlbrSharpness: TScrollBar
    Left = 104
    Top = 80
    Width = 265
    Height = 25
    PageSize = 0
    TabOrder = 4
    OnChange = scrlbrSharpnessChange
  end
end
