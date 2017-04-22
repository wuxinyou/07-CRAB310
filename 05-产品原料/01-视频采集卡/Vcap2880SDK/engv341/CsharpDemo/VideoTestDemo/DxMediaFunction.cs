using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;


namespace VideoTestDemo
{
    class DxMediaFunction
    {
        public static IntPtr[] CardHandle = new IntPtr[23];
        public static IntPtr[] PrvHandle = new IntPtr[23];
        public static string IniFileName;
        public static string RecSavePath;
        public static string PicSavePath;
        public static int BrightValue;
        public static int ContrastValue;
        public static int HueValue;
        public static int StaturationValue;
        public static int SharpValue;
        public static DxMediaApi.TDRateColorPara ColorPara;
  
        public static DxMediaApi.RECT[] PrvRect = new DxMediaApi.RECT[23];

        //   public static DxMediaApi.TCODEC_TAG VidCodecInfo;
        //   public static DxMediaApi.TCODEC_TAG AudCodecInfo;
        public static DxMediaApi.TDEVICE_TAG[] VideoDeviceInfo = new DxMediaApi.TDEVICE_TAG[32];
        public static DxMediaApi.TDEVICE_TAG[] AudioDeviceInfo = new DxMediaApi.TDEVICE_TAG[32];

        public static int NumCard;


        public struct Device_Info
        {

           
            public int dwHeight;
            public int dwWidth;
            public float dwFrameRate;
            public int dwColorspace;
            public int dwVidStandard;
            public int dwOpenDevState;
            public Boolean dwConnectState;
            public int dwPrviewState;
            public IntPtr dwCardHandle;
            public IntPtr dwPrvHandle;
            public DxMediaApi.RECT dwPrvRect;
            public DxMediaApi.RECT dwSnapPicRect;
            public  DxMediaApi.RECT dwZoomRect;
            public Boolean dwRawCallOk;
            public Boolean dwSnapOK;
            public Boolean dwRecOK;
            public Boolean dwFreezeRecOK;
            public Boolean dwFlipVideoEnable;
            public Boolean dwMirrorVideoEnable;
            public DxMediaApi.TVidCodecX264Para dwVideoCodecpara;        
            public string dwVideoCodecStr;


        }

        public static Device_Info[] DeviceInfo = new Device_Info[23];

        public struct IniFileSave_Value
        {
            //视频流尺寸
            public string iniWidthValue;
            public string iniHeightValue;
            public string iniVideoStandard;
            public string iniHueValue;
            public string iniBrightValue;
            public string iniContrastValue;
            public string iniSaturationValue;
            public string iniSharpValue;
        }

        public static IniFileSave_Value[] IniFileSaveValue = new IniFileSave_Value[23];


        public int InitDevice()
        {
            DxMediaApi.DXInitialize();
            int CardNum = DxMediaApi.DXGetDeviceCount();
            return CardNum;
        }
        public void UnInitDevice()
        {
            DxMediaApi.DXUninitialize();

        }
        public IntPtr OpenDevice(int nCard, ref int OpenDevState)
        {

            IntPtr DeviceHandle = DxMediaApi.DXOpenDevice(nCard, ref OpenDevState);
            return DeviceHandle;

        }

        public Boolean CloseDevice(IntPtr CardHandle)
        {
            DxMediaApi.DXCloseDevice(CardHandle);
            return true;
        }

        public Boolean ConnectDev(IntPtr CardHandle, int VideoStandard, int ColorSpace, int nWidth, int nHeight, float FrameRate)
        {
            DxMediaApi.DXSetVideoPara(CardHandle, VideoStandard, ColorSpace, nWidth, nHeight, FrameRate);
            DxMediaApi.DXDeviceRun(CardHandle);


            return true;
        }

        public Boolean DisConnectDev(IntPtr CardHandle)
        {
            DxMediaApi.DXStopPreview(CardHandle);
            DxMediaApi.DXDeviceStop(CardHandle);

            return true;
        }

