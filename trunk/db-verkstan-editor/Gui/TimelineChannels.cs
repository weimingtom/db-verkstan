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
    public partial class TimelineChannels : UserControl
    {
        private Point mouseMarkerLocation;
        private Point mouseLocation;
        private bool inMove = false;
        private int beat;
        private int channelPadding = 2;
        private Verkstan.Clip selectedClip = null;
      
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
                UpdateSize();
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

        private int selectedChannelIndex = - 1;
        public int SelectedChannelIndex
        {
            set
            {
                selectedChannelIndex = value;
                Refresh();
            }
            get
            {
                return selectedChannelIndex;
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
                selectedClip = null;
                selectedChannelIndex = -1;
                UpdateSize();
                Refresh();
            }
        }

        public TimelineChannels()
        {
            InitializeComponent();
            DoubleBuffered = true;
            Metronome.BeatChangedSlowUpdate += new Metronome.BeatChangedHandler(this.Channels_BeatChangedSlowUpdate);
        }

        public delegate void ChannelSelectedHandler(int index);
        public event ChannelSelectedHandler ChannelSelected;

        private void OnChannelSelected(int index)
        {
            if (ChannelSelected != null)
                ChannelSelected(index);
        }

        private void InvalidateSelectedChannel()
        {
            int y1 = channelHeight * selectedChannelIndex;
            Rectangle selectedChannelRect = new Rectangle(0, y1, Size.Width, channelHeight - 1);
            Invalidate(selectedChannelRect);
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
            if (scene == null)
            {
                Width = 0;
                Height = 0;
                return;
            }

            int width = scene.Beats / Metronome.TicksPerBeat * beatWidth + 1;
            int height = scene.Channels.Count * (channelHeight + 2 * channelPadding) + 1;                     
            Height = height;
            
            if (Width < width)
                Width = width;

            if (Parent == null)
                return;

            if (Parent.ClientRectangle.Width > Width)
                Width = Parent.ClientRectangle.Width;
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
            if (scene == null)
                return;

            for (int i = 0; i < scene.Channels.Count; i++)
                PaintChannelHighlights(e, i);
            PaintGrid(e);
            foreach (Verkstan.Channel channel in scene.Channels)
                 PaintChannelClips(e, channel);

            if (inMove)
                PaintMove(e);

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
            int h = Height / (channelPadding* 2 + channelHeight);

        
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

            int y = 0;
            for (int i = 0; i <= h; i++)
            {
                y += channelPadding;
                Rectangle rect = new Rectangle(0, y, Size.Width, 1);
                e.ClipRectangle.Intersect(rect);

                if (rect.IsEmpty)
                    continue;

                e.Graphics.DrawLine(p1, rect.X, rect.Y, rect.X + rect.Width, rect.Y);

                y += channelHeight;
                rect = new Rectangle(0, y, Size.Width, 1);
                e.ClipRectangle.Intersect(rect);

                if (rect.IsEmpty)
                    continue;

                e.Graphics.DrawLine(p1, rect.X, rect.Y, rect.X + rect.Width, rect.Y);
                y += channelPadding;
            }

            Brush b = new SolidBrush(BackColor);
            y = 0;
            for (int i = 0; i <= h; i++)
            {
                Rectangle rect = new Rectangle(0, y, Size.Width, channelPadding);
                e.ClipRectangle.Intersect(rect);

                if (rect.IsEmpty)
                    continue;

                e.Graphics.FillRectangle(b, rect);

                y += channelPadding + channelHeight + 1;
                rect = new Rectangle(0, y, Size.Width, channelPadding);
                e.ClipRectangle.Intersect(rect);

                if (rect.IsEmpty)
                    continue;

                e.Graphics.FillRectangle(b, rect);
                y += 1;
            }

            p1.Dispose();
            p2.Dispose();
            b.Dispose();
        }

        private void PaintChannelClips(PaintEventArgs e, Verkstan.Channel channel)
        {
            int index = scene.Channels.IndexOf(channel);
            int y =  index * (channelHeight + channelPadding * 2) + channelPadding;

            foreach(Verkstan.Clip clip in channel.Clips)
            {
                int start = clip.Start / Metronome.TicksPerBeat;
                int end = clip.End / Metronome.TicksPerBeat;

                Rectangle rect = new Rectangle(start*beatWidth, y, end*beatWidth - start*beatWidth + 1, channelHeight);
               
                if (!e.ClipRectangle.IntersectsWith(rect))
                    continue;

                double brightness = 1.0;
                if (clip == selectedClip)
                    brightness = 1.4;

                Color color = RGBHSL.ModifyBrightness(Color.FromArgb(70, 90, 150), brightness);
                Color lightColor = RGBHSL.ModifyBrightness(color, 1.3);
                Color notSoDarkColor = RGBHSL.ModifyBrightness(color, 0.9);
                Color darkColor = RGBHSL.ModifyBrightness(color, 0.7);
                Brush brush = new SolidBrush(color);
                Pen lightPen = new Pen(lightColor);
                Pen darkPen = new Pen(darkColor, 1);
                Pen notSoDarkPen = new Pen(notSoDarkColor, 1);
                Pen boundingPen = new Pen(Color.FromArgb(170, 170, 170));

                e.Graphics.FillRectangle(brush, rect);
                e.Graphics.DrawLine(notSoDarkPen, rect.X, rect.Y + rect.Height / 2, rect.X + rect.Width - 2, rect.Y + rect.Height / 2);
                Bitmap preview = ClipPreviewCache.GetPreview(clip, darkColor, beatWidth, channelHeight - 8);
                e.Graphics.DrawImage(preview, rect.X, rect.Y + 4);

                e.Graphics.DrawLine(lightPen,
                                    rect.X + 1,
                                    rect.Y + 1,
                                    rect.X + rect.Width - 1,
                                    rect.Y + 1);
                e.Graphics.DrawLine(lightPen,
                                   rect.X + 1,
                                   rect.Y + 2,
                                   rect.X + rect.Width - 2,
                                   rect.Y + 2);
                e.Graphics.DrawLine(darkPen,
                                   rect.X + 1,
                                   rect.Y + rect.Height - 3,
                                   rect.X + rect.Width - 2,
                                   rect.Y + rect.Height - 3);
                e.Graphics.DrawLine(darkPen,
                                    rect.X + 1,
                                    rect.Y + rect.Height - 2,
                                    rect.X + rect.Width - 2,
                                    rect.Y + rect.Height - 2);
                e.Graphics.DrawLine(darkPen,
                                   rect.X + 1,
                                   rect.Y + rect.Height - 1,
                                   rect.X + rect.Width - 2,
                                   rect.Y + rect.Height - 1);
                e.Graphics.DrawRectangle(boundingPen, rect.X, rect.Y, rect.Width - 1, rect.Height);
            }
        }

        private void PaintMove(PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(Pens.White, GetMovingClipRectangle());
        }

        private void PaintChannelHighlights(PaintEventArgs e, int index)
        {
            int y = channelHeight * index + index * 2 * channelPadding + channelPadding;

            Rectangle rect = new Rectangle(0, y, Size.Width, channelHeight);
            e.ClipRectangle.Intersect(rect);

            if (rect.IsEmpty)
                return;

            if (index == selectedChannelIndex)
            {
                Brush b = new SolidBrush(Color.FromArgb(40, 40, 40));
                e.Graphics.FillRectangle(b, rect);
                b.Dispose();
            }
        }

        private void Channels_MouseDown(object sender, MouseEventArgs e)
        {
            mouseMarkerLocation = e.Location;

            int index = e.Y / (channelHeight +  2 * channelPadding);
            if (index != SelectedChannelIndex)
            {
                selectedChannelIndex = index;
                OnChannelSelected(SelectedChannelIndex);
            }

            if (e.Button == MouseButtons.Left)
            {
                selectedClip = null;
                bool selectedClipFound = false;
                foreach (Verkstan.Channel channel in scene.Channels)
                {
                    foreach (Verkstan.Clip clip in channel.Clips)
                    {
                        int i = scene.Channels.IndexOf(channel);
                        int y = i * (channelHeight + channelPadding * 2) + channelPadding;

                        int start = clip.Start / Metronome.TicksPerBeat;
                        int end = clip.End / Metronome.TicksPerBeat;
                        Rectangle rect = new Rectangle(start * beatWidth, y, end * beatWidth - start * beatWidth, channelHeight);

                        if (rect.Contains(e.X, e.Y))
                        {
                            selectedClip = clip;
                            selectedClipFound = true;
                            break;
                        }
                    }

                    if (selectedClipFound)
                        break;
                }

                if (selectedClip != null)
                    inMove = true;
            }

            Refresh();
        }

        private void TimelineChannels_MouseMove(object sender, MouseEventArgs e)
        {
            mouseLocation = e.Location;

            if (inMove)
                Refresh();
        }

        private Rectangle GetMovingClipRectangle()
        {
            int index = mouseLocation.Y / (channelHeight +  2 * channelPadding);
            
            if (index < 0)
                index = 0;
            if (index > scene.Channels.Count - 1)
                index = scene.Channels.Count - 1;

            int x = selectedClip.Start / Metronome.TicksPerBeat * beatWidth - ((mouseLocation.X - mouseMarkerLocation.X) % beatWidth - (mouseLocation.X - mouseMarkerLocation.X));

            if (x < 0)
                x = 0;

            int y = channelHeight * index + index * 2 * channelPadding + channelPadding;
            int width = (selectedClip.End - selectedClip.Start) / Metronome.TicksPerBeat * beatWidth;
            int height = channelHeight;
            return new Rectangle(x, y, width, height);
        }

        private void TimelineChannels_MouseUp(object sender, MouseEventArgs e)
        {
            if (inMove)
            {
                inMove = false;
                Rectangle rect = GetMovingClipRectangle();
                scene.Channels[selectedChannelIndex].RemoveClip(selectedClip);
                int index = mouseLocation.Y / (channelHeight +  2 * channelPadding);
                scene.Channels[index].AddClip(selectedClip);
                selectedClip.Start = rect.X / beatWidth * Metronome.TicksPerBeat;
                selectedClip.End = selectedClip.Start + rect.Width / beatWidth * Metronome.TicksPerBeat;
                scene.UpdateRealClips();
                Metronome.Beats = scene.Beats;
                UpdateSize();
                Refresh();
            }
        }
   }
}
