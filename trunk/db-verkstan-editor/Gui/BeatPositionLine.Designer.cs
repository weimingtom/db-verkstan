﻿namespace VerkstanEditor.Gui
{
    partial class BeatPositionLine
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // BeatPositionLine
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.DoubleBuffered = true;
            this.Name = "BeatPositionLine";
            this.Size = new System.Drawing.Size(714, 25);
            this.Load += new System.EventHandler(this.BeatPositionLine_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.BeatPositionLine_Paint);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.BeatPositionLine_MouseMove);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.BeatPositionLine_MouseDown);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.BeatPositionLine_MouseUp);
            this.ResumeLayout(false);

        }

        #endregion

    }
}
