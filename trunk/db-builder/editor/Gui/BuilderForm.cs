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

        private void builderRenderTimer_Tick(object sender, EventArgs e)
        {
            builderWindow.Render();
        }
        private void previewPanel_SizeChanged(object sender, EventArgs e)
        {
           // if (builderWindow != null)
           //     builderWindow.Resize();
        }
        private void operatorPageView1_ViewedOperatorChanged(object sender, EventArgs e)
        {
            builderWindow.ViewedOperator = operatorPageView1.ViewedOperator.BindedOperator;
        }
    }
}
