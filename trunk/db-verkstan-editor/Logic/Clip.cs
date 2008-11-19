﻿using System;
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
        public int ChannelNumber
        {
            set
            {
                bindedCoreClip.SetChannel(value);
            }
            get
            {
                return bindedCoreClip.GetChannel();
            }
        }
        private Rectangle dimension;
        public Rectangle Dimension
        {
            get
            {
                return dimension;
            }
            set
            {
                if (!dimension.Equals(value))
                {
                    lastDimension = dimension;
                    dimension = value;
                    SetStartBeatAndBeats(dimension.X, dimension.Width);
                    OnStateChanged();
                }

            }
        }
        private Rectangle lastDimension;
        public Rectangle LastDimension
        {
            get
            {
                return lastDimension;
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
            dimension = new Rectangle(0, 0, 1, 1);
            lastDimension = dimension;
        }
        #endregion

        #region Public Abstract Methods
        public abstract void Dispose();
        #endregion

        #region Public Methods
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
        public void DestroyPreview()
        {
            preview = null;
        }
        #endregion

        #region Private Methods
        private void SetStartBeatAndBeats(int startBeat, int beats)
        {
            if (startBeat < 0)
                startBeat = 0;
            if (beats < 1)
                beats = 1;

            bindedCoreClip.SetStart(startBeat * Metronome.TicksPerBeat);
            bindedCoreClip.SetEnd(startBeat * Metronome.TicksPerBeat + beats * Metronome.TicksPerBeat);
        }
        #endregion

        #region Events
        public delegate void EventHandler(Clip clip);
        public event EventHandler StateChanged;
        protected void OnStateChanged()
        {
            if (StateChanged != null)
                StateChanged(this);
        }
        #endregion 
    }
}
