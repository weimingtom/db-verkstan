namespace VerkstanEditor.Gui
{
    partial class operatorPage
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
            this.components = new System.ComponentModel.Container();
            this.operatorsMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.SuspendLayout();
            // 
            // operatorsMenu
            // 
            this.operatorsMenu.Name = "OperatorsMenu";
            this.operatorsMenu.Size = new System.Drawing.Size(61, 4);
            this.operatorsMenu.Opened += new System.EventHandler(this.operatorsMenu_Opened);
            // 
            // operatorPage
            // 
            this.ContextMenuStrip = this.operatorsMenu;
            this.Name = "operatorPage";
            this.DoubleClick += new System.EventHandler(this.operatorPage_DoubleClick);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.OperatorPanel_Paint);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.OperatorPage_MouseMove);
            this.ParentChanged += new System.EventHandler(this.OperatorPage_ParentChanged);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.OperatorPage_MouseDown);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.OperatorPage_MouseUp);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.operatorPage_KeyDown);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ContextMenuStrip operatorsMenu;


    }
}
