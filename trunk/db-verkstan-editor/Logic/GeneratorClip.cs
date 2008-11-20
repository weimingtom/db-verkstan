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
            SetGeneratorType(0);
            SetPeriodInBeats(1);
            SetBindedCoreClip(bindedCoreGeneratorClip);
        }
        #endregion

        #region Public Methods
        public void SetGeneratorType(int type)
        {
            bindedCoreGeneratorClip.SetGeneratorType(type);
            DestroyPreview();
            OnStateChanged();
        }
        public int GetGeneratorType()
        {
            return bindedCoreGeneratorClip.GetGeneratorType();
        }
        public override void Dispose()
        {
            bindedCoreGeneratorClip.Dispose();
        }
        public void SetPeriodInTicks(int period)
        {
            bindedCoreGeneratorClip.SetPeriod(period);
            DestroyPreview();
            OnStateChanged();
        }
        public void SetPeriodInBeats(int period)
        {
            bindedCoreGeneratorClip.SetPeriod(period * Metronome.TicksPerBeat);
            DestroyPreview();
            OnStateChanged();
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
