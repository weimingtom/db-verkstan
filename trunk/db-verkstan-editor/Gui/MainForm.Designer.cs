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
            this.mainTransportSplitContainer = new System.Windows.Forms.SplitContainer();
            this.mainLeftAndRightSplitContainer = new System.Windows.Forms.SplitContainer();
            this.propertiesChannelSplitContainer = new System.Windows.Forms.SplitContainer();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.previewBoardSplitContainer = new System.Windows.Forms.SplitContainer();
            this.previewPanel = new System.Windows.Forms.Panel();
            this.boardTabControl = new System.Windows.Forms.TabControl();
            this.timelineTab = new System.Windows.Forms.TabPage();
            this.scenesTab = new System.Windows.Forms.TabPage();
            this.operatorsTab = new System.Windows.Forms.TabPage();
            this.operatorPagePanel = new System.Windows.Forms.Panel();
            this.operatorPage1 = new VerkstanEditor.Gui.OperatorPage();
            this.operatorPropertyGrid = new VerkstanEditor.Gui.OperatorPropertyGrid();
            this.transportPanel.SuspendLayout();
            this.mainMenu.SuspendLayout();
            this.toolStripContainer1.ContentPanel.SuspendLayout();
            this.toolStripContainer1.SuspendLayout();
            this.mainTransportSplitContainer.Panel1.SuspendLayout();
            this.mainTransportSplitContainer.Panel2.SuspendLayout();
            this.mainTransportSplitContainer.SuspendLayout();
            this.mainLeftAndRightSplitContainer.Panel1.SuspendLayout();
            this.mainLeftAndRightSplitContainer.Panel2.SuspendLayout();
            this.mainLeftAndRightSplitContainer.SuspendLayout();
            this.propertiesChannelSplitContainer.Panel1.SuspendLayout();
            this.propertiesChannelSplitContainer.SuspendLayout();
            this.previewBoardSplitContainer.Panel1.SuspendLayout();
            this.previewBoardSplitContainer.Panel2.SuspendLayout();
            this.previewBoardSplitContainer.SuspendLayout();
            this.boardTabControl.SuspendLayout();
            this.operatorsTab.SuspendLayout();
            this.operatorPagePanel.SuspendLayout();
            this.SuspendLayout();
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
            this.toolStripContainer1.ContentPanel.Controls.Add(this.mainTransportSplitContainer);
            this.toolStripContainer1.ContentPanel.Size = new System.Drawing.Size(643, 208);
            this.toolStripContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.toolStripContainer1.Location = new System.Drawing.Point(0, 24);
            this.toolStripContainer1.Name = "toolStripContainer1";
            this.toolStripContainer1.Size = new System.Drawing.Size(643, 233);
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
            this.mainTransportSplitContainer.Panel2.Controls.Add(this.transportPanel);
            this.mainTransportSplitContainer.Size = new System.Drawing.Size(643, 208);
            this.mainTransportSplitContainer.SplitterDistance = 146;
            this.mainTransportSplitContainer.TabIndex = 3;
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
            this.mainLeftAndRightSplitContainer.Panel2.Controls.Add(this.propertiesChannelSplitContainer);
            this.mainLeftAndRightSplitContainer.Size = new System.Drawing.Size(643, 146);
            this.mainLeftAndRightSplitContainer.SplitterDistance = 467;
            this.mainLeftAndRightSplitContainer.TabIndex = 0;
            // 
            // propertiesChannelSplitContainer
            // 
            this.propertiesChannelSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.propertiesChannelSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.propertiesChannelSplitContainer.Name = "propertiesChannelSplitContainer";
            this.propertiesChannelSplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // propertiesChannelSplitContainer.Panel1
            // 
            this.propertiesChannelSplitContainer.Panel1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.propertiesChannelSplitContainer.Panel1.Controls.Add(this.operatorPropertyGrid);
            // 
            // propertiesChannelSplitContainer.Panel2
            // 
            this.propertiesChannelSplitContainer.Panel2.BackColor = System.Drawing.SystemColors.ControlDark;
            this.propertiesChannelSplitContainer.Size = new System.Drawing.Size(172, 146);
            this.propertiesChannelSplitContainer.SplitterDistance = 73;
            this.propertiesChannelSplitContainer.TabIndex = 0;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Location = new System.Drawing.Point(0, 257);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(643, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // previewBoardSplitContainer
            // 
            this.previewBoardSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.previewBoardSplitContainer.Location = new System.Drawing.Point(0, 0);
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
            this.previewBoardSplitContainer.Size = new System.Drawing.Size(467, 146);
            this.previewBoardSplitContainer.SplitterDistance = 73;
            this.previewBoardSplitContainer.TabIndex = 0;
            // 
            // previewPanel
            // 
            this.previewPanel.BackColor = System.Drawing.SystemColors.ControlText;
            this.previewPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.previewPanel.Location = new System.Drawing.Point(0, 0);
            this.previewPanel.Name = "previewPanel";
            this.previewPanel.Size = new System.Drawing.Size(467, 73);
            this.previewPanel.TabIndex = 0;
            this.previewPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseMove);
            this.previewPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseDown);
            this.previewPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseUp);
            this.previewPanel.SizeChanged += new System.EventHandler(this.PreviewPanel_SizeChanged);
            // 
            // boardTabControl
            // 
            this.boardTabControl.Appearance = System.Windows.Forms.TabAppearance.Buttons;
            this.boardTabControl.Controls.Add(this.timelineTab);
            this.boardTabControl.Controls.Add(this.scenesTab);
            this.boardTabControl.Controls.Add(this.operatorsTab);
            this.boardTabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.boardTabControl.Location = new System.Drawing.Point(0, 0);
            this.boardTabControl.Name = "boardTabControl";
            this.boardTabControl.SelectedIndex = 0;
            this.boardTabControl.Size = new System.Drawing.Size(467, 69);
            this.boardTabControl.TabIndex = 0;
            // 
            // timelineTab
            // 
            this.timelineTab.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.timelineTab.Location = new System.Drawing.Point(4, 25);
            this.timelineTab.Name = "timelineTab";
            this.timelineTab.Padding = new System.Windows.Forms.Padding(3);
            this.timelineTab.Size = new System.Drawing.Size(459, 40);
            this.timelineTab.TabIndex = 0;
            this.timelineTab.Text = "Timeline";
            // 
            // scenesTab
            // 
            this.scenesTab.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.scenesTab.Location = new System.Drawing.Point(4, 25);
            this.scenesTab.Name = "scenesTab";
            this.scenesTab.Padding = new System.Windows.Forms.Padding(3);
            this.scenesTab.Size = new System.Drawing.Size(459, 40);
            this.scenesTab.TabIndex = 1;
            this.scenesTab.Text = "Scenes";
            // 
            // operatorsTab
            // 
            this.operatorsTab.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.operatorsTab.Controls.Add(this.operatorPagePanel);
            this.operatorsTab.Location = new System.Drawing.Point(4, 25);
            this.operatorsTab.Name = "operatorsTab";
            this.operatorsTab.Size = new System.Drawing.Size(459, 40);
            this.operatorsTab.TabIndex = 2;
            this.operatorsTab.Text = "Operators";
            // 
            // operatorPagePanel
            // 
            this.operatorPagePanel.AutoScroll = true;
            this.operatorPagePanel.Controls.Add(this.operatorPage1);
            this.operatorPagePanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.operatorPagePanel.Location = new System.Drawing.Point(0, 0);
            this.operatorPagePanel.Name = "operatorPagePanel";
            this.operatorPagePanel.Size = new System.Drawing.Size(459, 40);
            this.operatorPagePanel.TabIndex = 1;
            // 
            // operatorPage1
            // 
            this.operatorPage1.Location = new System.Drawing.Point(0, 0);
            this.operatorPage1.Name = "operatorPage1";
            this.operatorPage1.Size = new System.Drawing.Size(459, 40);
            this.operatorPage1.TabIndex = 0;
            // 
            // operatorPropertyGrid
            // 
            this.operatorPropertyGrid.AutoScroll = true;
            this.operatorPropertyGrid.Dock = System.Windows.Forms.DockStyle.Fill;
            this.operatorPropertyGrid.Location = new System.Drawing.Point(0, 0);
            this.operatorPropertyGrid.Name = "operatorPropertyGrid";
            this.operatorPropertyGrid.Operator = null;
            this.operatorPropertyGrid.Size = new System.Drawing.Size(172, 73);
            this.operatorPropertyGrid.TabIndex = 0;
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
            this.mainTransportSplitContainer.Panel1.ResumeLayout(false);
            this.mainTransportSplitContainer.Panel2.ResumeLayout(false);
            this.mainTransportSplitContainer.ResumeLayout(false);
            this.mainLeftAndRightSplitContainer.Panel1.ResumeLayout(false);
            this.mainLeftAndRightSplitContainer.Panel2.ResumeLayout(false);
            this.mainLeftAndRightSplitContainer.ResumeLayout(false);
            this.propertiesChannelSplitContainer.Panel1.ResumeLayout(false);
            this.propertiesChannelSplitContainer.ResumeLayout(false);
            this.previewBoardSplitContainer.Panel1.ResumeLayout(false);
            this.previewBoardSplitContainer.Panel2.ResumeLayout(false);
            this.previewBoardSplitContainer.ResumeLayout(false);
            this.boardTabControl.ResumeLayout(false);
            this.operatorsTab.ResumeLayout(false);
            this.operatorPagePanel.ResumeLayout(false);
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
        private System.Windows.Forms.SplitContainer mainTransportSplitContainer;
        private System.Windows.Forms.SplitContainer mainLeftAndRightSplitContainer;
        private System.Windows.Forms.SplitContainer previewBoardSplitContainer;
        private System.Windows.Forms.SplitContainer propertiesChannelSplitContainer;
        private VerkstanEditor.Gui.OperatorPropertyGrid operatorPropertyGrid;
        private System.Windows.Forms.TabControl boardTabControl;
        private System.Windows.Forms.TabPage timelineTab;
        private System.Windows.Forms.TabPage scenesTab;
        private System.Windows.Forms.TabPage operatorsTab;
        private System.Windows.Forms.Panel operatorPagePanel;
        private OperatorPage operatorPage1;
    }
}

