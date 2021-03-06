﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Xml;

namespace VerkstanEditor.Logic
{
    class CoreOperator: Operator
    {
        #region Private Variables
        private List<Operator> inputs;
        #endregion

        #region Properties
        public override Verkstan.Constants.OperatorTypes Type
        {
            get { return bindedOperator.Type; }
        }
        public override String TypeName
        {
            get
            {
                if (bindedOperator == null)
                    return "";
                else
                    return bindedOperator.Name;
            }
        }
        private bool isProcessable = false;
        public override bool IsProcessable
        {
            get
            {
                bool result = isProcessable;

                foreach (Operator op in senders)
                    result &= op.IsProcessable;

                return result;
            }
        }
        private Verkstan.OperatorBinding bindedOperator;
        public override Verkstan.OperatorBinding BindedOperator
        {
            get
            {
                return bindedOperator;
            }
        }
        public override ICollection<Verkstan.OperatorBindingProperty> Properties
        {
            get
            {
                return bindedOperator.Properties;
            }
        }
        #endregion

        #region Constructors
        public CoreOperator(Verkstan.OperatorBinding bindedOperator)
            :base()
        {
            this.bindedOperator = bindedOperator;
            isProcessable = bindedOperator.GetNumberOfRequiredInputs() == 0;
            UniqueName = AllocateUniqueName(TypeName);
            inputs = new List<Operator>();
        }
        #endregion

        #region Public Methods
        public override List<Operator> GetInputs()
        {
            return inputs;
        }
        public override void Dispose()
        {
            if (bindedOperator != null)
                bindedOperator.Dispose();
            base.Dispose();
        }
        public override void OnDisposed(Operator op)
        {

        }
        public override List<Operator> GetReceiverOperators()
        {
            List<Operator> result = new List<Operator>();
            result.Add(this);
            return result;
        }
        public override List<Operator> GetSenderOperators()
        {
            List<Operator> result = new List<Operator>();
            result.Add(this);
            return result;
        }
        public override List<Operator> GetSenderOperatorsForLoad()
        {
            return GetSenderOperators();
        }
        public override void StackConnectChangedUpwards()
        {
            UpdateCoreOutputConnections();
            OnStateChanged();
        }
        public override void CascadeStackConnectChangedDownwards()
        {
            UpdateCoreInputConnections();

            foreach (Operator op in receivers)
                op.CascadeStackConnectChangedDownwards();

            foreach (Operator op in loads)
                op.CascadeStackConnectChangedDownwards();

            OnStateChanged();
        }
        public override XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("operator");
            root.SetAttribute("type", TypeName);
            
            PopulateXmlElementWithBasicOperatorInformation(root, doc);

            XmlElement properties = doc.CreateElement("properties");
            root.AppendChild(properties);

