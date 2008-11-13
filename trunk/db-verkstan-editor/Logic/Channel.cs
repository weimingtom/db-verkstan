using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    public class Channel
    {
        #region Properties
        private List<Clip> clips;
        public ICollection<Clip> Clips
        {
            get
            {
                return clips;
            }
        }
        private int index;
        public int Index
        {
            set
            {
                if (index != value)
                {
                    index = value;
                    foreach (Clip clip in clips)
                        clip.ChannelIndex = value;
                    OnStateChanged();
                }
            }
            get
            {
                return index;
            }
        }
        #endregion

        #region Private Variables
        Clip.EventHandler stateChangedHandler;
        #endregion

        #region Constructors
        public Channel()
        {
            clips = new List<Clip>();
            stateChangedHandler = new Clip.EventHandler(this.clip_StateChanged);
        }
        #endregion

        #region Public Methods
        public Clip GetAt(int beat)
        {
            foreach (Clip clip in clips)
                if (clip.StartBeat <= beat && (clip.StartBeat + clip.Beats) > beat)
                    return clip;
            return null;
        }
        public int GetBeats()
        {
            int beats = 0;
            foreach (Clip clip in clips)
                if (clip.StartBeat + clip.Beats > beats)
                    beats = clip.StartBeat + clip.Beats;
            return beats;
        }
        public void AddClip(Clip clip)
        {
            clips.Add(clip);
            clip.StateChanged += stateChangedHandler;
            clip.ChannelIndex = index;
        }
        public void RemoveCip(Clip clip)
        {
            clips.Remove(clip);
            clip.StateChanged -= stateChangedHandler;
        }
        #endregion

        #region Events
        public delegate void EventHandler(Channel channel, Clip clip);
        public event EventHandler Added;
        protected void OnAdded(Clip clip)
        {
            if (Added != null)
                Added(this, clip);
        }
        public event EventHandler Removed;
        protected void OnRemoved(Clip clip)
        {
            if (Removed != null)
                Removed(this, clip);
        }
        public event EventHandler ClipStateChanged;
        protected void OnClipStateChanged(Clip clip)
        {
            if (ClipStateChanged != null)
                ClipStateChanged(this, clip);
        }
        public event EventHandler StateChanged;
        protected void OnStateChanged()
        {
            if (StateChanged != null)
                StateChanged(this, null);
        }
        #endregion 

        #region Event Handlers
        public void clip_StateChanged(Clip.EventArgs e)
        {
            OnClipStateChanged(e.Clip);
        }
        #endregion
    }
}
