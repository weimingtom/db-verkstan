using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Drawing.Design;
using VerkstanEditor.Logic;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class BeatPositionLine : UserControl
    {
        private int loopMarker = 0;
        private bool changeLoop = false;
        private bool dragBeat = false;
        private int beat;

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

        public BeatPositionLine()
        {
            InitializeComponent();
            Metronome.BeatChangedSlowUpdate += new Metronome.BeatChangedHandler(this.BeatPositionLine_BeatChangedSlowUpdate);
        }

        public void BeatPositionLine_BeatChangedSlowUpdate(int beat)
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

        private void BeatPositionLine_Paint(object sender, PaintEventArgs e)
        {
            /*
            Brush b = new SolidBrush(ForeColor);
            Pen p = new Pen(Color.FromArgb(100, 100, 100), 1);
            int beats = Width / beatWidth + 1;
            for (int i = 0; i < beats; i++)
            {
                Rectangle beatRectangle = new Rectangle(i * beatWidth, 0, beatWidth, Size.Height);
                if (!e.ClipRectangle.IntersectsWith(beatRectangle))
                    continue;

                if (i % 2 == 0)
                {
                    e.Graphics.DrawLine(p, new Point(i * beatWidth, 0), new Point(i * beatWidth, Height - 1));
                    String number = "" + (i + 1);
                    SizeF stringSize = e.Graphics.MeasureString(number, Font);
                    if (stringSize.Width < beatWidth)
                        e.Graphics.DrawString(number, Font, b, new Point(i * BeatWidth + 1, 0));
                }
                else
                {
                    e.Graphics.DrawLine(p, new Point(i * beatWidth, Height - 5), new Point(i * beatWidth, Height - 1));
                }
            }
            p.Dispose();
            b.Dispose();

            int beatInPixels = (int)(beatWidth * (beat / (float)Metronome.TicksPerBeat));
            e.Graphics.DrawLine(Pens.Red, new Point(beatInPixels, 0), new Point(beatInPixels, Height));

            Rectangle loopStartRectangle = new Rectangle(Metronome.LoopStart / Metronome.TicksPerBeat * beatWidth, 0, 2, Height);
            if (!e.ClipRectangle.IntersectsWith(loopStartRectangle))
                return;

            e.Graphics.DrawLine(Pens.Blue, loopStartRectangle.X, 0, loopStartRectangle.X, Height);
            e.Graphics.DrawLine(Pens.Blue, loopStartRectangle.X + 1, 0, loopStartRectangle.X + 1, Height);

            Rectangle loopEndRectangle = new Rectangle(Metronome.LoopEnd / Metronome.TicksPerBeat * beatWidth, 0, 2, Height);
            if (!e.ClipRectangle.IntersectsWith(loopEndRectangle))
                return;

            e.Graphics.DrawLine(Pens.Blue, loopEndRectangle.X, 0, loopEndRectangle.X, Height);
            e.Graphics.DrawLine(Pens.Blue, loopEndRectangle.X + 1, 0, loopEndRectangle.X + 1, Height);
            */     
        }

        private void BeatPositionLine_MouseDown(object sender, MouseEventArgs e)
        {
            /*
            if (e.Button == MouseButtons.Right)
            {
                loopMarker = e.X;
                changeLoop = true;
            }
            if (e.Button == MouseButtons.Left)
            {
                Metronome.Beat = e.X / beatWidth * Metronome.TicksPerBeat;
                dragBeat = true;
            }
             */
        }

        private void BeatPositionLine_MouseMove(object sender, MouseEventArgs e)
        {
            /*
            if (!dragBeat)
                return;

            Metronome.Beat = e.X / beatWidth * Metronome.TicksPerBeat;
             * */
        }

        private void BeatPositionLine_MouseUp(object sender, MouseEventArgs e)
        {
            /*
            dragBeat = false;

            if (changeLoop)
            {
                changeLoop = false;
                int diff = loopMarker - e.X;

                int start;
                int end;

                if (diff < 0)
                {
                    start = loopMarker / beatWidth * Metronome.TicksPerBeat;
                    end = e.X / beatWidth * Metronome.TicksPerBeat;
                }
                else
                {
                    start = loopMarker / beatWidth * Metronome.TicksPerBeat;
                    end = e.X / beatWidth * Metronome.TicksPerBeat;
                }

                if (start == end)
                    return;

                Metronome.LoopStart = start;
                Metronome.LoopEnd = end;
                Refresh();
            }
             * */
        }
    }
}
