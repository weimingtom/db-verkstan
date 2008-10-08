﻿namespace VorlonSeq
{
    partial class mainWindow
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
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripContainer1 = new System.Windows.Forms.ToolStripContainer();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.closeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mainSplit = new System.Windows.Forms.SplitContainer();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.arrangeTab = new System.Windows.Forms.TabPage();
            this.channelEditor1 = new VorlonSeq.ChannelEditor();
            this.composeTab = new System.Windows.Forms.TabPage();
            this.clipEditor1 = new VorlonSeq.ClipEditor();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.timeLabel = new System.Windows.Forms.Label();
            this.framesPerTickUpDown = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.bpmLabel = new System.Windows.Forms.Label();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.playButton = new System.Windows.Forms.Button();
            this.recordButton = new System.Windows.Forms.Button();
            this.rewindButton = new System.Windows.Forms.Button();
            this.toolStripContainer1.BottomToolStripPanel.SuspendLayout();
            this.toolStripContainer1.ContentPanel.SuspendLayout();
            this.toolStripContainer1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.mainSplit.Panel1.SuspendLayout();
            this.mainSplit.Panel2.SuspendLayout();
            this.mainSplit.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.arrangeTab.SuspendLayout();
            this.composeTab.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.framesPerTickUpDown)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // statusStrip1
            // 
            this.statusStrip1.Dock = System.Windows.Forms.DockStyle.None;
            this.statusStrip1.Location = new System.Drawing.Point(0, 0);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(947, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripContainer1
            // 
            // 
            // toolStripContainer1.BottomToolStripPanel
            // 
            this.toolStripContainer1.BottomToolStripPanel.Controls.Add(this.statusStrip1);
            // 
            // toolStripContainer1.ContentPanel
            // 
            this.toolStripContainer1.ContentPanel.AutoScroll = true;
            this.toolStripContainer1.ContentPanel.Controls.Add(this.mainSplit);
            this.toolStripContainer1.ContentPanel.Size = new System.Drawing.Size(947, 496);
            this.toolStripContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.toolStripContainer1.Location = new System.Drawing.Point(0, 24);
            this.toolStripContainer1.Name = "toolStripContainer1";
            this.toolStripContainer1.Size = new System.Drawing.Size(947, 543);
            this.toolStripContainer1.TabIndex = 2;
            this.toolStripContainer1.Text = "toolStripContainer1";
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(947, 24);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.closeToolStripMenuItem,
            this.toolStripMenuItem1,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(35, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.newToolStripMenuItem.Text = "New";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.openToolStripMenuItem.Text = "Open";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.saveToolStripMenuItem.Text = "Save";
            // 
            // closeToolStripMenuItem
            // 
            this.closeToolStripMenuItem.Name = "closeToolStripMenuItem";
            this.closeToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.closeToolStripMenuItem.Text = "Close";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(97, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            // 
            // mainSplit
            // 
            this.mainSplit.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.mainSplit.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainSplit.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.mainSplit.IsSplitterFixed = true;
            this.mainSplit.Location = new System.Drawing.Point(0, 0);
            this.mainSplit.Name = "mainSplit";
            this.mainSplit.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // mainSplit.Panel1
            // 
            this.mainSplit.Panel1.Controls.Add(this.tabControl1);
            this.mainSplit.Panel1.Padding = new System.Windows.Forms.Padding(0, 6, 0, 0);
            // 
            // mainSplit.Panel2
            // 
            this.mainSplit.Panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(39)))), ((int)(((byte)(61)))));
            this.mainSplit.Panel2.Controls.Add(this.tableLayoutPanel2);
            this.mainSplit.Panel2.Controls.Add(this.tableLayoutPanel1);
            this.mainSplit.Size = new System.Drawing.Size(947, 496);
            this.mainSplit.SplitterDistance = 440;
            this.mainSplit.TabIndex = 0;
            // 
            // tabControl1
            // 
            this.tabControl1.Appearance = System.Windows.Forms.TabAppearance.FlatButtons;
            this.tabControl1.Controls.Add(this.arrangeTab);
            this.tabControl1.Controls.Add(this.composeTab);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 6);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(943, 430);
            this.tabControl1.TabIndex = 1;
            // 
            // arrangeTab
            // 
            this.arrangeTab.BackColor = System.Drawing.SystemColors.Control;
            this.arrangeTab.Controls.Add(this.channelEditor1);
            this.arrangeTab.Location = new System.Drawing.Point(4, 25);
            this.arrangeTab.Name = "arrangeTab";
            this.arrangeTab.Padding = new System.Windows.Forms.Padding(3);
            this.arrangeTab.Size = new System.Drawing.Size(935, 401);
            this.arrangeTab.TabIndex = 0;
            this.arrangeTab.Text = "Arrange";
            this.arrangeTab.UseVisualStyleBackColor = true;
            // 
            // channelEditor1
            // 
            this.channelEditor1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.channelEditor1.Location = new System.Drawing.Point(3, 3);
            this.channelEditor1.Name = "channelEditor1";
            this.channelEditor1.Size = new System.Drawing.Size(929, 395);
            this.channelEditor1.TabIndex = 0;
            // 
            // composeTab
            // 
            this.composeTab.AutoScroll = true;
            this.composeTab.Controls.Add(this.clipEditor1);
            this.composeTab.Location = new System.Drawing.Point(4, 25);
            this.composeTab.Name = "composeTab";
            this.composeTab.Padding = new System.Windows.Forms.Padding(3);
            this.composeTab.Size = new System.Drawing.Size(935, 401);
            this.composeTab.TabIndex = 1;
            this.composeTab.Text = "Compose";
            this.composeTab.UseVisualStyleBackColor = true;
            // 
            // clipEditor1
            // 
            this.clipEditor1.AutoScroll = true;
            this.clipEditor1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.clipEditor1.Location = new System.Drawing.Point(3, 3);
            this.clipEditor1.Name = "clipEditor1";
            this.clipEditor1.Size = new System.Drawing.Size(929, 395);
            this.clipEditor1.TabIndex = 0;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 5;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 67.72908F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 32.27092F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 69F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 131F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 148F));
            this.tableLayoutPanel2.Controls.Add(this.timeLabel, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.framesPerTickUpDown, 2, 0);
            this.tableLayoutPanel2.Controls.Add(this.label1, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.bpmLabel, 3, 0);
            this.tableLayoutPanel2.ForeColor = System.Drawing.Color.Black;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(181, 0);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(571, 45);
            this.tableLayoutPanel2.TabIndex = 1;
            // 
            // timeLabel
            // 
            this.timeLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.timeLabel.AutoSize = true;
            this.timeLabel.Font = new System.Drawing.Font("David", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.timeLabel.ForeColor = System.Drawing.Color.White;
            this.timeLabel.Location = new System.Drawing.Point(3, 0);
            this.timeLabel.Name = "timeLabel";
            this.timeLabel.Size = new System.Drawing.Size(145, 45);
            this.timeLabel.TabIndex = 0;
            this.timeLabel.Text = "1.00.00";
            this.timeLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // framesPerTickUpDown
            // 
            this.framesPerTickUpDown.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.framesPerTickUpDown.Location = new System.Drawing.Point(225, 12);
            this.framesPerTickUpDown.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.framesPerTickUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.framesPerTickUpDown.Name = "framesPerTickUpDown";
            this.framesPerTickUpDown.Size = new System.Drawing.Size(63, 20);
            this.framesPerTickUpDown.TabIndex = 1;
            this.framesPerTickUpDown.Value = new decimal(new int[] {
            12,
            0,
            0,
            0});
            this.framesPerTickUpDown.ValueChanged += new System.EventHandler(this.framesPerTickUpDown_ValueChanged);
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(158, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(61, 28);
            this.label1.TabIndex = 2;
            this.label1.Text = "Frames Per Tick";
            // 
            // bpmLabel
            // 
            this.bpmLabel.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.bpmLabel.AutoSize = true;
            this.bpmLabel.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bpmLabel.ForeColor = System.Drawing.Color.White;
            this.bpmLabel.Location = new System.Drawing.Point(294, 15);
            this.bpmLabel.Name = "bpmLabel";
            this.bpmLabel.Size = new System.Drawing.Size(81, 14);
            this.bpmLabel.TabIndex = 2;
            this.bpmLabel.Text = "= 120 BPM";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 3;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableLayoutPanel1.Controls.Add(this.playButton, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.recordButton, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.rewindButton, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Left;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(178, 48);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // playButton
            // 
            this.playButton.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.playButton.AutoSize = true;
            this.playButton.BackColor = System.Drawing.SystemColors.ControlDark;
            this.playButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.playButton.Location = new System.Drawing.Point(53, 3);
            this.playButton.Name = "playButton";
            this.playButton.Size = new System.Drawing.Size(72, 42);
            this.playButton.TabIndex = 1;
            this.playButton.Text = "›";
            this.playButton.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.playButton.UseVisualStyleBackColor = false;
            // 
            // recordButton
            // 
            this.recordButton.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.recordButton.AutoSize = true;
            this.recordButton.BackColor = System.Drawing.SystemColors.ControlDark;
            this.recordButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.recordButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.recordButton.Location = new System.Drawing.Point(131, 3);
            this.recordButton.Name = "recordButton";
            this.recordButton.Size = new System.Drawing.Size(44, 42);
            this.recordButton.TabIndex = 0;
            this.recordButton.Text = "●";
            this.recordButton.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.recordButton.UseVisualStyleBackColor = false;
            // 
            // rewindButton
            // 
            this.rewindButton.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.rewindButton.AutoSize = true;
            this.rewindButton.BackColor = System.Drawing.SystemColors.ControlDark;
            this.rewindButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rewindButton.Location = new System.Drawing.Point(3, 3);
            this.rewindButton.Name = "rewindButton";
            this.rewindButton.Size = new System.Drawing.Size(44, 42);
            this.rewindButton.TabIndex = 0;
            this.rewindButton.Text = "‹‹";
            this.rewindButton.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.rewindButton.UseVisualStyleBackColor = false;
            // 
            // mainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(947, 567);
            this.Controls.Add(this.toolStripContainer1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "mainWindow";
            this.Text = "Vorlon2//Seq";
            this.toolStripContainer1.BottomToolStripPanel.ResumeLayout(false);
            this.toolStripContainer1.BottomToolStripPanel.PerformLayout();
            this.toolStripContainer1.ContentPanel.ResumeLayout(false);
            this.toolStripContainer1.ResumeLayout(false);
            this.toolStripContainer1.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.mainSplit.Panel1.ResumeLayout(false);
            this.mainSplit.Panel2.ResumeLayout(false);
            this.mainSplit.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.arrangeTab.ResumeLayout(false);
            this.composeTab.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.framesPerTickUpDown)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.SplitContainer mainSplit;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Button recordButton;
        private System.Windows.Forms.Button rewindButton;
        private System.Windows.Forms.Button playButton;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Label timeLabel;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripContainer toolStripContainer1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem closeToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private ChannelEditor channelEditor1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage arrangeTab;
        private System.Windows.Forms.TabPage composeTab;
        private System.Windows.Forms.NumericUpDown framesPerTickUpDown;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label bpmLabel;
        private ClipEditor clipEditor1;
    }
}

