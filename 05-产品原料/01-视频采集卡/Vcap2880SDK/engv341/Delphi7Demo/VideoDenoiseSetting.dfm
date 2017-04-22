object VideoDenoiseSet: TVideoDenoiseSet
  Left = 171
  Top = 326
  Width = 422
  Height = 245
  Caption = 'VideoDenoise'
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
    Top = 24
    Width = 73
    Height = 25
    AutoSize = False
    Caption = #35270#39057#38477#22122#65306
  end
  object DenoiseValue: TLabel
    Left = 344
    Top = 24
    Width = 57
    Height = 25
    AutoSize = False
    Caption = '100'
  end
  object Label2: TLabel
    Left = 8
    Top = 64
    Width = 73
    Height = 25
    AutoSize = False
    Caption = #35270#39057#38160#21270#65306
  end
  object SharpValue: TLabel
    Left = 349
    Top = 64
    Width = 57
    Height = 25
    AutoSize = False
    Caption = '100'
  end
  object BrightValue: TLabel
    Left = 349
    Top = 104
    Width = 57
    Height = 25
    AutoSize = False
    Caption = '100'
  end
  object ContrastValue: TLabel
    Left = 349
    Top = 144
    Width = 57
    Height = 25
    AutoSize = False
    Caption = '100'
  end
  object Label6: TLabel
    Left = 8
    Top = 104
    Width = 73
    Height = 25
    AutoSize = False
    Caption = #20142#24230#22686#24378#65306
  end
  object Label7: TLabel
    Left = 0
    Top = 136
    Width = 89
    Height = 25
    AutoSize = False
    Caption = #23545#27604#24230#22686#24378#65306
  end
  object ScrollBar1: TScrollBar
    Left = 80
    Top = 24
    Width = 249
    Height = 17
    PageSize = 0
    Position = 70
    TabOrder = 0
    OnChange = ScrollBarContrastChange
  end
  object ScrollBarSharp: TScrollBar
    Left = 80
    Top = 56
    Width = 249
    Height = 17
    PageSize = 0
    TabOrder = 1
  end
  object ScrollBarBright: TScrollBar
    Left = 80
    Top = 96
    Width = 249
    Height = 17
    PageSize = 0
    TabOrder = 2
  end
  object ScrollBarContrast: TScrollBar
    Left = 80
    Top = 136
    Width = 249
    Height = 17
    PageSize = 0
    TabOrder = 3
    OnChange = ScrollBarContrastChange
  end
end
