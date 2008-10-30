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
    public partial class Transport : UserControl
    {
        private bool showClockAsBeats = true;
        private int lastBeat;

        public Transport()
        {
            InitializeComponent();
            this.bpm.Value = Verkstan.Timer.BPM;
            this.beatsOrTime.Text = "Beats";
            UpdateClock();
            beatChangedTimer.Start();
        }

        public class BeatChangedEventArgs: EventArgs
        {
            public int Beat;
            public BeatChangedEventArgs(int beat)
            {
                Beat = beat;
            }
        }

        public delegate void BeatChangedHandler(object sender, BeatChangedEventArgs e);
        [Browsable(true)]
        [Description("Event fired when the beat has changed.")]
        [Editor(typeof(BeatChangedHandler), typeof(UITypeEditor))]
        public event BeatChangedHandler BeatChanged;

        public void OnBeatChanged(object sender, BeatChangedEventArgs e)
        {
            if (BeatChanged != null)
                BeatChanged(sender, e);
        }

        private void UpdateClock()
        {
            if (showClockAsBeats)
            {
                this.time.Text = String.Format("{0:0000.00}", Verkstan.Timer.GetBeat() / (float)Verkstan.Timer.GetTicksPerBeat() + 1);
            }
            else
            {
                TimeSpan ts = TimeSpan.FromMilliseconds(Verkstan.Timer.GetMilliseconds());
                this.time.Text = String.Format("{0:00}:{1:00}:{2:00}", (int)ts.TotalMinutes, ts.Seconds, ts.Milliseconds % 60);
            }
        }

        private void play_Click(object sender, EventArgs e)
        {
            Verkstan.Timer.Start();
            clock.Start();
        }

        private void stop_Click(object sender, EventArgs e)
        {
            Verkstan.Timer.Pause();
            Verkstan.Timer.SetBeat(0);
            clock.Stop();
            UpdateClock();
        }

        private void start_Click(object sender, EventArgs e)
        {
            Verkstan.Timer.SetBeat(0);
            UpdateClock();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            UpdateClock();
        }

        private void pause_Click(object sender, EventArgs e)
        {
            Verkstan.Timer.Pause();
        }

        private void bpm_ValueChanged(object sender, EventArgs e)
        {
            Verkstan.Timer.BPM = Convert.ToInt32(this.bpm.Value);
        }

        private void beatsOrTime_SelectedValueChanged(object sender, EventArgs e)
        {
            showClockAsBeats = (String)beatsOrTime.SelectedItem == "Beats";
            UpdateClock();

            int clockX = Size.Width / 2 - this.time.Size.Width / 2;
            this.time.Location = new Point(clockX, this.time.Location.Y);  
        }

        private void Transport_Resize(object sender, EventArgs e)
        {
            int clockX = Size.Width / 2 - this.time.Size.Width / 2;
            this.time.Location = new Point(clockX, this.time.Location.Y);

            int bpmX = Size.Width - this.bpm.Width - 3;
            this.bpm.Location = new Point(bpmX, this.bpm.Location.Y);

            int bpmLabelX = Size.Width - this.bpm.Width - this.label1.Size.Width - 3;
            this.label1.Location = new Point(bpmLabelX, this.label1.Location.Y);

            int beatsOrTimeLabelX = Size.Width - this.beatsOrTime.Width - this.label2.Size.Width - 3;
            this.label2.Location = new Point(beatsOrTimeLabelX, this.label2.Location.Y);

            int beatsOrTimeX = Size.Width - this.beatsOrTime.Width - 3;
            this.beatsOrTime.Location = new Point(beatsOrTimeX, this.beatsOrTime.Location.Y);
        }

        private void beatChangedTimer_Tick(object sender, EventArgs e)
        {
            int beat = Verkstan.Timer.GetBeat();

            if (beat != lastBeat)
            {
                OnBeatChanged(this, new BeatChangedEventArgs(beat));
            }

            lastBeat = beat;
        }
    }
}
