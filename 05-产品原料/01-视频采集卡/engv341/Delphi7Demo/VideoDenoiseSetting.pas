unit VideoDenoiseSetting;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TVideoDenoiseSet = class(TForm)
    ScrollBar1: TScrollBar;
    Label1: TLabel;
    DenoiseValue: TLabel;
    Label2: TLabel;
    SharpValue: TLabel;
    BrightValue: TLabel;
    ContrastValue: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    ScrollBarSharp: TScrollBar;
    ScrollBarBright: TScrollBar;
    ScrollBarContrast: TScrollBar;
    procedure FormCreate(Sender: TObject);
    procedure ScrollBarContrastChange(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  VideoDenoiseSet: TVideoDenoiseSet;

implementation
 uses GlobalVar,DxMediaApi;
{$R *.dfm}

procedure TVideoDenoiseSet.FormCreate(Sender: TObject);
begin


      
      DXEnableDenoise(DeviceInfo[CardNo].dwChannelHandle,ScrollBar1.position);
      DenoiseValue.caption:=inttostr(ScrollBar1.position);
end;

procedure TVideoDenoiseSet.ScrollBarContrastChange(Sender: TObject);
begin
       DXEnableDenoise(DeviceInfo[CardNo].dwChannelHandle,ScrollBar1.position);
       DenoiseValue.caption:=inttostr(ScrollBar1.position);
end;

end.
