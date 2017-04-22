////////////////////////////////////////////////////////////////////////////////////////////
//     (Copyright (C) 2011                                                               ///
//     All rights reserved.                                                              ///
//          %version: 1 %                                                                ///
//                                                                                       ///
// Last Update  : %date_modified: tony yu  2014 %   qq:67505494  e-mail:yyhnet@163.com   ///
//                                                                                       ///
// Description: DXMediaCap delphi7 api                                                     ///
///                                                                                      ///
////////////////////////////////////////////////////////////////////////////////////////////

unit DxMediaApi;

interface
uses
 Windows;
const
  DLL_DxMediaApi= 'DXMediaCap.dll';

type
    TNotifyEvent   =   procedure(Sender:   TObject)   of   object;

  TRETERRNO=
  (
	  RET_NOERROR	= 0,		//* no error */
	  RET_EXCEPTION,			//* sdk exception error */
	  RET_ERR_INIT,			//* do not initialize or initialize failed */
	  RET_INVALID_DEV,		//* do not find valid media device */
    RET_INVALID_CHANNEL,	//* invalid channel */
	  RET_BAD_POINTER,		//* invalid or Null pointer param */
	  RET_NO_MATCH,			//* do not match the compatiple object  */
	  RET_DX_FAILED,			//* fail from direct show */
	  RET_INVALID_HANDLE,		//* find null handle */
	  RET_INVALID_PARAM,		//* invalid function param */
	  RET_GDI_ERROR,			//* GDI error */
	  RET_IO_ERROR,			//* common io read or write error */
	  RET_FAILED,				//* common error */
	  RET_VIDFMT_ERROR		//* Video format selected do not support */
   );
         AnalogVideoStandard=
   (
    AnalogVideo_None       = $0,
    AnalogVideo_NTSC_M     = $1,
    AnalogVideo_NTSC_M_J   = $2,
    AnalogVideo_NTSC_433   = $4,
    AnalogVideo_PAL_B      = $10,
    AnalogVideo_PAL_D      = $20,
    AnalogVideo_PAL_H      = $80,
    AnalogVideo_PAL_I      = $100,
    AnalogVideo_PAL_M      = $200,
    AnalogVideo_PAL_N      = $400,
    AnalogVideo_PAL_60     = $800,
    AnalogVideo_SECAM_B    = $1000,
    AnalogVideo_SECAM_D    = $2000,
    AnalogVideo_SECAM_G    = $4000,
    AnalogVideo_SECAM_H    = $8000,
    AnalogVideo_SECAM_K    = $10000,
    AnalogVideo_SECAM_K1   = $20000,
    AnalogVideo_SECAM_L    = $40000,
    AnalogVideo_SECAM_L1   = $80000,
    AnalogVideo_PAL_N_COMBO = $100000
);


   TVideoProCamp_t=
   (
    VIDEOPROCAMP_BRIGHTNESS,            //
    VIDEOPROCAMP_CONTRAST,              //
    VIDEOPROCAMP_HUE,                   //
    VIDEOPROCAMP_SATURATION,            //
    VIDEOPROCAMP_SHARPNESS,             //
    VIDEOPROCAMP_GAMMA,                 //
    VIDEOPROCAMP_COLORENABLE,           //
    VIDEOPROCAMP_WHITEBALANCE,          //
    VIDEOPROCAMP_BACKLIGHT_COMPENSATION,// 
    VIDEOPROCAMP_GAIN                  //
    );
   //video original stream type
   TVideoOutputFormat_t=
   (
     UYVY = 0,                   //@enum BO_1234 - YUV422
     YUY2 = 1,                  //@enum BO_2143 - YUV422
     YV12 = 2,
     RGB24 = 3                 //@enum BO_1234 - RGB24
   );
   TosdType=
   (
     osd_text,
     osd_time,
     osd_image

   );



   THDVideoSource=
  (
    YpbprInput = 0,            //@enum input is CVBS channel 1
    HdmiInput  =1                //@enum input is CVBS channel 2

  );

  //video input port
  TVideoSource_t=
  (
    COMPOSITE_1 = 0,            //@enum input is CVBS channel 1
    COMPOSITE_2  =1,                //@enum input is CVBS channel 2
    S_VIDEO_1    =2,                  //@enum input is S-Video channel 1
    S_VIDEO_2    =3
  );
  //video standard
  TVideoStandard_t=
  (
    PAL = 0,                //@enum normal PAL standard
    NTSC = 1,               //@enum normal NTSC standard
    AUTOSTD = 2,             //@enum autodetect standard
    NO_COLOR_50HZ = 3      //@enum no color (black/white) in Auto mode
  );

 //video field type
 TStreamFlagsVideo_t=
 (
    hnOddField = 0,
    hnEvenField ,
    hnInterlaced
 );

 TBitrateControlType_t=
 (
	BITRATETYPE_CBR = 0,
	BITRATETYPE_VBR = 1
 );

 TImage_t =
 (
    IMAGE_BMP,
    IMAGE_JPG
 );


  TDEVICE_TAG = record
    idx:LongWord    ;
    cfFaceName:array[0..127] of AnsiChar ;
  end;
  PDEVICE_TAG=^TDEVICE_TAG;
   PRect=^ TRect ;


   TDRateColor_Para =record
     nBrightness:LongWord; // 亮度增强，取值(-255到255)
    	nContrast:LongWord ;  //对比度增强，取值(-100到100)
    end;


    ///add h264


