using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

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
                op.Timeline.AddChannel(channel1);
                Channel channel2 = new Channel();
                op.Timeline.AddChannel(channel2);
                Channel channel3 = new Channel();
                op.Timeline.AddChannel(channel3);
                Channel channel4 = new Channel();
                op.Timeline.AddChannel(channel4);

                GeneratorClip clip1 = new GeneratorClip();
                clip1.SetPeriodInBeats(2);
                clip1.SetGeneratorType(Verkstan.Constants.GeneratorClipTypes.Sine);
                op.Timeline.AddClip(clip1, new Point(0, 0), 10);
                GeneratorClip clip2 = new GeneratorClip();
                clip2.SetPeriodInBeats(2);
                clip2.SetGeneratorType(Verkstan.Constants.GeneratorClipTypes.SawTooth);
                op.Timeline.AddClip(clip2, new Point(0, 1), 20);
                GeneratorClip clip3 = new GeneratorClip();
                clip3.SetPeriodInBeats(1);
                clip3.SetGeneratorType(Verkstan.Constants.GeneratorClipTypes.RampUp);
                op.Timeline.AddClip(clip3, new Point(0, 2), 20);
                GeneratorClip clip4 = new GeneratorClip();
                clip4.SetPeriodInTicks(Metronome.TicksPerBeat / 2);
                clip4.SetGeneratorType(Verkstan.Constants.GeneratorClipTypes.Sine);
                op.Timeline.AddClip(clip4, new Point(0, 3), 40);
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
