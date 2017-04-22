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
    public partial class FrmDigitalZoom : Form
    {
        public FrmDigitalZoom()
        {
            InitializeComponent();
        }

        private void FrmDigitalZoom_Load(object sender, EventArgs e)
        {

        }

        private void btOK_Click(object sender, EventArgs e)
        {
            if (DxMediaFunction.DeviceInfo[Form1.nCard].dwOpenDevState == 0)
            {
               // DxMediaFunction.DeviceInfo[Form1.nCard].dwZoomRect.Left =
                DxMediaFunction.DeviceInfo[Form1.nCard].dwZoomRect.Top = Convert.ToInt32(txtZoomTop.Text);
                DxMediaFunction.DeviceInfo[Form1.nCard].dwZoomRect.Left = Convert.ToInt32(txtZoomLeft.Text);
                DxMediaFunction.DeviceInfo[Form1.nCard].dwZoomRect.Right = Convert.ToInt32(txtZoomRight.Text);
                DxMediaFunction.DeviceInfo[Form1.nCard].dwZoomRect.Bottom = Convert.ToInt32(txtZoomBot.Text);
                if (chkEnableZoom.Checked == true)
                {
                    DxMediaApi.DXEnFScale(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                            true,
                                             ref DxMediaFunction.DeviceInfo[Form1.nCard].dwZoomRect,
                                             0);
                }
                else
                {
                    DxMediaApi.DXEnFScale(DxMediaFunction.DeviceInfo[Form1.nCard].dwCardHandle,
                                            false,
                                             ref DxMediaFunction.DeviceInfo[Form1.nCard].dwZoomRect,
                                             0);

                }
            }
        }

        private void btExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
