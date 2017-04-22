///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                   Description: DxMediaApi C# API CLASS 
//                                                    VER:1.1.0.0
//                                                   Write by Tony yu   E-mail:  yyhnet@163.com
//                                                   Copyright (C) 2011/11 ShenZhen ZhongAn Vision              
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Drawing;



namespace VideoTestDemo
{
    class DxMediaApi
    {
        public const string DxMediaApiDll = "DXMediaCap.dll";
     


        public enum TVideoState
        {
            state_stopped,
            state_paused,
            state_running
        }

        public enum TDeinterlace
        {
            di_none,
            di_blend,
            di_bob,
            di_weave
        }
        public  enum TosdType
        {
            osd_text,
            osd_time,
            osd_image

        }
        public enum TColorSpace
        {
            cs_rgb24,
            cs_rgb32,
            cs_yuy2

        }
    /*    public struct TDEVICE_TAG
        {
            public int idx;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
            public char[] deviceName;
        }

        public struct TCODEC_TAG
        {
            public int idx;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
            public char[] CodecName;
        }
*/
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct TCODEC_TAG
        {
            public int idx;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
            public string CodecName;
        }

        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct TDEVICE_TAG
       {
           public int idx;

           [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
           public string Name;
       }
        

        public struct RECT
        {
            public int Left;
            public int Top;
            public int Right;
            public int Bottom;
        }
        public static RECT TRect = new RECT();

      

        public struct Device_ColorProp
        {
            public int ColorType;
            public int MinVal;
            public int MaxVal;
            public int StepVal;
            public int DefaultVal;
            public int CurVal;


        }
        public struct TosdInfo
        {
            public int TimeX;
            public int TimeY;
            public int TxtPlaceX;
            public int TxtPlaceY;
            public int PicPlaceX;
            public int PicPlaceY;
            public int TimeFontSizeVal;
            public int TxtFontSizeVal;
            public string Osd_Txtstring;
            public string PicOsdFile;
          //  public string TimeFont;
          //  public string TxtFont;
            public int TxtColor;
            public int TimeColor;

        }

        public enum TcodecType
        {
            codec_sys,
            codec_x264,
            codec_xvid

        }


        public enum TCodecMode
        {
            codec_CBR ,
            codec_VBR

        }


   

      //  public static TCodecMode TEncodMode = new TCodecMode();

        public struct TDRateColorPara
        {
            public int nBrightness; // 亮度，取值(-255到255)
            public int nContrast;  //对比度，取值(-100到100)
        };
        public struct TVidCodecSysPara
         {
             public int bitrate; // 码率（单位：kbps）
             public int keyinterval;  //关键帧间隔
        }

        public struct TVidCodecX264Para
        {
            public int fps;
            public int keyframeinterval;
            public TCodecMode rcMode;   //码率控制,x264_cqp(恒定质量), x264_crf(恒定码率), x264_abr(平均码率)
            public int Quality;
            public int Bitrate;
            public int Maxrbps;
            public int Peekbps;
        }

   






         

               //callback function
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            // init sdk
            //origin stream callback
            public delegate void TfnRawVideoCallback(IntPtr buffer, int colorSpace,
                                     int width, int height, int bytesWidth, IntPtr context);




           
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////

 

            //copy memory
            [DllImport("Kernel32.dll", EntryPoint = "RtlMoveMemory", SetLastError = false)]
            public static extern void MoveMemory(IntPtr dest, IntPtr src, int size);

            [DllImport("user32.dll")]
            public static extern int SendMessage(IntPtr hWnd, uint Msg, int wParam, int lParam);


            //write ini file
            [DllImport("kernel32")]
            public static extern long WritePrivateProfileString(string section, string key,
            string val, string filePath);
            //read ini file
            [DllImport("kernel32")]
            public static extern int GetPrivateProfileString(string section,
                                             string key, string def,
                                             StringBuilder retVal, int size, string filePath);
            [DllImport("kernel32")]
            private static extern int GetPrivateProfileInt(string lpApplicationName, string lpKeyName,  int nDefault, string lpFileName); 
            [DllImport(DxMediaApiDll)]
            public static extern int DXInitialize();
            // get card channels number
            [DllImport(DxMediaApiDll)]
            public static extern void DXUninitialize();

            [DllImport(DxMediaApiDll)]
            public static extern int DXGetDeviceCount();


            [DllImport(DxMediaApiDll)]
            public static extern int DXEnumVideoDevices(IntPtr  devTags, ref int Vidnum);

            [DllImport(DxMediaApiDll)]
            public static extern int DXEnumAudioDevices(IntPtr  devTags, ref int Audnum);

            [DllImport(DxMediaApiDll)]
            public static extern int DXEnumVideoCodecs(IntPtr devTags, ref int VideCodecnum);

            [DllImport(DxMediaApiDll)]
            public static extern int DXEnumAudioCodecs(IntPtr devTags, ref int AudioCodecnum);

            [DllImport(DxMediaApiDll)]
            public static extern int DXEnumSoundDevices(IntPtr devTags, int num);

            [DllImport(DxMediaApiDll)]
            public static extern IntPtr DXOpenDevice(int idx, ref int err);

            [DllImport(DxMediaApiDll)]
            public static extern int DXCloseDevice(IntPtr device);

            [DllImport(DxMediaApiDll)]
            public static extern int DXSetVideoSource(IntPtr Device, int source);

            [DllImport(DxMediaApiDll)]
            public static extern int DXGetVideoSource(IntPtr Device, ref int curSource, ref int sources, ref char num);

             [DllImport(DxMediaApiDll)]
            public static extern int DXGetSignalPresent(IntPtr Device, ref int signal);
       


            [DllImport(DxMediaApiDll)]
            public static extern int DXDeviceRun(IntPtr device);

            [DllImport(DxMediaApiDll)]
            public static extern int DXDevicePause(IntPtr device);

            [DllImport(DxMediaApiDll)]
            public static extern int DXDeviceStop(IntPtr Device);

            [DllImport(DxMediaApiDll)]
            public static extern int DXGetDeviceState(IntPtr Device, ref int state);



            [DllImport(DxMediaApiDll)]
            public static extern int DXGetVideoPara(IntPtr Device, ref int standard, ref int colorspace,
                                                      ref int width, ref int height, ref float framerate);

            [DllImport(DxMediaApiDll)]
            public static extern int DXSetVideoPara(IntPtr Device, int standard, int colorspace,
                                                       int width, int height, float framerate);

            [DllImport(DxMediaApiDll)]
            public static extern int DXSetDisplayPara(IntPtr Device, int paraType, int value, int flags);



            [DllImport(DxMediaApiDll)]
            public static extern int DXGetDisplayPara(IntPtr Device, int paraType, ref int value, ref int flags);


            [DllImport(DxMediaApiDll)]
            public static extern int DXGetDisplayParaRange(IntPtr Device, int paraType,
                                            ref int pMin,
                                            ref int pMax,
                                            ref int pSteppingDelta,
                                            ref int pDefault,
                                            ref int pCapsFlags);



            [DllImport(DxMediaApiDll)]
            public static extern int DXStartPreview(IntPtr Device, IntPtr hWnd, ref  RECT rect, int vmrtype);

            [DllImport(DxMediaApiDll)]
            public static extern int DXStopPreview(IntPtr Device);

            [DllImport(DxMediaApiDll)]
            public static extern int DXFreezePreview(IntPtr Device, Boolean bFreeze);

            [DllImport(DxMediaApiDll)]
            public static extern int DXSetAudioDevice(IntPtr Device, ref TDEVICE_TAG audioDevice);

           
            [DllImport(DxMediaApiDll)]
            public static extern int DXEnableMute(IntPtr Device, Boolean bMute);


            [DllImport(DxMediaApiDll)]
            public static extern int DXHasAudio(IntPtr Device, ref Boolean bHasAudio);

            [DllImport(DxMediaApiDll)]
            public static extern int DXSetSoundOut(IntPtr Device,  Boolean bSound);



            [DllImport(DxMediaApiDll)]
            public static extern int DXSetAudioVolume(IntPtr Device, char volume, ref char balance);

            [DllImport(DxMediaApiDll)]
            public static extern int DXGetAudioVolume(IntPtr Device, ref char volume, ref char balance);

            [DllImport(DxMediaApiDll)]
            public static extern int DXSetVideoCodec(IntPtr Device, ref TDEVICE_TAG videoEncoder);

             [DllImport(DxMediaApiDll)]
            public static extern int DXSetVideoCodecPara(IntPtr Device, int codecType, ref TVidCodecX264Para VideoCodecPara);


            [DllImport(DxMediaApiDll)]
            public static extern int DXSetAudioCodec(IntPtr Device,ref  TDEVICE_TAG audioEncoder);


            [DllImport(DxMediaApiDll)]
            public static extern int DXStartCapture(IntPtr Device,
                                    string szFileName,
                                    Boolean saveAudio,
                                    ref int timeSize,
                                    ref int dataSize,
                                    Point saveNotify);

            [DllImport(DxMediaApiDll)]
            public static extern int DXStopCapture(IntPtr Device);


            [DllImport(DxMediaApiDll)]
            public static extern int DXFreezeCaputre(IntPtr Device,Boolean  bFreeze);





            [DllImport(DxMediaApiDll)]
            public static extern int DXEnableDeinterlace(IntPtr Device, int deinterlace);

            [DllImport(DxMediaApiDll)]
            public static extern int DXEnableDenoise(IntPtr Device, int denoise);

            [DllImport(DxMediaApiDll)]
            public static extern int DXEnableSharpen(IntPtr Device, int deSharpness);



            [DllImport(DxMediaApiDll)]
            public static extern int DXSetTextOSD(IntPtr Device,
                                               int x,
                                                int y,
                                                int TextNO,
                                                IntPtr  osdText,
                                                int pointSize,
                                                string faceName,
                                                int color,
                                                int bgcolor,
                                                Boolean transparent);




            [DllImport(DxMediaApiDll)]
            public static extern int DXSetTimeOSD(IntPtr Device,
                                                 int x,
                                                  int y,
                                                  int pointSize,
                                                  string faceName,
                                                  int color,
                                                  int bgcolor,
                                                  Boolean transparent);




            [DllImport(DxMediaApiDll)]
            public static extern int DXSetPictureOSD(IntPtr Device,
                                                 int x,
                                                int y,
                                                int PicNO,
                                                string picFileName,
                                                Boolean transparent,
                                                 char alpha);

             //0表示时间叠加，1表示文本叠加，2表示图片叠加
          [DllImport(DxMediaApiDll)]
            public static extern int DXEnOSDDisp(IntPtr Device,
                                                 int osdType,
                                                int number,
                                                 Boolean transparent);
                                             





            //////////////////////////////////////////////////////////////////
//            [DllImport(DxMediaApiDll)]
          [DllImport(DxMediaApiDll)]
            public static extern int DXStartRawVideoCallback(IntPtr Device, TfnRawVideoCallback fn, IntPtr context);

//            [DllImport(DxMediaApiDll)]
          [DllImport(DxMediaApiDll)]
            public static extern int DXStopRawVideoCallback(IntPtr Device);



           //////////////////////////////////////////////////////////////////////
            [DllImport(DxMediaApiDll)]
            public static extern int DXSnapToBMPFile(IntPtr Device, [MarshalAs(UnmanagedType.AnsiBStr)] string szFileName, ref RECT rect);



            [DllImport(DxMediaApiDll)]
            public static extern int DXSnapToJPGFile(IntPtr Device, [MarshalAs(UnmanagedType.AnsiBStr)] string szFileName, int quality, ref RECT rect);


            [DllImport(DxMediaApiDll)]
            public static extern int DXSaveBMPFile([MarshalAs(UnmanagedType.AnsiBStr)] string szFileName, IntPtr buffer, int bufferLen,int colorSpace,
                             int width, int height, int bytesWidth);

            [DllImport(DxMediaApiDll)]
            public static extern int DXSaveJPGFile([MarshalAs(UnmanagedType.AnsiBStr)] string szFileName, IntPtr buffer, int bufferLen, int colorSpace,
                            int width, int height, int bytesWidth, int quality);

            [DllImport(DxMediaApiDll)]
            public static extern int DXGetFrameBuffer(IntPtr Device, IntPtr buffer, int bufferLen,
                              ref int gotBufferLen,ref int colorSpace,
                            ref int width, ref int height, ref int bytesWidth, ref RECT  rect);


         [DllImport(DxMediaApiDll)]
            public static extern int DXConvertYUVtoRGB(IntPtr Device,
                                                        IntPtr pYUVBuf,
                                                        IntPtr pRGBBuf,
                                                        int lImgWidth,
                                                        int lImgHeight,
                                                        Boolean bInverted,
                                                        Boolean bInvertColor);

        


         [DllImport(DxMediaApiDll)]
            public static extern int DXEnDataRaterPara(IntPtr Device, int RateType, ref  TDRateColorPara DataPara);


         [DllImport(DxMediaApiDll)]
         public static extern int DXEnFScale(IntPtr Device, Boolean bEnFScale, ref RECT rec, int enAlogrithm);
            


        /*
            [DllImport(DxMediaApiDll)]
            public static extern IntPtr DXCreateBufferImg(IntPtr imgbuffer,  int buffersize,
                              int colorSpace,int width,  int height, ref int err);


            [DllImport(DxMediaApiDll)]
            public static extern int DXCreateFileImg(ref string  szImgFile, ref int err);

            [DllImport(DxMediaApiDll)]
            public static extern int DXUpdateImg(IntPtr img, IntPtr hPrevWnd ,ref RECT rect);

            [DllImport(DxMediaApiDll)]
            public static extern int DXDestroyImg(IntPtr img);*/






             

            [DllImport(DxMediaApiDll)]
            public static extern int DXFlipVideo(IntPtr Device,Boolean flip);


            [DllImport(DxMediaApiDll)]
            public static extern int DXMirrorVideo(IntPtr Device, Boolean mirror);


    
          





            








            ///////////////////////////////////////////////////////
            // 获得窗口矩形
            [DllImport("user32.dll")]
            public static extern int GetWindowRect(IntPtr hWnd, out RECT lpRect);

            // 获得客户区矩形
            [DllImport("user32.dll")]
            public static extern int GetClientRect(IntPtr hWnd, out RECT lpRect);

          


            }
            }





















        
    


