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
            else if (typeName == "Timeline")
            {
                Verkstan.CoreOperator coreOp = Verkstan.CoreOperatorFactory.Create(typeName);
                op = new CoreOperator(coreOp);
                op.Timeline = new Timeline(op);

                /*
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
                clip1.SetGeneratorType(0);
                op.Timeline.AddClip(clip1, new Point(0, 0), 10);
                SplineClip clip2 = new SplineClip();
                clip2.Add(new ControlPoint(), 256, 0.5f);
                clip2.Add(new ControlPoint(), 256*2, 0.2f);
                clip2.Add(new ControlPoint(), 256*2+128, -0.7f);
                clip2.Add(new ControlPoint(), 256 * 4 + 128, 0.7f);
                clip2.Add(new ControlPoint(), 256 * 6 + 128, 0.1f);
                op.Timeline.AddClip(clip2, new Point(0, 1), 20);
                GeneratorClip clip3 = new GeneratorClip();
                clip3.SetPeriodInBeats(1);
                clip3.SetGeneratorType(2);
                op.Timeline.AddClip(clip3, new Point(0, 2), 20);
                GeneratorClip clip4 = new GeneratorClip();
                clip4.SetPeriodInTicks(Metronome.TicksPerBeat / 2);
                clip4.SetGeneratorType(1);
                op.Timeline.AddClip(clip4, new Point(0, 3), 40);
                 */
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
