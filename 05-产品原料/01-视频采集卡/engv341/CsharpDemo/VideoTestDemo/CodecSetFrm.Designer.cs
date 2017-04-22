namespace VideoTestDemo
{
    partial class CodecSetFrm
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBoxVidCodec = new System.Windows.Forms.ComboBox();
            this.comboBoxAudCodec = new System.Windows.Forms.ComboBox();
            this.btOk = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btPicPath = new System.Windows.Forms.Button();
            this.btnRecPath = new System.Windows.Forms.Button();
            this.TxtPicPath = new System.Windows.Forms.TextBox();
            this.TxtRecPath = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.rdX264 = new System.Windows.Forms.RadioButton();
            this.rdDivx = new System.Windows.Forms.RadioButton();
            this.rdXvid = new System.Windows.Forms.RadioButton();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 56);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Audio Codec";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 19);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "VideoCodec";
            // 
            // comboBoxVidCodec
            // 
            this.comboBoxVidCodec.FormattingEnabled = true;
            this.comboBoxVidCodec.Location = new System.Drawing.Point(83, 19);
            this.comboBoxVidCodec.Name = "comboBoxVidCodec";
            this.comboBoxVidCodec.Size = new System.Drawing.Size(321, 20);
            this.comboBoxVidCodec.TabIndex = 2;
            this.comboBoxVidCodec.SelectedIndexChanged += new System.EventHandler(this.comboBoxVidCodec_SelectedIndexChanged);
            // 
            // comboBoxAudCodec
            // 
            this.comboBoxAudCodec.FormattingEnabled = true;
            this.comboBoxAudCodec.Location = new System.Drawing.Point(83, 56);
            this.comboBoxAudCodec.Name = "comboBoxAudCodec";
            this.comboBoxAudCodec.Size = new System.Drawing.Size(321, 20);
            this.comboBoxAudCodec.TabIndex = 3;
            this.comboBoxAudCodec.SelectedIndexChanged += new System.EventHandler(this.comboBoxAudCodec_SelectedIndexChanged);
            // 
            // btOk
            // 
            this.btOk.Location = new System.Drawing.Point(174, 307);
            this.btOk.Name = "btOk";
            this.btOk.Size = new System.Drawing.Size(62, 28);
            this.btOk.TabIndex = 4;
            this.btOk.Text = "OK";
            this.btOk.UseVisualStyleBackColor = true;
            this.btOk.Click += new System.EventHandler(this.btOk_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.comboBoxAudCodec);
            this.groupBox1.Controls.Add(this.comboBoxVidCodec);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(6, 7);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(428, 102);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Enum the system codec infromation";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btPicPath);
            this.groupBox2.Controls.Add(this.btnRecPath);
            this.groupBox2.Controls.Add(this.TxtPicPath);
            this.groupBox2.Controls.Add(this.TxtRecPath);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Location = new System.Drawing.Point(9, 122);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(424, 95);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Save File Path";
            // 
            // btPicPath
            // 
            this.btPicPath.Location = new System.Drawing.Point(355, 62);
            this.btPicPath.Name = "btPicPath";
            this.btPicPath.Size = new System.Drawing.Size(51, 22);
            this.btPicPath.TabIndex = 5;
            this.btPicPath.Text = "Brower";
            this.btPicPath.UseVisualStyleBackColor = true;
            this.btPicPath.Click += new System.EventHandler(this.btPicPath_Click);
            // 
            // btnRecPath
            // 
            this.btnRecPath.Location = new System.Drawing.Point(355, 19);
            this.btnRecPath.Name = "btnRecPath";
            this.btnRecPath.Size = new System.Drawing.Size(51, 22);
            this.btnRecPath.TabIndex = 4;
            this.btnRecPath.Text = "Brower";
            this.btnRecPath.UseVisualStyleBackColor = true;
            this.btnRecPath.Click += new System.EventHandler(this.btnRecPath_Click);
            // 
            // TxtPicPath
            // 
            this.TxtPicPath.Location = new System.Drawing.Point(128, 62);
            this.TxtPicPath.Name = "TxtPicPath";
            this.TxtPicPath.Size = new System.Drawing.Size(217, 21);
            this.TxtPicPath.TabIndex = 3;
            this.TxtPicPath.Text = "d:\\Pic";
            // 
            // TxtRecPath
            // 
            this.TxtRecPath.Location = new System.Drawing.Point(132, 22);
            this.TxtRecPath.Name = "TxtRecPath";
            this.TxtRecPath.Size = new System.Drawing.Size(217, 21);
            this.TxtRecPath.TabIndex = 2;
            this.TxtRecPath.Text = "d:\\Video";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 62);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(107, 12);
            this.label4.TabIndex = 1;
            this.label4.Text = "Picture Save Path";
            this.label4.Click += new System.EventHandler(this.label4_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 24);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(95, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "Video Save Path";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.rdX264);
            this.groupBox3.Controls.Add(this.rdDivx);
            this.groupBox3.Controls.Add(this.rdXvid);
            this.groupBox3.Location = new System.Drawing.Point(6, 236);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(423, 56);
            this.groupBox3.TabIndex = 7;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "VideoCodec setting";
            // 
            // rdX264
            // 
            this.rdX264.AutoSize = true;
            this.rdX264.Location = new System.Drawing.Point(321, 24);
            this.rdX264.Name = "rdX264";
            this.rdX264.Size = new System.Drawing.Size(83, 16);
            this.rdX264.TabIndex = 2;
            this.rdX264.TabStop = true;
            this.rdX264.Text = "H264 Codec";
            this.rdX264.UseVisualStyleBackColor = true;
            this.rdX264.CheckedChanged += new System.EventHandler(this.rdX264_CheckedChanged);
            // 
            // rdDivx
            // 
            this.rdDivx.AutoSize = true;
            this.rdDivx.Location = new System.Drawing.Point(147, 24);
            this.rdDivx.Name = "rdDivx";
            this.rdDivx.Size = new System.Drawing.Size(83, 16);
            this.rdDivx.TabIndex = 1;
            this.rdDivx.TabStop = true;
            this.rdDivx.Text = "Divx Codec";
            this.rdDivx.UseVisualStyleBackColor = true;
            this.rdDivx.CheckedChanged += new System.EventHandler(this.rdDivx_CheckedChanged);
            // 
            // rdXvid
            // 
            this.rdXvid.AutoSize = true;
            this.rdXvid.Location = new System.Drawing.Point(13, 24);
            this.rdXvid.Name = "rdXvid";
            this.rdXvid.Size = new System.Drawing.Size(83, 16);
            this.rdXvid.TabIndex = 0;
            this.rdXvid.TabStop = true;
            this.rdXvid.Text = "Xvid Codec";
            this.rdXvid.UseVisualStyleBackColor = true;
            this.rdXvid.CheckedChanged += new System.EventHandler(this.rdXvid_CheckedChanged);
            // 
            // CodecSetFrm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(439, 347);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btOk);
            this.Name = "CodecSetFrm";
            this.Text = "CodecSetFrm";
            this.Load += new System.EventHandler(this.CodecSetFrm_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBoxVidCodec;
        private System.Windows.Forms.ComboBox comboBoxAudCodec;
        private System.Windows.Forms.Button btOk;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btPicPath;
        private System.Windows.Forms.Button btnRecPath;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.GroupBox groupBox3;
        public System.Windows.Forms.TextBox TxtRecPath;
        public System.Windows.Forms.TextBox TxtPicPath;
        public System.Windows.Forms.RadioButton rdX264;
        public System.Windows.Forms.RadioButton rdDivx;
        public System.Windows.Forms.RadioButton rdXvid;
    }
}