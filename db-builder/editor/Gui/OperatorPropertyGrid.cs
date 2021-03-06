﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using VerkstanEditor.Logic;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class OperatorPropertyGrid : UserControl
    {
        #region Properties
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
        public override Color BackColor
        {
            set
            {
                tableLayoutPanel1.BackColor = value;
                base.BackColor = value;
            }
            get
            {
                return base.BackColor;
            }
        }
        #endregion

        #region Private Variables
        private TableLayoutPanel tableLayoutPanel1;
        #endregion

        #region Constructor
        public OperatorPropertyGrid()
        {
            InitializeComponent();
            tableLayoutPanel1 = new TableLayoutPanel();
            tableLayoutPanel1.Dock = DockStyle.None;
            tableLayoutPanel1.Location = new Point(0, 0);
            tableLayoutPanel1.AutoScroll = false;
            tableLayoutPanel1.AutoSize = true;
            tableLayoutPanel1.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            Controls.Add(tableLayoutPanel1);
        }
        #endregion

        #region Private Methods
        private void Deinitialize()
        {
            tableLayoutPanel1.Visible = false;
            tableLayoutPanel1.Controls.Clear();
            tableLayoutPanel1.Height = 0;
        }
        private void Initialize()
        {
            tableLayoutPanel1.Controls.Clear();
            
            int row = 0;
            AddLabelForProperty("Name", row);
            row = AddNameProperty(row);
            foreach (Verkstan.OperatorBindingProperty property in op.Properties)
            {
                AddLabelForProperty(property.Name, row);
                if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Byte)
                    row = AddByteProperty(property, row);
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Int)
                    row = AddIntProperty(property, row);
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Float)
                    row = AddFloatProperty(property, row);
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.String)
                    row = AddStringProperty(property, row);
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Text)
                    row = AddTextProperty(property, row);
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Color)
                    row = AddColorProperty(property, row);
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Vector)
                    row = AddVectorProperty(property, row);
                else if (property.Type == Verkstan.Constants.OperatorPropertyTypes.Enum)
                    row = AddEnumProperty(property, row);                
            }

            // Add a dummy label at the end of the table. If we don't
            // then the last line of the properties will use the rest of the
            // space and end up too big.
            Label dummyLabel = new Label();
            dummyLabel.Width = 1;
            dummyLabel.Visible = false;
            tableLayoutPanel1.Controls.Add(dummyLabel);
            tableLayoutPanel1.SetCellPosition(dummyLabel, new TableLayoutPanelCellPosition(0, row));
            tableLayoutPanel1.Visible = true;
             
        }
        private void AddLabelForProperty(String text, int row)
        {
            Label label = new Label();
            label.AutoSize = true;
            label.Size = new Size(0, 0);
            label.Text = text;
            label.Dock = DockStyle.Right;
            label.TextAlign = ContentAlignment.MiddleCenter;
            label.Font = new Font(label.Font, FontStyle.Bold);
            label.Margin = new Padding(1, 1, 10, 1);
            // It is important to add the label to the table before we check it's size
            // as the auto size isn't done until the label is added to a control.
            tableLayoutPanel1.Controls.Add(label);
            tableLayoutPanel1.SetCellPosition(label, new TableLayoutPanelCellPosition(0, row));
        }
        private int AddByteProperty(Verkstan.OperatorBindingProperty property, int row)
        {
         
            int index = property.Index;
            NumericUpDown numericUpDown = new NumericUpDown();
            numericUpDown.Margin = new Padding(0, 1, 0, 1);
            numericUpDown.Increment = 1;
            numericUpDown.Minimum = 0;
            numericUpDown.Maximum = 255;
            numericUpDown.Value = (int)op.GetByteProperty(index);
            numericUpDown.Width = 50;
            numericUpDown.ValueChanged += new EventHandler((object o, EventArgs e) => op.SetByteProperty(index, (byte)numericUpDown.Value));
            tableLayoutPanel1.Controls.Add(numericUpDown);
            tableLayoutPanel1.SetCellPosition(numericUpDown, new TableLayoutPanelCellPosition(1, row));
            return row + 1;

        }
        private int AddIntProperty(Verkstan.OperatorBindingProperty property, int row)
        {          
            int index = property.Index;
            NumericUpDown numericUpDown = new NumericUpDown();
            numericUpDown.Margin = new Padding(0, 1, 0, 1);
            numericUpDown.Increment = 1;
            numericUpDown.Minimum = int.MinValue;
            numericUpDown.Maximum = int.MaxValue;
            numericUpDown.Value = op.GetIntProperty(index);
            numericUpDown.Width = 100;
            numericUpDown.ValueChanged += new EventHandler((object o, EventArgs e) => op.SetIntProperty(index, (int)numericUpDown.Value));
            tableLayoutPanel1.Controls.Add(numericUpDown);
            tableLayoutPanel1.SetCellPosition(numericUpDown, new TableLayoutPanelCellPosition(1, row));
            return row + 1;
        }
        private int AddFloatProperty(Verkstan.OperatorBindingProperty property, int row)
        {
            int index = property.Index;
            NumericUpDown numericUpDown = new NumericUpDown();
            numericUpDown.Margin = new Padding(0, 1, 0, 1);
            numericUpDown.Increment = 0.001M;
            numericUpDown.DecimalPlaces = 3;
            numericUpDown.Minimum = decimal.MinValue;
            numericUpDown.Maximum = decimal.MaxValue;
            numericUpDown.Value = Convert.ToDecimal(op.GetFloatProperty(index));
            numericUpDown.Width = 100;
            numericUpDown.ValueChanged += new EventHandler((object o, EventArgs e) => op.SetFloatProperty(index, Convert.ToSingle(numericUpDown.Value)));
            tableLayoutPanel1.Controls.Add(numericUpDown);
            tableLayoutPanel1.SetCellPosition(numericUpDown, new TableLayoutPanelCellPosition(1, row));
            return row + 1;
        }
        private int AddStringProperty(Verkstan.OperatorBindingProperty property, int row)
        {
            int index = property.Index;
            TextBox textBox = new TextBox();
            textBox.Margin = new Padding(0, 1, 0, 1);
            textBox.Dock = DockStyle.Fill;
            textBox.Text = op.GetStringProperty(index);
            textBox.TextChanged += new EventHandler((object o, EventArgs e) => op.SetStringProperty(index, textBox.Text));
            tableLayoutPanel1.Controls.Add(textBox);
            tableLayoutPanel1.SetCellPosition(textBox, new TableLayoutPanelCellPosition(1, row));
            return row + 1;
        }
        private int AddNameProperty(int row)
        {
            TextBox textBox = new TextBox();
            textBox.Margin = new Padding(0, 1, 0, 1);
            textBox.Dock = DockStyle.Fill;
            textBox.Text = op.Name;
            textBox.TextChanged += new EventHandler((object o, EventArgs e) => op.Name = textBox.Text);
            tableLayoutPanel1.Controls.Add(textBox);
            tableLayoutPanel1.SetCellPosition(textBox, new TableLayoutPanelCellPosition(1, row));
            return row + 1;
        }
        private int AddTextProperty(Verkstan.OperatorBindingProperty property, int row)
        {
            int index = property.Index;
            TextBox textBox = new TextBox();
            textBox.Margin = new Padding(0, 1, 0, 1);
            textBox.AcceptsReturn = true;
            textBox.AcceptsTab = true;
            textBox.Multiline = true;
            textBox.Height = 200;
            textBox.WordWrap = true;
            textBox.Dock = DockStyle.Fill;
            textBox.Text = op.GetStringProperty(index);
            textBox.TextChanged += new EventHandler((object o, EventArgs e) => op.SetStringProperty(index, textBox.Text));
            tableLayoutPanel1.Controls.Add(textBox);
            tableLayoutPanel1.SetCellPosition(textBox, new TableLayoutPanelCellPosition(1, row));
            return row + 1;
        }
        private int AddVectorProperty(Verkstan.OperatorBindingProperty property, int row)
        {
            int index = property.Index;
            VectorProperty vectorProperty = new VectorProperty();
            vectorProperty.Margin = new Padding(0, 1, 0, 1);
            Verkstan.Vector vector = op.GetVectorProperty(index);
            vectorProperty.X = vector.X;
            vectorProperty.Y = vector.Y;
            vectorProperty.Z = vector.Z;
            vectorProperty.ValueChanged += delegate(object o, EventArgs e)
            {
                op.SetVectorProperty(index, new Verkstan.Vector(vectorProperty.X, vectorProperty.Y, vectorProperty.Z));
            };

            tableLayoutPanel1.Controls.Add(vectorProperty);
            tableLayoutPanel1.SetCellPosition(vectorProperty, new TableLayoutPanelCellPosition(1, row));
            return row + 1;
        }
        private int AddColorProperty(Verkstan.OperatorBindingProperty property, int row)
        {
            int index = property.Index;
            ColorProperty colorProperty = new ColorProperty();
            colorProperty.Margin = new Padding(0, 1, 0, 1);
            colorProperty.Color = op.GetColorProperty(index);
            colorProperty.ColorChanged += delegate(object o, EventArgs e)
            {
                op.SetColorProperty(index, colorProperty.Color);
            };

            tableLayoutPanel1.Controls.Add(colorProperty);
            tableLayoutPanel1.SetCellPosition(colorProperty, new TableLayoutPanelCellPosition(1, row));
            return row + 1;
        }
        private int AddEnumProperty(Verkstan.OperatorBindingProperty property, int row)
        {
            int index = property.Index;
            List<String> enumValues = property.EnumValues;
            ComboBox comboBox = new ComboBox();
            comboBox.Margin = new Padding(0, 1, 0, 1);
            comboBox.DropDownStyle = ComboBoxStyle.DropDownList;

            foreach (String value in enumValues)
                comboBox.Items.Add(value);

            int enumValueIndex = op.GetByteProperty(index);
            comboBox.Text = enumValues[enumValueIndex];

            comboBox.SelectedValueChanged += delegate(object o, EventArgs e)
            {
                op.SetByteProperty(index, (byte)comboBox.SelectedIndex);
            };

            tableLayoutPanel1.Controls.Add(comboBox);
            tableLayoutPanel1.SetCellPosition(comboBox, new TableLayoutPanelCellPosition(1, row));
            return row + 1;
        }
        #endregion

        #region Event Handlers
        private void OperatorPropertyTable_MouseDown(object sender, MouseEventArgs e)
        {
            tableLayoutPanel1.Focus();
        }
        private void OperatorProperty_MouseDown(object sender, MouseEventArgs e)
        {
            tableLayoutPanel1.Focus();
        }
        private void OperatorProperty_LabelMouseDown(object sender, MouseEventArgs e)
        {
            tableLayoutPanel1.Focus();
        }
        #endregion
    }
}
