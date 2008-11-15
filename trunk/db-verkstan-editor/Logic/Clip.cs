using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace VerkstanEditor.Logic
{
    public abstract class Clip: IDisposable
    {
        #region Properties
        public abstract int Id { get; }
        public int Beats
        {
            get
            {
                return (bindedCoreClip.GetEnd() - bindedCoreClip.GetStart()) / Metronome.TicksPerBeat;
            }
            set
            {
                int currentStartBeat = StartBeat;
                int currentBeats = (bindedCoreClip.GetEnd() - bindedCoreClip.GetStart()) / Metronome.TicksPerBeat;
               
                if (value < 1)
                    value = 1;

                if (currentBeats != value)
                {
                    lastBeats = value;
                    int start = bindedCoreClip.GetStart();
                    bindedCoreClip.SetEnd(start + value * Metronome.TicksPerBeat);
                    StartBeat = currentStartBeat;
                }
            }
        }
        private int lastBeats;
        public int LastBeats
        {
            get
            {
                return lastBeats;
            }
        }
        public int StartBeat
        {
            get
            {
                return bindedCoreClip.GetStart() / Metronome.TicksPerBeat;
            }
            set
            {
                int currentBeats = Beats;
                int currrentStartBeat = bindedCoreClip.GetStart() / Metronome.TicksPerBeat;

                if (value < 0)
                    value = 0;

                if (currrentStartBeat != value)
                {
                    lastStartBeat = value;
                    bindedCoreClip.SetStart(value * Metronome.TicksPerBeat);
                    Beats = currentBeats;
                }
            }
        }
        private int lastStartBeat;
        public int LastStartBeat
        {
            get
            {
                return lastStartBeat;
            }
        }
        private bool selected = false;
        public bool Selected
        {
            get
            {
                return selected;
            }
            set
            {
                if (selected != value)
                {
                    selected = value;
                    OnStateChanged();
                }
            }
        }
        private int lastChannelIndex;
        public int LastChannelIndex
        {
            get
            {
                return lastChannelIndex;
            }
        }
        private int channelIndex;
        public int ChannelIndex
        {
            set
            {
                if (channelIndex != value)
                {
                    lastChannelIndex = channelIndex;
                    channelIndex = value;
                }
            }
            get
            {
                return channelIndex;
            }
        }
        private bool isSelected = false;
        public bool IsSelected
        {
            get
            {
                return isSelected;
            }
            set
            {
                if (isSelected != value)
                {
                    isSelected = value;
                    OnStateChanged();
                }
            }
        }
        #endregion

        #region Private Variables
        private Verkstan.CoreClip bindedCoreClip;
        private Bitmap preview;
        #endregion

        #region Constructors
        public Clip()
        {

        }
        #endregion

        #region Public Abstract Methods
        public abstract void Dispose();
        #endregion

        #region Public Methods
        public Rectangle GetDimension()
        {
            return new Rectangle(StartBeat, ChannelIndex, Beats, 1);
        }
        public Rectangle GetLastDimension()
        {
            return new Rectangle(LastStartBeat, LastChannelIndex, LastBeats, 1);
        }
        public Bitmap GetPreview(int width, int height, Color color)
        {
            if (preview != null && preview.Width == width && preview.Height == height)
                return preview;

            if (preview != null)
                preview.Dispose();

            preview = new Bitmap(width, height);
            Graphics g = Graphics.FromImage(preview);
            int ticks = bindedCoreClip.GetEnd() - bindedCoreClip.GetStart();
            int middle = height / 2 - 1;

            float v = bindedCoreClip.GetValue(0);
            int lastX = 0;
            int lastY = (int)(middle - v * middle);
            Pen p = new Pen(color);
            for (int x = 1; x < width; x++)
            {
                int beat = (int)((x / (float)width) * ticks);
                float value = bindedCoreClip.GetValue(beat);
                int y = (int)(middle - value * middle);
                g.DrawLine(p, lastX, lastY, x, y);
                lastX = x;
                lastY = y;
            }
            p.Dispose();

            return preview;
        }
        #endregion

        #region Protected Methods
        public void SetBindedCoreClip(Verkstan.CoreClip bindedCoreClip)
        {
            this.bindedCoreClip = bindedCoreClip;
        }
        #endregion

        #region Events
        public class EventArgs : System.EventArgs
        {
            public readonly Clip Clip;
            public EventArgs(Clip clip)
            {
                Clip = clip;
            }
        }
        public delegate void EventHandler(EventArgs e);
        public event EventHandler StateChanged;
        protected void OnStateChanged()
        {
            if (StateChanged != null)
                StateChanged(new Clip.EventArgs(this));
        }
        #endregion 
    }
}
