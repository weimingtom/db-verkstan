﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
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
        #region Public Enums
        public enum Modes
        {
            Move,
            DrawGenerator,
            DrawSpline
        }
        #endregion

        #region Private Variables
        private int channelPadding = 2;
        private bool inSelect = false;
        private bool inMove = false;
        private bool inResize = false;
        private bool inDraw = false;
        private Point selectMarkLocation;
        private Point markLocation;
        private Point mouseLocation;
        private int drawX;
        private Rectangle selectionRectangle;
        private Rectangle lastSelectionRectangle;
        private Rectangle moveRectangle;
        private Rectangle lastMoveRectangle;
        private Rectangle resizeRectangle;
        private Rectangle lastResizeRectangle;
        private Rectangle drawRectangle;
        private Rectangle lastDrawRectangle;
        private Timeline.EventHandler clipStateChangedHandler;
        private Timeline.EventHandler clipMovedHandler;
        private Timeline.EventHandler clipAddedHandler;
        private Timeline.EventHandler clipRemovedHandler;
        private Timeline.EventHandler clipResizedHandler;
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
                {
                    timeline.ClipStateChanged -= clipStateChangedHandler;
                    timeline.ClipMoved -= clipMovedHandler;
                    timeline.ClipRemoved -= clipRemovedHandler;
                    timeline.ClipResized -= clipResizedHandler;
                    timeline.ClipAdded -= clipAddedHandler;
                }

                timeline = value;
                if (timeline != null)
                {
                    timeline.ClipStateChanged += clipStateChangedHandler;
                    timeline.ClipMoved += clipMovedHandler;
                    timeline.ClipRemoved += clipRemovedHandler;
                    timeline.ClipResized += clipResizedHandler;
                    timeline.ClipAdded += clipAddedHandler;
                }
            }
        }
        private Modes mode;
        public Modes Mode
        {
            set
            {
                mode = value;
                if (timeline != null)
                    timeline.DeselectAll();
            }
            get
            {
                return mode;
            }
        }
        #endregion

        #region Constructors
        public TimelineChannels()
        {
            InitializeComponent();
            DoubleBuffered = true;
            Metronome.BeatChangedSlowUpdate += new Metronome.BeatChangedHandler(this.TimelineChannels_BeatChangedSlowUpdate);
            clipStateChangedHandler = new Timeline.EventHandler(this.timeline_ClipStateChanged);
            clipMovedHandler = new Timeline.EventHandler(this.timeline_ClipMoved);
            clipAddedHandler = new Timeline.EventHandler(this.timeline_ClipAdded);
            clipRemovedHandler = new Timeline.EventHandler(this.timeline_ClipRemoved);
            clipResizedHandler = new Timeline.EventHandler(this.timeline_ClipResized);
            Mode = Modes.Move;
        }
        #endregion

        #region Event Handlers
        public void timeline_ClipStateChanged(Timeline.EventArgs e)
        {
            foreach (Clip clip in e.Clips)
                Invalidate(ClipDimensionToPixelDimension(clip));
        }
        public void timeline_ClipMoved(Timeline.EventArgs e)
        {
            foreach (Clip clip in e.Clips)
            {
                Invalidate(BeatDimensionToPixelDimension(clip.LastDimension));
                Invalidate(BeatDimensionToPixelDimension(clip.Dimension));
            }

            UpdateSize();
        }
        public void timeline_ClipAdded(Timeline.EventArgs e)
        {
            foreach (Clip clip in e.Clips)
                Invalidate(BeatDimensionToPixelDimension(clip.Dimension));

            UpdateSize();
        }
        public void timeline_ClipRemoved(Timeline.EventArgs e)
        {
            foreach (Clip clip in e.Clips)
                Invalidate(BeatDimensionToPixelDimension(clip.Dimension));

            UpdateSize();
        }
        public void timeline_ClipResized(Timeline.EventArgs e)
        {
            foreach (Clip clip in e.Clips)
            {
                Invalidate(BeatDimensionToPixelDimension(clip.LastDimension));
                Invalidate(BeatDimensionToPixelDimension(clip.Dimension));
            }

            UpdateSize();
        }
        public void TimelineChannels_BeatChangedSlowUpdate(int beat)
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
        private void TimelineChannels_Load(object sender, EventArgs e)
        {
            UpdateSize();
        }
        private void TimelineChannels_ParentChanged(object sender, EventArgs e)
        {
            UpdateSize();
            Parent.Resize += new System.EventHandler(this.TimelineChannels_ParentResized);
        }
        private void TimelineChannels_ParentResized(object sender, EventArgs e)
        {
            UpdateSize();
        }
        private void TimelineChannels_Paint(object sender, PaintEventArgs e)
        {
            if (timeline == null)
                return;

            PaintGrid(e);

            foreach (Channel channel in timeline.Channels)
            {
                PaintChannel(e, channel);
            }
          
            /*
            PaintBeatPosition(e);
             * */

            if (inSelect)
            {
                Pen p = new Pen(Color.White, 1);
                p.DashStyle = DashStyle.Dash;
                e.Graphics.DrawRectangle(p, selectionRectangle.X, selectionRectangle.Y, selectionRectangle.Width - 1, selectionRectangle.Height - 1);
                p.Dispose();
            }

            if (inResize)
            {
                ICollection<Clip> selected = timeline.GetSelected();
                foreach (Clip clip in selected)
                    PaintResizingClip(clip, e);
            }

            if (inMove)
            {
                ICollection<Clip> selected = timeline.GetSelected();
                foreach (Clip clip in selected)
                    PaintMovingClip(clip, e);
            }

            if (inDraw)
            {
                PaintDraw(e);
            }
        }
        private void TimelineChannels_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                mouseLocation = new Point(e.X, e.Y);
                selectMarkLocation = mouseLocation;
                markLocation = selectMarkLocation;

                if (Mode == Modes.Move)
                {
                    selectionRectangle = CalculateSelectionRectangle();
                    ICollection<Clip> selected = timeline.GetIn(PixelDimensionToBeatDimension(selectionRectangle));

                    if (selected.Count == 0)
                    {
                        inSelect = true;
                        timeline.Select(PixelDimensionToBeatDimension(selectionRectangle));
                        Invalidate(selectionRectangle);
                    }
                    else
                    {
                        Clip clip = selected.First();

                        if (!clip.IsSelected)
                            timeline.Select(PixelDimensionToBeatDimension(selectionRectangle));


                        if (CalculateResizeAreaForClip(clip).Contains(mouseLocation))
                        {
                            inResize = true;
                            resizeRectangle = CalculateResizeRectangle();
                            Invalidate(resizeRectangle);
                        }
                        else
                        {

                            inMove = true;
                            moveRectangle = CalculateMoveRectangle();
                            Invalidate(moveRectangle);
                        }
                    }
                }

                if (Mode == Modes.DrawGenerator || Mode == Modes.DrawSpline)
                {
                    drawX = e.X - e.X % beatWidth;
                    drawRectangle = CalculateDrawRectangle();
                    Invalidate(drawRectangle);
                    inDraw = true; 
                }
            }
        }
        private void TimelineChannels_MouseMove(object sender, MouseEventArgs e)
        {
            mouseLocation = new Point(e.X, e.Y);

            if (Mode == Modes.Move)
            {
                if (inSelect)
                {
                    lastSelectionRectangle = selectionRectangle;
                    selectionRectangle = CalculateSelectionRectangle();
                    timeline.Select(PixelDimensionToBeatDimension(selectionRectangle));
                    if (!lastSelectionRectangle.Equals(selectionRectangle))
                    {
                        Invalidate(lastSelectionRectangle);
                        Invalidate(selectionRectangle);
                    }
                }

                if (inMove)
                {
                    lastMoveRectangle = moveRectangle;
                    moveRectangle = CalculateMoveRectangle();
                    if (!lastMoveRectangle.Equals(moveRectangle))
                    {
                        Invalidate(lastMoveRectangle);
                        Invalidate(moveRectangle);
                    }
                }

                if (inResize)
                {
                    lastResizeRectangle = resizeRectangle;
                    resizeRectangle = CalculateResizeRectangle();
                    if (!lastResizeRectangle.Equals(resizeRectangle))
                    {
                        Invalidate(lastResizeRectangle);
                        Invalidate(resizeRectangle);
                    }
                }
            }

            if (mode == Modes.DrawGenerator || mode == Modes.DrawSpline)
            {
                if (inDraw)
                {
                    lastDrawRectangle = drawRectangle;
                    drawRectangle = CalculateDrawRectangle();
                    if (!lastDrawRectangle.Equals(drawRectangle))
                    {
                        Invalidate(lastDrawRectangle);
                        Invalidate(drawRectangle);
                    }
                }
            }
        }
        private void TimelineChannels_MouseUp(object sender, MouseEventArgs e)
        {
            if (Mode == Modes.Move)
            {
                if (inSelect)
                {
                    Invalidate(selectionRectangle);
                }

                if (inMove)
                {        
                    moveRectangle = CalculateMoveRectangle();
                    Invalidate(moveRectangle);
                    timeline.MoveSelected(CalculateMovePoint());
                }

                if (inResize)
                {        
                    resizeRectangle = CalculateResizeRectangle();
                    Invalidate(resizeRectangle);
                    timeline.ResizeSelected(CalculateResizeX());
                }
            }

            if (Mode == Modes.DrawGenerator)
            {
                if (inDraw)
                {
                    drawRectangle = CalculateDrawRectangle();
                    Invalidate(drawRectangle);
                    
                    Clip clip = null;
                    if (mode == Modes.DrawGenerator)
                        clip = new GeneratorClip();
                    else if (mode == Modes.DrawSpline)
                        clip = new SplineClip();

                    timeline.AddClip(clip, CalculateDrawPoint(), CalculateDrawBeats());
                }
            }
            inSelect = false;
            inResize = false;
            inMove = false;
            inDraw = false;
        }
        private void TimelineChannels_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
                timeline.RemoveSelected();
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
                if (e.ClipRectangle.IntersectsWith(ClipDimensionToPixelDimension(clip)))
                    PaintClip(e, clip);
        }
        private void PaintClip(PaintEventArgs e, Clip clip)
        {
            Rectangle dimension = ClipDimensionToPixelDimension(clip);
            Region graphicsClip = e.Graphics.Clip;
            e.Graphics.Clip = new Region(dimension);

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

            e.Graphics.Clip = graphicsClip;
        }
        private void PaintMovingClip(Clip clip, PaintEventArgs e)
        {
            Point p = CalculateMovePoint();
            Rectangle dim = clip.Dimension;
            dim.X += p.X;
            dim.Y += p.Y;
            dim = BeatDimensionToPixelDimension(dim);
            dim.Height = channelHeight;
            e.Graphics.DrawRectangle(Pens.White, new Rectangle(dim.X, dim.Y, dim.Width - 1, dim.Height - 1));
        }
        private void PaintResizingClip(Clip clip, PaintEventArgs e)
        {
            int x = CalculateResizeX();
            Rectangle dim = clip.Dimension;
            dim.Width += x;
            dim = BeatDimensionToPixelDimension(dim);
            dim.Height = channelHeight;
            e.Graphics.DrawRectangle(Pens.White, new Rectangle(dim.X, dim.Y, dim.Width - 1, dim.Height - 1));
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
        private void PaintDraw(PaintEventArgs e)
        {
            Rectangle rect = CalculateDrawRectangle();
            e.Graphics.DrawRectangle(Pens.White, new Rectangle(rect.X, rect.Y, rect.Width - 1, rect.Height - 1));
        }
        private Rectangle CalculateSelectionRectangle()
        {
            int x1 = 0;
            int y1 = 0;
            int x2 = 0;
            int y2 = 0;

            if (mouseLocation.X < selectMarkLocation.X)
            {
                x1 = mouseLocation.X;
                x2 = selectMarkLocation.X;
            }
            else
            {
                x2 = mouseLocation.X;
                x1 = selectMarkLocation.X;
            }

            if (mouseLocation.Y < selectMarkLocation.Y)
            {
                y1 = mouseLocation.Y;
                y2 = selectMarkLocation.Y;
            }
            else
            {
                y2 = mouseLocation.Y;
                y1 = selectMarkLocation.Y;
            }

            return new Rectangle(x1, y1, x2 - x1, y2 - y1);
        }
        private Rectangle CalculateMoveRectangle()
        {
            ICollection<Clip> selected = timeline.GetSelected();
            Rectangle result = selected.First().Dimension;

            foreach (Clip clip in selected)
                result = Rectangle.Union(result, clip.Dimension);

            Point movePoint = CalculateMovePoint();
            result.X += movePoint.X;
            result.Y += movePoint.Y;

            return BeatDimensionToPixelDimension(result);
        }
        private Rectangle CalculateResizeRectangle()
        {
            int x = CalculateResizeX();
            ICollection<Clip> selected = timeline.GetSelected();
            Rectangle result = selected.First().Dimension;
            result.Width += x;
            foreach (Clip clip in selected)
            {
                Rectangle clipDimension = clip.Dimension;
                clipDimension.X += x;
                result = Rectangle.Union(result, clipDimension);
            }

            return BeatDimensionToPixelDimension(result);
        }
        private Rectangle CalculateDrawRectangle()
        {
            Point p = PixelPointToBeatPoint(markLocation);
            int width = CalculateDrawBeats();
            if (width < 1)
                width = 1;
            int height = 1;

            Rectangle result = new Rectangle(p.X, p.Y, width, height);
            result = BeatDimensionToPixelDimension(result);
            result.Height = channelHeight;
            return result;
        }
        private Point CalculateMovePoint()
        {
            Point p = PixelPointToBeatPoint(mouseLocation);
            Point p2 = PixelPointToBeatPoint(markLocation);
            return new Point(p.X - p2.X,
                             p.Y - p2.Y);
        }
        private int CalculateResizeX()
        {
            Point p = PixelPointToBeatPoint(mouseLocation);
            Point p2 = PixelPointToBeatPoint(markLocation);
            int x = p.X - p2.X;
            return x;
        }
        private int CalculateDrawBeats()
        {
            int x = mouseLocation.X - drawX;
            x -= x % beatWidth;

            return x / beatWidth + 1;
        }
        private Point CalculateDrawPoint()
        {
            return PixelPointToBeatPoint(markLocation);
        }
        private Rectangle ClipDimensionToPixelDimension(Clip clip)
        {
            Rectangle result = BeatDimensionToPixelDimension(clip.Dimension);
            result.Height = channelHeight;
            return result;
        }
        private Rectangle BeatDimensionToPixelDimension(Rectangle dimension)
        {
            Rectangle result = new Rectangle();
            result.X = dimension.X * beatWidth;
            result.Y = channelPadding + dimension.Y * channelHeight + dimension.Y * channelPadding * 2 + 1;
            result.Width = dimension.Width * beatWidth + 1;
            result.Height = dimension.Height * (channelHeight + channelPadding * 2);
            return result;
        }
        private Rectangle PixelDimensionToBeatDimension(Rectangle dimension)
        {
            Rectangle result = new Rectangle();
            result.X = dimension.X / beatWidth;
            result.Y = dimension.Y / (channelHeight + channelPadding * 2);
            result.Width = (dimension.X + dimension.Width) / beatWidth - dimension.X / beatWidth + 1;
            result.Height = (dimension.Y + dimension.Height) / (channelHeight + channelPadding * 2) - dimension.Y / (channelHeight + channelPadding * 2) + 1;
            return result;
        }
        private Point PixelPointToBeatPoint(Point point)
        {
            Point result = new Point();
            result.X = point.X / beatWidth;
            result.Y = point.Y / (channelHeight + channelPadding * 2);
            return result;
        }
        private Point BeatPointToPixelPoint(Point point)
        {
            Point result = new Point();
            result.X = point.X * beatWidth;
            result.Y = channelPadding + point.Y * channelHeight + point.Y * channelPadding * 2 + 1;
            return result;
        }
        private Rectangle CalculateResizeAreaForClip(Clip clip)
        {
            Rectangle dimension = ClipDimensionToPixelDimension(clip);
            Rectangle result = new Rectangle();
            result.X = dimension.X + dimension.Width - (beatWidth - 5);
            result.Y = dimension.Y;
            result.Width = beatWidth - 5;
            result.Height = dimension.Height;
            return result;
        }
        #endregion
    }
}
