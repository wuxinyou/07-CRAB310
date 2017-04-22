namespace VideoTestDemo
{
    partial class ColorSetting
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.SharpVal = new System.Windows.Forms.Label();
            this.HueVal = new System.Windows.Forms.Label();
            this.SaturatVal = new System.Windows.Forms.Label();
            this.ContrastVal = new System.Windows.Forms.Label();
            this.BrightVal = new System.Windows.Forms.Label();
            this.ScrollBarSharp = new System.Windows.Forms.HScrollBar();
            this.ScrollBarHue = new System.Windows.Forms.HScrollBar();
            this.ScrollBarSaturation = new System.Windows.Forms.HScrollBar();
            this.ScrollBarContrast = new System.Windows.Forms.HScrollBar();
            this.ScrollBarBrigh = new System.Windows.Forms.HScrollBar();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.btOK = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Controls.Add(this.SharpVal);
            this.groupBox1.Controls.Add(this.HueVal);
            this.groupBox1.Controls.Add(this.SaturatVal);
            this.groupBox1.Controls.Add(this.ContrastVal);
            this.groupBox1.Controls.Add(this.BrightVal);
            this.groupBox1.Controls.Add(this.ScrollBarSharp);
            this.groupBox1.Controls.Add(this.ScrollBarHue);
            this.groupBox1.Controls.Add(this.ScrollBarSaturation);
            this.groupBox1.Controls.Add(this.ScrollBarContrast);
            this.groupBox1.Controls.Add(this.ScrollBarBrigh);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(358, 210);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Enter += new System.EventHandler(this.groupBox1_Enter);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(140, 170);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(71, 24);
            this.button1.TabIndex = 15;
            this.button1.Text = "Default";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // SharpVal
            // 
            this.SharpVal.AutoSize = true;
            this.SharpVal.Location = new System.Drawing.Point(331, 145);
            this.SharpVal.Name = "SharpVal";
            this.SharpVal.Size = new System.Drawing.Size(11, 12);
            this.SharpVal.TabIndex = 14;
            this.SharpVal.Text = "5";
            // 
            // HueVal
            // 
            this.HueVal.AutoSize = true;
            this.HueVal.Location = new System.Drawing.Point(337, 120);
            this.HueVal.Name = "HueVal";
            this.HueVal.Size = new System.Drawing.Size(11, 12);
            this.HueVal.TabIndex = 13;
            this.HueVal.Text = "0";
            // 
            // SaturatVal
            // 
            this.SaturatVal.AutoSize = true;
            this.SaturatVal.Location = new System.Drawing.Point(331, 88);
            this.SaturatVal.Name = "SaturatVal";
            this.SaturatVal.Size = new System.Drawing.Size(17, 12);
            this.SaturatVal.TabIndex = 12;
            this.SaturatVal.Text = "68";
            // 
            // ContrastVal
            // 
            this.ContrastVal.AutoSize = true;
            this.ContrastVal.Location = new System.Drawing.Point(331, 55);
            this.ContrastVal.Name = "ContrastVal";
            this.ContrastVal.Size = new System.Drawing.Size(17, 12);
            this.ContrastVal.TabIndex = 11;
            this.ContrastVal.Text = "64";
            // 
            // BrightVal
            // 
            this.BrightVal.AutoSize = true;
            this.BrightVal.Location = new System.Drawing.Point(331, 25);
            this.BrightVal.Name = "BrightVal";
            this.BrightVal.Size = new System.Drawing.Size(23, 12);
            this.BrightVal.TabIndex = 10;
            this.BrightVal.Text = "128";
            // 
            // ScrollBarSharp
            // 
            this.ScrollBarSharp.Location = new System.Drawing.Point(94, 142);
            this.ScrollBarSharp.Name = "ScrollBarSharp";
            this.ScrollBarSharp.Size = new System.Drawing.Size(229, 16);
            this.ScrollBarSharp.TabIndex = 9;
            this.ScrollBarSharp.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar5_Scroll);
            // 
            // ScrollBarHue
            // 
            this.ScrollBarHue.Location = new System.Drawing.Point(94, 116);
            this.ScrollBarHue.Name = "ScrollBarHue";
            this.ScrollBarHue.Size = new System.Drawing.Size(229, 16);
            this.ScrollBarHue.TabIndex = 8;
            this.ScrollBarHue.Scroll += new System.Windows.Forms.ScrollEventHandler(this.ScrollBarHue_Scroll);
            // 
            // ScrollBarSaturation
            // 
            this.ScrollBarSaturation.Location = new System.Drawing.Point(94, 88);
            this.ScrollBarSaturation.Name = "ScrollBarSaturation";
            this.ScrollBarSaturation.Size = new System.Drawing.Size(229, 16);
            this.ScrollBarSaturation.TabIndex = 7;
            this.ScrollBarSaturation.Scroll += new System.Windows.Forms.ScrollEventHandler(this.ScrollBarSaturation_Scroll);
            // 
            // ScrollBarContrast
            // 
            this.ScrollBarContrast.Location = new System.Drawing.Point(94, 55);
            this.ScrollBarContrast.Name = "ScrollBarContrast";
            this.ScrollBarContrast.Size = new System.Drawing.Size(229, 16);
            this.ScrollBarContrast.TabIndex = 6;
            this.ScrollBarContrast.Scroll += new System.Windows.Forms.ScrollEventHandler(this.ScrollBarContrast_Scroll);
            // 
            // ScrollBarBrigh
            // 
            this.ScrollBarBrigh.Location = new System.Drawing.Point(94, 25);
            this.ScrollBarBrigh.Name = "ScrollBarBrigh";
            this.ScrollBarBrigh.Size = new System.Drawing.Size(229, 16);
            this.ScrollBarBrigh.TabIndex = 5;
            this.ScrollBarBrigh.Scroll += new System.Windows.Forms.ScrollEventHandler(this.ScrollBarBrigh_Scroll);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(17, 145);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(59, 12);
            this.label5.TabIndex = 4;
            this.label5.Text = "Sharpness";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(17, 88);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(71, 12);
            this.label4.TabIndex = 3;
            this.label4.Text = "Saturation:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(17, 116);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(23, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "Hue";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(17, 59);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "Contract";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(17, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Brightness";
            // 
            // btOK
            // 
            this.btOK.Location = new System.Drawing.Point(152, 239);
            this.btOK.Name = "btOK";
            this.btOK.Size = new System.Drawing.Size(60, 24);
            this.btOK.TabIndex = 1;
            this.btOK.Text = "Exit";
            this.btOK.UseVisualStyleBackColor = true;
            this.btOK.Click += new System.EventHandler(this.btOK_Click);
            // 
            // ColorSetting
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(382, 275);
            this.Controls.Add(this.btOK);
            this.Controls.Add(this.groupBox1);
            this.Name = "ColorSetting";
            this.Text = "ColorSetting";
            this.Load += new System.EventHandler(this.ColorSetting_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.HScrollBar ScrollBarSharp;
        private System.Windows.Forms.HScrollBar ScrollBarHue;
        private System.Windows.Forms.HScrollBar ScrollBarSaturation;
        private System.Windows.Forms.HScrollBar ScrollBarContrast;
        private System.Windows.Forms.HScrollBar ScrollBarBrigh;
        private System.Windows.Forms.Label ContrastVal;
        private System.Windows.Forms.Label BrightVal;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label SharpVal;
        private System.Windows.Forms.Label HueVal;
        private System.Windows.Forms.Label SaturatVal;
        private System.Windows.Forms.Button btOK;
    }
}