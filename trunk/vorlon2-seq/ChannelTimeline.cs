﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

using VorlonSeq.Seq;

namespace VorlonSeq
{
    public partial class ChannelTimeline : UserControl
    {
        static int topMargin = 16;
        static int channelHeight = 32;
        static int channelPadding = 3;
        static int pixelsPerBar = 12;
        static bool moving = false;
        static bool selecting = false;
        static Point mouseDownPos;
        static Point mousePos;

        static List<Clip> selectedClips = new List<Clip>();

        public ChannelTimeline()
        {
            InitializeComponent();

            this.SetStyle(
                ControlStyles.AllPaintingInWmPaint |
                ControlStyles.UserPaint |
                ControlStyles.DoubleBuffer, true);


            // TEMP!
            Clip clip = new Clip();
            clip.StartTime = 4 * 16 * 5;
            clip.Length = 4 * 16 * 4;
            Sequencer.Song.Channels[2].AddClip(clip);

            Clip clip2 = new Clip();
            clip2.StartTime = 4 * 16 * 2;
            clip2.Length = 4 * 16 * 8;
            Sequencer.Song.Channels[5].AddClip(clip2);
        }

        private void ChannelTimeline_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;

            Song song = Sequencer.Song;

            for (int i = 0; i < Song.NumChannels; i++)
            {
                int y1 = i * channelHeight + topMargin;
                int y2 = i * channelHeight + topMargin + channelHeight - channelPadding;
                g.DrawLine(Pens.DarkGray, new Point(0, y1), new Point(Width, y1));
                g.DrawLine(Pens.DarkGray, new Point(0, y2), new Point(Width, y2));
                g.FillRectangle(Brushes.WhiteSmoke, new Rectangle(0, y1 + 1, Width, y2 - y1 - 1));

                for (int x = 0; x < Width; x += pixelsPerBar)
                {
                    int bar = x / pixelsPerBar;
                    Pen pen = null;
                    if (bar % 4 == 0)
                    {
                        pen = Pens.Silver;
                    }
                    else
                    {
                        pen = Pens.LightGray;
                    }
                    g.DrawLine(pen, new Point(x, y1 + 1), new Point(x, y2 - 1));
                }

                foreach (Clip clip in song.Channels[i].Clips)
                {
                    int x1 = (clip.StartTime * pixelsPerBar) / (4 * 16);
                    int x2 = (clip.EndTime * pixelsPerBar) / (4 * 16);
                    Rectangle rect = new Rectangle(x1, y1, x2 - x1, y2 - y1 - (channelPadding == 0 ? 1 : 0));
                    Brush niceBrush = new LinearGradientBrush(rect, Color.SkyBlue, Color.White, 90.0f);
                    g.FillRectangle(niceBrush, rect);
                    g.DrawRectangle(Pens.Black, rect);
                    if (selectedClips.Contains(clip))
                    {
                        rect.Inflate(new Size(-1, -1));
                        g.DrawRectangle(Pens.Black, rect);
                    }
                    niceBrush.Dispose();
                }
            }

            if (moving)
            {
                Point m = GetSelectedClipsMovement();
                foreach (Clip clip in selectedClips)
                {
                    int i = clip.Channel.Number + m.Y;
                    int y1 = i * channelHeight + topMargin;
                    int y2 = i * channelHeight + topMargin + channelHeight - channelPadding;
                    int x1 = ((clip.StartTime + m.X) * pixelsPerBar) / (4 * 16);
                    int x2 = ((clip.EndTime + m.X) * pixelsPerBar) / (4 * 16);
                    Rectangle rect = new Rectangle(x1, y1, x2 - x1, y2 - y1 - (channelPadding == 0 ? 1 : 0));
                    rect.Inflate(new Size(-1, -1));
                    g.DrawRectangle(Pens.DarkSlateGray, rect);
                }
            }
        }

        private void ChannelTimeline_SizeChanged(object sender, EventArgs e)
        {
            int channelArea = Height - topMargin;
            int newChannelHeight = channelArea / Song.NumChannels;
            newChannelHeight = Math.Max(newChannelHeight, 4);
            if (newChannelHeight != channelHeight)
            {
                channelHeight = newChannelHeight;
                channelPadding = newChannelHeight / 5;
                
                Refresh();
            }
        }

        private Channel GetChannelAt(int y)
        {
            y -= topMargin;
            if (y % channelHeight > (channelHeight - channelPadding))
            {
                return null;
            }

            int channelNo = y / channelHeight;
            if (channelNo < 0 || channelNo >= Song.NumChannels)
            {
                return null;
            }

            return Sequencer.Song.Channels[channelNo];
        }

        private int ConvertXToTime(int x)
        {
            return (x * (16 * 4)) / pixelsPerBar;
        }

        Clip GetClipAt(Point p)
        {
            Channel channel = GetChannelAt(p.Y);

            if (channel != null)
            {
                Clip clip = channel.GetClipAt(ConvertXToTime(p.X));
                return clip;
            }

            return null;
        }

        private void ChannelTimeline_MouseDown(object sender, MouseEventArgs e)
        {
            
            Clip clickedClip = GetClipAt(e.Location);

            if (!selectedClips.Contains(clickedClip))
            {
                selectedClips.Clear();

                if (clickedClip != null)
                {
                    selectedClips.Add(clickedClip);
                }
            }

            if (clickedClip != null)
            {
                moving = true;
            }
            else
            {
                selecting = true;
            }

            mouseDownPos = e.Location;
            mousePos = e.Location;
            
            Refresh();
        }

        private void ChannelTimeline_MouseUp(object sender, MouseEventArgs e)
        {
            mousePos = e.Location;

            if (moving)
            {
                Point m = GetSelectedClipsMovement();
                foreach(Clip c in selectedClips)
                {
                    c.StartTime += m.X;

                    if (m.Y != 0)
                    {
                        int oldChannel = c.Channel.Number;
                        int newChannel = oldChannel + m.Y;
                        Sequencer.Song.Channels[oldChannel].RemoveClip(c);
                        Sequencer.Song.Channels[newChannel].AddClip(c);
                    }
                }
            }
            
            moving = false;
            selecting = false;
            Refresh();
        }

        private void ChannelTimeline_MouseMove(object sender, MouseEventArgs e)
        {
            mousePos = e.Location;
            Refresh();
        }

        private int GetMouseMovementBars()
        {
            return (mousePos.X - mouseDownPos.X) / pixelsPerBar;
        }

        private int GetMouseMovementChannels()
        {
            return (mousePos.Y - mouseDownPos.Y) / channelHeight;
        }

        private Point GetSelectedClipsMovement()
        {
            int channels = GetMouseMovementChannels();
            int bars = GetMouseMovementBars();

            foreach (Clip c in selectedClips)
            {
                if (c.StartTime + bars * 64 < 0)
                {
                    bars = -c.StartTime / 64;
                }

                if (c.Channel.Number + channels < 0)
                {
                    channels = -c.Channel.Number;
                }

                if (c.Channel.Number + channels >= Song.NumChannels)
                {
                    channels = Song.NumChannels - (c.Channel.Number + 1);
                }
            }

            return new Point(bars * 64, channels);
        }

        private void ChannelTimeline_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            Clip clicked = GetClipAt(e.Location);
            if (clicked != null)
            {
                OnClipEditRequested(clicked);
            }
        }

        public delegate void ClipEditRequest(Clip clip);
        public event ClipEditRequest ClipEditRequested;

        private void OnClipEditRequested(Clip clicked)
        {
            if (ClipEditRequested != null)
            {
                ClipEditRequested(clicked);
            }
        }
    }
}
