using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Xml;

namespace VerkstanEditor.Logic
{
    class CoreOperator: Operator
    {
        #region Properties
        public override Verkstan.Constants.OperatorTypes Type
        {
            get { return bindedCoreOperator.Type; }
        }
        public override String TypeName
        {
            get
            {
                if (bindedCoreOperator == null)
                    return "";
                else
                    return bindedCoreOperator.Name;
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
        private bool isProcessable = false;
        public override bool IsProcessable
        {
            get
            {
                bool result = isProcessable;

                foreach (OperatorJoint joint in inputJoints)
                    if (joint.Sender != null)
                        result &= joint.Sender.IsProcessable;

                return result;
            }
        }
        private Verkstan.CoreOperator bindedCoreOperator;
        public override Verkstan.CoreOperator BindedCoreOperator
        {
            get
            {
                return bindedCoreOperator;
            }
        }
        public override ICollection<Verkstan.OperatorProperty> Properties
        {
            get
            {
                return bindedCoreOperator.Properties;
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
        #endregion

        #region Constructors
        public CoreOperator(Verkstan.CoreOperator coreOperator)
            :base()
        {
            this.bindedCoreOperator = coreOperator;
            primaryJoint = new OperatorJoint();
            primaryJoint.AddSender(this);
            isProcessable = coreOperator.GetNumberOfRequiredInputs() == 0;
            inputJoints = new List<OperatorJoint>();
            outputJoints = new List<OperatorJoint>();
            outputJoints.Add(primaryJoint);
            senderAddedHandler = new OperatorJoint.EventHandler(this.operatorJoint_SenderAdded);
            senderRemovedHandler = new OperatorJoint.EventHandler(this.operatorJoint_SenderRemoved);
            receiverAddedHandler = new OperatorJoint.EventHandler(this.operatorJoint_ReceiverAdded);
            receiverRemovedHandler = new OperatorJoint.EventHandler(this.operatorJoint_ReceiverRemoved);
            primaryJoint.SenderAdded += senderAddedHandler;
            primaryJoint.SenderRemoved += senderRemovedHandler;
            primaryJoint.ReceiverAdded += receiverAddedHandler;
            primaryJoint.ReceiverRemoved += receiverRemovedHandler;
        }
        #endregion

        #region Public Methods
        public override void OnCascadeStateChanged()
        {
            OnStateChanged();

            foreach (OperatorJoint joint in outputJoints)
                foreach (Operator op in joint.Receivers)
                    op.OnCascadeStateChanged();
        }
        public override void Dispose()
        {
            if (bindedCoreOperator != null)
                bindedCoreOperator.Dispose();
            primaryJoint.Dispose();
        }
        public override XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("operator");
            XmlElement typeElement = doc.CreateElement("type");
            typeElement.InnerText = TypeName;
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
            XmlElement propertiesElement = doc.CreateElement("properties");
            root.AppendChild(propertiesElement);

            if (bindedCoreOperator == null)
                return root;

            foreach (Verkstan.OperatorProperty property in bindedCoreOperator.Properties)
            {
                if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Byte)
                {
                    XmlElement byteElement = doc.CreateElement("byte");
                    byteElement.InnerText = GetByteProperty(property.Index).ToString();
                    propertiesElement.AppendChild(byteElement);
                }
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Color)
                {
                    Color color = GetColorProperty(property.Index);
                    XmlElement colorElement = doc.CreateElement("color");
                    propertiesElement.AppendChild(colorElement);
                    XmlElement rElement = doc.CreateElement("r");
                    rElement.InnerText = color.R.ToString();
                    colorElement.AppendChild(rElement);
                    XmlElement gElement = doc.CreateElement("g");
                    gElement.InnerText = color.G.ToString();
                    colorElement.AppendChild(gElement);
                    XmlElement bElement = doc.CreateElement("b");
                    bElement.InnerText = color.B.ToString();
                    colorElement.AppendChild(bElement);
                }
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Enum)
                {
                    int index = GetByteProperty(property.Index);
                    XmlElement enumElement = doc.CreateElement("enum");
                    enumElement.InnerText = property.EnumValues[index];
                    propertiesElement.AppendChild(enumElement);
                }
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Float)
                {
                    XmlElement floatElement = doc.CreateElement("float");
                    floatElement.InnerText = GetFloatProperty(property.Index).ToString();
                    propertiesElement.AppendChild(floatElement);
                }
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Int)
                {
                    XmlElement intElement = doc.CreateElement("int");
                    intElement.InnerText = GetIntProperty(property.Index).ToString();
                    propertiesElement.AppendChild(intElement);
                }
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.String)
                {
                    XmlElement stringElement = doc.CreateElement("string");
                    stringElement.InnerText = GetStringProperty(property.Index);
                    propertiesElement.AppendChild(stringElement);
                }
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Text)
                {
                    XmlElement textElement = doc.CreateElement("text");
                    textElement.InnerText = GetStringProperty(property.Index);
                    propertiesElement.AppendChild(textElement);
                }
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Vector)
                {
                    Verkstan.Vector vector = GetVectorProperty(property.Index);
                    XmlElement vectorElement = doc.CreateElement("vector");
                    propertiesElement.AppendChild(vectorElement);
                    XmlElement vectorXElement = doc.CreateElement("x");
                    vectorXElement.InnerText = vector.X.ToString();
                    vectorElement.AppendChild(vectorXElement);
                    XmlElement vectorYElement = doc.CreateElement("y");
                    vectorYElement.InnerText = vector.Y.ToString();
                    vectorElement.AppendChild(vectorYElement);
                    XmlElement vectorZElement = doc.CreateElement("z");
                    vectorZElement.InnerText = vector.Z.ToString();
                    vectorElement.AppendChild(vectorZElement);
                }
            }

            return root;
        }
        public override void ConnectWithJointAsReceiver(OperatorJoint joint)
        {
            joint.SenderAdded += senderAddedHandler;
            joint.SenderRemoved += senderRemovedHandler;
            joint.ReceiverAdded += receiverAddedHandler;
            joint.ReceiverRemoved += receiverRemovedHandler;
            inputJoints.Add(joint);    
            joint.AddReceiver(this);
            UpdateCoreInputConnections();
            bindedCoreOperator.SetDirty(true);
        }
        public override void ConnectWithJointAsSender(OperatorJoint joint)
        {
            joint.SenderAdded += senderAddedHandler;
            joint.SenderRemoved += senderRemovedHandler;
            joint.ReceiverAdded += receiverAddedHandler;
            joint.ReceiverRemoved += receiverRemovedHandler;
            outputJoints.Add(joint);
            joint.AddSender(this);
            UpdateCoreOutputConnections();
            bindedCoreOperator.SetDirty(true);
        }
        public override void DisconnectFromAllJoints()
        {
            List<OperatorJoint> inputJointsCopy = new List<OperatorJoint>(inputJoints);
            foreach (OperatorJoint joint in inputJointsCopy)
                joint.RemoveReceiver(this);


            List<OperatorJoint> outputJointsCopy = new List<OperatorJoint>(outputJoints);
            foreach (OperatorJoint joint in outputJointsCopy)
            {
                if (joint == primaryJoint)
                    continue;

                joint.RemoveSender(this);
            }

            // As this operator owns the primary joint it's this operator's
            // responsibility to disconnect all receivers of the primary joint.
            primaryJoint.RemoveAllReceivers();

            UpdateCoreInputConnections();
            UpdateCoreOutputConnections();
        }
        #endregion

        #region Private Methods
        private void UpdateCoreInputConnections()
        {
            bindedCoreOperator.ClearInputConnections();

            List<Operator> inputOperators = new List<Operator>();
            foreach (OperatorJoint joint in inputJoints)
                if (joint.Sender != null)
                    inputOperators.Add(joint.Sender);

            int numberOfInputs = 0;
            int numberOfRequiredInputs = 0;

            foreach (Operator op in inputOperators)
            {
                if (op.BindedCoreOperator == null || op.BindedCoreOperator.Id == bindedCoreOperator.Id)
                    continue;

                bool accepted = false;
                for (int i = numberOfInputs; i < bindedCoreOperator.Inputs.Count; i++)
                {
                    Verkstan.OperatorInput input = bindedCoreOperator.Inputs[i];
                    if ((input.Type == op.BindedCoreOperator.Type || input.Type == Verkstan.Constants.OperatorTypes.Unspecified)
                        && bindedCoreOperator.GetInputConnectionId(i) == -1)
                    {
                        bindedCoreOperator.SetInputConnectionId(i, op.BindedCoreOperator.Id);
                        accepted = true;
                        numberOfInputs++;
                        if (!input.Optional)
                            numberOfRequiredInputs++;
                        break;
                    }
                }

                Verkstan.OperatorInput lastInput = null;
                if (bindedCoreOperator.Inputs.Count > 0)
                    lastInput = bindedCoreOperator.Inputs[bindedCoreOperator.Inputs.Count - 1];

                if (!accepted
                    && lastInput != null
                    && lastInput.Infinite
                    && (lastInput.Type == op.BindedCoreOperator.Type || lastInput.Type == Verkstan.Constants.OperatorTypes.Unspecified))
                {
                    for (int i = numberOfInputs; i < bindedCoreOperator.GetMaxInputConnections(); i++)
                    {
                        if (bindedCoreOperator.GetInputConnectionId(i) == -1)
                        {
                            bindedCoreOperator.SetInputConnectionId(i, op.BindedCoreOperator.Id);
                            accepted = true;
                            numberOfInputs++;
                            break;
                        }
                    }
                }

                if (!accepted)
                    IsWarningPresent = true;
            }

            bindedCoreOperator.SetNumberOfInputConnections(numberOfInputs);

            int requiredInputs = 0;
            for (int i = 0; i < bindedCoreOperator.Inputs.Count; i++)
                if (!bindedCoreOperator.Inputs[i].Optional)
                    requiredInputs++;

            SetProcessable(requiredInputs <= numberOfRequiredInputs);
        }
        private void UpdateCoreOutputConnections()
        {
            bindedCoreOperator.ClearOutputConnections();

            List<Operator> outputOperators = new List<Operator>();
            foreach (OperatorJoint joint in outputJoints)
                foreach (Operator op in joint.Receivers)
                    outputOperators.Add(op);

            int numberOfOutputs = 0;
            foreach (Operator op in outputOperators)
            {
                if (op.BindedCoreOperator == null)
                    continue;

                for (int i = 0; i < bindedCoreOperator.GetMaxOutputConnections(); i++)
                {
                    if (bindedCoreOperator.GetOutputConnectionId(i) == -1)
                    {
                        bindedCoreOperator.SetOutputConnectionId(i, op.BindedCoreOperator.Id);
                        numberOfOutputs++;
                        break;
                    }
                }
            }

            bindedCoreOperator.SetNumberOfOutputConnections(numberOfOutputs);
        }
        private void SetProcessable(bool processable)
        {
            isProcessable = processable;
            OnCascadeStateChanged();
        }
        #endregion

        #region Event Handlers
        private void operatorJoint_SenderAdded(OperatorJoint joint, OperatorJoint.EventArgs e)
        {
            if (inputJoints.Contains(joint))
            {
                UpdateCoreInputConnections();
                bindedCoreOperator.SetDirty(true);
            }
        }
        private void operatorJoint_SenderRemoved(OperatorJoint joint, OperatorJoint.EventArgs e)
        {
            if (outputJoints.Contains(joint) && e.Sender == this)
            {
                joint.SenderAdded -= senderAddedHandler;
                joint.SenderRemoved -= senderRemovedHandler;
                joint.ReceiverAdded -= receiverAddedHandler;
                joint.ReceiverRemoved -= receiverRemovedHandler;
                outputJoints.Remove(joint);
                UpdateCoreOutputConnections();
            }
            else if (inputJoints.Contains(joint))
            {
                UpdateCoreInputConnections();
                System.Console.WriteLine("Is processable = " + IsProcessable);
                bindedCoreOperator.SetDirty(true);
            }
        }
        private void operatorJoint_ReceiverAdded(OperatorJoint joint, OperatorJoint.EventArgs e)
        {
            if (outputJoints.Contains(joint))
                UpdateCoreOutputConnections();
        }
        private void operatorJoint_ReceiverRemoved(OperatorJoint joint, OperatorJoint.EventArgs e)
        {
            if (outputJoints.Contains(joint))
            {
                UpdateCoreOutputConnections();
            }
            else if (inputJoints.Contains(joint) && e.Receiver == this)
            {
                joint.SenderAdded -= senderAddedHandler;
                joint.SenderRemoved -= senderRemovedHandler;
                joint.ReceiverAdded -= receiverAddedHandler;
                joint.ReceiverRemoved -= receiverRemovedHandler;
                inputJoints.Remove(joint);
                UpdateCoreInputConnections();
                bindedCoreOperator.SetDirty(true);
            }
        }
        #endregion
    }
}
