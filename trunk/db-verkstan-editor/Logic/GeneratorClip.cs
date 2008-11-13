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
            get { return bindedCoreGeneratorClip.Id; }
        }
        #endregion

        #region Private Variables
        private Verkstan.CoreGeneratorClip bindedCoreGeneratorClip;
        #endregion

        #region Constructors
        public GeneratorClip()
        {
            bindedCoreGeneratorClip = new Verkstan.CoreGeneratorClip();
            SetBindedCoreClip(bindedCoreGeneratorClip);
        }
        #endregion

        #region Public Methods
        public void SetGeneratorType(Verkstan.Constants.GeneratorClipTypes type)
        {
            bindedCoreGeneratorClip.SetType(type);
        }
        public Verkstan.Constants.GeneratorClipTypes GetGeneratorType()
        {
            return bindedCoreGeneratorClip.GetType();
        }
        public override void Dispose()
        {
            bindedCoreGeneratorClip.Dispose();
        }
        public void SetPeriodInTicks(int period)
        {
            bindedCoreGeneratorClip.SetPeriod(period);
        }
        public void SetPeriodInBeats(int period)
        {
            bindedCoreGeneratorClip.SetPeriod(period * Metronome.TicksPerBeat);
        }
        public int GetPeriodInTicks()
        {
            return bindedCoreGeneratorClip.GetPeriod();
        }
        public int GetPeriodInBeats()
        {
            return bindedCoreGeneratorClip.GetPeriod() / Metronome.TicksPerBeat;
        }
        #endregion
    }
}
