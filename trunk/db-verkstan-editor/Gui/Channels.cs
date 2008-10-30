using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Design;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class Channels : UserControl
    {
        private int numberOfChannels = 12;
        private int beats = 4;
        public int Beats
        {
            set
            {
                beats = value;
                UpdateSize();
            }
            get
            {
                return beats;
            }
        }

        [Browsable(true)]
        [Description("The width of a beat in pixels.")]
        [Editor(typeof(int), typeof(UITypeEditor))]
        [DefaultValue(16)]
        private int beatWidth;
        public int BeatWidth
        {
            set
            {
                beatWidth = value;
                Refresh();
            }
            get
            {
                return beatWidth;
            }

        }

        [Browsable(true)]
        [Description("The height of a channel.")]
        [Editor(typeof(int), typeof(UITypeEditor))]
        [DefaultValue(30)]
        private int channelHeight;
        public int ChannelHeight
        {
            set
            {
                channelHeight = value;
                Refresh();
            }
            get
            {
                return channelHeight;
            }

        }

        private int playerPosition = 0;
        public int PlayerPosition
        {
            set
            {
                playerPosition = value;
                Refresh();
            }
            get
            {
                return playerPosition;
            }
        }


        public Channels()
        {
            InitializeComponent();
            DoubleBuffered = true;
        }

        private void UpdateSize()
        {
          
            int width = beatWidth * beats;
            int height = numberOfChannels * (channelHeight + 1) - 1;
                     
            Size = new Size(width, height);

            foreach (Control control in Controls)
                control.Size = new Size(width, control.Size.Height);

            if (Parent == null)
                return;

            if (Parent.ClientRectangle.Height > height)
                Size = new Size(width, Parent.ClientRectangle.Height);
        }

        private void Channels_Load(object sender, EventArgs e)
        {
            UpdateSize();
        }

        private void Channels_ParentChanged(object sender, EventArgs e)
        {
            UpdateSize();
            Parent.Resize += new System.EventHandler(this.Channels_ParentResized);
        }

        private void Channels_ParentResized(object sender, EventArgs e)
        {
            UpdateSize();
        }

        private void Channels_Paint(object sender, PaintEventArgs e)
        {
            for (int i = 0; i < numberOfChannels; i++)
                PaintChannel(e, i * (channelHeight + 1));

            Pen p = new Pen(Color.FromArgb(255, 0, 0), 1);
            int playerPositionInPixels = (int)(BeatWidth * (PlayerPosition / (float)Verkstan.Timer.GetTicksPerBeat()));
            e.Graphics.DrawLine(p, new Point(playerPositionInPixels, 0), new Point(playerPositionInPixels, Size.Height));
            p.Dispose();
        }

        private void PaintChannel(PaintEventArgs e, int y)
        {
            Pen p1 = new Pen(Color.FromArgb(80, 80, 80), 1);
            Pen p2 = new Pen(Color.FromArgb(30, 30, 30), 1);

            for (int i = 0; i < Beats; i++)
            {
                if (i % 2 == 0)
                    e.Graphics.DrawLine(p1, new Point(i * BeatWidth, y), new Point(i * BeatWidth, y + channelHeight));
                else
                    e.Graphics.DrawLine(p2, new Point(i * BeatWidth, y), new Point(i * BeatWidth, y + channelHeight));
            }

            e.Graphics.DrawLine(p1, new Point(0, y), new Point(Size.Width, y));
        }
    }
}
