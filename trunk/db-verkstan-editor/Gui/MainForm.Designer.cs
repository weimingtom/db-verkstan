namespace VerkstanEditor.Gui
{
    partial class MainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
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
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.stacksTab = new System.Windows.Forms.TabPage();
            this.operatorPageView1 = new VerkstanEditor.Gui.OperatorPageView();
            this.timelinesTab = new System.Windows.Forms.TabPage();
            this.timelinesView1 = new VerkstanEditor.Gui.TimelinesView();
            this.clipTab = new System.Windows.Forms.TabPage();
            this.operatorPropertyGrid = new VerkstanEditor.Gui.OperatorPropertyGrid();
            this.transport1 = new VerkstanEditor.Gui.Transport();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.slowRenderTimer = new System.Windows.Forms.Timer(this.components);
            this.clipView1 = new VerkstanEditor.Gui.ClipView();
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
            this.tabControl1.SuspendLayout();
            this.stacksTab.SuspendLayout();
            this.timelinesTab.SuspendLayout();
            this.clipTab.SuspendLayout();
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
            this.toolStripContainer1.ContentPanel.Size = new System.Drawing.Size(766, 331);
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
            this.mainTransportSplitContainer.Size = new System.Drawing.Size(766, 331);
            this.mainTransportSplitContainer.SplitterDistance = 263;
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
            this.mainLeftAndRightSplitContainer.Size = new System.Drawing.Size(766, 263);
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
            this.previewBoardSplitContainer.Panel2.Controls.Add(this.tabControl1);
            this.previewBoardSplitContainer.Size = new System.Drawing.Size(556, 263);
            this.previewBoardSplitContainer.SplitterDistance = 129;
            this.previewBoardSplitContainer.TabIndex = 0;
            // 
            // previewPanel
            // 
            this.previewPanel.BackColor = System.Drawing.SystemColors.ControlText;
            this.previewPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.previewPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.previewPanel.Location = new System.Drawing.Point(0, 0);
            this.previewPanel.Name = "previewPanel";
            this.previewPanel.Size = new System.Drawing.Size(556, 129);
            this.previewPanel.TabIndex = 0;
            this.previewPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseMove);
            this.previewPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseDown);
            this.previewPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseUp);
            this.previewPanel.SizeChanged += new System.EventHandler(this.PreviewPanel_SizeChanged);
            // 
            // tabControl1
            // 
            this.tabControl1.Appearance = System.Windows.Forms.TabAppearance.Buttons;
            this.tabControl1.Controls.Add(this.stacksTab);
            this.tabControl1.Controls.Add(this.timelinesTab);
            this.tabControl1.Controls.Add(this.clipTab);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Margin = new System.Windows.Forms.Padding(0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(556, 130);
            this.tabControl1.TabIndex = 0;
            // 
            // stacksTab
            // 
            this.stacksTab.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.stacksTab.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.stacksTab.Controls.Add(this.operatorPageView1);
            this.stacksTab.Location = new System.Drawing.Point(4, 25);
            this.stacksTab.Margin = new System.Windows.Forms.Padding(0);
            this.stacksTab.Name = "stacksTab";
            this.stacksTab.Size = new System.Drawing.Size(548, 88);
            this.stacksTab.TabIndex = 2;
            this.stacksTab.Text = "Stacks";
            this.stacksTab.UseVisualStyleBackColor = true;
            // 
            // operatorPageView1
            // 
            this.operatorPageView1.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.operatorPageView1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.operatorPageView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.operatorPageView1.Location = new System.Drawing.Point(0, 0);
            this.operatorPageView1.Name = "operatorPageView1";
            this.operatorPageView1.Page = null;
            this.operatorPageView1.Size = new System.Drawing.Size(548, 88);
            this.operatorPageView1.TabIndex = 0;
            this.operatorPageView1.ViewedOperator = null;
            this.operatorPageView1.ViewedOperatorProperties = null;
            this.operatorPageView1.ViewedOperatorPropertiesChanged += new System.EventHandler(this.operatorPageView1_ViewedOperatorPropertiesChanged);
            this.operatorPageView1.ViewedOperatorChanged += new System.EventHandler(this.operatorPageView1_ViewedOperatorChanged);
            // 
            // timelinesTab
            // 
            this.timelinesTab.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.timelinesTab.Controls.Add(this.timelinesView1);
            this.timelinesTab.Location = new System.Drawing.Point(4, 25);
            this.timelinesTab.Name = "timelinesTab";
            this.timelinesTab.Size = new System.Drawing.Size(548, 101);
            this.timelinesTab.TabIndex = 1;
            this.timelinesTab.Text = "Timelines";
            this.timelinesTab.UseVisualStyleBackColor = true;
            // 
            // timelinesView1
            // 
            this.timelinesView1.BackColor = System.Drawing.SystemColors.Control;
            this.timelinesView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.timelinesView1.Location = new System.Drawing.Point(0, 0);
            this.timelinesView1.Name = "timelinesView1";
            this.timelinesView1.Size = new System.Drawing.Size(548, 101);
            this.timelinesView1.TabIndex = 0;
            this.timelinesView1.ViewedClip = null;
            this.timelinesView1.ViewedClipChanged += new System.EventHandler(this.timelinesView1_ViewedClipChanged);
            // 
            // clipTab
            // 
            this.clipTab.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.clipTab.Controls.Add(this.clipView1);
            this.clipTab.Location = new System.Drawing.Point(4, 25);
            this.clipTab.Name = "clipTab";
            this.clipTab.Size = new System.Drawing.Size(548, 101);
            this.clipTab.TabIndex = 3;
            this.clipTab.Text = "Clip";
            this.clipTab.UseVisualStyleBackColor = true;
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
            this.operatorPropertyGrid.Size = new System.Drawing.Size(206, 263);
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
            // clipView1
            // 
            this.clipView1.BackColor = System.Drawing.SystemColors.Control;
            this.clipView1.Clip = null;
            this.clipView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.clipView1.Location = new System.Drawing.Point(0, 0);
            this.clipView1.Name = "clipView1";
            this.clipView1.Size = new System.Drawing.Size(548, 101);
            this.clipView1.TabIndex = 0;
            // 
            // MainForm
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
            this.Name = "MainForm";
            this.Text = "db - Verkstan 1";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
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
            this.tabControl1.ResumeLayout(false);
            this.stacksTab.ResumeLayout(false);
            this.timelinesTab.ResumeLayout(false);
            this.clipTab.ResumeLayout(false);
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
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage timelinesTab;
        private System.Windows.Forms.TabPage stacksTab;
        private System.Windows.Forms.TabPage clipTab;
        private Transport transport1;
        private System.Windows.Forms.SplitContainer mainTransportSplitContainer;
        private System.Windows.Forms.Timer slowRenderTimer;
        private OperatorPageView operatorPageView1;
        private TimelinesView timelinesView1;
        private ClipView clipView1;
    }
}

