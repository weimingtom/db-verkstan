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
            typeName = typeName.ToLower();

            Operator op = null;
            if (typeName == "store")
            {
                op = new StoreOperator();
            }
            else if (typeName == "load")
            {
                op = new LoadOperator();
            }
            else if (typeName == "propagate")
            {
                op = new PropagateOperator();
            }
            else
            {
                Verkstan.OperatorBinding opBinding = Verkstan.OperatorBindingFactory.Create(typeName);
                op = new CoreOperator(opBinding);
            }

            return op;
        }
        public static ICollection<String> GetCategories()
        {
            return Verkstan.OperatorBindingFactory.GetCategories().ToList<String>();
        }
        public static ICollection<String> GetNamesInCategory(String category)
        {
            return Verkstan.OperatorBindingFactory.GetNamesInCategory(category).ToList<String>();
        }
        #endregion
    }
}
