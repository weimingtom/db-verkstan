using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace db_director
{
    public partial class Form1 : Form
    {
        IDemo demo = null;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            if (new Random().Next(100) == 1)
            {
                MessageBox.Show("[E5521:W32SERVUNDEF]Unable to locate lnotes43.dll\n\nYou may experience problems with Lotus Notes integration\n\nPlease contact your system adminstrator to resolve the problem", "Error 5521", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Error);
            }
        }

        private void openDemoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult r = openDemoDialog.ShowDialog();
            if (r == DialogResult.OK)
            {
                demo = Plugin.GetPlugin<IDemo>(openDemoDialog.FileName);

                if (demo == null)
                {
                    MessageBox.Show("Could not find an IDemo in that assembly. :(", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                demo.Init(demoSplit.Panel1.Handle);
                ProgressWindow progressWindow = new ProgressWindow("Loading demo");
                progressWindow.Show(this);
                demo.Load(progressWindow);
                progressWindow.Hide();
            }
        }
    }
}
