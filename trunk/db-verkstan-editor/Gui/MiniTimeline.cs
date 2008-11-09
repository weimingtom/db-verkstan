using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using VerkstanEditor.Logic;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class MiniTimeline : UserControl
    {
        private bool dragBeat = false;
        private int beat;

        public MiniTimeline()
        {
            InitializeComponent();
            DoubleBuffered = true;
            Metronome.BeatChangedSlowUpdate += new Metronome.BeatChangedHandler(this.MiniTimeline_BeatChangedSlowUpdate);
        }

        public void MiniTimeline_BeatChangedSlowUpdate(int beat)
        {
            this.beat = beat;
            Refresh();
        }

        private void MiniTimeline_Paint(object sender, PaintEventArgs e)
        {
            /*
            Pen p = new Pen(ForeColor, 1);
            float beatPosition = this.beat / (float)Metronome.Beats; 
            int beatInPixels = (int)((Size.Width - 1) * beatPosition);
            e.Graphics.DrawLine(p, new Point(beatInPixels, 0), new Point(beatInPixels, Size.Height));
            p.Dispose();
             */
        }

        private void MiniTimeline_MouseDown(object sender, MouseEventArgs e)
        {
            /*
            if (e.Button != MouseButtons.Left)
                return;

            float beatPosition = e.X / (float)(Size.Width - 1);
            Metronome.Beat = (int)(Metronome.Beats * beatPosition);

            dragBeat = true;
             */
        }

        private void MiniTimeline_MouseMove(object sender, MouseEventArgs e)
        {
            /*
            if (!dragBeat)
                return;

            float beatPosition = e.X / (float)(Size.Width - 1);
            Metronome.Beat = (int)(Metronome.Beats * beatPosition);
             */
        }

        private void MiniTimeline_MouseUp(object sender, MouseEventArgs e)
        {
            dragBeat = false;
        }
    }
}
