unit VideoDevice;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TVideoDeviceFrm = class(TForm)
    Label1: TLabel;
    ComboBox1: TComboBox;
    procedure ComboBox1Change(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  VideoDeviceFrm: TVideoDeviceFrm;

implementation
uses DxMediaApi, GlobalVar,DxMediaFunction;
{$R *.dfm}

procedure TVideoDeviceFrm.ComboBox1Change(Sender: TObject);
var CurNo:longword;
begin
        CurNo:=ComboBox1.ItemIndex;
        if (curno<>CardNo) and (OpenDevState[CardNo]=0) then
        begin
             //  DisconnectDev(CardNo);
               if OpenDevState[CardNo]=0 then
               begin
                      DXCloseDevice(CardHandle[CardNo]);
               end;
               if OpenDevState[CurNo]<>0 then
               begin
                        CardHandle[CurNo]:=DXOpenDevice(CurNo,OpenDevState[CurNo] );
                        DXDeviceRun(CardHandle[CurNo]);
                                 //连接设备
                     //   ConnectOk[CurNo]:=ConnectDev(CurNo,PrvHandle[0],PrvRect);
                         //设置隔行算法
                       DXEnableDeinterlace( CardHandle[CurNo],2);
               end;
               CardNo:=CurNo ;
        end;
end;

end.
