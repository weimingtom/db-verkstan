using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    class NoOperator: Operator
    {
        #region Properties
        public override Verkstan.Constants.OperatorTypes Type
        {
            get { return Verkstan.Constants.OperatorTypes.Unspecified; }
        }
        private OperatorJoint primaryJoint;
        public override OperatorJoint PrimaryJoint
        {
            get { return primaryJoint; }
        }
        public override Verkstan.CoreOperator BindedCoreOperator
        {
            get 
            { 
                if (primaryJoint.Sender != null)
                    return primaryJoint.Sender.BindedCoreOperator;
                return null;
            }
        }
        public override bool IsProcessable
        {
            get
            {
                return PrimaryJoint.Sender != null && PrimaryJoint.Sender.IsProcessable;
            }
        }
        public override ICollection<Verkstan.OperatorProperty> Properties
        {
            get
            {
                return new List<Verkstan.OperatorProperty>();
            }
        }
        private String typeName;
        public override String TypeName
        {
            get
            {
                return typeName;
            }
        }
        #endregion

        #region Private Variables
        private OperatorJoint.EventHandler receiverRemovedHandler;
        private OperatorJoint.EventHandler senderRemovedHandler;
        private OperatorJoint.EventHandler senderAddedHandler;
        #endregion

        #region Constructors
        public NoOperator()
            : base()
        {
            typeName = "No operator";
            primaryJoint = new OperatorJoint();

            primaryJoint.SenderAdded += new OperatorJoint.EventHandler(this.operatorJoint_SenderRemoved);
            primaryJoint.SenderRemoved += new OperatorJoint.EventHandler(this.operatorJoint_SenderAdded); 
        }
        #endregion

        #region Public Methods
        public override void OnCascadeStateChanged()
        {
            OnStateChanged();
        }
        public override void ConnectWithJointAsReceiver(OperatorJoint joint)
        {
     
        }
        public override void ConnectWithJointAsSender(OperatorJoint joint)
        {

        }
        public override void Dispose()
        {
            primaryJoint.Dispose();
        }
        public override System.Xml.XmlElement ToXmlElement(System.Xml.XmlDocument doc)
        {
            return doc.CreateElement("NoOperator");
        }
        public override void DisconnectFromAllJoints()
        {
            primaryJoint.RemoveSender(primaryJoint.Sender);
            primaryJoint.RemoveAllReceivers();
        }
        #endregion

        #region Event Handlers
        private void operatorJoint_SenderAdded(OperatorJoint joint, OperatorJoint.EventArgs e)
        {
            OnStateChanged();
        }
        private void operatorJoint_SenderRemoved(OperatorJoint joint, OperatorJoint.EventArgs e)
        {
            OnStateChanged();
        }
        #endregion
    }
}
