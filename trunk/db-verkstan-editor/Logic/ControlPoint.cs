using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    public class ControlPoint
    {
        #region Properties
        private float y;
        public float Y
        {
            get
            {
                return y;
            }
            set
            {
                if (y != value)
                {
                    lastY = y;
                    y = value;
                }
            }
        }
        private float lastY;
        public float LastY
        {
            get
            {
                return lastY;
            }
        }
        private int x;
        public int X
        {
            get
            {
                return x;
            }
            set
            {
                if (x != value)
                {
                    lastX = x;
                    x = value;
                }
            }
        }
        private int lastX;
        public int LastX
        {
            get
            {
                return lastX;
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

        #region Events
        public class EventArgs : System.EventArgs
        {
            public readonly ControlPoint ControlPoint;
            public EventArgs(ControlPoint controlPoint)
            {
                ControlPoint = controlPoint;
            }
        }
        public delegate void EventHandler(ControlPoint.EventArgs e);
        public event EventHandler StateChanged;
        protected void OnStateChanged()
        {
            if (StateChanged != null)
                StateChanged(new ControlPoint.EventArgs(this));
        }
        #endregion
    }
}
