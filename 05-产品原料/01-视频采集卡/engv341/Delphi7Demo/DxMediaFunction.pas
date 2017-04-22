unit DxMediaFunction;

interface
uses Windows,Messages, SysUtils,Variants, Classes, Graphics, Controls,
     StdCtrls, ExtCtrls,IniFiles,DxMediaApi,GlobalVar;

   var
      DeviceInf:Device_Info;
      
     //定义视频属性值及默认值全局变量
   BrightValue:integer;
   ContrastValue:integer;
   HueValue:integer;
   StaturationValue:integer;
   SharpValue:integer;
   NoiseValue:integer;
   BrightDefault :LongWord;
   HueDefault:LongWord;
   ContrastDefault:LongWord;
   SaturationDefault :LongWord;
   ShappnessDefault :LongWord;
   NoiseDefault:LongWord;
    //
   IniName:string;
   SettingIni:Tinifile;



   BmpHeader:  TBitmapFileHeader;
   Bmpinfo:   TBitmapInfo;
   buf: pointer;
   Bmp:TBitmap;
   BmpFileName:string;
   nWidth:longword;
   nHeight:longword;
   framerate :longword;
   colorspace:LongWord;
   VidStandard:LongWord ;
   RgbBuff:pointer;


  DrawHwnd:HWND;
  DRect:TRECT;
  DrawCanvas:TCanvas;

  OpenDevState:array[0..23] of LongWord ;

  



   SnapRect:TRect ;
   CardNo:LongWord ;
 
   /////////////////////////////////////////////////////////////////////////////////////////////////
   //
   //
   ///////////////////////////////////////////////////////////////////////////////////////////////////
   function InitDevice():longword;
procedure UnInitDevice();
function OpenDevice(nCard:LongWord; OpenState:LongWord):THandle;
function CloseDevice(ChannelHandle:THandle):Boolean;
function ConnectDevice(ChannelHandle:THandle;
                      VideoStandard:LongWord;
                      ColorSpace:LongWord;
                      nWidth:LongWord;
                      nHeight:LongWord;
                      framerate:Single):Boolean;
function DisconnectDevice(ChannelHandle:THandle):Boolean;
function SetVideoSource(ChannelHandle:THandle;VidSource:LongWord):Boolean;
function StartPrview(ChannelHandle:THandle;PrvHwnd:Thandle; PreviewRect:TRect;PrvModel:LongWord ):Boolean;
function  StopPrview(ChannelHandle:THandle):Boolean;
function FreezePreview (ChannelHandle:THandle;bFreeze:Boolean):Boolean;
function GetVideoPara(ChannelHandle:THandle;
                      VideoStandard:LongWord;
                      ColorSpace:LongWord;
                      nWidth:LongWord;
                      nHeight:LongWord;
                      framerate:Single):Boolean;

function SnapPicture(ChannelHandle:THandle;szFileName:string;PictureType:LongWord;SnapRect:TRect):Boolean;
 function StartRecord( ChannelHandle:THandle;szFileName:string;CodecName:string;H264CodecPara:TVidCodecX264Para;AudioRec:boolean):Boolean;
