using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    public class ClipFactory
    {
        public static Clip Create(String type)
        {
            if (type == "Generator")
            {
                return new GeneratorClip();
            }
            if (type == "Spline")
            {
                return new SplineClip();
            }

            return null;
        }
    }
}
