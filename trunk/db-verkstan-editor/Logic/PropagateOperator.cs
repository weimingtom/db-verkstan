using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace VerkstanEditor.Logic
{
    class PropagateOperator: Operator
    {
        #region Properties
        public override Verkstan.CoreOperator BindedCoreOperator
        {
            get 
            {
                List<Verkstan.CoreOperator> senderCores = GetSenderCoreOperators();
                if (senderCores.Count == 0)
                    return null;
                else
                    return senderCores.First();
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
                return "Propagate";
            }
        }
        #endregion

        #region Constructors
        public PropagateOperator()
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
            List<Verkstan.CoreOperator> result = new List<Verkstan.CoreOperator>();
            foreach (Operator op in receivers)
                foreach (Verkstan.CoreOperator coreOp in op.GetReceiverCoreOperators())
                    result.Add(coreOp);

            return result;
        }
        public override List<Verkstan.CoreOperator> GetSenderCoreOperators()
        {
            List<Verkstan.CoreOperator> result = new List<Verkstan.CoreOperator>();
            foreach (Operator op in senders)
                foreach (Verkstan.CoreOperator coreOp in op.GetSenderCoreOperators())
                    result.Add(coreOp);

            return result;
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
            foreach (Operator op in senders)
                op.StackConnectChangedUpwards();

            OnStateChanged();
        }
        public override void CascadeStackConnectChangedDownwards()
        {
            foreach (Operator op in receivers)
                op.CascadeStackConnectChangedDownwards();

            foreach (Operator op in loads)
                op.CascadeStackConnectChangedDownwards();

            IsWarningPresent = senders.Count != 1;
            OnStateChanged();
        }
        public override XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("operator");
            XmlElement typeElement = doc.CreateElement("type");
            typeElement.InnerText = "Propagate";
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
        #endregion
    }
}
