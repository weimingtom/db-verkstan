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
            this.fastRenderTimer = new System.Windows.Forms.Timer(this.components);
            this.mainMenu = new System.Windows.Forms.MenuStrip();
            this.mainMenuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.mainMenuFileNew = new System.Windows.Forms.ToolStripMenuItem();
            this.mainMenuFileOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.mainMenuFileExit = new System.Windows.Forms.ToolStripMenuItem();
            this.mainMenuHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.mainMenuHelpAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripContainer1 = new System.Windows.Forms.ToolStripContainer();
            this.mainTransportSplitContainer = new System.Windows.Forms.SplitContainer();
            this.mainLeftAndRightSplitContainer = new System.Windows.Forms.SplitContainer();
            this.previewBoardSplitContainer = new System.Windows.Forms.SplitContainer();
            this.previewPanel = new System.Windows.Forms.Panel();
            this.boardTabControl = new System.Windows.Forms.TabControl();
            this.operatorsTab = new System.Windows.Forms.TabPage();
            this.scenesTab = new System.Windows.Forms.TabPage();
            this.channelTab = new System.Windows.Forms.TabPage();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.slowRenderTimer = new System.Windows.Forms.Timer(this.components);
            this.operatorPageControl1 = new VerkstanEditor.Gui.OperatorPage();
            this.operatorPropertyGrid = new VerkstanEditor.Gui.OperatorPropertyGrid();
            this.transport1 = new VerkstanEditor.Gui.Transport();
            this.timeline1 = new VerkstanEditor.Gui.Timeline();
            this.mainMenu.SuspendLayout();
            this.toolStripContainer1.ContentPanel.SuspendLayout();
            this.toolStripContainer1.SuspendLayout();
            this.mainTransportSplitContainer.Panel1.SuspendLayout();
            this.mainTransportSplitContainer.Panel2.SuspendLayout();
            this.mainTransportSplitContainer.SuspendLayout();
            this.mainLeftAndRightSplitContainer.Panel1.SuspendLayout();
            this.mainLeftAndRightSplitContainer.Panel2.SuspendLayout();
            this.mainLeftAndRightSplitContainer.SuspendLayout();
            this.previewBoardSplitContainer.Panel1.SuspendLayout();
            this.previewBoardSplitContainer.Panel2.SuspendLayout();
            this.previewBoardSplitContainer.SuspendLayout();
            this.boardTabControl.SuspendLayout();
            this.operatorsTab.SuspendLayout();
            this.scenesTab.SuspendLayout();
            this.SuspendLayout();
            // 
            // fastRenderTimer
            // 
            this.fastRenderTimer.Interval = 10;
            this.fastRenderTimer.Tick += new System.EventHandler(this.FastRenderTimer_Tick);
            // 
            // mainMenu
            // 
            this.mainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mainMenuFile,
            this.mainMenuHelp});
            this.mainMenu.Location = new System.Drawing.Point(0, 0);
            this.mainMenu.Name = "mainMenu";
            this.mainMenu.Size = new System.Drawing.Size(766, 24);
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
            this.toolStripContainer1.ContentPanel.Controls.Add(this.mainTransportSplitContainer);
            this.toolStripContainer1.ContentPanel.Size = new System.Drawing.Size(766, 306);
            this.toolStripContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.toolStripContainer1.Location = new System.Drawing.Point(0, 24);
            this.toolStripContainer1.Name = "toolStripContainer1";
            this.toolStripContainer1.Size = new System.Drawing.Size(766, 331);
            this.toolStripContainer1.TabIndex = 0;
            this.toolStripContainer1.Text = "toolStripContainer1";
            // 
            // mainTransportSplitContainer
            // 
            this.mainTransportSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainTransportSplitContainer.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.mainTransportSplitContainer.IsSplitterFixed = true;
            this.mainTransportSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.mainTransportSplitContainer.Name = "mainTransportSplitContainer";
            this.mainTransportSplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // mainTransportSplitContainer.Panel1
            // 
            this.mainTransportSplitContainer.Panel1.Controls.Add(this.mainLeftAndRightSplitContainer);
            // 
            // mainTransportSplitContainer.Panel2
            // 
            this.mainTransportSplitContainer.Panel2.Controls.Add(this.transport1);
            this.mainTransportSplitContainer.Size = new System.Drawing.Size(766, 306);
            this.mainTransportSplitContainer.SplitterDistance = 238;
            this.mainTransportSplitContainer.TabIndex = 0;
            // 
            // mainLeftAndRightSplitContainer
            // 
            this.mainLeftAndRightSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainLeftAndRightSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.mainLeftAndRightSplitContainer.Name = "mainLeftAndRightSplitContainer";
            // 
            // mainLeftAndRightSplitContainer.Panel1
            // 
            this.mainLeftAndRightSplitContainer.Panel1.Controls.Add(this.previewBoardSplitContainer);
            // 
            // mainLeftAndRightSplitContainer.Panel2
            // 
            this.mainLeftAndRightSplitContainer.Panel2.Controls.Add(this.operatorPropertyGrid);
            this.mainLeftAndRightSplitContainer.Size = new System.Drawing.Size(766, 238);
            this.mainLeftAndRightSplitContainer.SplitterDistance = 556;
            this.mainLeftAndRightSplitContainer.TabIndex = 0;
            // 
            // previewBoardSplitContainer
            // 
            this.previewBoardSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.previewBoardSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.previewBoardSplitContainer.Margin = new System.Windows.Forms.Padding(0);
            this.previewBoardSplitContainer.Name = "previewBoardSplitContainer";
            this.previewBoardSplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // previewBoardSplitContainer.Panel1
            // 
            this.previewBoardSplitContainer.Panel1.Controls.Add(this.previewPanel);
            // 
            // previewBoardSplitContainer.Panel2
            // 
            this.previewBoardSplitContainer.Panel2.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.previewBoardSplitContainer.Panel2.Controls.Add(this.boardTabControl);
            this.previewBoardSplitContainer.Size = new System.Drawing.Size(556, 238);
            this.previewBoardSplitContainer.SplitterDistance = 118;
            this.previewBoardSplitContainer.TabIndex = 0;
            // 
            // previewPanel
            // 
            this.previewPanel.BackColor = System.Drawing.SystemColors.ControlText;
            this.previewPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.previewPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.previewPanel.Location = new System.Drawing.Point(0, 0);
            this.previewPanel.Name = "previewPanel";
            this.previewPanel.Size = new System.Drawing.Size(556, 118);
            this.previewPanel.TabIndex = 0;
            this.previewPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseMove);
            this.previewPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseDown);
            this.previewPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseUp);
            this.previewPanel.SizeChanged += new System.EventHandler(this.PreviewPanel_SizeChanged);
            // 
            // boardTabControl
            // 
            this.boardTabControl.Appearance = System.Windows.Forms.TabAppearance.Buttons;
            this.boardTabControl.Controls.Add(this.operatorsTab);
            this.boardTabControl.Controls.Add(this.scenesTab);
            this.boardTabControl.Controls.Add(this.channelTab);
            this.boardTabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.boardTabControl.Location = new System.Drawing.Point(0, 0);
            this.boardTabControl.Margin = new System.Windows.Forms.Padding(0);
            this.boardTabControl.Name = "boardTabControl";
            this.boardTabControl.SelectedIndex = 0;
            this.boardTabControl.Size = new System.Drawing.Size(556, 116);
            this.boardTabControl.TabIndex = 0;
            // 
            // operatorsTab
            // 
            this.operatorsTab.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.operatorsTab.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.operatorsTab.Controls.Add(this.operatorPageControl1);
            this.operatorsTab.Location = new System.Drawing.Point(4, 25);
            this.operatorsTab.Margin = new System.Windows.Forms.Padding(0);
            this.operatorsTab.Name = "operatorsTab";
            this.operatorsTab.Size = new System.Drawing.Size(548, 87);
            this.operatorsTab.TabIndex = 2;
            this.operatorsTab.Text = "Operators";
            this.operatorsTab.UseVisualStyleBackColor = true;
            // 
            // scenesTab
            // 
            this.scenesTab.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.scenesTab.Controls.Add(this.timeline1);
            this.scenesTab.Location = new System.Drawing.Point(4, 25);
            this.scenesTab.Name = "scenesTab";
            this.scenesTab.Size = new System.Drawing.Size(548, 87);
            this.scenesTab.TabIndex = 1;
            this.scenesTab.Text = "Scenes";
            this.scenesTab.UseVisualStyleBackColor = true;
            // 
            // channelTab
            // 
            this.channelTab.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.channelTab.Location = new System.Drawing.Point(4, 25);
            this.channelTab.Name = "channelTab";
            this.channelTab.Size = new System.Drawing.Size(548, 87);
            this.channelTab.TabIndex = 3;
            this.channelTab.Text = "Channel";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Location = new System.Drawing.Point(0, 355);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(766, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // slowRenderTimer
            // 
            this.slowRenderTimer.Tick += new System.EventHandler(this.slowRenderTimer_Tick);
            // 
            // operatorPageControl1
            // 
            this.operatorPageControl1.BackColor = System.Drawing.SystemColors.Control;
            this.operatorPageControl1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.operatorPageControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.operatorPageControl1.Location = new System.Drawing.Point(0, 0);
            this.operatorPageControl1.Name = "operatorPageControl1";
            this.operatorPageControl1.Size = new System.Drawing.Size(548, 87);
            this.operatorPageControl1.TabIndex = 0;
            // 
            // operatorPropertyGrid
            // 
            this.operatorPropertyGrid.AutoScroll = true;
            this.operatorPropertyGrid.AutoSize = true;
            this.operatorPropertyGrid.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.operatorPropertyGrid.BackColor = System.Drawing.SystemColors.ControlDark;
            this.operatorPropertyGrid.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.operatorPropertyGrid.Dock = System.Windows.Forms.DockStyle.Fill;
            this.operatorPropertyGrid.Location = new System.Drawing.Point(0, 0);
            this.operatorPropertyGrid.Name = "operatorPropertyGrid";
            this.operatorPropertyGrid.Operator = null;
            this.operatorPropertyGrid.Size = new System.Drawing.Size(206, 238);
            this.operatorPropertyGrid.TabIndex = 0;
            // 
            // transport1
            // 
            this.transport1.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.transport1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.transport1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.transport1.Location = new System.Drawing.Point(0, 0);
            this.transport1.Name = "transport1";
            this.transport1.Size = new System.Drawing.Size(766, 64);
            this.transport1.TabIndex = 0;
            // 
            // timeline1
            // 
            this.timeline1.BackColor = System.Drawing.SystemColors.Control;
            this.timeline1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.timeline1.Location = new System.Drawing.Point(0, 0);
            this.timeline1.Name = "timeline1";
            this.timeline1.Size = new System.Drawing.Size(548, 87);
            this.timeline1.TabIndex = 0;
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(766, 377);
            this.Controls.Add(this.toolStripContainer1);
            this.Controls.Add(this.mainMenu);
            this.Controls.Add(this.statusStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.mainMenu;
            this.Name = "mainForm";
            this.Text = "db - Verkstan 1";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.mainMenu.ResumeLayout(false);
            this.mainMenu.PerformLayout();
            this.toolStripContainer1.ContentPanel.ResumeLayout(false);
            this.toolStripContainer1.ResumeLayout(false);
            this.toolStripContainer1.PerformLayout();
            this.mainTransportSplitContainer.Panel1.ResumeLayout(false);
            this.mainTransportSplitContainer.Panel2.ResumeLayout(false);
            this.mainTransportSplitContainer.ResumeLayout(false);
            this.mainLeftAndRightSplitContainer.Panel1.ResumeLayout(false);
            this.mainLeftAndRightSplitContainer.Panel2.ResumeLayout(false);
            this.mainLeftAndRightSplitContainer.Panel2.PerformLayout();
            this.mainLeftAndRightSplitContainer.ResumeLayout(false);
            this.previewBoardSplitContainer.Panel1.ResumeLayout(false);
            this.previewBoardSplitContainer.Panel2.ResumeLayout(false);
            this.previewBoardSplitContainer.ResumeLayout(false);
            this.boardTabControl.ResumeLayout(false);
            this.operatorsTab.ResumeLayout(false);
            this.scenesTab.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer fastRenderTimer;
        private System.Windows.Forms.Panel previewPanel;
        private System.Windows.Forms.MenuStrip mainMenu;
        private System.Windows.Forms.ToolStripMenuItem mainMenuFile;
        private System.Windows.Forms.ToolStripMenuItem mainMenuFileNew;
        private System.Windows.Forms.ToolStripMenuItem mainMenuFileOpen;
        private System.Windows.Forms.ToolStripMenuItem mainMenuFileExit;
        private System.Windows.Forms.ToolStripMenuItem mainMenuHelp;
        private System.Windows.Forms.ToolStripMenuItem mainMenuHelpAbout;
        private System.Windows.Forms.ToolStripContainer toolStripContainer1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.SplitContainer mainLeftAndRightSplitContainer;
        private System.Windows.Forms.SplitContainer previewBoardSplitContainer;
        private VerkstanEditor.Gui.OperatorPropertyGrid operatorPropertyGrid;
        private System.Windows.Forms.TabControl boardTabControl;
        private System.Windows.Forms.TabPage scenesTab;
        private System.Windows.Forms.TabPage operatorsTab;
        private System.Windows.Forms.TabPage channelTab;
        private Transport transport1;
        private System.Windows.Forms.SplitContainer mainTransportSplitContainer;
        private System.Windows.Forms.Timer slowRenderTimer;
        private OperatorPage operatorPageControl1;
        private Timeline timeline1;
    }
}

