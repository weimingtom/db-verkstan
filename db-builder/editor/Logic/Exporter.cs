﻿using System;
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
        private List<String> exportDefines = new List<String>();
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
            WriteToHeader(filename, project.Name);
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
            PopulateIdNormalizerHash();

            foreach (ushort oldId in oldIdToNewId.Keys)
            {
                System.Console.WriteLine("oldId == " + oldId + " is now == " + oldIdToNewId[oldId]);
            }
            
            PopulateFilterDefines();
            PopulateExportDefines();

            AddOperatorFilterTypes();
            AddOperatorProperties();
            AddOperatorConnections();
            AddExports();
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
        private void PopulateIdNormalizerHash()
        {
            ushort id = 0;
            foreach (Operator op in exportOperators)
            {
                id = PopulateIdNormalizerHash(op, id);
                id++;
            }
        }
        private ushort PopulateIdNormalizerHash(Operator root, ushort id)
        {
            if (!oldIdToNewId.ContainsKey(root.BindedOperator.Id))
            {
                oldIdToNewId.Add(root.BindedOperator.Id, id);
                operatorsSortedOnNewId.Add(root);
            }
            foreach (Operator op in root.GetInputs())
            {
                id = PopulateIdNormalizerHash(op, ++id);
            }

            return id;
        }
        private void PopulateFilterDefines()
        {
            foreach (Operator op in exportOperators)
            {
                PopulateOperatorDefines(op);
            }
        }
        private void PopulateOperatorDefines(Operator root)
        {
            String name = root.BindedOperator.Name + root.BindedOperator.Type.ToString();
            name = name.ToUpper().Replace(" ", "");
            operatorDefines.Add("#define DB_" + name + "FILTER 1");

            foreach (Operator op in root.GetInputs())
                PopulateOperatorDefines(op);
        }
        private void PopulateExportDefines()
        {
            List<ExportOperator> textureExports = new List<ExportOperator>();
            List<ExportOperator> meshExports = new List<ExportOperator>();
            List<ExportOperator> renderableExports = new List<ExportOperator>();

            foreach (ExportOperator exportOp in exportOperators)
            {
                if (exportOp.BindedOperator.Type == Verkstan.Constants.OperatorTypes.Texture)
                    textureExports.Add(exportOp);
                else if (exportOp.BindedOperator.Type == Verkstan.Constants.OperatorTypes.Mesh)
                    meshExports.Add(exportOp);
                else
                    renderableExports.Add(exportOp);
            }

            int number = 0;
            foreach (ExportOperator exportOp in textureExports)
            {
                String name = exportOp.UniqueName;
                name = name.ToUpper().Replace(" ", "");
                exportDefines.Add("#define DB_BUILDER_EXPORT_" + name + " " + number);
                number++;
            }

            number = 0;
            foreach (ExportOperator exportOp in meshExports)
            {
                String name = exportOp.UniqueName;
                name = name.ToUpper().Replace(" ", "");
                exportDefines.Add("#define DB_BUILDER_EXPORT_" + name + " " + number);
                number++;
            }

            number = 0;
            foreach (ExportOperator exportOp in renderableExports)
            {
                String name = exportOp.UniqueName;
                name = name.ToUpper().Replace(" ", "");
                exportDefines.Add("#define DB_BUILDER_EXPORT_" + name + " " + number);
                number++;
            }
        }
        private void AddOperatorFilterTypes()
        {
            AddToData((ushort)oldIdToNewId.Count);
            foreach (Operator op in operatorsSortedOnNewId)
            {
                System.Console.WriteLine("FilterType = " + (byte)op.BindedOperator.FilterType);
                AddToData((byte)op.BindedOperator.FilterType);
            }

        }
        private void AddOperatorProperties()
        {
            IDictionary<byte, List<Operator>> filterType2Operators = new SortedDictionary<byte, List<Operator>>();

            foreach (Operator op in operatorsSortedOnNewId)
            {
                if (!filterType2Operators.ContainsKey(op.BindedOperator.FilterType))
                    filterType2Operators.Add(op.BindedOperator.FilterType, new List<Operator>());

                List<Operator> operators = filterType2Operators[op.BindedOperator.FilterType];
                operators.Add(op);
                operators.Sort(delegate(Operator op1, Operator op2)
                {
                    return oldIdToNewId[op1.BindedOperator.Id].CompareTo(oldIdToNewId[op2.BindedOperator.Id]);
                });
            }

            foreach (KeyValuePair<byte, List<Operator>> pair in filterType2Operators)
            {
                /*
                System.Console.Write("FilterType="+pair.Key + " [");
                foreach (Operator op in pair.Value)
                    System.Console.Write("newid=" + oldIdToNewId[op.BindedOperator.Id] + " oldid=" + op.BindedOperator.Id);
                System.Console.WriteLine("]");*/

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
        private void AddExports()
        {
            List<ExportOperator> textureExports = new List<ExportOperator>();
            List<ExportOperator> meshExports = new List<ExportOperator>();
            List<ExportOperator> renderableExports = new List<ExportOperator>();

            foreach (ExportOperator exportOp in exportOperators)
            {
                if (exportOp.BindedOperator.Type == Verkstan.Constants.OperatorTypes.Texture)
                    textureExports.Add(exportOp);
                else if (exportOp.BindedOperator.Type == Verkstan.Constants.OperatorTypes.Mesh)
                    meshExports.Add(exportOp);
                else
                    renderableExports.Add(exportOp);
            }

            AddToData((ushort)textureExports.Count);
            System.Console.WriteLine("Texture Exports=" + textureExports.Count);
            AddToData((ushort)meshExports.Count);
            System.Console.WriteLine("Mesh Exports=" + meshExports.Count);
            AddToData((ushort)renderableExports.Count);
            System.Console.WriteLine("Renderable Exports=" + renderableExports.Count);

            foreach (ExportOperator exportOp in textureExports)
            {
                AddToData((ushort)oldIdToNewId[exportOp.BindedOperator.Id]);
                System.Console.WriteLine("Texture id=" + oldIdToNewId[exportOp.BindedOperator.Id]);
            }

            foreach (ExportOperator exportOp in meshExports)
            {
                AddToData((ushort)oldIdToNewId[exportOp.BindedOperator.Id]);
                System.Console.WriteLine("Mesh id=" + oldIdToNewId[exportOp.BindedOperator.Id]);
            }

            foreach (ExportOperator exportOp in renderableExports)
            {
                AddToData((ushort)oldIdToNewId[exportOp.BindedOperator.Id]);
                System.Console.WriteLine("Renderable id=" + oldIdToNewId[exportOp.BindedOperator.Id]);
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
        private void WriteToHeader(String filename, String arrayName)
        {
            TextWriter textWriter = new StreamWriter(filename);

            textWriter.WriteLine("// Generated by Darkbits(r) Verkstan(tm) Enterprise Graphical");
            textWriter.WriteLine("// Demonstration Solutions Productivity Suite(tm) - Builder");
            textWriter.WriteLine("// Time of generation:" + DateTime.Now);
            textWriter.WriteLine();

            foreach (String define in operatorDefines)
                textWriter.WriteLine(define);

            textWriter.WriteLine();

            foreach (String define in exportDefines)
                textWriter.WriteLine(define);

            textWriter.WriteLine();
            textWriter.WriteLine("unsigned char " + arrayName.ToLowerInvariant() + "BuilderData[] = {");

            for (int i = 0; i < bytes.Count; i++)
            {
                textWriter.Write("0x"+bytes[i].ToString("X2").ToLower());

                if (i != bytes.Count - 1)
                    textWriter.Write(",");

                if ((i + 1) % 15 == 0)
                    textWriter.WriteLine();
            }

            textWriter.WriteLine(" };");
            textWriter.Close();
        }
        private void WriteToFile(String filename)
        {
            FileStream stream = File.Open(filename, FileMode.Create);
            BinaryWriter binaryWriter = new BinaryWriter(stream);

            for (int i = 0; i < bytes.Count; i++)
                binaryWriter.Write(bytes[i]);

            stream.Close();
        }
        #endregion
    }
}
