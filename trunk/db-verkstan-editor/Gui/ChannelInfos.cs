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
    public partial class ChannelInfos : UserControl
    {
        public ChannelInfos()
        {
            InitializeComponent();
            AddChannelInfo();
            AddChannelInfo();
            AddChannelInfo();
            AddChannelInfo();
            AddChannelInfo();
            AddChannelInfo();
            AddChannelInfo();
            AddChannelInfo();
            AddChannelInfo();
            AddChannelInfo();
            AddChannelInfo();
            AddChannelInfo();
            LayoutChannelInfos();
        }

        private void UpdateSize()
        {
            int height = 0;
            foreach (Control control in Controls)
            {
                height += control.Size.Height + control.Padding.Top + control.Padding.Bottom + 1;
            }

            Size = new Size(Size.Width, height);
        }

        private void ChannelInfos_Load(object sender, EventArgs e)
        {
            UpdateSize();
        }

        private void AddChannelInfo()
        {
            ChannelInfo ci = new ChannelInfo();
            ci.Size = new Size(Size.Width, 30);
            ci.Margin = new Padding(0, 1, 0, 1);
            this.Controls.Add(ci);
        }

        private void LayoutChannelInfos()
        {
            int y = 1;
            foreach (Control control in Controls)
            {
                y += control.Padding.Top;
                control.Location = new Point(0, y);
                y += control.Padding.Bottom + control.Size.Height + 1;
            }
        }
    }
}
