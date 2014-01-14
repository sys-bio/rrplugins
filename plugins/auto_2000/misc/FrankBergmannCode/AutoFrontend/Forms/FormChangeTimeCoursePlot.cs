using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace AutoFrontend.Forms
{
    /// <summary>
    ///     Summary description for FormChangeTimeCoursePlot.
    /// </summary>
    public class FormChangeTimeCoursePlot : Form
    {
        private static FormChangeTimeCoursePlot _Instance;

        /// <summary>
        ///     Required designer variable.
        /// </summary>
        private readonly Container components = null;

        private CheckBox chkAntiAlias;
        private ComboBox cmbXAxis;
        private Button cmdCancel;
        private Button cmdOK;
        private GroupBox groupBox1;
        private Panel panel1;
        private Panel panel2;
        private Panel panel3;
        private Panel panel4;

        private FormChangeTimeCoursePlot()
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

            //
            // TODO: Add any constructor code after InitializeComponent call
            //
        }

        public static FormChangeTimeCoursePlot Instance
        {
            get
            {
                if (_Instance == null) _Instance = new FormChangeTimeCoursePlot();
                return _Instance;
            }
            set { _Instance = value; }
        }

        public bool IsAntiAlias
        {
            get { return chkAntiAlias.Checked; }
            set { chkAntiAlias.Checked = value; }
        }

        public object[] XAxisValues
        {
            get
            {
                var oResult = new object[cmbXAxis.Items.Count];
                cmbXAxis.Items.CopyTo(oResult, 0);
                return oResult;
            }
            set
            {
                cmbXAxis.Items.Clear();
                cmbXAxis.Items.AddRange(value);
                cmbXAxis.SelectedIndex = 0;
            }
        }

        public int SelectedIndex
        {
            get { return cmbXAxis.SelectedIndex; }
            set { cmbXAxis.SelectedIndex = value; }
        }

        /// <summary>
        ///     Clean up any resources being used.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (components != null)
                {
                    components.Dispose();
                }
            }
            base.Dispose(disposing);
        }

        private void FormChangeTimeCoursePlot_Closing(object sender, CancelEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }

        private void cmdOK_Click(object sender, EventArgs e)
        {
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///     Required method for Designer support - do not modify
        ///     the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            var resources = new System.ComponentModel.ComponentResourceManager(typeof (FormChangeTimeCoursePlot));
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.chkAntiAlias = new System.Windows.Forms.CheckBox();
            this.panel4 = new System.Windows.Forms.Panel();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.cmbXAxis = new System.Windows.Forms.ComboBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.cmdOK = new System.Windows.Forms.Button();
            this.cmdCancel = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel4.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.panel3);
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(3, 3);
            this.panel1.Name = "panel1";
            this.panel1.Padding = new System.Windows.Forms.Padding(3);
            this.panel1.Size = new System.Drawing.Size(286, 260);
            this.panel1.TabIndex = 0;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.chkAntiAlias);
            this.panel3.Controls.Add(this.panel4);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(3, 3);
            this.panel3.Name = "panel3";
            this.panel3.Padding = new System.Windows.Forms.Padding(5);
            this.panel3.Size = new System.Drawing.Size(280, 214);
            this.panel3.TabIndex = 1;
            // 
            // chkAntiAlias
            // 
            this.chkAntiAlias.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.chkAntiAlias.AutoSize = true;
            this.chkAntiAlias.Checked = true;
            this.chkAntiAlias.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkAntiAlias.Location = new System.Drawing.Point(8, 67);
            this.chkAntiAlias.Name = "chkAntiAlias";
            this.chkAntiAlias.Size = new System.Drawing.Size(142, 17);
            this.chkAntiAlias.TabIndex = 1;
            this.chkAntiAlias.Text = "Anti Alias Preview Graph";
            this.chkAntiAlias.UseVisualStyleBackColor = true;
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.groupBox1);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel4.Location = new System.Drawing.Point(5, 5);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(270, 56);
            this.panel4.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.cmbXAxis);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(270, 56);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "X Axis";
            // 
            // cmbXAxis
            // 
            this.cmbXAxis.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cmbXAxis.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbXAxis.Location = new System.Drawing.Point(3, 16);
            this.cmbXAxis.Name = "cmbXAxis";
            this.cmbXAxis.Size = new System.Drawing.Size(264, 21);
            this.cmbXAxis.TabIndex = 0;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.cmdOK);
            this.panel2.Controls.Add(this.cmdCancel);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel2.Location = new System.Drawing.Point(3, 217);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(280, 40);
            this.panel2.TabIndex = 0;
            // 
            // cmdOK
            // 
            this.cmdOK.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 ((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.cmdOK.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdOK.Location = new System.Drawing.Point(121, 5);
            this.cmdOK.Name = "cmdOK";
            this.cmdOK.Size = new System.Drawing.Size(75, 23);
            this.cmdOK.TabIndex = 1;
            this.cmdOK.Text = "OK";
            this.cmdOK.Click += new System.EventHandler(this.cmdOK_Click);
            // 
            // cmdCancel
            // 
            this.cmdCancel.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 ((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cmdCancel.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdCancel.Location = new System.Drawing.Point(201, 5);
            this.cmdCancel.Name = "cmdCancel";
            this.cmdCancel.Size = new System.Drawing.Size(75, 23);
            this.cmdCancel.TabIndex = 0;
            this.cmdCancel.Text = "Cancel";
            // 
            // FormChangeTimeCoursePlot
            // 
            this.AcceptButton = this.cmdOK;
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.CancelButton = this.cmdCancel;
            this.ClientSize = new System.Drawing.Size(292, 266);
            this.Controls.Add(this.panel1);
            try
            {
                this.Icon = ((System.Drawing.Icon) (resources.GetObject("$this.Icon")));
            }
            catch
            {
            }
            this.Name = "FormChangeTimeCoursePlot";
            this.Padding = new System.Windows.Forms.Padding(3);
            this.Text = "Customize Graph";
            this.Closing += new System.ComponentModel.CancelEventHandler(this.FormChangeTimeCoursePlot_Closing);
            this.panel1.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.panel4.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.ResumeLayout(false);
        }

        #endregion
    }
}