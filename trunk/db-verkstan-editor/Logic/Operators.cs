using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Linq;

namespace VerkstanEditor
{
    public class Operators
    {
        private static Operator viewedOperator;
        public static Operator ViewedOperator
        {
            set
            {
                viewedOperator = value;
                OnViewedOperatorChanged(value);
            }
            get
            {
                return viewedOperator;
            }
        }
        private static Operator viewedOperatorProperties;
        public static Operator ViewedOperatorProperties
        {
            set
            {
                viewedOperatorProperties = value;
                OnViewedOperatorPropertiesChanged(value);
            }
            get
            {
                return viewedOperatorProperties;
            }
        }
        
        static List<Operator> operators = new List<Operator>();

        public delegate void ViewedOperatorChangedHandler(Operator op);
        public static event ViewedOperatorChangedHandler ViewedOperatorChanged;

        public static void OnViewedOperatorChanged(Operator op)
        {
            if (ViewedOperatorChanged != null)
                ViewedOperatorChanged(op);
        }

        public delegate void ViewedOperatorPropertiesChangedHandler(Operator op);
        public static event ViewedOperatorPropertiesChangedHandler ViewedOperatorPropertiesChanged;

        public static void OnViewedOperatorPropertiesChanged(Operator op)
        {
            if (ViewedOperatorPropertiesChanged != null)
                ViewedOperatorPropertiesChanged(op);
        }

        public delegate void ViewedOperatorPropertyAnimationChangedHandler(Verkstan.OperatorProperty property);
        public static event ViewedOperatorPropertyAnimationChangedHandler ViewedOperatorPropertyAnimationChanged;

        public static void OnViewedOperatorPropertyAnimationChanged(Verkstan.OperatorProperty property)
        {
            if (ViewedOperatorPropertyAnimationChanged != null)
                ViewedOperatorPropertyAnimationChanged(property);
        }

        public static ICollection<String> GetCategories()
        {
            return Verkstan.OperatorFactory.GetCategories().ToList<String>();
        }

        public static ICollection<String> GetNamesInCategory(String category)
        {
            return Verkstan.OperatorFactory.GetNamesInCategory(category).ToList<String>();
        }

        public static void AddOperatorInPage(String pageName, Point location, String name)
        {
            Operator other = GetOperatorInPageAt(pageName, location);

            if (other != null)
                return;

            Operator op = new Operator(pageName, location, Verkstan.OperatorFactory.Create(name));
            operators.Add(op);
            ConnectOperatorInPageWithNeighbours(pageName, op);
        }

        public static void MoveOperatorInPage(String pageName, Point point, Operator op)
        {
            Point opLocation = Operator.QuantizeLocation(new Point(op.Location.X + point.X,
                                                         op.Location.Y + point.Y));

            // Don't move the operator if it hasn't been moved.
            if (opLocation == op.Location)
                return;

            op.Location = opLocation;
            ConnectOperatorInPageWithNeighbours(pageName, op);
        }

        public static void ConnectOperatorInPageWithNeighbours(String pageName, Operator op)
        {
            Verkstan.Connector.Disconnect(op.Binding);

            List<Operator> inConnections = GetOperatorsInPageIn(pageName, op.GetAreaForInConnections());
            foreach (Operator inOperator in inConnections)
                Verkstan.Connector.Connect(inOperator.Binding, op.Binding);
          
            List<Operator> outConnections = GetOperatorsInPageIn(pageName, op.GetAreaForOutConnections());
            foreach (Operator outOperator in outConnections)
                Verkstan.Connector.Connect(op.Binding, outOperator.Binding);
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
            List<Operator> nonSelectedOperators = GetNonSelectedOperatorsInPage(pageName);

            foreach (Operator selectedOp in selectedOperators)
            {
                Rectangle selectedOpDim = new Rectangle(selectedOp.Location.X + point.X,
                                                        selectedOp.Location.Y + point.Y, 
                                                        selectedOp.Size.Width,
                                                        selectedOp.Size.Height);

                foreach (Operator nonSelectedOp in nonSelectedOperators)
                {
                    if (nonSelectedOp.Dimension.IntersectsWith(selectedOpDim))
                    {
                        // Cannot peform move due to a collision.
                        return;
                    }
                }
            }

            foreach (Operator selectedOp in selectedOperators)
                MoveOperatorInPage(pageName, point, selectedOp);
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

        public static void DeleteSelectedOperatorsInPage(String pageName)
        {
            List<Operator> operators = GetSelectedOperatorsInPage(pageName);

            foreach (Operator op in operators)
                DeleteOperator(op);
        }

        public static void DeleteOperator(Operator op)
        {
            if (op == viewedOperator)
                ViewedOperator = null;
            if (op == viewedOperatorProperties)
                ViewedOperatorProperties = null;
         
            Verkstan.Connector.Disconnect(op.Binding);
            op.Binding.Dispose();
            operators.Remove(op);
        }

        public static void ResizeSelectedOperatorsInPage(string pageName, int additionalWidth)
        {
            List<Operator> selectedOperators = GetSelectedOperatorsInPage(pageName);
            List<Operator> nonSelectedOperators = GetNonSelectedOperatorsInPage(pageName);

            foreach (Operator selectedOp in selectedOperators)
            {
                Rectangle selectedOpDim = new Rectangle(selectedOp.Location.X,
                                                        selectedOp.Location.Y,
                                                        selectedOp.Size.Width + additionalWidth,
                                                        selectedOp.Size.Height);

                foreach (Operator nonSelectedOp in nonSelectedOperators)
                {
                    if (nonSelectedOp.Dimension.IntersectsWith(selectedOpDim))
                    {
                        // Cannot peform resize due to a collision.
                        return;
                    }
                }
            }

            foreach (Operator op in selectedOperators)
            {
                op.Size = new Size(op.Size.Width + additionalWidth, op.Size.Height);
                ConnectOperatorInPageWithNeighbours(pageName, op);
            }
        }
    }
}
