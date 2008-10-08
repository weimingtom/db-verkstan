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
            this.previewComposeSplitContainer.Panel1.SuspendLayout();
            this.previewComposeSplitContainer.Panel2.SuspendLayout();
            this.previewComposeSplitContainer.SuspendLayout();
            this.composeTransportSplitContainer.Panel1.SuspendLayout();
            this.composeTransportSplitContainer.Panel2.SuspendLayout();
            this.composeTransportSplitContainer.SuspendLayout();
            this.operatorPanel.SuspendLayout();
            this.operatorsPropertiesSplitContainer.SuspendLayout();
            this.transportPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // previewComposeSplitContainer
            // 
            this.previewComposeSplitContainer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
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
            this.previewComposeSplitContainer.Size = new System.Drawing.Size(643, 279);
            this.previewComposeSplitContainer.SplitterDistance = 98;
            this.previewComposeSplitContainer.TabIndex = 0;
            // 
            // previewPanel
            // 
            this.previewPanel.BackColor = System.Drawing.SystemColors.ControlText;
            this.previewPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.previewPanel.Location = new System.Drawing.Point(0, 0);
            this.previewPanel.Name = "previewPanel";
            this.previewPanel.Size = new System.Drawing.Size(641, 96);
            this.previewPanel.TabIndex = 0;
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
            this.composeTransportSplitContainer.Size = new System.Drawing.Size(641, 175);
            this.composeTransportSplitContainer.SplitterDistance = 117;
            this.composeTransportSplitContainer.TabIndex = 0;
            // 
            // operatorPanel
            // 
            this.operatorPanel.Controls.Add(this.operatorsPropertiesSplitContainer);
            this.operatorPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.operatorPanel.Location = new System.Drawing.Point(0, 0);
            this.operatorPanel.Name = "operatorPanel";
            this.operatorPanel.Size = new System.Drawing.Size(641, 117);
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
            this.operatorsPropertiesSplitContainer.Size = new System.Drawing.Size(641, 117);
            this.operatorsPropertiesSplitContainer.SplitterDistance = 473;
            this.operatorsPropertiesSplitContainer.TabIndex = 0;
            // 
            // transportPanel
            // 
            this.transportPanel.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.transportPanel.Controls.Add(this.transportTimeLabel);
            this.transportPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.transportPanel.Location = new System.Drawing.Point(0, 0);
            this.transportPanel.Name = "transportPanel";
            this.transportPanel.Size = new System.Drawing.Size(641, 54);
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
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(643, 279);
            this.Controls.Add(this.previewComposeSplitContainer);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
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
            this.ResumeLayout(false);

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
    }
}

