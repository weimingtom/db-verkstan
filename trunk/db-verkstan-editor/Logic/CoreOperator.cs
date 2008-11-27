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
        private Verkstan.CoreOperator bindedCoreOperator;
        public override Verkstan.CoreOperator BindedCoreOperator
        {
            get
            {
                return bindedCoreOperator;
            }
        }
        public override ICollection<Verkstan.CoreOperatorProperty> Properties
        {
            get
            {
                return bindedCoreOperator.Properties;
            }
        }
        #endregion

        #region Constructors
        public CoreOperator(Verkstan.CoreOperator coreOperator)
            :base()
        {
            this.bindedCoreOperator = coreOperator;
            isProcessable = coreOperator.GetNumberOfRequiredInputs() == 0;
            UniqueName = AllocateUniqueName(TypeName);
        }
        #endregion

        #region Public Methods
        public override void Dispose()
        {
            if (bindedCoreOperator != null)
                bindedCoreOperator.Dispose();
            base.Dispose();
        }
        public override void Disposed(Operator op)
        {

        }
        public override List<Verkstan.CoreOperator> GetReceiverCoreOperators()
        {
            List<Verkstan.CoreOperator> result = new List<Verkstan.CoreOperator>();
            result.Add(bindedCoreOperator);
            return result;
        }
        public override List<Verkstan.CoreOperator> GetSenderCoreOperators()
        {
            List<Verkstan.CoreOperator> result = new List<Verkstan.CoreOperator>();
            result.Add(bindedCoreOperator);
            return result;
        }
        public override List<Verkstan.CoreOperator> GetSenderCoreOperatorsForLoad()
        {
            return GetSenderCoreOperators();
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
            PopulateXmlElementWithBasicOperatorInformation(root, doc);

            XmlElement properties = doc.CreateElement("properties");
            root.AppendChild(properties);

            foreach (Verkstan.CoreOperatorProperty property in bindedCoreOperator.Properties)
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

            if (Timeline != null)
            {
                XmlElement timline = Timeline.ToXmlElement(doc);
                root.AppendChild(timline);
            }

            return root;
        }
        public override void FromXmlElement(XmlElement root)
        {
            PopulateOperatorWithBasicXmlElementInformation(root);
        }
        #endregion

        #region Private Methods
        private void UpdateCoreInputConnections()
        {
            bindedCoreOperator.ClearInputConnections();

            List<Verkstan.CoreOperator> inputOperators = new List<Verkstan.CoreOperator>();
            foreach (Operator op in senders)
                foreach (Verkstan.CoreOperator coreOp in op.GetSenderCoreOperators())
                    inputOperators.Add(coreOp);

            int numberOfInputs = 0;
            int numberOfRequiredInputs = 0;

            foreach (Verkstan.CoreOperator coreOp in inputOperators)
            {
                if (coreOp.Id == bindedCoreOperator.Id)
                    continue;

                bool accepted = false;
                for (int i = numberOfInputs; i < bindedCoreOperator.Inputs.Count; i++)
                {
                    Verkstan.CoreOperatorInput input = bindedCoreOperator.Inputs[i];
                    if ((input.Type == coreOp.Type || input.Type == Verkstan.Constants.OperatorTypes.Unspecified)
                        && bindedCoreOperator.GetInputConnectionId(i) == -1)
                    {
                        bindedCoreOperator.SetInputConnectionId(i, coreOp.Id);
                        accepted = true;
                        numberOfInputs++;
                        if (!input.Optional)
                            numberOfRequiredInputs++;
                        break;
                    }
                }

                Verkstan.CoreOperatorInput lastInput = null;
                if (bindedCoreOperator.Inputs.Count > 0)
                    lastInput = bindedCoreOperator.Inputs[bindedCoreOperator.Inputs.Count - 1];

                if (!accepted
                    && lastInput != null
                    && lastInput.Infinite
                    && (lastInput.Type == coreOp.Type || lastInput.Type == Verkstan.Constants.OperatorTypes.Unspecified))
                {
                    for (int i = numberOfInputs; i < bindedCoreOperator.GetMaxInputConnections(); i++)
                    {
                        if (bindedCoreOperator.GetInputConnectionId(i) == -1)
                        {
                            bindedCoreOperator.SetInputConnectionId(i, coreOp.Id);
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

            isProcessable = requiredInputs <= numberOfRequiredInputs;
            bindedCoreOperator.SetDirty(true);
        }
        private void UpdateCoreOutputConnections()
        {
            bindedCoreOperator.ClearOutputConnections();

            List<Verkstan.CoreOperator> outputOperators = new List<Verkstan.CoreOperator>();
            foreach (Operator op in receivers)
                foreach (Verkstan.CoreOperator coreOp in op.GetReceiverCoreOperators())
                    outputOperators.Add(coreOp);

            int numberOfOutputs = 0;
            foreach (Verkstan.CoreOperator coreOp in outputOperators)
            {
                if (coreOp == null)
                    continue;

                for (int i = 0; i < bindedCoreOperator.GetMaxOutputConnections(); i++)
                {
                    if (bindedCoreOperator.GetOutputConnectionId(i) == -1)
                    {
                        bindedCoreOperator.SetOutputConnectionId(i, coreOp.Id);
                        numberOfOutputs++;
                        break;
                    }
                }
            }

            bindedCoreOperator.SetNumberOfOutputConnections(numberOfOutputs);
        }
        private XmlElement FromBytePropertyToXmlElement(XmlDocument doc, int index)
        {
            XmlElement byteElement = doc.CreateElement("byte");
            byteElement.SetAttribute("value", GetByteProperty(index).ToString());
            byteElement.AppendChild(FromPropertyAnimationToXmlElement(doc, index, 0));
            return byteElement;
        }
        private void FromXmlElementToByteProperty(XmlElement byteElement, int index)
        {
            byte value = byte.Parse(byteElement.GetAttribute("value"));
            SetByteProperty(index, value);
            FromXmlElementToPropertyAnimation((XmlElement)byteElement.ChildNodes[0], index, 0);
        }
        private XmlElement FromColorPropertyToXmlElement(XmlDocument doc, int index)
        {
            Color color = GetColorProperty(index);
            XmlElement colorElement = doc.CreateElement("color");
            XmlElement r = doc.CreateElement("r");
            colorElement.SetAttribute("r", color.R.ToString());
            colorElement.SetAttribute("g", color.G.ToString());
            colorElement.SetAttribute("b", color.B.ToString());
            colorElement.AppendChild(FromPropertyAnimationToXmlElement(doc, index, 0));
            colorElement.AppendChild(FromPropertyAnimationToXmlElement(doc, index, 1));
            colorElement.AppendChild(FromPropertyAnimationToXmlElement(doc, index, 2));
            return colorElement;
        }
        private void FromXmlElementToColorProperty(XmlElement colorElement, int index)
        {
            int r = int.Parse(colorElement.GetAttribute("r"));
            int g = int.Parse(colorElement.GetAttribute("g"));
            int b = int.Parse(colorElement.GetAttribute("b"));
            Color color = Color.FromArgb(r, g, b);
            SetColorProperty(index, color);
            FromXmlElementToPropertyAnimation((XmlElement)colorElement.ChildNodes[0], index, 0);
            FromXmlElementToPropertyAnimation((XmlElement)colorElement.ChildNodes[1], index, 1);
            FromXmlElementToPropertyAnimation((XmlElement)colorElement.ChildNodes[2], index, 2);
        }
        private XmlElement FromEnumPropertyToXmlElement(XmlDocument doc, int index)
        {
            byte enumIndex = GetByteProperty(index);
            XmlElement enumElement = doc.CreateElement("enum");
            enumElement.SetAttribute("value", enumIndex.ToString());
            enumElement.AppendChild(FromPropertyAnimationToXmlElement(doc, index, 0));
            return enumElement;
        }
        private void FromXmlElementToEnumProperty(XmlElement enumElement, int index)
        {
            byte enumIndex = byte.Parse(enumElement.GetAttribute("value"));
            SetByteProperty(index, enumIndex);
            FromXmlElementToPropertyAnimation((XmlElement)enumElement.ChildNodes[0], index, 0);
        }
        private XmlElement FromFloatPropertyToXmlElement(XmlDocument doc, int index)
        {
            float f = GetFloatProperty(index);
            XmlElement floatElement = doc.CreateElement("float");
            floatElement.SetAttribute("value", f.ToString());
            floatElement.AppendChild(FromPropertyAnimationToXmlElement(doc, index, 0));
            return floatElement;
        }
        private void FromXmlElementToProperty(XmlElement floatElement, int index)
        {
            float f = float.Parse(floatElement.GetAttribute("value"));
            FromXmlElementToPropertyAnimation((XmlElement)floatElement.ChildNodes[0], index, 0);
        }
        private XmlElement FromIntPropertyToXmlElement(XmlDocument doc, int index)
        {
            int i = GetIntProperty(index);
            XmlElement intElement = doc.CreateElement("int");
            intElement.SetAttribute("value", i.ToString());
            intElement.AppendChild(FromPropertyAnimationToXmlElement(doc, index, 0));
            return intElement;
        }
        private void FromXmlElementToIntProperty(XmlElement intElement, int index)
        {
            int i = int.Parse(intElement.GetAttribute("value"));
            SetIntProperty(index, i);
            FromXmlElementToPropertyAnimation((XmlElement)intElement.ChildNodes[0], index, 0);
        }
        private XmlElement FromStringPropertyToXmlElement(XmlDocument doc, int index)
        {
            String value = GetStringProperty(index);
            XmlElement stringElement = doc.CreateElement("string");
            stringElement.SetAttribute("value", value);
            stringElement.AppendChild(FromPropertyAnimationToXmlElement(doc, index, 0));
            return stringElement;
        }
        private void FromXmlElementToStringProperty(XmlElement stringElement, int index)
        {
            String value = stringElement.GetAttribute("value");
            SetStringProperty(index, value);
            FromXmlElementToPropertyAnimation((XmlElement)stringElement.ChildNodes[0], index, 0);

        }
        private XmlElement FromTextPropertyToXmlElement(XmlDocument doc, int index)
        {
            XmlElement textElement = doc.CreateElement("text");
            textElement.InnerText = GetStringProperty(index);
            textElement.AppendChild(FromPropertyAnimationToXmlElement(doc, index, 0));
            return textElement;
        }
        private void FromXmlElementToTextProperty(XmlElement textElement, int index)
        {
            String text = textElement.InnerText;
            SetStringProperty(index, text);
            FromXmlElementToPropertyAnimation((XmlElement)textElement.ChildNodes[0], index, 0);
        }
        private XmlElement FromVectorPropertyToXmlElement(XmlDocument doc, int index)
        {
            Verkstan.Vector vector = GetVectorProperty(index);
            XmlElement vectorElement = doc.CreateElement("vector");
            vectorElement.SetAttribute("x", vector.X.ToString());
            vectorElement.SetAttribute("y", vector.Y.ToString());
            vectorElement.SetAttribute("z", vector.Z.ToString());
            vectorElement.AppendChild(FromPropertyAnimationToXmlElement(doc, index, 0));
            vectorElement.AppendChild(FromPropertyAnimationToXmlElement(doc, index, 1));
            vectorElement.AppendChild(FromPropertyAnimationToXmlElement(doc, index, 2));
            return vectorElement;
        }
        private void FromXmlElementToVectorProperty(XmlElement vectorElement, int index)
        {
            float x = float.Parse(vectorElement.GetAttribute("x"));
            float y = float.Parse(vectorElement.GetAttribute("y"));
            float z = float.Parse(vectorElement.GetAttribute("z"));
            Verkstan.Vector vector = new Verkstan.Vector(x, y, z);
            SetVectorProperty(index, vector);
            FromXmlElementToPropertyAnimation((XmlElement)vectorElement.ChildNodes[0], index, 0);
            FromXmlElementToPropertyAnimation((XmlElement)vectorElement.ChildNodes[1], index, 1);
            FromXmlElementToPropertyAnimation((XmlElement)vectorElement.ChildNodes[2], index, 2);
        }
        private XmlElement FromPropertyAnimationToXmlElement(XmlDocument doc, int index, int valueIndex)
        {
            XmlElement animationElement = doc.CreateElement("animation");
            animationElement.SetAttribute("channel", GetPropertyChannel(index, valueIndex).ToString());
            animationElement.SetAttribute("amplify", GetPropertyAmplify(index, valueIndex).ToString());
            return animationElement;
        }
        private void FromXmlElementToPropertyAnimation(XmlElement animationElement, int index, int valueIndex)
        {
            int channel = int.Parse(animationElement.GetAttribute("channel"));
            float amplify = float.Parse(animationElement.GetAttribute("amplify"));
            SetPropertyChannel(index, valueIndex, channel);
            SetPropertyAmplify(index, valueIndex, amplify);
        }
        #endregion
    }
}
