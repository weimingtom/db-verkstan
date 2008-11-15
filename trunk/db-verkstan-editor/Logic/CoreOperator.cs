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
        public override ICollection<Verkstan.OperatorProperty> Properties
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
                    Verkstan.OperatorInput input = bindedCoreOperator.Inputs[i];
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

                Verkstan.OperatorInput lastInput = null;
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
        #endregion
    }
}
