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
                return primaryJoint.Sender.BindedCoreOperator;
            }
        }
        private OperatorJoint primaryJoint;
        public override OperatorJoint PrimaryJoint
        {
            get
            {
                return primaryJoint;
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
        public override String Name
        {
            set
            {
                PrimaryJoint.Name = value;
                base.Name = value;

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
            primaryJoint = new OperatorJoint();
            primaryJoint.SenderAdded += new OperatorJoint.EventHandler(this.operatorJoint_SenderAdded);
            primaryJoint.SenderRemoved += new OperatorJoint.EventHandler(this.operatorJoint_SenderRemoved);    
        }
        #endregion

        #region Public Methods
        public override void OnCascadeStateChanged()
        {
            
        }
        public override void Dispose()
        {
            primaryJoint.Dispose();
        }
        public override void DisconnectFromAllJoints()
        {
            PrimaryJoint.RemoveSender(PrimaryJoint.Sender);
        }
        public override void ConnectWithJointAsReceiver(OperatorJoint joint)
        {
           
        }
        public override void ConnectWithJointAsSender(OperatorJoint joint)
        {
         
        }
        public override System.Xml.XmlElement ToXmlElement(System.Xml.XmlDocument doc)
        {
            return doc.CreateElement("Store");
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
