using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    public class Metronome
    {
        #region Properties
        public static int TicksPerBeat
        {
            get
            {
                return 256;
            }
        }
        #endregion

        #region Events
        public delegate void BeatChangedHandler(int beat);
        public static event BeatChangedHandler BeatChangedFastUpdate;
        public static event BeatChangedHandler BeatChangedSlowUpdate;
        public static void OnBeatChangedFastUpdate(int beat)
        {
            if (BeatChangedFastUpdate != null)
                BeatChangedFastUpdate(beat);
        }
        public static void OnBeatChangedSlowUpdate(int beat)
        {
            if (BeatChangedSlowUpdate != null)
                BeatChangedSlowUpdate(beat);
        }
        #endregion
        /*
        public static int Beat
        {
            set
            {
                Verkstan.Metronome.Beat = value;
            }
            get
            {
                return Verkstan.Metronome.Beat;
            }
        }

        public static int Beats
        {
            set
            {
                Verkstan.Metronome.Beats = value;
            }
            get
            {
                return Verkstan.Metronome.Beats;
            }
        }

        public static int BPM
        {
            set
            {
                Verkstan.Metronome.BPM = value;
            }
            get
            {
                return Verkstan.Metronome.BPM;
            }
        }

        public static bool Loop
        {
            set
            {
                Verkstan.Metronome.Loop = value;
            }
            get
            {
                return Verkstan.Metronome.Loop;
            }
        }

        public static int LoopStart
        {
            set
            {
                Verkstan.Metronome.LoopStart = value;
            }
            get
            {
                return Verkstan.Metronome.LoopStart;
            }
        }

        public static int LoopEnd
        {
            set
            {
                Verkstan.Metronome.LoopEnd = value;
            }
            get
            {
                return Verkstan.Metronome.LoopEnd;
            }
        }

        public static int TicksPerBeat
        {
            get
            {
                return Verkstan.Metronome.TicksPerBeat;
            }
        }

        public static int Milliseconds
        {
            get
            {
                return Verkstan.Metronome.Milliseconds;
            }
        }

        public static void Start()
        {
            Verkstan.Metronome.Start();
        }

        public static void Pause()
        {
            Verkstan.Metronome.Pause();
        }
         */
    }
}
