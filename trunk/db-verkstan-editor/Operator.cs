using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using VerkstanBindings;

namespace VerkstanEditor
{
    public class Operator
    {
        public OperatorBinding Binding;
        public String Page;
        public Point location;
        public Point Location
        {
            set
            {
                location = QuantizeLocation(value);
            }
            get
            {
                return location;
            }
        }
        private Size size;
        public Size Size
        {
            set
            {
                size = QuantizeSize(value);
            }
            get
            {
                return size;
            }
        }
        public Boolean Selected = false;
        public Rectangle Dimension
        {
            get
            {
                return new Rectangle(Location.X, Location.Y, Size.Width, Size.Height);
            }
        }

        public static Point QuantizeLocation(Point location)
        {
            return new Point(location.X - location.X % 100,
                             location.Y - location.Y % 20);
        }

        public static Size QuantizeSize(Size size)
        {
            Size quantizedSize = new Size(size.Width - size.Width % 100,
                                          size.Height - size.Height % 20);

            if (quantizedSize.Width < 100)
                quantizedSize.Width = 100;
            if (quantizedSize.Height < 20)
                quantizedSize.Height = 20;
           
            return quantizedSize;
        }

        public Operator(String page, Point location, OperatorBinding binding)
        {
            Page = page;
            Binding = binding;
            Location = location;
            Size = new Size(100, 20);
        }

        public Rectangle GetAreaForInConnections()
        {
            return new Rectangle(location.X, location.Y - 1, size.Width - 1, 1);
        }

        public Rectangle GetAreaForOutConnections()
        {
            return new Rectangle(location.X, location.Y + size.Height, size.Width - 1, 1);
        }

        public Rectangle GetAreaForResize()
        {
            return new Rectangle(location.X + size.Width - 15, 
                                 location.Y, 
                                 15,
                                 20);
        }

    }
}
