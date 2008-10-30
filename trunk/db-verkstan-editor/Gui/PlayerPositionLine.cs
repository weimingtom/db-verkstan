using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Drawing.Design;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class PlayerPositionLine : UserControl
    {
        private int beats = 4;
        public int Beats
        {
            set
            {
                beats = value;
                UpdateSize();
            }
            get
            {
                return beats;
            }
        }

        [Browsable(true)]
        [Description("The width of a beat in pixels.")]
        [Editor(typeof(int), typeof(UITypeEditor))]
        [DefaultValue(16)]
        private int beatWidth;
        public int BeatWidth
        {
            set
            {
                beatWidth = value;
                Refresh();
            }
            get
            {
                return beatWidth;
            }

        }
        private int playerPosition = 0;
        public int PlayerPosition
        {
            set
            {
                playerPosition = value;
                Refresh();
            }
            get
            {
                return playerPosition;
            }
        }

        public PlayerPositionLine()
        {
            InitializeComponent();
            UpdateSize();
        }

        private void UpdateSize()
        {
            Size = new Size(beats * beatWidth, 25);
        }

        private void PlayerPositionLine_Paint(object sender, PaintEventArgs e)
        {
            Brush b = new SolidBrush(ForeColor);
            Pen p = new Pen(Color.FromArgb(100, 100, 100), 1);
            for (int i = 0; i < Beats; i++)
            {
                if (i % 2 == 0)
                {
                    e.Graphics.DrawLine(p, new Point(i * BeatWidth, 0), new Point(i * BeatWidth, 24));
                    e.Graphics.DrawString("" + (i + 1), Font, b, new Point(i * BeatWidth + 1, 0));
                }
                else
                    e.Graphics.DrawLine(p, new Point(i * BeatWidth, 20), new Point(i * BeatWidth, 24));
            }
            p.Dispose();
            b.Dispose();

            p = new Pen(Color.FromArgb(255, 0, 0), 1);
            int playerPositionInPixels = (int)(BeatWidth * (PlayerPosition / (float)Verkstan.Timer.GetTicksPerBeat()));
            e.Graphics.DrawLine(p, new Point(playerPositionInPixels, 0), new Point(playerPositionInPixels, 25));
            p.Dispose();
        }

        private void PlayerPositionLine_Load(object sender, EventArgs e)
        {
            UpdateSize();
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

        private void PlayerPositionLine_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                int newBeat = (int)((e.X / (float)beatWidth) * Verkstan.Timer.GetTicksPerBeat());
                OnPlayerPositionChanged(this, new PlayerPositionChangedEventArgs(newBeat));
            }
        }
    }
}
