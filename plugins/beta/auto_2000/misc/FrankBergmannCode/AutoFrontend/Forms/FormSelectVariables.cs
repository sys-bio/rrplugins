using System;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using AutoFrontend.Controls;
using LibRoadRunner;

namespace AutoFrontend.Forms
{
    /// <summary>
    ///     Summary description for FormSelectVariables.
    /// </summary>
    public class FormSelectVariables : Form
    {
        /// <summary>
        ///     Required designer variable.
        /// </summary>
        private readonly Container components = null;

        private ArrayList _Parameters;
        private Button cmdOk;

        private SelectControl ctrlParameters;
        private SelectControl ctrlVariables;
        private Panel panel1;
        private Panel panel2;
        private Panel panel3;
        private Panel panel4;
        private Panel panel5;
        private Splitter splitter1;

        public FormSelectVariables()
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

            //
            // TODO: Add any constructor code after InitializeComponent call
            //
        }

        public FormSelectVariables(IModel oModel) : this()
        {
            InitializeFromModel(oModel);
        }

        private RoadRunner Simulator
        {
            get { return MainForm.Simulator; }
        }

        public ArrayList Parameters
        {
            get { return _Parameters; }
            set
            {
                _Parameters = value;
                ctrlParameters.SelectedItems.Clear();
                ctrlParameters.SelectedItems.AddRange(value.ToArray());
            }
        }

        public int[] SelectedVariableIndices
        {
            get
            {
                ListBox.ObjectCollection selectedItems = ctrlVariables.SelectedItems;
                var oResult = new int[selectedItems.Count];
                for (int i = 0; i < selectedItems.Count; i++)
                {
                    oResult[i] = ctrlVariables.IndexOf(selectedItems[i]);
                }

                return oResult;
            }
        }

        public int NumSelectedBoundaries
        {
            get
            {
                int nBoundary = Simulator.getNumberOfBoundarySpecies();
                int nCount = 0;

                int[] selectedIndices = ctrlParameters.SelectedIndices;
                for (int i = 0; i < Math.Min(selectedIndices.Length, nBoundary); i++)
                {
                    if (selectedIndices[i] < nBoundary)
                        nCount++;
                }
                return nCount;
            }
        }

        public int NumSelectedParameters
        {
            get
            {
                int nBoundary = Simulator.getNumberOfBoundarySpecies();
                int nCount = 0;


                int[] selectedIndices = ctrlParameters.SelectedIndices;
                for (int i = 0; i < selectedIndices.Length; i++)
                {
                    if (selectedIndices[i] >= nBoundary)
                        nCount++;
                }
                return nCount;
            }
        }

        public int[] SelectedParameters
        {
            get
            {
                int nBoundary = Simulator.getNumberOfBoundarySpecies();
                var oResult = new int[NumSelectedParameters];

                int nCount = 0;

                int[] selectedIndices = ctrlParameters.SelectedIndices;
                for (int i = 0; i < selectedIndices.Length; i++)
                {
                    if (selectedIndices[i] >= nBoundary)
                    {
                        oResult[nCount] = selectedIndices[i] - nBoundary;
                        nCount++;
                    }
                }

                return oResult;
            }
        }

