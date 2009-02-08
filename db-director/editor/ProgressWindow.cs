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
    public partial class ProgressWindow : Form, IProgressCallback
    {
        public ProgressWindow(string title)
        {
            InitializeComponent();
            Text = title;
        }

        private void ProgressWindow_Load(object sender, EventArgs e)
        {

        }

        public void ProgressUpdated(float progress)
        {
            progressBar1.Value = (int)(progress * progressBar1.Maximum + 0.5f);
        }
    }
}
