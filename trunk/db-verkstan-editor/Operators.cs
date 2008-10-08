using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Linq;
using VerkstanBindings;

namespace VerkstanEditor
{
    public class Operators
    {
        static List<Operator> operators = new List<Operator>();

        public static void AddOperatorInPage(String pageName, Point location, String name)
        {
            Operator other = GetOperatorInPageAt(pageName, location);

            if (other != null)
                return;

            Operator op = new Operator(pageName, location, OperatorBindingFactory.Create(name));
            operators.Add(op);
            MoveOperatorInPage(pageName, new Point(0, 0), op);
        }

        public static void MoveOperatorInPage(String pageName, Point point, Operator op)
        {
            op.Binding.Disconnect();
            op.Location = new Point(op.Location.X + point.X,
                                    op.Location.Y + point.Y);

            List<Operator> inConnections = GetOperatorsInPageIn(pageName, op.GetAreaForInConnections());
            foreach (Operator inOperator in inConnections)
            {
                op.Binding.ConnectInWith(inOperator.Binding);
            }

            List<Operator> outConnections = GetOperatorsInPageIn(pageName, op.GetAreaForOutConnections());
            foreach (Operator outOperator in outConnections)
            {
                op.Binding.ConnectOutWith(outOperator.Binding);
            }
        }

        public static List<Operator> GetOperatorsInPage(String pageName)
        {
            List<Operator> result = new List<Operator>();

            foreach (Operator op in operators)
            {
                if (op.Page == pageName)
                    result.Add(op);
            }

            return result;
        }

        public static List<Operator> GetSelectedOperatorsInPage(String pageName)
        {
            List<Operator> ops = GetOperatorsInPage(pageName);
            
            List<Operator> result = new List<Operator>();

            foreach (Operator op in ops)
            {
                if (op.Selected)
                    result.Add(op);
            }

            return result;
        }

        public static List<Operator> GetNonSelectedOperatorsInPage(String pageName)
        {
            List<Operator> ops = GetOperatorsInPage(pageName);

            List<Operator> result = new List<Operator>();

            foreach (Operator op in ops)
            {
                if (!op.Selected)
                    result.Add(op);
            }

            return result;
        }

        public static void DeleteOperator(Operator op)
        {
            operators.Remove(op);
        }

        public static void SetOperatorsSelectedInPage(String pageName, Rectangle rectangle)
        {
            List<Operator> ops = GetOperatorsInPage(pageName);

            foreach (Operator op in ops)
            {
                Rectangle opRect = new Rectangle(op.Location, op.Size);
                if (rectangle.IntersectsWith(opRect))
                    op.Selected = true;
                else
                    op.Selected = false;
            }
        }

        public static List<Operator> GetOperatorsInPageIn(String pageName, Rectangle rectangle)
        {
            List<Operator> ops = GetOperatorsInPage(pageName);
            List<Operator> result = new List<Operator>();

            foreach (Operator op in ops)
            {
                Rectangle opRect = new Rectangle(op.Location, op.Size);

                if (opRect.IntersectsWith(rectangle))
                    result.Add(op);
            }

            return result;
        }

        public static Operator GetOperatorInPageAt(String pageName, Point point)
        {
            List<Operator> ops = GetOperatorsInPage(pageName);
            
            Rectangle pointRect = new Rectangle(point.X, point.Y, 1, 1);

            foreach (Operator op in ops)
            {
                Rectangle opRect = new Rectangle(op.Location, op.Size);

                if (opRect.IntersectsWith(pointRect))
                    return op;
            }

            return null;
        }

        public static void MoveSelectedOperatorsInPage(String pageName, Point point)
        {
            List<Operator> selectedOperators = GetSelectedOperatorsInPage(pageName);
            List<Operator> nonSelecteOperators = GetNonSelectedOperatorsInPage(pageName);

            foreach (Operator selectedOp in selectedOperators)
            {
                Rectangle selectedOpDim = new Rectangle(selectedOp.Location.X + point.X,
                                                        selectedOp.Location.Y + point.Y, 
                                                        selectedOp.Size.Width,
                                                        selectedOp.Size.Height);

                foreach (Operator nonSelectedOp in nonSelecteOperators)
                {
                    if (nonSelectedOp.Dimension.IntersectsWith(selectedOpDim))
                    {
                        // Cannot peform move due to a collision.
                        return;
                    }
                }
            }

            foreach (Operator selectedOp in selectedOperators)
            {
                MoveOperatorInPage(pageName, point, selectedOp);
            }
        }

        public static Rectangle GetOperatorsDimensionInPage(String pageName)
        {
            List<Operator> operators = GetOperatorsInPage(pageName);

            int x1 = 0;
            int y1 = 0;
            int x2 = 0;
            int y2 = 0;

            foreach (Operator op in operators)
            {
                if (op.Location.X < x1)
                    x1 = op.Location.X;
                if (op.Location.Y < y1)
                    y1 = op.Location.Y;
                if (op.Location.X + op.Size.Width > x2)
                    x2 = op.Location.X + op.Size.Width;
                if (op.Location.Y + op.Size.Height > y2)
                    y2 = op.Location.Y + op.Size.Height;
            }

            return new Rectangle(x1, y1, x2 - x1, y2 - y1);
        }

        public static void SelectAllOperatorsInPage(String pageName)
        {
            List<Operator> operators = GetOperatorsInPage(pageName);

            foreach (Operator op in operators)
                op.Selected = true;
        }

        public static void DeselectAllOperatorsInPage(String pageName)
        {
            List<Operator> operators = GetOperatorsInPage(pageName);

            foreach (Operator op in operators)
                op.Selected = false;
        }
    }
}
