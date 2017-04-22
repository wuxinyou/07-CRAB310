object OKBottomDlg: TOKBottomDlg
  Left = 476
  Top = 291
  BorderStyle = bsDialog
  Caption = 'DevicePropertyDialog'
  ClientHeight = 301
  ClientWidth = 405
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object OKBtn: TButton
    Left = 87
    Top = 268
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object CancelBtn: TButton
    Left = 199
    Top = 268
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object DlgPrvHwnd: TPanel
    Left = 8
    Top = 8
    Width = 393
    Height = 233
    TabOrder = 2
  end
end
