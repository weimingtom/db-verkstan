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
    public partial class ClipView : UserControl
    {
        #region Properties
        private Clip clip;
        public Clip Clip
        {
            get
            {
                return clip;
            }
            set
            {
                clip = value;
                
                if (clip == null)
                {
                    generatorClipPropertiesView1.Visible = false;
                    generatorClipValueView1.Visible = false;
                }       
                else if (clip.GetType() == typeof(GeneratorClip))
                {
                    generatorClipPropertiesView1.GeneratorClip = (GeneratorClip)clip;
                    generatorClipValueView1.GeneratorClip = (GeneratorClip)clip;
                    generatorClipPropertiesView1.Visible = true;
                    generatorClipValueView1.Visible = true;
                    generatorClipValueView1.BeatWidth = Convert.ToInt32(numericUpDown1.Value);
                }
            }
        }
        #endregion

        #region Constructor
        public ClipView()
        {
            InitializeComponent();
        }
        #endregion

        #region Event Handlers
        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            generatorClipValueView1.BeatWidth = Convert.ToInt32(numericUpDown1.Value);
        }
        #endregion
    }
}
