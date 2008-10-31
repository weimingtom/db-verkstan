using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Design;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class SceneTimeline : UserControl
    {
        public SceneTimeline()
        {
            InitializeComponent();
        }

        private void channels1_LocationChanged(object sender, EventArgs e)
        {
            playerPositionLine1.Location = new Point(channels1.Location.X, 0);
            channelInfos1.Location = new Point(0, channels1.Location.Y);
        }
    }
}
