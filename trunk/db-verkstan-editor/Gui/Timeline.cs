using System;
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
    public partial class Timeline : UserControl
    {
        private Verkstan.SceneOperator scene;
        public Timeline()
        {
            InitializeComponent();
            this.MouseWheel += new MouseEventHandler(Timeline_MouseWheel);
            timelineChannels1.ChannelSelected += new TimelineChannels.ChannelSelectedHandler(this.timelineChannels1_ChannelSelected);
            scene = (Verkstan.SceneOperator)Verkstan.OperatorFactory.Create("Scene");
            timelineChannels1.Scene = scene;
            Metronome.Beats = scene.Beats;
            Metronome.LoopStart = 0;
            Metronome.LoopEnd = scene.Beats;
        }

        private void timelineChannels1_Resize(object sender, EventArgs e)
        {
            UpdateScrollBars();
            beatPositionLine1.Width = timelineChannels1.Width;
        }

        private void UpdateScrollBars()
        {
            hScrollBar1.Enabled = timelineChannels1.Width > splitPositionAndChannels.Panel2.Width;
            vScrollBar1.Enabled = timelineChannels1.Height > splitPositionAndChannels.Panel2.Height;

            hScrollBar1.Minimum = 0;
            hScrollBar1.Maximum = timelineChannels1.Width;
            hScrollBar1.LargeChange = splitPositionAndChannels.Panel2.Width;
            hScrollBar1.SmallChange = 10;
          
            vScrollBar1.Minimum = 0;
            vScrollBar1.Maximum = timelineChannels1.Height;
            vScrollBar1.LargeChange = splitPositionAndChannels.Panel2.Height;
            vScrollBar1.SmallChange = 10;


            if (!hScrollBar1.Enabled)
            {
                timelineChannels1.Left = 0;
                beatPositionLine1.Left = 0;
            }

            if (!vScrollBar1.Enabled)
            {
                timelineChannels1.Top = 0;
                timelineChannelInfos1.Top = 0;
            }
        }

        private void timelineChannels1_Load(object sender, EventArgs e)
        {
           UpdateScrollBars();
        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            timelineChannels1.Left = -e.NewValue;
            beatPositionLine1.Left = -e.NewValue;
        }

        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            timelineChannels1.Top = -e.NewValue;
            timelineChannelInfos1.Top = -e.NewValue;
        }

        private void Timeline_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
            {
                if (vScrollBar1.Value - vScrollBar1.SmallChange > vScrollBar1.Minimum)
                    vScrollBar1.Value -= vScrollBar1.SmallChange;
                else
                    vScrollBar1.Value = vScrollBar1.Minimum;
            }
            else
            {
                if (vScrollBar1.Value + vScrollBar1.SmallChange < (vScrollBar1.Maximum - vScrollBar1.LargeChange + 1))
                    vScrollBar1.Value += vScrollBar1.SmallChange;
                else
                    vScrollBar1.Value = vScrollBar1.Maximum - vScrollBar1.LargeChange + 1;
            }

            timelineChannels1.Top = -vScrollBar1.Value;
            timelineChannelInfos1.Top = -vScrollBar1.Value;
        }

        private void timelineChannels1_ChannelSelected(int index)
        {

        }
    }
}
