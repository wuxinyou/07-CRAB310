unit ImagealgorithmSetting;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs,IniFiles, StdCtrls;

type
  TImagealgorithmFrm = class(TForm)
    scrlbrBright: TScrollBar;
    scrlbrContrast: TScrollBar;
    btnExit: TButton;
    Label1: TLabel;
    Label2: TLabel;
    lblBrightValue: TLabel;
    lblContrastValue: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    lblSharpValue: TLabel;
    lblDenoiseValue: TLabel;
    scrlbrDenoise: TScrollBar;
    scrlbrSharpness: TScrollBar;
    procedure FormCreate(Sender: TObject);
    procedure scrlbrBrightChange(Sender: TObject);
    procedure scrlbrContrastChange(Sender: TObject);
    procedure btnExitClick(Sender: TObject);
    procedure scrlbrDenoiseChange(Sender: TObject);
    procedure scrlbrSharpnessChange(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  ImagealgorithmFrm: TImagealgorithmFrm;

implementation
 uses GlobalVar,DxMediaFunction,DxMediaApi;
{$R *.dfm}

procedure TImagealgorithmFrm.FormCreate(Sender: TObject);
begin

             scrlbrDenoise.Max :=100;
               scrlbrDenoise.Min :=0;
              scrlbrDenoise.LargeChange :=1;
              scrlbrDenoise.Position :=65;


                scrlbrSharpness.Max :=255;
                scrlbrSharpness.Min :=0;
               scrlbrSharpness.LargeChange :=1;
               scrlbrSharpness.Position :=10;


              scrlbrBright.Max :=255;
              scrlbrBright.Min :=-255;
              scrlbrBright.LargeChange :=1;
              scrlbrBright.Position :=0;

              scrlbrContrast.Max :=100;
              scrlbrContrast.Min :=-100;
              scrlbrContrast.LargeChange :=1;
              scrlbrContrast.Position :=30;

              lblDenoiseValue.Caption :=IntToStr( scrlbrDenoise.Position);
              lblDenoiseValue.Caption :=IntToStr( scrlbrDenoise.Position);

              lblSharpValue.Caption :=IntToStr( scrlbrSharpness.Position);
              lblSharpValue.Caption :=IntToStr( scrlbrSharpness.Position);

              lblBrightValue.Caption :=IntToStr( scrlbrBright.Position);
              lblContrastValue.Caption :=IntToStr( scrlbrContrast.Position);

              DRateColorPara[CardNo].nBrightness :=scrlbrBright.Position;
              DRateColorPara[CardNo].nContrast  :=scrlbrContrast.Position;






end;

procedure TImagealgorithmFrm.scrlbrBrightChange(Sender: TObject);
begin
          DRateColorPara[CardNo].nBrightness :=scrlbrBright.Position;
          lblBrightValue.Caption :=IntToStr( scrlbrBright.Position);
          DXEnDataRaterPara(DeviceInfo[CardNo].dwChannelHandle,0, DRateColorPara[CardNo]);

         // SettingIni.WriteInteger('Imagealgorithm','Brightness'+inttostr(CardNo),scrlbrBright.Position);
end;

procedure TImagealgorithmFrm.scrlbrContrastChange(Sender: TObject);
begin
          DRateColorPara[CardNo].nContrast  :=scrlbrContrast.Position;
          lblContrastValue.Caption :=IntToStr( scrlbrContrast.Position);
          DXEnDataRaterPara(DeviceInfo[CardNo].dwChannelHandle,0, DRateColorPara[CardNo]);

      // SettingIni.WriteInteger('Imagealgorithm','Contrast'+inttostr(CardNo),scrlbrContrast.Position);
end;

procedure TImagealgorithmFrm.btnExitClick(Sender: TObject);
begin
          ImagealgorithmFrm.Close ;
end;

procedure TImagealgorithmFrm.scrlbrDenoiseChange(Sender: TObject);
begin
         DXEnableDenoise(DeviceInfo[CardNo].dwChannelHandle,scrlbrDenoise.position);
         lblDenoiseValue.caption:=inttostr(scrlbrDenoise.position);
end;


procedure TImagealgorithmFrm.scrlbrSharpnessChange(Sender: TObject);
begin
         DXEnableSharpen(DeviceInfo[CardNo].dwChannelHandle,scrlbrSharpness.position);
         lblSharpValue.caption:=inttostr(scrlbrSharpness.position);
end;

end.
