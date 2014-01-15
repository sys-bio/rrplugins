using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace AutoFrontend.Controls
{
    /// <summary>
    ///     Summary description for SelectControl.
    /// </summary>
    public class SelectControl : UserControl
    {
        /// <summary>
        ///     Required designer variable.
        /// </summary>
        private readonly Container components = null;

        private Button cmdAdd;
        private Button cmdAddAll;
        private Button cmdRemove;
        private Button cmdRemoveAll;
        private GroupBox groupBox2;
        private GroupBox groupBox3;
        private GroupBox grpLabel;
        private ListBox lstAvailable;
        private ListBox lstSelected;
        private Panel panel1;
        private Panel panel2;
        private Panel panel3;
        private Panel panel4;

        public SelectControl()
        {
            // This call is required by the Windows.Forms Form Designer.
            InitializeComponent();

            // TODO: Add any initialization after the InitializeComponent call
        }

        public string PropertyName
        {
            get { return grpLabel.Text; }
            set { grpLabel.Text = value; }
        }

        public ListBox.ObjectCollection AvailableItems
        {
            get { return lstAvailable.Items; }
            set
            {
                lstAvailable.Items.Clear();
                lstAvailable.Items.AddRange(value);
            }
        }

        public ListBox.ObjectCollection SelectedItems
        {
            get { return lstSelected.Items; }
            set
            {
                lstSelected.Items.Clear();
                lstSelected.Items.AddRange(value);
            }
        }

        public int[] SelectedIndices
        {
            get
            {
                ListBox.ObjectCollection selectedItems = SelectedItems;
                var oResult = new int[selectedItems.Count];
                for (int i = 0; i < selectedItems.Count; i++)
                {
                    oResult[i] = IndexOf(selectedItems[i]);
                }

                return oResult;
            }
            set
            {
                lstSelected.Items.Clear();
                for (int i = 0; i < value.Length; i++)
                {
                    lstSelected.Items.Add(lstAvailable.Items[value[i]]);
                }
            }
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

        public int IndexOf(object obj)
        {
            return lstAvailable.Items.IndexOf(obj);
        }

        public int SelectItem(object obj)
        {
            if (lstAvailable.Items.Contains(obj))
            {
                if (!lstSelected.Items.Contains(obj))
                    lstSelected.Items.Add(obj);
                return IndexOf(obj);
            }
            return -1;
        }

        private void cmdAddAll_Click(object sender, EventArgs e)
        {
            lstSelected.Items.Clear();
            lstSelected.Items.AddRange(lstAvailable.Items);
        }

        private void cmdAdd_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < lstAvailable.SelectedItems.Count; i++)
            {
                if (!lstSelected.Items.Contains(lstAvailable.SelectedItems[i]))
                    lstSelected.Items.Add(lstAvailable.SelectedItems[i]);
            }
        }

        private void cmdRemoveAll_Click(object sender, EventArgs e)
        {
            lstSelected.Items.Clear();
        }

        private void cmdRemove_Click(object sender, EventArgs e)
        {
            ListBox.SelectedIndexCollection oObjects = lstSelected.SelectedIndices;
            for (int i = oObjects.Count - 1; i >= 0; i--)
            {
                lstSelected.Items.RemoveAt(oObjects[i]);
            }
        }

        private void lstAvailable_DoubleClick(object sender, EventArgs e)
        {
            cmdAdd_Click(sender, e);
        }

        private void lstSelected_DoubleClick(object sender, EventArgs e)
        {
            cmdRemove_Click(sender, e);
        }

        #region Component Designer generated code

        /// <summary>
        ///     Required method for Designer support - do not modify
        ///     the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.grpLabel = new System.Windows.Forms.GroupBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.lstAvailable = new System.Windows.Forms.ListBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.lstSelected = new System.Windows.Forms.ListBox();
            this.cmdAddAll = new System.Windows.Forms.Button();
            this.cmdAdd = new System.Windows.Forms.Button();
            this.cmdRemove = new System.Windows.Forms.Button();
            this.cmdRemoveAll = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.grpLabel.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel4.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // grpLabel
            // 
            this.grpLabel.Controls.Add(this.panel2);
            this.grpLabel.Controls.Add(this.panel1);
            this.grpLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.grpLabel.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.grpLabel.Location = new System.Drawing.Point(3, 3);
            this.grpLabel.Name = "grpLabel";
            this.grpLabel.Size = new System.Drawing.Size(494, 194);
            this.grpLabel.TabIndex = 0;
            this.grpLabel.TabStop = false;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.groupBox2);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel1.DockPadding.All = 3;
            this.panel1.Location = new System.Drawing.Point(3, 16);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(200, 175);
            this.panel1.TabIndex = 0;
            // 
            // lstAvailable
            // 
            this.lstAvailable.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lstAvailable.Location = new System.Drawing.Point(3, 16);
            this.lstAvailable.Name = "lstAvailable";
            this.lstAvailable.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.lstAvailable.Size = new System.Drawing.Size(188, 147);
            this.lstAvailable.TabIndex = 0;
            this.lstAvailable.DoubleClick += new System.EventHandler(this.lstAvailable_DoubleClick);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.panel4);
            this.panel2.Controls.Add(this.panel3);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(203, 16);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(288, 175);
            this.panel2.TabIndex = 1;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.cmdRemoveAll);
            this.panel3.Controls.Add(this.cmdRemove);
            this.panel3.Controls.Add(this.cmdAdd);
            this.panel3.Controls.Add(this.cmdAddAll);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel3.Location = new System.Drawing.Point(0, 0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(88, 175);
            this.panel3.TabIndex = 0;
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.groupBox3);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel4.Location = new System.Drawing.Point(88, 0);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(200, 175);
            this.panel4.TabIndex = 1;
            // 
            // lstSelected
            // 
            this.lstSelected.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lstSelected.Location = new System.Drawing.Point(3, 16);
            this.lstSelected.Name = "lstSelected";
            this.lstSelected.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.lstSelected.Size = new System.Drawing.Size(194, 147);
            this.lstSelected.TabIndex = 0;
            this.lstSelected.DoubleClick += new System.EventHandler(this.lstSelected_DoubleClick);
            // 
            // cmdAddAll
            // 
            this.cmdAddAll.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdAddAll.Location = new System.Drawing.Point(8, 32);
            this.cmdAddAll.Name = "cmdAddAll";
            this.cmdAddAll.TabIndex = 0;
            this.cmdAddAll.Text = "Add All";
            this.cmdAddAll.Click += new System.EventHandler(this.cmdAddAll_Click);
            // 
            // cmdAdd
            // 
            this.cmdAdd.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdAdd.Location = new System.Drawing.Point(8, 64);
            this.cmdAdd.Name = "cmdAdd";
            this.cmdAdd.TabIndex = 1;
            this.cmdAdd.Text = "Add";
            this.cmdAdd.Click += new System.EventHandler(this.cmdAdd_Click);
            // 
            // cmdRemove
            // 
            this.cmdRemove.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdRemove.Location = new System.Drawing.Point(8, 104);
            this.cmdRemove.Name = "cmdRemove";
            this.cmdRemove.TabIndex = 2;
            this.cmdRemove.Text = "Remove";
            this.cmdRemove.Click += new System.EventHandler(this.cmdRemove_Click);
            // 
            // cmdRemoveAll
            // 
            this.cmdRemoveAll.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdRemoveAll.Location = new System.Drawing.Point(8, 136);
            this.cmdRemoveAll.Name = "cmdRemoveAll";
            this.cmdRemoveAll.TabIndex = 3;
            this.cmdRemoveAll.Text = "Remove All";
            this.cmdRemoveAll.Click += new System.EventHandler(this.cmdRemoveAll_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.lstAvailable);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox2.Location = new System.Drawing.Point(3, 3);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(194, 169);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = " Available: ";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.lstSelected);
            this.groupBox3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox3.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox3.Location = new System.Drawing.Point(0, 0);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(200, 175);
            this.groupBox3.TabIndex = 1;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = " Selected: ";
            // 
            // SelectControl
            // 
            this.Controls.Add(this.grpLabel);
            this.DockPadding.All = 3;
            this.Name = "SelectControl";
            this.Size = new System.Drawing.Size(500, 200);
            this.grpLabel.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.panel4.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.ResumeLayout(false);
        }

        #endregion
    }
}