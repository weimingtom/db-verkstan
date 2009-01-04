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
        public override List<Operator> GetInputs()
        {
            throw new NotImplementedException();
        }
        public override void OnDisposed(Operator op)
        {

        }
        public override List<Operator> GetReceiverOperators()
        {
            return new List<Operator>();
        }
        public override List<Operator> GetSenderOperators()
        {
            return new List<Operator>();
        }
        public override List<Operator> GetSenderOperatorsForLoad()
        {
            List<Operator> result = new List<Operator>();

            foreach (Operator op in senders)
                foreach (Operator opp in op.GetSenderOperators())
                    result.Add(opp);
           
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
            root.SetAttribute("type", "Store");

            PopulateXmlElementWithBasicOperatorInformation(root, doc);

            return root;
        }
        public override void FromXmlElement(XmlElement root)
        {
            PopulateOperatorWithBasicXmlElementInformation(root);
        }
        #endregion
    }
}
