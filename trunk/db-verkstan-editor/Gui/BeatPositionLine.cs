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
            UpdateSize();
            Metronome.BeatChangedSlowUpdate += new Metronome.BeatChangedHandler(this.BeatPositionLine_BeatChangedSlowUpdate);
        }

        public void BeatPositionLine_BeatChangedSlowUpdate(int beat)
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
            Size = new Size(Metronome.Beats / Metronome.TicksPerBeat * beatWidth + 1, 25);
        }

        private void BeatPositionLine_Paint(object sender, PaintEventArgs e)
        {
            Brush b = new SolidBrush(ForeColor);
            Pen p = new Pen(Color.FromArgb(100, 100, 100), 1);
            int beats = Metronome.Beats;
            for (int i = 0; i < beats; i++)
            {
                Rectangle beatRectangle = new Rectangle(i * beatWidth, 0, beatWidth, Size.Height);
                if (!e.ClipRectangle.IntersectsWith(beatRectangle))
                    continue;

                if (i % 2 == 0)
                {
                    e.Graphics.DrawLine(p, new Point(i * beatWidth, 0), new Point(i * beatWidth, 24));
                    e.Graphics.DrawString("" + (i + 1), Font, b, new Point(i * BeatWidth + 1, 0));
                }
                else
                {
                    e.Graphics.DrawLine(p, new Point(i * beatWidth, 20), new Point(i * beatWidth, 24));
                }
            }
            p.Dispose();
            b.Dispose();

            p = new Pen(Color.FromArgb(255, 0, 0), 1);
            int beatInPixels = (int)(beatWidth * (beat / (float)Metronome.TicksPerBeat));
            e.Graphics.DrawLine(p, new Point(beatInPixels, 0), new Point(beatInPixels, 25));
            p.Dispose();
        }

        private void BeatPositionLine_Load(object sender, EventArgs e)
        {
            UpdateSize();
        }

        private void BeatPositionLine_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left)
                return;

            Metronome.Beat = e.X / beatWidth * Metronome.TicksPerBeat;

            dragBeat = true;
        }

        private void BeatPositionLine_MouseMove(object sender, MouseEventArgs e)
        {
            if (!dragBeat)
                return;

            Metronome.Beat = e.X / beatWidth * Metronome.TicksPerBeat;
        }

        private void BeatPositionLine_MouseUp(object sender, MouseEventArgs e)
        {
            dragBeat = false;
        }
    }
}
