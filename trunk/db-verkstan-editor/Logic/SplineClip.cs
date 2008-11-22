using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace VerkstanEditor.Logic
{
    public class SplineClip: Clip
    {
        #region Properties
        public override int Id
        {
            get { return bindedSplineCoreClip.Id; }
        }
        public ICollection<SplineControlPoint> ControlPoints
        {
            get
            {
                return controlPoints;
            }
        }
        #endregion

        #region Private Variables
        private Verkstan.CoreSplineClip bindedSplineCoreClip;
        private List<SplineControlPoint> controlPoints;
        #endregion

        #region Constructors
        public SplineClip()
        {
            bindedSplineCoreClip = new Verkstan.CoreSplineClip();
            SetBindedCoreClip(bindedSplineCoreClip);
            controlPoints = new List<SplineControlPoint>();
        }
        #endregion

        #region Public Methods
        public override void Dispose()
        {
            bindedSplineCoreClip.Dispose();
        }
        public void Add(SplineControlPoint point, int x, float y)
        {
            point.X = x;
            point.Y = y;
            controlPoints.Add(point);
            UpdateCoreClip();
        }
        public void RemoveSelected()
        {

        }
        public SplineControlPoint GetAt(Point point)
        {
            return null;
        }
        public void Select(SplineControlPoint point)
        {

        }
        public void DeselectAll()
        {

        }
        #endregion

        #region Private Methods
        private void SortControlPoints()
        {

        }
        private void UpdateCoreClip()
        {
            for(int i = 0; i < controlPoints.Count; i++)
                bindedSplineCoreClip.SetControlPoint(i, controlPoints[i].X, controlPoints[i].Y);

            bindedSplineCoreClip.SetNumberOfControlPoints(controlPoints.Count);
        }
        #endregion
    }
}
