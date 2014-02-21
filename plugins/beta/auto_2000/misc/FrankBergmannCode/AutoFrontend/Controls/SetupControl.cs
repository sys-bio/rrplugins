using System;
using System.ComponentModel;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using AutoFrontend.Forms;
using LibAutoCSharp;
using LibRoadRunner;

namespace AutoFrontend.Controls
{
    /// <summary>
    ///     Summary description for SetupControl.
    /// </summary>
    public class SetupControl : UserControl
    {
        private readonly FormGraphPopup _oPopup = new FormGraphPopup();
        private AutoInputConstants _CurrentConfig = AutoInputConstants.DefaultConstants;
        private CheckBox chkAutoSteadyState;
        private CheckBox chkReload;
        private ComboBox cmbParameters;
        private Button cmdLoadSBML;
        private Button cmdRun;
        private Button cmdSimReset;
        private Button cmdSimSendToSimDriver;
        private Button cmdSimSimulate;
        private Button cmdSteadyState;
        private IContainer components;
        private GroupBox groupBox1;
        private GroupBox groupBox2;
        private GroupBox groupBox4;
        private GroupBox grpSimulation;
        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private Label label5;
        private Label label6;
        private Label label7;
        private Label label8;
        private Label label9;
        private Panel panel1;
        private Panel panel2;
        private Panel panel3;
        private Panel panel4;
        private RadioButton radBackward;
        private RadioButton radForward;
        private ToolTip toolTip1;
        private TextBox txtEnd;
        private TextBox txtMaxSteps;
        private TextBox txtNumBifurcationsToTrack;
        private TextBox txtSimNumPoints;
        private TextBox txtSimTimeEnd;
        private TextBox txtSimTimeStart;
        private TextBox txtStart;
        private TextBox txtSteadyResult;

        public SetupControl()
        {
            // This call is required by the Windows.Forms Form Designer.
            InitializeComponent();

            // TODO: Add any initialization after the InitializeComponent call
            _oPopup.StartPosition = FormStartPosition.Manual;
            _oPopup.Location = grpSimulation.PointToScreen(new Point(0, 0));


            txtEnd.TextChanged += UpdateConfig;
            txtMaxSteps.TextChanged += UpdateConfig;
            txtNumBifurcationsToTrack.TextChanged += UpdateConfig;
            txtStart.TextChanged += UpdateConfig;
            radBackward.CheckedChanged += UpdateConfig;
            radForward.CheckedChanged += UpdateConfig;
        }


        private RoadRunner Simulator
        {
            get { return MainForm.Simulator; }
        }


        public bool CalculateSteadyState
        {
            get { return chkAutoSteadyState.Checked; }
            set { chkAutoSteadyState.Checked = value; }
        }

        public double StartValue
        {
            get { return Util.ConvertToDouble(txtStart.Text, 0.01); }
            set { txtStart.Text = value.ToString(); }
        }

        public int MaxBifurcations
        {
            get { return Util.ConvertToInt(txtNumBifurcationsToTrack.Text, -1); }
            set { txtNumBifurcationsToTrack.Text = value.ToString(); }
        }


        public int MaxSteps
        {
            get { return Util.ConvertToInt(txtMaxSteps.Text, 1000); }
            set { txtMaxSteps.Text = value.ToString(); }
        }

        public double EndValue
        {
            get { return Util.ConvertToDouble(txtEnd.Text, 10.0); }
            set { txtEnd.Text = value.ToString(); }
        }

        public string Parameter
        {
            get { return cmbParameters.Text; }
            set { cmbParameters.Text = value; }
        }


        public double SimulationStartTime
        {
            get { return Util.ConvertToDouble(txtSimTimeStart.Text, 0.0); }
            set { txtSimTimeStart.Text = value.ToString(); }
        }

        public double SimulationEndTime
        {
            get { return Util.ConvertToDouble(txtSimTimeEnd.Text, 10.0); }
            set { txtSimTimeEnd.Text = value.ToString(); }
        }

        public double SimulationNumPoints
        {
            get { return Util.ConvertToDouble(txtSimNumPoints.Text, 100); }
            set { txtSimNumPoints.Text = value.ToString(); }
        }

