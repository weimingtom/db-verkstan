namespace VerkstanEditor.Gui
{
    partial class SceneTimeline
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
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer3 = new System.Windows.Forms.SplitContainer();
            this.label1 = new System.Windows.Forms.Label();
            this.channelInfos1 = new VerkstanEditor.Gui.ChannelInfos();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.playerPositionLine1 = new VerkstanEditor.Gui.PlayerPositionLine();
            this.channels1 = new VerkstanEditor.Gui.Channels();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.splitContainer3.Panel1.SuspendLayout();
            this.splitContainer3.Panel2.SuspendLayout();
            this.splitContainer3.SuspendLayout();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.BackColor = System.Drawing.SystemColors.ControlLight;
            this.splitContainer1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.IsSplitterFixed = true;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Margin = new System.Windows.Forms.Padding(0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer3);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.splitContainer1.Panel2.Controls.Add(this.splitContainer2);
            this.splitContainer1.Size = new System.Drawing.Size(684, 264);
            this.splitContainer1.SplitterDistance = 94;
            this.splitContainer1.TabIndex = 0;
            // 
            // splitContainer3
            // 
            this.splitContainer3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer3.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer3.IsSplitterFixed = true;
            this.splitContainer3.Location = new System.Drawing.Point(0, 0);
            this.splitContainer3.Name = "splitContainer3";
            this.splitContainer3.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer3.Panel1
            // 
            this.splitContainer3.Panel1.BackColor = System.Drawing.SystemColors.Control;
            this.splitContainer3.Panel1.Controls.Add(this.label1);
            // 
            // splitContainer3.Panel2
            // 
            this.splitContainer3.Panel2.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.splitContainer3.Panel2.Controls.Add(this.channelInfos1);
            this.splitContainer3.Size = new System.Drawing.Size(92, 262);
            this.splitContainer3.SplitterDistance = 25;
            this.splitContainer3.SplitterWidth = 1;
            this.splitContainer3.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(28, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Channel";
            // 
            // channelInfos1
            // 
            this.channelInfos1.BackColor = System.Drawing.SystemColors.Control;
            this.channelInfos1.Location = new System.Drawing.Point(-1, 0);
            this.channelInfos1.Name = "channelInfos1";
            this.channelInfos1.Size = new System.Drawing.Size(93, 372);
            this.channelInfos1.TabIndex = 0;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer2.IsSplitterFixed = true;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.splitContainer2.Panel1.Controls.Add(this.playerPositionLine1);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.AutoScroll = true;
            this.splitContainer2.Panel2.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.splitContainer2.Panel2.Controls.Add(this.channels1);
            this.splitContainer2.Size = new System.Drawing.Size(584, 262);
            this.splitContainer2.SplitterDistance = 25;
            this.splitContainer2.SplitterWidth = 1;
            this.splitContainer2.TabIndex = 0;
            // 
            // playerPositionLine1
            // 
            this.playerPositionLine1.AutoScroll = true;
            this.playerPositionLine1.BackColor = System.Drawing.SystemColors.Control;
            this.playerPositionLine1.Beats = 40;
            this.playerPositionLine1.BeatWidth = 16;
            this.playerPositionLine1.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.playerPositionLine1.Location = new System.Drawing.Point(0, 0);
            this.playerPositionLine1.Margin = new System.Windows.Forms.Padding(0);
            this.playerPositionLine1.Name = "playerPositionLine1";
            this.playerPositionLine1.PlayerPosition = 0;
            this.playerPositionLine1.Size = new System.Drawing.Size(640, 25);
            this.playerPositionLine1.TabIndex = 0;
            this.playerPositionLine1.PlayerPositionChanged += new VerkstanEditor.Gui.PlayerPositionLine.PlayerPositionChangedHandler(this.playerPositionLine1_PlayerPositionChanged);
            // 
            // channels1
            // 
            this.channels1.BackColor = System.Drawing.SystemColors.ControlText;
            this.channels1.Beats = 4;
            this.channels1.BeatWidth = 16;
            this.channels1.ChannelHeight = 30;
            this.channels1.Location = new System.Drawing.Point(0, 0);
            this.channels1.Margin = new System.Windows.Forms.Padding(0);
            this.channels1.Name = "channels1";
            this.channels1.Size = new System.Drawing.Size(64, 236);
            this.channels1.TabIndex = 0;
            this.channels1.LocationChanged += new System.EventHandler(this.channels1_LocationChanged);
            // 
            // SceneTimeline
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer1);
            this.Name = "SceneTimeline";
            this.Size = new System.Drawing.Size(684, 264);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer3.Panel1.ResumeLayout(false);
            this.splitContainer3.Panel1.PerformLayout();
            this.splitContainer3.Panel2.ResumeLayout(false);
            this.splitContainer3.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            this.splitContainer2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer3;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private PlayerPositionLine playerPositionLine1;
        private Channels channels1;
        private ChannelInfos channelInfos1;
        private System.Windows.Forms.Label label1;
    }
}
