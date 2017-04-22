unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, StdCtrls, ExtCtrls,IniFiles;
  const My_Message=WM_USER+200;
type
  TForm1 = class(TForm)
    Button3: TButton;
    MainMenu1: TMainMenu;
    Button4: TButton;
    Button5: TButton;
    btEnumVideoCodec: TButton;
    btSnap: TButton;
    btCapture: TButton;
    btFreezeCap: TButton;
    btSetOSD: TButton;
    VideoSourceMenu: TMenuItem;
    VideoStandMenu: TMenuItem;
    DeinterlaceMenu: TMenuItem;
    DeinterBlend: TMenuItem;
    DeinterBob: TMenuItem;
    DeinterCancel: TMenuItem;
    PalMenu: TMenuItem;
    NtscMenu: TMenuItem;
    btEnableRawCall: TButton;
    btCallBackSnap: TButton;
    VideoEffect: TMenuItem;
    VideoFlipMenu: TMenuItem;
    VideoMirrMenu: TMenuItem;
    N1: TMenuItem;
    AV1Menu: TMenuItem;
    av2Menu: TMenuItem;
    SVIDEOMenu: TMenuItem;
    Timer1: TTimer;
    CheckBox1: TCheckBox;
    N2: TMenuItem;
    D1Menu: TMenuItem;
    CIFMenu: TMenuItem;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Imageenhancement1: TMenuItem;
    Menu768: TMenuItem;
    DeinterLow: TMenuItem;
    GroupBox2: TGroupBox;
    VMR7Mode: TRadioButton;
    OffScreamMode: TRadioButton;
    VMR9Mode: TRadioButton;
    btZoom: TButton;
    procedure FormShow(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure btEnumVideoCodecClick(Sender: TObject);
    procedure btCaptureClick(Sender: TObject);
    procedure btFreezeCapClick(Sender: TObject);
    procedure btSnapClick(Sender: TObject);
    procedure btSetOSDClick(Sender: TObject);
    procedure DeinterBlendClick(Sender: TObject);
    procedure DeinterBobClick(Sender: TObject);
    procedure DeinterweaveClick(Sender: TObject);
    procedure DeinterCancelClick(Sender: TObject);
    procedure btEnableRawCallClick(Sender: TObject);
    procedure D1MenuClick(Sender: TObject);
    procedure CIFMenuClick(Sender: TObject);
    procedure btCallBackSnapClick(Sender: TObject);
    procedure VideoFlipMenuClick(Sender: TObject);
    procedure VideoMirrMenuClick(Sender: TObject);
    procedure DevProptyMenuClick(Sender: TObject);
    procedure btSnapPreviewClick(Sender: TObject);
    procedure N1Click(Sender: TObject);
  
    procedure AV1MenuClick(Sender: TObject);
    procedure av2MenuClick(Sender: TObject);
    procedure SVIDEOMenuClick(Sender: TObject);
    procedure PalMenuClick(Sender: TObject);
    procedure NtscMenuClick(Sender: TObject);
    procedure VideoDevMenuClick(Sender: TObject);
    procedure DenoiseMenuClick(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure MyHwndClick(Sender: TObject);
    procedure MyMouseDown(Sender: TObject; Button: TMouseButton;
                           Shift: TShiftState; X, Y: Integer);
    procedure Imageenhancement1Click(Sender: TObject);
    procedure Menu768Click(Sender: TObject);
    procedure DeinterLowClick(Sender: TObject);
    procedure VMR7ModeClick(Sender: TObject);
    procedure OffScreamModeClick(Sender: TObject);
    procedure VMR9ModeClick(Sender: TObject);
    procedure btZoomClick(Sender: TObject);


  private
    { Private declarations }
   
    procedure MyMessage(var MyMsg:TMessage);message My_Message;
  public
    { Public declarations }
  end;


var
  Form1: TForm1;
  CardNum:LongWord ;
  VideoPrvHwnd:array [0..23] of TPanel ;
  AudioHas:Boolean ;
  VidDeviceMenu:   TMainMenu;
  AudDeviceMenu:   TMainMenu;
  VidDeviceName:array[0..23] of TMenuItem;
  AudioDeviceName:array[0..23] of TMenuItem;

  //y预先分配抓拍的内存空间
   pBufSnapPic: PChar;
   PRgbBuf:PChar;
   nBytesWidth:LongWord ;
   nColorSpace:LongWord;
   BufSize:LongWord;

   PrvWidth:LongWord;
   PrvHeight:LongWord;
   nIndex:LongWord;
   m_nWndNum:LongWord;
    m_nShowMode:LongWord;



implementation
uses GlobalVar,DxMediaApi,DxMediaFunction,EnumCodecSet,OSDSetting,DeviceProperty,DlgPicPrview,DlgDigitalZoom,VideoDevice,VideoDenoiseSetting,ColorSetting,ImagealgorithmSetting;

{$R *.dfm}
////此消息函数对一帧视频数据进行保存
procedure TForm1.MyMessage(var MyMsg:TMessage);
var nCardNo:LongWord ;
begin
        //将buf数据存储为照片
          //  DXSaveBMPFile(PAnsiChar(AnsiString(PicFileName)),pBufSnapPic,BufSize, nColorSpace ,nWidth ,nHeight ,nBytesWidth);
             nCardNo:= MyMsg.WParam ;
             //将回调到的YUV2原始数据转换成rgb24
            DxMediaApi.DXConvertYUVtoRGB(DeviceInfo[nCardNo].dwChannelHandle,
            pBufSnapPic,
            PRgbBuf,
            nWidth,
            nHeight,
            True ,false) ;
            DxMediaFunction.CreateBmpFile(PicFileName,PRgbBuf,nWidth,nHeight);
             {
            ///// Add the bmp header information//////////////////
               //填充bmp信息头
             FillChar(bmpinfo, sizeof(bmpinfo), 0);
             BmpHeader.bfType :=$4D42;
             BmpHeader.bfSize :=40;
             BmpHeader.bfOffBits :=sizeof(Bmpinfo)+sizeof(BmpHeader)+3*sizeof(dword);
             Bmpinfo.bmiHeader.biSize := sizeof(BITMAPINFOHEADER);
             Bmpinfo.bmiHeader.biWidth := nWidth;
             Bmpinfo.bmiHeader.biHeight := nHeight;
             Bmpinfo.bmiHeader.biCompression :=BI_RGB;
             Bmpinfo.bmiHeader.biPlanes := 1;
             Bmpinfo.bmiHeader.biBitCount :=3*8;
             Bmpinfo.bmiHeader.biSizeImage := nWidth * nHeight*3;
               //创建bmp
             Bmp :=  Tbitmap.Create;
             Bmp.Handle :=CreateDIBSection(0,Bmpinfo,DIB_PAL_COLORS,buf,0,0);
               //拷贝rgb24数据到bmp缓冲区
             Move(PRgbBuf^, buf^, Bmpinfo.bmiHeader.biSizeImage);
            // Bmp.SaveToFile(PAnsiChar(AnsiString(PicFileName))); }

end;

///{---- 抓拍回调函数，注意保持回调函数的简洁快速，所以关于视频数据的大量处理应另外处理
//此处我是发送一个消息My_Message ，在消息函数中对视频数据进行保存文件

procedure CallBackSnap (pBuff: PByte ;
                        colorSpace: longword;
                        lWidth:longword;
                        lHeight:longword;
                        bytesWidth:LongWord;
                        var context:LongWord); stdcall;

begin

    if  CallSnapOk= false then
    begin
        exit;
    end;
        nWidth:=lWidth;
        nHeight:= lHeight;
        nColorSpace:=colorSpace;
        nBytesWidth:=bytesWidth;
        BufSize:= nWidth* nHeight* colorSpace;
        //把回调到的buf数据拷贝到预先分配好的buf空间
        move(pBuff^, pBufSnapPic^, BufSize);
        Postmessage(form1.Handle ,My_Message,context,0);
        CallSnapOk:=False ;

end;


procedure TForm1.FormShow(Sender: TObject);
var

     i:longword;
     j:LongWord;

  


begin


        nIndex:=0;
        Form1.Left :=10;
        form1.Top :=10;
        form1.Width :=720+125;
        form1.Height :=576+50;

       CardNo:=0;


                         //创建ini文件
          CreateIniFile('DelphiSetting.ini');



       /////////////////////////////read the ini file parameter  start///////////////////

         // OSD INI FILE
        TimeX:=SettingIni.ReadInteger('OSDSetting','TimeX',10);
        TimeY:=SettingIni.ReadInteger('OSDSetting','TimeY',30);
        TimeFontSizeVal:=SettingIni.ReadInteger('OSDSetting','TimeFontSize',25);
        TxtFontSizeVal[0]:=SettingIni.ReadInteger('OSDSetting','TxtFontSize0',25);
        TxtPlaceX[0]:= SettingIni.ReadInteger('OSDSetting','TxtPlaceX0',10);
        TxtPlaceY[0]:=SettingIni.ReadInteger('OSDSetting','TxtPlaceY0', 70);
        Osd_Txt[0]:=SettingIni.ReadString('OSDSetting','Osd_Txt0', 'Camera1');
        TxtFontSizeVal[1]:=SettingIni.ReadInteger('OSDSetting','TxtFontSize1',25);
        TxtPlaceX[1]:= SettingIni.ReadInteger('OSDSetting','TxtPlaceX1',10);
        TxtPlaceY[1]:=SettingIni.ReadInteger('OSDSetting','TxtPlaceY1', 110);
        Osd_Txt[1]:=SettingIni.ReadString('OSDSetting','Osd_Txt1', 'Camera2');

         OsdSettingDlg.TimePlaceX.Text :=inttostr(TimeX);
         OsdSettingDlg.TimePlaceY.Text  :=inttostr(TimeY);
         OsdSettingDlg.TimeFontSize.Text :=Inttostr(TimeFontSizeVal);

        OsdSettingDlg.TextPlaceX1.Text  :=inttostr( TxtPlaceX[0]);
        OsdSettingDlg.TextPlaceY1.Text  :=inttostr( TxtPlaceY[0]);
        OsdSettingDlg.TxtFontSize1.Text :=Inttostr( TxtFontSizeVal[0]);
        OsdSettingDlg.OsdText1.Text:=Osd_Txt[0];

        OsdSettingDlg.TextPlaceX2.Text  :=inttostr( TxtPlaceX[1]);
        OsdSettingDlg.TextPlaceY2.Text  :=inttostr( TxtPlaceY[1]);
        OsdSettingDlg.TxtFontSize2.Text :=Inttostr( TxtFontSizeVal[1]);
        OsdSettingDlg.OsdText2.Text:=Osd_Txt[1];

          if Comparetext(SettingIni.ReadString('OSDSetting','TextTranspar1', 'True'),'True')=0 then
         begin
              OsdSettingDlg.TextTranspar1.Checked :=True;

        end
        else
        begin
               OsdSettingDlg.TextTranspar1.Checked :=False;
        end;

        if Comparetext(SettingIni.ReadString('OSDSetting','TextTranspar2', 'True'),'True')=0 then
        begin
               OsdSettingDlg.TextTranspar2.Checked :=True;
        end
        else
        begin
               OsdSettingDlg.TextTranspar2.Checked :=false;
        end;

          if Comparetext(SettingIni.ReadString('OSDSetting','TextOsdEnable1', 'True'),'True')=0 then
         begin
                OsdSettingDlg.TextOsd1.Checked:=True;
        end
        else
        begin
                OsdSettingDlg.TextOsd1.Checked:=false;
        end;
        if Comparetext(SettingIni.ReadString('OSDSetting','TextOsdEnable2', 'True'),'True')=0 then
         begin
                 OsdSettingDlg.TextOsd2.Checked:=True;
        end
        else
        begin
               OsdSettingDlg.TextOsd2.Checked:=false;
        end;

            if Comparetext(SettingIni.ReadString('OSDSetting','TimeOsdEnable', 'True'),'True')=0 then

        begin
                 OsdSettingDlg.TimeOsd.Checked :=True;
        end
        else
        begin
               OsdSettingDlg.TimeOsd.Checked :=false;
        end;

         if Comparetext(SettingIni.ReadString('OSDSetting','TimeTranspar', 'True'),'True')=0 then

        begin
               OsdSettingDlg.TimeTranspar.Checked :=True;
        end
        else
        begin
                  OsdSettingDlg.TimeTranspar.Checked :=false;
        end;

        /////////system par ini



        RecSavePath:=SettingIni.ReadString('SystemSetting','VideoSavePath', 'd:\');
        PicSavePath:=SettingIni.ReadString('SystemSetting','PictureSavePath', 'd:\');
        EnumCodecFrm.TxtPicPath.Text :=  PicSavePath;
        EnumCodecFrm.TxtRecPath.Text:=RecSavePath;
        

      if Comparetext(SettingIni.ReadString('SystemSetting','VideoCodec', 'x264 Codec'),'x264 Codec')=0 then
      begin
              EnumCodecFrm.rbX264.Checked :=True;

      end;

      if Comparetext(SettingIni.ReadString('SystemSetting','VideoCodec', 'DivX? 5.1.1 Codec'),'DivX? 5.1.1 Codec')=0 then
      begin
              EnumCodecFrm.rbDivx.Checked :=True;

      end;

      if Comparetext(SettingIni.ReadString('SystemSetting','VideoCodec', 'xvid Codec'),'xvid Codec')=0 then
      begin
              EnumCodecFrm.rbXvid.Checked :=True;

      end;

         /////////////////////////////read the ini file parameter  end/////////////////// ///////////
               if Comparetext(SettingIni.ReadString('SystemSetting','PreviewMode', 'VMR7'),'VMR7')=0 then
               begin
                      dwPreviewMode:=0;
                      VMR7Mode.Checked :=true;
                      VMR9Mode.Checked :=false;
                      OffScreamMode.Checked :=false;

               end;

                if Comparetext(SettingIni.ReadString('SystemSetting','PreviewMode', 'OffScream'),'OffScream')=0 then
               begin
                      dwPreviewMode:=1;
                      VMR7Mode.Checked :=false;
                      VMR9Mode.Checked :=false;
                      OffScreamMode.Checked :=true;

               end;


                if Comparetext(SettingIni.ReadString('SystemSetting','PreviewMode', 'VMR9'),'VMR9')=0 then
               begin
                      dwPreviewMode:=2;
                     VMR7Mode.Checked :=false;
                      VMR9Mode.Checked :=true;
                      OffScreamMode.Checked :=false;

               end;

       ////////////////////////////////////////The variable initialization start //////////////////////////////////
       for i:=0 to 23 do
       begin

            ConnectOk[i]:=1;
            RawCallOk[i]:=1;
            OpenDevState[i]:=1;
            DeviceInfo[i].dwRecOK:=false;
            DeviceInfo[i].dwFreezeOK:=false;
       end;

        CodecSet:=False ;

        CallSnapOk:=false ;
        AudioHas:=False ;
        DeinterBob.Checked :=True;
        //初始化赋值视频卡号
        CardNo:=0;
        VideoDeviceNum:=126;
        AudioDeviceNum:=126;
        ImageFlip:=false;
        ImageMirr :=False;
         timer1.Enabled :=false  ;

       ////////////////////////////////The variable initialization end////////////////////////////////////////////////////////
       //初始化SDK得到系统中设备数量

       CardNum:=DxMediaFunction.InitDevice;

        //枚举系统中有效的音频设备名称
        DXEnumAudioDevices(AudioDeviceInfo[0],AudioDeviceNum);

       ////////////////////////start create the preview hwnd and the hwnd preview mode   //////////////

       //单路窗体显示
       if CardNum<2 then
       begin

                  m_nWndNum:=1;
                  m_nShowMode:=1;
                  //1分屏显示时预览窗体大小
                PrvWidth:=Trunc((Form1.Width-130)/ m_nShowMode);
                PrvHeight :=Trunc((Form1.Height -50)/ m_nShowMode);

       end;
       //4 screen preview mode
       if (CardNum>1) and (CardNum<5) then
       begin

                  m_nWndNum:=4;
                  m_nShowMode:=2;
                  //4 screen preview mode  the windows size
                PrvWidth:=Trunc((Form1.Width-130)/ m_nShowMode);
                PrvHeight :=Trunc((Form1.Height -50)/ m_nShowMode);


       end;
        for i:=0 to m_nWndNum-1 do
          begin
                VideoPrvHwnd[i]:=TPanel.Create(Form1);
                VideoPrvHwnd[i].BorderStyle := bsNone;
                VideoPrvHwnd[i].Parent:=Form1;
                VideoPrvHwnd [i].Width := PrvWidth;
                VideoPrvHwnd [i].Height :=PrvHeight;
                VideoPrvHwnd [i].OnDblClick :=MyHwndClick;
                VideoPrvHwnd [i].OnMouseDown :=MyMouseDown;
                VideoPrvHwnd[i].Visible:=True;
                VideoPrvHwnd[i].Color :=RGB(0,0,255) ;
                VideoPrvHwnd[i].Name:='panel'+inttostr(i);
                VideoPrvHwnd[i].Caption:='';

                DeviceInfo[i].dwPrvHandle:= VideoPrvHwnd [i].Handle ;
                Windows.GetClientRect(VideoPrvHwnd[i].Handle, DeviceInfo[i].dwPrvRect);



          end;

                //  Define the preview window position
          for i:=0 to m_nShowMode-1 do
          begin
                for j:=0 to m_nShowMode-1  do
                begin
                  nIndex:=i*m_nShowMode+j;
                  if  nIndex >= m_nWndNum then
                  begin

                        Exit;
                  end;
                 VideoPrvHwnd[nIndex].Left :=PrvWidth*j;
                 VideoPrvHwnd[nIndex].Top :=PrvHeight  *i;

                end;


           end;
       ////////////////////end windows  create   ////////////////////////////////////
        if CardNum<1 then
       begin
             ShowMessage('init sdk false,please check the card valid?');
       end
       else
       begin

               for i:=0 to CardNum-1 do
               begin
                      /// ////read the ini file set the video property  start//////////
                    DeviceInfo[i].dwVidStandard:=SettingIni.ReadInteger('SystemSetting','VidStandard'+inttostr(i),$20);
                    DeviceInfo[i].dwColorspace:=2;
                    DeviceInfo[i].dwCapWeight:=SettingIni.ReadInteger('SystemSetting','VidWidth'+inttostr(i),720);
                    DeviceInfo[i].dwCapHeight:=SettingIni.ReadInteger('SystemSetting','VidHeight'+inttostr(i),576);
                    DeviceInfo[i].dwFrameRate:=SettingIni.ReadInteger('SystemSetting','FrameRate'+inttostr(i),25);

                        /// ////read the ini file set the video property  end//////////

                    //open device
                    DeviceInfo[i].dwChannelHandle:=DxMediaFunction.OpenDevice(i,OpenDevState[i] );
                    //connect the device
                    DeviceInfo[i].dwConnectState:=DxMediaFunction.ConnectDevice(DeviceInfo[i].dwChannelHandle,
                                                                                DeviceInfo[i].dwVidStandard,
                                                                                DeviceInfo[i].dwColorspace,
                                                                                DeviceInfo[i].dwCapWeight,
                                                                                DeviceInfo[i].dwCapHeight,
                                                                                DeviceInfo[i].dwFrameRate);

                    if(DeviceInfo[i].dwConnectState=true) then
                    begin
                            // start preview
                            DeviceInfo[i].dwPrviewState:=DxMediaFunction.StartPrview(DeviceInfo[i].dwChannelHandle,
                                                                                   DeviceInfo[i].dwPrvHandle,
                                                                                   DeviceInfo[i].dwPrvRect,
                                                                                   dwPreviewMode);

                    end;
                     //set the video Deinterlace  algorithm
                     ////value= 0: CPU resources is lower, apply to older cpu  Celeron or Pentium Dual-Core ////////////////////
                     ///value=-1 ; cancel the  Deinterlace  algorithm
                    DXEnableDeinterlace(DeviceInfo[i].dwChannelHandle,0) ;



               end;

          

       end;




  end;
        
 procedure TForm1.MyMouseDown(Sender: TObject; Button: TMouseButton;
                           Shift: TShiftState; X, Y: Integer);
 var str:string;
 begin
            str:= Copy(TPanel(sender).Name,6,1);
            with   Sender   as   TPanel   do
            begin
                    case StrToInt(str)  of

                        0:
                        begin
                             CardNo:=0;
                             Label1.Caption:='Card'+'1' ;
                        end;
                         1:
                        begin
                             CardNo:=1;
                             Label1.Caption:='Card'+'2' ;
                        end;
                         2:
                        begin
                             CardNo:=2;
                             Label1.Caption:='Card'+'3' ;
                        end;
                         3:
                        begin
                             CardNo:=3;
                             Label1.Caption:='Card'+'4' ;
                        end;
                  end;
              end;
 end;
//

procedure TForm1.MyHwndClick (Sender: TObject);
var i:LongWord;
    j:LongWord ;
    k:LongWord;
    p:LongWord;
    str:string;
begin
            str:= Copy(TPanel(sender).Name,6,1);
            with   Sender   as   TPanel   do
            begin
                    case StrToInt(str)  of

                        0:
                        begin

                            if DeviceInfo[0].dwMaxHwnd=False then
                            begin

                              VideoPrvHwnd[CardNo].Width :=Form1.Width-130;

                              VideoPrvHwnd[CardNo].Height :=Form1.Height -50;

                              Windows.GetClientRect(VideoPrvHwnd[CardNo].Handle, DeviceInfo[CardNo].dwPrvRect);
                              DxMediaFunction.StopPrview(DeviceInfo[CardNo].dwChannelHandle);
                              for i:=0 to m_nWndNum-1 do
                              begin

                                     VideoPrvHwnd[i].Visible:=false;

                              end;
                              VideoPrvHwnd[0].Visible:=true;
                              DeviceInfo[CardNo].dwPrviewState:=DxMediaFunction.StartPrview(DeviceInfo[CardNo].dwChannelHandle,
                                                                                   DeviceInfo[CardNo].dwPrvHandle,
                                                                                   DeviceInfo[CardNo].dwPrvRect,
                                                                                   dwPreviewMode);

                               DeviceInfo[0].dwMaxHwnd:=True;

                            end
                            else
                            begin


                                  VideoPrvHwnd[CardNo].Width :=PrvWidth;

                                  VideoPrvHwnd[CardNo].Height :=PrvHeight;                          //  定义窗体位置
                                  for i:=0 to m_nShowMode-1 do
                                  begin
                                        for j:=0 to m_nShowMode-1  do
                                        begin
                                          nIndex:=i*m_nShowMode+j;
                                          if  nIndex >= m_nWndNum then
                                          begin

                                                Exit;
                                          end;
                                         VideoPrvHwnd[nIndex].Left :=PrvWidth*j;
                                         VideoPrvHwnd[nIndex].Top :=PrvHeight  *i;

                                        end;
                                        for k:=0 to m_nWndNum-1 do
                                        begin

                                               VideoPrvHwnd[k].Visible:=true;
                                               Windows.GetClientRect(VideoPrvHwnd[k].Handle, DeviceInfo[k].dwPrvRect);

                                        end;
                                         if  CardNum>0 then
                                         begin
                                                for p:=0 to CardNum-1 do
                                                 begin

                                                             DxMediaFunction.StopPrview(DeviceInfo[p].dwChannelHandle);
                                                            DeviceInfo[CardNo].dwPrviewState:=DxMediaFunction.StartPrview(DeviceInfo[p].dwChannelHandle,
                                                                                           DeviceInfo[p].dwPrvHandle,
                                                                                           DeviceInfo[p].dwPrvRect,
                                                                                          dwPreviewMode);

                                                 end;

                                         end;



                                         DeviceInfo[0].dwMaxHwnd:=False;
                                   end;

                            end;


                        end;
                  end;
              end;
 end;

procedure TForm1.Button3Click(Sender: TObject);
var
    PicSaveFile:string;
    PicBuf:pchar ;
    RgbBuf:PChar;
    colorSpace:LongWord ;
    nWidth:LongWord ;
    nHeight:LongWord ;
    BufSize:LongWord;
    BytesWidth:LongWord ;
    gotBufferLen:LongWord ;



begin

        BufSize:=2048*1024*3;
        PicBuf:=AllocMem(BufSize);
        RgbBuf:=AllocMem(BufSize);
         //create the save picture file name
        // PicSaveFile:=CreateCaptureFile(CardNo,'.bmp',PicSavePath+'\');
        nWidth:=0;
        nHeight:=0;
        colorSpace:=0;
        BytesWidth:=0;
        gotBufferLen:=0;
         if(DeviceInfo[CardNo].dwConnectState=true) then
         begin
        //get the video device property
              DXGetVideoPara(DeviceInfo[CardNo].dwChannelHandle, DeviceInf.dwVidStandard,
                                               DeviceInf.dwColorspace,
                                               DeviceInf.dwCapWeight,
                                               DeviceInf.dwCapHeight,
                                               DeviceInf.dwFrameRate);

             SnapRect.Left :=0;
             SnapRect.Top :=0;
             SnapRect.Right :=DeviceInf.dwCapWeight;
             SnapRect.Bottom :=DeviceInf.dwCapHeight;

            //get the cur buf data
             DXGetFrameBuffer(DeviceInfo[CardNo].dwChannelHandle,PicBuf,BufSize,gotBufferLen, colorSpace,nWidth ,nHeight,BytesWidth,SnapRect );

             DXConvertYUVtoRGB(DeviceInfo[CardNo].dwChannelHandle,PicBuf,RgbBuf,nWidth, nHeight,True,false);
              PicSaveFile:=CreateCaptureFile(CardNo,'.bmp',PicSavePath+'\');
             CreateBmpFile(PAnsiChar(AnsiString(PicSaveFile)), RgbBuf,nWidth,nHeight);
             //save the buf to bmp file
          //  DXSaveBMPFile(PAnsiChar(AnsiString(PicSaveFile)),PicBuf,gotBufferLen, colorSpace ,nWidth ,nHeight ,BytesWidth);
             PicSaveFile:=CreateCaptureFile(CardNo,'.jpg',PicSavePath+'\');
               //save the buf to jpg file
            DXSaveJPGFile(PAnsiChar(AnsiString(PicSaveFile)),PicBuf,gotBufferLen, colorSpace ,nWidth ,nHeight ,BytesWidth,100);


            ShowMessage('snap ok:'+PicSaveFile);

        end;
       FreeMem(PicBuf,BufSize);
       FreeMem(RgbBuf,BufSize);

end;




procedure TForm1.Button5Click(Sender: TObject);
var i:LongWord;
begin
      if RawCallOk[CardNo]=0 then
      begin
             //stop the callback
            DXStopRawVideoCallback(DeviceInfo[CardNo].dwChannelHandle);
            FreeMem(pBufSnapPic,DeviceInf.dwCapWeight *  DeviceInf.dwCapHeight *2);
      end;
        if CardNum>0 then
        begin

                            for i:=0 to CardNum-1 do
                   begin

                          if DeviceInfo[i].dwPrviewState=True then
                          begin
                               DxMediaFunction.StopPrview(DeviceInfo[i].dwChannelHandle);

                          end;
                          if DeviceInfo[i].dwConnectState=True then
                          begin

                                DxMediaFunction.DisconnectDevice(DeviceInfo[i].dwChannelHandle);
                                DxMediaFunction.CloseDevice(DeviceInfo[i].dwChannelHandle);

                          end;


                   end;

                //uninit sdk resource
                DXUninitialize;

        end;

      //close the project
      Application.Terminate ;
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
var i:LongWord;
begin

      if RawCallOk[CardNo]=0 then
      begin

            DXStopRawVideoCallback(DeviceInfo[CardNo].dwChannelHandle);
            FreeMem(pBufSnapPic,DeviceInf.dwCapWeight *  DeviceInf.dwCapHeight *2);
      end;
       if CardNum>0 then
       begin
               for i:=0 to CardNum-1 do
               begin

                      if DeviceInfo[i].dwPrviewState=True then
                      begin
                           DxMediaFunction.StopPrview(DeviceInfo[i].dwChannelHandle);

                      end;
                      if DeviceInfo[i].dwConnectState=True then
                      begin

                            DxMediaFunction.DisconnectDevice(DeviceInfo[i].dwChannelHandle);
                            DxMediaFunction.CloseDevice(DeviceInfo[i].dwChannelHandle);

                      end;


               end;



            //uninit sdk resource
            DXUninitialize;


       end;


end;

procedure TForm1.btEnumVideoCodecClick(Sender: TObject);
begin
         EnumCodecFrm.Show ;
end;

procedure TForm1.btCaptureClick(Sender: TObject);
var VidSaveFile:string;
begin
        //得到视频设备的属性参数
              DXGetVideoPara(DeviceInfo[CardNo].dwChannelHandle, DeviceInf.dwVidStandard,
                                               DeviceInf.dwColorspace,
                                               DeviceInf.dwCapWeight,
                                               DeviceInf.dwCapHeight,
                                               DeviceInf.dwFrameRate);

          //create the save video file name
        VidSaveFile:=CreateCaptureFile(CardNo,'.avi',RecSavePath+'\');
        //指定编码格式
       // DeviceInfo[CardNo].dwVideoCodecStr:='Xvid MPEG-4 Codec';
           //DeviceInf.dwVideoCodecStr:='xvid Codec';

  if DeviceInfo[CardNo].dwConnectState=True  then
      begin
          if (DeviceInfo[CardNo].dwRecOK=false) then
          begin
              if DeviceInfo[CardNo].dwVideoCodecStr='x264 Codec' then
              begin
                           //set the h264 codec property
			      	DeviceInfo[CardNo].dwVideoCodecpara.Bitrate:= 0;  ////为0时候,编码器内部自己计算
			        DeviceInfo[CardNo].dwVideoCodecpara.fps :=trunc(DeviceInf.dwFrameRate);
				     DeviceInfo[CardNo].dwVideoCodecpara.keyframeinterval := 110;
				      DeviceInfo[CardNo].dwVideoCodecpara.rcMode := codec_VBR;
				     DeviceInfo[CardNo].dwVideoCodecpara.Quality := 9;
               DeviceInfo[CardNo].dwVideoCodecpara.Maxrbps:=4000;
                 DeviceInfo[CardNo].dwVideoCodecpara.Peekbps:=2000;
                //create the save video file name
             VidSaveFile:=CreateCaptureFile(CardNo,'.mp4',RecSavePath+'\');

              end;

               if DeviceInfo[CardNo].dwVideoCodecStr='xvid Codec' then
              begin
                          //set the xvid codec property
			      	DeviceInfo[CardNo].dwVideoCodecpara.Bitrate:= 2000;
			       DeviceInfo[CardNo].dwVideoCodecpara.fps :=trunc(DeviceInf.dwFrameRate);
				     DeviceInfo[CardNo].dwVideoCodecpara.keyframeinterval := 110;
				      DeviceInfo[CardNo].dwVideoCodecpara.rcMode := codec_VBR;
				      DeviceInfo[CardNo].dwVideoCodecpara.Quality := 4;
              VidSaveFile:=CreateCaptureFile(CardNo,'.avi',RecSavePath+'\');

              end;
               DxMediaFunction.StartRecord(DeviceInfo[CardNo].dwChannelHandle,
                                        VidSaveFile,
                                        DeviceInfo[CardNo].dwVideoCodecStr,
                                         DeviceInfo[CardNo].dwVideoCodecpara,
                                       false);
                                  DeviceInfo[CardNo].dwRecOK:=true;
                                 btCapture.Caption :='Stop Rec' ;
             end
              else
              begin
                                   DxMediaFunction.StopRecord(DeviceInfo[CardNo].dwChannelHandle);
                                   btCapture.Caption :='Record' ;
                                   DeviceInfo[CardNo].dwRecOK:=False;
                                   ShowMessage('record ok '+VidSaveFile);


              end;




      end;




      ////


end;

procedure TForm1.btFreezeCapClick(Sender: TObject);

begin
      if  DeviceInfo[CardNo].dwConnectState=True then
      begin
            if (DeviceInfo[CardNo].dwRecOK=True) and (DeviceInfo[CardNo].dwFreezeOK=False)  then
            begin
                   //pause the video recording
                   DeviceInfo[CardNo].dwFreezeOK:=DxMediaFunction.FreezeRecord(DeviceInfo[CardNo].dwChannelHandle,True);
                   btFreezeCap.Caption :='Stop Pause' ;
                    DeviceInfo[CardNo].dwFreezeOK:=true;
            end
            else
            begin
                    DxMediaFunction.FreezeRecord(DeviceInfo[CardNo].dwChannelHandle,False);
                     btFreezeCap.Caption :='Pause Rec';
                     DeviceInfo[CardNo].dwFreezeOK:=False  ;

            end;

      end;

end;

procedure TForm1.btSnapClick(Sender: TObject);
 var PicSaveFile:string ;
begin


        

        if  (DeviceInfo[CardNo].dwConnectState=True) then
        begin
              //get the video device property
              DxMediaFunction.GetVideoPara(DeviceInfo[CardNo].dwChannelHandle,
                                               DeviceInfo[CardNo].dwVidStandard,
                                               DeviceInfo[CardNo].dwColorspace,
                                               DeviceInfo[CardNo].dwCapWeight,
                                               DeviceInfo[CardNo].dwCapHeight,
                                               DeviceInfo[CardNo].dwFrameRate);

             SnapRect.Left :=0;
             SnapRect.Top :=0;
             SnapRect.Right :=DeviceInf.dwCapWeight;
             SnapRect.Bottom :=DeviceInf.dwCapHeight;

              //create the save picture file name
              PicSaveFile:=CreateCaptureFile(CardNo,'.bmp',PicSavePath+'\');
              DxMediaFunction.SnapPicture(DeviceInfo[CardNo].dwChannelHandle, PicSaveFile,0,SnapRect);


              PicSaveFile:=CreateCaptureFile(CardNo,'.jpg',PicSavePath+'\');
              DxMediaFunction.SnapPicture(DeviceInfo[CardNo].dwChannelHandle, PicSaveFile,1,SnapRect);
              ShowMessage('snap ok '+PicSaveFile);

        end;


end;

procedure TForm1.btSetOSDClick(Sender: TObject);
begin
      //show the osd setting from
      OsdSettingDlg.Show ;
end;

procedure TForm1.DeinterBlendClick(Sender: TObject);
begin
      DeinterBlend.Checked :=True;
      DeinterBob.Checked :=False ;
      DeinterLow.Checked :=False;
      DeinterCancel.Checked :=False ;
      //设置隔行算法为 Blend
      DXEnableDeinterlace(DeviceInfo[CardNo].dwChannelHandle,1);
end;

procedure TForm1.DeinterBobClick(Sender: TObject);
begin
      DeinterBlend.Checked :=False ;
      DeinterBob.Checked :=True  ;
       DeinterLow.Checked :=False;
      DeinterCancel.Checked :=False ;
      //设置隔行算法为 Bob

      DXEnableDeinterlace( DeviceInfo[CardNo].dwChannelHandle,2);
       
end;

procedure TForm1.DeinterweaveClick(Sender: TObject);
begin
      DeinterBlend.Checked :=False ;
      DeinterBob.Checked :=False ;

      DeinterCancel.Checked :=False ;
        //设置隔行算法为 weave
      DXEnableDeinterlace( DeviceInfo[CardNo].dwChannelHandle,3);
end;

procedure TForm1.DeinterCancelClick(Sender: TObject);
begin
      DeinterBlend.Checked :=False ;
      DeinterBob.Checked :=False ;

      DeinterCancel.Checked :=True  ;

      DeinterLow.Checked :=False;
    
      //不启用去隔行算法
      DXEnableDeinterlace( DeviceInfo[CardNo].dwChannelHandle,4);
end;

procedure TForm1.btEnableRawCallClick(Sender: TObject);
begin
      if( DeviceInfo[CardNo].dwConnectState=True) then
        begin

               
                     //预先分配回调数据内存空间
               pBufSnapPic :=  AllocMem(DeviceInfo[CardNo].dwCapWeight*DeviceInfo[CardNo].dwCapHeight*2 );
               PRgbBuf:=  AllocMem(DeviceInfo[CardNo].dwCapWeight*DeviceInfo[CardNo].dwCapHeight*3 );
               if  RawCallOk[CardNo]<>0 then
               begin
                        // 检测上下文传递通道号
                    RawCallOk[CardNo]:=DXStartRawVideoCallback( DeviceInfo[CardNo].dwChannelHandle,CallBackSnap,CardNo);


                    btEnableRawCall.Caption :='StopCallback'


               end
               else
               begin
                     DXStopRawVideoCallback(DeviceInfo[CardNo].dwChannelHandle);
                     btEnableRawCall.Caption :='StartCallback' ;
                     RawCallOk[CardNo]:=1;
                     FreeMem(pBufSnapPic,DeviceInf.dwCapWeight *  DeviceInf.dwCapHeight *2);
               end;

        end;



end;

procedure TForm1.D1MenuClick(Sender: TObject);
begin
      D1Menu.Checked :=True;
      CIFMenu.Checked :=False;
      Menu768.Checked :=False;
      if(DeviceInfo[CardNo].dwOpenDevState=0) then
      begin
                if  DeviceInfo[CardNo].dwVidStandard= $20 then
                begin
                       if (DeviceInfo[CardNo].dwCapWeight<>720) then
                       begin
                               if( DeviceInfo[CardNo].dwPrviewState=True) then
                               begin
                                       DxMediaFunction.StopPrview(DeviceInfo[CardNo].dwChannelHandle);

                               end;
                               if( DeviceInfo[CardNo].dwConnectState=True) then
                               begin
                                       DxMediaFunction.DisconnectDevice(DeviceInfo[CardNo].dwChannelHandle);

                               end;
                              DeviceInfo[CardNo].dwCapWeight:=720;
                              DeviceInfo[CardNo].dwCapHeight:=576;
                                SettingIni.WriteInteger('SystemSetting','VidWidth'+inttostr(CardNo), DeviceInfo[CardNo].dwCapWeight);
                              SettingIni.WriteInteger('SystemSetting','VidHeight'+inttostr(CardNo), DeviceInfo[CardNo].dwCapHeight);
                              DeviceInfo[CardNo].dwConnectState:=DxMediaFunction.ConnectDevice(DeviceInfo[CardNo].dwChannelHandle,
                                                                                DeviceInfo[CardNo].dwVidStandard,
                                                                                DeviceInfo[CardNo].dwColorspace,
                                                                                DeviceInfo[CardNo].dwCapWeight,
                                                                                DeviceInfo[CardNo].dwCapHeight,
                                                                                DeviceInfo[CardNo].dwFrameRate);

                                if(DeviceInfo[CardNo].dwConnectState=true) then
                                begin

                                        DeviceInfo[CardNo].dwPrviewState:=DxMediaFunction.StartPrview(DeviceInfo[CardNo].dwChannelHandle,
                                                                                               DeviceInfo[CardNo].dwPrvHandle,
                                                                                               DeviceInfo[CardNo].dwPrvRect,
                                                                                               dwPreviewMode);

                                end;


                       end;

                end
                else
                begin

                        if (DeviceInfo[CardNo].dwCapWeight<>720) then
                       begin
                               if( DeviceInfo[CardNo].dwPrviewState=True) then
                               begin
                                       DxMediaFunction.StopPrview(DeviceInfo[CardNo].dwChannelHandle);

                               end;
                               if( DeviceInfo[CardNo].dwConnectState=True) then
                               begin
                                       DxMediaFunction.DisconnectDevice(DeviceInfo[CardNo].dwChannelHandle);

                               end;
                              DeviceInfo[CardNo].dwCapWeight:=720;
                              DeviceInfo[CardNo].dwCapHeight:=480;
                              SettingIni.WriteInteger('SystemSetting','VidWidth'+inttostr(CardNo), DeviceInfo[CardNo].dwCapWeight);
                              SettingIni.WriteInteger('SystemSetting','VidHeight'+inttostr(CardNo), DeviceInfo[CardNo].dwCapHeight);
                              DeviceInfo[CardNo].dwConnectState:=DxMediaFunction.ConnectDevice(DeviceInfo[CardNo].dwChannelHandle,
                                                                                DeviceInfo[CardNo].dwVidStandard,
                                                                                DeviceInfo[CardNo].dwColorspace,
                                                                                DeviceInfo[CardNo].dwCapWeight,
                                                                                DeviceInfo[CardNo].dwCapHeight,
                                                                                DeviceInfo[CardNo].dwFrameRate);

                                if(DeviceInfo[CardNo].dwConnectState=true) then
                                begin

                                        DeviceInfo[CardNo].dwPrviewState:=DxMediaFunction.StartPrview(DeviceInfo[CardNo].dwChannelHandle,
                                                                                               DeviceInfo[CardNo].dwPrvHandle,
                                                                                               DeviceInfo[CardNo].dwPrvRect,
                                                                                               dwPreviewMode);

                                end;


                       end;
                end;



      end;



end;

procedure TForm1.CIFMenuClick(Sender: TObject);
begin
       D1Menu.Checked :=False ;
      CIFMenu.Checked :=True ;
         Menu768.Checked :=False;
     if(DeviceInfo[CardNo].dwOpenDevState=0) then
      begin
                if  DeviceInfo[CardNo].dwVidStandard= $20 then
                begin
                       if (DeviceInfo[CardNo].dwCapWeight<>352) then
                       begin
                               if( DeviceInfo[CardNo].dwPrviewState=True) then
                               begin
                                       DxMediaFunction.StopPrview(DeviceInfo[CardNo].dwChannelHandle);

                               end;
                               if( DeviceInfo[CardNo].dwConnectState=True) then
                               begin
                                       DxMediaFunction.DisconnectDevice(DeviceInfo[CardNo].dwChannelHandle);

                               end;
                              DeviceInfo[CardNo].dwCapWeight:=352;
                              DeviceInfo[CardNo].dwCapHeight:=288;
                              SettingIni.WriteInteger('SystemSetting','VidWidth'+inttostr(CardNo), DeviceInfo[CardNo].dwCapWeight);
                              SettingIni.WriteInteger('SystemSetting','VidHeight'+inttostr(CardNo),DeviceInfo[CardNo].dwCapHeight);
                              DeviceInfo[CardNo].dwConnectState:=DxMediaFunction.ConnectDevice(DeviceInfo[CardNo].dwChannelHandle,
                                                                                DeviceInfo[CardNo].dwVidStandard,
                                                                                DeviceInfo[CardNo].dwColorspace,
                                                                                DeviceInfo[CardNo].dwCapWeight,
                                                                                DeviceInfo[CardNo].dwCapHeight,
                                                                                DeviceInfo[CardNo].dwFrameRate);

                                if(DeviceInfo[CardNo].dwConnectState=true) then
                                begin

                                        DeviceInfo[CardNo].dwPrviewState:=DxMediaFunction.StartPrview(DeviceInfo[CardNo].dwChannelHandle,
                                                                                               DeviceInfo[CardNo].dwPrvHandle,
                                                                                               DeviceInfo[CardNo].dwPrvRect,
                                                                                               dwPreviewMode);

                                end;


                       end;

                end;

      end;

end;

procedure TForm1.btCallBackSnapClick(Sender: TObject);
begin
       if  RawCallOk[CardNo]<>0 then
       begin
              ShowMessage('Please start the raw callback');

       end
       else
       begin

               if CallSnapOk=false then
               begin
                     CallSnapOk:=true;
                     PicFileName:=CreateCaptureFile(CardNo,'.bmp',PicSavePath+'\');

               end;

       end;

end;

procedure TForm1.VideoFlipMenuClick(Sender: TObject);
begin
       if ImageFlip =False then
       begin
             VideoFlipMenu.Checked :=True ;
             DXFlipVideo( DeviceInfo[CardNo].dwChannelHandle,True);
             ImageFlip:=True ;
       end
       else
       begin

             VideoFlipMenu.Checked :=false ;
             DXFlipVideo( DeviceInfo[CardNo].dwChannelHandle,false);
             ImageFlip:=false ;
       end;

  end;

procedure TForm1.VideoMirrMenuClick(Sender: TObject);
begin
          if ImageMirr =False  then
          begin
                VideoMirrMenu.Checked :=True;
               DXMirrorVideo( DeviceInfo[CardNo].dwChannelHandle,True);
               ImageMirr:=True;


          end
          else
          begin
                 VideoMirrMenu.Checked :=False ;
                 DXMirrorVideo( DeviceInfo[CardNo].dwChannelHandle,False );
                ImageMirr:=False ;
          end;

end;

procedure TForm1.DevProptyMenuClick(Sender: TObject);
begin
        OKBottomDlg.Show ;
end;

procedure TForm1.btSnapPreviewClick(Sender: TObject);
begin

      DlgPrvHwnd.Show ;
    //  DXUpdateImg(PrvImageHandle, DlgPrvHwnd.panel1.Handle , PrvRect);

end;

procedure TForm1.N1Click(Sender: TObject);
begin
       ColorProperty.show;
end;

procedure TForm1.NtscMenuClick(Sender: TObject);
begin

          PalMenu.Checked :=true;
          NtscMenu .Checked :=false;
      if (DeviceInfo[CardNo].dwConnectState=true) then
      begin
                    PalMenu.Checked :=false;
                    NtscMenu .Checked :=true;
                    if (DeviceInfo[CardNo].dwVidStandard<>$1) then
                    begin

                            if( DeviceInfo[CardNo].dwPrviewState=True) then
                               begin
                                       DxMediaFunction.StopPrview(DeviceInfo[CardNo].dwChannelHandle);

                               end;
                               if( DeviceInfo[CardNo].dwConnectState=True) then
                               begin
                                       DxMediaFunction.DisconnectDevice(DeviceInfo[CardNo].dwChannelHandle);

                               end;

                              if( DeviceInfo[CardNo].dwCapHeight>480) then
                                   DeviceInfo[CardNo].dwCapHeight:=480;
                              DeviceInfo[CardNo].dwFrameRate:=30;
                                DeviceInfo[CardNo].dwVidStandard:= $1;

                                  //write the video property value to ini file
                               SettingIni.WriteInteger('SystemSetting','VidWidth'+inttostr(CardNo), DeviceInfo[CardNo].dwCapWeight);
                              SettingIni.WriteInteger('SystemSetting','VidHeight'+inttostr(CardNo), DeviceInfo[CardNo].dwCapHeight);
                              SettingIni.WriteInteger('SystemSetting','FrameRate'+inttostr(CardNo), round (DeviceInfo[CardNo].dwFrameRate));
                              SettingIni.WriteInteger('SystemSetting','VidStandard'+inttostr(CardNo), DeviceInfo[CardNo].dwVidStandard);

                              DeviceInfo[CardNo].dwConnectState:=DxMediaFunction.ConnectDevice(DeviceInfo[CardNo].dwChannelHandle,
                                                                                DeviceInfo[CardNo].dwVidStandard,
                                                                                DeviceInfo[CardNo].dwColorspace,
                                                                                DeviceInfo[CardNo].dwCapWeight,
                                                                                DeviceInfo[CardNo].dwCapHeight,
                                                                                DeviceInfo[CardNo].dwFrameRate);

                                if(DeviceInfo[CardNo].dwConnectState=true) then
                                begin

                                        DeviceInfo[CardNo].dwPrviewState:=DxMediaFunction.StartPrview(DeviceInfo[CardNo].dwChannelHandle,
                                                                                               DeviceInfo[CardNo].dwPrvHandle,
                                                                                               DeviceInfo[CardNo].dwPrvRect,
                                                                                              dwPreviewMode);

                                end;



                    end;

      end;
end;

procedure TForm1.PalMenuClick(Sender: TObject);
begin
       if (DeviceInfo[CardNo].dwVidStandard<>$20) then
                    begin

                            if( DeviceInfo[CardNo].dwPrviewState=True) then
                               begin
                                       DxMediaFunction.StopPrview(DeviceInfo[CardNo].dwChannelHandle);

                               end;
                               if( DeviceInfo[CardNo].dwConnectState=True) then
                               begin
                                       DxMediaFunction.DisconnectDevice(DeviceInfo[CardNo].dwChannelHandle);

                               end;
                               DeviceInfo[CardNo].dwFrameRate:=25;
                                DeviceInfo[CardNo].dwVidStandard:= $20;
                              SettingIni.WriteInteger('SystemSetting','FrameRate'+inttostr(CardNo), round (DeviceInfo[CardNo].dwFrameRate));
                              SettingIni.WriteInteger('SystemSetting','VidStandard'+inttostr(CardNo), DeviceInfo[CardNo].dwVidStandard);

                              DeviceInfo[CardNo].dwConnectState:=DxMediaFunction.ConnectDevice(DeviceInfo[CardNo].dwChannelHandle,
                                                                                DeviceInfo[CardNo].dwVidStandard,
                                                                                DeviceInfo[CardNo].dwColorspace,
                                                                                DeviceInfo[CardNo].dwCapWeight,
                                                                                DeviceInfo[CardNo].dwCapHeight,
                                                                                DeviceInfo[CardNo].dwFrameRate);

                                if(DeviceInfo[CardNo].dwConnectState=true) then
                                begin

                                        DeviceInfo[CardNo].dwPrviewState:=DxMediaFunction.StartPrview(DeviceInfo[CardNo].dwChannelHandle,
                                                                                               DeviceInfo[CardNo].dwPrvHandle,
                                                                                               DeviceInfo[CardNo].dwPrvRect,
                                                                                               dwPreviewMode);

                                end;



                    end;


end;

procedure TForm1.SVIDEOMenuClick(Sender: TObject);
begin
       if( DeviceInfo[CardNo].dwConnectState=True) then
      begin
              DXSetVideoSource(DeviceInfo[CardNo].dwChannelHandle,3);
              SVIDEOMenu.Checked :=True;
              av2Menu.Checked :=False ;
              AV1Menu.Checked :=False;

      end;
end;







procedure TForm1.AV1MenuClick(Sender: TObject);
begin
    if( DeviceInfo[CardNo].dwConnectState=True) then
      begin
              DXSetVideoSource(DeviceInfo[CardNo].dwChannelHandle,1);
              SVIDEOMenu.Checked :=false;
              av2Menu.Checked :=False ;
              AV1Menu.Checked :=true;

      end;

end;

procedure TForm1.av2MenuClick(Sender: TObject);
begin
    if( DeviceInfo[CardNo].dwConnectState=True) then
      begin
              DXSetVideoSource(DeviceInfo[CardNo].dwChannelHandle,2);
              SVIDEOMenu.Checked :=false;
              av2Menu.Checked :=true ;
              AV1Menu.Checked :=False;

      end;
end;

procedure TForm1.VideoDevMenuClick(Sender: TObject);
begin
          VideoDeviceFrm.show;
end;

procedure TForm1.DenoiseMenuClick(Sender: TObject);
begin
        VideoDenoiseSet.show;
end;

procedure TForm1.CheckBox1Click(Sender: TObject);
begin
          if CheckBox1.Checked =true then
          begin
                    timer1.Enabled :=true;
                    timer1.Interval :=20000;
          end
          else
          begin
                 timer1.Enabled :=false;
          end;

end;

procedure TForm1.Timer1Timer(Sender: TObject);
var PicSaveFile:string;
begin
       
      if  ConnectOk[CardNo]=0 then
        begin
              //得到视频设备的属性参数
              DXGetVideoPara(DeviceInfo[CardNo].dwChannelHandle, DeviceInf.dwVidStandard,
                                               DeviceInf.dwColorspace,
                                               DeviceInf.dwCapWeight,
                                               DeviceInf.dwCapHeight,
                                               DeviceInf.dwFrameRate);

             SnapRect.Left :=0;
             SnapRect.Top :=0;
             SnapRect.Right :=DeviceInf.dwCapWeight;
             SnapRect.Bottom :=DeviceInf.dwCapHeight;

             PicSaveFile:=CreateCaptureFile(CardNo,'.jpg','d:\pic2000\');
                  //snap the picture
              DXSnapToJPGFile(DeviceInfo[CardNo].dwChannelHandle,PAnsiChar(AnsiString(PicSaveFile)),100,SnapRect);


        end;
end;

procedure TForm1.Imageenhancement1Click(Sender: TObject);
begin
       ImagealgorithmFrm.Show ;
end;

procedure TForm1.Menu768Click(Sender: TObject);
begin
       D1Menu.Checked :=false;
      CIFMenu.Checked :=False;
      Menu768.Checked :=true;
      if(DeviceInfo[CardNo].dwOpenDevState=0) then
      begin
                if  DeviceInfo[CardNo].dwVidStandard= $20 then
                begin
                       if (DeviceInfo[CardNo].dwCapWeight<>768) then
                       begin
                               if( DeviceInfo[CardNo].dwPrviewState=True) then
                               begin
                                       DxMediaFunction.StopPrview(DeviceInfo[CardNo].dwChannelHandle);

                               end;
                               if( DeviceInfo[CardNo].dwConnectState=True) then
                               begin
                                       DxMediaFunction.DisconnectDevice(DeviceInfo[CardNo].dwChannelHandle);

                               end;
                              DeviceInfo[CardNo].dwCapWeight:=768;
                              DeviceInfo[CardNo].dwCapHeight:=576;
                              SettingIni.WriteInteger('SystemSetting','VidWidth'+inttostr(CardNo), DeviceInfo[CardNo].dwCapWeight);
                              SettingIni.WriteInteger('SystemSetting','VidHeight'+inttostr(CardNo), DeviceInfo[CardNo].dwCapHeight);

                              DeviceInfo[CardNo].dwConnectState:=DxMediaFunction.ConnectDevice(DeviceInfo[CardNo].dwChannelHandle,
                                                                                DeviceInfo[CardNo].dwVidStandard,
                                                                                DeviceInfo[CardNo].dwColorspace,
                                                                                DeviceInfo[CardNo].dwCapWeight,
                                                                                DeviceInfo[CardNo].dwCapHeight,
                                                                                DeviceInfo[CardNo].dwFrameRate);

                                if(DeviceInfo[CardNo].dwConnectState=true) then
                                begin

                                        DeviceInfo[CardNo].dwPrviewState:=DxMediaFunction.StartPrview(DeviceInfo[CardNo].dwChannelHandle,
                                                                                               DeviceInfo[CardNo].dwPrvHandle,
                                                                                               DeviceInfo[CardNo].dwPrvRect,
                                                                                               dwPreviewMode);

                                end;


                       end;

                end
                else
                begin

                        if (DeviceInfo[CardNo].dwCapWeight<>768) then
                       begin
                               if( DeviceInfo[CardNo].dwPrviewState=True) then
                               begin
                                       DxMediaFunction.StopPrview(DeviceInfo[CardNo].dwChannelHandle);

                               end;
                               if( DeviceInfo[CardNo].dwConnectState=True) then
                               begin
                                       DxMediaFunction.DisconnectDevice(DeviceInfo[CardNo].dwChannelHandle);

                               end;
                              DeviceInfo[CardNo].dwCapWeight:=768;
                              DeviceInfo[CardNo].dwCapHeight:=480;
                                SettingIni.WriteInteger('SystemSetting','VidWidth'+inttostr(CardNo), DeviceInfo[CardNo].dwCapWeight);
                              SettingIni.WriteInteger('SystemSetting','VidHeight'+inttostr(CardNo), DeviceInfo[CardNo].dwCapHeight);
                              DeviceInfo[CardNo].dwConnectState:=DxMediaFunction.ConnectDevice(DeviceInfo[CardNo].dwChannelHandle,
                                                                                DeviceInfo[CardNo].dwVidStandard,
                                                                                DeviceInfo[CardNo].dwColorspace,
                                                                                DeviceInfo[CardNo].dwCapWeight,
                                                                                DeviceInfo[CardNo].dwCapHeight,
                                                                                DeviceInfo[CardNo].dwFrameRate);

                                if(DeviceInfo[CardNo].dwConnectState=true) then
                                begin

                                        DeviceInfo[CardNo].dwPrviewState:=DxMediaFunction.StartPrview(DeviceInfo[CardNo].dwChannelHandle,
                                                                                               DeviceInfo[CardNo].dwPrvHandle,
                                                                                               DeviceInfo[CardNo].dwPrvRect,
                                                                                               dwPreviewMode);

                                end;


                       end;
                end;



      end;

end;

procedure TForm1.DeinterLowClick(Sender: TObject);
begin
    DXEnableDeinterlace(DeviceInfo[CardNo].dwChannelHandle,0);
      DeinterBlend.Checked :=False ;
      DeinterBob.Checked :=False ;
      DeinterLow.Checked :=True;
      DeinterCancel.Checked :=False ;
end;

procedure TForm1.VMR7ModeClick(Sender: TObject);
begin
         SettingIni.WriteString('SystemSetting','PreviewMode', 'VMR7');

end;

procedure TForm1.OffScreamModeClick(Sender: TObject);
begin
        SettingIni.WriteString('SystemSetting','PreviewMode', 'OffScream');

end;

procedure TForm1.VMR9ModeClick(Sender: TObject);
begin
       SettingIni.WriteString('SystemSetting','PreviewMode', 'VMR9');

end;

procedure TForm1.btZoomClick(Sender: TObject);
begin
       DlgZoom.Show ;
end;

end.

