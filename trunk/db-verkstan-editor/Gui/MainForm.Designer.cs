namespace VerkstanEditor.Gui
{
    partial class mainForm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(mainForm));
            this.previewPanel = new System.Windows.Forms.Panel();
            this.transportPanel = new System.Windows.Forms.Panel();
            this.transportTimeLabel = new System.Windows.Forms.Label();
            this.renderTimer = new System.Windows.Forms.Timer(this.components);
            this.mainMenu = new System.Windows.Forms.MenuStrip();
            this.mainMenuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.mainMenuFileNew = new System.Windows.Forms.ToolStripMenuItem();
            this.mainMenuFileOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.mainMenuFileExit = new System.Windows.Forms.ToolStripMenuItem();
            this.mainMenuHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.mainMenuHelpAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripContainer1 = new System.Windows.Forms.ToolStripContainer();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.splitContainer3 = new System.Windows.Forms.SplitContainer();
            this.splitContainer4 = new System.Windows.Forms.SplitContainer();
            this.transportPanel.SuspendLayout();
            this.mainMenu.SuspendLayout();
            this.toolStripContainer1.ContentPanel.SuspendLayout();
            this.toolStripContainer1.SuspendLayout();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.splitContainer3.Panel1.SuspendLayout();
            this.splitContainer3.SuspendLayout();
            this.splitContainer4.SuspendLayout();
            this.SuspendLayout();
            // 
            // previewPanel
            // 
            this.previewPanel.BackColor = System.Drawing.SystemColors.ControlText;
            this.previewPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.previewPanel.Location = new System.Drawing.Point(0, 0);
            this.previewPanel.Name = "previewPanel";
            this.previewPanel.Size = new System.Drawing.Size(467, 86);
            this.previewPanel.TabIndex = 0;
            this.previewPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseMove);
            this.previewPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseDown);
            this.previewPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseUp);
            this.previewPanel.SizeChanged += new System.EventHandler(this.PreviewPanel_SizeChanged);
            // 
            // transportPanel
            // 
            this.transportPanel.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.transportPanel.Controls.Add(this.transportTimeLabel);
            this.transportPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.transportPanel.Location = new System.Drawing.Point(0, 0);
            this.transportPanel.Name = "transportPanel";
            this.transportPanel.Size = new System.Drawing.Size(643, 58);
            this.transportPanel.TabIndex = 0;
            this.transportPanel.SizeChanged += new System.EventHandler(this.TransportPanel_SizeChanged);
            // 
            // transportTimeLabel
            // 
            this.transportTimeLabel.AutoSize = true;
            this.transportTimeLabel.Font = new System.Drawing.Font("David", 30F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.transportTimeLabel.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.transportTimeLabel.Location = new System.Drawing.Point(238, 1);
            this.transportTimeLabel.Name = "transportTimeLabel";
            this.transportTimeLabel.Size = new System.Drawing.Size(180, 46);
            this.transportTimeLabel.TabIndex = 0;
            this.transportTimeLabel.Text = "03:00:00";
            this.transportTimeLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // renderTimer
            // 
            this.renderTimer.Interval = 10;
            this.renderTimer.Tick += new System.EventHandler(this.RenderTimer_Tick);
            // 
            // mainMenu
            // 
            this.mainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mainMenuFile,
            this.mainMenuHelp});
            this.mainMenu.Location = new System.Drawing.Point(0, 0);
            this.mainMenu.Name = "mainMenu";
            this.mainMenu.Size = new System.Drawing.Size(643, 24);
            this.mainMenu.TabIndex = 0;
            this.mainMenu.Text = "menuStrip1";
            // 
            // mainMenuFile
            // 
            this.mainMenuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mainMenuFileNew,
            this.mainMenuFileOpen,
            this.mainMenuFileExit});
            this.mainMenuFile.Name = "mainMenuFile";
            this.mainMenuFile.Size = new System.Drawing.Size(35, 20);
            this.mainMenuFile.Text = "File";
            // 
            // mainMenuFileNew
            // 
            this.mainMenuFileNew.Name = "mainMenuFileNew";
            this.mainMenuFileNew.Size = new System.Drawing.Size(100, 22);
            this.mainMenuFileNew.Text = "New";
            // 
            // mainMenuFileOpen
            // 
            this.mainMenuFileOpen.Name = "mainMenuFileOpen";
            this.mainMenuFileOpen.Size = new System.Drawing.Size(100, 22);
            this.mainMenuFileOpen.Text = "Open";
            // 
            // mainMenuFileExit
            // 
            this.mainMenuFileExit.Name = "mainMenuFileExit";
            this.mainMenuFileExit.Size = new System.Drawing.Size(100, 22);
            this.mainMenuFileExit.Text = "Exit";
            // 
            // mainMenuHelp
            // 
            this.mainMenuHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mainMenuHelpAbout});
            this.mainMenuHelp.Name = "mainMenuHelp";
            this.mainMenuHelp.Size = new System.Drawing.Size(40, 20);
            this.mainMenuHelp.Text = "Help";
            // 
            // mainMenuHelpAbout
            // 
            this.mainMenuHelpAbout.Name = "mainMenuHelpAbout";
            this.mainMenuHelpAbout.Size = new System.Drawing.Size(103, 22);
            this.mainMenuHelpAbout.Text = "About";
            // 
            // toolStripContainer1
            // 
            // 
            // toolStripContainer1.ContentPanel
            // 
            this.toolStripContainer1.ContentPanel.Controls.Add(this.splitContainer1);
            this.toolStripContainer1.ContentPanel.Size = new System.Drawing.Size(643, 233);
            this.toolStripContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.toolStripContainer1.Location = new System.Drawing.Point(0, 24);
            this.toolStripContainer1.Name = "toolStripContainer1";
            this.toolStripContainer1.Size = new System.Drawing.Size(643, 233);
            this.toolStripContainer1.TabIndex = 0;
            this.toolStripContainer1.Text = "toolStripContainer1";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Location = new System.Drawing.Point(0, 257);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(643, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.transportPanel);
            this.splitContainer1.Size = new System.Drawing.Size(643, 233);
            this.splitContainer1.SplitterDistance = 171;
            this.splitContainer1.TabIndex = 3;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.splitContainer3);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.splitContainer4);
            this.splitContainer2.Size = new System.Drawing.Size(643, 171);
            this.splitContainer2.SplitterDistance = 467;
            this.splitContainer2.TabIndex = 0;
            // 
            // splitContainer3
            // 
            this.splitContainer3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer3.Location = new System.Drawing.Point(0, 0);
            this.splitContainer3.Name = "splitContainer3";
            this.splitContainer3.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer3.Panel1
            // 
            this.splitContainer3.Panel1.Controls.Add(this.previewPanel);
            // 
            // splitContainer3.Panel2
            // 
            this.splitContainer3.Panel2.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.splitContainer3.Size = new System.Drawing.Size(467, 171);
            this.splitContainer3.SplitterDistance = 86;
            this.splitContainer3.TabIndex = 0;
            // 
            // splitContainer4
            // 
            this.splitContainer4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer4.Location = new System.Drawing.Point(0, 0);
            this.splitContainer4.Name = "splitContainer4";
            this.splitContainer4.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer4.Panel1
            // 
            this.splitContainer4.Panel1.BackColor = System.Drawing.SystemColors.ControlDark;
            // 
            // splitContainer4.Panel2
            // 
            this.splitContainer4.Panel2.BackColor = System.Drawing.SystemColors.ControlDark;
            this.splitContainer4.Size = new System.Drawing.Size(172, 171);
            this.splitContainer4.SplitterDistance = 86;
            this.splitContainer4.TabIndex = 0;
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(643, 279);
            this.Controls.Add(this.toolStripContainer1);
            this.Controls.Add(this.mainMenu);
            this.Controls.Add(this.statusStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.mainMenu;
            this.Name = "mainForm";
            this.Text = "db - Verkstan 1";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.transportPanel.ResumeLayout(false);
            this.transportPanel.PerformLayout();
            this.mainMenu.ResumeLayout(false);
            this.mainMenu.PerformLayout();
            this.toolStripContainer1.ContentPanel.ResumeLayout(false);
            this.toolStripContainer1.ResumeLayout(false);
            this.toolStripContainer1.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            this.splitContainer2.ResumeLayout(false);
            this.splitContainer3.Panel1.ResumeLayout(false);
            this.splitContainer3.ResumeLayout(false);
            this.splitContainer4.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer renderTimer;
        private System.Windows.Forms.Panel previewPanel;
        private System.Windows.Forms.Panel transportPanel;
        private System.Windows.Forms.Label transportTimeLabel;
        private System.Windows.Forms.MenuStrip mainMenu;
        private System.Windows.Forms.ToolStripMenuItem mainMenuFile;
        private System.Windows.Forms.ToolStripMenuItem mainMenuFileNew;
        private System.Windows.Forms.ToolStripMenuItem mainMenuFileOpen;
        private System.Windows.Forms.ToolStripMenuItem mainMenuFileExit;
        private System.Windows.Forms.ToolStripMenuItem mainMenuHelp;
        private System.Windows.Forms.ToolStripMenuItem mainMenuHelpAbout;
        private System.Windows.Forms.ToolStripContainer toolStripContainer1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.SplitContainer splitContainer3;
        private System.Windows.Forms.SplitContainer splitContainer4;
    }
}