            foreach (Verkstan.OperatorBindingProperty property in bindedOperator.Properties)
            {
                if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Byte)
                    properties.AppendChild(FromBytePropertyToXmlElement(doc, property.Index));
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Color)
                    properties.AppendChild(FromColorPropertyToXmlElement(doc, property.Index));
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Enum)
                    properties.AppendChild(FromEnumPropertyToXmlElement(doc, property.Index));
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Float)
                    properties.AppendChild(FromFloatPropertyToXmlElement(doc, property.Index));
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Int)
                    properties.AppendChild(FromIntPropertyToXmlElement(doc, property.Index));
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.String)
                    properties.AppendChild(FromStringPropertyToXmlElement(doc, property.Index));
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Text)
                    properties.AppendChild(FromTextPropertyToXmlElement(doc, property.Index));
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Vector)
                    properties.AppendChild(FromVectorPropertyToXmlElement(doc, property.Index));
            }
            return root;
        }
        public override void FromXmlElement(XmlElement root)
        {
            PopulateOperatorWithBasicXmlElementInformation(root);

            foreach (XmlNode node in root.ChildNodes)
            {
                if (node.Name == "properties")
                {
                    for (int i = 0; i < node.ChildNodes.Count; i++)
                    {
                        XmlElement element = (XmlElement)node.ChildNodes[i];
                        if (element.Name == "byte")
                            FromXmlElementToByteProperty(element, i);
                        else if (element.Name == "color")
                            FromXmlElementToColorProperty(element, i);
                        else if (element.Name == "enum")
                            FromXmlElementToEnumProperty(element, i);
                        else if (element.Name == "float")
                            FromXmlElementToFloatProperty(element, i);
                        else if (element.Name == "int")
                            FromXmlElementToIntProperty(element, i);
                        else if (element.Name == "string")
                            FromXmlElementToStringProperty(element, i);
                        else if (element.Name == "text")
                            FromXmlElementToTextProperty(element, i);
                        else if (element.Name == "vector")
                            FromXmlElementToVectorProperty(element, i);
                    }
                }
            }
        }
        #endregion

        #region Private Methods
        private void UpdateCoreInputConnections()
        {
             bindedOperator.ClearInputConnections();
         
             List<Operator> unsortedInputs = new List<Operator>();

             List<Operator> sendersToConsiderAsInput = new List<Operator>();
             foreach (Operator op in senders)
             {
                 foreach (Operator opp in op.GetSenderOperators())
                     sendersToConsiderAsInput.Add(opp);
             }
             int numberOfInputs = 0;
             int numberOfRequiredInputs = 0;

             List<Boolean> inputAccepted = new List<bool>();
             foreach (Verkstan.OperatorBindingInput input in bindedOperator.Inputs)
                 inputAccepted.Add(false);
            
        
             foreach (Operator op in sendersToConsiderAsInput)
             {
                Verkstan.OperatorBinding bOp = op.BindedOperator;

                if (bOp.Id == bindedOperator.Id)
                    continue;

                bool accepted = false;
                for (int i = 0; i < bindedOperator.Inputs.Count; i++)
                {
                    if (inputAccepted[i])
                        continue;

                    Verkstan.OperatorBindingInput input = bindedOperator.Inputs[i];
                    if ((input.Type == bOp.Type || input.Type == Verkstan.Constants.OperatorTypes.Unspecified)
                        && bindedOperator.GetInputConnectionId(i) == -1)
                    {
                        bindedOperator.SetInputConnectionId(i, bOp.Id);
                        accepted = true;
                        inputAccepted[i] = true;
                        numberOfInputs++;
                        if (!input.Optional)
                            numberOfRequiredInputs++;
                        unsortedInputs.Add(op);
                        break;
                    }
                }

                Verkstan.OperatorBindingInput lastInput = null;
                if (bindedOperator.Inputs.Count > 0)
                    lastInput = bindedOperator.Inputs[bindedOperator.Inputs.Count - 1];

                if (!accepted
                    && lastInput != null
                    && lastInput.Infinite
                    && (lastInput.Type == bOp.Type || lastInput.Type == Verkstan.Constants.OperatorTypes.Unspecified))
                {
                    for (int i = 0; i < bindedOperator.GetMaxInputConnections(); i++)
                    {
                        if (bindedOperator.GetInputConnectionId(i) == -1)
                        {
                            bindedOperator.SetInputConnectionId(i, bOp.Id);
                            accepted = true;
                            numberOfInputs++;
                            unsortedInputs.Add(op);
                            break;
                        }
                    }
                }

                if (!accepted)
                {
                    IsWarningPresent = true;
                }
             }

             bindedOperator.SetNumberOfInputConnections(numberOfInputs);

         
             int requiredInputs = 0;
             for (int i = 0; i < bindedOperator.Inputs.Count; i++)
                if (!bindedOperator.Inputs[i].Optional && !bindedOperator.Inputs[i].Infinite)
                    requiredInputs++;

             isProcessable = requiredInputs <= numberOfRequiredInputs;
               
             bindedOperator.SetDirty(true);

             // Populate the list of inputs.
             inputs.Clear();
             for (int i = 0; i < numberOfInputs; i++)
             {
                int inputId = bindedOperator.GetInputConnectionId(i);

                foreach (Operator op in unsortedInputs)
                {
                    if (op.BindedOperator.Id == inputId)
                    {
                        inputs.Add(op);
                        break;
                    }
                }
             }
        }
        private void UpdateCoreOutputConnections()
        {
            bindedOperator.ClearOutputConnections();

            List<Operator> receiversToConsiderAsOutput = new List<Operator>();
            foreach (Operator receiver in receivers)
                foreach (Operator receiverReceiver in receiver.GetReceiverOperators())
                    receiversToConsiderAsOutput.Add(receiverReceiver);

            foreach (Operator receiver in loads)
                foreach (Operator receiverReceiver in receiver.GetReceiverOperators())
                    receiversToConsiderAsOutput.Add(receiverReceiver);

            int numberOfOutputs = 0;
            foreach (Operator op in receiversToConsiderAsOutput)
            {
                Verkstan.OperatorBinding bOp = op.BindedOperator;

                if (bOp == null)
                    continue;

                for (int i = 0; i < bindedOperator.GetMaxOutputConnections(); i++)
                {
                    if (bindedOperator.GetOutputConnectionId(i) == -1)
                    {
                        bindedOperator.SetOutputConnectionId(i, bOp.Id);
                        numberOfOutputs++;
                        break;
                    }
                }
            }

            bindedOperator.SetNumberOfOutputConnections(numberOfOutputs);
        }
        private XmlElement FromBytePropertyToXmlElement(XmlDocument doc, int index)
        {
            XmlElement byteElement = doc.CreateElement("byte");
            byteElement.SetAttribute("value", GetByteProperty(index).ToString());
            return byteElement;
        }
        private void FromXmlElementToByteProperty(XmlElement byteElement, int index)
        {
            byte value = byte.Parse(byteElement.GetAttribute("value"));
            SetByteProperty(index, value);
        }
        private XmlElement FromColorPropertyToXmlElement(XmlDocument doc, int index)
        {
            Color color = GetColorProperty(index);
            XmlElement colorElement = doc.CreateElement("color");
            XmlElement r = doc.CreateElement("r");
            colorElement.SetAttribute("r", color.R.ToString());
            colorElement.SetAttribute("g", color.G.ToString());
            colorElement.SetAttribute("b", color.B.ToString());
            return colorElement;
        }
        private void FromXmlElementToColorProperty(XmlElement colorElement, int index)
        {
            int r = int.Parse(colorElement.GetAttribute("r"));
            int g = int.Parse(colorElement.GetAttribute("g"));
            int b = int.Parse(colorElement.GetAttribute("b"));
            Color color = Color.FromArgb(r, g, b);
            SetColorProperty(index, color);
        }
        private XmlElement FromEnumPropertyToXmlElement(XmlDocument doc, int index)
        {
            byte enumIndex = GetByteProperty(index);
            XmlElement enumElement = doc.CreateElement("enum");
            enumElement.SetAttribute("value", enumIndex.ToString());
            return enumElement;
        }
        private void FromXmlElementToEnumProperty(XmlElement enumElement, int index)
        {
            byte enumIndex = byte.Parse(enumElement.GetAttribute("value"));
            SetByteProperty(index, enumIndex);
        }
        private XmlElement FromFloatPropertyToXmlElement(XmlDocument doc, int index)
        {
            float f = GetFloatProperty(index);
            XmlElement floatElement = doc.CreateElement("float");
            floatElement.SetAttribute("value", f.ToString());
            return floatElement;
        }
        private void FromXmlElementToFloatProperty(XmlElement floatElement, int index)
        {
            float f = float.Parse(floatElement.GetAttribute("value"));
            SetFloatProperty(index, f);
        }
        private XmlElement FromIntPropertyToXmlElement(XmlDocument doc, int index)
        {
            int i = GetIntProperty(index);
            XmlElement intElement = doc.CreateElement("int");
            intElement.SetAttribute("value", i.ToString());
            return intElement;
        }
        private void FromXmlElementToIntProperty(XmlElement intElement, int index)
        {
            int i = int.Parse(intElement.GetAttribute("value"));
            SetIntProperty(index, i);
        }
        private XmlElement FromStringPropertyToXmlElement(XmlDocument doc, int index)
        {
            String value = GetStringProperty(index);
            XmlElement stringElement = doc.CreateElement("string");
            stringElement.SetAttribute("value", value);
            return stringElement;
        }
        private void FromXmlElementToStringProperty(XmlElement stringElement, int index)
        {
            String value = stringElement.GetAttribute("value");
            SetStringProperty(index, value);
        }
        private XmlElement FromTextPropertyToXmlElement(XmlDocument doc, int index)
        {
            XmlElement textElement = doc.CreateElement("text");
            textElement.InnerText = GetStringProperty(index);
            return textElement;
        }
        private void FromXmlElementToTextProperty(XmlElement textElement, int index)
        {
            String text = textElement.InnerText;
            SetStringProperty(index, text);
        }
        private XmlElement FromVectorPropertyToXmlElement(XmlDocument doc, int index)
        {
            Verkstan.Vector vector = GetVectorProperty(index);
            XmlElement vectorElement = doc.CreateElement("vector");
            vectorElement.SetAttribute("x", vector.X.ToString());
            vectorElement.SetAttribute("y", vector.Y.ToString());
            vectorElement.SetAttribute("z", vector.Z.ToString());
            return vectorElement;
        }
        private void FromXmlElementToVectorProperty(XmlElement vectorElement, int index)
        {
            float x = float.Parse(vectorElement.GetAttribute("x"));
            float y = float.Parse(vectorElement.GetAttribute("y"));
            float z = float.Parse(vectorElement.GetAttribute("z"));
            Verkstan.Vector vector = new Verkstan.Vector(x, y, z);
            SetVectorProperty(index, vector);
        }
        #endregion
    }
}
