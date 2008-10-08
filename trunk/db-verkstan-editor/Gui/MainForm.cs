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

            operatorPage.OperatorSelected += new operatorPage.OperatorSelectedHandler(this.OperatorPage_OperatorSelected);
            operatorPage.OperatorPreview += new operatorPage.OperatorPreviewHandler(this.OperatorPage_OperatorPreview); 
            operatorsPropertiesSplitContainer.Panel1.Controls.Add(operatorPage);
            operatorsPropertiesSplitContainer.Panel2.Controls.Add(operatorProperty);
            operatorProperty.Dock = DockStyle.Fill;
            operatorsPropertiesSplitContainer.Panel1.VerticalScroll.SmallChange = 40;
            operatorsPropertiesSplitContainer.Panel1.VerticalScroll.LargeChange = 40;

            unsafe
            {
                VerkstanBindings.CoreBinding.Boot(previewPanel.Handle.ToPointer());
            }


            
            /*
            OperatorBinding o = new OperatorBinding(OperatorBinding.Names.Text);
       
        o.SetProperty(0, 0xffffffff);
        o.SetProperty(1, (char)50);
        o.SetProperty(2, (char)0);
        o.SetProperty(3, (char)0);
        o.SetProperty(4, "Verdana");
        o.SetProperty(5, "Darkbits!");*/
           

          
         /*
            OperatorDelegate o = new OperatorDelegate(OperatorDelegate.Id.PIXELS);

            
            o.SetProperty(0, 255);
            o.SetProperty(1, 255);
            o.SetProperty(2, 255);
            o.SetProperty(3, 255);
            o.SetProperty(4, 512);
            o.SetProperty(5, 10);*/

            //VerkstanBindings.CoreBinding.SetPreview(o);
   
           
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

        private void OperatorPage_OperatorSelected(Operator op)
        {
            operatorProperty.Operator = op;
        }

        private void OperatorPage_OperatorPreview(Operator op)
        {
            VerkstanBindings.CoreBinding.SetPreview(op.Binding);
        }
    }
}