        public int StartPrview(IntPtr CardHandle, IntPtr PrvHwnd, DxMediaApi.RECT PrvRect, int PrvModle)
        {
            int ok = DxMediaApi.DXStartPreview(CardHandle, PrvHwnd, ref PrvRect, PrvModle);
            return ok;

        }
        public void StopPrview(IntPtr CardHandle)
        {
            DxMediaApi.DXStopPreview(CardHandle);
        }
        public void SnapPicture(IntPtr CardHandle, string SaveName, int PictureType, DxMediaApi.RECT SnapRect)
        {
            if (PictureType == 0)
            {
                DxMediaApi.DXSnapToBMPFile(CardHandle, SaveName, ref SnapRect);
            }
            else
            {
                DxMediaApi.DXSnapToJPGFile(CardHandle, SaveName, 100, ref SnapRect);
            }

        }

        public int StartRecord(IntPtr CardHandle, string SaveName, string CodecName, DxMediaApi.TVidCodecX264Para dwH264CodecPara, Boolean AudioRec)
        {
            DxMediaApi.TDEVICE_TAG[] VidCodecInfo = new DxMediaApi.TDEVICE_TAG[125];
            DxMediaApi.TDEVICE_TAG[] AuCodecInfo = new DxMediaApi.TDEVICE_TAG[125];
            int CodecNum=32;
            int CurCodec=0;
            int AuCodecNum = 32;
            int AuCurCodec = 0;
          
            int Size = Marshal.SizeOf(typeof(DxMediaApi.TDEVICE_TAG)) * 32;
            IntPtr VideoCodecBuf = Marshal.AllocHGlobal(Size);
            IntPtr AudioCodecBuf = Marshal.AllocHGlobal(Size);
           
        
            //enum the video Codec
            DxMediaApi.DXEnumVideoCodecs(VideoCodecBuf, ref CodecNum);


            //enum the audio Codec
            DxMediaApi.DXEnumVideoCodecs(AudioCodecBuf, ref AuCodecNum);


            //set the video codec
            for (int i = 0; i < CodecNum; i++)
            {
                IntPtr VidCodecBuf = new IntPtr(VideoCodecBuf.ToInt64() + Marshal.SizeOf(typeof(DxMediaApi.TDEVICE_TAG)) * i);
                VidCodecInfo[i] = (DxMediaApi.TDEVICE_TAG)Marshal.PtrToStructure(VidCodecBuf, typeof(DxMediaApi.TDEVICE_TAG));

                //set video codec 
                if (VidCodecInfo[i].Name.ToLower () == CodecName.ToLower ())
                {
                        CurCodec=i;
                        break;

                }


            }

            //set the audio codec
            for (int i = 0; i < AuCodecNum; i++)
            {
                IntPtr AudCodecBuf = new IntPtr(AudioCodecBuf.ToInt64() + Marshal.SizeOf(typeof(DxMediaApi.TDEVICE_TAG)) * i);
                AuCodecInfo[i] = (DxMediaApi.TDEVICE_TAG)Marshal.PtrToStructure(AudCodecBuf, typeof(DxMediaApi.TDEVICE_TAG));

                //set video codec 
                if (AuCodecInfo[i].Name.ToLower() == CodecName.ToLower())
                {
                    AuCurCodec = i;
                    break;

                }


            }
            //set the video codec 
            DxMediaApi.DXSetVideoCodec(CardHandle, ref  VidCodecInfo[CurCodec]);

            if (AudioRec == true)
            {
                DxMediaApi.DXSetAudioCodec(CardHandle, ref  AuCodecInfo[AuCurCodec]);
            }
                //////////////////set the x264 video codec parameter
            string X264Name = "x264 Codec";
            string XvidName="xvid Codec";
            if (VidCodecInfo[CurCodec].Name.ToLower() == X264Name.ToLower()||VidCodecInfo[CurCodec].Name.ToLower() == XvidName.ToLower())
            {

                DxMediaApi.DXSetVideoCodecPara(CardHandle, 1, ref dwH264CodecPara);
            }
          
            Marshal.FreeHGlobal(VideoCodecBuf);
            Marshal.FreeHGlobal(AudioCodecBuf);
           //  Marshal.FreeHGlobal(AudCodecBuf);
           // Marshal.FreeHGlobal(VidCodecBuf);
          
            int ok=1;
            Point Notify;
            int nTimeValue=0;
            int nSizeValue=0;
            Notify = new Point();

            ok = DxMediaApi.DXStartCapture(CardHandle, SaveName, AudioRec, ref nTimeValue, ref nSizeValue, Notify);
            return ok;


        }

