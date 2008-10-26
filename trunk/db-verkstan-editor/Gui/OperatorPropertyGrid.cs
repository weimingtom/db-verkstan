﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class OperatorPropertyGrid : UserControl 
    {
        private Operator op;

        public Operator Operator
        {
            set
            {
                if (op != value)
                {
                    op = value;
                    Deinitialize();

                    if (value != null)
                        Initialize();
                }
            }
            get
            {
                return op;
            }
        }

        private void Deinitialize()
        {
            OperatorPropertyTable.Visible = false;
            OperatorPropertyTable.Controls.Clear();
            OperatorPropertyTable.Height = 0;
        }

        private void Initialize()
        {
            Verkstan.OperatorProperties properties = op.Properties;

           OperatorPropertyTable.RowCount = properties.Count;
           int row = 0;
           foreach (Verkstan.OperatorProperty property in properties.GetList())
           {
               Label label = new Label();
               label.MouseDown += new System.Windows.Forms.MouseEventHandler(this.OperatorProperty_LabelMouseDown);
               label.Text = property.Name;
               label.Dock = DockStyle.Left;
               label.Font = new Font(label.Font, FontStyle.Bold);
               label.TextAlign = ContentAlignment.MiddleRight;

               OperatorPropertyTable.Controls.Add(label);
               OperatorPropertyTable.SetCellPosition(label, new TableLayoutPanelCellPosition(0, row));

               if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Byte)
               {
                   int index = property.CoreIndex;
                   NumericUpDown numericUpDown = new NumericUpDown();
                   numericUpDown.Increment = 1;
                   numericUpDown.Minimum = 0;
                   numericUpDown.Maximum = 255;
                   numericUpDown.Value = (int)op.Binding.GetByteProperty(index);
                   numericUpDown.Width = 50;
                   numericUpDown.ValueChanged += new EventHandler((object o, EventArgs e) => op.Binding.SetByteProperty(index, (byte)numericUpDown.Value));
                   OperatorPropertyTable.Controls.Add(numericUpDown);
                   OperatorPropertyTable.SetCellPosition(numericUpDown, new TableLayoutPanelCellPosition(1, row));
               }
               else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Int)
               {
                   int index = property.CoreIndex;
                   NumericUpDown numericUpDown = new NumericUpDown();
                   numericUpDown.Increment = 1;
                   numericUpDown.Minimum = int.MinValue;
                   numericUpDown.Maximum = int.MaxValue;
                   numericUpDown.Value = op.Binding.GetIntProperty(index);
                   numericUpDown.Width = 100;
                   numericUpDown.ValueChanged += new EventHandler((object o, EventArgs e) => op.Binding.SetIntProperty(index, (int)numericUpDown.Value));
                   OperatorPropertyTable.Controls.Add(numericUpDown);
                   OperatorPropertyTable.SetCellPosition(numericUpDown, new TableLayoutPanelCellPosition(1, row));
               }
               else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Float)
               {
                   int index = property.CoreIndex;
                   NumericUpDown numericUpDown = new NumericUpDown();
                   numericUpDown.Increment = 0.001M;
                   numericUpDown.DecimalPlaces = 3;
                   numericUpDown.Minimum = decimal.MinValue;
                   numericUpDown.Maximum = decimal.MaxValue;
                   numericUpDown.Value = Convert.ToDecimal(op.Binding.GetFloatProperty(index));
                   numericUpDown.Width = 100;
                   numericUpDown.ValueChanged += new EventHandler((object o, EventArgs e) => op.Binding.SetFloatProperty(index, Convert.ToSingle(numericUpDown.Value)));
                   OperatorPropertyTable.Controls.Add(numericUpDown);
                   OperatorPropertyTable.SetCellPosition(numericUpDown, new TableLayoutPanelCellPosition(1, row));
               }
               else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.String)
               {
                   int index = property.CoreIndex;
                   TextBox textBox = new TextBox();
                   textBox.Dock = DockStyle.Fill;
                   textBox.Text = op.Binding.GetStringProperty(index);
                   textBox.TextChanged += new EventHandler((object o, EventArgs e) => op.Binding.SetStringProperty(index, textBox.Text));
                   OperatorPropertyTable.Controls.Add(textBox);
                   OperatorPropertyTable.SetCellPosition(textBox, new TableLayoutPanelCellPosition(1, row));
               }
               else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Text)
               {
                   int index = property.CoreIndex;
                   TextBox textBox = new TextBox();
                   textBox.AcceptsReturn = true;
                   textBox.AcceptsTab = true;
                   textBox.Multiline = true;
                   textBox.Height = 200;
                   textBox.WordWrap = true;
                   textBox.Dock = DockStyle.Fill;
                   textBox.Text = op.Binding.GetStringProperty(index);
                   textBox.TextChanged += new EventHandler((object o, EventArgs e) => op.Binding.SetStringProperty(index, textBox.Text));
                   OperatorPropertyTable.Controls.Add(textBox);
                   OperatorPropertyTable.SetCellPosition(textBox, new TableLayoutPanelCellPosition(1, row));
               }
               else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Color)
               {
                   int index = property.CoreIndex;
                   ColorProperty colorProperty = new ColorProperty();
                   colorProperty.Color = Color.FromArgb(op.Binding.GetByteProperty(index),
                                                        op.Binding.GetByteProperty(index + 1),
                                                        op.Binding.GetByteProperty(index + 2));
                   colorProperty.ColorChanged += delegate(object o, EventArgs e)
                   {
                       op.Binding.SetByteProperty(index, colorProperty.Color.R);
                       op.Binding.SetByteProperty(index + 1, colorProperty.Color.G);
                       op.Binding.SetByteProperty(index + 2, colorProperty.Color.B);
                   };

                   OperatorPropertyTable.Controls.Add(colorProperty);
                   OperatorPropertyTable.SetCellPosition(colorProperty, new TableLayoutPanelCellPosition(1, row));
               }
               else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Vector)
               {
                   int index = property.CoreIndex;
                   VectorProperty vectorProperty = new VectorProperty();
                   vectorProperty.X = op.Binding.GetFloatProperty(index);
                   vectorProperty.Y = op.Binding.GetFloatProperty(index + 1);
                   vectorProperty.Z = op.Binding.GetFloatProperty(index + 2);
                   vectorProperty.ValueChanged += delegate(object o, EventArgs e)
                   {
                       op.Binding.SetFloatProperty(index, vectorProperty.X);
                       op.Binding.SetFloatProperty(index + 1, vectorProperty.Y);
                       op.Binding.SetFloatProperty(index + 2, vectorProperty.Z);
                   };

                   OperatorPropertyTable.Controls.Add(vectorProperty);
                   OperatorPropertyTable.SetCellPosition(vectorProperty, new TableLayoutPanelCellPosition(1, row));
               }
               row++;
            }

            // Add a dummy label at the end of the table. If we don't
            // then the last line of the properties will use the rest of the
            // space and end up too big.
            Label dummyLabel = new Label();
            OperatorPropertyTable.Controls.Add(dummyLabel);
            OperatorPropertyTable.SetCellPosition(dummyLabel, new TableLayoutPanelCellPosition(0, row));
            OperatorPropertyTable.Visible = true;
        }

        public OperatorPropertyGrid()
        {
            InitializeComponent();
        }

        private void OperatorPropertyTable_MouseDown(object sender, MouseEventArgs e)
        {
            OperatorPropertyTable.Focus();
        }

        private void OperatorProperty_MouseDown(object sender, MouseEventArgs e)
        {
            OperatorPropertyTable.Focus();
        }

        private void OperatorProperty_LabelMouseDown(object sender, MouseEventArgs e)
        {
            OperatorPropertyTable.Focus();
        }
    }
}
