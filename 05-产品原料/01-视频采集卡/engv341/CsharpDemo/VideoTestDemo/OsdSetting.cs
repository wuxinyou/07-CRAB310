using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace VideoTestDemo
{
    public partial class OsdSetting : Form
    {
        public int BackColor;
        DxMediaApi.TosdInfo [] TosdInfoVal = new DxMediaApi.TosdInfo[16];
        DxMediaFunction DxSdkFunction = new DxMediaFunction();
       
        public OsdSetting()
        {
            InitializeComponent();
        }

        private void btBrowse_Click(object sender, EventArgs e)
        {
           // string PicPathFile = "";


            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            //define open default path 
            openFileDialog1.InitialDirectory = "D://";
            //define open file type
            openFileDialog1.Filter = "All files (*.*)|*.*|bmp files (*.bmp)|*.bmp";
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.RestoreDirectory = true;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
                TosdInfoVal[1].PicOsdFile = openFileDialog1.FileName;

            TxtPicPath.Text = TosdInfoVal[1].PicOsdFile;
            DxMediaApi.WritePrivateProfileString("OSDPar", "OsdPicFile", TosdInfoVal[1].PicOsdFile, DxMediaFunction.IniFileName);
        }

        private void btTimeFontColor_Click(object sender, EventArgs e)
        {
           
            colorDialog1.ShowDialog();
            TosdInfoVal[1].TimeColor = ColorTranslator.ToWin32(colorDialog1.Color);
        }

        private void OsdSetting_Load(object sender, EventArgs e)
        {
            
            //////////////read ini setting value/////////////////////

            string TimeOsdValue;
           
            string TimeTransparValue;
            string TextEnableValue1;
            string TextTransparValue1;
            string TextEnableValue2;
            string TextTransparValue2;

            hScrollBar1.Minimum = 0;
            hScrollBar1.Maximum = 255;
            hScrollBar1.Value = 128;
            hScrollBar1.LargeChange = 1;
            //read ini file    text osd value
            TosdInfoVal[1].Osd_Txtstring = DxSdkFunction.IniReadValue("OSDPar", "OsdText1", 20, DxMediaFunction.IniFileName);
            TosdInfoVal[2].Osd_Txtstring = DxSdkFunction.IniReadValue("OSDPar", "OsdText2", 20, DxMediaFunction.IniFileName);
            TxtOsd1.Text = TosdInfoVal[1].Osd_Txtstring;
            TxtOsd2.Text = TosdInfoVal[2].Osd_Txtstring;

            // time osd enable value
             TimeOsdValue= DxSdkFunction.IniReadValue("OSDPar", "TimeOsdEnable", 20, DxMediaFunction.IniFileName);

             TimeTransparValue = DxSdkFunction.IniReadValue("OSDPar", "TimeTranspar", 20, DxMediaFunction.IniFileName);

             // text1 osd enable value
             TextEnableValue1 = DxSdkFunction.IniReadValue("OSDPar", "Text1OsdEnable", 20, DxMediaFunction.IniFileName);

             TextTransparValue1 = DxSdkFunction.IniReadValue("OSDPar", "Text1OsdTranspar", 20, DxMediaFunction.IniFileName);

             // text2 osd enable value
             TextEnableValue2 = DxSdkFunction.IniReadValue("OSDPar", "Text2OsdEnable", 20, DxMediaFunction.IniFileName);

             TextTransparValue2 = DxSdkFunction.IniReadValue("OSDPar", "Text2OsdTranspar", 20, DxMediaFunction.IniFileName);
            
            if (TimeOsdValue=="Enable")
            {
                checkTimeEn.Checked = true;
            }
            else
            {
                checkTimeEn.Checked = false ;
            }

            if (TimeTransparValue == "Enable")
            {
                checkTimeTranspar.Checked = true;
            }
            else
            {
                checkTimeTranspar.Checked = false;
            }

            //// text1 osd
            if (TextEnableValue1 == "Enable")
            {
                checkTxtEn1.Checked = true;
            }
            else
            {
                checkTxtEn1.Checked = false;
            }

            if (TextTransparValue1 == "Enable")
            {
                checkTxtTranspar1.Checked = true;
            }
            else
            {
                checkTxtTranspar1.Checked = false;
            }


            //text2 osd
            if (TextEnableValue2 == "Enable")
            {
                checkTxtEn2.Checked = true;
            }
            else
            {
                checkTxtEn2.Checked = false;
            }

            if (TextTransparValue2 == "Enable")
            {
                checkTxtTranspar2.Checked = true;
            }
            else
            {
                checkTxtTranspar2.Checked = false;
            }


        









         ///////////////////////////////////
            
            
            
            
            
            // 
            BackColor = ColorTranslator.ToWin32(Color.FromArgb(255, 255, 255));
            TosdInfoVal[1].TxtColor = ColorTranslator.ToWin32 (Color.FromArgb(0, 255, 0));
            TosdInfoVal[2].TxtColor = ColorTranslator.ToWin32(Color.FromArgb(0, 255, 0));
            TosdInfoVal[1].TimeColor = ColorTranslator.ToWin32(Color.FromArgb(0, 255, 0));
            TosdInfoVal[1].TimeX = Convert.ToInt32(TxtTimeX.Text);
            TosdInfoVal[1].TimeY = Convert.ToInt32(TxtTimeY.Text);
            TosdInfoVal[1].PicPlaceX = Convert.ToInt32(TxtPicX.Text);
            TosdInfoVal[1].PicPlaceY = Convert.ToInt32(TxtPicY.Text);

            //The first line of text osd parameter Settings
            TosdInfoVal[1].TxtPlaceX = Convert.ToInt32(TxtTextX1.Text);
            TosdInfoVal[1].TxtPlaceY = Convert.ToInt32(TxtTextY1.Text);

          
           
            TosdInfoVal[1].TxtFontSizeVal = Convert.ToInt32(TxtFontSize1.Text);
            TosdInfoVal[1].TimeFontSizeVal = Convert.ToInt32(TimeFontSize.Text);

            //The second line of text osd parameter Settings
            TosdInfoVal[2].TxtColor = ColorTranslator.ToWin32(Color.FromArgb(0,255, 0));
            TosdInfoVal[2].TxtPlaceX = Convert.ToInt32(TxtTextX2.Text);
            TosdInfoVal[2].TxtPlaceY = Convert.ToInt32(TxtTextY2.Text);
           
            TosdInfoVal[2].TxtFontSizeVal = Convert.ToInt32(TxtFontSize2.Text);
         
           
          


        }

        private void button1_Click(object sender, EventArgs e)
        {
            IntPtr TextOsd1 = Marshal.StringToHGlobalAnsi(TosdInfoVal[1].Osd_Txtstring);
            IntPtr TextOsd2 = Marshal.StringToHGlobalAnsi(TosdInfoVal[2].Osd_Txtstring);
            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwOpenDevState == 0)
            {
                if (checkTimeEn.Checked == true)
                {
                    if (checkTimeTranspar.Checked  == true)
                    {
                        //set time osd parameter, enable transparent
                        DxMediaApi.DXSetTimeOSD(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                                TosdInfoVal[1].TimeX,
                                                TosdInfoVal[1].TimeY,
                                                TosdInfoVal[1].TimeFontSizeVal,
                                                "Arial",
                                                TosdInfoVal[1].TimeColor,
                                                BackColor,
                                                true);
                    
                    }
                    else
                    {
                          //set time osd parameter, disable transparent
                        DxMediaApi.DXSetTimeOSD(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                                TosdInfoVal[1].TimeX,
                                                TosdInfoVal[1].TimeY,
                                                TosdInfoVal[1].TimeFontSizeVal,
                                                "Arial",
                                                TosdInfoVal[1].TimeColor,
                                                BackColor,
                                                false);
                    }

                    //enable the time osd
                    DxMediaApi.DXEnOSDDisp(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                          0,
                                          0,
                                          true );
                 

                }
                else
                {
                    //disable the time osd
                    DxMediaApi.DXEnOSDDisp(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                          0,
                                          0,
                                          false );

                }
                
                if (checkTxtEn1.Checked == true)
                {
                   
                    if (checkTxtTranspar1.Checked == true)
                    {
                           //set text osd parameter, enable transparent
                        DxMediaApi.DXSetTextOSD(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                                TosdInfoVal[1].TxtPlaceX,
                                                TosdInfoVal[1].TxtPlaceY,
                                                0,
                                                TextOsd1,
                                                TosdInfoVal[1].TxtFontSizeVal,
                                                "Arial",
                                                TosdInfoVal[1].TxtColor,
                                                BackColor,
                                                true);
                       

                    }
                    else
                    {
                        //   //set time osd parameter, disable transparent
                        DxMediaApi.DXSetTextOSD(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                                TosdInfoVal[1].TxtPlaceX,
                                                TosdInfoVal[1].TxtPlaceY,
                                                0,
                                                TextOsd1,
                                                TosdInfoVal[1].TxtFontSizeVal,
                                                "Arial",
                                                TosdInfoVal[1].TxtColor,
                                                BackColor,
                                                false);
                    }
                    // enable the first line of text osd

                    DxMediaApi.DXEnOSDDisp(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                          1,
                                          0,
                                          true );
                }
                else
                {
                         // disable the first line of text osd
                    DxMediaApi.DXEnOSDDisp(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                          1,
                                          0,
                                          false );

                }

                
                 if (checkTxtEn2.Checked == true)
                {
                   
                    if (checkTxtTranspar2.Checked == true)
                    {
                           //set text osd parameter, enable transparent
                        DxMediaApi.DXSetTextOSD(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                                TosdInfoVal[2].TxtPlaceX,
                                                TosdInfoVal[2].TxtPlaceY,
                                                1,
                                                TextOsd2,
                                                TosdInfoVal[2].TxtFontSizeVal,
                                                "Arial",
                                                TosdInfoVal[2].TxtColor,
                                                BackColor,
                                                true);
                       

                    }
                    else
                    {
                        //   //set time osd parameter, disable transparent
                          DxMediaApi.DXSetTextOSD(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                                TosdInfoVal[2].TxtPlaceX,
                                                TosdInfoVal[2].TxtPlaceY,
                                                1,
                                                TextOsd2,
                                                TosdInfoVal[2].TxtFontSizeVal,
                                                "Arial",
                                                TosdInfoVal[2].TxtColor,
                                                BackColor,
                                                false);


                    }
                    // enable the second line of text osd

                     DxMediaApi.DXEnOSDDisp(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                          1,
                                          1,
                                          true );
                }
                else
                {
                         // disable the second line of text osd
                      DxMediaApi.DXEnOSDDisp(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                          1,
                                          1,
                                          false );

                }
                /*
                 if (checkEnablePic.Checked == true)
                 {
                     //set picture osd parameter, disable transparent
                     DxMediaApi.DXSetPictureOSD(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                                TosdInfoVal[1].PicPlaceX,
                                                TosdInfoVal[1].PicPlaceY,
                                                0,
                                                TosdInfoVal[1].PicOsdFile,
                                                true,
                                                Convert.ToChar(255));
                     DxMediaApi.DXEnOSDDisp(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                           2,
                                           0,
                                           true);
                 }
                 else
                 {
                     DxMediaApi.DXEnOSDDisp(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                            2,
                                            0,
                                            false);
                 }*/
              
            }
          

        }

        private void TxtTimeX_TextChanged(object sender, EventArgs e)
        {
            TosdInfoVal[1].TimeX = Convert.ToInt32(TxtTimeX.Text);
         
            
            
        }

        private void TxtTimeY_TextChanged(object sender, EventArgs e)
        {
            TosdInfoVal[1].TimeY = Convert.ToInt32(TxtTimeY.Text); 
        }

        private void TxtTextX_TextChanged(object sender, EventArgs e)
        {
            TosdInfoVal[1].TxtPlaceX =Convert.ToInt32( TxtTextX1.Text);
        }

        private void TxtTextY_TextChanged(object sender, EventArgs e)
        {
            TosdInfoVal[1].TxtPlaceY = Convert.ToInt32(TxtTextY1.Text);
        }

        private void TxtOsd_TextChanged(object sender, EventArgs e)
        {
            TosdInfoVal[1].Osd_Txtstring = TxtOsd1.Text;
            DxMediaApi.WritePrivateProfileString("OSDPar", "OsdText1", TosdInfoVal[1].Osd_Txtstring, DxMediaFunction.IniFileName);


        }

        private void btTxtFontColor_Click(object sender, EventArgs e)
        {
            colorDialog1.ShowDialog();
            TosdInfoVal[1].TxtColor = ColorTranslator.ToWin32(colorDialog1.Color);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void TxtFontSize1_TextChanged(object sender, EventArgs e)
        {
            TosdInfoVal[1].TxtFontSizeVal = Convert.ToInt32(TxtFontSize1.Text);
        }

        private void TxtTextX2_TextChanged(object sender, EventArgs e)
        {
            TosdInfoVal[2].TxtPlaceX = Convert.ToInt32(TxtTextX2.Text);
        }

        private void TxtTextY2_TextChanged(object sender, EventArgs e)
        {
            TosdInfoVal[2].TxtPlaceY = Convert.ToInt32(TxtTextY2.Text);
        }

        private void TxtFontSize2_TextChanged(object sender, EventArgs e)
        {
            TosdInfoVal[2].TxtFontSizeVal = Convert.ToInt32(TxtFontSize2.Text);
        }

        private void TxtPicX_TextChanged(object sender, EventArgs e)
        {
            TosdInfoVal[1].PicPlaceX = Convert.ToInt32(TxtPicX.Text);
        }

        private void TxtPicY_TextChanged(object sender, EventArgs e)
        {
            TosdInfoVal[1].PicPlaceY = Convert.ToInt32(TxtPicY.Text);
        }

        private void checkTimeEn_CheckedChanged(object sender, EventArgs e)
        {
            if (checkTimeEn.Checked == true)
            {
                DxMediaApi.WritePrivateProfileString("OSDPar", "TimeOsdEnable", "Enable", DxMediaFunction.IniFileName);
            }
            else
            {
                DxMediaApi.WritePrivateProfileString("OSDPar", "TimeOsdEnable", "Disable", DxMediaFunction.IniFileName);
                checkTimeEn.Checked = false;
            }
           
        }

        private void checkTimeTranspar_CheckedChanged(object sender, EventArgs e)
        {
            if (checkTimeTranspar.Checked == true)
            {

                DxMediaApi.WritePrivateProfileString("OSDPar", "TimeTranspar", "Enable", DxMediaFunction.IniFileName);
            }
            else
            {
                DxMediaApi.WritePrivateProfileString("OSDPar", "TimeTranspar", "Disable", DxMediaFunction.IniFileName);
                checkTimeTranspar.Checked = false;
            }
          
        }

        private void checkTxtEn1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkTxtEn1.Checked == true)
            {

                DxMediaApi.WritePrivateProfileString("OSDPar", "Text1OsdEnable", "Enable", DxMediaFunction.IniFileName);
            }
            else
            {
                DxMediaApi.WritePrivateProfileString("OSDPar", "Text1OsdEnable", "Disable", DxMediaFunction.IniFileName);
                checkTxtEn1.Checked = false;
            }
            
        }

        private void checkTxtTranspar1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkTxtTranspar1.Checked == true)
            {
                DxMediaApi.WritePrivateProfileString("OSDPar", "Text1OsdTranspar", "Enable", DxMediaFunction.IniFileName);
            }
            else
            {
                DxMediaApi.WritePrivateProfileString("OSDPar", "Text1OsdTranspar", "Disable", DxMediaFunction.IniFileName);
                checkTxtTranspar1.Checked = false;
            }

          
        }

        private void TxtOsd2_TextChanged(object sender, EventArgs e)
        {
            TosdInfoVal[2].Osd_Txtstring = TxtOsd2.Text;
            DxMediaApi.WritePrivateProfileString("OSDPar", "OsdText2", TosdInfoVal[2].Osd_Txtstring, DxMediaFunction.IniFileName);
        }

        private void checkTxtEn2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkTxtEn2.Checked == true)
            {

                DxMediaApi.WritePrivateProfileString("OSDPar", "Text2OsdEnable", "Enable", DxMediaFunction.IniFileName);
            }
            else
            {
                DxMediaApi.WritePrivateProfileString("OSDPar", "Text2OsdEnable", "Disable", DxMediaFunction.IniFileName);
                checkTxtEn2.Checked = false;
            }
        }

        private void checkTxtTranspar2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkTxtTranspar2.Checked == true)
            {
                DxMediaApi.WritePrivateProfileString("OSDPar", "Text2OsdTranspar", "Enable", DxMediaFunction.IniFileName);
            }
            else
            {
                DxMediaApi.WritePrivateProfileString("OSDPar", "Text2OsdTranspar", "Disable", DxMediaFunction.IniFileName);
                checkTxtTranspar2.Checked = false;
            }
        }

        private void PichScrollBar_Scroll(object sender, ScrollEventArgs e)
        {
          
           
        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            //set picture osd parameter, disable transparent
            DxMediaApi.DXSetPictureOSD(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                       TosdInfoVal[1].PicPlaceX,
                                       TosdInfoVal[1].PicPlaceY,
                                       0,
                                       TosdInfoVal[1].PicOsdFile,
                                       true,
                                       Convert.ToChar(hScrollBar1.Value));
            DxMediaApi.DXEnOSDDisp(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                          2,
                                          0,
                                          true);
          
        }

        private void hScrollBar1_SizeChanged(object sender, EventArgs e)
        {

            
              
              
            
        }

        private void checkEnablePic_CheckedChanged(object sender, EventArgs e)
        {

        }       
    }
}
