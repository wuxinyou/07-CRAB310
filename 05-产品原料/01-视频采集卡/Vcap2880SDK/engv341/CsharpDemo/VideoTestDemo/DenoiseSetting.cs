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
    public partial class DenoiseSetting : Form
    {
        
       
        public DenoiseSetting()
        {
            InitializeComponent();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void DenoiseSetting_Load(object sender, EventArgs e)
        {
           
            hScrollDenoise.Minimum = 0;
            hScrollDenoise.Maximum = 100;
            hScrollDenoise.Value = 70;
            hScrollDenoise.LargeChange = 1;
            hScrollSharp.Minimum = 0;
            hScrollSharp.Maximum = 255;
            hScrollSharp.Value = 15;
            hScrollSharp.LargeChange = 1;


            hScrollBright.Minimum = -255;
            hScrollBright.Maximum = 255;
            hScrollBright.Value = 0;
            hScrollBright.LargeChange = 1;


            hScrollContract.Minimum = -100;
            hScrollContract.Maximum = 100;
            hScrollContract.Value = 15;
            hScrollContract.LargeChange = 1;


            DenoiseValue.Text = System.Convert.ToString(hScrollDenoise.Value);

            SharpValue.Text = System.Convert.ToString(hScrollSharp.Value);


            BrighValue.Text = System.Convert.ToString(hScrollBright.Value);

            ContractValue.Text = System.Convert.ToString(hScrollContract.Value);
            DxMediaFunction.ColorPara.nBrightness = hScrollBright.Value;
            DxMediaFunction.ColorPara.nContrast = hScrollContract.Value;
            
            

        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            DxMediaApi.DXEnableDenoise(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, hScrollDenoise.Value);
            DenoiseValue.Text = System.Convert.ToString(hScrollDenoise.Value);
        }

        private void hScrollBar2_Scroll(object sender, ScrollEventArgs e)
        {
            DxMediaApi.DXEnableSharpen(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, hScrollSharp.Value);
            SharpValue.Text = System.Convert.ToString(hScrollSharp.Value);
        }

        private void hScrollBar3_Scroll(object sender, ScrollEventArgs e)
        {
            DxMediaFunction.ColorPara.nBrightness = hScrollBright.Value;
            DxMediaFunction.ColorPara.nContrast = hScrollContract.Value;
            BrighValue.Text = System.Convert.ToString(hScrollBright.Value);


            DxMediaApi.DXEnDataRaterPara(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, 0, ref DxMediaFunction.ColorPara); 
        }

        private void hScrollContract_Scroll(object sender, ScrollEventArgs e)
        {
            DxMediaFunction.ColorPara.nBrightness = hScrollBright.Value;
            DxMediaFunction.ColorPara.nContrast = hScrollContract.Value;
            ContractValue.Text = System.Convert.ToString(hScrollContract.Value);

            DxMediaApi.DXEnDataRaterPara(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, 0, ref DxMediaFunction.ColorPara); 
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DxMediaApi.DXEnableDenoise(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, hScrollDenoise.Value);
            DxMediaApi.DXEnableSharpen(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle, hScrollSharp.Value);
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
    }
}
