using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace VerkstanEditor.Logic
{
    class ClipPreviewCache
    {
        public static Bitmap GetPreview(Verkstan.Clip clip, int beatWidth, int height)
        {
            int width = (clip.End - clip.Start) / Metronome.TicksPerBeat * beatWidth;
            Bitmap preview = new Bitmap(width, height);
            Graphics g = Graphics.FromImage(preview);

            int clipLength = (clip.End - clip.Start);
            int middle = height / 2 - 1;

            float v = clip.GetValue(0);
            int lastX = 0;
            int lastY = (int)(middle -  v * middle);
            preview.SetPixel(lastX, lastY, Color.Black);

            for (int x = 1; x < width; x++)
            {
                int beat = (int)((x / (float)width) * clipLength);
                float value = clip.GetValue(beat);
                int y = (int)(middle - value * middle);
                g.DrawLine(Pens.Black, lastX, lastY, x, y);
                preview.SetPixel(x, y, Color.Black);
                lastX = x;
                lastY = y;
            }
            
            return preview;
        }
    }
}
