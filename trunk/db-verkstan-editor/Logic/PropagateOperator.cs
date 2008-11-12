using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

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
        public override ICollection<Verkstan.OperatorProperty> Properties
        {
            get
            {
                return new List<Verkstan.OperatorProperty>();
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

            IsWarningPresent = senders.Count != 1;
            OnStateChanged();
        }
        public override System.Xml.XmlElement ToXmlElement(System.Xml.XmlDocument doc)
        {
            return doc.CreateElement("Propagate");
        }
        #endregion
    }
}
