﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using VerkstanEditor.Logic;

namespace VerkstanEditor.Gui
{
    public partial class MainForm : Form
    {
        #region Private Variables
        private Verkstan.Window verkstanWindow;
        private OperatorPage page;
        private Operator viewedOperator;
        #endregion

        #region Constructor
        public MainForm()
        {
            InitializeComponent();
            verkstanWindow = new Verkstan.Window();
            verkstanWindow.ClearColor = Color.DarkCyan.ToArgb();
           // Operators.ViewedOperatorChanged += new Operators.ViewedOperatorChangedHandler(this.Operators_ViewedOperatorChanged); 
           // Operators.ViewedOperatorPropertiesChanged += new Operators.ViewedOperatorPropertiesChangedHandler(this.Operators_ViewedOperatorPropertiesChanged);

            unsafe
            {
                verkstanWindow.Boot(previewPanel.Handle.ToPointer());
            }

            fastRenderTimer.Enabled = true;
            slowRenderTimer.Enabled = true;

            page = new OperatorPage();
            operatorPageView1.Page = page;
        }
        #endregion

        #region Event Handlers
        private void FastRenderTimer_Tick(object sender, EventArgs e)
        {
            if (viewedOperator != null && viewedOperator.IsProcessable)
                verkstanWindow.ViewedOperator = viewedOperator.BindedCoreOperator;

            if (viewedOperator == null || !viewedOperator.IsProcessable)
                verkstanWindow.ViewedOperator = null;

            verkstanWindow.Render();
           
            /*
           Metronome.OnBeatChangedFastUpdate(Metronome.Beat);
            */
        }
        private void PreviewPanel_SizeChanged(object sender, EventArgs e)
        {
            if (verkstanWindow != null)
                verkstanWindow.Resize();
        }
        private void Operators_ViewedOperatorPropertiesChanged(Operator op)
        {
            operatorPropertyGrid.Operator = op;
        }
        private void Operators_ViewedOperatorChanged(Operator op)
        {
            /*
            if (op == null)
                verkstanWindow.ViewedOperator = null;
            else
                verkstanWindow.ViewedOperator = op.Binding;*/
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
        private void slowRenderTimer_Tick(object sender, EventArgs e)
        {
            //Metronome.OnBeatChangedSlowUpdate(Metronome.Beat);
        }
        private void operatorPageView1_ViewedOperatorChanged(object sender, EventArgs e)
        {
            viewedOperator = operatorPageView1.ViewedOperator;
        }
        private void operatorPageView1_ViewedOperatorPropertiesChanged(object sender, EventArgs e)
        {
            operatorPropertyGrid.Operator = operatorPageView1.ViewedOperatorProperties;
        }
        #endregion
    }
}
