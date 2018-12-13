namespace OLauncher
{
    partial class FrmMain
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            this.BtnStart = new System.Windows.Forms.Button();
            this.BtnStart2 = new System.Windows.Forms.Button();
            this.BtnStart3 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // BtnStart
            // 
            this.BtnStart.Location = new System.Drawing.Point(55, 26);
            this.BtnStart.Name = "BtnStart";
            this.BtnStart.Size = new System.Drawing.Size(171, 40);
            this.BtnStart.TabIndex = 0;
            this.BtnStart.Text = "일반 게임";
            this.BtnStart.UseVisualStyleBackColor = true;
            this.BtnStart.Click += new System.EventHandler(this.BtnStart_Click);
            // 
            // BtnStart2
            // 
            this.BtnStart2.Location = new System.Drawing.Point(55, 103);
            this.BtnStart2.Name = "BtnStart2";
            this.BtnStart2.Size = new System.Drawing.Size(171, 40);
            this.BtnStart2.TabIndex = 1;
            this.BtnStart2.Text = "시나리오 게임";
            this.BtnStart2.UseVisualStyleBackColor = true;
            this.BtnStart2.Click += new System.EventHandler(this.BtnStart2_Click);
            // 
            // BtnStart3
            // 
            this.BtnStart3.Location = new System.Drawing.Point(55, 177);
            this.BtnStart3.Name = "BtnStart3";
            this.BtnStart3.Size = new System.Drawing.Size(171, 40);
            this.BtnStart3.TabIndex = 2;
            this.BtnStart3.Text = "맵에디터";
            this.BtnStart3.UseVisualStyleBackColor = true;
            this.BtnStart3.Click += new System.EventHandler(this.BtnStart3_Click);
            // 
            // FrmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(282, 253);
            this.Controls.Add(this.BtnStart3);
            this.Controls.Add(this.BtnStart2);
            this.Controls.Add(this.BtnStart);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(300, 300);
            this.MinimumSize = new System.Drawing.Size(300, 300);
            this.Name = "FrmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "OLauncher";
            this.ResumeLayout(false);

        }

        private System.Windows.Forms.Button BtnStart;
        private System.Windows.Forms.Button BtnStart2;
        private System.Windows.Forms.Button BtnStart3;
    }
}