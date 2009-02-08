namespace db_director
{
    partial class Form1
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
            this.mainSplit = new System.Windows.Forms.SplitContainer();
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openDemoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.loadTweakablesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveTweakablesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveTweakablesAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.exportTweakablesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.transport1 = new VerkstanEditor.Gui.Transport();
            this.demoSplit = new System.Windows.Forms.SplitContainer();
            this.mainSplit.Panel1.SuspendLayout();
            this.mainSplit.Panel2.SuspendLayout();
            this.mainSplit.SuspendLayout();
            this.menuStrip.SuspendLayout();
            this.demoSplit.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainSplit
            // 
            this.mainSplit.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainSplit.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.mainSplit.IsSplitterFixed = true;
            this.mainSplit.Location = new System.Drawing.Point(0, 24);
            this.mainSplit.Name = "mainSplit";
            this.mainSplit.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // mainSplit.Panel1
            // 
            this.mainSplit.Panel1.Controls.Add(this.demoSplit);
            // 
            // mainSplit.Panel2
            // 
            this.mainSplit.Panel2.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.mainSplit.Panel2.Controls.Add(this.transport1);
            this.mainSplit.Size = new System.Drawing.Size(703, 395);
            this.mainSplit.SplitterDistance = 329;
            this.mainSplit.TabIndex = 0;
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
            this.menuStrip.Size = new System.Drawing.Size(703, 24);
            this.menuStrip.TabIndex = 1;
            this.menuStrip.Text = "menuStrip";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openDemoToolStripMenuItem,
            this.toolStripMenuItem1,
            this.loadTweakablesToolStripMenuItem,
            this.saveTweakablesToolStripMenuItem,
            this.saveTweakablesAsToolStripMenuItem,
            this.toolStripMenuItem2,
            this.exportTweakablesToolStripMenuItem,
            this.toolStripMenuItem3,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(35, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openDemoToolStripMenuItem
            // 
            this.openDemoToolStripMenuItem.Name = "openDemoToolStripMenuItem";
            this.openDemoToolStripMenuItem.Size = new System.Drawing.Size(204, 22);
            this.openDemoToolStripMenuItem.Text = "Open demo...";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(201, 6);
            // 
            // loadTweakablesToolStripMenuItem
            // 
            this.loadTweakablesToolStripMenuItem.Name = "loadTweakablesToolStripMenuItem";
            this.loadTweakablesToolStripMenuItem.Size = new System.Drawing.Size(204, 22);
            this.loadTweakablesToolStripMenuItem.Text = "Load tweakables...";
            // 
            // saveTweakablesToolStripMenuItem
            // 
            this.saveTweakablesToolStripMenuItem.Name = "saveTweakablesToolStripMenuItem";
            this.saveTweakablesToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveTweakablesToolStripMenuItem.Size = new System.Drawing.Size(204, 22);
            this.saveTweakablesToolStripMenuItem.Text = "Save tweakables";
            // 
            // saveTweakablesAsToolStripMenuItem
            // 
            this.saveTweakablesAsToolStripMenuItem.Name = "saveTweakablesAsToolStripMenuItem";
            this.saveTweakablesAsToolStripMenuItem.Size = new System.Drawing.Size(204, 22);
            this.saveTweakablesAsToolStripMenuItem.Text = "Save tweakables as...";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(201, 6);
            // 
            // exportTweakablesToolStripMenuItem
            // 
            this.exportTweakablesToolStripMenuItem.Name = "exportTweakablesToolStripMenuItem";
            this.exportTweakablesToolStripMenuItem.Size = new System.Drawing.Size(204, 22);
            this.exportTweakablesToolStripMenuItem.Text = "Export tweakables...";
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(201, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(204, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            // 
            // transport1
            // 
            this.transport1.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.transport1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.transport1.Location = new System.Drawing.Point(0, 0);
            this.transport1.Name = "transport1";
            this.transport1.Size = new System.Drawing.Size(703, 62);
            this.transport1.TabIndex = 0;
            // 
            // demoSplit
            // 
            this.demoSplit.Dock = System.Windows.Forms.DockStyle.Fill;
            this.demoSplit.Location = new System.Drawing.Point(0, 0);
            this.demoSplit.Name = "demoSplit";
            this.demoSplit.Size = new System.Drawing.Size(703, 329);
            this.demoSplit.SplitterDistance = 526;
            this.demoSplit.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(703, 419);
            this.Controls.Add(this.mainSplit);
            this.Controls.Add(this.menuStrip);
            this.MainMenuStrip = this.menuStrip;
            this.Name = "Form1";
            this.Text = "Darkbits® Verkstan™ Enhanced Graphical Demonstration Solutions Productivity Suite" +
                "™ Director";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.mainSplit.Panel1.ResumeLayout(false);
            this.mainSplit.Panel2.ResumeLayout(false);
            this.mainSplit.ResumeLayout(false);
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.demoSplit.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.SplitContainer mainSplit;
        private VerkstanEditor.Gui.Transport transport1;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openDemoToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem loadTweakablesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveTweakablesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveTweakablesAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem exportTweakablesToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.SplitContainer demoSplit;
    }
}

