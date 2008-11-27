using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace VerkstanEditor.Logic
{
    class LoadOperator: Operator
    {
        #region Properties
        public override Verkstan.Constants.OperatorTypes Type
        {
            get { return Verkstan.Constants.OperatorTypes.Unspecified; }
        }
        public override Verkstan.CoreOperator BindedCoreOperator
        {
            get 
            {
                if (target == null)
                    return null;

                return target.BindedCoreOperator;
            }
        }
        public override bool IsProcessable
        {
            get
            {
                if (target == null)
                    return false;
                return target.IsProcessable;
            }
        }
        public override ICollection<Verkstan.CoreOperatorProperty> Properties
        {
            get
            {
                ICollection<Verkstan.CoreOperatorProperty> properties = new List<Verkstan.CoreOperatorProperty>();
                properties.Add(new Verkstan.CoreOperatorProperty(0, "Target", Verkstan.Constants.OperatorPropertyTypes.String));
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
        private Operator target;
        private Operator.EventHandler stateChangedEventHandler;
        #endregion

        #region Constructors
        public LoadOperator()
            : base()
        {
            typeName = "Load";
            stateChangedEventHandler = new Operator.EventHandler(this.load_StateChanged);
            UniqueName = AllocateUniqueName(TypeName);
        }
        #endregion

        #region Public Methods
        public override void Disposed(Operator op)
        {
            if (target == op)
            {
                target = null;
                typeName = "Load";
                OnStateChanged();
            }
        }
        public override List<Verkstan.CoreOperator> GetReceiverCoreOperators()
        {
            return new List<Verkstan.CoreOperator>();
        }
        public override List<Verkstan.CoreOperator> GetSenderCoreOperators()
        {
            if (target == null)
                return new List<Verkstan.CoreOperator>();
            else
                return target.GetSenderCoreOperatorsForLoad();
        }
        public override List<Verkstan.CoreOperator> GetSenderCoreOperatorsForLoad()
        {
            return new List<Verkstan.CoreOperator>();
        }
        public override void StackConnectChangedUpwards()
        {
            OnStateChanged();
        }
        public override void CascadeStackConnectChangedDownwards()
        {
            foreach (Operator op in receivers)
                op.CascadeStackConnectChangedDownwards();

            foreach (Operator op in loads)
                op.CascadeStackConnectChangedDownwards();

            OnStateChanged();
        }
        public override String GetStringProperty(int index)
        {   
            if (index == 0 && target != null)
                return target.Name;

            return "";   
        }
        public override void SetStringProperty(int index, String value)
        {
            if (index == 0)
            {
                Operator newTarget = Operator.Find(value);

                if (newTarget == target)
                    return;

                if (target != null)
                {
                    target.RemoveLoadOperator(this);
                    target.StateChanged -= stateChangedEventHandler;
                }

                target = newTarget;
                if (target != null)
                    typeName = "L<" + target.Name + ">";
                else
                    typeName = "Load";

                if (target != null)
                {
                    target.ConnectWithLoadOperator(this);
                    target.StateChanged += stateChangedEventHandler;
                }

                CascadeStackConnectChangedDownwards();
            }
        }
        public override XmlElement ToXmlElement(System.Xml.XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("operator");
            XmlElement typeElement = doc.CreateElement("type");
            typeElement.InnerText = "Load";
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
        public override void FromXmlElement(XmlElement root)
        {

        }
        #endregion

        #region Event Handlers
        void load_StateChanged(Operator.EventArgs e)
        {
            if (e.Operator.Name == null || e.Operator.Name == "")
                target = null;

            if (target != null)
                typeName = "L<" + target.Name + ">";
            else
                typeName = "Load";

            OnStateChanged();
        }
        #endregion
    }
}
