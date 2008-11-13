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
            get { return -1; }
        }
        #endregion

        #region Private Variables
        private Verkstan.CoreSplineClip bindedSplineCoreClip;
        #endregion

        #region Constructors
        public SplineClip()
        {

        }
        #endregion

        #region Public Methods
        public override void Dispose()
        {

        }
        #endregion

        #region Private Methods
        private void UpdateCoreClip()
        {

        }
        #endregion
    }
}
