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
            channelEditor1.ClipEditRequested += new ChannelEditor.ClipEditRequest(channelEditor1_ClipEditRequested); 
        }

        void channelEditor1_ClipEditRequested(VorlonSeq.Seq.Clip clip)
        {
            clipEditor1.Clip = clip;
            tabControl1.SelectTab(1);
        }

        private void framesPerTickUpDown_ValueChanged(object sender, EventArgs e)
        {
            Seq.Sequencer.FramesPerTick = (int)framesPerTickUpDown.Value;
            bpmLabel.Text = "= " + Seq.Sequencer.BPM + " BPM";
        }

        private void mainWindow_FormClosed(object sender, FormClosedEventArgs e)
        {
            Seq.Sequencer.StopVorlon();
        }

        private void playButton_Click(object sender, EventArgs e)
        {
            Seq.Sequencer.IsPlaying = !Seq.Sequencer.IsPlaying;
        }

        private void rewindButton_Click(object sender, EventArgs e)
        {
            Seq.Sequencer.PlayPosition = 0;
        }
    }
}
