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

    public partial class Form1 : Form
    {
       
        public static int nCard;
     
        public Panel[] PreviewHwnd = new Panel[4];

        public static int PreviewMode;
        public static int PrvWidth;
        public static int PrvHeight;
        public int nIndex = 0;
        public int m_nShowMode;
        public int m_nWndNum ;
        public Boolean[] MaxFrmSn = new Boolean[4];


      
        public static Boolean CodecSet;
      
        public Boolean RawCallOk;
        public static Boolean SnapOk;
        public Boolean AudioHas;
        public static IntPtr pCallBuf;

        public static int nWidth;
        public static int nHeight;
        public static int BufSize;
        public static int colorSpace;
        public static int BytesWidth;
        public static int gotBufferLen;

   


        public const int WM = 0x0400;
        public const int MyMesg = WM + 100;
        public static Form1 msgForm;

        private static DxMediaApi.TfnRawVideoCallback SnapCall;


    

     
        DxMediaFunction DxSdkFunction = new DxMediaFunction();
   






        // DenoiseSetting VideoDenoise = new DenoiseSetting();

        public static string[] VideoDevStr = new string[125];
        public static string[] AudioDevStr = new string[125];
     
       
   
        // origin call back function
        public static void snapcallback(IntPtr buffer, int colorSpaceValue,
                                        int width, int height, int bytesWidthValue, IntPtr  context)
        {
             nCard = (int)context;
            if (DxMediaFunction.DeviceInfo[nCard].dwSnapOK == true)
            {
               
              
                string szPath;


                DateTime CurTime = DateTime.Now;
                szPath = DxMediaFunction.PicSavePath +"\\" + CurTime.ToString("yyyyMMddHHmmss") + "-" + "Camera" + System.Convert.ToString(nCard) + ".bmp";

                gotBufferLen = width * height * colorSpaceValue;
                DxMediaApi.DXSaveBMPFile(szPath, buffer, gotBufferLen, colorSpace, width, height, bytesWidthValue);
                MessageBox.Show("Snap bmp ok: " + szPath);
                //  DxMediaApi.MoveMemory(pCallBuf, buffer, Marshal.SizeOf(buffer)); 

                // DxMediaApi.PostMessage(msgForm.Handle, MyMesg, context, 0);

                DxMediaFunction.DeviceInfo[nCard].dwSnapOK = false;
            }

        }
        /*
        //message recave
        protected override void DefWndProc(ref System.Windows.Forms.Message m)
        {
           // int BufSize;
            //BufSize = 2048 * 1024 * 3;
            string SaveFile;
            //create the snap picture file name
          
            switch (m.Msg)
            {
                case MyMesg:
                   nCard  = (int)(m.WParam);
                   SaveFile = DxSdkFunction.CreateFileName(nCard, ".bmp", "c:\\");
                   gotBufferLen = nWidth * nHeight * colorSpace;
                   DxMediaApi.DXSaveBMPFile( SaveFile, pCallBuf, gotBufferLen,colorSpace, nWidth, nHeight, BytesWidth); 

                    break;
                default:
                    base.DefWndProc(ref   m);
                    break;
            }
        }*/
        public Form1()
        {
            InitializeComponent();
        }

       
       

        private void Form1_Load(object sender, EventArgs e)
        {

            ////////////int 
            this.Width = 720 + 155;
            this.Height = 600 + 40;
            //定义主窗体弹出位置
            this.Left = 10;
            this.Top = 10;

            msgForm = new Form1();
            CodecSetFrm CodecFrm = new CodecSetFrm();
            
         
            int j = 0;
            int k = 0;

          
            /////////////////create the ini file start/////////////////////////

            DxMediaFunction.IniFileName = System.AppDomain.CurrentDomain.BaseDirectory + "CsharpSetting.ini";

            ///// Check  the ini file doesn't already exist. If it doesn't exist, create
            if (!File.Exists(DxMediaFunction.IniFileName))
            {
                FileStream IniFile = System.IO.File.Create(DxMediaFunction.IniFileName);
               
            }

            /////////////////create the ini file end/////////////////////////
           
            


            //////////////////Read the ini file value start///////////////////////////////////////////


            DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr = DxSdkFunction.IniReadValue("SystemSetting", "VideoCodec", 20, DxMediaFunction.IniFileName);
            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr == "")
            {
                DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr = "x264 Codec";
            }

            if(DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr== "DivX? 5.1.1 Codec")
            {

                CodecFrm.rdDivx.Checked = true;
             }

            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr == "XviD MPEG-4 Codec")
            {

                CodecFrm.rdXvid.Checked = true;
            }

            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwVideoCodecStr == "x264 Codec")
            {

                CodecFrm.rdX264.Checked = true;
            }


            /////save path
            DxMediaFunction.PicSavePath = DxSdkFunction.IniReadValue("SystemSetting", "PicSaveParh", 20, DxMediaFunction.IniFileName);
            if (DxMediaFunction.PicSavePath == "")
            {
                DxMediaFunction.PicSavePath = "d:\\Pic";
                if (!Directory.Exists(DxMediaFunction.PicSavePath))//判断是否存在
                 {
                     Directory.CreateDirectory(DxMediaFunction.PicSavePath);//创建新路径
                 }
            }
            DxMediaFunction.RecSavePath = DxSdkFunction.IniReadValue("SystemSetting", "VideoSaveParh", 20, DxMediaFunction.IniFileName);
            if (DxMediaFunction.RecSavePath == "")
            {
                DxMediaFunction.PicSavePath = "d:\\Video";
                if (!Directory.Exists(DxMediaFunction.RecSavePath))//判断是否存在
                 {
                     Directory.CreateDirectory(DxMediaFunction.RecSavePath);//创建新路径
                 }
            }
            ///Set the control state
            CodecFrm.TxtPicPath.Text = DxMediaFunction.PicSavePath;
            CodecFrm.TxtRecPath.Text = DxMediaFunction.RecSavePath;


            // read the inf file and set the preview mode
            if (DxSdkFunction.IniReadValue("SystemSetting", "PreviewMode", 20, DxMediaFunction.IniFileName) == "VMR7")
            {

                PreviewMode = 0;
                radiovmr7.Checked = true;
            }

            if (DxSdkFunction.IniReadValue("SystemSetting", "PreviewMode", 20, DxMediaFunction.IniFileName) == "OFFscream")
            {

                PreviewMode = 1;
                radiooffscrean.Checked = true;
            }

            if (DxSdkFunction.IniReadValue("SystemSetting", "PreviewMode", 20, DxMediaFunction.IniFileName) == "VMR9")
            {

                PreviewMode = 2;
                radiovmr9.Checked = true;
            }

            ////////////////////////////////////Read the ini file value end///////////////////////////////


            for (int i = 0; i < 23; i++)
            {
                //DxMediaFunction.VideoDeviceInfo[i].idx = 0;
                // DxMediaFunction.VideoDeviceInfo[i].deviceName =""; //new char[128];
                //DxMediaFunction.AudioDeviceInfo[i].idx = 0;
                //DxMediaFunction.AudioDeviceInfo[i].deviceName = ""; //new char[128];

                DxMediaFunction.DeviceInfo[i].dwOpenDevState = 1;
            }
          

            // init
            ///////////////////////////////////////////////////////////////////////////////////////////////////////

       
            CodecSet = false;
       
            
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            SnapCall = new DxMediaApi.TfnRawVideoCallback(snapcallback);
            //init sdk resource and get the video device number
            DxMediaFunction.NumCard = DxSdkFunction.InitDevice();


         


                //Single preview Hwnd
                if (DxMediaFunction.NumCard < 2)
                {
                    m_nShowMode = 1;
                    m_nWndNum = 1;
                    PrvWidth = (this.Width - 130) / m_nShowMode;
                    PrvHeight = (this.Height - 40) / m_nShowMode;

                }

           // Four screen
            if ((DxMediaFunction.NumCard < 5)&(DxMediaFunction.NumCard >1))
            {
                m_nShowMode = 2;
                m_nWndNum = 4;
                PrvWidth = (this.Width - 130) / m_nShowMode;
                PrvHeight = (this.Height - 40) / m_nShowMode;

            }

            // dynamic create  panel
            for (int i = 0; i < m_nWndNum; i++)
            {
                MaxFrmSn[i] = false;
                // PrvHwnd[i].
                PreviewHwnd[i] = new Panel();
                PreviewHwnd[i].Size = new System.Drawing.Size(PrvWidth, PrvHeight);

                this.Controls.Add(PreviewHwnd[i]);

                PreviewHwnd[i].Name = Convert.ToString(i);
                PreviewHwnd[i].BackColor = Color.FromArgb(255, 0, 255);
                //get preview hwnd handle
                DxMediaFunction.DeviceInfo[i].dwPrvHandle = PreviewHwnd[i].Handle;
          
                PreviewHwnd[i].DoubleClick += new EventHandler(MyHwndDbClick);
                PreviewHwnd[i].MouseDoubleClick += new MouseEventHandler(MyMouseDb);
                PreviewHwnd[i].Click += new EventHandler(MyHwndClick);

            }

            //定义panel控件位置
            //////////////////


            for (k = 0; k < m_nShowMode; k++)
            {
                for (j = 0; j < m_nShowMode; j++)
                {
                    nIndex = k * m_nShowMode + j;
                    if (nIndex >= m_nWndNum)
                    {
                        break;
                    }
                    PreviewHwnd[nIndex].Left = PreviewHwnd[0].Width * j;
                    PreviewHwnd[nIndex].Top = PreviewHwnd[0].Height * k;


                }

            }

            //Get the preview hwnd rect
            for (int i = 0; i < m_nWndNum; i++)
            {
                //get the preview rect
                DxMediaApi.GetClientRect(PreviewHwnd[i].Handle, out DxMediaFunction.DeviceInfo[i].dwPrvRect);
            }


            if (DxMediaFunction.NumCard > 0)
            {
                /////
                for (int i = 0; i < DxMediaFunction.NumCard; i++)
                {
                   
                       // DxMediaFunction.DeviceInfo[i].dwVidStandard = 32;
                        DxMediaFunction.DeviceInfo[i].dwColorspace = 2;
                      //  DxMediaFunction.DeviceInfo[i].dwWidth = 720;
                       // DxMediaFunction.DeviceInfo[i].dwHeight = 576;
                       // DxMediaFunction.DeviceInfo[i].dwFrameRate = 25;


                        // ////////////////////////////read the ini save value start////////////////////
                          //  //read ini file    video stream size
                          DxMediaFunction.IniFileSaveValue[i].iniWidthValue = DxSdkFunction.IniReadValue("VideoPar", "VideoWidth"+Convert.ToString(i), 20, DxMediaFunction.IniFileName);
                          DxMediaFunction.IniFileSaveValue[i].iniHeightValue = DxSdkFunction.IniReadValue("VideoPar", "VideoHeight" + Convert.ToString(i), 20, DxMediaFunction.IniFileName);
                          DxMediaFunction.DeviceInfo[i].dwWidth = Convert.ToInt32(DxMediaFunction.IniFileSaveValue[i].iniWidthValue);
                          DxMediaFunction.DeviceInfo[i].dwHeight = Convert.ToInt32(DxMediaFunction.IniFileSaveValue[i].iniHeightValue);


                          //  //read ini file    video standard  pal/ntsc
                     
                          DxMediaFunction.IniFileSaveValue[i].iniVideoStandard = DxSdkFunction.IniReadValue("VideoPar", "VideoStandard" + Convert.ToString(i), 20, DxMediaFunction.IniFileName);
                          if (DxMediaFunction.IniFileSaveValue[i].iniVideoStandard == "PAL")
                          {
                              //PAL= 0X20
                              DxMediaFunction.DeviceInfo[i].dwVidStandard = 32;
                              DxMediaFunction.DeviceInfo[i].dwFrameRate = 25;

                          }
                          else
                          {
                              //NTSC=0X01
                              DxMediaFunction.DeviceInfo[i].dwVidStandard = 1;
                              DxMediaFunction.DeviceInfo[i].dwFrameRate = 30;

                          }
                  
                        ////////////////////////////read the ini save value  end///////////////////////////////
                            //open the video device
                        DxMediaFunction.DeviceInfo[i].dwCardHandle = DxSdkFunction.OpenDevice(i, ref  DxMediaFunction.DeviceInfo[i].dwOpenDevState);
                            //connect the video device
                        DxMediaFunction.DeviceInfo[i].dwConnectState = DxSdkFunction.ConnectDev(DxMediaFunction.DeviceInfo[i].dwCardHandle,
                                                                                             DxMediaFunction.DeviceInfo[i].dwVidStandard,
                                                                                             DxMediaFunction.DeviceInfo[i].dwColorspace,
                                                                                             DxMediaFunction.DeviceInfo[i].dwWidth,
                                                                                              DxMediaFunction.DeviceInfo[i].dwHeight,
                                                                                             DxMediaFunction.DeviceInfo[i].dwFrameRate);

                        
                            //start video preview
                      DxMediaFunction.DeviceInfo[i].dwPrviewState = DxSdkFunction.StartPrview(DxMediaFunction.DeviceInfo[i].dwCardHandle,
                                                                                 DxMediaFunction.DeviceInfo[i].dwPrvHandle,
                                                                                 DxMediaFunction.DeviceInfo[i].dwPrvRect,
                                                                                 PreviewMode);

                            //set the video deinterlace 
                        DxMediaApi.DXEnableDeinterlace(DxMediaFunction.DeviceInfo[i].dwCardHandle, 0);
                      //set the video denoise
                      DxMediaApi.DXEnableDenoise(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, 65);

                     // DxMediaApi.DXEnableSharpen(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, 25);

                       
                        if ( DxMediaFunction.DeviceInfo[i].dwPrviewState!= 0)
                        {
                            MessageBox.Show("Start preview False");
                        }

                    }


                }











              
            else
            {
                MessageBox.Show("Init False, Please check the Card valid!");
            }


        }
        void MyMouseDb(object sender, MouseEventArgs e)
        {
            Panel PrvFrm = (Panel)sender;
            switch (PrvFrm.Name)
            {
                case "0":

                    break;
            }

        }
        void MyHwndClick(object sender, EventArgs e)
        {
            Panel PrvFrm = (Panel)sender;
             switch (PrvFrm.Name)
            {
               
              case "0":
                  nCard = 0;
                  DeviceNo.Text = "Channel" + "1";
                
                  break;
              case "1":
                  nCard = 1;
                  DeviceNo.Text = "Channel" + "2";
                
                  break;
              case "2":
                  nCard = 2;
                  DeviceNo.Text = "Channel" + "3";
                 
                  break;
              case "3":
                  nCard = 3;
                  DeviceNo.Text = "Channel" + "4";
                 
                  break;

            }

        }
        //定义预览窗体的双击事件，双击放大当前路，再双击回到4分屏状态
        void MyHwndDbClick(object sender, EventArgs e)
        {
              int k, j;
              Panel  PrvFrm = (Panel )sender;
              switch (PrvFrm.Name)
              {
                  case "0":
                          if (MaxFrmSn[0] == false)
                          {
                              PreviewHwnd[0].Width = this.Width - 130;
                              PreviewHwnd[0].Top = 10;
                              PreviewHwnd[0].Left  = 0;
                              PreviewHwnd[0].Height = this.Height - 40;
                              MaxFrmSn[0] = true;

                          }
                          else
                          {
                           
                              for (k = 0; k < m_nShowMode; k++)
                              {
                                  for (j = 0; j < m_nShowMode; j++)
                                  {
                                      nIndex = k * m_nShowMode + j;
                                      if (nIndex >= m_nWndNum)
                                      {
                                          break;
                                      }
                                      PreviewHwnd[nIndex].Left = PrvWidth * j;
                                      PreviewHwnd[nIndex].Top = PrvHeight * k;


                                  }

                              }
                              MaxFrmSn[0] = false ;
                            

                                 


                         }
                              if (MaxFrmSn[0] == false)
                              {
                                  PreviewHwnd[0].Width = PrvWidth;
                                  PreviewHwnd[0].Height = PrvHeight;
                              }
                              for (int i = 0; i < DxMediaFunction.NumCard; i++)
                              {
                                  if (DxMediaFunction.DeviceInfo[i].dwPrviewState == 0)
                                  {
                                      DxSdkFunction.StopPrview(DxMediaFunction.DeviceInfo[i].dwCardHandle);

                                  }
                                 
                               
                                  DxMediaApi.GetClientRect(PreviewHwnd[i].Handle, out DxMediaFunction.DeviceInfo[i].dwPrvRect);

                                  DxMediaFunction.DeviceInfo[i].dwPrviewState = DxSdkFunction.StartPrview(DxMediaFunction.DeviceInfo[i].dwCardHandle,
                                                                                             DxMediaFunction.DeviceInfo[i].dwPrvHandle,
                                                                                             DxMediaFunction.DeviceInfo[i].dwPrvRect,
                                                                                             PreviewMode);
                                  
                              }
                
                      break;
                  case "1":
                      if (MaxFrmSn[1] == false)
                      {
                          PreviewHwnd[1].Width = this.Width - 130;
                          PreviewHwnd[1].Top = 10;
                          PreviewHwnd[1].Left = 0;
                          PreviewHwnd[1].Height = this.Height - 40;
                          MaxFrmSn[1] = true;

                      }
                      else
                      {
                      
                          for (k = 0; k < m_nShowMode; k++)
                          {
                              for (j = 0; j < m_nShowMode; j++)
                              {
                                  nIndex = k * m_nShowMode + j;
                                  if (nIndex >= m_nWndNum)
                                  {
                                      break;
                                  }
                                  PreviewHwnd[nIndex].Left = PrvWidth * j;
                                  PreviewHwnd[nIndex].Top = PrvHeight * k;


                              }

                          }
                          MaxFrmSn[1] = false;
                         
                      }
                      if (MaxFrmSn[1] == false)
                      {
                          PreviewHwnd[1].Width = PrvWidth;
                          PreviewHwnd[1].Height = PrvHeight;
                      }
                      for (int i = 0; i < DxMediaFunction.NumCard; i++)
                      {
                          if (DxMediaFunction.DeviceInfo[i].dwPrviewState == 0)
                          {
                              DxSdkFunction.StopPrview(DxMediaFunction.DeviceInfo[i].dwCardHandle);

                          }

                          DxMediaApi.GetClientRect(PreviewHwnd[i].Handle, out DxMediaFunction.DeviceInfo[i].dwPrvRect);

                          DxMediaFunction.DeviceInfo[i].dwPrviewState = DxSdkFunction.StartPrview(DxMediaFunction.DeviceInfo[i].dwCardHandle,
                                                                                     DxMediaFunction.DeviceInfo[i].dwPrvHandle,
                                                                                     DxMediaFunction.DeviceInfo[i].dwPrvRect,
                                                                                     PreviewMode);




                      }
                      break;
                  case "2":
                      if (MaxFrmSn[2] == false)
                      {
                          PreviewHwnd[2].Width = this.Width - 130;
                          PreviewHwnd[2].Top = 10;
                          PreviewHwnd[2].Left = 0;
                          PreviewHwnd[2].Height = this.Height - 40;
                          MaxFrmSn[2] = true;

                      }
                      else
                      {
                        
                          for (k = 0; k < m_nShowMode; k++)
                          {
                              for (j = 0; j < m_nShowMode; j++)
                              {
                                  nIndex = k * m_nShowMode + j;
                                  if (nIndex >= m_nWndNum)
                                  {
                                      break;
                                  }
                                  PreviewHwnd[nIndex].Left = PrvWidth * j;
                                  PreviewHwnd[nIndex].Top = PrvHeight * k;


                              }

                          }
                          MaxFrmSn[2] = false;
                         
                      }
                      if (MaxFrmSn[2] == false)
                      {
                          PreviewHwnd[2].Width = PrvWidth;
                          PreviewHwnd[2].Height = PrvHeight;
                      }
                      for (int i = 0; i < DxMediaFunction.NumCard; i++)
                      {
                          if (DxMediaFunction.DeviceInfo[i].dwPrviewState == 0)
                          {
                              DxSdkFunction.StopPrview(DxMediaFunction.DeviceInfo[i].dwCardHandle);

                          }

                          DxMediaApi.GetClientRect(PreviewHwnd[i].Handle, out DxMediaFunction.DeviceInfo[i].dwPrvRect);

                          DxMediaFunction.DeviceInfo[i].dwPrviewState = DxSdkFunction.StartPrview(DxMediaFunction.DeviceInfo[i].dwCardHandle,
                                                                                     DxMediaFunction.DeviceInfo[i].dwPrvHandle,
                                                                                     DxMediaFunction.DeviceInfo[i].dwPrvRect,
                                                                                     PreviewMode);




                      }
                      break;
                  case "3":
                      if (MaxFrmSn[0] == false)
                      {
                          PreviewHwnd[3].Width = this.Width - 130;
                          PreviewHwnd[3].Top = 10;
                          PreviewHwnd[3].Left =0;
                          PreviewHwnd[3].Height = this.Height - 40;
                          MaxFrmSn[3] = true;

                      }
                      else
                      {
                       
                          for (k = 0; k < m_nShowMode; k++)
                          {
                              for (j = 0; j < m_nShowMode; j++)
                              {
                                  nIndex = k * m_nShowMode + j;
                                  if (nIndex >= m_nWndNum)
                                  {
                                      break;
                                  }
                                  PreviewHwnd[nIndex].Left = PrvWidth * j;
                                  PreviewHwnd[nIndex].Top = PrvHeight * k;


                              }

                          }
                          MaxFrmSn[3] = false;
                        
                      }
                      if (MaxFrmSn[3] == false)
                      {
                          PreviewHwnd[3].Width = PrvWidth;
                          PreviewHwnd[3].Height = PrvHeight;
                      }
                      for (int i = 0; i < DxMediaFunction.NumCard; i++)
                      {
                          if (DxMediaFunction.DeviceInfo[i].dwPrviewState == 0)
                          {
                              DxSdkFunction.StopPrview(DxMediaFunction.DeviceInfo[i].dwCardHandle);

                          }

                          DxMediaApi.GetClientRect(PreviewHwnd[i].Handle, out DxMediaFunction.DeviceInfo[i].dwPrvRect);

                          DxMediaFunction.DeviceInfo[i].dwPrviewState = DxSdkFunction.StartPrview(DxMediaFunction.DeviceInfo[i].dwCardHandle,
                                                                                     DxMediaFunction.DeviceInfo[i].dwPrvHandle,
                                                                                     DxMediaFunction.DeviceInfo[i].dwPrvRect,
                                                                                     PreviewMode);




                      }
                      break;


              }
        }

       

        private void btSnap_Click(object sender, EventArgs e)
        {
            string SaveFile;
          
             if(DxMediaFunction.DeviceInfo [nCard].dwOpenDevState ==0)
            {

                DxMediaFunction.DeviceInfo[nCard].dwSnapPicRect.Top = 0;
                DxMediaFunction.DeviceInfo[nCard].dwSnapPicRect.Left = 0;
                DxMediaFunction.DeviceInfo[nCard].dwSnapPicRect.Bottom = DxMediaFunction.DeviceInfo[nCard].dwHeight;
                DxMediaFunction.DeviceInfo[nCard].dwSnapPicRect.Right = DxMediaFunction.DeviceInfo[nCard].dwWidth;
                
                //create the snap picture file name
                SaveFile = DxSdkFunction.CreateFileName(nCard, ".bmp", DxMediaFunction.PicSavePath +"\\");
                //snap the picture to bmp file
                DxSdkFunction.SnapPicture(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, SaveFile, 0, DxMediaFunction.DeviceInfo[nCard].dwSnapPicRect);

                SaveFile = DxSdkFunction.CreateFileName(nCard, ".jpg", DxMediaFunction.PicSavePath + "\\");
               //snap the picture to bmp file
                DxSdkFunction.SnapPicture(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, SaveFile, 1, DxMediaFunction.DeviceInfo[nCard].dwSnapPicRect);
                MessageBox.Show("Snap ok" + SaveFile);
            }
           
           
           




        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            OsdSetting OsdSetFrom = new OsdSetting();
            //show the osd setting form 
            OsdSetFrom.ShowDialog();
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void btExit_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < DxMediaFunction.NumCard; i++)
            {
                //stop thet video prview
                if (DxMediaFunction.DeviceInfo[i].dwPrviewState == 0)
                {
                    DxSdkFunction.StopPrview(DxMediaFunction.DeviceInfo[i].dwCardHandle);

                }
                //disconnect then device
                if (DxMediaFunction.DeviceInfo[i].dwConnectState == true)
                {
                    DxSdkFunction.DisConnectDev(DxMediaFunction.DeviceInfo[i].dwCardHandle);

                }
                if (DxMediaFunction.DeviceInfo[i].dwOpenDevState  == 0)
                {
                    DxSdkFunction.CloseDevice(DxMediaFunction.DeviceInfo[i].dwCardHandle);

                }



            }

            // uninit the sdk function
            DxMediaApi.DXUninitialize();

            // exit the application 
            Application.Exit();

        }

        private void colorSetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //open the video color property dialog box
            ColorSetting ColorSetFrom = new ColorSetting();
            ColorSetFrom.Show();
        }

        private void btGetCurBuf_Click(object sender, EventArgs e)
        {


            string SaveFile;

          
            //create the snap picture file name
            SaveFile = DxSdkFunction.CreateFileName(nCard, ".bmp", DxMediaFunction.PicSavePath + "\\");

            //Marshal.AllocHGlobal 
            if (DxMediaFunction.DeviceInfo[nCard].dwOpenDevState == 0)
            {
              

                //get the device  property
                DxMediaApi.DXGetVideoPara(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                            ref DxMediaFunction.DeviceInfo[nCard].dwVidStandard,
                                            ref DxMediaFunction.DeviceInfo[nCard].dwColorspace,
                                            ref DxMediaFunction.DeviceInfo[nCard].dwWidth,
                                            ref DxMediaFunction.DeviceInfo[nCard].dwHeight,
                                            ref DxMediaFunction.DeviceInfo[nCard].dwFrameRate);
               int BufSize = DxMediaFunction.DeviceInfo[nCard].dwWidth * DxMediaFunction.DeviceInfo[nCard].dwHeight * 2;
                IntPtr pBuf = Marshal.AllocHGlobal(BufSize);
                BufSize = DxMediaFunction.DeviceInfo[nCard].dwWidth * DxMediaFunction.DeviceInfo[nCard].dwHeight * 3;
                IntPtr RgbBuf = Marshal.AllocHGlobal(BufSize);

                //set the snap rect
                DxMediaFunction.DeviceInfo[nCard].dwSnapPicRect.Left = 0;
                DxMediaFunction.DeviceInfo[nCard].dwSnapPicRect.Top = 0;
                DxMediaFunction.DeviceInfo[nCard].dwSnapPicRect.Right = DxMediaFunction.DeviceInfo[nCard].dwWidth;
                DxMediaFunction.DeviceInfo[nCard].dwSnapPicRect.Bottom = DxMediaFunction.DeviceInfo[nCard].dwHeight;
                //get the cur buf( yuv2 stream type)
                DxMediaApi.DXGetFrameBuffer(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 
                                            pBuf, 
                                            BufSize,
                                            ref gotBufferLen,
                                            ref colorSpace,
                                            ref nWidth,
                                            ref  nHeight,
                                            ref BytesWidth,
                                            ref DxMediaFunction.DeviceInfo[nCard].dwSnapPicRect);

                //Convert yuv2 to rgb24

                DxMediaApi.DXConvertYUVtoRGB(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                            pBuf,
                                            RgbBuf,
                                            nWidth,
                                            nHeight,
                                            false,
                                            false);
                byte[] pData = new byte[BufSize];
                Marshal.Copy(RgbBuf, pData, 0, pData.Length);
                // DxSdkFunction.SaveBmpToFile(pData, nWidth, nHeight, SaveFile);
                //save the cur buf to bmp file
                DxMediaApi.DXSaveBMPFile(SaveFile, pBuf, gotBufferLen, colorSpace, nWidth, nHeight, BytesWidth);
                SaveFile = DxSdkFunction.CreateFileName(nCard, ".jpg", DxMediaFunction.PicSavePath + "\\");
               DxMediaApi.DXSaveJPGFile(SaveFile, pBuf, gotBufferLen, colorSpace, nWidth, nHeight, BytesWidth, 100);
                MessageBox.Show("Snap jpg ok: " + SaveFile);
            }
        }

      
        private void btRecord_Click(object sender, EventArgs e)
        {

            string SaveVideoFile;

            //create the save file name
            SaveVideoFile = DxSdkFunction.CreateFileName(nCard, ".avi", DxMediaFunction.RecSavePath + "\\");
            

           
          
           
           
            
            if (DxMediaFunction.DeviceInfo[nCard].dwOpenDevState == 0)
            {
                //get the device  property
                DxMediaApi.DXGetVideoPara(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                            ref DxMediaFunction.DeviceInfo[nCard].dwVidStandard,
                                            ref DxMediaFunction.DeviceInfo[nCard].dwColorspace,
                                            ref DxMediaFunction.DeviceInfo[nCard].dwWidth,
                                            ref DxMediaFunction.DeviceInfo[nCard].dwHeight,
                                            ref DxMediaFunction.DeviceInfo[nCard].dwFrameRate);

                if (DxMediaFunction.DeviceInfo[nCard].dwRecOK == false)
                {
                    
                    if (DxMediaFunction.DeviceInfo[nCard].dwVideoCodecStr == "x264 Codec")
                    {
                         //set h264 codec property
                        DxMediaFunction.DeviceInfo[nCard].dwVideoCodecpara.Bitrate = 0;
                        DxMediaFunction.DeviceInfo[nCard].dwVideoCodecpara.fps = (int)DxMediaFunction.DeviceInfo[nCard].dwFrameRate;
                        DxMediaFunction.DeviceInfo[nCard].dwVideoCodecpara.keyframeinterval = 110;
                        DxMediaFunction.DeviceInfo[nCard].dwVideoCodecpara.rcMode = DxMediaApi.TCodecMode.codec_VBR;
                        DxMediaFunction.DeviceInfo[nCard].dwVideoCodecpara.Maxrbps = 4000;
                        DxMediaFunction.DeviceInfo[nCard].dwVideoCodecpara.Peekbps = 2000;
                        DxMediaFunction.DeviceInfo[nCard].dwVideoCodecpara.Quality = 8;
                     SaveVideoFile = DxSdkFunction.CreateFileName(nCard, ".mp4", DxMediaFunction.RecSavePath + "\\");
                    }

                    if (DxMediaFunction.DeviceInfo[nCard].dwVideoCodecStr == "xvid Codec")
                    {
                         //set xvid codec property
                        DxMediaFunction.DeviceInfo[nCard].dwVideoCodecpara.Bitrate = 1280;
                        DxMediaFunction.DeviceInfo[nCard].dwVideoCodecpara.fps = (int)DxMediaFunction.DeviceInfo[nCard].dwFrameRate;
                        DxMediaFunction.DeviceInfo[nCard].dwVideoCodecpara.keyframeinterval = 110;
                        DxMediaFunction.DeviceInfo[nCard].dwVideoCodecpara.rcMode = DxMediaApi.TCodecMode.codec_VBR;
                        DxMediaFunction.DeviceInfo[nCard].dwVideoCodecpara.Quality = 4;
                    SaveVideoFile = DxSdkFunction.CreateFileName(nCard, ".avi", DxMediaFunction.RecSavePath + "\\");

                 }
                   
                    //start recording
                    DxSdkFunction.StartRecord(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 
                                                SaveVideoFile,
                                                DxMediaFunction.DeviceInfo[nCard].dwVideoCodecStr,
                                               DxMediaFunction.DeviceInfo[nCard].dwVideoCodecpara,
                                               false);
                                        

                    btRecord.Text = "Stop Rec";
                    DxMediaFunction.DeviceInfo[nCard].dwRecOK = true;

                }
                else
                {
                    //stop recording
                    DxSdkFunction.StopRecord(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);
                    btRecord.Text = "Record";
                    DxMediaFunction.DeviceInfo[nCard].dwRecOK = false;
                    MessageBox.Show("Record ok" + SaveVideoFile);

                }

               

            }
        }





        

        private void btCodecSet_Click(object sender, EventArgs e)
        {
            //Open the video codec setting dialog box
            CodecSetFrm CodecSetForm = new CodecSetFrm();
            CodecSetForm.Show();
        }

        private void btPauseRec_Click(object sender, EventArgs e)
        {
           
            if (DxMediaFunction.DeviceInfo [nCard].dwOpenDevState == 0)
            {
               
                    if ((DxMediaFunction.DeviceInfo [nCard].dwRecOK == true)&&(DxMediaFunction.DeviceInfo [nCard].dwFreezeRecOK == false))
                    {

                        DxSdkFunction.FreezeRecord(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,true);
                         btPauseRec.Text = "CancelPause";
                         DxMediaFunction.DeviceInfo [nCard].dwFreezeRecOK  = true;
                    }
                    else
                    {
                         DxSdkFunction.FreezeRecord(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,false);
                        btPauseRec.Text = "Pause Rec";
                        DxMediaFunction.DeviceInfo [nCard].dwFreezeRecOK  = false;
                    }
            
            
            }

        }

        private void btCallBack_Click(object sender, EventArgs e)
        {
            if (DxMediaFunction.DeviceInfo [nCard].dwOpenDevState == 0)
            {
                if (DxMediaFunction.DeviceInfo [nCard].dwRawCallOk == false)
                {

                    DxMediaApi.DXStartRawVideoCallback(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, SnapCall,(IntPtr) nCard);
                    btCallBack.Text = "StopCall";
                    DxMediaFunction.DeviceInfo [nCard].dwRawCallOk  = true;

                }
                else
                {
                    DxMediaApi.DXStopRawVideoCallback(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);
                    btCallBack.Text = "CallBack";
                    DxMediaFunction.DeviceInfo [nCard].dwRawCallOk  = false;
                }




            }
        }

        private void btCallSnap_Click(object sender, EventArgs e)
        {
            if (DxMediaFunction.DeviceInfo [nCard].dwRawCallOk  == false)
            {
                MessageBox.Show("please start the raw data callback!");
            }
            else
            {
                DxMediaFunction.DeviceInfo [nCard].dwSnapOK = true;
            }
        }

       




        private void PrvHwnd_Paint(object sender, PaintEventArgs e)
        {

        }

        private void AV1MenuItem_Click(object sender, EventArgs e)
        {
             if (DxMediaFunction.DeviceInfo [nCard].dwOpenDevState == 0)
            {
                DxMediaApi.DXSetVideoSource(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 1);
                AV1MenuItem.Checked = true;
                AV2MenuItem.Checked = false;
                SVIDEOMenuItem.Checked = false;
            }
        }

        private void AV2MenuItem_Click(object sender, EventArgs e)
        {
            if (DxMediaFunction.DeviceInfo [nCard].dwOpenDevState == 0)
            {
                DxMediaApi.DXSetVideoSource(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 2);
                AV1MenuItem.Checked = true;
                AV2MenuItem.Checked = false;
                SVIDEOMenuItem.Checked = false;
            }
        }

        private void SVIDEOMenuItem_Click(object sender, EventArgs e)
        {
             if (DxMediaFunction.DeviceInfo [nCard].dwOpenDevState == 0)
            {
                DxMediaApi.DXSetVideoSource(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 3);
                AV1MenuItem.Checked = true;
                AV2MenuItem.Checked = false;
                SVIDEOMenuItem.Checked = false;
            }
        }

        private void D1MenuItem_Click(object sender, EventArgs e)
        {


            D1MenuItem.Checked = true;
            MenuItem768.Checked = false;
            MenuItemCif.Checked = false;

            if (DxMediaFunction.DeviceInfo[nCard].dwOpenDevState == 0)
            {
                if (DxMediaFunction.DeviceInfo[nCard].dwVidStandard == 32)
                {
                    if (DxMediaFunction.DeviceInfo[nCard].dwWidth != 720)
                    {
                        if (DxMediaFunction.DeviceInfo[nCard].dwPrviewState == 0)
                        {
                            DxSdkFunction.StopPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                        }
                        if (DxMediaFunction.DeviceInfo[nCard].dwConnectState == true)
                        {
                            DxSdkFunction.DisConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                        }
                        DxMediaFunction.DeviceInfo[nCard].dwWidth = 720;
                        DxMediaFunction.DeviceInfo[nCard].dwHeight = 576;
                        DxMediaFunction.DeviceInfo[nCard].dwConnectState = DxSdkFunction.ConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwVidStandard,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwColorspace,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwWidth,
                                                                                         DxMediaFunction.DeviceInfo[nCard].dwHeight,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwFrameRate);



                        DxMediaFunction.DeviceInfo[nCard].dwPrviewState = DxSdkFunction.StartPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                             DxMediaFunction.DeviceInfo[nCard].dwPrvHandle,
                                                                             DxMediaFunction.DeviceInfo[nCard].dwPrvRect,
                                                                             PreviewMode);

                        DxMediaApi.DXEnableDeinterlace(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 2);



                    }

                }
                else
                {
                    if (DxMediaFunction.DeviceInfo[nCard].dwWidth != 720)
                    {
                        if (DxMediaFunction.DeviceInfo[nCard].dwPrviewState == 0)
                        {
                            DxSdkFunction.StopPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                        }
                        if (DxMediaFunction.DeviceInfo[nCard].dwConnectState == true)
                        {
                            DxSdkFunction.DisConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                        }
                        DxMediaFunction.DeviceInfo[nCard].dwWidth = 720;
                        DxMediaFunction.DeviceInfo[nCard].dwHeight = 480;
                        DxMediaFunction.DeviceInfo[nCard].dwConnectState = DxSdkFunction.ConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwVidStandard,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwColorspace,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwWidth,
                                                                                         DxMediaFunction.DeviceInfo[nCard].dwHeight,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwFrameRate);



                        DxMediaFunction.DeviceInfo[nCard].dwPrviewState = DxSdkFunction.StartPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                             DxMediaFunction.DeviceInfo[nCard].dwPrvHandle,
                                                                             DxMediaFunction.DeviceInfo[nCard].dwPrvRect,
                                                                             PreviewMode);

                        DxMediaApi.DXEnableDeinterlace(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 1);



                    }
                }


                //write video stream size to ini file
                DxMediaApi.WritePrivateProfileString("VideoPar", "VideoWidth" + Convert.ToString(nCard), Convert.ToString(DxMediaFunction.DeviceInfo[nCard].dwWidth), DxMediaFunction.IniFileName);
                DxMediaApi.WritePrivateProfileString("VideoPar", "VideoHeight" + Convert.ToString(nCard), Convert.ToString(DxMediaFunction.DeviceInfo[nCard].dwHeight), DxMediaFunction.IniFileName);
            }
        }







        private void AV1MenuItem_Click_1(object sender, EventArgs e)
        {
            if (DxMediaFunction.DeviceInfo[nCard].dwOpenDevState == 0)
            {
                DxMediaApi.DXSetVideoSource(DxMediaFunction.DeviceInfo[nCard].dwCardHandle ,1);
                AV1MenuItem.Checked = true;
                AV2MenuItem.Checked = false;
                SVIDEOMenuItem.Checked = false;
            }
        }

        private void VideoDevMenu_Click(object sender, EventArgs e)
        {
            
        }

      

        private void AV2MenuItem_Click_1(object sender, EventArgs e)
        {
          if (DxMediaFunction.DeviceInfo[nCard].dwOpenDevState == 0)
            {
                DxMediaApi.DXSetVideoSource(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 2);
                AV1MenuItem.Checked = false;
                AV2MenuItem.Checked = true;
                SVIDEOMenuItem.Checked = false;
            }
        }

        private void SVIDEOMenuItem_Click_1(object sender, EventArgs e)
        {
            if (DxMediaFunction.DeviceInfo[nCard].dwOpenDevState == 0)
            {
                DxMediaApi.DXSetVideoSource(DxMediaFunction.DeviceInfo[nCard].dwCardHandle ,3);
                AV1MenuItem.Checked = false;
                AV2MenuItem.Checked = false;
                SVIDEOMenuItem.Checked = true;
            }
        }

        private void flipVideoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (DxMediaFunction.DeviceInfo[nCard].dwFlipVideoEnable == false)
            {
                flipVideoToolStripMenuItem.Checked = true;
                DxMediaApi.DXFlipVideo(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, true);
                DxMediaFunction.DeviceInfo[nCard].dwFlipVideoEnable = true;
            }
            else
            {
                flipVideoToolStripMenuItem.Checked = false;
                DxMediaApi.DXFlipVideo( DxMediaFunction.DeviceInfo[nCard].dwCardHandle, false);
                DxMediaFunction.DeviceInfo[nCard].dwFlipVideoEnable = false;
            }

        }

        private void mirrorVideoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (DxMediaFunction.DeviceInfo[nCard].dwMirrorVideoEnable == false)
            {
                mirrorVideoToolStripMenuItem.Checked = true;
                DxMediaApi.DXMirrorVideo(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, true);
                DxMediaFunction.DeviceInfo[nCard].dwMirrorVideoEnable = true;
            }
            else
            {
                mirrorVideoToolStripMenuItem.Checked = false;
                DxMediaApi.DXMirrorVideo(DxMediaFunction.DeviceInfo[nCard].dwCardHandle , false);
               DxMediaFunction.DeviceInfo[nCard].dwMirrorVideoEnable = false;
            }

        }

        private void beToolStripMenuItem_Click(object sender, EventArgs e)
        {
            standardMenuItem.Checked = false;
            goodMenuItem.Checked = false;
            bestMenuItem.Checked = true;
            cancelMenuItem.Checked = false;
            DxMediaApi.DXEnableDeinterlace(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 2);
        }

        private void stanToolStripMenuItem_Click(object sender, EventArgs e)
        {
            standardMenuItem.Checked = true;
            goodMenuItem.Checked = false;
            bestMenuItem.Checked = false;
            cancelMenuItem.Checked = false;
            DxMediaApi.DXEnableDeinterlace(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 0);
        }

        private void goodMenuItem_Click(object sender, EventArgs e)
        {
            standardMenuItem.Checked = false;
            goodMenuItem.Checked = true;
            bestMenuItem.Checked = false;
            cancelMenuItem.Checked = false;
            DxMediaApi.DXEnableDeinterlace(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 1);
        }

        private void cancelMenuItem_Click(object sender, EventArgs e)
        {
            standardMenuItem.Checked = false;
            goodMenuItem.Checked = false;
            bestMenuItem.Checked = false;
            cancelMenuItem.Checked = true;
            DxMediaApi.DXEnableDeinterlace(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,4);
        }

        private void deinterlaceToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void denoiseToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DenoiseSetting VideoDenoise = new DenoiseSetting();
            VideoDenoise.Show();
        }

      

        private void fToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int k;
            int j;
            for (int i = 0; i < 4; i++)
            {
                PreviewHwnd[i].Width = PrvWidth;
                PreviewHwnd[i].Height = PrvHeight;
            }
            for (k = 0; k < m_nShowMode; k++)
            {
                for (j = 0; j < m_nShowMode; j++)
                {
                    nIndex = k * m_nShowMode + j;
                    if (nIndex >= m_nWndNum)
                    {
                        break;
                    }
                    PreviewHwnd[nIndex].Left = PrvWidth * j;
                    PreviewHwnd[nIndex].Top = PrvHeight * k;


                }

            }
            /*
            for (int i = 0; i < 4; i++)
            {


              //  if (PreviewOK[i] == 0)
                {
                    DxMediaApi.DXStopPreview(DxMediaFunction.CardHandle[i]);
                    PreviewOK[i] = 1;
                }
                DxMediaApi.GetClientRect(PreviewHwnd[i].Handle, out DxMediaFunction.PrvRect[i]);
                DxMediaApi.DXStartPreview(DxMediaFunction.CardHandle[i], PreviewHwnd[i].Handle, ref  DxMediaFunction.PrvRect[i], 0);
                MaxFrmSn[nCard] = false;
            }*/

        }

       

      

     
     


      

        private void pALToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //write video standard  to ini file
         //   DxMediaApi.WritePrivateProfileString("VideoPar", "VideoStandard"+Convert.ToString(Form1.nCard ), "PAL", DxMediaFunction.IniFileName);
            
                   
            
            nTSCToolStripMenuItem.Checked = false;
            pALToolStripMenuItem.Checked = true;

            if(DxMediaFunction.DeviceInfo[nCard].dwVidStandard!=0x20)
            {
                if (DxMediaFunction.DeviceInfo[nCard].dwPrviewState == 0)
                {
                    DxSdkFunction.StopPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                }
                if (DxMediaFunction.DeviceInfo[nCard].dwConnectState == true)
                {
                    DxSdkFunction.DisConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                }
                DxMediaFunction.DeviceInfo[nCard].dwVidStandard = 0x20;
                DxMediaFunction.DeviceInfo[nCard].dwFrameRate = 25;
                DxMediaFunction.DeviceInfo[nCard].dwConnectState = DxSdkFunction.ConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                                DxMediaFunction.DeviceInfo[nCard].dwVidStandard,
                                                                                DxMediaFunction.DeviceInfo[nCard].dwColorspace,
                                                                                DxMediaFunction.DeviceInfo[nCard].dwWidth,
                                                                                 DxMediaFunction.DeviceInfo[nCard].dwHeight,
                                                                                DxMediaFunction.DeviceInfo[nCard].dwFrameRate);



                DxMediaFunction.DeviceInfo[nCard].dwPrviewState = DxSdkFunction.StartPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                     DxMediaFunction.DeviceInfo[nCard].dwPrvHandle,
                                                                     DxMediaFunction.DeviceInfo[nCard].dwPrvRect,
                                                                     PreviewMode);

                DxMediaApi.DXEnableDeinterlace(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 1);



            }

            //write video stream size to ini file
            DxMediaApi.WritePrivateProfileString("VideoPar", "VideoWidth" + Convert.ToString(nCard), Convert.ToString(DxMediaFunction.DeviceInfo[nCard].dwWidth), DxMediaFunction.IniFileName);
            DxMediaApi.WritePrivateProfileString("VideoPar", "VideoHeight" + Convert.ToString(nCard), Convert.ToString(DxMediaFunction.DeviceInfo[nCard].dwHeight), DxMediaFunction.IniFileName);
            DxMediaApi.WritePrivateProfileString("VideoPar", "VideoStandard" + Convert.ToString(Form1.nCard), "PAL", DxMediaFunction.IniFileName);

           
        }

        private void nTSCToolStripMenuItem_Click_1(object sender, EventArgs e)
        {

            //write video standard  to ini file
           



            nTSCToolStripMenuItem.Checked = true;
            pALToolStripMenuItem.Checked = false;

            if (DxMediaFunction.DeviceInfo[nCard].dwVidStandard != 0x01);
            {
                if (DxMediaFunction.DeviceInfo[nCard].dwPrviewState == 0)
                {
                    DxSdkFunction.StopPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                }
                if (DxMediaFunction.DeviceInfo[nCard].dwConnectState == true)
                {
                    DxSdkFunction.DisConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                }
                if (DxMediaFunction.DeviceInfo[nCard].dwHeight > 480)
                {
                    DxMediaFunction.DeviceInfo[nCard].dwHeight = 480;
                }
                DxMediaFunction.DeviceInfo[nCard].dwVidStandard = 0x01;
                DxMediaFunction.DeviceInfo[nCard].dwFrameRate = 30;
                DxMediaFunction.DeviceInfo[nCard].dwConnectState = DxSdkFunction.ConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                                DxMediaFunction.DeviceInfo[nCard].dwVidStandard,
                                                                                DxMediaFunction.DeviceInfo[nCard].dwColorspace,
                                                                                DxMediaFunction.DeviceInfo[nCard].dwWidth,
                                                                                 DxMediaFunction.DeviceInfo[nCard].dwHeight,
                                                                                DxMediaFunction.DeviceInfo[nCard].dwFrameRate);



                DxMediaFunction.DeviceInfo[nCard].dwPrviewState = DxSdkFunction.StartPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                     DxMediaFunction.DeviceInfo[nCard].dwPrvHandle,
                                                                     DxMediaFunction.DeviceInfo[nCard].dwPrvRect,
                                                                     PreviewMode);

                DxMediaApi.DXEnableDeinterlace(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 0);

                //write video stream size to ini file
                DxMediaApi.WritePrivateProfileString("VideoPar", "VideoWidth" + Convert.ToString(nCard), Convert.ToString(DxMediaFunction.DeviceInfo[nCard].dwWidth), DxMediaFunction.IniFileName);
                DxMediaApi.WritePrivateProfileString("VideoPar", "VideoHeight" + Convert.ToString(nCard), Convert.ToString(DxMediaFunction.DeviceInfo[nCard].dwHeight), DxMediaFunction.IniFileName);
                DxMediaApi.WritePrivateProfileString("VideoPar", "VideoStandard" + Convert.ToString(Form1.nCard), "NTSC", DxMediaFunction.IniFileName);


            }


           


        }

        private void MenuItemvga_Click(object sender, EventArgs e)
        {

            D1MenuItem.Checked = false;
            MenuItem768.Checked = true;
            MenuItemCif.Checked = false;

            if (DxMediaFunction.DeviceInfo[nCard].dwOpenDevState == 0)
            {
                if (DxMediaFunction.DeviceInfo[nCard].dwVidStandard == 32)
                {
                    if (DxMediaFunction.DeviceInfo[nCard].dwWidth != 768)
                    {
                        if (DxMediaFunction.DeviceInfo[nCard].dwPrviewState == 0)
                        {
                            DxSdkFunction.StopPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                        }
                        if (DxMediaFunction.DeviceInfo[nCard].dwConnectState == true)
                        {
                            DxSdkFunction.DisConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                        }
                        DxMediaFunction.DeviceInfo[nCard].dwWidth = 768;
                        DxMediaFunction.DeviceInfo[nCard].dwHeight = 576;
                        DxMediaFunction.DeviceInfo[nCard].dwConnectState = DxSdkFunction.ConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwVidStandard,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwColorspace,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwWidth,
                                                                                         DxMediaFunction.DeviceInfo[nCard].dwHeight,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwFrameRate);



                        DxMediaFunction.DeviceInfo[nCard].dwPrviewState = DxSdkFunction.StartPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                             DxMediaFunction.DeviceInfo[nCard].dwPrvHandle,
                                                                             DxMediaFunction.DeviceInfo[nCard].dwPrvRect,
                                                                             PreviewMode);

                        DxMediaApi.DXEnableDeinterlace(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 0);



                    }

                }
                else
                {
                    if (DxMediaFunction.DeviceInfo[nCard].dwWidth != 768)
                    {
                        if (DxMediaFunction.DeviceInfo[nCard].dwPrviewState == 0)
                        {
                            DxSdkFunction.StopPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                        }
                        if (DxMediaFunction.DeviceInfo[nCard].dwConnectState == true)
                        {
                            DxSdkFunction.DisConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                        }
                        DxMediaFunction.DeviceInfo[nCard].dwWidth = 768;
                        DxMediaFunction.DeviceInfo[nCard].dwHeight = 480;
                        DxMediaFunction.DeviceInfo[nCard].dwConnectState = DxSdkFunction.ConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwVidStandard,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwColorspace,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwWidth,
                                                                                         DxMediaFunction.DeviceInfo[nCard].dwHeight,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwFrameRate);



                        DxMediaFunction.DeviceInfo[nCard].dwPrviewState = DxSdkFunction.StartPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                             DxMediaFunction.DeviceInfo[nCard].dwPrvHandle,
                                                                             DxMediaFunction.DeviceInfo[nCard].dwPrvRect,
                                                                             PreviewMode);

                        DxMediaApi.DXEnableDeinterlace(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 1);



                    }
                }

                //write video stream size to ini file
                DxMediaApi.WritePrivateProfileString("VideoPar", "VideoWidth" + Convert.ToString(nCard ), Convert.ToString(DxMediaFunction.DeviceInfo[nCard].dwWidth), DxMediaFunction.IniFileName);
                DxMediaApi.WritePrivateProfileString("VideoPar", "VideoHeight"+ Convert.ToString(nCard ), Convert.ToString(DxMediaFunction.DeviceInfo[nCard].dwHeight), DxMediaFunction.IniFileName);
            }

        }

        private void MenuItemCif_Click(object sender, EventArgs e)
        {

            D1MenuItem.Checked = false;
            MenuItem768.Checked = false;
            MenuItemCif.Checked = true;

            if (DxMediaFunction.DeviceInfo[nCard].dwOpenDevState == 0)
            {
              
                    if (DxMediaFunction.DeviceInfo[nCard].dwWidth != 352)
                    {
                        if (DxMediaFunction.DeviceInfo[nCard].dwPrviewState == 0)
                        {
                            DxSdkFunction.StopPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                        }
                        if (DxMediaFunction.DeviceInfo[nCard].dwConnectState == true)
                        {
                            DxSdkFunction.DisConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle);

                        }
                        DxMediaFunction.DeviceInfo[nCard].dwWidth = 352;
                        DxMediaFunction.DeviceInfo[nCard].dwHeight = 288;
                        DxMediaFunction.DeviceInfo[nCard].dwConnectState = DxSdkFunction.ConnectDev(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwVidStandard,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwColorspace,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwWidth,
                                                                                         DxMediaFunction.DeviceInfo[nCard].dwHeight,
                                                                                        DxMediaFunction.DeviceInfo[nCard].dwFrameRate);



                        DxMediaFunction.DeviceInfo[nCard].dwPrviewState = DxSdkFunction.StartPrview(DxMediaFunction.DeviceInfo[nCard].dwCardHandle,
                                                                             DxMediaFunction.DeviceInfo[nCard].dwPrvHandle,
                                                                             DxMediaFunction.DeviceInfo[nCard].dwPrvRect,
                                                                             PreviewMode);

                        DxMediaApi.DXEnableDeinterlace(DxMediaFunction.DeviceInfo[nCard].dwCardHandle, 0);



                    }

                }
              
                


                //write video stream size to ini file
                DxMediaApi.WritePrivateProfileString("VideoPar", "VideoWidth" + Convert.ToString(nCard), Convert.ToString(DxMediaFunction.DeviceInfo[nCard].dwWidth), DxMediaFunction.IniFileName);
                DxMediaApi.WritePrivateProfileString("VideoPar", "VideoHeight" + Convert.ToString(nCard), Convert.ToString(DxMediaFunction.DeviceInfo[nCard].dwHeight), DxMediaFunction.IniFileName);
            
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            for (int i = 0; i < DxMediaFunction.NumCard; i++)
            {

                if (DxMediaFunction.DeviceInfo[i].dwPrviewState == 0)
                {
                    DxSdkFunction.StopPrview(DxMediaFunction.DeviceInfo[i].dwCardHandle);

                }
                if (DxMediaFunction.DeviceInfo[i].dwConnectState == true)
                {
                    DxSdkFunction.DisConnectDev(DxMediaFunction.DeviceInfo[i].dwCardHandle);

                }
                if (DxMediaFunction.DeviceInfo[i].dwOpenDevState == 0)
                {
                    DxSdkFunction.CloseDevice(DxMediaFunction.DeviceInfo[i].dwCardHandle);

                }



            }


            DxMediaApi.DXUninitialize();

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            DxMediaApi.WritePrivateProfileString("SystemSetting", "PreviewMode", "VMR7", DxMediaFunction.IniFileName);
        }

        private void radiooffscrean_CheckedChanged(object sender, EventArgs e)
        {
            DxMediaApi.WritePrivateProfileString("SystemSetting", "PreviewMode", "OFFscream", DxMediaFunction.IniFileName);
        }

        private void radiovmr9_CheckedChanged(object sender, EventArgs e)
        {
            DxMediaApi.WritePrivateProfileString("SystemSetting", "PreviewMode", "VMR9", DxMediaFunction.IniFileName);
        }

        private void btZoom_Click(object sender, EventArgs e)
        {

            FrmDigitalZoom DigZoomFrm = new FrmDigitalZoom();
            //show  setting form 
            DigZoomFrm.ShowDialog();
        }




            ///////////////

    
           

          
    }
}

       
    

