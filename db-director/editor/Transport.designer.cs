﻿namespace VerkstanEditor.Gui
{
    partial class Transport
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
            this.stop = new System.Windows.Forms.Button();
            this.play = new System.Windows.Forms.Button();
            this.pause = new System.Windows.Forms.Button();
            this.start = new System.Windows.Forms.Button();
            this.rewind = new System.Windows.Forms.Button();
            this.fastForward = new System.Windows.Forms.Button();
            this.end = new System.Windows.Forms.Button();
            this.time = new System.Windows.Forms.Label();
            this.loopPlay = new System.Windows.Forms.Button();
            this.miniTimeline1 = new VerkstanEditor.Gui.MiniTimeline();
            this.SuspendLayout();
            // 
            // stop
            // 
            this.stop.BackColor = System.Drawing.SystemColors.Control;
            this.stop.Font = new System.Drawing.Font("Arial", 5.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stop.Location = new System.Drawing.Point(4, 4);
            this.stop.Margin = new System.Windows.Forms.Padding(1);
            this.stop.Name = "stop";
            this.stop.Size = new System.Drawing.Size(20, 20);
            this.stop.TabIndex = 0;
            this.stop.Text = "■";
            this.stop.UseVisualStyleBackColor = false;
            this.stop.Click += new System.EventHandler(this.stop_Click);
            // 
            // play
            // 
            this.play.BackColor = System.Drawing.SystemColors.Control;
            this.play.Font = new System.Drawing.Font("Arial", 5.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.play.Location = new System.Drawing.Point(26, 4);
            this.play.Margin = new System.Windows.Forms.Padding(1);
            this.play.Name = "play";
            this.play.Size = new System.Drawing.Size(20, 20);
            this.play.TabIndex = 1;
            this.play.Text = "►";
            this.play.UseVisualStyleBackColor = false;
            this.play.Click += new System.EventHandler(this.play_Click);
            // 
            // pause
            // 
            this.pause.BackColor = System.Drawing.SystemColors.Control;
            this.pause.Location = new System.Drawing.Point(70, 4);
            this.pause.Margin = new System.Windows.Forms.Padding(1);
            this.pause.Name = "pause";
            this.pause.Size = new System.Drawing.Size(20, 20);
            this.pause.TabIndex = 7;
            this.pause.Text = "\"";
            this.pause.UseVisualStyleBackColor = false;
            this.pause.Click += new System.EventHandler(this.pause_Click);
            // 
            // start
            // 
            this.start.BackColor = System.Drawing.SystemColors.Control;
            this.start.Font = new System.Drawing.Font("Arial", 5.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.start.Location = new System.Drawing.Point(4, 26);
            this.start.Margin = new System.Windows.Forms.Padding(1);
            this.start.Name = "start";
            this.start.Size = new System.Drawing.Size(20, 20);
            this.start.TabIndex = 8;
            this.start.Text = "|◄";
            this.start.UseVisualStyleBackColor = false;
            this.start.Click += new System.EventHandler(this.start_Click);
            // 
            // rewind
            // 
            this.rewind.BackColor = System.Drawing.SystemColors.Control;
            this.rewind.Font = new System.Drawing.Font("Arial", 5.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rewind.Location = new System.Drawing.Point(26, 26);
            this.rewind.Margin = new System.Windows.Forms.Padding(1);
            this.rewind.Name = "rewind";
            this.rewind.Size = new System.Drawing.Size(20, 20);
            this.rewind.TabIndex = 9;
            this.rewind.Text = "◄◄";
            this.rewind.UseVisualStyleBackColor = false;
            // 
            // fastForward
            // 
            this.fastForward.BackColor = System.Drawing.SystemColors.Control;
            this.fastForward.Font = new System.Drawing.Font("Arial", 5.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.fastForward.Location = new System.Drawing.Point(48, 26);
            this.fastForward.Margin = new System.Windows.Forms.Padding(1);
            this.fastForward.Name = "fastForward";
            this.fastForward.Size = new System.Drawing.Size(20, 20);
            this.fastForward.TabIndex = 10;
            this.fastForward.Text = "►►";
            this.fastForward.UseVisualStyleBackColor = false;
            // 
            // end
            // 
            this.end.BackColor = System.Drawing.SystemColors.Control;
            this.end.Font = new System.Drawing.Font("Arial", 5.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.end.Location = new System.Drawing.Point(70, 26);
            this.end.Margin = new System.Windows.Forms.Padding(1);
            this.end.Name = "end";
            this.end.Size = new System.Drawing.Size(20, 20);
            this.end.TabIndex = 11;
            this.end.Text = "►|";
            this.end.UseVisualStyleBackColor = false;
            // 
            // time
            // 
            this.time.AutoSize = true;
            this.time.Font = new System.Drawing.Font("Microsoft Sans Serif", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.time.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.time.Location = new System.Drawing.Point(258, -5);
            this.time.Name = "time";
            this.time.Size = new System.Drawing.Size(52, 55);
            this.time.TabIndex = 13;
            this.time.Text = "0";
            // 
            // loopPlay
            // 
            this.loopPlay.BackColor = System.Drawing.SystemColors.Control;
            this.loopPlay.Location = new System.Drawing.Point(48, 4);
            this.loopPlay.Margin = new System.Windows.Forms.Padding(1);
            this.loopPlay.Name = "loopPlay";
            this.loopPlay.Size = new System.Drawing.Size(20, 20);
            this.loopPlay.TabIndex = 20;
            this.loopPlay.Text = "L";
            this.loopPlay.UseVisualStyleBackColor = false;
            this.loopPlay.Click += new System.EventHandler(this.loopPlay_Click);
            // 
            // miniTimeline1
            // 
            this.miniTimeline1.BackColor = System.Drawing.SystemColors.ControlText;
            this.miniTimeline1.BeatPosition = 0F;
            this.miniTimeline1.ForeColor = System.Drawing.Color.Red;
            this.miniTimeline1.Location = new System.Drawing.Point(4, 49);
            this.miniTimeline1.Name = "miniTimeline1";
            this.miniTimeline1.Size = new System.Drawing.Size(559, 10);
            this.miniTimeline1.TabIndex = 18;
            // 
            // Transport
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.Controls.Add(this.loopPlay);
            this.Controls.Add(this.miniTimeline1);
            this.Controls.Add(this.end);
            this.Controls.Add(this.fastForward);
            this.Controls.Add(this.rewind);
            this.Controls.Add(this.start);
            this.Controls.Add(this.pause);
            this.Controls.Add(this.play);
            this.Controls.Add(this.stop);
            this.Controls.Add(this.time);
            this.Name = "Transport";
            this.Size = new System.Drawing.Size(574, 62);
            this.Resize += new System.EventHandler(this.Transport_Resize);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button stop;
        private System.Windows.Forms.Button play;
        private System.Windows.Forms.Button pause;
        private System.Windows.Forms.Button start;
        private System.Windows.Forms.Button rewind;
        private System.Windows.Forms.Button fastForward;
        private System.Windows.Forms.Button end;
        private System.Windows.Forms.Label time;
        private MiniTimeline miniTimeline1;
        private System.Windows.Forms.Button loopPlay;
    }
}
