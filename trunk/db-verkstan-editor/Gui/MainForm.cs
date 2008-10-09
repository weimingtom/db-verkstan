using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using VerkstanBindings;

namespace VerkstanEditor.Gui
{
    public partial class mainForm : Form
    {
        operatorPage operatorPage = new operatorPage();
        OperatorProperty operatorProperty = new OperatorProperty();

        public mainForm()
        {
            InitializeComponent();
            VerkstanBindings.CoreBinding.ClearColor = Color.DarkCyan.ToArgb();
            Operators.ViewedOperatorChanged += new Operators.ViewedOperatorChangedHandler(this.OperatorPage_ViewedOperatorChanged); 
            Operators.ViewedOperatorPropertiesChanged += new Operators.ViewedOperatorPropertiesChangedHandler(this.OperatorPage_ViewedOperatorPropertiesChanged);
            operatorsPropertiesSplitContainer.Panel1.Controls.Add(operatorPage);
            operatorsPropertiesSplitContainer.Panel2.Controls.Add(operatorProperty);
            operatorProperty.Dock = DockStyle.Fill;
            operatorsPropertiesSplitContainer.Panel1.VerticalScroll.SmallChange = 40;
            operatorsPropertiesSplitContainer.Panel1.VerticalScroll.LargeChange = 40;

            unsafe
            {
                VerkstanBindings.CoreBinding.Boot(previewPanel.Handle.ToPointer());
            }

            renderTimer.Enabled = true;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {

        }

        private void RenderTimer_Tick(object sender, EventArgs e)
        {
            VerkstanBindings.CoreBinding.Render();
        }

        private void PreviewPanel_SizeChanged(object sender, EventArgs e)
        {
            VerkstanBindings.CoreBinding.Resize();
        }

        private void TransportPanel_SizeChanged(object sender, EventArgs e)
        {
            transportTimeLabel.Location = new Point(transportPanel.Width / 2 - transportTimeLabel.Width / 2, 0);        
        }

        private void OperatorPage_ViewedOperatorPropertiesChanged(Operator op)
        {
            operatorProperty.Operator = op;
        }

        private void OperatorPage_ViewedOperatorChanged(Operator op)
        {
            if (op == null)
                VerkstanBindings.CoreBinding.ViewedOperatorBinding = null;
            else
                VerkstanBindings.CoreBinding.ViewedOperatorBinding = op.Binding;
        }
    }
}
