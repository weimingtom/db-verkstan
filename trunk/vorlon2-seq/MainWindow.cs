using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VorlonSeq
{
    public partial class mainWindow : Form
    {
        public mainWindow()
        {
            InitializeComponent();
            framesPerTickUpDown_ValueChanged(null, null);
        }

        private void framesPerTickUpDown_ValueChanged(object sender, EventArgs e)
        {
            Seq.Sequencer.FramesPerTick = (int)framesPerTickUpDown.Value;
            bpmLabel.Text = "= " + Seq.Sequencer.BPM + " BPM";
        }
    }
}
