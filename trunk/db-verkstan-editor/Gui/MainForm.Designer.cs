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
            this.previewComposeSplitContainer = new System.Windows.Forms.SplitContainer();
            this.previewPanel = new System.Windows.Forms.Panel();
            this.composeTransportSplitContainer = new System.Windows.Forms.SplitContainer();
            this.operatorPanel = new System.Windows.Forms.Panel();
            this.operatorsPropertiesSplitContainer = new System.Windows.Forms.SplitContainer();
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
            this.previewComposeSplitContainer.Panel1.SuspendLayout();
            this.previewComposeSplitContainer.Panel2.SuspendLayout();
            this.previewComposeSplitContainer.SuspendLayout();
            this.composeTransportSplitContainer.Panel1.SuspendLayout();
            this.composeTransportSplitContainer.Panel2.SuspendLayout();
            this.composeTransportSplitContainer.SuspendLayout();
            this.operatorPanel.SuspendLayout();
            this.operatorsPropertiesSplitContainer.SuspendLayout();
            this.transportPanel.SuspendLayout();
            this.mainMenu.SuspendLayout();
            this.toolStripContainer1.ContentPanel.SuspendLayout();
            this.toolStripContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // previewComposeSplitContainer
            // 
            this.previewComposeSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.previewComposeSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.previewComposeSplitContainer.Name = "previewComposeSplitContainer";
            this.previewComposeSplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // previewComposeSplitContainer.Panel1
            // 
            this.previewComposeSplitContainer.Panel1.Controls.Add(this.previewPanel);
            // 
            // previewComposeSplitContainer.Panel2
            // 
            this.previewComposeSplitContainer.Panel2.Controls.Add(this.composeTransportSplitContainer);
            this.previewComposeSplitContainer.Size = new System.Drawing.Size(643, 208);
            this.previewComposeSplitContainer.SplitterDistance = 72;
            this.previewComposeSplitContainer.TabIndex = 0;
            // 
            // previewPanel
            // 
            this.previewPanel.BackColor = System.Drawing.SystemColors.ControlText;
            this.previewPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.previewPanel.Location = new System.Drawing.Point(0, 0);
            this.previewPanel.Name = "previewPanel";
            this.previewPanel.Size = new System.Drawing.Size(643, 72);
            this.previewPanel.TabIndex = 0;
            this.previewPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseDown);
            this.previewPanel.SizeChanged += new System.EventHandler(this.PreviewPanel_SizeChanged);
            // 
            // composeTransportSplitContainer
            // 
            this.composeTransportSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.composeTransportSplitContainer.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.composeTransportSplitContainer.IsSplitterFixed = true;
            this.composeTransportSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.composeTransportSplitContainer.Name = "composeTransportSplitContainer";
            this.composeTransportSplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // composeTransportSplitContainer.Panel1
            // 
            this.composeTransportSplitContainer.Panel1.Controls.Add(this.operatorPanel);
            // 
            // composeTransportSplitContainer.Panel2
            // 
            this.composeTransportSplitContainer.Panel2.Controls.Add(this.transportPanel);
            this.composeTransportSplitContainer.Size = new System.Drawing.Size(643, 132);
            this.composeTransportSplitContainer.SplitterDistance = 74;
            this.composeTransportSplitContainer.TabIndex = 0;
            // 
            // operatorPanel
            // 
            this.operatorPanel.Controls.Add(this.operatorsPropertiesSplitContainer);
            this.operatorPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.operatorPanel.Location = new System.Drawing.Point(0, 0);
            this.operatorPanel.Name = "operatorPanel";
            this.operatorPanel.Size = new System.Drawing.Size(643, 74);
            this.operatorPanel.TabIndex = 0;
            // 
            // operatorsPropertiesSplitContainer
            // 
            this.operatorsPropertiesSplitContainer.BackColor = System.Drawing.SystemColors.Control;
            this.operatorsPropertiesSplitContainer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.operatorsPropertiesSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.operatorsPropertiesSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.operatorsPropertiesSplitContainer.Name = "operatorsPropertiesSplitContainer";
            // 
            // operatorsPropertiesSplitContainer.Panel1
            // 
            this.operatorsPropertiesSplitContainer.Panel1.AutoScroll = true;
            this.operatorsPropertiesSplitContainer.Panel1.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            // 
            // operatorsPropertiesSplitContainer.Panel2
            // 
            this.operatorsPropertiesSplitContainer.Panel2.BackColor = System.Drawing.SystemColors.ControlDark;
            this.operatorsPropertiesSplitContainer.Size = new System.Drawing.Size(643, 74);
            this.operatorsPropertiesSplitContainer.SplitterDistance = 474;
            this.operatorsPropertiesSplitContainer.TabIndex = 0;
            // 
            // transportPanel
            // 
            this.transportPanel.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.transportPanel.Controls.Add(this.transportTimeLabel);
            this.transportPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.transportPanel.Location = new System.Drawing.Point(0, 0);
            this.transportPanel.Name = "transportPanel";
            this.transportPanel.Size = new System.Drawing.Size(643, 54);
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
            this.toolStripContainer1.ContentPanel.Controls.Add(this.previewComposeSplitContainer);
            this.toolStripContainer1.ContentPanel.Size = new System.Drawing.Size(643, 208);
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
            this.previewComposeSplitContainer.Panel1.ResumeLayout(false);
            this.previewComposeSplitContainer.Panel2.ResumeLayout(false);
            this.previewComposeSplitContainer.ResumeLayout(false);
            this.composeTransportSplitContainer.Panel1.ResumeLayout(false);
            this.composeTransportSplitContainer.Panel2.ResumeLayout(false);
            this.composeTransportSplitContainer.ResumeLayout(false);
            this.operatorPanel.ResumeLayout(false);
            this.operatorsPropertiesSplitContainer.ResumeLayout(false);
            this.transportPanel.ResumeLayout(false);
            this.transportPanel.PerformLayout();
            this.mainMenu.ResumeLayout(false);
            this.mainMenu.PerformLayout();
            this.toolStripContainer1.ContentPanel.ResumeLayout(false);
            this.toolStripContainer1.ResumeLayout(false);
            this.toolStripContainer1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.SplitContainer previewComposeSplitContainer;
        private System.Windows.Forms.Timer renderTimer;
        private System.Windows.Forms.Panel previewPanel;
        private System.Windows.Forms.SplitContainer composeTransportSplitContainer;
        private System.Windows.Forms.Panel operatorPanel;
        private System.Windows.Forms.Panel transportPanel;
        private System.Windows.Forms.Label transportTimeLabel;
        private System.Windows.Forms.SplitContainer operatorsPropertiesSplitContainer;
        private System.Windows.Forms.MenuStrip mainMenu;
        private System.Windows.Forms.ToolStripMenuItem mainMenuFile;
        private System.Windows.Forms.ToolStripMenuItem mainMenuFileNew;
        private System.Windows.Forms.ToolStripMenuItem mainMenuFileOpen;
        private System.Windows.Forms.ToolStripMenuItem mainMenuFileExit;
        private System.Windows.Forms.ToolStripMenuItem mainMenuHelp;
        private System.Windows.Forms.ToolStripMenuItem mainMenuHelpAbout;
        private System.Windows.Forms.ToolStripContainer toolStripContainer1;
        private System.Windows.Forms.StatusStrip statusStrip1;
    }
}

