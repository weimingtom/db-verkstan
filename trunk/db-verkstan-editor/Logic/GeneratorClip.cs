using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    public class GeneratorClip: Clip
    {
        #region Properties
        public override int Id
        {
            get { return bindedCoreClip.Id; }
        }
        #endregion

        #region Private Variables
        private Verkstan.CoreGeneratorClip bindedCoreClip;
        #endregion

        #region Public Methods
        public override void Dispose()
        {
            bindedCoreClip.Dispose();
        }
        public void SetPeriod(int period)
        {
            bindedCoreClip.SetPeriod(period);
        }
        public int GetPeriod()
        {
            return bindedCoreClip.GetPeriod();
        }
        public void SetType(Verkstan.Constants.GeneratorClipTypes type)
        {
            bindedCoreClip.SetType(type);
        }
        public Verkstan.Constants.GeneratorClipTypes GetType()
        {
            return bindedCoreClip.GetType();
        }
        #endregion
    }
}
