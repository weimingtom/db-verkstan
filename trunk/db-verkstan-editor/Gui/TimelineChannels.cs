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
        #region Private Variables
        private Point mouseMarkerLocation;
        private Point mouseLocation;
        private bool inMove = false;
        private int channelPadding = 2;
        private Timeline.EventHandler clipStateChangedHandler;
        #endregion

        #region Properties
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
                UpdateSize();
            }
            get
            {
                return channelHeight;
            }

        }
        private Timeline timeline;
        public Timeline Timeline
        {
            get
            {
                return timeline;
            }
            set
            {
                if (timeline != null)
                    timeline.ClipStateChanged -= clipStateChangedHandler;

                timeline = value;
                if (timeline != null)
                    timeline.ClipStateChanged += clipStateChangedHandler;
            }
        }
        #endregion

        #region Constructors
        public TimelineChannels()
        {
            InitializeComponent();
            DoubleBuffered = true;
            Metronome.BeatChangedSlowUpdate += new Metronome.BeatChangedHandler(this.Channels_BeatChangedSlowUpdate);
            clipStateChangedHandler = new Timeline.EventHandler(this.timeline_ClipStateChanged);
        }
        #endregion

        #region Event Handlers
        public void timeline_ClipStateChanged(Channel channel, Clip clip)
        {
            Invalidate(GetClipDimension(clip));
        }
        public void Channels_BeatChangedSlowUpdate(int beat)
        {
            /*
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
             */
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
            if (timeline == null)
                return;

            PaintGrid(e);

           
            foreach (Channel channel in timeline.Channels)
            {
                PaintChannel(e, channel);
            }
          
            /*
            if (inMove)
                PaintMove(e);

            PaintBeatPosition(e);
             * */
        }
        private void Channels_MouseDown(object sender, MouseEventArgs e)
        {
            mouseMarkerLocation = e.Location;

            int beat = e.X / beatWidth;
            int channelIndex = e.Y / (channelHeight + 2 * channelPadding);

            if (e.Button == MouseButtons.Left)
            {
                Clip selected = timeline.GetAt(channelIndex, beat);
                if (selected != null)
                    timeline.SelectAt(channelIndex, beat);
                else
                    timeline.Deselect();
            }
            /*
            

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
             */
        }
        private void TimelineChannels_MouseMove(object sender, MouseEventArgs e)
        {
            mouseLocation = e.Location;

            if (inMove)
                Refresh();
        }
        private void TimelineChannels_MouseUp(object sender, MouseEventArgs e)
        {
            /*
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
             */

        }
        #endregion

        #region Private Methods
        private void UpdateSize()
        {
            if (timeline == null)
            {
                Width = 0;
                Height = 0;
                return;
            }

            int width = timeline.GetBeats() * beatWidth + 1;
            int height = timeline.Channels.Count * (channelHeight + 2 * channelPadding) + 1;

            if (Parent == null)
            {
                this.Size = new Size(width, height);
                return;
            }

            if (Parent.ClientRectangle.Width > width)
                width = Parent.ClientRectangle.Width;

            this.Size = new Size(width, height);
            Rectangle rectangle = new Rectangle(0, 0, width, height);

            Invalidate(Rectangle.Intersect(Parent.ClientRectangle, rectangle));
        }
        private void PaintBeatPosition(PaintEventArgs e)
        {
            /*
            int beatInPixels = (int)(beatWidth * (beat / (float)Metronome.TicksPerBeat));

            Rectangle rect = new Rectangle(beatInPixels, 0, 1, Height);
            e.ClipRectangle.Intersect(rect);

            if (rect.IsEmpty)
                return;

            Pen p = new Pen(Color.FromArgb(255, 0, 0), 1);
            e.Graphics.DrawLine(p, rect.X, rect.Y, rect.X, rect.Y + rect.Height);
            p.Dispose();
             */
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
        private void PaintChannel(PaintEventArgs e, Channel channel)
        {
            foreach (Clip clip in channel.Clips)
            {
                Rectangle dimension = GetClipDimension(clip);
                if (e.ClipRectangle.IntersectsWith(dimension))
                    PaintClip(e, clip);
            }
            /*
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
       * */
        }
        private void PaintClip(PaintEventArgs e, Clip clip)
        {
            double brightness = 1.0;
            if (clip.IsSelected)
                brightness = 1.3;

            Color color = RGBHSL.ModifyBrightness(Color.FromArgb(70, 90, 150), brightness);
            Color lightColor = RGBHSL.ModifyBrightness(color, 1.3);
            Color notSoDarkColor = RGBHSL.ModifyBrightness(color, 0.9);
            Color darkColor = RGBHSL.ModifyBrightness(color, 0.7);
            Color previewColor = RGBHSL.ModifyBrightness(Color.FromArgb(70, 90, 150), 0.75);

            Brush b = new SolidBrush(color);
            Pen p1 = new Pen(notSoDarkColor);
            Pen p2 = new Pen(lightColor);
            Pen p3 = new Pen(darkColor);
            Rectangle dimension = GetClipDimension(clip);
            e.Graphics.FillRectangle(b, dimension);
            e.Graphics.DrawLine(p1, dimension.Left, dimension.Top + dimension.Height / 2, dimension.Left + dimension.Width - 1, dimension.Top + dimension.Height / 2);
            Bitmap preview = clip.GetPreview(dimension.Width, dimension.Height - 2, previewColor);
            e.Graphics.DrawImage(preview, dimension.Left, dimension.Top + 2);
            e.Graphics.DrawLine(p2, dimension.Left, dimension.Top, dimension.Left + dimension.Width - 1, dimension.Top);
            e.Graphics.DrawLine(p2, dimension.Left, dimension.Top, dimension.Left, dimension.Top + dimension.Height - 1);
            e.Graphics.DrawLine(p2, dimension.Left + dimension.Width - 1, dimension.Top, dimension.Left + dimension.Width - 1, dimension.Top + dimension.Height - 1);
            e.Graphics.DrawLine(p3, dimension.Left + 1, dimension.Top + dimension.Height - 2, dimension.Left + dimension.Width - 2, dimension.Top + dimension.Height - 2);
            e.Graphics.DrawLine(p3, dimension.Left + 1, dimension.Top + dimension.Height - 1, dimension.Left + dimension.Width - 2, dimension.Top + dimension.Height - 1);
            p1.Dispose();
            p2.Dispose();
            p3.Dispose();
            b.Dispose();
        }
        private void PaintMove(PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(Pens.White, GetMovingClipRectangle());
        }
        private void PaintChannelHighlights(PaintEventArgs e, int index)
        {
            /*
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
             * */
        }
        private Rectangle GetMovingClipRectangle()
        {
            return new Rectangle();
            /*
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
             */
        }
        private Rectangle GetClipDimension(Clip clip)
        {
            int y = channelPadding + clip.ChannelIndex*channelHeight + clip.ChannelIndex*channelPadding*2 + 1;
            return new Rectangle(clip.StartBeat * beatWidth, y, clip.Beats * beatWidth + 1, channelHeight - 1); 
        }
        #endregion
    }
}