        public int StopRecord(IntPtr CardHandle)
        {

            int ok = 1;
            ok = DxMediaApi.DXStopCapture(CardHandle);
            return ok;
        }
        public int FreezeRecord(IntPtr CardHandle, Boolean Enable)
        {

            int ok = 1;
            ok = DxMediaApi.DXFreezeCaputre(CardHandle,Enable);
            return ok;
        }
        public void GetVideoPara(IntPtr CardHandle, int nWidth, int nHeight, int nColorSpace, int VideoStandard, float FrameRate)
        {
            DxMediaApi.DXGetVideoPara(CardHandle, ref VideoStandard, ref nColorSpace, ref nWidth, ref nHeight, ref FrameRate);
        }



        public void SaveBmpToFile(byte[] rgbFrame, int width, int height, string SaveName)
        {

         
           Bitmap pic = new Bitmap(width, height, System.Drawing.Imaging.PixelFormat.Format32bppRgb);
            Color c;

            for (int i = 0; i < rgbFrame.Length; i++)
            {
                c = Color.FromArgb(rgbFrame[i]);
                pic.SetPixel(i / width, i / height, c);

            }

            pic.Save(SaveName);
/*
            // 写 BMP 图像文件。
            int rgb = width * 3 % 4;
            int bytePerLine = 0;
            rgb = rgb != 0 ? 4 - rgb : rgb;
            bytePerLine = width * 3 + rgb;

            using (FileStream fs = File.Open(SaveName, FileMode.Create))
            {
                using (BinaryWriter bw = new BinaryWriter(fs))
                {
                    bw.Write('B');
                    bw.Write('M');
                    bw.Write(bytePerLine * height + 54);
                    bw.Write(0);
                    bw.Write(54);
                    bw.Write(40);
                    bw.Write(width);
                    bw.Write(height);
                    bw.Write((ushort)1);
                    bw.Write((ushort)24);
                    bw.Write(0);
                    bw.Write(bytePerLine * height);
                    bw.Write(0);
                    bw.Write(0);
                    bw.Write(0);
                    bw.Write(0);

                    byte[] data = new byte[bytePerLine * height];
                    int gIndex = width * height;
                    int bIndex = gIndex * 2;

                    for (int y = height - 1, j = 0; y >= 0; y--, j++)
                    {
                        for (int x = 0, i = 0; x < width; x++)
                        {
                            data[y * bytePerLine + i++] = rgbFrame[bIndex + j * width + x];    // B
                            data[y * bytePerLine + i++] = rgbFrame[gIndex + j * width + x];    // G
                            data[y * bytePerLine + i++] = rgbFrame[j * width + x];  // R
                        }
                    }
                    bw.Write(data, 0, data.Length);
                    bw.Flush();
                }
            }
            */
           
        }


        /// <summary>
        /// ////////////////////
        /// </summary>
        /// <param name="nCard"></param>
        /// <param name="FileType"></param>
        /// <param name="PicSavePath"></param>
        /// <returns></returns>
        public string CreateFileName(int nCard, string FileType, string PicSavePath)
        {
            string szPath;


            DateTime CurTime = DateTime.Now;
            szPath = PicSavePath + CurTime.ToString("yyyyMMddHHmmss") + "-" + "Camera" + System.Convert.ToString(nCard) + FileType;
            return szPath;

        }
        //write ini file function
        public void IniWriteValue(string Section, string Key, string Value, string iniFileName)
        {


            DxMediaApi.WritePrivateProfileString(Section, Key, Value, iniFileName);
        }

        //read ini file function
        public string IniReadValue(string Section, string Key, int size, string iniFileName)
        {
            StringBuilder temp = new StringBuilder(500);
            DxMediaApi.GetPrivateProfileString(Section, Key, "", temp, size, iniFileName);
            return temp.ToString();
        }
    }
}
