using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Drawing;

namespace VerkstanEditor.Logic
{
    class Exporter
    {
        #region Private Static Variables
        private IList<ExportOperator> exportOperators = new List<ExportOperator>();
        private IDictionary<ushort, ushort> oldIdToNewId = new Dictionary<ushort, ushort>();
        private IList<Operator> operatorsSortedOnNewId = new List<Operator>();
        private IList<byte> bytes = new List<byte>();
        private HashSet<String> operatorDefines = new HashSet<String>();
        #endregion

        #region Constructor
        public Exporter()
        {
        }
        #endregion

        #region Public Static Methods
        public void ExportToHeader(Project project, String filename)
        {
            Export(project);
            WriteToHeader(filename);
        }
        public void ExportToFile(Project project, String filename)
        {
            Export(project);
            WriteToFile(filename);
        }
        #endregion

        #region Private Methods
        private void Export(Project project)
        {
            LocateAllExportOperators(project);
            System.Console.WriteLine("Number of exports == " + exportOperators.Count);
            PopulateOldIdToNewIdAndOperatorsSortedOnNewId();

            foreach (ushort oldId in oldIdToNewId.Keys)
            {
                System.Console.WriteLine("oldId == " + oldId + " is now == " + oldIdToNewId[oldId]);
            }
            //PopulateOperatorDefines(root);

            //AddOperatorInstances();
            //AddOperatorProperties();
            //AddOperatorConnections();

           
        }
        private void LocateAllExportOperators(Project project)
        {
            foreach (Page page in project.Pages)
            {
                foreach (Operator op in page.Operators)
                {
                    if (op.GetType() == typeof(ExportOperator) && op.IsProcessable)
                    {
                        exportOperators.Add((ExportOperator)op);
                    }
                }
            }
        }
        private void PopulateOldIdToNewIdAndOperatorsSortedOnNewId()
        {
            ushort id = 0;
            foreach (Operator op in exportOperators)
            {
                id = PopulateOldIdToNewIdAndOperatorsSortedOnNewId(op, id);
            }
        }
        private ushort PopulateOldIdToNewIdAndOperatorsSortedOnNewId(Operator root, ushort id)
        {
            if (!oldIdToNewId.ContainsKey(root.BindedOperator.Id))
            {
                oldIdToNewId.Add(root.BindedOperator.Id, id);
                operatorsSortedOnNewId.Add(root);
            }
            foreach (Operator op in root.GetInputs())
            {
                id = PopulateOldIdToNewIdAndOperatorsSortedOnNewId(op, ++id);
            }
            return id;
        }
        private void PopulateOperatorDefines(Operator root)
        {
            operatorDefines.Add(root.BindedOperator.Name);

            foreach (Operator op in root.GetInputs())
                PopulateOperatorDefines(op);
        }
        private void AddOperatorInstances()
        {
            AddToData((short)oldIdToNewId.Count);

            foreach (Operator op in operatorsSortedOnNewId)
                AddToData((byte)op.BindedOperator.Number);

        }
        private void AddOperatorProperties()
        {
            IDictionary<byte, List<Operator>> number2Operators = new SortedDictionary<byte, List<Operator>>();

            foreach (Operator op in operatorsSortedOnNewId)
            {
                if (!number2Operators.ContainsKey(op.BindedOperator.Number))
                    number2Operators.Add(op.BindedOperator.Number, new List<Operator>());

                List<Operator> operators = number2Operators[op.BindedOperator.Number];
                operators.Add(op);
                operators.Sort(delegate(Operator op1, Operator op2)
                {
                    return oldIdToNewId[op1.BindedOperator.Id].CompareTo(oldIdToNewId[op2.BindedOperator.Id]);
                });
            }

            foreach (KeyValuePair<byte, List<Operator>> pair in number2Operators)
            {
                System.Console.Write("Number="+pair.Key + " [");
                foreach (Operator op in pair.Value)
                    System.Console.Write("newid=" + oldIdToNewId[op.BindedOperator.Id] + " oldid=" + op.BindedOperator.Id);
                System.Console.WriteLine("]");

                AddOperatorProperties(pair.Value);
            }
        }
        private void AddOperatorProperties(List<Operator> operators)
        {
            Operator first = operators.First();

            foreach (Verkstan.OperatorBindingProperty property in first.BindedOperator.Properties)
            {
                foreach (Operator op in operators)
                {
                    switch (property.Type)
                    {
                        case Verkstan.Constants.OperatorPropertyTypes.Byte:
                            AddToData(op.GetByteProperty(property.Index));
                            break;
                        case Verkstan.Constants.OperatorPropertyTypes.Color:
                            AddToData(op.GetColorProperty(property.Index));
                            break;
                        case Verkstan.Constants.OperatorPropertyTypes.Enum:
                            AddToData(op.GetByteProperty(property.Index));
                            break;
                        case Verkstan.Constants.OperatorPropertyTypes.Float:
                            AddToData(op.GetFloatProperty(property.Index));
                            break;
                        case Verkstan.Constants.OperatorPropertyTypes.Int:
                            AddToData((short)op.GetIntProperty(property.Index));
                            break;
                        case Verkstan.Constants.OperatorPropertyTypes.String:
                            AddToData(op.GetStringProperty(property.Index));
                            break;
                        case Verkstan.Constants.OperatorPropertyTypes.Text:
                            AddToData(op.GetStringProperty(property.Index));
                            break;
                        case Verkstan.Constants.OperatorPropertyTypes.Vector:
                            AddToData(op.GetVectorProperty(property.Index));
                            break;
                    }
                }
            }
        }
        private void AddOperatorConnections()
        {
            foreach (Operator op in operatorsSortedOnNewId)
                if (op.BindedOperator.NumberOfConstantInputs == -1)
                    AddToData((byte)op.BindedOperator.GetNumberOfInputConnections());

            foreach (Operator op in operatorsSortedOnNewId)
            {
                ushort opId = oldIdToNewId[op.BindedOperator.Id];
                ushort lastId = 0; // Used for delta encoding
                for (int i = 0; i < op.BindedOperator.GetNumberOfInputConnections(); i++)
                {
                    // When getting input ids, it's important to use the CoreOperator.GetInputConnectionId
                    // and not rely on the Operator.GetInputs method as the Operator.GetInputs method
                    // isn't sorted correctly.
                    ushort inputId = oldIdToNewId[(ushort)op.BindedOperator.GetInputConnectionId(i)];
                    ushort id = (ushort)((inputId - opId) - lastId);
                    AddToData(id);
                    lastId = id;
                }
            }
        }
        private void AddToData(byte b)
        {
            bytes.Add(b);
        }
        private void AddToData(sbyte b)
        {
            bytes.Add(unchecked((byte)b));
        }
        private void AddToData(Color color)
        {
            AddToData((byte)color.R);
            AddToData((byte)color.G);
            AddToData((byte)color.B);
        }
        private void AddToData(short s)
        {
            byte[] array = BitConverter.GetBytes(s);

            foreach (byte arrayByte in array)
                bytes.Add(arrayByte);
        }
        private void AddToData(ushort s)
        {
            byte[] array = BitConverter.GetBytes(s);

            foreach (byte arrayByte in array)
                bytes.Add(arrayByte);
        }
        private void AddToData(int i)
        {
            byte[] array = BitConverter.GetBytes(i);

            foreach (byte arrayByte in array)
                bytes.Add(arrayByte);
        }
        private void AddToData(float f)
        {
            byte[] array = BitConverter.GetBytes(f);

            foreach (byte arrayByte in array)
                bytes.Add(arrayByte);
        }
        private void AddToData(String str)
        {
            byte[] byteArray = Encoding.GetEncoding("iso-8859-1").GetBytes(str);
            AddToData((ushort)byteArray.Length);
            foreach (byte b in byteArray)
                bytes.Add(b);
        }
        private void AddToData(Verkstan.Vector v)
        {
            AddToData(v.X);
            AddToData(v.Y);
            AddToData(v.Z);
        }
        private void WriteToHeader(String filename)
        {
            TextWriter textWriter = new StreamWriter(filename);

            textWriter.WriteLine("// Generated by db-builder " + DateTime.Now);
            textWriter.WriteLine();

            foreach (String str in operatorDefines)
                textWriter.WriteLine("#define DB_" + str.ToUpper().Replace(" ", "") + "OPERATOR 1");

            textWriter.WriteLine();
            textWriter.WriteLine("unsigned char graphicsData[] = {");

            for (int i = 0; i < bytes.Count; i++)
            {
                textWriter.Write("0x"+bytes[i].ToString("X2").ToLower());

                if (i != bytes.Count - 1)
                    textWriter.Write(",");

                if ((i + 1) % 10 == 0)
                    textWriter.WriteLine();
            }

            textWriter.WriteLine(" };");
            textWriter.Close();
        }
        private void WriteToFile(String filename)
        {
            throw new NotImplementedException();
        }
        #endregion
    }
}
