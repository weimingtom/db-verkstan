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
using VerkstanEditor.Util;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class Channels : UserControl
    {
        private int beat;
        private int numberOfChannels = 12;
        public int SelectedChannelIndex = 3;
      
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
        [DefaultValue(31)]
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
                PaintChannelHighlights(e, i);
            PaintGrid(e);
            for (int i = 0; i < numberOfChannels; i++)
                PaintChannelClips(e, i); 
            PaintBeatPosition(e);
        }

        private void PaintBeatPosition(PaintEventArgs e)
        {
            int beatInPixels = (int)(beatWidth * (beat / (float)Metronome.TicksPerBeat));

            Rectangle rect = new Rectangle(beatInPixels, 0, 1, Height);
            e.ClipRectangle.Intersect(rect);

            if (rect.IsEmpty)
                return;

            Pen p = new Pen(Color.FromArgb(255, 0, 0), 1);
            e.Graphics.DrawLine(p, rect.X, rect.Y, rect.X, rect.Y + rect.Height);
            p.Dispose();
        }

        private void PaintGrid(PaintEventArgs e)
        {
            if (beatWidth == 0 || channelHeight == 0)
                return;

            Pen p1 = new Pen(Color.FromArgb(120, 120, 120), 1);
            Pen p2 = new Pen(Color.FromArgb(60, 60, 60), 1);

            int w = Width / beatWidth + 1;
            int h = Height / channelHeight + 1;

            for (int i = 0; i < h; i++)
            {
                Rectangle rect = new Rectangle(0, i * channelHeight, Size.Width, 1);
                e.ClipRectangle.Intersect(rect);

                if (rect.IsEmpty)
                    continue;

                e.Graphics.DrawLine(p1, rect.X, rect.Y, rect.X + rect.Width, rect.Y);
            }

            for (int i = 0; i < w; i++)
            {
                Rectangle rect = new Rectangle(i * beatWidth, 0, 1, Size.Height);
                e.ClipRectangle.Intersect(rect);

                if (rect.IsEmpty)
                    continue;

                if (i % 4 == 0)
                    e.Graphics.DrawLine(p1, rect.X, rect.Y, rect.X, rect.Y + rect.Height);
                else
                    e.Graphics.DrawLine(p2, rect.X, rect.Y, rect.X, rect.Y + rect.Height);
            }

            p1.Dispose();
            p2.Dispose();
        }

        private void PaintChannelClips(PaintEventArgs e, int index)
        {
            int y = index * channelHeight + 1;

            if (index != 4)
                return;

            for (int i = 0; i < 2; i++)
            {
                int start = 4;
                int end = 16;

               
                if (i == 1)
                {
                    start = 14;
                    end = 20;
                }

                Rectangle rect = new Rectangle(start*beatWidth, y, end*beatWidth - start*beatWidth, channelHeight - 1);
               

                if (!e.ClipRectangle.IntersectsWith(rect))
                    continue;

                double brightness = 1.0;
                if (false)
                    brightness = 1.3;

                Color color = RGBHSL.ModifyBrightness(Color.FromArgb(0, 0, 150), brightness);
                Color lightColor = RGBHSL.ModifyBrightness(color, 1.5);
                Color darkColor = RGBHSL.ModifyBrightness(color, 0.5);
                Brush brush = new SolidBrush(color);
                Pen lightPen = new Pen(lightColor);
                Pen darkPen = new Pen(darkColor, 1);
                Pen boundingPen = new Pen(Color.FromArgb(170, 170, 170));

                e.Graphics.FillRectangle(brush, rect);
                e.Graphics.DrawLine(lightPen,
                                    rect.X + 1,
                                    rect.Y + 1,
                                    rect.X + rect.Width - 1,
                                    rect.Y + 1);
                e.Graphics.DrawLine(lightPen,
                                   rect.X + 1,
                                   rect.Y + 2,
                                   rect.X + rect.Width - 1,
                                   rect.Y + 2);
                e.Graphics.DrawLine(darkPen,
                                   rect.X + 1,
                                   rect.Y + rect.Height - 3,
                                   rect.X + rect.Width - 1,
                                   rect.Y + rect.Height - 3);
                e.Graphics.DrawLine(darkPen,
                                    rect.X + 1,
                                    rect.Y + rect.Height - 2,
                                    rect.X + rect.Width - 1,
                                    rect.Y + rect.Height - 2);
                e.Graphics.DrawLine(darkPen,
                                   rect.X + 1,
                                   rect.Y + rect.Height - 1,
                                   rect.X + rect.Width - 1,
                                   rect.Y + rect.Height - 1);
                e.Graphics.DrawRectangle(boundingPen, rect);
            }
        }

        private void PaintChannelHighlights(PaintEventArgs e, int index)
        {
            int y = channelHeight * index;

            Rectangle rect = new Rectangle(0, y, Size.Width, channelHeight - 1);
            e.ClipRectangle.Intersect(rect);

            if (rect.IsEmpty)
                return;

            if (index == SelectedChannelIndex)
            {
                Brush b = new SolidBrush(Color.FromArgb(40, 40, 40));
                e.Graphics.FillRectangle(b, rect);
                b.Dispose();
            }
        }

        private void Channels_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left)
                return;

            int y1 = channelHeight * SelectedChannelIndex;
            Rectangle selectedChannelRect = new Rectangle(0, y1, Size.Width, channelHeight - 1);
            SelectedChannelIndex = e.Y / channelHeight;
            int y2 = channelHeight * SelectedChannelIndex;
            Rectangle newSelectedChannelRect = new Rectangle(0, y2, Size.Width, channelHeight - 1);
            
            Invalidate(selectedChannelRect);
            Update();
            Invalidate(newSelectedChannelRect);
            Update();
        }
    }
}
