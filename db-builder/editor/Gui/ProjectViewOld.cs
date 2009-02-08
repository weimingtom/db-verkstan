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
        //private Verkstan.Window verkstanWindow;
        //private Operator viewedOperator;
        //private Project project;
        //private MouseButtons previewPanelLastMouseButtonDown;
        #endregion

        #region Constructor
        public ProjectView()
        {
            /*
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
             */
        }
        #endregion

        #region Public Methods
        public String SaveBackup()
        {
            /*
            String filename;

            if (project.Filename == null)
                filename = Environment.GetFolderPath(Environment.SpecialFolder.Personal) + "\\demo-backup";
            else
                filename = project.Filename + "-backup";

            filename += "-"+DateTime.Now.ToShortTimeString().Replace(":", "_")+"_"+DateTime.Now.ToShortDateString().Replace(":", "_");
            XmlDocument doc = new XmlDocument();
            doc.AppendChild(project.ToXmlElement(doc));
            doc.Save(filename);

            return filename;
             */
            return "";
        }
        #endregion
    }
}
