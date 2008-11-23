using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

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
        public override System.Xml.XmlElement ToXmlElement(System.Xml.XmlDocument doc)
        {
            return doc.CreateElement("Store");
        }
        #endregion
    }
}
