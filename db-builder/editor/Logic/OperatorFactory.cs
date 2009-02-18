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
            else if (typeName == "export")
            {
                op = new ExportOperator();
            }
            else
            {
                Verkstan.OperatorBinding opBinding = Verkstan.OperatorBindingFactory.Create(typeName);
                if (opBinding == null)
                    throw new Exception("Unable to find an operator with name '" + typeName + "'");
                op = new CoreOperator(opBinding);
            }

            return op;
        }
        public static ICollection<String> GetCategories()
        {
            List<String> categories = Verkstan.OperatorBindingFactory.GetCategories().ToList<String>();

            if (!categories.Contains("Misc"))
                categories.Add("Misc");
            return categories;
        }
        public static ICollection<String> GetNamesInCategory(String category)
        {
            if (category == "Misc")
            {
                List<String> names = new List<string>();
                names.Add("Store");
                names.Add("Load");
                names.Add("Propagate");
                names.Add("Export");
                return names;
            }

            return Verkstan.OperatorBindingFactory.GetNamesInCategory(category).ToList<String>();
        }
        #endregion
    }
}
