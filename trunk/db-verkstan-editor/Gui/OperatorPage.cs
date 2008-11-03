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
    public partial class OperatorPage : UserControl
    {
        public OperatorPage()
        {
            InitializeComponent();
            operatorPagePanel1.MouseWheel += new MouseEventHandler(operatorPagePanel1_MouseWheel);
        }

        private void operatorPagePanel1_Resize(object sender, EventArgs e)
        {
            UpdateScrollBars();
        }

        private void OperatorPage_Resize(object sender, EventArgs e)
        {
            if (operatorPagePanel1.Width < (Width - vScrollBar1.Width - 1))
                operatorPagePanel1.Width = (Width - vScrollBar1.Width - 1);
            if (operatorPagePanel1.Height < (Height - hScrollBar1.Height - 1))
                operatorPagePanel1.Height = (Height - hScrollBar1.Height - 1);

            UpdateScrollBars();
        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            operatorPagePanel1.Left = -e.NewValue; 
        }

        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            operatorPagePanel1.Top = -e.NewValue;
        }

        private void hScrollBar1_Layout(object sender, LayoutEventArgs e)
        {
            hScrollBar1.Width = Width - vScrollBar1.Width - 1;
        }

        private void vScrollBar1_Layout(object sender, LayoutEventArgs e)
        {
            vScrollBar1.Height = Height - hScrollBar1.Height - 1;
        }

        private void UpdateScrollBars()
        {
            hScrollBar1.Enabled = operatorPagePanel1.Width > (Width - vScrollBar1.Width - 1);
            vScrollBar1.Enabled = operatorPagePanel1.Height > (Height - hScrollBar1.Height - 1);

            hScrollBar1.Minimum = 0;
            hScrollBar1.Maximum = operatorPagePanel1.Width;
            hScrollBar1.LargeChange = Width - vScrollBar1.Width;
            hScrollBar1.SmallChange = 10;  
            vScrollBar1.Minimum = 0;
            vScrollBar1.Maximum = operatorPagePanel1.Height;
            vScrollBar1.LargeChange = Height - hScrollBar1.Height;
            vScrollBar1.SmallChange = 10;

            if (!hScrollBar1.Enabled)
                operatorPagePanel1.Left = 0;

            if (!vScrollBar1.Enabled)
                operatorPagePanel1.Top = 0;
        }

        private void operatorPagePanel1_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
            {
                if (vScrollBar1.Value - vScrollBar1.SmallChange > vScrollBar1.Minimum)
                    vScrollBar1.Value -= vScrollBar1.SmallChange;
                else
                    vScrollBar1.Value = vScrollBar1.Minimum;
            }
            else
            {
                if (vScrollBar1.Value + vScrollBar1.SmallChange < (vScrollBar1.Maximum - vScrollBar1.LargeChange + 1))
                    vScrollBar1.Value += vScrollBar1.SmallChange;
                else
                    vScrollBar1.Value = vScrollBar1.Maximum - vScrollBar1.LargeChange + 1;
            }

            operatorPagePanel1.Top = -vScrollBar1.Value;
        }
    }
}
