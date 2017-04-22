namespace VideoTestDemo
{
    partial class DenoiseSetting
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
            this.hScrollDenoise = new System.Windows.Forms.HScrollBar();
            this.label1 = new System.Windows.Forms.Label();
            this.DenoiseValue = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SharpValue = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.hScrollSharp = new System.Windows.Forms.HScrollBar();
            this.hScrollBright = new System.Windows.Forms.HScrollBar();
            this.hScrollContract = new System.Windows.Forms.HScrollBar();
            this.BrighValue = new System.Windows.Forms.Label();
            this.ContractValue = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // hScrollDenoise
            // 
            this.hScrollDenoise.Location = new System.Drawing.Point(110, 37);
            this.hScrollDenoise.Name = "hScrollDenoise";
            this.hScrollDenoise.Size = new System.Drawing.Size(264, 22);
            this.hScrollDenoise.TabIndex = 1;
            this.hScrollDenoise.Value = 70;
            this.hScrollDenoise.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar1_Scroll);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 37);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "Denoise：";
            // 
            // DenoiseValue
            // 
            this.DenoiseValue.Location = new System.Drawing.Point(380, 37);
            this.DenoiseValue.Name = "DenoiseValue";
            this.DenoiseValue.Size = new System.Drawing.Size(54, 20);
            this.DenoiseValue.TabIndex = 2;
            this.DenoiseValue.Text = "70";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(128, 75);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(207, 18);
            this.label2.TabIndex = 3;
            this.label2.Text = "Value=0 :Cancel the function";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // SharpValue
            // 
            this.SharpValue.Location = new System.Drawing.Point(380, 113);
            this.SharpValue.Name = "SharpValue";
            this.SharpValue.Size = new System.Drawing.Size(54, 20);
            this.SharpValue.TabIndex = 6;
            this.SharpValue.Text = "15";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 113);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(71, 12);
            this.label4.TabIndex = 5;
            this.label4.Text = "Sharpness：";
            // 
            // hScrollSharp
            // 
            this.hScrollSharp.Location = new System.Drawing.Point(113, 113);
            this.hScrollSharp.Name = "hScrollSharp";
            this.hScrollSharp.Size = new System.Drawing.Size(264, 22);
            this.hScrollSharp.TabIndex = 4;
            this.hScrollSharp.Value = 70;
            this.hScrollSharp.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar2_Scroll);
            // 
            // hScrollBright
            // 
            this.hScrollBright.Location = new System.Drawing.Point(110, 170);
            this.hScrollBright.Name = "hScrollBright";
            this.hScrollBright.Size = new System.Drawing.Size(264, 22);
            this.hScrollBright.TabIndex = 7;
            this.hScrollBright.Value = 70;
            this.hScrollBright.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar3_Scroll);
            // 
            // hScrollContract
            // 
            this.hScrollContract.Location = new System.Drawing.Point(110, 224);
            this.hScrollContract.Name = "hScrollContract";
            this.hScrollContract.Size = new System.Drawing.Size(264, 22);
            this.hScrollContract.TabIndex = 8;
            this.hScrollContract.Value = 70;
            this.hScrollContract.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollContract_Scroll);
            // 
            // BrighValue
            // 
            this.BrighValue.Location = new System.Drawing.Point(380, 170);
            this.BrighValue.Name = "BrighValue";
            this.BrighValue.Size = new System.Drawing.Size(54, 20);
            this.BrighValue.TabIndex = 9;
            this.BrighValue.Text = "15";
            // 
            // ContractValue
            // 
            this.ContractValue.Location = new System.Drawing.Point(380, 234);
            this.ContractValue.Name = "ContractValue";
            this.ContractValue.Size = new System.Drawing.Size(54, 20);
            this.ContractValue.TabIndex = 10;
            this.ContractValue.Text = "15";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 172);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 12);
            this.label3.TabIndex = 11;
            this.label3.Text = "Brightness";
            this.label3.Click += new System.EventHandler(this.label3_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 224);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(59, 12);
            this.label5.TabIndex = 12;
            this.label5.Text = "Contract:";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(154, 268);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(85, 31);
            this.button1.TabIndex = 13;
            this.button1.Text = "OK";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // DenoiseSetting
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(424, 306);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.ContractValue);
            this.Controls.Add(this.BrighValue);
            this.Controls.Add(this.hScrollContract);
            this.Controls.Add(this.hScrollBright);
            this.Controls.Add(this.SharpValue);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.hScrollSharp);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.DenoiseValue);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.hScrollDenoise);
            this.Name = "DenoiseSetting";
            this.Text = "DenoiseSetting";
            this.Load += new System.EventHandler(this.DenoiseSetting_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.HScrollBar hScrollDenoise;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label DenoiseValue;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label SharpValue;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.HScrollBar hScrollSharp;
        private System.Windows.Forms.HScrollBar hScrollBright;
        private System.Windows.Forms.HScrollBar hScrollContract;
        private System.Windows.Forms.Label BrighValue;
        private System.Windows.Forms.Label ContractValue;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button button1;
    }
}