using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VerkstanEditor.Gui
{
    public partial class OperatorProperty : UserControl 
    {
        private Operator op;

        public Operator Operator
        {
            set
            {
                op = value;
                Deinitialize();
                Initialize();
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
            List<VerkstanBindings.OperatorBindingProperty> properties = op.Binding.Properties;

           OperatorPropertyTable.RowCount = properties.Count;
           int row = 0;
           foreach (VerkstanBindings.OperatorBindingProperty property in properties)
           {
               Label label = new Label();
               label.MouseDown += new System.Windows.Forms.MouseEventHandler(this.OperatorProperty_LabelMouseDown);
               label.Text = property.Name;
               label.Dock = DockStyle.Left;
               label.Font = new Font(label.Font, FontStyle.Bold);
               label.TextAlign = ContentAlignment.MiddleRight;

               OperatorPropertyTable.Controls.Add(label);
               OperatorPropertyTable.SetCellPosition(label, new TableLayoutPanelCellPosition(0, row));

               if (property.Type == VerkstanBindings.Constants.OperatorPropertyTypes.Byte)
               {
                   NumericUpDown numericUpDown = new NumericUpDown();
                   numericUpDown.Increment = 1;
                   numericUpDown.Minimum = 0;
                   numericUpDown.Maximum = 255;
                   numericUpDown.Value = (int)op.Binding.GetByteProperty(property.Index);
                   numericUpDown.Width = 50;
                   int index = property.Index;
                   numericUpDown.ValueChanged += new EventHandler((object o, EventArgs e) => op.Binding.SetByteProperty(index, (byte)numericUpDown.Value));
                   OperatorPropertyTable.Controls.Add(numericUpDown);
                   OperatorPropertyTable.SetCellPosition(numericUpDown, new TableLayoutPanelCellPosition(1, row));
               }
               else if (property.Type == VerkstanBindings.Constants.OperatorPropertyTypes.Int)
               {
                   NumericUpDown numericUpDown = new NumericUpDown();
                   numericUpDown.Increment = 1;
                   numericUpDown.Minimum = int.MinValue;
                   numericUpDown.Maximum = int.MaxValue;
                   numericUpDown.Value = op.Binding.GetIntProperty(property.Index);
                   numericUpDown.Width = 100;
                   int index = property.Index;
                   numericUpDown.ValueChanged += new EventHandler((object o, EventArgs e) => op.Binding.SetIntProperty(index, (int)numericUpDown.Value));
                   OperatorPropertyTable.Controls.Add(numericUpDown);
                   OperatorPropertyTable.SetCellPosition(numericUpDown, new TableLayoutPanelCellPosition(1, row));
               }
               else if (property.Type == VerkstanBindings.Constants.OperatorPropertyTypes.String)
               {
                   TextBox textBox = new TextBox();
                   textBox.Dock = DockStyle.Fill;
                   textBox.Text = op.Binding.GetStringProperty(property.Index);
                   int index = property.Index;
                   textBox.TextChanged += new EventHandler((object o, EventArgs e) => op.Binding.SetStringProperty(index, textBox.Text));
                   OperatorPropertyTable.Controls.Add(textBox);
                   OperatorPropertyTable.SetCellPosition(textBox, new TableLayoutPanelCellPosition(1, row));
               }
               else if (property.Type == VerkstanBindings.Constants.OperatorPropertyTypes.Text)
               {
                   TextBox textBox = new TextBox();
                   textBox.AcceptsReturn = true;
                   textBox.AcceptsTab = true;
                   textBox.Multiline = true;
                   textBox.Height = 200;
                   textBox.WordWrap = true;
                   textBox.Dock = DockStyle.Fill;
                   textBox.Text = op.Binding.GetStringProperty(property.Index);
                   int index = property.Index;
                   textBox.TextChanged += new EventHandler((object o, EventArgs e) => op.Binding.SetStringProperty(index, textBox.Text));
                   OperatorPropertyTable.Controls.Add(textBox);
                   OperatorPropertyTable.SetCellPosition(textBox, new TableLayoutPanelCellPosition(1, row));
               }
               else if (property.Type == VerkstanBindings.Constants.OperatorPropertyTypes.Color)
               {
                   ColorProperty colorProperty = new ColorProperty();
                   colorProperty.Color = Color.FromArgb(op.Binding.GetIntProperty(property.Index));
                   int index = property.Index;
                   colorProperty.ColorChanged += new EventHandler((object o, EventArgs e) => op.Binding.SetIntProperty(index, colorProperty.Color.ToArgb()));
                   OperatorPropertyTable.Controls.Add(colorProperty);
                   OperatorPropertyTable.SetCellPosition(colorProperty, new TableLayoutPanelCellPosition(1, row));
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

        public OperatorProperty()
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
