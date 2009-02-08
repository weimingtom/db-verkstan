using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using VerkstanEditor.Logic;

namespace VerkstanEditor
{
    public partial class BuilderForm : Form
    {
        #region Private Variables
        private Project project;
        private Page page;
        private Verkstan.Window builderWindow;
        private MouseButtons previewPanelLastMouseButtonDown;
        #endregion

        #region Constructors
        public BuilderForm()
        {
            InitializeComponent();

            builderWindow = new Verkstan.Window();
            builderWindow.ClearColor = Color.DarkCyan.ToArgb();
            unsafe
            {
                builderWindow.Boot(previewPanel.Handle.ToPointer());
            }

            project = new Project();
            page = new Page();
            project.OperatorPages.Add(page);
            operatorPageView1.Page = page;
        }
        #endregion

        #region Event Handlers
        private void builderRenderTimer_Tick(object sender, EventArgs e)
        {
            builderWindow.Render();
        }
        private void previewPanel_SizeChanged(object sender, EventArgs e)
        {
            if (builderWindow != null)
                 builderWindow.Resize();
        }
        private void operatorPageView1_ViewedOperatorChanged(object sender, EventArgs e)
        {
            if (operatorPageView1.ViewedOperator != null)
                builderWindow.ViewedOperator = operatorPageView1.ViewedOperator.BindedOperator;
            else
                builderWindow.ViewedOperator = null;
        }
        private void operatorPageView1_ViewedOperatorPropertiesChanged(object sender, EventArgs e)
        {
            operatorPropertyGrid1.Operator = operatorPageView1.ViewedOperatorProperties;
        }
        private void previewPanel_MouseDown(object sender, MouseEventArgs e)
        {
            previewPanelLastMouseButtonDown = e.Button;

            int button = 0;

            if (e.Button == MouseButtons.Left)
                button = 1;
            else if (e.Button == MouseButtons.Middle)
                button = 2;
            else if (e.Button == MouseButtons.Right)
                button = 3;

            builderWindow.MouseDown(button, e.X, e.Y);
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

            builderWindow.MouseUp(button, e.X, e.Y);
        }
        private void previewPanel_MouseMove(object sender, MouseEventArgs e)
        {
            builderWindow.MouseMove(e.X, e.Y);
        }
        #endregion
    }
}
