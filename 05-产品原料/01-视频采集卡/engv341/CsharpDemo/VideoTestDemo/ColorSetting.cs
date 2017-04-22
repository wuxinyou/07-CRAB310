using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VideoTestDemo
{
    public partial class ColorSetting : Form
    {
        public int iFlags;


       DxMediaApi.Device_ColorProp[] DevColorInfo = new DxMediaApi.Device_ColorProp[16];
        public ColorSetting()
        {
            InitializeComponent();
           
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void hScrollBar5_Scroll(object sender, ScrollEventArgs e)
        {
          
            DxMediaFunction.SharpValue = ScrollBarSharp.Value;
            SharpVal.Text = System.Convert.ToString(ScrollBarSharp.Value);
           
            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwOpenDevState == 0)
            {
                DxMediaApi.DXSetDisplayPara(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, 4, DxMediaFunction.SharpValue, 0);
                DxMediaApi.WritePrivateProfileString("VideoPar", "Sharp"+ Convert.ToString(Form1.nCard ), SharpVal.Text, DxMediaFunction.IniFileName);
            }
        }

        private void ScrollBarBrigh_Scroll(object sender, ScrollEventArgs e)
        {
            DxMediaFunction.BrightValue =ScrollBarBrigh.Value ;
            BrightVal.Text = System.Convert.ToString(ScrollBarBrigh.Value);
            //
            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwOpenDevState == 0)
            {
                DxMediaApi.DXSetDisplayPara(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, 0, DxMediaFunction.BrightValue, 0);
                DxMediaApi.WritePrivateProfileString("VideoPar", "Bright" + Convert.ToString(Form1.nCard), BrightVal.Text, DxMediaFunction.IniFileName);
            }
            
        }

        private void ScrollBarContrast_Scroll(object sender, ScrollEventArgs e)
        {
            DxMediaFunction.ContrastValue = ScrollBarContrast.Value;
            ContrastVal.Text = System.Convert.ToString(ScrollBarContrast.Value);

            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwOpenDevState == 0)
            {
                DxMediaApi.DXSetDisplayPara(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, 1, DxMediaFunction.ContrastValue, 0);
                DxMediaApi.WritePrivateProfileString("VideoPar", "Contrast" + Convert.ToString(Form1.nCard), ContrastVal.Text, DxMediaFunction.IniFileName);
            }
        }

        private void ScrollBarSaturation_Scroll(object sender, ScrollEventArgs e)
        {
            DxMediaFunction.StaturationValue = ScrollBarSaturation.Value;
            SaturatVal.Text = System.Convert.ToString(ScrollBarSaturation.Value);

            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwOpenDevState == 0)
            {
                DxMediaApi.DXSetDisplayPara(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, 2, DxMediaFunction.StaturationValue, 0);
                DxMediaApi.WritePrivateProfileString("VideoPar", "Saturation" + Convert.ToString(Form1.nCard), SaturatVal.Text, DxMediaFunction.IniFileName);
            }
        }

        private void ScrollBarHue_Scroll(object sender, ScrollEventArgs e)
        {
            DxMediaFunction.HueValue = ScrollBarHue.Value;
            HueVal.Text = System.Convert.ToString(ScrollBarHue.Value);
            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwOpenDevState == 0)
            {
                DxMediaApi.DXSetDisplayPara(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, 3, DxMediaFunction.HueValue, 0);
                DxMediaApi.WritePrivateProfileString("VideoPar", " Hue"+ Convert.ToString(Form1.nCard ), HueVal.Text, DxMediaFunction.IniFileName);
            }
        }

        private void ColorSetting_Load(object sender, EventArgs e)
        {

            
            int i;
           
            for (i = 0; i < 16; i++)
            {
                
                
                DevColorInfo[i].MinVal = 0;
                DevColorInfo[i].MaxVal = 0;
                DevColorInfo[i].DefaultVal = 0;
                DevColorInfo[i].ColorType = 0;
                DevColorInfo[i].StepVal = 0;
                DevColorInfo[i].CurVal = 0;

            }
            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwOpenDevState == 0)
            {
                for (i = 0; i < 5; i++)
                {
                    DxMediaApi.DXGetDisplayParaRange(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, i,
                                             ref DevColorInfo[i].MinVal,
                                             ref DevColorInfo[i].MaxVal,
                                             ref DevColorInfo[i].StepVal,
                                             ref DevColorInfo[i].DefaultVal,
                                             ref iFlags);

                }


            }
            //
            ScrollBarBrigh.Maximum = DevColorInfo[0].MaxVal;
            ScrollBarBrigh.Minimum = DevColorInfo[0].MinVal;
            ScrollBarBrigh.LargeChange = DevColorInfo[0].StepVal;
            ScrollBarBrigh.Value = DevColorInfo[0].DefaultVal;

            //
            ScrollBarContrast.Maximum = DevColorInfo[1].MaxVal;
            ScrollBarContrast.Minimum = DevColorInfo[1].MinVal;
            ScrollBarContrast.LargeChange = DevColorInfo[1].StepVal;
            ScrollBarContrast.Value = DevColorInfo[1].DefaultVal;

            //
            ScrollBarSaturation.Maximum = DevColorInfo[2].MaxVal;
            ScrollBarSaturation.Minimum = DevColorInfo[2].MinVal;
            ScrollBarSaturation.LargeChange = DevColorInfo[2].StepVal;
            ScrollBarSaturation.Value = DevColorInfo[2].DefaultVal;

            //
            ScrollBarHue.Maximum = DevColorInfo[3].MaxVal;
            ScrollBarHue.Minimum = DevColorInfo[3].MinVal;
            ScrollBarHue.LargeChange = DevColorInfo[3].StepVal;
            ScrollBarHue.Value = DevColorInfo[3].DefaultVal;

            //
            ScrollBarSharp.Maximum = DevColorInfo[4].MaxVal;
            ScrollBarSharp.Minimum = DevColorInfo[4].MinVal;
            ScrollBarSharp.LargeChange = DevColorInfo[4].StepVal;
          //  ScrollBarSharp.Value = DevColorInfo[4].DefaultVal;

            //
            BrightVal.Text = System.Convert.ToString(ScrollBarBrigh.Value);
            ContrastVal.Text = System.Convert.ToString(ScrollBarContrast.Value);
            SaturatVal.Text = System.Convert.ToString(ScrollBarSaturation.Value);
            SharpVal.Text = System.Convert.ToString(ScrollBarSharp.Value);
            HueVal.Text = System.Convert.ToString(ScrollBarHue.Value);


        }

        private void button1_Click(object sender, EventArgs e)
        {
            //
            ScrollBarBrigh.Value = DevColorInfo[0].DefaultVal;
            ScrollBarContrast.Value = DevColorInfo[1].DefaultVal;
            ScrollBarSaturation.Value = DevColorInfo[2].DefaultVal;
            ScrollBarSharp.Value = DevColorInfo[4].DefaultVal;
            ScrollBarHue.Value = DevColorInfo[3].DefaultVal;

            //
            BrightVal.Text = System.Convert.ToString(ScrollBarBrigh.Value);
            ContrastVal.Text = System.Convert.ToString(ScrollBarContrast.Value);
            SaturatVal.Text = System.Convert.ToString(ScrollBarSaturation.Value);
            SharpVal.Text = System.Convert.ToString(ScrollBarSharp.Value);
            HueVal.Text = System.Convert.ToString(ScrollBarHue.Value);



            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwOpenDevState == 0)
            {
                for (int i = 0; i < 5; i++)
                {
                    DxMediaApi.DXSetDisplayPara(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, i, DevColorInfo[i].DefaultVal, 0);

                }


            }
        }

        private void btOK_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
