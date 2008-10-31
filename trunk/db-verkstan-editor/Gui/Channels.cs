using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Design;
using VerkstanEditor.Logic;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class Channels : UserControl
    {
        private int beat;
        private int numberOfChannels = 12;
      
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

        public Channels()
        {
            InitializeComponent();
            DoubleBuffered = true;
            Metronome.BeatChangedSlowUpdate += new Metronome.BeatChangedHandler(this.Channels_BeatChangedSlowUpdate);
        }

        public void Channels_BeatChangedSlowUpdate(int beat)
        {
            int oldBeatInPixels = (int)(beatWidth * (this.beat / (float)Metronome.TicksPerBeat));
            int newBeatInPixels = (int)(beatWidth * (beat / (float)Metronome.TicksPerBeat));
            this.beat = beat;

            int x = 0;
            int width = 0;
            if (oldBeatInPixels < newBeatInPixels)
            {
                x = oldBeatInPixels;
                width = newBeatInPixels - oldBeatInPixels + 1;
            }
            else
            {
                x = newBeatInPixels;
                width = oldBeatInPixels - newBeatInPixels + 1;
            }

            Invalidate(new Rectangle(x, 0, width, Size.Height), false);
            Update();
        }

        private void UpdateSize()
        {
            int width = beatWidth * Metronome.Beats / Metronome.TicksPerBeat + 1;
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
            {
                PaintChannel(e, i * (channelHeight + 1));
            }

            Pen p = new Pen(Color.FromArgb(255, 0, 0), 1);
            int beatInPixels = (int)(BeatWidth * (beat / (float)Metronome.TicksPerBeat));
            e.Graphics.DrawLine(p, new Point(beatInPixels, 0), new Point(beatInPixels, Size.Height));
            p.Dispose();
        }

        private void PaintChannel(PaintEventArgs e, int y)
        {
            Pen p1 = new Pen(Color.FromArgb(80, 80, 80), 1);
            Pen p2 = new Pen(Color.FromArgb(30, 30, 30), 1);

            int beats = Metronome.Beats;
            for (int i = 0; i < beats; i++)
            {
                Rectangle beatRectangle = new Rectangle(i * beatWidth, 0, beatWidth, Size.Height);
                if (!e.ClipRectangle.IntersectsWith(beatRectangle))
                    continue;

                if (i % 2 == 0)
                    e.Graphics.DrawLine(p1, new Point(i * BeatWidth, y), new Point(i * BeatWidth, y + channelHeight));
                else
                    e.Graphics.DrawLine(p2, new Point(i * BeatWidth, y), new Point(i * BeatWidth, y + channelHeight));
            }

            e.Graphics.DrawLine(p1, new Point(0, y), new Point(Size.Width, y));
        }
    }
}
