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
    public partial class TimelinesView : UserControl
    {
        #region Constructors
        public TimelinesView()
        {
            InitializeComponent();
        }
        #endregion

        #region Event Handlers
        private void moveButton_Click(object sender, EventArgs e)
        {
            selectedToolLabel.Text = "Move Tool Selected";
            timelineView1.Mode = TimelineChannelsView.Modes.Move;
        }
        private void generatorButton_Click(object sender, EventArgs e)
        {
            selectedToolLabel.Text = "Generator Drawing Tool Selected";
            timelineView1.Mode = TimelineChannelsView.Modes.DrawGenerator;
        }
        private void splineButton_Click(object sender, EventArgs e)
        {
            selectedToolLabel.Text = "Spline Drawing Tool Selected";
            timelineView1.Mode = TimelineChannelsView.Modes.DrawSpline;
        }
        #endregion
    }
}
