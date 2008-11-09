using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    class LoadOperator: Operator
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
                ICollection<Verkstan.OperatorProperty> properties = new List<Verkstan.OperatorProperty>();
                properties.Add(new Verkstan.OperatorProperty(0, "Target", Verkstan.Constants.OperatorPropertyTypes.String));
                return properties;
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
        private OperatorJoint loadJoint;
        private List<Operator> receivers;
        private OperatorJoint.EventHandler receiverRemovedHandler;
        private OperatorJoint.EventHandler senderRemovedHandler;
        private OperatorJoint.EventHandler senderAddedHandler;
        private OperatorJoint.EventHandler nameChangedHandler;
        #endregion

        #region Constructors
        public LoadOperator()
            : base()
        {
            typeName = "Load";
            loadJoint = new OperatorJoint();
            primaryJoint = loadJoint;
            receivers = new List<Operator>();

            receiverRemovedHandler = new OperatorJoint.EventHandler(this.operatorJoint_ReceiverRemoved);
            senderRemovedHandler = new OperatorJoint.EventHandler(this.operatorJoint_SenderRemoved);
            senderAddedHandler = new OperatorJoint.EventHandler(this.operatorJoint_SenderAdded);
            nameChangedHandler = new OperatorJoint.EventHandler(this.operatorJoint_NameChanged);
            loadJoint.ReceiverRemoved += receiverRemovedHandler;
        }
        #endregion

        #region Public Methods
        public override void OnCascadeStateChanged()
        {
            OnStateChanged();
        }
        public void AddReceiver(Operator receiver)
        {
            receivers.Add(receiver);
        }
        public override void ConnectWithJointAsReceiver(OperatorJoint joint)
        {
     
        }
        public override void ConnectWithJointAsSender(OperatorJoint joint)
        {

        }
        public override void Dispose()
        {
            loadJoint.Dispose();
        }
        public override System.Xml.XmlElement ToXmlElement(System.Xml.XmlDocument doc)
        {
            return doc.CreateElement("Load");
        }
        public override void DisconnectFromAllJoints()
        {
            List<Operator> receiversCopy = new List<Operator>(receivers);
            foreach (Operator op in receiversCopy)
                primaryJoint.RemoveReceiver(op);
        }
        public override String GetStringProperty(int index)
        {   
            if (index == 0)
                return primaryJoint.Name;

            return "";   
        }
        public override void SetStringProperty(int index, String value)
        {
            if (index == 0)
            {
                OperatorJoint joint = OperatorJoint.Find(value);
                UpdatePrimaryJoint(joint);

                if (joint != null)
                    typeName = "L<"+joint.Name+">";
                else
                    typeName = "Load";
                OnStateChanged();
            }
        }
        #endregion

        #region Private Methods
        private void UpdatePrimaryJoint(OperatorJoint joint)
        {
            if (joint == null)
                joint = loadJoint;

            if (joint != primaryJoint)
            {
                if (primaryJoint != loadJoint)
                {
                    primaryJoint.ReceiverRemoved -= receiverRemovedHandler;
                    joint.SenderRemoved -= senderRemovedHandler;
                    joint.SenderAdded -= senderAddedHandler;
                    joint.NameChanged -= nameChangedHandler;
                }

                List<Operator> receiversCopy = new List<Operator>(receivers);
                foreach (Operator op in receiversCopy)
                {
                    primaryJoint.RemoveReceiver(op);
                    op.ConnectWithJointAsReceiver(joint);
                }
                receivers = receiversCopy;

                joint.ReceiverRemoved += receiverRemovedHandler;
                joint.SenderRemoved += senderRemovedHandler;
                joint.SenderAdded += senderAddedHandler;
                joint.NameChanged += nameChangedHandler;
            }

            primaryJoint = joint;
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
        private void operatorJoint_ReceiverRemoved(OperatorJoint joint, OperatorJoint.EventArgs e)
        {
            if (joint == primaryJoint)
                receivers.Remove(e.Receiver);
        }
        private void operatorJoint_NameChanged(OperatorJoint joint, OperatorJoint.EventArgs e)
        {
            if (joint == primaryJoint)
            {
                if (joint.Name == null || joint.Name == "")
                {
                    typeName = "Load";
                    UpdatePrimaryJoint(loadJoint);
                }
                else
                {
                    typeName = "L<" + joint.Name + ">";
                    OnStateChanged();
                }
            }
        }
        #endregion
    }
}