        public bool DirectionPositive
        {
            get { return radForward.Checked; }
            set
            {
                if (value)
                    radForward.Checked = true;
                else
                    radBackward.Checked = true;
            }
        }

        public bool ReloadAfterRun
        {
            get { return chkReload.Checked; }
        }

        public object[] Parameters
        {
            get
            {
                var oResult = new object[cmbParameters.Items.Count];
                cmbParameters.Items.CopyTo(oResult, 0);
                return oResult;
            }
            set
            {
                cmbParameters.Items.Clear();
                cmbParameters.Items.AddRange(value);
                if (cmbParameters.Items.Count > 0)
                {
                    cmbParameters.SelectedIndex = 0;
                    cmbParameters.Enabled = true;
                }
            }
        }

        public bool ParameterAvailable
        {
            get { return cmbParameters.Enabled; }
            set
            {
                cmbParameters.Enabled = value;
                if (!cmbParameters.Enabled)
                {
                    cmbParameters.Items.Clear();
                }
            }
        }


        public int Label { get; set; }

        public bool RunContinuation { get; set; }


        public AutoInputConstants CurrentConfig
        {
            get { return _CurrentConfig; }
            set { _CurrentConfig = value; }
        }

        public string Configuration
        {
            get
            {
                return CurrentConfig.ToInputString();

                //int nDim = GetNumFloating();
                //if (RunContinuation)
                //    return new LibAutoCSharp.AutoConfiguration(
                //    Util.ConvertToDouble(txtStart.Text, 0.01),
                //    Util.ConvertToDouble(txtEnd.Text, 10.0),
                //    radForward.Checked, nDim, Util.ConvertToInt(txtMaxSteps.Text, 1000), Label).GenerateConfigFile();
                //else

                //return new LibAutoCSharp.AutoConfiguration(
                //    Util.ConvertToDouble(txtStart.Text, 0.01),
                //    Util.ConvertToDouble(txtEnd.Text, 10.0), 
                //    radForward.Checked, nDim, Util.ConvertToInt(txtMaxSteps.Text, 1000)).GenerateConfigFile();
            }
        }

        internal void CalculateSteadyStateIfNecessary()
        {
            if (CalculateSteadyState)
                DoCalculateSteadyState();
        }

