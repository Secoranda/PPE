namespace PPE_Lab3
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.Canvas = new System.Windows.Forms.PictureBox();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.width = new System.Windows.Forms.ToolStripDropDownButton();
            this.widthThin = new System.Windows.Forms.ToolStripMenuItem();
            this.widthMedium = new System.Windows.Forms.ToolStripMenuItem();
            this.widthThick = new System.Windows.Forms.ToolStripMenuItem();
            this.shapes = new System.Windows.Forms.ToolStripDropDownButton();
            this.line = new System.Windows.Forms.ToolStripMenuItem();
            this.square = new System.Windows.Forms.ToolStripMenuItem();
            this.circle = new System.Windows.Forms.ToolStripMenuItem();
            this.triangle = new System.Windows.Forms.ToolStripMenuItem();
            this.style = new System.Windows.Forms.ToolStripDropDownButton();
            this.filled = new System.Windows.Forms.ToolStripMenuItem();
            this.unfilled = new System.Windows.Forms.ToolStripMenuItem();
            this.color = new System.Windows.Forms.ToolStripMenuItem();
            this.clear = new System.Windows.Forms.ToolStripButton();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.lines = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.Canvas)).BeginInit();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();

            this.Canvas.BackColor = System.Drawing.Color.White;
            this.Canvas.Location = new System.Drawing.Point(12, 40);
            this.Canvas.Name = "Canvas";
            this.Canvas.Size = new System.Drawing.Size(683, 316);
            this.Canvas.TabIndex = 0;
            this.Canvas.TabStop = false;
            this.Canvas.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Canvas_MouseDown);
            this.Canvas.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Canvas_MouseMove);
            this.Canvas.MouseUp += new System.Windows.Forms.MouseEventHandler(this.Canvas_MouseUp);

            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.width,
            this.shapes,
            this.style,
            this.clear});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(707, 25);
            this.toolStrip1.TabIndex = 1;
            this.toolStrip1.Text = "toolStrip1";

            this.width.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.width.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.widthThin,
            this.widthMedium,
            this.widthThick,
            });
            this.width.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.width.Name = "width";
           this.width.Size = new System.Drawing.Size(75, 22);
            this.width.Text = "Width";

            this.widthThin.Name = "widthThin";
            this.widthThin.Size = new System.Drawing.Size(75, 22);
            this.widthThin.Text = "Thin";
            this.widthThin.Click += new System.EventHandler(this.widthThin_Click);

            this.widthMedium.Name = "widthMedium";
            this.widthMedium.Size = new System.Drawing.Size(75, 22);
            this.widthMedium.Text = "Medium";
            this.widthMedium.Click += new System.EventHandler(this.widthMedium_Click);

            this.widthThick.Name = "widthThick";
            this.widthThick.Size = new System.Drawing.Size(75, 22);
            this.widthThick.Text = "Thick";
            this.widthThick.Click += new System.EventHandler(this.widthThick_Click);

            this.shapes.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.shapes.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.line,
            this.square,
            this.circle,
            this.triangle,
            this.lines});
            this.shapes.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.shapes.Name = "shapes";
            this.shapes.Size = new System.Drawing.Size(75, 22);
            this.shapes.Text = "Shapes";

            this.line.Name = "line";
            this.line.Size = new System.Drawing.Size(75, 22);
            this.line.Text = "Paint";
            this.line.Click += new System.EventHandler(this.line_Click);

            this.square.Name = "square";
            this.square.Size = new System.Drawing.Size(75, 22);
            this.square.Text = "Rectangle";
            this.square.Click += new System.EventHandler(this.square_Click);

            this.circle.Name = "circle";
            this.circle.Size = new System.Drawing.Size(75, 22);
            this.circle.Text = "Circle";
            this.circle.Click += new System.EventHandler(this.circle_CLICK);

            this.triangle.Name = "triangle";
            this.triangle.Size = new System.Drawing.Size(75, 22);
            this.triangle.Text = "Triangle";
            this.triangle.Click += new System.EventHandler(this.triangle_Click);

            this.style.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.style.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.filled,
            this.unfilled,
            this.color});
            this.style.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.style.Name = "style";
            this.style.Size = new System.Drawing.Size(75, 22);
            this.style.Text = "Change style";

            this.filled.Name = "filled";
            this.filled.Size = new System.Drawing.Size(75, 22);
            this.filled.Text = "Filled";
            this.filled.Click += new System.EventHandler(this.filled_CLICK);

            this.unfilled.Name = "unfilled";
            this.unfilled.Size = new System.Drawing.Size(75, 22);
            this.unfilled.Text = "Unfilled";
            this.unfilled.Click += new System.EventHandler(this.unfilled_Click);

            this.color.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.color.Name = "toolStripColorButton";
            this.color.Size = new System.Drawing.Size(75, 22);
            this.color.Text = "Colors";
            this.color.Click += new System.EventHandler(this.color_Click);

            this.clear.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.clear.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.clear.Name = "clear";
            this.clear.Size = new System.Drawing.Size(75, 22);
            this.clear.Text = "Clear";
            this.clear.Click += new System.EventHandler(this.clear_Click);

            this.lines.Name = "lines";
            this.lines.Size = new System.Drawing.Size(75, 22);
            this.lines.Text = "Lines";
            this.lines.Click += new System.EventHandler(this.lines_Click);

            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.ClientSize = new System.Drawing.Size(707, 368);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.Canvas);
            this.MinimumSize = new System.Drawing.Size(400, 200);
            this.Name = "Form1";
            this.Text = "LAB6";
            this.Resize += new System.EventHandler(this.Form1_Resize);
            ((System.ComponentModel.ISupportInitialize)(this.Canvas)).EndInit();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox Canvas;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripDropDownButton width;
        private System.Windows.Forms.ToolStripMenuItem widthThin;
        private System.Windows.Forms.ToolStripMenuItem widthMedium;
        private System.Windows.Forms.ToolStripMenuItem widthThick;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.ToolStripButton clear;
        private System.Windows.Forms.ToolStripDropDownButton shapes;
        private System.Windows.Forms.ToolStripMenuItem line;
        private System.Windows.Forms.ToolStripMenuItem square;
        private System.Windows.Forms.ToolStripMenuItem circle;
        private System.Windows.Forms.ToolStripMenuItem triangle;
        private System.Windows.Forms.ToolStripDropDownButton style;
        private System.Windows.Forms.ToolStripMenuItem filled;
        private System.Windows.Forms.ToolStripMenuItem unfilled;
        private System.Windows.Forms.ToolStripMenuItem color;
        private System.Windows.Forms.ToolStripMenuItem lines;
    }
}

