namespace VerkstanEditor.Gui
{
    partial class OperatorProperty
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.OperatorPropertyTable = new System.Windows.Forms.TableLayoutPanel();
            this.SuspendLayout();
            // 
            // OperatorPropertyTable
            // 
            this.OperatorPropertyTable.AutoScroll = true;
            this.OperatorPropertyTable.AutoSize = true;
            this.OperatorPropertyTable.ColumnCount = 2;
            this.OperatorPropertyTable.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 60F));
            this.OperatorPropertyTable.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.OperatorPropertyTable.Dock = System.Windows.Forms.DockStyle.Fill;
            this.OperatorPropertyTable.Location = new System.Drawing.Point(0, 0);
            this.OperatorPropertyTable.Name = "OperatorPropertyTable";
            this.OperatorPropertyTable.RowCount = 1;
            this.OperatorPropertyTable.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.OperatorPropertyTable.Size = new System.Drawing.Size(144, 306);
            this.OperatorPropertyTable.TabIndex = 0;
            this.OperatorPropertyTable.MouseDown += new System.Windows.Forms.MouseEventHandler(this.OperatorPropertyTable_MouseDown);
            // 
            // OperatorProperty
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.OperatorPropertyTable);
            this.Name = "OperatorProperty";
            this.Size = new System.Drawing.Size(144, 306);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.OperatorProperty_MouseDown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel OperatorPropertyTable;
    }
}
