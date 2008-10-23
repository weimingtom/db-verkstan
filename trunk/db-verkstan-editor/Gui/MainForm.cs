using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VerkstanEditor.Gui
{
    public partial class mainForm : Form
    {
        operatorPage operatorPage = new operatorPage();
        OperatorProperty operatorProperty = new OperatorProperty();
        Verkstan.Window verkstanWindow;

        public mainForm()
        {
            InitializeComponent();
            verkstanWindow = new Verkstan.Window();
            verkstanWindow.ClearColor = Color.DarkCyan.ToArgb();
            Operators.ViewedOperatorChanged += new Operators.ViewedOperatorChangedHandler(this.OperatorPage_ViewedOperatorChanged); 
            Operators.ViewedOperatorPropertiesChanged += new Operators.ViewedOperatorPropertiesChangedHandler(this.OperatorPage_ViewedOperatorPropertiesChanged);
            splitContainer3.Panel2.Controls.Add(operatorPage);
            splitContainer4.Panel1.Controls.Add(operatorProperty);
            operatorProperty.Dock = DockStyle.Fill;

            unsafe
            {
                verkstanWindow.Boot(previewPanel.Handle.ToPointer());
            }

            renderTimer.Enabled = true;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {

        }

        private void RenderTimer_Tick(object sender, EventArgs e)
        {
            verkstanWindow.Render();
        }

        private void PreviewPanel_SizeChanged(object sender, EventArgs e)
        {
            if (verkstanWindow != null)
                verkstanWindow.Resize();
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
                verkstanWindow.ViewedOperator = null;
            else
                verkstanWindow.ViewedOperator = op.Binding;
        }

        private void previewPanel_MouseDown(object sender, MouseEventArgs e)
        {
            int button = 0;

            if (e.Button == MouseButtons.Left)
                button = 1;
            else if (e.Button == MouseButtons.Middle)
                button = 2;
            else if (e.Button == MouseButtons.Right)
                button = 3;

            verkstanWindow.MouseDown(button, e.X, e.Y);
        }

        private void previewPanel_MouseUp(object sender, MouseEventArgs e)
        {
            int button = 0;

            if (e.Button == MouseButtons.Left)
                button = 1;
            else if (e.Button == MouseButtons.Middle)
                button = 2;
            else if (e.Button == MouseButtons.Right)
                button = 3;

            verkstanWindow.MouseUp(button, e.X, e.Y);
        }

        private void previewPanel_MouseMove(object sender, MouseEventArgs e)
        {
            verkstanWindow.MouseMove(e.X, e.Y);
        }
    }
}
