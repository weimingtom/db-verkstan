using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using VerkstanEditor.Util;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class OperatorPage : UserControl
    {
        private bool InSelect = false;
        private bool InMove = false;
        private bool InResize = false;
        private Point SelectMarkLocation;
        private Point MarkLocation;
        private Point MouseLocation;
        private Point AddLocation;

        public OperatorPage()
        {
            this.Size = new Size(0, 0);
            this.DoubleBuffered = true;
            InitializeComponent();

            CheckSize();

            foreach (String category in Operators.GetCategories())
            {
                ToolStripMenuItem item = new ToolStripMenuItem();
                item.AutoSize = true;
                item.Name = category;
                item.Text = item.Name;
                operatorsMenu.Items.Add(item);
                ICollection<String> names = Operators.GetNamesInCategory(category);
                foreach (String name in names)
                {
                    ToolStripMenuItem nestedItem = new ToolStripMenuItem();
                    nestedItem.AutoSize = true;
                    nestedItem.Name = name;
                    nestedItem.Text = nestedItem.Name;
                    String clickedName = name;
                    nestedItem.Click += delegate (object o, EventArgs e)
                    {
                        Operators.AddOperatorInPage("First", AddLocation, clickedName);
                        Refresh();
                    };
                    item.DropDownItems.Add(nestedItem);
                }            
            }
        }

        private void OperatorPanel_Paint(object sender, PaintEventArgs e)
        {
            List<Operator> ops = Operators.GetOperatorsInPage("First");

            foreach (Operator op in ops)
            {
                PaintOperator(op, e);
            }

            if (InMove)
            {
                List<Operator> selectedOperators = Operators.GetSelectedOperatorsInPage("First");
                foreach (Operator op in selectedOperators)
                {
                    PaintMovingOperator(op, e);
                }
            }

            if (InResize)
            {
                List<Operator> selectedOperators = Operators.GetSelectedOperatorsInPage("First");
                foreach (Operator op in selectedOperators)
                {
                    PaintResizingOperator(op, e);
                }
            }

            if (InSelect)
            {
                Pen p = new Pen(Color.Black, 1);
                p.DashStyle = DashStyle.Dash;
                e.Graphics.DrawRectangle(p, GetSelectionRectangle());
                p.Dispose();
            }
        }

        private void PaintMovingOperator(Operator op, PaintEventArgs e)
        {
            Point p = GetMovePoint();
            Point opLocation = op.Location;
            opLocation.X += p.X;
            opLocation.Y += p.Y;
            opLocation = Operator.QuantizeLocation(opLocation);
            Pen pen = new Pen(Color.Black, 2);
            e.Graphics.DrawRectangle(pen, opLocation.X, opLocation.Y, op.Size.Width, op.Size.Height);
            pen.Dispose();
        }

        private void PaintResizingOperator(Operator op, PaintEventArgs e)
        {
            Size size = Operator.QuantizeSize(new Size(op.Size.Width + GetResizeWidth(),
                                                       op.Size.Height));
            Pen pen = new Pen(Color.Black, 2);
            e.Graphics.DrawRectangle(pen, op.Location.X, op.Location.Y, size.Width, size.Height);
            pen.Dispose();
        }

        private void PaintOperator(Operator op, PaintEventArgs e)
        {
            Rectangle rect = new Rectangle(op.Location, op.Size);
            SizeF stringSize = e.Graphics.MeasureString(op.Binding.DisplayName, Font);
            Point namePoint = new Point(rect.Width / 2 - (int)stringSize.Width / 2 + rect.X,
                                        rect.Height / 2 - (int)stringSize.Height / 2 + rect.Y);

            double brightness = 1.0;
            if (op.Selected)
                brightness = 1.3;
            double saturation = 0.0;
            if (op.Binding.IsProcessable())
                saturation = 1.0;

            Color color = RGBHSL.ModifyBrightness(op.Color, brightness);
            color = RGBHSL.ModifySaturation(color, saturation);
            Color lightColor = RGBHSL.ModifyBrightness(color, 1.3);
            Color darkColor = RGBHSL.ModifyBrightness(color, 0.7);
            Brush brush = new SolidBrush(color);
            Pen lightPen = new Pen(lightColor);
            Pen darkPen = new Pen(darkColor);

            e.Graphics.FillRectangle(brush, rect);
            e.Graphics.DrawLine(lightPen,
                                op.Location.X,
                                op.Location.Y + op.Size.Height - 1,
                                op.Location.X,
                                op.Location.Y);
            e.Graphics.DrawLine(lightPen,
                                op.Location.X,
                                op.Location.Y,
                                op.Location.X + op.Size.Width - 1,
                                op.Location.Y);
            e.Graphics.DrawLine(darkPen,
                                op.Location.X + op.Size.Width - 1,
                                op.Location.Y,
                                op.Location.X + op.Size.Width - 1,
                                op.Location.Y + op.Size.Height - 1);
            e.Graphics.DrawLine(darkPen,
                                op.Location.X,
                                op.Location.Y + op.Size.Height - 1,
                                op.Location.X + op.Size.Width - 1,
                                op.Location.Y + op.Size.Height - 1);
            Brush textBrush = new SolidBrush(op.TextColor);
            e.Graphics.DrawString(op.Binding.DisplayName, Font, textBrush, namePoint);

            int x1 = op.GetAreaForResize().Left;
            int y1 = op.Location.Y + 3;
            int y2 = op.Location.Y + op.Size.Height - 4;

            for (int i = 0; i < 4; i++)
            {
                e.Graphics.DrawLine(lightPen,
                                    x1 + i * 3,
                                    y1,
                                    x1 + i * 3,
                                    y2);
                e.Graphics.DrawLine(darkPen,
                                    x1 + 1 + i * 3,
                                    y1,
                                    x1 + 1 + i * 3,
                                    y2);
            }

            if (!op.Binding.IsProcessable() || op.Binding.IsWarningPresent())
                e.Graphics.DrawImage(VerkstanEditor.Properties.Resources.warning_icon, op.Location.X + 1, op.Location.Y + 1);
            if (op == Operators.ViewedOperator)
                e.Graphics.DrawImage(VerkstanEditor.Properties.Resources.eye_icon, op.Location.X + 1, op.Location.Y + 1);
        }

        private void OperatorPage_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                MouseLocation = new Point(e.X, e.Y);
                SelectMarkLocation = MouseLocation;
                MarkLocation = SelectMarkLocation;
                Operator op = Operators.GetOperatorInPageAt("First", MouseLocation);

                if (op == null)
                {
                    InSelect = true;
                    Operators.SetOperatorsSelectedInPage("First", GetSelectionRectangle());
                }
                else
                {                   
                    if (op.GetAreaForResize().IntersectsWith(new Rectangle(MouseLocation.X, MouseLocation.Y, 1, 1)))
                    {
                        InResize = true;
                        Operators.SetOperatorsSelectedInPage("First", GetSelectionRectangle());
                    }
                    else
                    {
                        InMove = true;
                        if (!op.Selected)
                            Operators.SetOperatorsSelectedInPage("First", GetSelectionRectangle());
                    }

                    Operators.ViewedOperatorProperties = op;
                }
            }
            else if (e.Button == MouseButtons.Right)
            {
                InSelect = false;
                InMove = false;
                Operators.DeselectAllOperatorsInPage("First");
            }
            Refresh();
        }

        private void operatorPage_DoubleClick(object sender, EventArgs e)
        {
            Operator op = Operators.GetOperatorInPageAt("First", MouseLocation);

            if (op != null)
                Operators.ViewedOperator = op;

            Refresh();
        }

        private void OperatorPage_MouseUp(object sender, MouseEventArgs e)
        {
            if (InMove)
            {
                Operators.MoveSelectedOperatorsInPage("First", GetMovePoint());
                CheckSize();
            }

            if (InResize)
            {
                Operators.ResizeSelectedOperatorsInPage("First", GetResizeWidth());
                CheckSize();
            }

            InSelect = false;
            InMove = false;
            InResize = false;
            Refresh();
        }

        private void OperatorPage_MouseMove(object sender, MouseEventArgs e)
        {
            MouseLocation = new Point(e.X, e.Y);

            if (InSelect)
                Operators.SetOperatorsSelectedInPage("First", GetSelectionRectangle());

            if (InMove || InSelect || InResize)
                Refresh();
         
        }

        private Point GetMovePoint()
        {
            Point mouseLocation = Operator.QuantizeLocation(MouseLocation);
            Point moveMarkerLocation = Operator.QuantizeLocation(MarkLocation);
            return new Point(mouseLocation.X - moveMarkerLocation.X,
                             mouseLocation.Y - moveMarkerLocation.Y);
        }

        private int GetResizeWidth()
        {
            return MouseLocation.X - MarkLocation.X;
        }

        private Rectangle GetSelectionRectangle()
        {
            int x1 = 0;
            int y1 = 0;
            int x2 = 0;
            int y2 = 0;

            if (MouseLocation.X < SelectMarkLocation.X)
            {
                x1 = MouseLocation.X;
                x2 = SelectMarkLocation.X;
            }
            else
            {
                x2 = MouseLocation.X;
                x1 = SelectMarkLocation.X;
            }

            if (MouseLocation.Y < SelectMarkLocation.Y)
            {
                y1 = MouseLocation.Y;
                y2 = SelectMarkLocation.Y;
            }
            else
            {
                y2 = MouseLocation.Y;
                y1 = SelectMarkLocation.Y;
            }

            return new Rectangle(x1, y1, x2 - x1, y2 - y1);
        }

        private void CheckSize()
        {
            Rectangle dimension = Operators.GetOperatorsDimensionInPage("First");

            // Check the size of the operators dimension.
            Point move = new Point();
            if (dimension.X < 0)
                move.X = -dimension.X - 1;
            if (dimension.Y < 0)
                move.Y = -dimension.Y - 1;

            if (move.X != 0 || move.Y != 0)
            {
                Operators.SelectAllOperatorsInPage("First");
                Operators.MoveSelectedOperatorsInPage("First", move);
                Operators.DeselectAllOperatorsInPage("First");
            }

            // Move operators if necessary.
            if (Size.Width < dimension.Width)
                Size = new Size(dimension.Width + 1, Size.Height);

            if (Size.Height < dimension.Height)
                Size = new Size(Size.Width, dimension.Height + 1);


            if (Parent == null)
                return;

            // Finally, check that the page is at least as big as it's
            // parent.
            Size parentSize = Parent.Size;

            if (Size.Width < parentSize.Width)
                Size = new Size(parentSize.Width, Size.Height);

            if (Size.Height < parentSize.Height)
                Size = new Size(Size.Width, parentSize.Height);
        }

        private void OperatorPage_ParentChanged(object sender, EventArgs e)
        {
            Parent.Resize += new System.EventHandler(this.operatorPage_ParentResized);
        }

        private void operatorPage_ParentResized(object sender, EventArgs e)
        {
            CheckSize();
        }

        private void operatorsMenu_Opened(object sender, EventArgs e)
        {
            AddLocation = MouseLocation;
        }

        private void operatorPage_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                Operators.DeleteSelectedOperatorsInPage("First");
                Refresh();
            }
        }
    }
}
