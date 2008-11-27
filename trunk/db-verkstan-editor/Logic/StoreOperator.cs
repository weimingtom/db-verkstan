using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace VerkstanEditor.Logic
{
    class StoreOperator: Operator
    {
        #region Properties
        public override Verkstan.CoreOperator BindedCoreOperator
        {
            get 
            {
                if (senders.Count == 0)
                    return null;
                else
                    return senders.First().BindedCoreOperator;
            }
        }
        public override Verkstan.Constants.OperatorTypes Type
        {
            get
            {
                return Verkstan.Constants.OperatorTypes.Unspecified;
            }
        }
        public override bool IsProcessable
        {
            get
            {
                if (senders.Count == 0)
                    return false;
                else
                    return senders.First().IsProcessable;
            }
        }
        public override ICollection<Verkstan.CoreOperatorProperty> Properties
        {
            get
            {
                return new List<Verkstan.CoreOperatorProperty>();
            }
        }
        public override String TypeName
        {
            get
            {
                return "Store";
            }
        }
        #endregion

        #region Constructors
        public StoreOperator()
            :base()
        {
            UniqueName = AllocateUniqueName(TypeName);
        }
        #endregion

        #region Public Methods
        public override void Disposed(Operator op)
        {

        }
        public override List<Verkstan.CoreOperator> GetReceiverCoreOperators()
        {
            return new List<Verkstan.CoreOperator>();
        }
        public override List<Verkstan.CoreOperator> GetSenderCoreOperators()
        {
            return new List<Verkstan.CoreOperator>();
        }
        public override List<Verkstan.CoreOperator> GetSenderCoreOperatorsForLoad()
        {
            List<Verkstan.CoreOperator> result = new List<Verkstan.CoreOperator>();

            foreach (Operator op in senders)
                foreach (Verkstan.CoreOperator coreOp in op.GetSenderCoreOperators())
                    result.Add(coreOp);
           
            return result;
        }
        public override void StackConnectChangedUpwards()
        {
            OnStateChanged();
        }
        public override void CascadeStackConnectChangedDownwards()
        {
            foreach (Operator op in loads)
                op.CascadeStackConnectChangedDownwards();

            OnStateChanged();
        }
        public override XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("operator");
            XmlElement typeElement = doc.CreateElement("type");
            typeElement.InnerText = "Store";
            root.AppendChild(typeElement);
            XmlElement nameElement = doc.CreateElement("name");
            nameElement.InnerText = Name;
            root.AppendChild(nameElement);
            XmlElement xElement = doc.CreateElement("x");
            xElement.InnerText = Left.ToString();
            root.AppendChild(xElement);
            XmlElement yElement = doc.CreateElement("y");
            yElement.InnerText = Top.ToString();
            root.AppendChild(yElement);
            XmlElement widthElement = doc.CreateElement("width");
            widthElement.InnerText = Width.ToString();
            root.AppendChild(widthElement);
            XmlElement heightElement = doc.CreateElement("height");
            heightElement.InnerText = Height.ToString();
            root.AppendChild(heightElement);

            return root;
        }
        public override void FromXmlElement(XmlElement root)
        {

        }
        #endregion
    }
}
