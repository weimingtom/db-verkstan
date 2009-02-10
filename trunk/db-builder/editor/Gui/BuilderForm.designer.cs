namespace VerkstanEditor
{
    partial class BuilderForm
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
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.previewPanel = new System.Windows.Forms.Panel();
            this.builderRenderTimer = new System.Windows.Forms.Timer(this.components);
            this.newProjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openProjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.exportAsHeaderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportAsFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveExportAsHeaderFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.saveProjectFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.openProjectFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.operatorPageView1 = new VerkstanEditor.Gui.OperatorPageView();
            this.operatorPropertyGrid1 = new VerkstanEditor.Gui.OperatorPropertyGrid();
            this.saveExportAsFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.menuStrip1.SuspendLayout();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.SuspendLayout();
            // 
            // statusStrip1
            // 
            this.statusStrip1.Location = new System.Drawing.Point(0, 251);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(680, 22);
            this.statusStrip1.TabIndex = 0;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.viewToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(680, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newProjectToolStripMenuItem,
            this.openProjectToolStripMenuItem,
            this.openFileToolStripMenuItem,
            this.toolStripSeparator1,
            this.saveToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.toolStripSeparator2,
            this.exportAsHeaderToolStripMenuItem,
            this.exportAsFileToolStripMenuItem,
            this.toolStripSeparator3,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(35, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // viewToolStripMenuItem
            // 
            this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
            this.viewToolStripMenuItem.Size = new System.Drawing.Size(41, 20);
            this.viewToolStripMenuItem.Text = "View";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(40, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // splitContainer1
            // 
            this.splitContainer1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 24);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.operatorPropertyGrid1);
            this.splitContainer1.Size = new System.Drawing.Size(680, 227);
            this.splitContainer1.SplitterDistance = 513;
            this.splitContainer1.TabIndex = 2;
            // 
            // splitContainer2
            // 
            this.splitContainer2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.BackColor = System.Drawing.SystemColors.ControlText;
            this.splitContainer2.Panel1.Controls.Add(this.previewPanel);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.operatorPageView1);
            this.splitContainer2.Size = new System.Drawing.Size(513, 227);
            this.splitContainer2.SplitterDistance = 82;
            this.splitContainer2.TabIndex = 0;
            // 
            // previewPanel
            // 
            this.previewPanel.BackColor = System.Drawing.Color.DarkCyan;
            this.previewPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.previewPanel.Location = new System.Drawing.Point(0, 0);
            this.previewPanel.Name = "previewPanel";
            this.previewPanel.Size = new System.Drawing.Size(511, 80);
            this.previewPanel.TabIndex = 0;
            this.previewPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseMove);
            this.previewPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseDown);
            this.previewPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseUp);
            this.previewPanel.SizeChanged += new System.EventHandler(this.previewPanel_SizeChanged);
            // 
            // builderRenderTimer
            // 
            this.builderRenderTimer.Enabled = true;
            this.builderRenderTimer.Interval = 10;
            this.builderRenderTimer.Tick += new System.EventHandler(this.builderRenderTimer_Tick);
            // 
            // newProjectToolStripMenuItem
            // 
            this.newProjectToolStripMenuItem.Name = "newProjectToolStripMenuItem";
            this.newProjectToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.newProjectToolStripMenuItem.Text = "New Project...";
            // 
            // openProjectToolStripMenuItem
            // 
            this.openProjectToolStripMenuItem.Name = "openProjectToolStripMenuItem";
            this.openProjectToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.openProjectToolStripMenuItem.Text = "Open Project...";
            this.openProjectToolStripMenuItem.Click += new System.EventHandler(this.openProjectToolStripMenuItem_Click);
            // 
            // openFileToolStripMenuItem
            // 
            this.openFileToolStripMenuItem.Name = "openFileToolStripMenuItem";
            this.openFileToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.openFileToolStripMenuItem.Text = "Open File...";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(168, 6);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.saveToolStripMenuItem.Text = "Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.saveAsToolStripMenuItem.Text = "Save As...";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(168, 6);
            // 
            // exportAsHeaderToolStripMenuItem
            // 
            this.exportAsHeaderToolStripMenuItem.Name = "exportAsHeaderToolStripMenuItem";
            this.exportAsHeaderToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.exportAsHeaderToolStripMenuItem.Text = "Export As Header...";
            this.exportAsHeaderToolStripMenuItem.Click += new System.EventHandler(this.exportAsHeaderToolStripMenuItem_Click);
            // 
            // exportAsFileToolStripMenuItem
            // 
            this.exportAsFileToolStripMenuItem.Name = "exportAsFileToolStripMenuItem";
            this.exportAsFileToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.exportAsFileToolStripMenuItem.Text = "Export As File...";
            this.exportAsFileToolStripMenuItem.Click += new System.EventHandler(this.exportAsFileToolStripMenuItem_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(168, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            // 
            // saveExportAsHeaderFileDialog1
            // 
            this.saveExportAsHeaderFileDialog1.Filter = "C++ header files|*.hpp|All files|*.*";
            this.saveExportAsHeaderFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.saveExportAsHeaderFileDialog1_FileOk);
            // 
            // saveProjectFileDialog1
            // 
            this.saveProjectFileDialog1.Filter = "db Builder files |*.dbb|All files|*.*";
            this.saveProjectFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.saveProjectFileDialog1_FileOk);
            // 
            // openProjectFileDialog1
            // 
            this.openProjectFileDialog1.FileName = "openFileDialog1";
            this.openProjectFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openProjectFileDialog1_FileOk);
            // 
            // operatorPageView1
            // 
            this.operatorPageView1.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.operatorPageView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.operatorPageView1.Location = new System.Drawing.Point(0, 0);
            this.operatorPageView1.Name = "operatorPageView1";
            this.operatorPageView1.Page = null;
            this.operatorPageView1.Size = new System.Drawing.Size(511, 139);
            this.operatorPageView1.TabIndex = 0;
            this.operatorPageView1.ViewedOperator = null;
            this.operatorPageView1.ViewedOperatorProperties = null;
            this.operatorPageView1.ViewedOperatorPropertiesChanged += new System.EventHandler(this.operatorPageView1_ViewedOperatorPropertiesChanged);
            this.operatorPageView1.ViewedOperatorChanged += new System.EventHandler(this.operatorPageView1_ViewedOperatorChanged);
            // 
            // operatorPropertyGrid1
            // 
            this.operatorPropertyGrid1.AutoScroll = true;
            this.operatorPropertyGrid1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.operatorPropertyGrid1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.operatorPropertyGrid1.Location = new System.Drawing.Point(0, 0);
            this.operatorPropertyGrid1.Name = "operatorPropertyGrid1";
            this.operatorPropertyGrid1.Operator = null;
            this.operatorPropertyGrid1.Size = new System.Drawing.Size(161, 225);
            this.operatorPropertyGrid1.TabIndex = 0;
            // 
            // saveExportAsFileDialog1
            // 
            this.saveExportAsFileDialog1.Filter = "Data files|*.dat|All files|*.*";
            this.saveExportAsFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.saveExportAsFileDialog1_FileOk);
            // 
            // BuilderForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(680, 273);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "BuilderForm";
            this.Text = " Darkbits® Verkstan™ Enterprise Graphical Demonstration Solutions Productivity Su" +
                "ite™  - Builder";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            this.splitContainer2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem viewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private VerkstanEditor.Gui.OperatorPageView operatorPageView1;
        private VerkstanEditor.Gui.OperatorPropertyGrid operatorPropertyGrid1;
        private System.Windows.Forms.Timer builderRenderTimer;
        private System.Windows.Forms.Panel previewPanel;
        private System.Windows.Forms.ToolStripMenuItem newProjectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openProjectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem exportAsHeaderToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exportAsFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.SaveFileDialog saveExportAsHeaderFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveProjectFileDialog1;
        private System.Windows.Forms.OpenFileDialog openProjectFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveExportAsFileDialog1;
    }
}

