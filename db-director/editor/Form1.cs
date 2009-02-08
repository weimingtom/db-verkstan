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
    }
}
