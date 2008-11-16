namespace VerkstanEditor.Gui
{
    partial class TimelineChannels
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
            // TimelineChannels
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlText;
            this.Name = "TimelineChannels";
            this.Size = new System.Drawing.Size(736, 368);
            this.Load += new System.EventHandler(this.TimelineChannels_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.TimelineChannels_Paint);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.TimelineChannels_MouseMove);
            this.ParentChanged += new System.EventHandler(this.TimelineChannels_ParentChanged);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.TimelineChannels_MouseDown);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.TimelineChannels_MouseUp);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.TimelineChannels_KeyDown);
            this.ResumeLayout(false);

        }

        #endregion

    }
}
