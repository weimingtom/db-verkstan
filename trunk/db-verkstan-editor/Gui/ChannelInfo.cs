using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class ChannelInfo : UserControl
    {
        public bool Folded = false;

        public ChannelInfo()
        {
            InitializeComponent();
        }

        private void ChannelInfo_Paint(object sender, PaintEventArgs e)
        {
            Pen p = new Pen(Color.FromArgb(0, 0, 0), 1);
            e.Graphics.DrawLine(p, new Point(0, 0), new Point(Size.Width, 0));
            e.Graphics.DrawLine(p, new Point(0, Size.Height - 1), new Point(Size.Width, Size.Height - 1));
            p.Dispose();
        }

        private void label2_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
                Folded = !Folded;
        }
    }
}
