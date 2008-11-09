using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VerkstanEditor.Logic
{
    public class OperatorJoint: IDisposable
    {
        #region Properties
        private String name;
        public String Name
        {
            get
            {
                return name;
            }
            set
            {
                if (name != value)
                {
                    name = value;
                    OnNameChanged();
                }
            }
        }
        private List<Operator> receivers;
        public ICollection<Operator> Receivers
        {
            get
            {
                return receivers.AsReadOnly();
            }
        }
        private Operator sender;
        public Operator Sender
        {
            get
            {
                return sender;
            }
        }
        #endregion
        
        #region Constructors
        public OperatorJoint()
        {
            receivers = new List<Operator>();
            joints.Add(this);
        }
        #endregion

        #region Static Variables
        private static List<OperatorJoint> joints = new List<OperatorJoint>();
        #endregion

        #region Static Methods
        public static OperatorJoint Find(String name)
        {
            foreach (OperatorJoint joint in joints)
             if (joint.Name == name)
                 return joint;

            return null;
        }
        #endregion

        #region Public Methods
        public void Dispose()
        {
            joints.Remove(this);
        }
        public void AddSender(Operator op)
        {
            if (op == null)
                throw new Exception("Null sender not allowed!");

            sender = op;
            OnSenderAdded(sender);
        }
        public void RemoveSender(Operator op)
        {
            if (sender != op)
                throw new Exception("Operator is not a sender of this joint!");

            sender = null;
            OnSenderRemoved(op);  
        }
        public void AddReceiver(Operator op)
        {
            receivers.Add(op);
            OnReceiverAdded(op);
        }
        public void RemoveReceiver(Operator op)
        {
            receivers.Remove(op);
            OnReceiverRemoved(op);
        }
        public void RemoveAllReceivers()
        {
            ICollection<Operator> operators = new List<Operator>(receivers);
            foreach (Operator op in operators)
            {
                receivers.Remove(op);
                OnReceiverRemoved(op);
            }
        }
        #endregion

        #region Events
        public class EventArgs : System.EventArgs
        {
            public Operator Sender;
            public Operator Receiver;
            public EventArgs(Operator sender, Operator receiver)
            {
                Sender = sender;
                Receiver = receiver;
            }
        }
        public delegate void EventHandler(OperatorJoint joint, EventArgs e);
        public event EventHandler SenderAdded;
        protected void OnSenderAdded(Operator sender)
        {
            if (SenderAdded != null)
                SenderAdded(this, new EventArgs(sender, null));
        }
        public event EventHandler SenderRemoved;
        protected void OnSenderRemoved(Operator sender)
        {
            if (SenderRemoved != null)
                SenderRemoved(this, new EventArgs(sender, null));
        }
        public event EventHandler ReceiverAdded;
        protected void OnReceiverAdded(Operator receiver)
        {
            if (ReceiverAdded != null)
                ReceiverAdded(this, new EventArgs(null, receiver));
        }
        public event EventHandler ReceiverRemoved;
        protected void OnReceiverRemoved(Operator receiver)
        {
            if (ReceiverRemoved != null)
                ReceiverRemoved(this, new EventArgs(null, receiver));
        }
        public event EventHandler NameChanged;
        protected void OnNameChanged()
        {
            if (NameChanged != null)
                NameChanged(this, new EventArgs(null, null));
        }
        #endregion
    }
}
