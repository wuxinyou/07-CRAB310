program DelphiDemo;

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  EnumCodecSet in 'EnumCodecSet.pas' {EnumCodecFrm},
  GlobalVar in 'GlobalVar.pas',
  DeviceProperty in 'DeviceProperty.pas' {OKBottomDlg},
  ColorSetting in 'ColorSetting.pas' {ColorProperty},
  DxMediaFunction in 'DxMediaFunction.pas',
  OSDSetting in 'OSDSetting.pas' {OsdSettingDlg},
  DxMediaApi in 'DxMediaApi.pas',
  DlgPicPrview in 'DlgPicPrview.pas' {DlgPrvHwnd},
  VideoDevice in 'VideoDevice.pas' {VideoDeviceFrm},
  VideoDenoiseSetting in 'VideoDenoiseSetting.pas' {VideoDenoiseSet},
  ImagealgorithmSetting in 'ImagealgorithmSetting.pas' {ImagealgorithmFrm},
  DlgDigitalZoom in 'DlgDigitalZoom.pas' {DlgZoom};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(TEnumCodecFrm, EnumCodecFrm);
  Application.CreateForm(TOsdSettingDlg, OsdSettingDlg);
  Application.CreateForm(TOKBottomDlg, OKBottomDlg);
  Application.CreateForm(TDlgPrvHwnd, DlgPrvHwnd);
  Application.CreateForm(TColorProperty, ColorProperty);
  Application.CreateForm(TOsdSettingDlg, OsdSettingDlg);
  Application.CreateForm(TDlgPrvHwnd, DlgPrvHwnd);
  Application.CreateForm(TVideoDeviceFrm, VideoDeviceFrm);
  Application.CreateForm(TVideoDenoiseSet, VideoDenoiseSet);
  Application.CreateForm(TImagealgorithmFrm, ImagealgorithmFrm);
  Application.CreateForm(TDlgZoom, DlgZoom);
  Application.Run;
end.
