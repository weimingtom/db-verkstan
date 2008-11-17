using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    public class SplineClip: Clip
    {
        #region Properties
        public override int Id
        {
            get { return bindedSplineCoreClip.Id; }
        }
        #endregion

        #region Private Variables
        private Verkstan.CoreSplineClip bindedSplineCoreClip;
        #endregion

        #region Constructors
        public SplineClip()
        {
            bindedSplineCoreClip = new Verkstan.CoreSplineClip();
            SetBindedCoreClip(bindedSplineCoreClip);
        }
        #endregion

        #region Public Methods
        public override void Dispose()
        {
            bindedSplineCoreClip.Dispose();
        }
        #endregion
    }
}
