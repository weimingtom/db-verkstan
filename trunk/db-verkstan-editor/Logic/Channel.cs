using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Xml;

namespace VerkstanEditor.Logic
{
    public class Channel: IDisposable
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
        private int channelNumber;
        public int ChannelNumber
        {
            set
            {
                if (channelNumber != value)
                {
                    channelNumber = value;
                    foreach (Clip clip in clips)
                        clip.ChannelNumber = value;
                    
                    OnStateChanged();
                }
            }
            get
            {
                return channelNumber;
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
        private int y;
        public int Y
        {
            set
            {
                if (y != value)
                {
                    y = value;
                    foreach (Clip clip in clips)
                        clip.Dimension = new Rectangle(clip.Dimension.X, value, clip.Dimension.Width, clip.Dimension.Height);
                }
            }
            get
            {
                return y;
            }
        }
        #endregion

        #region Constructors
        public Channel()
        {
            clips = new List<Clip>();
        }
        #endregion

        #region Public Methods
        public void Dispose()
        {
            foreach (Clip clip in clips)
                clip.Dispose();
        }
        public int GetBeats()
        {
            int beats = 0;
            foreach (Clip clip in clips)
            {
                Rectangle dim = clip.Dimension;
                if (dim.X + dim.Width > beats)
                    beats = dim.X + dim.Width;
            }
            return beats;
        }
        public void AddClip(Clip clip)
        {
            clips.Add(clip);
            clip.ChannelNumber = channelNumber;
        }
        public void RemoveCip(Clip clip)
        {
            clips.Remove(clip);
        }
        public XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("channel");
            XmlElement channelNumber = doc.CreateElement("channelnumber");
            channelNumber.InnerText = ChannelNumber.ToString();
            root.AppendChild(channelNumber);

            foreach (Clip clip in clips)
            {
                XmlElement clipElement = clip.ToXmlElement(doc);
                root.AppendChild(clipElement);
            }
            return root;
        }
        #endregion

        #region Events
        public delegate void EventHandler(Channel channel);
        public event EventHandler StateChanged;
        protected void OnStateChanged()
        {
            if (StateChanged != null)
                StateChanged(this);
        }
        #endregion 
    }
}
