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
    public partial class TimelineChannelInfos : UserControl
    {
        private int channelHeight = 31;
        public int ChannelHeight
        {
            set
            {
                channelHeight = value;
            }
            get
            {
                return channelHeight;
            }
        }
        private int selectedChannel;
        public int SelectedChannel
        {
            set
            {
                selectedChannel = value;
            }
            get
            {
                return selectedChannel;
            }
        }

        private Verkstan.SceneOperator scene;
        public Verkstan.SceneOperator Scene
        {
            get
            {
                return scene;
            }
            set
            {
                scene = value;
            }
        }

        public TimelineChannelInfos()
        {
            InitializeComponent();
        }

        private void UpdateSize()
        {
            int height = 0;
            foreach (Control control in Controls)
            {
                height += control.Size.Height + control.Padding.Bottom + 1;
            }

            Height = height;

            if (Parent == null)
                return;
            
            Width = Parent.Width;
        }

        private void ChannelInfos_Load(object sender, EventArgs e)
        {
            UpdateSize();
        }

        private void AddChannelInfo()
        {
            ChannelInfo ci = new ChannelInfo();
            ci.Height = channelHeight;
            ci.Margin = new Padding(0, 0, 0, 1);
            this.Controls.Add(ci);
        }

        private void LayoutChannelInfos()
        {
            int y = 0;
            foreach (Control control in Controls)
            {
                control.Location = new Point(0, y);
                control.Width = Width;
                y += control.Padding.Bottom + control.Size.Height + 1;
            }
        }

        private void TimelineChannelInfos_Layout(object sender, LayoutEventArgs e)
        {
            LayoutChannelInfos();
        }
    }
}
