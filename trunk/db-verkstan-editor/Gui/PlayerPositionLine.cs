using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace VerkstanEditor.Gui
{
    public partial class PlayerPositionLine : UserControl
    {
        public int Beats;

        public PlayerPositionLine()
        {
            InitializeComponent();
            Beats = 40;
        }

        private void PlayerPositionLine_Paint(object sender, PaintEventArgs e)
        {
            Brush b = new SolidBrush(ForeColor);
            Pen p = new Pen(Color.FromArgb(100, 100, 100), 1);
            for (int i = 0; i < Beats; i++)
            {
                if (i % 2 == 0)
                {
                    e.Graphics.DrawLine(p, new Point(i * 17, 0), new Point(i * 17, 24));
                    e.Graphics.DrawString("" + (i + 1), Font, b, new Point(i * 17 + 1, 0));
                }
                else
                    e.Graphics.DrawLine(p, new Point(i * 17, 20), new Point(i * 17, 24));
            }
            p.Dispose();
            b.Dispose();
        }
    }
}