TRcmode=
(
    codec_CBR=0,
    codec_VBR

) ;
 TcodecType=
 (
   codec_sys,
   codec_x264 ,
   codec_xvid
 );

TVidCodecSysPara=record
	 bitrate:Integer; // 码率（单位：kbps）
   keyinterval:Integer;  //关键帧间隔
end;

TVidCodecX264Para=record
      fps:Integer;
      keyframeinterval:Integer;
      rcMode:TRcmode;   //码率控制,x264_cqp(恒定质量), x264_crf(恒定码率), x264_abr(平均码率)
      Quality:Integer;
      Bitrate :Integer;
      Maxrbps:integer;
      Peekbps:integer;
 end;



   //自定义设备信息结构
Device_Info= Record
            dwCardNo:LongWord;
            dwChannelHandle:THandle;
            dwPrvHandle:THandle;
            dwPrvRect:TRect;
            dwSnapPicRect:TRect;
            dwZoomRect:TRect;
            dwCapHeight:Longword;//DWORD
            dwCapWeight:Longword;//DWORD
            dwFrameRate:Single;//DWORD
            dwColorspace:LongWord;
            dwVidStandard:LongWord ;
            dwOpenDevState:LongWord;
            dwConnectState:Boolean;
            dwPrviewState:Boolean;
            dwSharpness:Longword;  //DWORD
            dwSaturation:Longword; //DWORD
            dwHue:Longword; //DWORD
            dwContrast:Longword;// DWORD
            dwBrightness:Longword; //DWORD
            dwRecOK:Boolean;
            dwFreezeOK:Boolean;
            dwMaxHwnd:Boolean;
            dwVideoCodecStr:string ;
            dwVideoCodecpara:TVidCodecX264Para ;
           

  end;
   pDevice_Info=^Device_Info;
   //定义视频设备色彩属性值
  Device_ColorProp=record
               ColorType:LongWord  ;
               MinVal:Integer  ;
               MaxVal:Integer  ;
               StepVal:Integer ;
               DefaultVal:Integer  ;
               CurVal:Integer  ;

  end;






  ///

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                              HnLiveSdk  delphi7  api
///              
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//---- call back functions define
  // 原始流回调函数和
  TRawVideoCallback = procedure (           pBuff: PByte   ;
                                            colorSpace: longword;
                                            lWidth:longword;
                                            lHeight:longword;
                                            bytesWidth:LongWord;
                                            var context:LongWord); stdcall;

   //IO报警回调函数
   TIOALARM_READ_CALLBACK= procedure(channelNumber: longword;
                                      lAlarmAddr:longword;
                                      lAlarmData:longword;
                                      context:pointer); stdcall;
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //    'DXMediaCap.dll';  此dll为核心dll和和设备相关的 功能都封装在此dll中
   //     DLL_DxMediaApi
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /// init sdk resource
  function DXInitialize():longword ; stdcall  ; external DLL_DxMediaApi;
  //'uninit sdk resource
   procedure  DXUninitialize(); stdcall; external DLL_DxMediaApi;
   //get sdk version
  function DXGetDeviceCount() :longword; stdcall ; external DLL_DxMediaApi;

  function DXEnumVideoDevices(var evTags:TDEVICE_TAG;var num:longword  ):longword; stdcall; external DLL_DxMediaApi;
  /// get video device number
  function DXEnumVideoCodecs(var evTags:TDEVICE_TAG;var num:longword  ):longword; stdcall; external DLL_DxMediaApi;

  function DXEnumAudioCodecs(var evTags:TDEVICE_TAG;var num:LongWord ):longword; stdcall; external DLL_DxMediaApi;

  function DXSetVideoCodec(device:THandle ; var evTags:TDEVICE_TAG ):longword; stdcall; external DLL_DxMediaApi;

  function DXSetAudioCodec(device:THandle ;var evTags:TDEVICE_TAG ):longword; stdcall; external DLL_DxMediaApi;

  function DXSetVideoCodecPara(device:THandle ;codecType:TcodecType;var pPara:TVidCodecX264Para):longword; stdcall; external DLL_DxMediaApi;


  function DXEnumAudioDevices(var evTags:TDEVICE_TAG;var num:longword  ):longword; stdcall; external DLL_DxMediaApi;

  function DXEnumSoundDevices(var evTags:TDEVICE_TAG;var num:longword  ):longword; stdcall; external DLL_DxMediaApi;

  function DXOpenDevice(idx:longword ; var  err:LongWord  ):THandle   ; stdcall ; external DLL_DxMediaApi;

  function DXCloseDevice(device:THandle ):longword ; stdcall; external DLL_DxMediaApi;

  function DXDeviceRun(device:THandle ):longword ; stdcall; external DLL_DxMediaApi;

  function DXDevicePause(device:THandle ):longword ; stdcall; external DLL_DxMediaApi;

  function DXDeviceStop(device:THandle ):longword ; stdcall; external DLL_DxMediaApi;

  function DXGetDeviceState(device:THandle;var state:LongWord ):longword ; stdcall; external DLL_DxMediaApi;

   function DXSetVideoSource(device:THandle;source:LongWord ):longword ; stdcall; external DLL_DxMediaApi;


  function DXGetVideoPara(device:THandle;
                           var standard:LongWord;
                           var colorspace:LongWord;
                           var width:LongWord ;
                           var height:LongWord ;
                           var framerate:Single ):longword ; stdcall; external DLL_DxMediaApi;

  function DXSetVideoPara(device:THandle;
                           standard:LongWord;
                           colorspace:LongWord;
                           width:LongWord ;
                           height:LongWord ;
                           framerate:Single  ):longword ; stdcall; external DLL_DxMediaApi;

  function DXSetDisplayPara(device:THandle;
                           paraType:LongWord;
                           value:Integer ;
                           flags:LongWord ):longword ; stdcall; external DLL_DxMediaApi;

  function DXGetDisplayPara(device:THandle;
                           paraType:LongWord;
                           var value:LongWord;
                           var flags:LongWord ):longword ; stdcall; external DLL_DxMediaApi;

   function DXGetDisplayParaRange(device:THandle;
                                   paraType:LongWord  ;
                                   var pMin:Integer ;
                                   var pMax:Integer  ;
                                   var pSteppingDelta:Integer  ;
                                   var pDefault:Integer;
                                   var pCapsFlags :Integer  ):longword ; stdcall; external DLL_DxMediaApi;


  function DXGetSignalPresent(device:THandle; var signal:LongWord) :longword ; stdcall; external DLL_DxMediaApi;

  function DXShowDeviceAttr(device:THandle;attrID:LongWord ;hOwner:THandle;var rect:TRect ):longword ; stdcall ; external DLL_DxMediaApi;


  function DXStartPreview(device:THandle;hWnd:THandle;var rect:TRect;vmrtype:LongWord ):longword ; stdcall ; external DLL_DxMediaApi;

  function DXStopPreview(device:THandle):longword ; stdcall ; external DLL_DxMediaApi;


  function DXFreezePreview(device:THandle;bFreeze:Boolean ):longword ; stdcall; external DLL_DxMediaApi;

  function DXHasAudio(device:THandle;var bHasAudio:Boolean  ):longword ; stdcall; external DLL_DxMediaApi;

  function DXSetAudioDevice(device:THandle;var audioDevice:TDEVICE_TAG ):longword ; stdcall; external DLL_DxMediaApi;

  function DXSetSoundOut(device:THandle;bSound:Boolean ):longword ; stdcall; external DLL_DxMediaApi;

  function DXEnableMute(device:THandle;bMute:Boolean):longword ; stdcall; external DLL_DxMediaApi;

  function DXSetAudioVolume(device:THandle;volume:LongWord;var balance:Char):longword ; stdcall; external DLL_DxMediaApi;

    //enum {di_none, di_blend, di_bob, di_weave};    deinterlace=-1 cancel
  function DXEnableDeinterlace(device:THandle;deinterlace:LongWord  ):longword ; stdcall; external DLL_DxMediaApi;

  // 降噪模式enum {dn_none, dn_b};
  function DXEnableDenoise(device:THandle;denoise:LongWord  ):longword ; stdcall; external DLL_DxMediaApi;


  function DXEnableSharpen(device:THandle;deSharpness:LongWord  ):longword ; stdcall; external DLL_DxMediaApi;




   function DXStartCapture(device:THandle;szFileName:PAnsiChar;saveAudio:Boolean  ;
                            timeSize:PInteger ;dataSize:PInteger ;saveNotify:Pointer;vidRatio:longword ):longword ; stdcall; external DLL_DxMediaApi;

   function DXStopCapture(device:THandle):longword ; stdcall; external DLL_DxMediaApi;



   function DXFreezeCaputre(device:THandle;bFreeze:Boolean ):longword ; stdcall; external DLL_DxMediaApi;



  function DXConvertYUVtoRGB(device:THandle;
                             pYUVBuf:pchar ;
                             pRGBBuf:PChar ;
                             lImgWidth:longWord ;
                             lImgHeight:LongWord;
                             bInverted:Boolean;
                             bInvertColor:Boolean):longword ; stdcall; external DLL_DxMediaApi;

   function DXSetTimeOSD(device:THandle;
                             x:longword ;
                             y:longword ;
                             pointSize:longWord ;
                             faceName:PAnsiChar;
                             color:COLORREF ;
                             bgcolor:COLORREF ;
                             transparent:Boolean ):longword ; stdcall; external DLL_DxMediaApi;

    function DXSetTextOSD(device:THandle;
                             x:longword ;
                             y:longword ;
                             TextNO:longword;
                             osdText:PAnsiChar;
                             pointSize:longWord ;
                             faceName:PAnsiChar;
                             color:COLORREF ;
                             bgcolor:COLORREF ;
                             transparent:Boolean ):longword ; stdcall; external DLL_DxMediaApi;

    function DXSetPictureOSD(device:THandle;
                             x:longword ;
                             y:longword ;
                             PicNO:longword;
                             picFileName:PAnsiChar;
                             transparent:Boolean;
                             alpha: byte ):longword ; stdcall; external DLL_DxMediaApi;

   function DXEnOSDDisp(device:THandle;
                             osdType:longword ;  //0表示时间叠加，1表示文本叠加，2表示图片叠加
                             number:longword ;
                              enable:Boolean):longword ; stdcall; external DLL_DxMediaApi;  	//* 叠加编号，当number = -1时为全部 */





  function DXGetFrameBuffer(device:THandle; buffer:pchar ;bufferLen:LongWord ;
                           var  gotBufferLen:longWord ;var colorSpace:LongWord;
                           var  width:LongWord; var height:LongWord ;
                           var  bytesWidth:LongWord; var rect:TRect ):longword ; stdcall; external DLL_DxMediaApi;


    function DXSaveBMPFile(szFileName:PAnsiChar;buffer:PChar  ;bufferLen:LongWord ;
                            colorSpace:LongWord ;width:LongWord;
                            height:LongWord; bytesWidth:LongWord):longword ; stdcall; external DLL_DxMediaApi;
  function DXSaveJPGFile(szFileName:PAnsiChar;buffer:PChar  ;bufferLen:LongWord ;
                            colorSpace:LongWord ;width:LongWord;
                            height:LongWord; bytesWidth:LongWord;quality:LongWord ):longword ; stdcall; external DLL_DxMediaApi;

  function DXSnapToBMPFile(device:THandle;szFileName:PAnsiChar;var rect:TRect ):longword ; stdcall; external DLL_DxMediaApi;


  function DXSnapToJPGFile(device:THandle;szFileName:PAnsiChar ;quality:LongWord ;var rect:TRect ):longword ; stdcall; external DLL_DxMediaApi;




    function DXStartRawVideoCallback(device:THandle; fn:TRawVideoCallback; var context: longword):longword ; stdcall; external DLL_DxMediaApi;


    function DXStopRawVideoCallback(device:THandle):longword ; stdcall; external DLL_DxMediaApi;


    function DXFlipVideo(device:THandle;flip:Boolean ):longword ; stdcall; external DLL_DxMediaApi;


     function DXMirrorVideo(device:THandle;mirror:Boolean ):longword ; stdcall; external DLL_DxMediaApi;

     
    function DXCreateBufferImg(imgbuffer:pchar ;
                               buffersize:LongWord ;
                               colorspace:longWord ;
                               width:LongWord;
                               height:LongWord;
                               var err:LongWord ):THandle ; stdcall; external DLL_DxMediaApi;


    function DXCreateFileImg(szImgFile:pchar;var err:LongWord ):longword ; stdcall; external DLL_DxMediaApi;

    
    function DXUpdateImg(img:THandle;hPrevWnd:THandle; var rect:TRect ):longword ; stdcall; external DLL_DxMediaApi;


    function DXDestroyImg(img:THandle):longword ; stdcall; external DLL_DxMediaApi;


     function DXEnDataRaterPara(device:THandle;RateType:LongWord;var pPara:TDRateColor_Para):longword ; stdcall; external DLL_DxMediaApi;


    function DXEnFScale(device:THandle;bEnFScale:boolean;var rect:TRect;enAlogrithm:LongWord):longword ; stdcall; external DLL_DxMediaApi;





 var DeviceInf:Device_Info;
     VidCodeInfo:TDEVICE_TAG ;
     AudCodeInfo:TDEVICE_TAG ;
     DeviceInfo:array [0..23]of Device_Info;
     DRateColorPara:array [0..23]of TDRateColor_Para;
     DeviceColor :array [0..23]of Device_ColorProp;
     VideoDeviceInfo:array [0..126]of TDEVICE_TAG;
     AudioDeviceInfo:array [0..126]of TDEVICE_TAG;
     VideoCodecInfo:array [0..126]of TDEVICE_TAG;
    AudioCodecInfo:array [0..126] of TDEVICE_TAG;
      VideoDeviceNum:LongWord  ;
     AudioDeviceNum:LongWord  ;
     VideoNameStr:array [0..16]of string ;
    AudioNameStr:array [0..16]of string ;


implementation


end.

