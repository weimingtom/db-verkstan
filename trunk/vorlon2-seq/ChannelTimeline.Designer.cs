namespace VorlonSeq
{
    partial class ChannelTimeline
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
            // ChannelTimeline
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Name = "ChannelTimeline";
            this.Size = new System.Drawing.Size(680, 460);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.ChannelTimeline_Paint);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.ChannelTimeline_MouseMove);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ChannelTimeline_MouseDown);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.ChannelTimeline_MouseUp);
            this.SizeChanged += new System.EventHandler(this.ChannelTimeline_SizeChanged);
            this.ResumeLayout(false);

        }

        #endregion
    }
}
