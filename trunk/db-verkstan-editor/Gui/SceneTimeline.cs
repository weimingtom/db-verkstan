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
        public int PlayerPosition
        {
            set
            {
                playerPositionLine1.PlayerPosition = value;
                channels1.PlayerPosition = value;
            }
        }

        public SceneTimeline()
        {
            InitializeComponent();
            playerPositionLine1.Beats = 40;
            channels1.Beats = 40;
        }

        private void channels1_LocationChanged(object sender, EventArgs e)
        {
            playerPositionLine1.Location = new Point(channels1.Location.X, 0);
            channelInfos1.Location = new Point(0, channels1.Location.Y);
        }

        public class PlayerPositionChangedEventArgs : EventArgs
        {
            public int Position;
            public PlayerPositionChangedEventArgs(int position)
            {
                Position = position;
            }
        }

        public delegate void PlayerPositionChangedHandler(object sender, PlayerPositionChangedEventArgs e);
        [Browsable(true)]
        [Description("Event fired when the player position has changed by the user.")]
        [Editor(typeof(PlayerPositionChangedHandler), typeof(UITypeEditor))]
        public event PlayerPositionChangedHandler PlayerPositionChanged;

        public void OnPlayerPositionChanged(object sender, PlayerPositionChangedEventArgs e)
        {
            if (PlayerPositionChanged != null)
                PlayerPositionChanged(sender, e);
        }

        private void playerPositionLine1_PlayerPositionChanged(object sender, PlayerPositionLine.PlayerPositionChangedEventArgs e)
        {
            OnPlayerPositionChanged(this, new PlayerPositionChangedEventArgs(e.Position));
        }
    }
}