        public int[] SelectedBoundarySpecies
        {
            get
            {
                int numSelectedBoundaries = NumSelectedBoundaries;
                var oResult = new int[numSelectedBoundaries];
                int[] selectedIndices = ctrlParameters.SelectedIndices;
                for (int i = 0; i < numSelectedBoundaries; i++)
                {
                    oResult[i] = selectedIndices[i];
                }
                return oResult;
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

        private void FormSelectVariables_Closing(object sender, CancelEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }

        public void InitializeFromModel(IModel oModel)
        {
            _Parameters = new ArrayList();

            ctrlParameters.AvailableItems.Clear();
            ctrlParameters.SelectedItems.Clear();

            _Parameters.AddRange(Simulator.getBoundarySpeciesNames());
            _Parameters.AddRange(Simulator.getGlobalParameterNames());

            ctrlParameters.AvailableItems.AddRange(Parameters.ToArray());

            ctrlVariables.AvailableItems.Clear();
            ctrlVariables.SelectedItems.Clear();

            ctrlVariables.AvailableItems.AddRange(Simulator.getFloatingSpeciesNames().ToArray());
            ctrlVariables.SelectedItems.AddRange(Simulator.getFloatingSpeciesNames().ToArray());
        }

        private void cmdOk_Click(object sender, EventArgs e)
        {
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///     Required method for Designer support - do not modify
        ///     the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            var resources = new System.Resources.ResourceManager(typeof (FormSelectVariables));
            this.ctrlVariables = new AutoFrontend.Controls.SelectControl();
            this.ctrlParameters = new AutoFrontend.Controls.SelectControl();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.cmdOk = new System.Windows.Forms.Button();
            this.panel5 = new System.Windows.Forms.Panel();
            this.panel1.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel4.SuspendLayout();
            this.panel5.SuspendLayout();
            this.SuspendLayout();
            // 
            // ctrlVariables
            // 
            this.ctrlVariables.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ctrlVariables.DockPadding.All = 3;
            this.ctrlVariables.Location = new System.Drawing.Point(0, 0);
            this.ctrlVariables.Name = "ctrlVariables";
            this.ctrlVariables.PropertyName = " Variables: ";
            this.ctrlVariables.SelectedIndices = new int[0];
            this.ctrlVariables.Size = new System.Drawing.Size(768, 216);
            this.ctrlVariables.TabIndex = 0;
            // 
            // ctrlParameters
            // 
            this.ctrlParameters.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ctrlParameters.DockPadding.All = 3;
            this.ctrlParameters.Location = new System.Drawing.Point(0, 0);
            this.ctrlParameters.Name = "ctrlParameters";
            this.ctrlParameters.PropertyName = " Parameters: ";
            this.ctrlParameters.SelectedIndices = new int[0];
            this.ctrlParameters.Size = new System.Drawing.Size(768, 238);
            this.ctrlParameters.TabIndex = 1;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.panel3);
            this.panel1.Controls.Add(this.splitter1);
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(768, 462);
            this.panel1.TabIndex = 2;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.ctrlParameters);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(0, 224);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(768, 238);
            this.panel3.TabIndex = 2;
            // 
            // splitter1
            // 
            this.splitter1.Dock = System.Windows.Forms.DockStyle.Top;
            this.splitter1.Location = new System.Drawing.Point(0, 216);
            this.splitter1.MinSize = 200;
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(768, 8);
            this.splitter1.TabIndex = 1;
            this.splitter1.TabStop = false;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.ctrlVariables);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel2.Location = new System.Drawing.Point(0, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(768, 216);
            this.panel2.TabIndex = 0;
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.cmdOk);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel4.Location = new System.Drawing.Point(0, 462);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(768, 40);
            this.panel4.TabIndex = 3;
            // 
            // cmdOk
            // 
            this.cmdOk.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.cmdOk.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdOk.Location = new System.Drawing.Point(680, 8);
            this.cmdOk.Name = "cmdOk";
            this.cmdOk.TabIndex = 0;
            this.cmdOk.Text = "Ok";
            this.cmdOk.Click += new System.EventHandler(this.cmdOk_Click);
            // 
            // panel5
            // 
            this.panel5.Controls.Add(this.panel1);
            this.panel5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel5.Location = new System.Drawing.Point(0, 0);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(768, 462);
            this.panel5.TabIndex = 4;
            // 
            // FormSelectVariables
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(768, 502);
            this.Controls.Add(this.panel5);
            this.Controls.Add(this.panel4);
            try
            {
                this.Icon = ((System.Drawing.Icon) (resources.GetObject("$this.Icon")));
            }
            catch
            {
            }
            this.Name = "FormSelectVariables";
            this.Text = "Select Variables and Parameters for AUTO";
            this.Closing += new System.ComponentModel.CancelEventHandler(this.FormSelectVariables_Closing);
            this.panel1.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel4.ResumeLayout(false);
            this.panel5.ResumeLayout(false);
            this.ResumeLayout(false);
        }

        #endregion
    }
}