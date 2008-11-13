using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    public class OperatorFactory
    {
        #region Static Methods
        public static Operator Create(String typeName)
        {
            Operator op = null;
            if (typeName == "Store")
            {
                op = new StoreOperator();
            }
            else if (typeName == "Load")
            {
                op = new LoadOperator();
            }
            else if (typeName == "Propagate")
            {
                op = new PropagateOperator();
            }
            else if (typeName == "Scene")
            {
                Verkstan.CoreOperator coreOp = Verkstan.CoreOperatorFactory.Create(typeName);
                op = new CoreOperator(coreOp);
                op.Timeline = new Timeline(op);
                Channel channel1 = new Channel();
                GeneratorClip clip1 = new GeneratorClip();
                clip1.StartBeat = 2;
                clip1.Beats = 10;
                clip1.SetPeriodInBeats(2);
                clip1.SetGeneratorType(Verkstan.Constants.GeneratorClipTypes.Sine);
                
                channel1.AddClip(clip1);
                op.Timeline.AddChannel(channel1);

                Channel channel2 = new Channel();
                GeneratorClip clip2 = new GeneratorClip();
                clip2.StartBeat = 0;
                clip2.Beats = 20;
                clip2.SetPeriodInBeats(2);
                clip2.SetGeneratorType(Verkstan.Constants.GeneratorClipTypes.SawTooth);
                channel2.AddClip(clip2);
                op.Timeline.AddChannel(channel2);

                Channel channel3 = new Channel();
                GeneratorClip clip3 = new GeneratorClip();
                clip3.StartBeat = 0;
                clip3.Beats = 20;
                clip3.SetPeriodInBeats(1);
                clip3.SetGeneratorType(Verkstan.Constants.GeneratorClipTypes.RampUp);
                channel3.AddClip(clip3);
                op.Timeline.AddChannel(channel3);

                Channel channel4 = new Channel();
                GeneratorClip clip4 = new GeneratorClip();
                clip4.StartBeat = 0;
                clip4.Beats = 40;
                clip4.SetPeriodInTicks(Metronome.TicksPerBeat / 2);
                clip4.SetGeneratorType(Verkstan.Constants.GeneratorClipTypes.Sine);
                channel4.AddClip(clip4);
                op.Timeline.AddChannel(channel4);
            }
            else
            {
                Verkstan.CoreOperator coreOp = Verkstan.CoreOperatorFactory.Create(typeName);
                op = new CoreOperator(coreOp);
            }

            return op;
        }
        public static ICollection<String> GetCategories()
        {
            return Verkstan.CoreOperatorFactory.GetCategories().ToList<String>();
        }
        public static ICollection<String> GetNamesInCategory(String category)
        {
            return Verkstan.CoreOperatorFactory.GetNamesInCategory(category).ToList<String>();
        }
        #endregion
    }
}
