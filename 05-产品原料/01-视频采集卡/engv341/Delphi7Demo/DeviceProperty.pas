unit DeviceProperty;

interface

uses Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls, 
  Buttons, ExtCtrls;

type
  TOKBottomDlg = class(TForm)
    OKBtn: TButton;
    CancelBtn: TButton;
    DlgPrvHwnd: TPanel;
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  OKBottomDlg: TOKBottomDlg;

implementation
uses GlobalVar,DxMediaApi,DxMediaFunction;
{$R *.dfm}

procedure TOKBottomDlg.FormShow(Sender: TObject);
var prvrect:TRect ;
begin
        if  ConnectOk[CardNo]=0 then
        begin
              Windows.GetClientRect(DlgPrvHwnd.Handle , prvrect);
              DXShowDeviceAttr(CardHandle[CardNo],1, DlgPrvHwnd.Handle , prvrect);
        end;

end;

end.
