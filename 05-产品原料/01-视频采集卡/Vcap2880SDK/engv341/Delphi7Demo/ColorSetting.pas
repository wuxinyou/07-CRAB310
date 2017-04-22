unit ColorSetting;

interface

uses Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls,
  Buttons, ExtCtrls,IniFiles;

type
  TColorProperty = class(TForm)
    OKBtn: TButton;
    CancelBtn: TButton;
    GroupBox1: TGroupBox;
    ScrollBarBright: TScrollBar;
    ScrollBarContrast: TScrollBar;
    ScrollBarHue: TScrollBar;
    ScrollBarSaturation: TScrollBar;
    ScrollBarSharp: TScrollBar;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    BrightVal: TLabel;
    ContrastVal: TLabel;
    HueVal: TLabel;
    SaturationVal: TLabel;
    SharpVal: TLabel;
    DefColor: TButton;
    procedure ScrollBarBrightChange(Sender: TObject);
    procedure ScrollBarContrastChange(Sender: TObject);
    procedure ScrollBarHueChange(Sender: TObject);
    procedure ScrollBarSaturationChange(Sender: TObject);
    procedure ScrollBarSharpChange(Sender: TObject);
    procedure OKBtnClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure DefColorClick(Sender: TObject);
    procedure CancelBtnClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  ColorProperty: TColorProperty;
  iFlags:Integer   ;

implementation
 uses GlobalVar,DxMediaFunction,DxMediaApi;
{$R *.dfm}

procedure TColorProperty.ScrollBarBrightChange(Sender: TObject);
begin
     BrightValue:= ScrollBarBright.Position;
     BrightVal.Caption :=IntToStr(BrightValue);
     DXSetDisplayPara(DeviceInfo[CardNo].dwChannelHandle,0, BrightValue,iFlags);

     SettingIni.WriteInteger('Colorpropterty','BrightnessValue'+inttostr(CardNo),BrightValue);
end;

procedure TColorProperty.ScrollBarContrastChange(Sender: TObject);
begin
    ContrastValue:= ScrollBarContrast.Position;
     ContrastVal.Caption :=IntToStr(ContrastValue);
     DXSetDisplayPara(DeviceInfo[CardNo].dwChannelHandle,1, ContrastValue,iFlags);

     SettingIni.WriteInteger('Colorpropterty','ContrastValue'+inttostr(CardNo),ContrastValue);
end;

procedure TColorProperty.ScrollBarHueChange(Sender: TObject);
begin
      HueValue:= ScrollBarHue.Position;
      HueVal.Caption :=IntToStr(HueValue);
       DXSetDisplayPara(DeviceInfo[CardNo].dwChannelHandle,2, HueValue,iFlags);

      SettingIni.WriteInteger('Colorpropterty','HueValue'+inttostr(CardNo),HueValue);
end;

procedure TColorProperty.ScrollBarSaturationChange(Sender: TObject);
begin
      StaturationValue:= ScrollBarSaturation.Position;
      SaturationVal.Caption :=IntToStr(StaturationValue);
      DXSetDisplayPara(DeviceInfo[CardNo].dwChannelHandle,3, StaturationValue,iFlags);

     SettingIni.WriteInteger('Colorpropterty','StaturationValue'+inttostr(CardNo),StaturationValue);

end;

procedure TColorProperty.ScrollBarSharpChange(Sender: TObject);
begin
      SharpValue:= ScrollBarSharp.Position;
      SharpVal.Caption :=IntToStr(SharpValue);
      DXSetDisplayPara(DeviceInfo[CardNo].dwChannelHandle,4, SharpValue,iFlags);
      
      SettingIni.WriteInteger('Colorpropterty','SharpnessValue'+inttostr(CardNo),SharpValue);
end;

procedure TColorProperty.OKBtnClick(Sender: TObject);
begin
     ColorProperty.Close ;
end;

procedure TColorProperty.FormShow(Sender: TObject);
var
     i:LongWord   ;
begin


        if  (DeviceInfo[CardNo].dwConnectState=True) then
       begin
              for i:=0 to 4 do
              begin
                     //得到视频设备色彩空间范围和默认值
                       DXGetDisplayParaRange(DeviceInfo[CardNo].dwChannelHandle,i,
                                             DeviceColor[i].MinVal,
                                             DeviceColor[i].MaxVal,
                                             DeviceColor[i].StepVal,
                                             DeviceColor[i].DefaultVal,
                                             iFlags);


              end;
              //赋值亮度进度条
                ScrollBarBright.Max :=DeviceColor[0].MaxVal;
              ScrollBarBright.Min :=DeviceColor[0].MinVal;
              ScrollBarBright.LargeChange :=DeviceColor[0].StepVal;
              ScrollBarBright.Position :=DeviceColor[0].DefaultVal;
              //赋值对比度进度条
             ScrollBarContrast.Max :=DeviceColor[1].MaxVal;
              ScrollBarContrast.Min :=DeviceColor[1].MinVal;
              ScrollBarContrast.LargeChange :=DeviceColor[1].StepVal;
              ScrollBarContrast.Position :=DeviceColor[1].DefaultVal;
              //赋值饱和度进度条
              ScrollBarHue.Max :=DeviceColor[2].MaxVal;
              ScrollBarHue.Min :=DeviceColor[2].MinVal;
              ScrollBarHue.LargeChange:=DeviceColor[2].StepVal;
              ScrollBarHue.Position := DeviceColor[2].DefaultVal;
                   //赋值色度进度条
             ScrollBarSaturation.Max :=DeviceColor[3].MaxVal;
              ScrollBarSaturation.Min :=DeviceColor[3].MinVal;
              ScrollBarSaturation.LargeChange:=DeviceColor[3].StepVal;
              ScrollBarSaturation.Position :=DeviceColor[3].DefaultVal;

               ////赋值
              ScrollBarSharp.Max :=DeviceColor[4].MaxVal;
              ScrollBarSharp.Min :=DeviceColor[4].MinVal;
              ScrollBarSharp.LargeChange :=DeviceColor[4].StepVal;
              ScrollBarSharp.Position :=DeviceColor[4].DefaultVal;

       end;








end;

procedure TColorProperty.DefColorClick(Sender: TObject);
var i:LongWord ;


begin
           if  (DeviceInfo[CardNo].dwConnectState=True) then
       begin
            ScrollBarBright.Position :=DeviceColor[0].DefaultVal;
            ScrollBarContrast.Position :=DeviceColor[1].DefaultVal;
            ScrollBarHue.Position := DeviceColor[2].DefaultVal;
            ScrollBarSaturation.Position :=DeviceColor[3].DefaultVal;
            ScrollBarSharp.Position :=DeviceColor[4].DefaultVal;
            for i:=0 to 4 do
            begin
                  DXSetDisplayPara(DeviceInfo[CardNo].dwChannelHandle,i,DeviceColor[i].DefaultVal,iFlags);
            end;

       end;


end;

procedure TColorProperty.CancelBtnClick(Sender: TObject);
begin
      ColorProperty.Close ;
end;

end.
