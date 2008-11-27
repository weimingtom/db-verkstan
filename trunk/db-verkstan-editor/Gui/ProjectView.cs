using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using VerkstanEditor.Logic;

namespace VerkstanEditor.Gui
{
    public partial class ProjectView : Form
    {
        #region Private Variables
        private Verkstan.Window verkstanWindow;
        private Operator viewedOperator;
        private Project project;
        #endregion

        #region Constructor
        public ProjectView()
        {
            InitializeComponent();
            verkstanWindow = new Verkstan.Window();
            verkstanWindow.ClearColor = Color.DarkCyan.ToArgb();
            unsafe
            {
                verkstanWindow.Boot(previewPanel.Handle.ToPointer());
            }

            fastRenderTimer.Enabled = true;
            slowRenderTimer.Enabled = true;

            project = new Project();
            Page page = new Page();
            project.OperatorPages.Add(page);
            operatorPageView1.Page = page;
        }
        #endregion

        #region Event Handlers
        private void FastRenderTimer_Tick(object sender, EventArgs e)
        {
            if (viewedOperator != null && viewedOperator.IsProcessable)
                verkstanWindow.ViewedOperator = viewedOperator.BindedCoreOperator;

            if (viewedOperator == null || !viewedOperator.IsProcessable)
                verkstanWindow.ViewedOperator = null;

            verkstanWindow.Render(Metronome.Tick);
            Metronome.OnBeatChangedFastUpdate(Metronome.Tick);
        }
        private void PreviewPanel_SizeChanged(object sender, EventArgs e)
        {
            if (verkstanWindow != null)
                verkstanWindow.Resize();
        }
        private void Operators_ViewedOperatorPropertiesChanged(Operator op)
        {
            operatorPropertyGrid.Operator = op;
        }
        private void Operators_ViewedOperatorChanged(Operator op)
        {
            /*
            if (op == null)
                verkstanWindow.ViewedOperator = null;
            else
                verkstanWindow.ViewedOperator = op.Binding;*/
        }
        private void previewPanel_MouseDown(object sender, MouseEventArgs e)
        {
            int button = 0;

            if (e.Button == MouseButtons.Left)
                button = 1;
            else if (e.Button == MouseButtons.Middle)
                button = 2;
            else if (e.Button == MouseButtons.Right)
                button = 3;

            verkstanWindow.MouseDown(button, e.X, e.Y);
        }
        private void previewPanel_MouseUp(object sender, MouseEventArgs e)
        {
            int button = 0;

            if (e.Button == MouseButtons.Left)
                button = 1;
            else if (e.Button == MouseButtons.Middle)
                button = 2;
            else if (e.Button == MouseButtons.Right)
                button = 3;

            verkstanWindow.MouseUp(button, e.X, e.Y);
        }
        private void previewPanel_MouseMove(object sender, MouseEventArgs e)
        {
            verkstanWindow.MouseMove(e.X, e.Y);
        }
        private void slowRenderTimer_Tick(object sender, EventArgs e)
        {
            Metronome.OnBeatChangedSlowUpdate(Metronome.Tick);
        }
        private void operatorPageView1_ViewedOperatorChanged(object sender, EventArgs e)
        {
            viewedOperator = operatorPageView1.ViewedOperator;
        }
        private void operatorPageView1_ViewedOperatorPropertiesChanged(object sender, EventArgs e)
        {
            operatorPropertyGrid.Operator = operatorPageView1.ViewedOperatorProperties;
        }
        private void timelinesView1_ViewedClipChanged(object sender, EventArgs e)
        {
            if (timelinesView1.ViewedClip != null)
            {
                clipView1.Clip = timelinesView1.ViewedClip;
                tabControl1.SelectedTab = clipTab;
            }
        }
        private void openMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }
        private void saveMenuItem_Click(object sender, EventArgs e)
        {
            if (project.Filename == null)
                return;

            XmlDocument doc = new XmlDocument();
            doc.AppendChild(project.ToXmlElement(doc));
            doc.Save(project.Filename);
        }
        private void saveAsMenuItem_Click(object sender, EventArgs e)
        {
            if (project.Filename != null)
                saveFileDialog1.FileName = project.Filename;
            else
                saveFileDialog1.FileName = "demo.dbv";
            saveFileDialog1.ShowDialog();
        }
        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            project.Filename = saveFileDialog1.FileName;
            XmlDocument doc = new XmlDocument();
            doc.AppendChild(project.ToXmlElement(doc));
            doc.Save(project.Filename);
        }
        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            String filename = openFileDialog1.FileName;
            XmlDocument doc = new XmlDocument();
            doc.Load(filename);
            XmlElement rootElement = doc.DocumentElement;
            project = new Project();
            project.FromXmlElement(rootElement);
            operatorPageView1.Page = project.OperatorPages.First();
        }
        #endregion
    }
}