        public bool Contains(string sId)
        {
            return cmbParameters.Items.Contains(sId);
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

        internal void DoCalculateSteadyState()
        {
            try
            {
                txtSteadyResult.Text = Simulator.steadyState().ToString();
            }
            catch
            {
                txtSteadyResult.Text = "(could not compute)";
            }
        }

        private int GetNumFloating()
        {
            int nDim;
            try
            {
                if (!Simulator.modelLoaded) return 2;
                nDim = Simulator.getNumberOfFloatingSpecies();
            }
            catch (Exception)
            {
                nDim = 2;
            }
            return nDim;
        }

        private void UpdateConfig(object sender, EventArgs e)
        {
            CurrentConfig.NDIM = GetNumFloating();
            CurrentConfig.MXBF = Util.ConvertToInt(txtNumBifurcationsToTrack.Text, -1);
            CurrentConfig.RL0 = Util.ConvertToDouble(txtStart.Text, 0.01);
            CurrentConfig.RL1 = Util.ConvertToDouble(txtEnd.Text, 10.0);
            CurrentConfig.NMX = Util.ConvertToInt(txtMaxSteps.Text, 1000);

            if (radForward.Checked)
            {
                CurrentConfig.DS = Math.Abs(CurrentConfig.DS);
            }
            else
            {
                CurrentConfig.DS = Math.Abs(CurrentConfig.DS)*-1.0;
            }

            //int nDim = GetNumFloating();
            //if (RunContinuation)
            //    return new LibAutoCSharp.AutoConfiguration(
            //    Util.ConvertToDouble(txtStart.Text, 0.01),
            //    Util.ConvertToDouble(txtEnd.Text, 10.0),
            //    radForward.Checked, nDim, Util.ConvertToInt(txtMaxSteps.Text, 1000), Label).GenerateConfigFile();
            //else

            //return new LibAutoCSharp.AutoConfiguration(
            //    Util.ConvertToDouble(txtStart.Text, 0.01),
            //    Util.ConvertToDouble(txtEnd.Text, 10.0), 
            //    radForward.Checked, nDim, Util.ConvertToInt(txtMaxSteps.Text, 1000)).GenerateConfigFile();
        }

        private void cmdLoadSBML_Click(object sender, EventArgs e)
        {
            _oPopup.Location = grpSimulation.PointToScreen(new Point(0, 0));
            MainForm.Instance.OpenSBML();
        }

        private void cmdRun_Click(object sender, EventArgs e)
        {
            MainForm.Instance.RunAuto();
        }

        private void cmdSimReset_Click(object sender, EventArgs e)
        {
            Simulator.reset();
        }

        private void cmdSimSendToSimDriver_Click(object sender, EventArgs e)
        {
            Util.SentToSimulator(MainForm.SBML);
        }

        private void cmdSimSimulate_Click(object sender, EventArgs e)
        {
            try
            {
                _oPopup.Label = "Simulation";
                _oPopup.SetData(Simulator.simulateEx(
                    Util.ConvertToDouble(txtSimTimeStart.Text, 0.0),
                    Util.ConvertToDouble(txtSimTimeEnd.Text, 10.0),
                    Util.ConvertToInt(txtSimNumPoints.Text, 1000)));

                _oPopup.Location = grpSimulation.PointToScreen(new Point(0, 0));
                Application.DoEvents();
                _oPopup.Show();
                _oPopup.Refresh();

                Application.DoEvents();

                Thread.Sleep(2000);

                _oPopup.Hide();
            }
            catch (Exception)
            {
            }
        }

        private void cmdSteadyState_Click(object sender, EventArgs e)
        {
            DoCalculateSteadyState();
        }

        #region Component Designer generated code

        /// <summary>
        ///     Required method for Designer support - do not modify
        ///     the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.txtMaxSteps = new System.Windows.Forms.TextBox();
            this.chkReload = new System.Windows.Forms.CheckBox();
            this.cmdLoadSBML = new System.Windows.Forms.Button();
            this.cmdRun = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.radBackward = new System.Windows.Forms.RadioButton();
            this.radForward = new System.Windows.Forms.RadioButton();
            this.label3 = new System.Windows.Forms.Label();
            this.cmbParameters = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtEnd = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txtStart = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.chkAutoSteadyState = new System.Windows.Forms.CheckBox();
            this.cmdSteadyState = new System.Windows.Forms.Button();
            this.txtSteadyResult = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.grpSimulation = new System.Windows.Forms.GroupBox();
            this.cmdSimSendToSimDriver = new System.Windows.Forms.Button();
            this.cmdSimReset = new System.Windows.Forms.Button();
            this.cmdSimSimulate = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.txtSimNumPoints = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.txtSimTimeEnd = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.txtSimTimeStart = new System.Windows.Forms.TextBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.label9 = new System.Windows.Forms.Label();
            this.txtNumBifurcationsToTrack = new System.Windows.Forms.TextBox();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.groupBox1.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.grpSimulation.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel4.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.txtNumBifurcationsToTrack);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.txtMaxSteps);
            this.groupBox1.Controls.Add(this.chkReload);
            this.groupBox1.Controls.Add(this.cmdLoadSBML);
            this.groupBox1.Controls.Add(this.cmdRun);
            this.groupBox1.Controls.Add(this.groupBox4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.cmbParameters);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.txtEnd);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txtStart);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(210, 255);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = " Auto Settings: ";
            // 
            // label8
            // 
            this.label8.Location = new System.Drawing.Point(8, 102);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(80, 23);
            this.label8.TabIndex = 11;
            this.label8.Text = "Max Steps:";
            // 
            // txtMaxSteps
            // 
            this.txtMaxSteps.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.txtMaxSteps.Location = new System.Drawing.Point(96, 99);
            this.txtMaxSteps.Name = "txtMaxSteps";
            this.txtMaxSteps.Size = new System.Drawing.Size(100, 20);
            this.txtMaxSteps.TabIndex = 6;
            this.txtMaxSteps.Text = "1000";
            this.txtMaxSteps.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.toolTip1.SetToolTip(this.txtMaxSteps,
                                     "Maximum Number of Steps to Perform, increase this if End Value is never reached");
            // 
            // chkReload
            // 
            this.chkReload.AutoSize = true;
            this.chkReload.Checked = true;
            this.chkReload.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkReload.Location = new System.Drawing.Point(8, 231);
            this.chkReload.Name = "chkReload";
            this.chkReload.Size = new System.Drawing.Size(139, 17);
            this.chkReload.TabIndex = 12;
            this.chkReload.Text = "Reload Model after Run";
            this.chkReload.UseVisualStyleBackColor = true;
            // 
            // cmdLoadSBML
            // 
            this.cmdLoadSBML.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdLoadSBML.Location = new System.Drawing.Point(8, 204);
            this.cmdLoadSBML.Name = "cmdLoadSBML";
            this.cmdLoadSBML.Size = new System.Drawing.Size(88, 23);
            this.cmdLoadSBML.TabIndex = 10;
            this.cmdLoadSBML.Text = "&Load";
            this.cmdLoadSBML.Click += new System.EventHandler(this.cmdLoadSBML_Click);
            // 
            // cmdRun
            // 
            this.cmdRun.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdRun.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdRun.Location = new System.Drawing.Point(104, 204);
            this.cmdRun.Name = "cmdRun";
            this.cmdRun.Size = new System.Drawing.Size(96, 23);
            this.cmdRun.TabIndex = 9;
            this.cmdRun.Text = "&Run";
            this.cmdRun.Click += new System.EventHandler(this.cmdRun_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox4.Controls.Add(this.radBackward);
            this.groupBox4.Controls.Add(this.radForward);
            this.groupBox4.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.groupBox4.Location = new System.Drawing.Point(8, 148);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(192, 48);
            this.groupBox4.TabIndex = 8;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = " Direction:      ";
            // 
            // radBackward
            // 
            this.radBackward.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.radBackward.Location = new System.Drawing.Point(96, 17);
            this.radBackward.Name = "radBackward";
            this.radBackward.Size = new System.Drawing.Size(64, 24);
            this.radBackward.TabIndex = 1;
            this.radBackward.Text = "Negative";
            // 
            // radForward
            // 
            this.radForward.Checked = true;
            this.radForward.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.radForward.Location = new System.Drawing.Point(8, 17);
            this.radForward.Name = "radForward";
            this.radForward.Size = new System.Drawing.Size(64, 24);
            this.radForward.TabIndex = 0;
            this.radForward.TabStop = true;
            this.radForward.Text = "Positive";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(8, 72);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(80, 23);
            this.label3.TabIndex = 5;
            this.label3.Text = "Parameter:";
            // 
            // cmbParameters
            // 
            this.cmbParameters.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.cmbParameters.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbParameters.Enabled = false;
            this.cmbParameters.Location = new System.Drawing.Point(96, 72);
            this.cmbParameters.Name = "cmbParameters";
            this.cmbParameters.Size = new System.Drawing.Size(96, 21);
            this.cmbParameters.TabIndex = 4;
            this.toolTip1.SetToolTip(this.cmbParameters, "Bifurcation Parameter");
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(8, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(80, 23);
            this.label2.TabIndex = 3;
            this.label2.Text = "End Value:";
            // 
            // txtEnd
            // 
            this.txtEnd.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.txtEnd.Location = new System.Drawing.Point(96, 48);
            this.txtEnd.Name = "txtEnd";
            this.txtEnd.Size = new System.Drawing.Size(100, 20);
            this.txtEnd.TabIndex = 2;
            this.txtEnd.Text = "10.0";
            this.txtEnd.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.toolTip1.SetToolTip(this.txtEnd, "End Value for the Parameter");
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(8, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(80, 23);
            this.label1.TabIndex = 1;
            this.label1.Text = "Start Value:";
            // 
            // txtStart
            // 
            this.txtStart.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.txtStart.Location = new System.Drawing.Point(96, 24);
            this.txtStart.Name = "txtStart";
            this.txtStart.Size = new System.Drawing.Size(100, 20);
            this.txtStart.TabIndex = 0;
            this.txtStart.Text = "0.01";
            this.txtStart.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.toolTip1.SetToolTip(this.txtStart, "Start Value For the Parameter");
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.chkAutoSteadyState);
            this.groupBox2.Controls.Add(this.cmdSteadyState);
            this.groupBox2.Controls.Add(this.txtSteadyResult);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox2.Location = new System.Drawing.Point(0, 0);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(210, 136);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = " Steady State: ";
            // 
            // chkAutoSteadyState
            // 
            this.chkAutoSteadyState.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.chkAutoSteadyState.Checked = true;
            this.chkAutoSteadyState.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkAutoSteadyState.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chkAutoSteadyState.Location = new System.Drawing.Point(8, 104);
            this.chkAutoSteadyState.Name = "chkAutoSteadyState";
            this.chkAutoSteadyState.Size = new System.Drawing.Size(192, 24);
            this.chkAutoSteadyState.TabIndex = 3;
            this.chkAutoSteadyState.Text = "Bring Model to Steadystate before a Run";
            // 
            // cmdSteadyState
            // 
            this.cmdSteadyState.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdSteadyState.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdSteadyState.Location = new System.Drawing.Point(8, 72);
            this.cmdSteadyState.Name = "cmdSteadyState";
            this.cmdSteadyState.Size = new System.Drawing.Size(192, 23);
            this.cmdSteadyState.TabIndex = 2;
            this.cmdSteadyState.Text = "Steadystate";
            this.cmdSteadyState.Click += new System.EventHandler(this.cmdSteadyState_Click);
            // 
            // txtSteadyResult
            // 
            this.txtSteadyResult.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.txtSteadyResult.Location = new System.Drawing.Point(8, 48);
            this.txtSteadyResult.Name = "txtSteadyResult";
            this.txtSteadyResult.Size = new System.Drawing.Size(192, 20);
            this.txtSteadyResult.TabIndex = 1;
            this.txtSteadyResult.Text = "(not calculated)";
            this.txtSteadyResult.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label4
            // 
            this.label4.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.label4.Location = new System.Drawing.Point(8, 24);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(192, 23);
            this.label4.TabIndex = 0;
            this.label4.Text = "Closeness to Steadystate";
            // 
            // grpSimulation
            // 
            this.grpSimulation.Controls.Add(this.cmdSimSendToSimDriver);
            this.grpSimulation.Controls.Add(this.cmdSimReset);
            this.grpSimulation.Controls.Add(this.cmdSimSimulate);
            this.grpSimulation.Controls.Add(this.label7);
            this.grpSimulation.Controls.Add(this.txtSimNumPoints);
            this.grpSimulation.Controls.Add(this.label5);
            this.grpSimulation.Controls.Add(this.txtSimTimeEnd);
            this.grpSimulation.Controls.Add(this.label6);
            this.grpSimulation.Controls.Add(this.txtSimTimeStart);
            this.grpSimulation.Dock = System.Windows.Forms.DockStyle.Fill;
            this.grpSimulation.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.grpSimulation.Location = new System.Drawing.Point(0, 0);
            this.grpSimulation.Name = "grpSimulation";
            this.grpSimulation.Size = new System.Drawing.Size(210, 128);
            this.grpSimulation.TabIndex = 2;
            this.grpSimulation.TabStop = false;
            this.grpSimulation.Text = " Simulation: ";
            // 
            // cmdSimSendToSimDriver
            // 
            this.cmdSimSendToSimDriver.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdSimSendToSimDriver.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdSimSendToSimDriver.Location = new System.Drawing.Point(8, 136);
            this.cmdSimSendToSimDriver.Name = "cmdSimSendToSimDriver";
            this.cmdSimSendToSimDriver.Size = new System.Drawing.Size(192, 23);
            this.cmdSimSendToSimDriver.TabIndex = 12;
            this.cmdSimSendToSimDriver.Text = "Send to Simulation Tool";
            this.cmdSimSendToSimDriver.Click += new System.EventHandler(this.cmdSimSendToSimDriver_Click);
            // 
            // cmdSimReset
            // 
            this.cmdSimReset.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdSimReset.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdSimReset.Location = new System.Drawing.Point(124, 104);
            this.cmdSimReset.Name = "cmdSimReset";
            this.cmdSimReset.Size = new System.Drawing.Size(75, 23);
            this.cmdSimReset.TabIndex = 11;
            this.cmdSimReset.Text = "Reset";
            this.cmdSimReset.Click += new System.EventHandler(this.cmdSimReset_Click);
            // 
            // cmdSimSimulate
            // 
            this.cmdSimSimulate.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdSimSimulate.Location = new System.Drawing.Point(8, 104);
            this.cmdSimSimulate.Name = "cmdSimSimulate";
            this.cmdSimSimulate.Size = new System.Drawing.Size(75, 23);
            this.cmdSimSimulate.TabIndex = 10;
            this.cmdSimSimulate.Text = "Simulate";
            this.cmdSimSimulate.Click += new System.EventHandler(this.cmdSimSimulate_Click);
            // 
            // label7
            // 
            this.label7.Location = new System.Drawing.Point(8, 72);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(80, 23);
            this.label7.TabIndex = 9;
            this.label7.Text = "# Points:";
            // 
            // txtSimNumPoints
            // 
            this.txtSimNumPoints.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.txtSimNumPoints.Location = new System.Drawing.Point(96, 72);
            this.txtSimNumPoints.Name = "txtSimNumPoints";
            this.txtSimNumPoints.Size = new System.Drawing.Size(100, 20);
            this.txtSimNumPoints.TabIndex = 8;
            this.txtSimNumPoints.Text = "100";
            this.txtSimNumPoints.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(8, 48);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(80, 23);
            this.label5.TabIndex = 7;
            this.label5.Text = "End Time:";
            // 
            // txtSimTimeEnd
            // 
            this.txtSimTimeEnd.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.txtSimTimeEnd.Location = new System.Drawing.Point(96, 48);
            this.txtSimTimeEnd.Name = "txtSimTimeEnd";
            this.txtSimTimeEnd.Size = new System.Drawing.Size(100, 20);
            this.txtSimTimeEnd.TabIndex = 6;
            this.txtSimTimeEnd.Text = "10.0";
            this.txtSimTimeEnd.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(8, 24);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(80, 23);
            this.label6.TabIndex = 5;
            this.label6.Text = "Start Time:";
            // 
            // txtSimTimeStart
            // 
            this.txtSimTimeStart.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.txtSimTimeStart.Location = new System.Drawing.Point(96, 24);
            this.txtSimTimeStart.Name = "txtSimTimeStart";
            this.txtSimTimeStart.Size = new System.Drawing.Size(100, 20);
            this.txtSimTimeStart.TabIndex = 4;
            this.txtSimTimeStart.Text = "0.0";
            this.txtSimTimeStart.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.panel4);
            this.panel1.Controls.Add(this.panel3);
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Padding = new System.Windows.Forms.Padding(3);
            this.panel1.Size = new System.Drawing.Size(216, 525);
            this.panel1.TabIndex = 3;
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.grpSimulation);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel4.Location = new System.Drawing.Point(3, 394);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(210, 128);
            this.panel4.TabIndex = 2;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.groupBox2);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel3.Location = new System.Drawing.Point(3, 258);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(210, 136);
            this.panel3.TabIndex = 1;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.groupBox1);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel2.Location = new System.Drawing.Point(3, 3);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(210, 255);
            this.panel2.TabIndex = 0;
            // 
            // label9
            // 
            this.label9.Location = new System.Drawing.Point(8, 125);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(80, 23);
            this.label9.TabIndex = 13;
            this.label9.Text = "Follow #:";
            // 
            // txtNumBifurcationsToTrack
            // 
            this.txtNumBifurcationsToTrack.Anchor =
                ((System.Windows.Forms.AnchorStyles)
                 (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                   | System.Windows.Forms.AnchorStyles.Right)));
            this.txtNumBifurcationsToTrack.Location = new System.Drawing.Point(96, 122);
            this.txtNumBifurcationsToTrack.Name = "txtNumBifurcationsToTrack";
            this.txtNumBifurcationsToTrack.Size = new System.Drawing.Size(100, 20);
            this.txtNumBifurcationsToTrack.TabIndex = 7;
            this.txtNumBifurcationsToTrack.Text = "-1";
            this.txtNumBifurcationsToTrack.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.toolTip1.SetToolTip(this.txtNumBifurcationsToTrack,
                                     "Maximum Number of Bifurcations to follow, by default follow one.");
            // 
            // SetupControl
            // 
            this.Controls.Add(this.panel1);
            this.Name = "SetupControl";
            this.Size = new System.Drawing.Size(216, 525);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.grpSimulation.ResumeLayout(false);
            this.grpSimulation.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel4.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.ResumeLayout(false);
        }

        #endregion
    }
}