﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace VerkstanEditor.Logic
{
    class ExportOperator: Operator
    {
        #region Properties
        public override Verkstan.OperatorBinding BindedOperator
        {
            get
            {
                if (senders.Count == 0)
                    return null;
                else
                    return senders.First().BindedOperator;
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
                if (senders.Count != 1)
                    return false;
                else
                    return senders.First().IsProcessable;
            }
        }
        public override ICollection<Verkstan.OperatorBindingProperty> Properties
        {
            get
            {
                return new List<Verkstan.OperatorBindingProperty>();
            }
        }
        public override String TypeName
        {
            get
            {
                return "Export";
            }
        }
        public override String DisplayName
        {
            get
            {
                return UniqueName;
            }
        }
        #endregion

        #region Constructors
        public ExportOperator()
            : base()
        {
            UniqueName = AllocateUniqueName(TypeName);
        }
        #endregion

        #region Public Methods
        public override List<Operator> GetInputs()
        {
            if (senders.Count == 0)
                return new List<Operator>();
            else
                return senders.First().GetInputs();
        }
        public override void OnDisposed(Operator op)
        {

        }
        public override List<Operator> GetReceiverOperators()
        {
            List<Operator> result = new List<Operator>();
            foreach (Operator receiver in loads)
                foreach (Operator receiverReceiver in receiver.GetReceiverOperators())
                    result.Add(receiverReceiver);

            return result;
        }
        public override List<Operator> GetSenderOperators()
        {
            return new List<Operator>();
        }
        public override List<Operator> GetSenderOperatorsForLoad()
        {
            List<Operator> result = new List<Operator>();

            foreach (Operator sender in senders)
                foreach (Operator senderSender in sender.GetSenderOperators())
                    result.Add(senderSender);
           
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
            root.SetAttribute("type", "Export");

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
