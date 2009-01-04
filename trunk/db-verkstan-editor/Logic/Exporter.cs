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
        private static IDictionary<ushort, ushort> oldIdToNewId = new Dictionary<ushort, ushort>();
        private static IList<Operator> operatorsSortedOnNewId = new List<Operator>();
        private static IList<byte> bytes = new List<byte>();
        private static IList<String> operatorDefines = new List<String>();
        #endregion

        #region Public Static Methods
        public static void Export(Operator root, String filename)
        {
            oldIdToNewId.Clear();
            operatorsSortedOnNewId.Clear();
            bytes.Clear();
            operatorDefines.Clear();

            System.Console.WriteLine("Populating id directory.");
            PopulateOldIdToNewIdAndOperatorsSortedOnNewId(root, 0);
            System.Console.WriteLine("Populating operator defines.");
            PopulateOperatorDefines(root);
            
            AddOperatorInstances();
            AddOperatorProperties();
            AddOperatorConnections();
            // 5. Write the operators connections.

            // 6. Write property animations

            // 7. Write the number of timelines.

            // 8. Write timelines.

            // 9. Be happy!

            WriteToFile(filename);
        }
        #endregion

        #region Private Static Methods
        private static ushort PopulateOldIdToNewIdAndOperatorsSortedOnNewId(Operator root, ushort id)
        {
            System.Console.WriteLine(root.UniqueName + " id=" + root.BindedCoreOperator.Id + " newid=" + id);
            oldIdToNewId.Add(root.BindedCoreOperator.Id, id);
            operatorsSortedOnNewId.Add(root);
            foreach (Operator op in root.GetInputs())
                id = PopulateOldIdToNewIdAndOperatorsSortedOnNewId(op, ++id);

            return id;
        }
        private static void PopulateOperatorDefines(Operator root)
        {
            operatorDefines.Add(root.BindedCoreOperator.Name);

            foreach (Operator op in root.GetInputs())
                PopulateOperatorDefines(op);
        }
        private static void AddOperatorInstances()
        {
            AddToData((short)oldIdToNewId.Count);

            foreach (Operator op in operatorsSortedOnNewId)
                AddToData((byte)op.BindedCoreOperator.Number);

        }
        private static void AddOperatorProperties()
        {
            IDictionary<byte, List<Operator>> number2Operators = new SortedDictionary<byte, List<Operator>>();

            foreach (Operator op in operatorsSortedOnNewId)
            {
                if (!number2Operators.ContainsKey(op.BindedCoreOperator.Number))
                    number2Operators.Add(op.BindedCoreOperator.Number, new List<Operator>());

                List<Operator> operators = number2Operators[op.BindedCoreOperator.Number];
                operators.Add(op);
                operators.Sort(delegate(Operator op1, Operator op2)
                {
                    return oldIdToNewId[op1.BindedCoreOperator.Id].CompareTo(oldIdToNewId[op2.BindedCoreOperator.Id]);
                });
            }

            foreach (KeyValuePair<byte, List<Operator>> pair in number2Operators)
            {
                System.Console.Write("Number="+pair.Key + " [");
                foreach (Operator op in pair.Value)
                    System.Console.Write("newid=" + oldIdToNewId[op.BindedCoreOperator.Id] + " oldid=" + op.BindedCoreOperator.Id);
                System.Console.WriteLine("]");

                AddOperatorProperties(pair.Value);
            }
        }
        private static void AddOperatorProperties(List<Operator> operators)
        {
            Operator first = operators.First();

            foreach (Verkstan.CoreOperatorProperty property in first.BindedCoreOperator.Properties)
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
        private static void AddOperatorConnections()
        {
            foreach (Operator op in operatorsSortedOnNewId)
                if (op.BindedCoreOperator.NumberOfConstantInputs == -1)
                    AddToData((byte)op.BindedCoreOperator.GetNumberOfInputConnections());

            foreach (Operator op in operatorsSortedOnNewId)
            {
                ushort opId = oldIdToNewId[op.BindedCoreOperator.Id];
                foreach (Operator input in op.GetInputs())
                {
                    ushort id = (ushort)(oldIdToNewId[input.BindedCoreOperator.Id] - opId);
                    AddToData(id);
                }
            }
        }
        private static void AddToData(byte b)
        {
            bytes.Add(b);
        }
        private static void AddToData(Color color)
        {
            AddToData((byte)color.R);
            AddToData((byte)color.G);
            AddToData((byte)color.B);
        }
        private static void AddToData(short s)
        {
            byte[] array = BitConverter.GetBytes(s);

            foreach (byte arrayByte in array)
                bytes.Add(arrayByte);
        }
        private static void AddToData(ushort s)
        {
            byte[] array = BitConverter.GetBytes(s);

            foreach (byte arrayByte in array)
                bytes.Add(arrayByte);
        }
        private static void AddToData(float f)
        {
            byte[] array = BitConverter.GetBytes(f);

            foreach (byte arrayByte in array)
                bytes.Add(arrayByte);
        }
        private static void AddToData(String str)
        {
            AddToData((short)str.Length);

            foreach (char c in str.ToCharArray())
                foreach (byte b in BitConverter.GetBytes(c))
                    bytes.Add(b);
        }
        private static void AddToData(Verkstan.Vector v)
        {
            AddToData(v.X);
            AddToData(v.Y);
            AddToData(v.Z);
        }
        private static void WriteToFile(String filename)
        {
            TextWriter textWriter = new StreamWriter(filename);

            textWriter.WriteLine("// Generated by db Verkstan " + DateTime.Now);
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
        #endregion
    }
}
