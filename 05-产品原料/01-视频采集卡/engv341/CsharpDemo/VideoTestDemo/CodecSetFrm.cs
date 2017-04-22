using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;

namespace VideoTestDemo
{
    public partial class CodecSetFrm : Form
    {
        DxMediaApi.TDEVICE_TAG[] VideoCodecInfo = new DxMediaApi.TDEVICE_TAG[125];
        DxMediaApi.TDEVICE_TAG[] AudioCodecInfo = new DxMediaApi.TDEVICE_TAG[125];
        DxMediaApi.TDEVICE_TAG VidCodeInfo;
        DxMediaApi.TDEVICE_TAG AudCodeInfo;


        int VideoCodecNum;
        int AudioCodecNum;
        int VideoCurCodec;
        int AudioCurCodec;
        string CurVidName;
        string CurAudName;
        string[] VideoCodecStr = new string[125];
        string[] AudioCodecStr = new string[125];
        


        public CodecSetFrm()
        {
            InitializeComponent();
        }

        private void CodecSetFrm_Load(object sender, EventArgs e)
        {

         
            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr == "DivX? 5.1.1 Codec")
            {

                rdDivx.Checked = true;
            }

            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr == "XviD MPEG-4 Codec")
            {

                rdXvid.Checked = true;
            }

            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr == "x264 Codec")
            {

                rdX264.Checked = true;
            }

            
            VideoCodecNum = 32;
            AudioCodecNum = 32;
            VideoCurCodec = 0;
            AudioCurCodec = 0;
            int i;

            for ( i = 0; i < 125; i++)
            {
                VideoCodecInfo[i].idx = 0;
                VideoCodecInfo[i].Name = "";
                AudioCodecInfo[i].idx = 0;
                AudioCodecInfo[i].Name = "";


            }
            int Size = Marshal.SizeOf(typeof(DxMediaApi.TDEVICE_TAG)) * 32;
            IntPtr VideoCodecBuf = Marshal.AllocHGlobal(Size);
            IntPtr AudioCodecBuf = Marshal.AllocHGlobal(Size);
            //enum the video and the audio codec
            DxMediaApi.DXEnumVideoCodecs(VideoCodecBuf, ref VideoCodecNum);
            DxMediaApi.DXEnumAudioCodecs(AudioCodecBuf, ref AudioCodecNum);


            for (int j = 0; j < 32; j++)
            {
                IntPtr VidCodecBuf = new IntPtr(VideoCodecBuf.ToInt64() + Marshal.SizeOf(typeof(DxMediaApi.TDEVICE_TAG)) * j);
                VideoCodecInfo[j] = (DxMediaApi.TDEVICE_TAG)Marshal.PtrToStructure(VidCodecBuf, typeof(DxMediaApi.TDEVICE_TAG));

                IntPtr AudCodecBuf = new IntPtr(AudioCodecBuf.ToInt64() + Marshal.SizeOf(typeof(DxMediaApi.TDEVICE_TAG)) * j);
                AudioCodecInfo[j] = (DxMediaApi.TDEVICE_TAG)Marshal.PtrToStructure(AudCodecBuf, typeof(DxMediaApi.TDEVICE_TAG));
            }
            Marshal.FreeHGlobal(VideoCodecBuf);
            Marshal.FreeHGlobal(AudioCodecBuf);


            for ( i = 0; i < VideoCodecNum; i++)
            {
                VideoCodecStr[i] =VideoCodecInfo[i].Name;
                comboBoxVidCodec.Items.Add(VideoCodecStr[i]);


                if ((VideoCodecStr[i] == "XviD MPEG-4 Codec") || (VideoCodecStr[i] == "Xvid MPEG-4 Codec"))
                {
                    VideoCurCodec=i;
                    
                }

                comboBoxVidCodec.SelectedIndex = VideoCurCodec;
            
                      
              


            }
            for (i = 0; i < AudioCodecNum; i++)
            {

                AudioCodecStr[i] = AudioCodecInfo[i].Name;
                comboBoxAudCodec.Items.Add(AudioCodecStr[i]);
                if (AudioCodecStr[i] == "Microsoft ADPCM") 
                {
                    AudioCurCodec = i;
                   
                }
                comboBoxAudCodec.SelectedIndex = AudioCurCodec;
                

            }

        }

        private void btOk_Click(object sender, EventArgs e)
        {
            //////////Create the save directoy start//////////////////////////
            if (!Directory.Exists(TxtPicPath.Text))//判断是否存在
            {
                 Directory.CreateDirectory(TxtPicPath.Text);//创建新路径
            }

            if (!Directory.Exists(TxtRecPath.Text))//判断是否存在
            {
                Directory.CreateDirectory(TxtRecPath.Text);//创建新路径
            }
            //PicSavePath
            DxMediaFunction.PicSavePath = TxtPicPath.Text;
            DxMediaFunction.RecSavePath = TxtRecPath.Text;
            DxMediaApi.WritePrivateProfileString("SystemSetting", "PicSaveParh" , TxtPicPath.Text, DxMediaFunction.IniFileName);

            DxMediaApi.WritePrivateProfileString("SystemSetting", "VideoSaveParh", TxtRecPath.Text, DxMediaFunction.IniFileName);

                //////////Create the save directoy end//////////////////////////


            ///////////////////Set the video Codec Name Start/////////////////////
            if (rdXvid.Checked == true)
            {
                DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr = "xvid Codec";
               

            }

             if (rdDivx.Checked == true)
            {
                DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr = "DivX? 5.1.1 Codec";
               
            }

             if (rdX264.Checked == true)
            {
                DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr = "x264 Codec";
               

            }

             DxMediaApi.WritePrivateProfileString("SystemSetting", "VideoCodec",  DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr , DxMediaFunction.IniFileName);
            
               ///////////////////Set the video Codec Name End/////////////////////////////////


            
            this.Close();
                
        }

        private void comboBoxVidCodec_SelectedIndexChanged(object sender, EventArgs e)
        {
            VideoCurCodec=comboBoxVidCodec.SelectedIndex;
        }

        private void comboBoxAudCodec_SelectedIndexChanged(object sender, EventArgs e)
        {
           AudioCurCodec= comboBoxAudCodec.SelectedIndex;
        }

        private void btnRecPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog Recfolder = new System.Windows.Forms.FolderBrowserDialog();
            if (Recfolder.ShowDialog() == DialogResult.OK)
            {
                TxtRecPath.Text = Recfolder.SelectedPath;
                 
            }

           
            DxMediaFunction.RecSavePath = TxtRecPath.Text;
        }

        private void btPicPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog Picfolder = new System.Windows.Forms.FolderBrowserDialog();
            if (Picfolder.ShowDialog() == DialogResult.OK)
            {
                TxtPicPath.Text = Picfolder.SelectedPath;
                

            }

      
            DxMediaFunction.RecSavePath = TxtRecPath.Text;
        }

        private void rdXvid_CheckedChanged(object sender, EventArgs e)
        {
            if (rdXvid.Checked == true)
            {
                DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr="XviD MPEG-4 Codec";
                DxMediaApi.WritePrivateProfileString("SystemSetting", "VideoCodec", "XviD MPEG-4 Codec", DxMediaFunction.IniFileName);

            }
        }

        private void rdDivx_CheckedChanged(object sender, EventArgs e)
        {
            if (rdDivx.Checked == true)
            {
                DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr = "DivX? 5.1.1 Codec";
                DxMediaApi.WritePrivateProfileString("SystemSetting", "VideoCodec", "DivX? 5.1.1 Codec", DxMediaFunction.IniFileName);

            }
        }

        private void rdX264_CheckedChanged(object sender, EventArgs e)
        {
            if (rdX264.Checked == true)
            {
                DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr = "x264 Codec";
                DxMediaApi.WritePrivateProfileString("SystemSetting", "VideoCodec", "x264 Codec", DxMediaFunction.IniFileName);

            }
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }
    }
}
