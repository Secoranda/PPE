using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PPE_Lab3
{
    public partial class Form1 : Form
    {

        private bool paint;
        private bool drawFilledObjects;

        private Point beginP;
        private Point endP;

        private Pen pencil;
        private Pen redraw_pencil;

        private SolidBrush brush;
        private SolidBrush refill_brush;

        private float pencil_offset;
        private Graphics g;

        private string draw_OBJ;

        private Point initialP;
        private int direction;

        public Form1()
        {
            InitializeComponent();
            pencil_offset = 1.4f;
            paint = false;
            drawFilledObjects = false;


            draw_OBJ = "Line";

            beginP = new Point(0, 0);
            endP = new Point(0, 0);

            g = Canvas.CreateGraphics();
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            brush = new SolidBrush(Color.Black);
            refill_brush = new SolidBrush(Color.White);

            pencil = new Pen(Color.Black, 1);
            pencil.StartCap = pencil.EndCap = System.Drawing.Drawing2D.LineCap.Round;

            redraw_pencil = new Pen(Color.White, 1 + pencil_offset);
            redraw_pencil.StartCap = redraw_pencil.EndCap = System.Drawing.Drawing2D.LineCap.Round;

            initialP = new Point();
            direction = 1;
        }

        private void Canvas_MouseUp(object sender, MouseEventArgs e)
        {
            paint = false;
        }

        private void Canvas_MouseDown(object sender, MouseEventArgs e)
        {
            paint = true;
            beginP.X = e.X;
            beginP.Y = e.Y;
        }

        private void Canvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (paint)
            {
                switch (draw_OBJ)
                {
                    case "Line":
                        DrawLine(e);
                        break;
                    case "Lines":
                        DrawLines(e);
                        break;
                    case "Rectangle":
                        DrawRectangle(e);
                        break;
                    case "Ellipse":
                        DrawEllipse(e);
                        break;
                    case "Triangle":
                        DrawTriangle(e);
                        break;
                    default:
                        MessageBox.Show("Mouse not pressed");
                        break;
                }
            }
            else
            {
                beginP.X = endP.X = e.X;
                beginP.Y = endP.Y = e.Y;
                initialP.X = e.X;
                initialP.Y = e.Y;
                direction = 1;
            }
        }
        private void DrawLine(MouseEventArgs e)
        {
            endP = new Point(e.X, e.Y);
            g.DrawLine(pencil, beginP, endP);
  
            beginP = endP;
        }

        private void DrawLines(MouseEventArgs e)
        {
            g.DrawLine(redraw_pencil, beginP, endP);
            endP = new Point(e.X, e.Y);
            g.DrawLine(pencil, beginP, endP);
        }

        private void DrawTriangle(MouseEventArgs e)
        {
            if (drawFilledObjects)
            {
                int offset = 0;
                if (beginP.X < endP.X)
                    offset = 2;
                else
                    offset = -2;

                Point[] points =
                {
                    new Point(beginP.X-offset, beginP.Y+Math.Abs(offset/2)*direction ),
                    new Point(endP.X+offset, beginP.Y+Math.Abs(offset/2)*direction),
                    new Point((endP.X + beginP.X) / 2 , beginP.Y - (Math.Abs(endP.X - beginP.X) / 2 + Math.Abs(offset/2))*direction)

                };

                g.FillPolygon(refill_brush, points);

                if (initialP.Y >= e.Y)
                    direction = 1;
                else
                    direction = -1;

                endP.X = e.X;
                endP.Y = e.Y;

                Point[] points2 =
                {
                    new Point(beginP.X, beginP.Y),
                    new Point(endP.X, beginP.Y),
                    new Point((endP.X + beginP.X) / 2, beginP.Y - (Math.Abs(endP.X - beginP.X) / 2)*direction)
                };

                g.FillPolygon(brush, points2);
            }
            else
            {
                Point[] points =
                {
                    new Point(beginP.X, beginP.Y),
                    new Point(endP.X, beginP.Y),
                    new Point((endP.X + beginP.X) / 2, beginP.Y - (Math.Abs(endP.X - beginP.X) / 2*direction ))

                };

                g.DrawPolygon(redraw_pencil, points);

                if (initialP.Y >= e.Y)
                    direction = 1;
                else
                    direction = -1;

                endP.X = e.X;
                endP.Y = e.Y;
                Point[] points2 =
                {
                    new Point(beginP.X, beginP.Y),
                    new Point(endP.X, beginP.Y),
                    new Point((endP.X + beginP.X) / 2, beginP.Y - (Math.Abs(endP.X - beginP.X) / 2*direction))
                };
                g.DrawPolygon(pencil, points2);
            }
        }

        private void DrawRectangle(MouseEventArgs e)
        {

            if (drawFilledObjects)
            {
                g.FillRectangle(refill_brush, beginP.X - pencil_offset / 2, beginP.Y - pencil_offset / 2,
                    Math.Abs(endP.X - beginP.X) + pencil_offset, Math.Abs(endP.Y - beginP.Y) + pencil_offset);

                if (e.X >= initialP.X)
                    endP.X = e.X;
                else
                    beginP.X = e.X;

                if (e.Y >= initialP.Y)
                    endP.Y = e.Y;
                else
                    beginP.Y = e.Y;

                g.FillRectangle(brush, beginP.X, beginP.Y,
                    Math.Abs(endP.X - beginP.X), Math.Abs(endP.Y - beginP.Y));
            }
            else
            {
                g.DrawRectangle(redraw_pencil, beginP.X, beginP.Y,
                    Math.Abs(endP.X - beginP.X), Math.Abs(endP.Y - beginP.Y));

                if (e.X >= initialP.X)
                    endP.X = e.X;
                else
                    beginP.X = e.X;

                if (e.Y >= initialP.Y)
                    endP.Y = e.Y;
                else
                    beginP.Y = e.Y;

                g.DrawRectangle(pencil, beginP.X, beginP.Y,
                    Math.Abs(endP.X - beginP.X), Math.Abs(endP.Y - beginP.Y));
            }

        }

        private void DrawEllipse(MouseEventArgs e)
        {
            if (drawFilledObjects)
            {
                float redrawOffset = 2.4f;
                g.FillEllipse(refill_brush, beginP.X - redrawOffset / 2, beginP.Y - redrawOffset / 2,
                    Math.Abs(endP.X - beginP.X) + redrawOffset, Math.Abs(endP.Y - beginP.Y) + redrawOffset);

                if (e.X >= initialP.X)
                    endP.X = e.X;
                else
                    beginP.X = e.X;

                if (e.Y >= initialP.Y)
                    endP.Y = e.Y;
                else
                    beginP.Y = e.Y;

                g.FillEllipse(brush, beginP.X, beginP.Y,
                    Math.Abs(endP.X - beginP.X), Math.Abs(endP.Y - beginP.Y));

            }
            else
            {

                g.DrawEllipse(redraw_pencil, beginP.X, beginP.Y,
                    Math.Abs(endP.X - beginP.X), Math.Abs(endP.Y - beginP.Y));

                if (e.X >= initialP.X)
                    endP.X = e.X;
                else
                    beginP.X = e.X;

                if (e.Y >= initialP.Y)
                    endP.Y = e.Y;
                else
                    beginP.Y = e.Y;

                g.DrawEllipse(pencil, beginP.X, beginP.Y,
                    Math.Abs(endP.X - beginP.X), Math.Abs(endP.Y - beginP.Y));
            }
        }

        private void color_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            if (cd.ShowDialog() == DialogResult.OK)
            {
                pencil.Color = cd.Color;
                brush.Color = cd.Color;
            }
        }

        private void widthThin_Click(object sender, EventArgs e)
        {
            pencil.Width = 1;
            redraw_pencil.Width = 1 + pencil_offset;
        }

        private void widthMedium_Click(object sender, EventArgs e)
        {
            pencil.Width = 10;
            redraw_pencil.Width = 5 + pencil_offset;
        }

        private void widthThick_Click(object sender, EventArgs e)
        {
            pencil.Width = 20;
            redraw_pencil.Width = 10 + pencil_offset;
        }


        private void clear_Click(object sender, EventArgs e)
        {
            g.Clear(Color.White);
        }

        private void line_Click(object sender, EventArgs e)
        {
            draw_OBJ = "Line";

        }

        private void square_Click(object sender, EventArgs e)
        {
            draw_OBJ = "Rectangle";
        }

        private void circle_CLICK(object sender, EventArgs e)
        {
            draw_OBJ = "Ellipse";
        }

        private void triangle_Click(object sender, EventArgs e)
        {
            draw_OBJ = "Triangle";
        }

        private void filled_CLICK(object sender, EventArgs e)
        {
            drawFilledObjects = true;
        }

        private void unfilled_Click(object sender, EventArgs e)
        {
            drawFilledObjects = false;
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            this.Canvas.Width = this.Width - 40;
            this.Canvas.Height = this.Height - 90;

            g = Canvas.CreateGraphics();
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
        }

        private void lines_Click(object sender, EventArgs e)
        {
            draw_OBJ = "Lines";
        }
    }
}
