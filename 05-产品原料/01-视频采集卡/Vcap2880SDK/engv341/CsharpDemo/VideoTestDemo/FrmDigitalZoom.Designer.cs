namespace VideoTestDemo
{
    partial class FrmDigitalZoom
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
            this.btOK = new System.Windows.Forms.Button();
            this.btExit = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.txtZoomTop = new System.Windows.Forms.TextBox();
            this.txtZoomLeft = new System.Windows.Forms.TextBox();
            this.txtZoomRight = new System.Windows.Forms.TextBox();
            this.txtZoomBot = new System.Windows.Forms.TextBox();
            this.chkEnableZoom = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // btOK
            // 
            this.btOK.Location = new System.Drawing.Point(39, 223);
            this.btOK.Name = "btOK";
            this.btOK.Size = new System.Drawing.Size(86, 31);
            this.btOK.TabIndex = 0;
            this.btOK.Text = "Application";
            this.btOK.UseVisualStyleBackColor = true;
            this.btOK.Click += new System.EventHandler(this.btOK_Click);
            // 
            // btExit
            // 
            this.btExit.Location = new System.Drawing.Point(194, 222);
            this.btExit.Name = "btExit";
            this.btExit.Size = new System.Drawing.Size(86, 31);
            this.btExit.TabIndex = 1;
            this.btExit.Text = "Exit";
            this.btExit.UseVisualStyleBackColor = true;
            this.btExit.Click += new System.EventHandler(this.btExit_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "ZoomTop";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "ZoomLeft";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 103);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "ZoomRight";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 144);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 12);
            this.label4.TabIndex = 5;
            this.label4.Text = "ZoomBootom";
            // 
            // txtZoomTop
            // 
            this.txtZoomTop.Location = new System.Drawing.Point(86, 22);
            this.txtZoomTop.Name = "txtZoomTop";
            this.txtZoomTop.Size = new System.Drawing.Size(79, 21);
            this.txtZoomTop.TabIndex = 6;
            this.txtZoomTop.Text = "20";
            // 
            // txtZoomLeft
            // 
            this.txtZoomLeft.Location = new System.Drawing.Point(86, 63);
            this.txtZoomLeft.Name = "txtZoomLeft";
            this.txtZoomLeft.Size = new System.Drawing.Size(79, 21);
            this.txtZoomLeft.TabIndex = 7;
            this.txtZoomLeft.Text = "20";
            // 
            // txtZoomRight
            // 
            this.txtZoomRight.Location = new System.Drawing.Point(86, 103);
            this.txtZoomRight.Name = "txtZoomRight";
            this.txtZoomRight.Size = new System.Drawing.Size(79, 21);
            this.txtZoomRight.TabIndex = 8;
            this.txtZoomRight.Text = "300";
            // 
            // txtZoomBot
            // 
            this.txtZoomBot.Location = new System.Drawing.Point(86, 144);
            this.txtZoomBot.Name = "txtZoomBot";
            this.txtZoomBot.Size = new System.Drawing.Size(79, 21);
            this.txtZoomBot.TabIndex = 9;
            this.txtZoomBot.Text = "300";
            // 
            // chkEnableZoom
            // 
            this.chkEnableZoom.AutoSize = true;
            this.chkEnableZoom.Location = new System.Drawing.Point(22, 188);
            this.chkEnableZoom.Name = "chkEnableZoom";
            this.chkEnableZoom.Size = new System.Drawing.Size(90, 16);
            this.chkEnableZoom.TabIndex = 10;
            this.chkEnableZoom.Text = "Enable Zoom";
            this.chkEnableZoom.UseVisualStyleBackColor = true;
            // 
            // FrmDigitalZoom
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(353, 262);
            this.Controls.Add(this.chkEnableZoom);
            this.Controls.Add(this.txtZoomBot);
            this.Controls.Add(this.txtZoomRight);
            this.Controls.Add(this.txtZoomLeft);
            this.Controls.Add(this.txtZoomTop);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btExit);
            this.Controls.Add(this.btOK);
            this.Name = "FrmDigitalZoom";
            this.Text = "FrmDigitalZoom";
            this.Load += new System.EventHandler(this.FrmDigitalZoom_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btOK;
        private System.Windows.Forms.Button btExit;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtZoomTop;
        private System.Windows.Forms.TextBox txtZoomLeft;
        private System.Windows.Forms.TextBox txtZoomRight;
        private System.Windows.Forms.TextBox txtZoomBot;
        private System.Windows.Forms.CheckBox chkEnableZoom;
    }
}