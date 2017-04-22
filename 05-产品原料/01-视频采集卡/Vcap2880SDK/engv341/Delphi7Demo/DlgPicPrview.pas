unit DlgPicPrview;

interface

uses Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls, 
  Buttons, ExtCtrls;

type
  TDlgPrvHwnd = class(TForm)
    Button1: TButton;
    procedure FormShow(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormActivate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure FormResize(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  DlgPrvHwnd: TDlgPrvHwnd;
   PrvImageHandle:Thandle;
    PicBuf:pchar ;
      BufSize:LongWord;
implementation
uses GlobalVar,DxMediaApi,DxMediaFunction, Unit1;
{$R *.dfm}

procedure TDlgPrvHwnd.FormShow(Sender: TObject);
var

    colorSpace:LongWord ;
    nWidth:LongWord ;
    nHeight:LongWord ;

    BytesWidth:LongWord ;
    gotBufferLen:LongWord ;
  
    PrvRect:TRect;


begin


        nWidth:=0;
        nHeight:=0;
        colorSpace:=0;
        BytesWidth:=0;
        gotBufferLen:=0;

       

         Windows.GetClientRect(DlgPrvHwnd.Handle  , PrvRect);
        if ConnectOk[CardNo]=0 then
        begin
              BufSize:=2048*1024*3;
              PicBuf:=AllocMem(BufSize);

              //得到视频设备的属性参数
              DXGetVideoPara(CardHandle[CardNo], DeviceInf.dwVidStandard,
                                               DeviceInf.dwColorspace,
                                               DeviceInf.dwCapWeight,
                                               DeviceInf.dwCapHeight,
                                               DeviceInf.dwFrameRate);
             //抓拍图像的区域
             SnapRect.Left :=0;
             SnapRect.Top :=0;
             SnapRect.Right :=DeviceInf.dwCapWeight;
             SnapRect.Bottom :=DeviceInf.dwCapHeight;
           //  PrvRect.Left :=0;
            // PrvRect.Top :=0;
            //  PrvRect.Right :=DeviceInf.dwCapWeight;
             //PrvRect.Bottom :=DeviceInf.dwCapHeight;

            //得到当前帧的buf数据
             DXGetFrameBuffer(CardHandle[CardNo],PicBuf,BufSize,gotBufferLen, colorSpace,nWidth ,nHeight,BytesWidth,SnapRect );
            // PrvImageHandle:=DXCreateBufferImg(PicBuf, gotBufferLen, colorSpace,nWidth,nHeight,PrvImageState);
           //  DXUpdateImg(PrvImageHandle, DlgPrvHwnd.Handle , PrvRect);
             PrvOk:=true;
            //  Timer1.Interval :=50;
             //Timer1.Enabled :=True ;
        end;

  end;

procedure TDlgPrvHwnd.FormClose(Sender: TObject; var Action: TCloseAction);
begin
         if PrvOk=true then
         begin
              // DXDestroyImg(PrvImageHandle);
               FreeMem(PicBuf,BufSize);
         end;
end;

procedure TDlgPrvHwnd.FormResize(Sender: TObject);
begin
        //DXUpdateImg(PrvImageHandle, panel1.Handle , PrvRect);
end;

procedure TDlgPrvHwnd.FormActivate(Sender: TObject);
begin
           //DXUpdateImg(PrvImageHandle, DlgPrvHwnd.Handle , PrvRect);
end;

procedure TDlgPrvHwnd.Button1Click(Sender: TObject);
begin
       //DXUpdateImg(PrvImageHandle, DlgPrvHwnd.Handle , PrvRect);
end;

procedure TDlgPrvHwnd.Timer1Timer(Sender: TObject);
begin
           // DXUpdateImg(PrvImageHandle, panel1.Handle , PrvRect);
end;

end.
