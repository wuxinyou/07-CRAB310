unit GlobalVar;

interface
uses Windows,SysUtils,DxMediaApi,IniFiles;
 var
     dwPreviewMode:longword;
    PicSavePath :string;
    RecSavePath:string;
    szPicFile:string;
    szRecFile:string;
    SnapMode:string;
    BackColor:TCOLORREF ;
    TimeColor:TCOLORREF ;
    TextColor:array [0..32] of TCOLORREF ;
    PicAlphaValue :array [0..32] of byte;




    nCurBuff:pointer;
    FreeBuf:boolean;
    nPrvHwnd:boolean;
    GetBuffSize:longword;
    DrawBuffOk:Boolean ;
    TimeX:Integer;
    TimeY:Integer;
    TxtPlaceX:array [0..32] of Integer;
    TxtPlaceY:array [0..32] of Integer;
    PicPlaceX:array [0..32] of Integer;
    PicPlaceY:array [0..32] of Integer;
    TimeFontSizeVal:LongWord;
    TxtFontSizeVal:array [0..32] of LongWord;
    Osd_Txt:array [0..32] of string;
    PicOsdFile:array [0..32] of string;
    KeyFrameValue:LongWord;
    VBRQuantValue:LongWord;
    FrameRateValue:LongWord;
    EncodeMode:TBitrateControlType_t;

    PrvHandle:array[0..23] of THandle ;
    CardHandle: array [0..23]of THandle ;
    VideoCodec:array [0..32] of Char ;
    AudioCodec:array [0..32] of Char ;
       PrvRect:TRect ;
    VideoInput:THDVideoSource ;

    
   //枚举编码器相关变量定义
  CurVideoCodec:LongWord ;
  CurAudioCodec:LongWord ;
  VideoCodecName:array [0..127]of PAnsiChar;
  AudioCodecName:array [0..127]of PAnsiChar;




  ConnectOk:array[0..23] of LongWord ;
  nCard:longword;
  NumCard:longword;
  PreviewRect:TRECT;
  CodecSet:Boolean ;
  RecOK:Boolean ;
  FreezeOK:Boolean ;
  PrvOk:Boolean;
  CardNo:LongWord ;
  RawCallOk:array[0..23]of longword;
  CallSnapOk:boolean;
  PicFileName:string;
  ImageFlip:Boolean ;
  ImageMirr:Boolean ;




implementation




end.
