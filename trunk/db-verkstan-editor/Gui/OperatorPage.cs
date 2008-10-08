using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace VerkstanEditor.Gui
{
    public partial class operatorPage : UserControl
    {
        private Boolean InSelect = false;
        private Boolean InMove = false;
        private Point SelectMarkLocation;
        private Point MoveMarkLocation;
        private Point MouseLocation;
        private Point AddLocation;

        public operatorPage()
        {
            this.Size = new Size(0, 0);
            this.DoubleBuffered = true;
            InitializeComponent();

            //Operators.AddOperatorInPage("First", 100, 100, VerkstanBindings.OperatorBinding.Names.Text);
            //Operators.AddOperatorInPage("First", 100, 150, VerkstanBindings.OperatorBinding.Names.Pixels);
            CheckSize();

            foreach (String category in VerkstanBindings.OperatorBindingFactory.GetCategories())
            {
                ToolStripMenuItem item = new ToolStripMenuItem();
                item.AutoSize = true;
                item.Name = category;
                item.Text = item.Name;
                operatorsMenu.Items.Add(item);
                ICollection<String> names = VerkstanBindings.OperatorBindingFactory.GetNamesInCategory(category);
                foreach (String name in names)
                {
                    ToolStripMenuItem nestedItem = new ToolStripMenuItem();
                    nestedItem.AutoSize = true;
                    nestedItem.Name = name;
                    nestedItem.Text = nestedItem.Name;
                    String clickedName = name;
                    nestedItem.Click += new EventHandler((object o, EventArgs e) => Operators.AddOperatorInPage("First", AddLocation, clickedName));
                    item.DropDownItems.Add(nestedItem);
                }            
            }
        }

        public delegate void OperatorSelectedHandler(Operator op);
        public event OperatorSelectedHandler OperatorSelected;
       
        public void OnOperatorSelected(Operator op)
        {
            if (OperatorSelected != null)
                OperatorSelected(op);
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

        private void PaintOperator(Operator op, PaintEventArgs e)
        {
            Rectangle rect = new Rectangle(op.Location, op.Size);
            SizeF stringSize = e.Graphics.MeasureString(op.Binding.Name, Font);
            Point namePoint = new Point(rect.Width / 2 - (int)stringSize.Width / 2 + rect.X,
                                        rect.Height / 2 - (int)stringSize.Height / 2 + rect.Y);

            if (op.Selected && op.Binding.IsProcessable())
            {
                e.Graphics.FillRectangle(Brushes.LightCyan, rect);
                e.Graphics.DrawRectangle(Pens.Black, rect);
                e.Graphics.DrawString(op.Binding.Name, Font, Brushes.Black, namePoint);
            }
            else if (op.Selected && !op.Binding.IsProcessable())
            {
                e.Graphics.FillRectangle(Brushes.LightGray, rect);
                e.Graphics.DrawRectangle(Pens.Black, rect);
                e.Graphics.DrawString(op.Binding.Name, Font, Brushes.Black, namePoint);
            }
            else if (op.Binding.IsProcessable())
            {
                e.Graphics.FillRectangle(Brushes.Cyan, rect);
                e.Graphics.DrawRectangle(Pens.Black, rect);
                e.Graphics.DrawString(op.Binding.Name, Font, Brushes.Black, namePoint);
            }
            else
            {
                e.Graphics.FillRectangle(Brushes.Gray, rect);
                e.Graphics.DrawRectangle(Pens.Black, rect);
                e.Graphics.DrawString(op.Binding.Name, Font, Brushes.Black, namePoint);
            }
        }

        private void OperatorPage_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                MouseLocation = new Point(e.X, e.Y);
                SelectMarkLocation = MouseLocation;
                MoveMarkLocation = SelectMarkLocation;
                Operator op = Operators.GetOperatorInPageAt("First", MouseLocation);

                if (op == null)
                {
                    InSelect = true;
                    Operators.SetOperatorsSelectedInPage("First", GetSelectionRectangle());
                }
                else if (op.Selected)
                {
                    op.Selected = true;
                    InMove = true;
                    OnOperatorSelected(op);
                }
                else
                {
                    InMove = true;
                    Operators.SetOperatorsSelectedInPage("First", GetSelectionRectangle());
                }
            }
            else if (e.Button == MouseButtons.Right)
            {
                InSelect = false;
                InMove = false;
                Operators.DeselectAllOperatorsInPage("First");
            }

            Parent.Focus();
            Refresh();
        }

        private void OperatorPage_MouseUp(object sender, MouseEventArgs e)
        {
            if (InMove)
            {
                Operators.MoveSelectedOperatorsInPage("First", GetMovePoint());
                CheckSize();
            }

            InSelect = false;
            InMove = false;
            Refresh();
        }

        private void OperatorPage_MouseMove(object sender, MouseEventArgs e)
        {
            MouseLocation = new Point(e.X, e.Y);
           
            if (InSelect)
                Operators.SetOperatorsSelectedInPage("First", GetSelectionRectangle());

            Refresh();
        }

        private Point GetMovePoint()
        {
            Point mouseLocation = Operator.QuantizeLocation(MouseLocation);
            Point moveMarkerLocation = Operator.QuantizeLocation(MoveMarkLocation);
            return new Point(mouseLocation.X - moveMarkerLocation.X,
                             mouseLocation.Y - moveMarkerLocation.Y);
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
            Parent.Resize += new System.EventHandler(this.OperatorPage_ParentResized);
        }

        private void OperatorPage_ParentResized(object sender, EventArgs e)
        {
            CheckSize();
        }

        private void operatorsMenu_Opened(object sender, EventArgs e)
        {
            AddLocation = MouseLocation;
        }
    }
}
