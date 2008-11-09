using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Xml;

namespace VerkstanEditor.Logic
{
    public abstract class Operator : IDisposable
    {
        #region Abstract Properties
        public abstract Verkstan.CoreOperator BindedCoreOperator { get;}
        public abstract ICollection<Verkstan.OperatorProperty> Properties { get; }
        public abstract String TypeName  { get; }
        public abstract OperatorJoint PrimaryJoint { get; }
        public abstract bool IsProcessable { get; }
        public abstract Verkstan.Constants.OperatorTypes Type { get; }
        #endregion

        #region Properties
        public int Top
        {
            get
            {
                return dimension.Top;
            }
        }
        public int LastTop
        {
            get
            {
                return lastDimension.Top;
            }
        }
        public int Left
        {
            get
            {
                return dimension.Left;
            }
        }
        public int LastLeft
        {
            get
            {
                return lastDimension.Left;
            }
        }
        public int Width
        {
            get
            {
                return dimension.Width;
            }
        }
        public int LastWidth
        {
            get
            {
                return lastDimension.Width;
            }
        }
        public int Height
        {
            get
            {
                return dimension.Height;
            }
        }
        public int LastHeight
        {
            get
            {
                return lastDimension.Height;
            }
        }
        public Point Location
        {
            get
            {
                return new Point(dimension.X, dimension.Y);
            }
        }
        public Point LastLocation
        {
            get
            {
                return new Point(lastDimension.X, lastDimension.Y);
            }
        }
        public Size Size
        {
            get
            {
                return new Size(dimension.Width, dimension.Height);
            }
        }
        public Size LastSize
        {
            get
            {
                return new Size(lastDimension.Width, lastDimension.Height);
            }
        }
        private Rectangle dimension;
        public Rectangle Dimension
        {
            set
            {
                lastDimension = dimension;
                dimension = value;
            }
            get
            {
                return dimension;
            }
        }
        private Rectangle lastDimension;
        public Rectangle LastDimension
        {
            get
            {
                return lastDimension;
            }
        }
        private String name;
        public virtual String Name
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
                    OnStateChanged();
                }
            }
        }
        private Boolean isSelected = false;
        public Boolean IsSelected
        {
            get
            {
                return isSelected;
            }
            set
            {
                if (isSelected != value)
                {
                    isSelected = value;
                    OnStateChanged();
                }
            }
        }
        private bool isWarningPresent = false;
        public bool IsWarningPresent
        {
            set
            {
                if (isWarningPresent != value)
                {
                    isWarningPresent = value;
                    OnStateChanged();
                }
            }
            get
            {
                return isWarningPresent;
            }
        }
        #endregion

        #region Private Variables
        private List<OperatorJoint> inputJoints;
        private List<OperatorJoint> outputJoints;
        private OperatorJoint.EventHandler senderAddedHandler;
        private OperatorJoint.EventHandler senderRemovedHandler;
        private OperatorJoint.EventHandler receiverAddedHandler;
        private OperatorJoint.EventHandler receiverRemovedHandler;
        private OperatorJoint.EventHandler processableChangedHandler;
        #endregion

        #region Public Static methods
        public static Point QuantizeLocation(Point location)
        {
            return new Point(location.X - location.X % 100,
                             location.Y - location.Y % 20);
        }
        public static Size QuantizeSize(Size size)
        {
            Size quantizedSize = new Size(size.Width - size.Width % 100,
                                          size.Height - size.Height % 20);

            if (quantizedSize.Width < 100)
                quantizedSize.Width = 100;
            if (quantizedSize.Height < 20)
                quantizedSize.Height = 20;
           
            return quantizedSize;
        }
        public static void Disconnect(Operator op)
        {
            op.DisconnectFromAllJoints();
        }
        public static void Connect(Operator sender, Operator receiver)
        {
            if (sender.GetType() == typeof(StoreOperator))
            {
                return;
            }
            else if (receiver.GetType() == typeof(LoadOperator))
            {
                return;
            }   
            else if (receiver.GetType() == typeof(StoreOperator))
            {
                sender.ConnectWithJointAsSender(receiver.PrimaryJoint);
            }
            else if (receiver.GetType() == typeof(NoOperator))
            {
                sender.ConnectWithJointAsSender(receiver.PrimaryJoint);
            }
            else if (sender.GetType() == typeof(LoadOperator))
            {
                receiver.ConnectWithJointAsReceiver(sender.PrimaryJoint);
                LoadOperator loadOp = (LoadOperator)sender;
                loadOp.AddReceiver(receiver);
            }
            else if (sender.GetType() == typeof(NoOperator))
            {
                receiver.ConnectWithJointAsReceiver(sender.PrimaryJoint);
            }
            else
            {
                receiver.ConnectWithJointAsReceiver(sender.PrimaryJoint);
            }
        }
        #endregion

        #region Constructors
        public Operator()
        {
            dimension = new Rectangle(0, 0, 100, 20);
            lastDimension = dimension;
        }
        #endregion

        #region Public Abstract Methods
        public abstract void OnCascadeStateChanged();
        public abstract void Dispose();
        public abstract void ConnectWithJointAsReceiver(OperatorJoint joint);
        public abstract void ConnectWithJointAsSender(OperatorJoint joint);
        public abstract void DisconnectFromAllJoints();
        public abstract XmlElement ToXmlElement(XmlDocument doc);
        #endregion

        #region Public methods
        public byte GetByteProperty(int index)
        {
            return BindedCoreOperator.GetByteProperty(index);
        }
        public void SetByteProperty(int index, byte value)
        {
            BindedCoreOperator.SetByteProperty(index, value);
        }
        public int GetIntProperty(int index)
        {
            return BindedCoreOperator.GetIntProperty(index);
        }
        public void SetIntProperty(int index, int value)
        {
            BindedCoreOperator.SetIntProperty(index, value);
        }
        public float GetFloatProperty(int index)
        {
            return BindedCoreOperator.GetFloatProperty(index);
        }
        public void SetFloatProperty(int index, float value)
        {
            BindedCoreOperator.SetFloatProperty(index, value);
        }
        public Color GetColorProperty(int index)
        {
            Verkstan.Color vc = BindedCoreOperator.GetColorProperty(index);
            return Color.FromArgb(vc.R, vc.G, vc.B);
        }
        public void SetColorProperty(int index, Color value)
        {
            Verkstan.Color vc = new Verkstan.Color(value.R, value.G, value.B);
            BindedCoreOperator.SetColorProperty(index, vc);
        }
        public Verkstan.Vector GetVectorProperty(int index)
        {
            return BindedCoreOperator.GetVectorProperty(index);
        }
        public void SetVectorProperty(int index, Verkstan.Vector value)
        {
            BindedCoreOperator.SetVectorProperty(index, value);
        }
        public virtual String GetStringProperty(int index)
        {
            return BindedCoreOperator.GetStringProperty(index);
        }
        public virtual void SetStringProperty(int index, String value)
        {
            BindedCoreOperator.SetStringProperty(index, value);
        }
        public int GetPropertyChannel(int index, int valueIndex)
        {
            return BindedCoreOperator.GetPropertyChannel(index, valueIndex);
        }
        public void SetPropertyChannel(int index, int valueIndex, int channel)
        {
            BindedCoreOperator.SetPropertyChannel(index, valueIndex, channel);
        }
        public float GetPropertyAmplify(int index, int valueIndex)
        {
            return BindedCoreOperator.GetPropertyAmplify(index, valueIndex);
        }
        public void SetPropertyAmplify(int index, int valueIndex, float amplify)
        {
            BindedCoreOperator.SetPropertyAmplify(index, valueIndex, amplify);
        }
        public Rectangle GetAreaForInConnections()
        {
            return new Rectangle(Left, Top - 1, Width - 1, 1);
        }
        public Rectangle GetAreaForOutConnections()
        {
            return new Rectangle(Left, Top + Height, Width - 1, 1);
        }
        public Rectangle GetAreaForResize()
        {
            return new Rectangle(Left + Width - 15, 
                                 Top, 
                                 15,
                                 20);
        }
        #endregion

        #region Events
        public class EventArgs : System.EventArgs
        {
            public readonly Operator Operator;
            public EventArgs(Operator op)
            {
                Operator = op;
            }
        }
        public delegate void EventHandler(EventArgs e);
        public event EventHandler StateChanged;
        protected void OnStateChanged()
        {
            if (StateChanged != null)
                StateChanged(new Operator.EventArgs(this));
        }
        #endregion 
    }
}
