using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using VorlonSeq.Seq;

namespace VorlonSeq
{
    public partial class PianoRoll : UserControl
    {        
        const int numKeys = 127;
        int keyHeight = 6;
        int pixelsPerTick = 10;
        public Clip Clip;

        public PianoRoll()
        {
            InitializeComponent();

            this.SetStyle(
                ControlStyles.AllPaintingInWmPaint |
                ControlStyles.UserPaint |
                ControlStyles.DoubleBuffer, true);
            
            Refresh();
        }

        private void PianoRoll_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;

            for (int i = 0; i < numKeys; i++)
            {
                int key = numKeys - i - 1;
                int y = i * keyHeight;
                bool blackKey = (key % 12 == 2 || key % 12 == 4 || key % 12 == 7 || key % 12 == 9 || key % 12 == 11);
                g.FillRectangle(blackKey ? Brushes.Silver : Brushes.LightGray, new Rectangle(0, y, Width, keyHeight - 1));
            }

            for (int x = 0; x < Width; x += pixelsPerTick)
            {
                g.DrawLine(Pens.White, new Point(x, 0), new Point(x, Height));
                
                if ((x / pixelsPerTick) % 4 == 0)
                {
                    g.DrawLine(Pens.White, new Point(x - 1, 0), new Point(x - 1, Height));
                }

                if ((x / pixelsPerTick) % 16 == 0)
                {
                    g.DrawLine(Pens.White, new Point(x + 1, 0), new Point(x + 1, Height));
                }
            }

            if (Clip != null)
            {                
                foreach(Clip.NoteEvent note in Clip.NoteEvents)
                {
                    int i = numKeys - note.Note - 1;
                    int y = i * keyHeight;
                    int h = keyHeight;
                    int x = note.StartTime * pixelsPerTick;
                    int w = note.Length * pixelsPerTick;
                    g.FillRectangle(Brushes.RosyBrown, new Rectangle(x, y, w, h));
                    g.DrawRectangle(Pens.Black, new Rectangle(x, y, w, h));
                }
            }
        }

        private void PianoRoll_Layout(object sender, LayoutEventArgs e)
        {
            Size = new Size(Width, numKeys * keyHeight);
        }
    }
}