function StopRecord(ChannelHandle:THandle):Boolean;
function FreezeRecord(ChannelHandle:THandle;Enable:Boolean):Boolean;
function CreateIniFile(IniName:string):longword;
function CreateCaptureFile(nCard:longword;FileType:string;PicSavePath:string):string;
function CreateBmpFile(BmpFileName:string;RgbBuff:pointer;nWidth:longword;nHeight:longword):longword;
procedure DrawRect(DrawHwnd:HWND; DRect:TRECT;DrawColor:Tcolor);




  
implementation

    function InitDevice():longword;
    var CardNum:LongWord;
    begin
          DXInitialize;
          CardNum:=DXGetDeviceCount;
          result:= CardNum;
    end;

    procedure UnInitDevice();
    begin
          DXUninitialize();
    end;

    function OpenDevice(nCard:LongWord; OpenState:LongWord):THandle;
    var DeviceHandle:THandle;
    begin

        DeviceHandle:=DXOpenDevice(nCard, OpenState);
        result:=DeviceHandle;

    end;

    function CloseDevice(ChannelHandle:THandle):Boolean;

    begin

         if (DXCloseDevice(ChannelHandle)=0) then
          begin
                 result:=True;
          end
          else
          begin

                result:=False;

          end;

    end;

    function ConnectDevice(ChannelHandle:THandle;
                        VideoStandard:LongWord;
                        ColorSpace:LongWord;
                        nWidth:LongWord;
                        nHeight:LongWord;
                        framerate:Single):Boolean;
    begin
              DXSetVideoPara( ChannelHandle,VideoStandard ,ColorSpace, nWidth,nHeight, framerate);
              if (DXDeviceRun(ChannelHandle)=0) then
                begin
                       result:=True;
                end
                else
                begin

                      result:=False;

                end;


    end;

    function DisconnectDevice(ChannelHandle:THandle):Boolean;
    begin
          DXStopPreview(ChannelHandle);
          if(DXDeviceStop(ChannelHandle)=0) then
          begin
               result:=True;
          end
          else
          begin

              result:=False;

          end;
    end;

    function SetVideoSource(ChannelHandle:THandle;VidSource:LongWord):Boolean;
    begin
          

               if (DXSetVideoSource(ChannelHandle,VidSource)=0) then
            begin
                 result:=True;
            end
            else
            begin

                result:=False;

            end;

    end;

    function StartPrview(ChannelHandle:THandle;PrvHwnd:Thandle; PreviewRect:TRect;PrvModel:LongWord ):Boolean;
    begin
            if (DXStartPreview( ChannelHandle, PrvHwnd, PreviewRect,PrvModel)=0) then
            begin
                 result:=True;
            end
            else
            begin

                result:=False;

            end;

    end;

    function  StopPrview(ChannelHandle:THandle):Boolean;
    begin
          if( DXStopPreview(ChannelHandle)=0 ) then
          begin
                 result:=True;

          end
          else

          begin

               result:=False;
          end;

    end;

    function FreezePreview (ChannelHandle:THandle;bFreeze:Boolean):Boolean;
    begin
          if( DXFreezePreview(ChannelHandle,bFreeze)=0 ) then
          begin
                 result:=True;

          end
          else

          begin

               result:=False;
          end;

    end;

    function GetVideoPara(ChannelHandle:THandle;
                          VideoStandard:LongWord;
                          ColorSpace:LongWord;
                          nWidth:LongWord;
                          nHeight:LongWord;
                          framerate:Single):Boolean;
    begin

            DXGetVideoPara(ChannelHandle,VideoStandard,ColorSpace,nWidth, nHeight,framerate);
            result:=True;

    end;

  //get the device signal state
  function GetSignalPresent(ChannelHandle:THandle;signal:LongWord):Boolean;
  begin
          DXGetSignalPresent(ChannelHandle,signal);
          result:=True;


  end;

  function SnapPicture(ChannelHandle:THandle;szFileName:string;PictureType:LongWord;SnapRect:TRect):Boolean;
  var ok :LongWord  ;
  begin
      ok:=1;
      if ( PictureType=0) then
      begin
            ok:=DXSnapToBMPFile(ChannelHandle,PAnsiChar(AnsiString(szFileName)),SnapRect);
      end
      else
      begin

             ok:=DXSnapToJPGFile(ChannelHandle,PAnsiChar(AnsiString(szFileName)),100,SnapRect);
      end;

       if(ok=0) then
          begin
                 result:=True;

          end
          else

          begin

               result:=False;
          end;


  end;

 function StartRecord( ChannelHandle:THandle;szFileName:string;CodecName:string;H264CodecPara:TVidCodecX264Para;AudioRec:boolean):Boolean;
  var  VideoCodec:array [0..126]of TDEVICE_TAG;
      CodecNum:LongWord;
      CurCodec:LongWord;
      AudioCodec:array [0..126]of TDEVICE_TAG;
      AuCodecNum:LongWord;
      AuCurCodec:LongWord;

      i:LongWord;
  begin
          CodecNum:=126;
          CurCodec:=0;
           AuCodecNum:=126;
           AuCurCodec:=0;
          DXEnumVideoCodecs(VideoCodec[0],CodecNum);
          DXEnumAudioCodecs(AudioCodec[0],AuCodecNum);
          //指定video codec
          for  i:=0 to CodecNum -1 do
          begin
                if AnsiCompareText(VideoCodec[i].cfFaceName,CodecName)=0 then
                 begin

                        CurCodec:=i;
                       break;
                 end;

          end;
           //指定 audio codec
           for  i:=0 to AuCodecNum -1 do
          begin
                if AnsiCompareText(AudioCodec[i].cfFaceName,'Microsoft ADPCM')=0 then
                 begin

                        AuCurCodec:=i;
                         break;
                 end;

          end;
          DXSetVideoCodec(ChannelHandle,VideoCodec[CurCodec]);
          if AudioRec=true then
          begin

                DXSetAudioCodec(ChannelHandle, AudioCodec[AuCurCodec]);
          end;

          // set h264 codec parameter
          if( AnsiCompareText('x264 Codec',CodecName)=0 )then
          begin
                DXSetVideoCodecPara(ChannelHandle, codec_x264, H264CodecPara);

          end;
               // set xvid codec parameter
           if( AnsiCompareText('xvid Codec',CodecName)=0 )then
          begin
                DXSetVideoCodecPara(ChannelHandle, codec_xvid, H264CodecPara);

          end;
         if( DXStartCapture(ChannelHandle,PAnsiChar(AnsiString(szFileName)),AudioRec ,nil ,nil,nil,1)=0) then
           begin
                 result:=True;

          end
          else

          begin

               result:=False;
          end;


  end;
  function StopRecord(ChannelHandle:THandle):Boolean;
  begin
         if(DXStopCapture(ChannelHandle)=0) then
         begin
                 result:=True;

          end
          else

          begin

               result:=False;
          end;

  end;

  function FreezeRecord(ChannelHandle:THandle;Enable:Boolean):Boolean;
  begin
          if(DXFreezeCaputre(ChannelHandle,Enable)=0) then
         begin
                 result:=True;

          end
          else

          begin

               result:=False;
          end;

  end;

  function EnableDeinterlace(ChannelHandle:THandle;DeintType:LongWord;enable:Boolean ):Boolean;
  begin

          DXEnableDeinterlace(ChannelHandle,DeintType);
          if(enable=False) then
          begin

                  DXEnableDeinterlace(ChannelHandle,4);
          end;

  end;

  //////////////////////////////////////////////////////////////////////////////////////////////



     // 创建ini函数
     function CreateIniFile(IniName:string):longword;
     var Filename:string;
     begin
          Filename:=ExtractFilePath(Paramstr(0))+IniName;
          SettingIni:=Tinifile.Create(filename);
          result:= 0;
     end;
     //创建存储文件名
     function CreateCaptureFile(nCard:longword;FileType:string;PicSavePath:string):string;
      var Cur:TDateTime;
           PicSaveFile:string ;
      begin
               //得到当前系统时间
        Cur:=Now();
        //设置时间日期显示格式
        ShortDateFormat := 'yyyymmdd-hhnnss';
        PicSaveFile := PicSavePath + DateToStr(Cur)+' Cam'+IntToStr(nCard)+FileType;
        result:= PicSaveFile;

      end;
     //画矩形框
     procedure DrawRect(DrawHwnd:HWND; DRect:TRECT;DrawColor:Tcolor);
     begin
      DrawCanvas:=TCanvas.Create ;
      DrawCanvas.Handle :=GetDC(DrawHwnd);
      DrawCanvas.brush.Style :=bsclear;
      DrawCanvas.Pen.Color :=DrawColor;
      DrawCanvas.Pen.Mode :=pmNotXor;
      DrawCanvas.Pen.Width :=2;
      DrawCanvas.Rectangle(DRect);
     end;
     //创建BMP文件
     function CreateBmpFile(BmpFileName:string;RgbBuff:pointer;nWidth:longword;nHeight:longword):longword;
     begin
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
             Move(RgbBuff^, buf^, Bmpinfo.bmiHeader.biSizeImage);
             Bmp.SaveToFile(BmpFileName);
             result:= 0;
     end;






end.
