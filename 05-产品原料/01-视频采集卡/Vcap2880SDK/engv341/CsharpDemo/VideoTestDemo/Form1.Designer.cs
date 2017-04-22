namespace VideoTestDemo
{
    partial class Form1
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.VideoSizeMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem768 = new System.Windows.Forms.ToolStripMenuItem();
            this.D1MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItemCif = new System.Windows.Forms.ToolStripMenuItem();
            this.videoStandardToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pALToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nTSCToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.VideoSourceMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.AV1MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.AV2MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.SVIDEOMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.colorSetToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deinterlaceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.standardMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.goodMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.bestMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cancelMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.denoiseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.videoEffectsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.flipVideoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mirrorVideoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.btSnap = new System.Windows.Forms.Button();
            this.btOsdSetting = new System.Windows.Forms.Button();
            this.btExit = new System.Windows.Forms.Button();
            this.btGetCurBuf = new System.Windows.Forms.Button();
            this.btRecord = new System.Windows.Forms.Button();
            this.btPauseRec = new System.Windows.Forms.Button();
            this.btCodecSet = new System.Windows.Forms.Button();
            this.btCallBack = new System.Windows.Forms.Button();
            this.btCallSnap = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.DeviceNo = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.radiovmr9 = new System.Windows.Forms.RadioButton();
            this.radiooffscrean = new System.Windows.Forms.RadioButton();
            this.radiovmr7 = new System.Windows.Forms.RadioButton();
            this.btZoom = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.VideoSizeMenu,
            this.videoStandardToolStripMenuItem,
            this.VideoSourceMenu,
            this.colorSetToolStripMenuItem,
            this.deinterlaceToolStripMenuItem,
            this.denoiseToolStripMenuItem,
            this.videoEffectsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(886, 25);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
            this.menuStrip1.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.menuStrip1_ItemClicked);
            // 
            // VideoSizeMenu
            // 
            this.VideoSizeMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuItem768,
            this.D1MenuItem,
            this.MenuItemCif});
            this.VideoSizeMenu.Name = "VideoSizeMenu";
            this.VideoSizeMenu.Size = new System.Drawing.Size(77, 21);
            this.VideoSizeMenu.Text = "VideoSize";
            // 
            // MenuItem768
            // 
            this.MenuItem768.Name = "MenuItem768";
            this.MenuItem768.Size = new System.Drawing.Size(123, 22);
            this.MenuItem768.Text = "768*576";
            this.MenuItem768.Click += new System.EventHandler(this.MenuItemvga_Click);
            // 
            // D1MenuItem
            // 
            this.D1MenuItem.Name = "D1MenuItem";
            this.D1MenuItem.Size = new System.Drawing.Size(123, 22);
            this.D1MenuItem.Text = "720*576";
            this.D1MenuItem.Click += new System.EventHandler(this.D1MenuItem_Click);
            // 
            // MenuItemCif
            // 
            this.MenuItemCif.Name = "MenuItemCif";
            this.MenuItemCif.Size = new System.Drawing.Size(123, 22);
            this.MenuItemCif.Text = "352*288";
            this.MenuItemCif.Click += new System.EventHandler(this.MenuItemCif_Click);
            // 
            // videoStandardToolStripMenuItem
            // 
            this.videoStandardToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.pALToolStripMenuItem,
            this.nTSCToolStripMenuItem});
            this.videoStandardToolStripMenuItem.Name = "videoStandardToolStripMenuItem";
            this.videoStandardToolStripMenuItem.Size = new System.Drawing.Size(107, 21);
            this.videoStandardToolStripMenuItem.Text = "VideoStandard";
            // 
            // pALToolStripMenuItem
            // 
            this.pALToolStripMenuItem.Name = "pALToolStripMenuItem";
            this.pALToolStripMenuItem.Size = new System.Drawing.Size(108, 22);
            this.pALToolStripMenuItem.Text = "PAL";
            this.pALToolStripMenuItem.Click += new System.EventHandler(this.pALToolStripMenuItem_Click);
            // 
            // nTSCToolStripMenuItem
            // 
            this.nTSCToolStripMenuItem.Name = "nTSCToolStripMenuItem";
            this.nTSCToolStripMenuItem.Size = new System.Drawing.Size(108, 22);
            this.nTSCToolStripMenuItem.Text = "NTSC";
            this.nTSCToolStripMenuItem.Click += new System.EventHandler(this.nTSCToolStripMenuItem_Click_1);
            // 
            // VideoSourceMenu
            // 
            this.VideoSourceMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.AV1MenuItem,
            this.AV2MenuItem,
            this.SVIDEOMenuItem});
            this.VideoSourceMenu.Name = "VideoSourceMenu";
            this.VideoSourceMenu.Size = new System.Drawing.Size(94, 21);
            this.VideoSourceMenu.Text = "VideoSource";
            // 
            // AV1MenuItem
            // 
            this.AV1MenuItem.Name = "AV1MenuItem";
            this.AV1MenuItem.Size = new System.Drawing.Size(121, 22);
            this.AV1MenuItem.Text = "AV1";
            this.AV1MenuItem.Click += new System.EventHandler(this.AV1MenuItem_Click_1);
            // 
            // AV2MenuItem
            // 
            this.AV2MenuItem.Name = "AV2MenuItem";
            this.AV2MenuItem.Size = new System.Drawing.Size(121, 22);
            this.AV2MenuItem.Text = "AV2";
            this.AV2MenuItem.Click += new System.EventHandler(this.AV2MenuItem_Click_1);
            // 
            // SVIDEOMenuItem
            // 
            this.SVIDEOMenuItem.Name = "SVIDEOMenuItem";
            this.SVIDEOMenuItem.Size = new System.Drawing.Size(121, 22);
            this.SVIDEOMenuItem.Text = "SVIDEO";
            this.SVIDEOMenuItem.Click += new System.EventHandler(this.SVIDEOMenuItem_Click_1);
            // 
            // colorSetToolStripMenuItem
            // 
            this.colorSetToolStripMenuItem.Name = "colorSetToolStripMenuItem";
            this.colorSetToolStripMenuItem.Size = new System.Drawing.Size(92, 21);
            this.colorSetToolStripMenuItem.Text = "ColorSetting";
            this.colorSetToolStripMenuItem.Click += new System.EventHandler(this.colorSetToolStripMenuItem_Click);
            // 
            // deinterlaceToolStripMenuItem
            // 
            this.deinterlaceToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.standardMenuItem,
            this.goodMenuItem,
            this.bestMenuItem,
            this.cancelMenuItem});
            this.deinterlaceToolStripMenuItem.Name = "deinterlaceToolStripMenuItem";
            this.deinterlaceToolStripMenuItem.Size = new System.Drawing.Size(85, 21);
            this.deinterlaceToolStripMenuItem.Text = "Deinterlace";
            this.deinterlaceToolStripMenuItem.Click += new System.EventHandler(this.deinterlaceToolStripMenuItem_Click);
            // 
            // standardMenuItem
            // 
            this.standardMenuItem.Name = "standardMenuItem";
            this.standardMenuItem.Size = new System.Drawing.Size(129, 22);
            this.standardMenuItem.Text = "Default";
            this.standardMenuItem.Click += new System.EventHandler(this.stanToolStripMenuItem_Click);
            // 
            // goodMenuItem
            // 
            this.goodMenuItem.Name = "goodMenuItem";
            this.goodMenuItem.Size = new System.Drawing.Size(129, 22);
            this.goodMenuItem.Text = "Standard";
            this.goodMenuItem.Click += new System.EventHandler(this.goodMenuItem_Click);
            // 
            // bestMenuItem
            // 
            this.bestMenuItem.Name = "bestMenuItem";
            this.bestMenuItem.Size = new System.Drawing.Size(129, 22);
            this.bestMenuItem.Text = "good";
            this.bestMenuItem.Click += new System.EventHandler(this.beToolStripMenuItem_Click);
            // 
            // cancelMenuItem
            // 
            this.cancelMenuItem.Name = "cancelMenuItem";
            this.cancelMenuItem.Size = new System.Drawing.Size(129, 22);
            this.cancelMenuItem.Text = "cancel";
            this.cancelMenuItem.Click += new System.EventHandler(this.cancelMenuItem_Click);
            // 
            // denoiseToolStripMenuItem
            // 
            this.denoiseToolStripMenuItem.Name = "denoiseToolStripMenuItem";
            this.denoiseToolStripMenuItem.Size = new System.Drawing.Size(114, 21);
            this.denoiseToolStripMenuItem.Text = "ImageAlgorithm";
            this.denoiseToolStripMenuItem.Click += new System.EventHandler(this.denoiseToolStripMenuItem_Click);
            // 
            // videoEffectsToolStripMenuItem
            // 
            this.videoEffectsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.flipVideoToolStripMenuItem,
            this.mirrorVideoToolStripMenuItem});
            this.videoEffectsToolStripMenuItem.Name = "videoEffectsToolStripMenuItem";
            this.videoEffectsToolStripMenuItem.Size = new System.Drawing.Size(96, 21);
            this.videoEffectsToolStripMenuItem.Text = "VideoEffects ";
            // 
            // flipVideoToolStripMenuItem
            // 
            this.flipVideoToolStripMenuItem.Name = "flipVideoToolStripMenuItem";
            this.flipVideoToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.flipVideoToolStripMenuItem.Text = "FlipVideo";
            this.flipVideoToolStripMenuItem.Click += new System.EventHandler(this.flipVideoToolStripMenuItem_Click);
            // 
            // mirrorVideoToolStripMenuItem
            // 
            this.mirrorVideoToolStripMenuItem.Name = "mirrorVideoToolStripMenuItem";
            this.mirrorVideoToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.mirrorVideoToolStripMenuItem.Text = "MirrorVideo";
            this.mirrorVideoToolStripMenuItem.Click += new System.EventHandler(this.mirrorVideoToolStripMenuItem_Click);
            // 
            // btSnap
            // 
            this.btSnap.Location = new System.Drawing.Point(747, 122);
            this.btSnap.Name = "btSnap";
            this.btSnap.Size = new System.Drawing.Size(103, 27);
            this.btSnap.TabIndex = 4;
            this.btSnap.Text = "Snap";
            this.btSnap.UseVisualStyleBackColor = true;
            this.btSnap.Click += new System.EventHandler(this.btSnap_Click);
            // 
            // btOsdSetting
            // 
            this.btOsdSetting.Location = new System.Drawing.Point(747, 383);
            this.btOsdSetting.Name = "btOsdSetting";
            this.btOsdSetting.Size = new System.Drawing.Size(103, 27);
            this.btOsdSetting.TabIndex = 5;
            this.btOsdSetting.Text = "OSDsetting";
            this.btOsdSetting.UseVisualStyleBackColor = true;
            this.btOsdSetting.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // btExit
            // 
            this.btExit.Location = new System.Drawing.Point(746, 573);
            this.btExit.Name = "btExit";
            this.btExit.Size = new System.Drawing.Size(87, 24);
            this.btExit.TabIndex = 6;
            this.btExit.Text = "Exit";
            this.btExit.UseVisualStyleBackColor = true;
            this.btExit.Click += new System.EventHandler(this.btExit_Click);
            // 
            // btGetCurBuf
            // 
            this.btGetCurBuf.Location = new System.Drawing.Point(747, 159);
            this.btGetCurBuf.Name = "btGetCurBuf";
            this.btGetCurBuf.Size = new System.Drawing.Size(103, 27);
            this.btGetCurBuf.TabIndex = 7;
            this.btGetCurBuf.Text = "GetCurBuff";
            this.btGetCurBuf.UseVisualStyleBackColor = true;
            this.btGetCurBuf.Click += new System.EventHandler(this.btGetCurBuf_Click);
            // 
            // btRecord
            // 
            this.btRecord.Location = new System.Drawing.Point(747, 309);
            this.btRecord.Name = "btRecord";
            this.btRecord.Size = new System.Drawing.Size(103, 27);
            this.btRecord.TabIndex = 9;
            this.btRecord.Text = "Record";
            this.btRecord.UseVisualStyleBackColor = true;
            this.btRecord.Click += new System.EventHandler(this.btRecord_Click);
            // 
            // btPauseRec
            // 
            this.btPauseRec.Location = new System.Drawing.Point(747, 346);
            this.btPauseRec.Name = "btPauseRec";
            this.btPauseRec.Size = new System.Drawing.Size(103, 27);
            this.btPauseRec.TabIndex = 10;
            this.btPauseRec.Text = "PauseRecord";
            this.btPauseRec.UseVisualStyleBackColor = true;
            this.btPauseRec.Click += new System.EventHandler(this.btPauseRec_Click);
            // 
            // btCodecSet
            // 
            this.btCodecSet.Location = new System.Drawing.Point(747, 272);
            this.btCodecSet.Name = "btCodecSet";
            this.btCodecSet.Size = new System.Drawing.Size(103, 27);
            this.btCodecSet.TabIndex = 11;
            this.btCodecSet.Text = "CodecSetting";
            this.btCodecSet.UseVisualStyleBackColor = true;
            this.btCodecSet.Click += new System.EventHandler(this.btCodecSet_Click);
            // 
            // btCallBack
            // 
            this.btCallBack.Location = new System.Drawing.Point(747, 196);
            this.btCallBack.Name = "btCallBack";
            this.btCallBack.Size = new System.Drawing.Size(103, 27);
            this.btCallBack.TabIndex = 12;
            this.btCallBack.Text = "StartCallback";
            this.btCallBack.UseVisualStyleBackColor = true;
            this.btCallBack.Click += new System.EventHandler(this.btCallBack_Click);
            // 
            // btCallSnap
            // 
            this.btCallSnap.Location = new System.Drawing.Point(747, 233);
            this.btCallSnap.Name = "btCallSnap";
            this.btCallSnap.Size = new System.Drawing.Size(103, 29);
            this.btCallSnap.TabIndex = 13;
            this.btCallSnap.Text = "CallbackSnap";
            this.btCallSnap.UseVisualStyleBackColor = true;
            this.btCallSnap.Click += new System.EventHandler(this.btCallSnap_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.DeviceNo);
            this.groupBox1.Location = new System.Drawing.Point(747, 35);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(89, 70);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "CurDevice";
            // 
            // DeviceNo
            // 
            this.DeviceNo.AutoSize = true;
            this.DeviceNo.Location = new System.Drawing.Point(5, 29);
            this.DeviceNo.Name = "DeviceNo";
            this.DeviceNo.Size = new System.Drawing.Size(53, 12);
            this.DeviceNo.TabIndex = 0;
            this.DeviceNo.Text = "Channel1";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.radiovmr9);
            this.groupBox2.Controls.Add(this.radiooffscrean);
            this.groupBox2.Controls.Add(this.radiovmr7);
            this.groupBox2.Location = new System.Drawing.Point(744, 458);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(130, 108);
            this.groupBox2.TabIndex = 15;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "PreviewMode";
            // 
            // radiovmr9
            // 
            this.radiovmr9.AutoSize = true;
            this.radiovmr9.Location = new System.Drawing.Point(12, 81);
            this.radiovmr9.Name = "radiovmr9";
            this.radiovmr9.Size = new System.Drawing.Size(77, 16);
            this.radiovmr9.TabIndex = 2;
            this.radiovmr9.TabStop = true;
            this.radiovmr9.Text = "VMR9 Mode";
            this.radiovmr9.UseVisualStyleBackColor = true;
            this.radiovmr9.CheckedChanged += new System.EventHandler(this.radiovmr9_CheckedChanged);
            // 
            // radiooffscrean
            // 
            this.radiooffscrean.AutoSize = true;
            this.radiooffscrean.Location = new System.Drawing.Point(12, 53);
            this.radiooffscrean.Name = "radiooffscrean";
            this.radiooffscrean.Size = new System.Drawing.Size(77, 16);
            this.radiooffscrean.TabIndex = 1;
            this.radiooffscrean.TabStop = true;
            this.radiooffscrean.Text = "Offscream";
            this.radiooffscrean.UseVisualStyleBackColor = true;
            this.radiooffscrean.CheckedChanged += new System.EventHandler(this.radiooffscrean_CheckedChanged);
            // 
            // radiovmr7
            // 
            this.radiovmr7.AutoSize = true;
            this.radiovmr7.Location = new System.Drawing.Point(11, 27);
            this.radiovmr7.Name = "radiovmr7";
            this.radiovmr7.Size = new System.Drawing.Size(77, 16);
            this.radiovmr7.TabIndex = 0;
            this.radiovmr7.TabStop = true;
            this.radiovmr7.Text = "VMR7 Mode";
            this.radiovmr7.UseVisualStyleBackColor = true;
            this.radiovmr7.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // btZoom
            // 
            this.btZoom.Location = new System.Drawing.Point(747, 421);
            this.btZoom.Name = "btZoom";
            this.btZoom.Size = new System.Drawing.Size(103, 24);
            this.btZoom.TabIndex = 16;
            this.btZoom.Text = "DigitalZoom";
            this.btZoom.UseVisualStyleBackColor = true;
            this.btZoom.Click += new System.EventHandler(this.btZoom_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(886, 604);
            this.Controls.Add(this.btZoom);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btCallSnap);
            this.Controls.Add(this.btCallBack);
            this.Controls.Add(this.btCodecSet);
            this.Controls.Add(this.btPauseRec);
            this.Controls.Add(this.btRecord);
            this.Controls.Add(this.btGetCurBuf);
            this.Controls.Add(this.btExit);
            this.Controls.Add(this.btOsdSetting);
            this.Controls.Add(this.btSnap);
            this.Controls.Add(this.menuStrip1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem deinterlaceToolStripMenuItem;
        private System.Windows.Forms.Button btSnap;
        private System.Windows.Forms.Button btOsdSetting;
        private System.Windows.Forms.Button btExit;
        private System.Windows.Forms.ToolStripMenuItem VideoSizeMenu;
        private System.Windows.Forms.ToolStripMenuItem VideoSourceMenu;
        private System.Windows.Forms.ToolStripMenuItem colorSetToolStripMenuItem;
        private System.Windows.Forms.Button btGetCurBuf;
        private System.Windows.Forms.Button btRecord;
        private System.Windows.Forms.Button btPauseRec;
        private System.Windows.Forms.Button btCodecSet;
        private System.Windows.Forms.Button btCallBack;
        private System.Windows.Forms.Button btCallSnap;
        private System.Windows.Forms.ToolStripMenuItem D1MenuItem;
        private System.Windows.Forms.ToolStripMenuItem AV1MenuItem;
        private System.Windows.Forms.ToolStripMenuItem AV2MenuItem;
        private System.Windows.Forms.ToolStripMenuItem SVIDEOMenuItem;
        private System.Windows.Forms.ToolStripMenuItem videoEffectsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem flipVideoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mirrorVideoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem standardMenuItem;
        private System.Windows.Forms.ToolStripMenuItem goodMenuItem;
        private System.Windows.Forms.ToolStripMenuItem bestMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cancelMenuItem;
        private System.Windows.Forms.ToolStripMenuItem denoiseToolStripMenuItem;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label DeviceNo;
        private System.Windows.Forms.ToolStripMenuItem MenuItem768;
        private System.Windows.Forms.ToolStripMenuItem videoStandardToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pALToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nTSCToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem MenuItemCif;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton radiovmr9;
        private System.Windows.Forms.RadioButton radiooffscrean;
        private System.Windows.Forms.RadioButton radiovmr7;
        private System.Windows.Forms.Button btZoom;
    }
}

