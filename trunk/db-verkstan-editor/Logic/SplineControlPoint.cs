using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    public class SplineControlPoint
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
                y = value;
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
                x = value;
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
                }
            }
        }
        #endregion
    }
}
