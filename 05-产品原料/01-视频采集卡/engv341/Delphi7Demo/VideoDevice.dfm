object VideoDeviceFrm: TVideoDeviceFrm
  Left = 140
  Top = 218
  Width = 380
  Height = 98
  Caption = 'DeviceInfo'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 24
    Width = 97
    Height = 25
    AutoSize = False
    Caption = 'VideoDevice:'
  end
  object ComboBox1: TComboBox
    Left = 112
    Top = 24
    Width = 217
    Height = 21
    ItemHeight = 13
    TabOrder = 0
    OnChange = ComboBox1Change
  end
end
