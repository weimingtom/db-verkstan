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
