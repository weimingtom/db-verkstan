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
            // Channels
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlText;
            this.Name = "Channels";
            this.Size = new System.Drawing.Size(736, 368);
            this.Load += new System.EventHandler(this.Channels_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Channels_Paint);
            this.ParentChanged += new System.EventHandler(this.Channels_ParentChanged);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Channels_MouseDown);
            this.ResumeLayout(false);

        }

        #endregion

    }
}
