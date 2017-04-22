unit DlgDigitalZoom;

interface

uses Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls, 
  Buttons, ExtCtrls;

type
  TDlgZoom = class(TForm)
    OKBtn: TButton;
    CancelBtn: TButton;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    etZoomTop: TEdit;
    etZoomLeft: TEdit;
    etZoomRight: TEdit;
    etZoomBot: TEdit;
    chkEnableZoom: TCheckBox;
    procedure OKBtnClick(Sender: TObject);
    procedure CancelBtnClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  DlgZoom: TDlgZoom;

implementation
  uses GlobalVar,DxMediaFunction,DxMediaApi;
{$R *.dfm}

procedure TDlgZoom.OKBtnClick(Sender: TObject);
begin

           DeviceInfo[CardNo].dwZoomRect.Top:=StrToInt(etZoomTop.Text);
           DeviceInfo[CardNo].dwZoomRect.Left:=StrToInt(etZoomLeft.Text);
            DeviceInfo[CardNo].dwZoomRect.Right:=StrToInt(etZoomRight.Text);
            DeviceInfo[CardNo].dwZoomRect.Bottom:=StrToInt(etZoomBot.Text);
                if( DeviceInfo[CardNo].dwConnectState=True) then
                begin
                        if  chkEnableZoom.Checked =true then
                        begin
                               DXEnFScale(DeviceInfo[CardNo].dwChannelHandle,
                                           true,
                                           DeviceInfo[CardNo].dwZoomRect,
                                           0);
                        end
                        else
                        begin

                                DXEnFScale(DeviceInfo[CardNo].dwChannelHandle,
                                           false,
                                           DeviceInfo[CardNo].dwZoomRect,
                                           0);
                        end;

                end;


end;

procedure TDlgZoom.CancelBtnClick(Sender: TObject);
begin
       DlgZoom.Close ;
end;

end.
