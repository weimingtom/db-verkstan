using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Midi;

namespace VorlonSeq
{
    public partial class mainWindow : Form
    {
        MidiInDevice.MidiInHandler handlerKeepalive;
        MidiInDevice midiDevice = null;
        int selectedTab = 0;

        public mainWindow()
        {
            handlerKeepalive = new MidiInDevice.MidiInHandler(OnMidiInput);
            InitializeComponent();
            framesPerTickUpDown_ValueChanged(null, null);
            channelEditor1.ClipEditRequested += new ChannelEditor.ClipEditRequest(channelEditor1_ClipEditRequested);

            int i = 0;
            MidiInDevice firstDevice = null;
            foreach(MidiInDevice device in MidiInDevice.EnumerateDevices()) {
                if (firstDevice == null)
                {
                    firstDevice = device;
                }
                ToolStripMenuItem item = new ToolStripMenuItem(device.Name);
                item.Tag = device;
                item.DropDownItemClicked += midiToolStripMenuItem_DropDownItemClicked;
                midiToolStripMenuItem.DropDownItems.Insert(i++, item);
            }

            if (firstDevice != null)
            {
                SwitchToMidiDevice(firstDevice);
            }
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
            SwitchToMidiDevice(null);
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

        private void midiToolStripMenuItem_DropDownItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            SwitchToMidiDevice((MidiInDevice)e.ClickedItem.Tag);
        }

        private void SwitchToMidiDevice(MidiInDevice device)
        {
            foreach (ToolStripItem item in midiToolStripMenuItem.DropDownItems)
            {
                if (item is ToolStripMenuItem)
                {
                    ((ToolStripMenuItem)item).Checked = (item.Tag == device);
                }
            }

            if (midiDevice != null)
            {
                midiDevice.Stop();
                midiDevice.Close();
            }

            midiDevice = device;

            if (midiDevice != null)
            {
                midiDevice.Open(handlerKeepalive);
                midiDevice.Start();
            }
        }

        void OnMidiInput(MidiInDevice sender, MidiMessage message)
        {
            if (selectedTab == 0)
            {
                channelEditor1.OnMidiInput(message);                
            }
            else
            {
                clipEditor1.OnMidiInput(message);
            }
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {
            selectedTab = tabControl1.SelectedIndex;
        }
    }
}
