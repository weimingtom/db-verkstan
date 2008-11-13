using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    public class Timeline
    {
        #region Properties
        private List<Channel> channels;
        public ICollection<Channel> Channels
        {
            get
            {
                return channels;
            }
        }
        public String Name
        {
            get
            {
                return operatorParent.Name;
            }
        }
        #endregion

        #region Private Variables
        private Clip selectedClip;
        private Operator operatorParent;
        private Channel.EventHandler addedHandler;
        private Channel.EventHandler removedHandler;
        private Channel.EventHandler clipStateChangedHandler;
        private Channel.EventHandler channelStateChangedHandler;
        #endregion

        #region Constructors
        public Timeline(Operator operatorParent)
        {
            this.operatorParent = operatorParent;
            channels = new List<Channel>();
            addedHandler = new Channel.EventHandler(this.channel_Added);
            removedHandler = new Channel.EventHandler(this.channel_Removed);
            clipStateChangedHandler = new Channel.EventHandler(this.channel_ClipStateChanged);
            channelStateChangedHandler = new Channel.EventHandler(this.channel_StateChanged);
        }
        #endregion

        #region Public Methods
        public void SelectAt(int channelIndex, int beat)
        {
            Clip clip = channels[channelIndex].GetAt(beat);

            if (clip != selectedClip)
            {
                if (selectedClip != null)
                    selectedClip.IsSelected = false;
                clip.IsSelected = true;
                selectedClip = clip;
            }
        }
        public void Deselect()
        {
            if (selectedClip != null)
            {
                selectedClip.IsSelected = false;
                selectedClip = null;
            }
        }
        public Clip GetAt(int channelIndex, int beat)
        {
            return channels[channelIndex].GetAt(beat);
        }
        public int GetBeats()
        {
            int beats = 0;
            foreach (Channel channel in channels)
                if (channel.GetBeats() > beats)
                    beats = channel.GetBeats();
            return beats;
        }
        public void AddChannel(Channel channel)
        {
            channel.Index = channels.Count;
            channels.Add(channel);
            OnChannelAdded(channel);
            channel.Added += addedHandler;
            channel.Removed += removedHandler;
            channel.ClipStateChanged += clipStateChangedHandler;
            channel.StateChanged += channelStateChangedHandler;
        }
        public void RemoveChannel(Channel channel)
        {
            channels.Remove(channel);
            OnChannelRemoved(channel);
            int i = 0;
            foreach (Channel c in channels)
            {
                c.Index = i;
                i++;
            }
            channel.Added -= addedHandler;
            channel.Removed -= removedHandler;
            channel.ClipStateChanged -= clipStateChangedHandler;
            channel.StateChanged -= channelStateChangedHandler;
        }
        #endregion

        #region Private Methods
        private void UpdateCoreClips()
        {

        }
        #endregion

        #region Events
        public delegate void EventHandler(Channel channel, Clip clip);
        public event EventHandler ClipStateChanged;
        protected void OnClipStateChanged(Channel channel, Clip clip)
        {
            if (ClipStateChanged != null)
                ClipStateChanged(channel, clip);
        }
        public event EventHandler ChannelStateChanged;
        protected void OnChannelStateChanged(Channel channel)
        {
            if (ChannelStateChanged != null)
                ChannelStateChanged(channel, null);
        }
        public event EventHandler ChannelAdded;
        protected void OnChannelAdded(Channel channel)
        {
            if (ChannelAdded != null)
                ChannelAdded(channel, null);
        }
        public event EventHandler ChannelRemoved;
        protected void OnChannelRemoved(Channel channel)
        {
            if (ChannelRemoved != null)
                ChannelRemoved(channel, null);
        }
        public event EventHandler ClipAdded;
        protected void OnClipAdded(Channel channel, Clip clip)
        {
            if (ClipAdded != null)
                ClipAdded(channel, clip);
        }
        public event EventHandler ClipRemoved;
        protected void OnClipRemoved(Channel channel, Clip clip)
        {
            if (ClipRemoved != null)
                ClipRemoved(channel, clip);
        }
        #endregion 

        #region Event Handlers
        private void channel_StateChanged(Channel channel, Clip clip)
        {
            OnChannelStateChanged(channel);
        }
        private void channel_ClipStateChanged(Channel channel, Clip clip)
        {
            OnClipStateChanged(channel, clip);
        }
        private void channel_Added(Channel channel, Clip clip)
        {
            OnClipAdded(channel, clip);
        }
        private void channel_Removed(Channel channel, Clip clip)
        {
            OnClipRemoved(channel, clip);
        }
        #endregion
    }
}
