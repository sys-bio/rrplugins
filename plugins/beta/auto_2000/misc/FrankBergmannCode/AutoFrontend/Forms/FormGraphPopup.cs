using System;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using LibRoadRunner;
using ZedGraph;
using Label = System.Windows.Forms.Label;

namespace AutoFrontend.Forms
{
    /// <summary>
    ///     Summary description for FormGraphPopup.
    /// </summary>
    public class FormGraphPopup : Form
    {
        private readonly FormChangeTimeCoursePlot _ChangeTimeCoursePlot;

        /// <summary>
        ///     Required designer variable.
        /// </summary>
        private readonly Container components = null;

        private double[,] _Data;
        private Button cmdSetupGraph;

        private Label label1;
        private Panel panel4;
        private Panel panel5;
        private Panel panel6;
        private Panel panel7;
        private ZedGraphControl zedGraphControl1;

        public FormGraphPopup()
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

            zedGraphControl1.GraphPane.XAxis.Title.IsVisible = false;
            zedGraphControl1.GraphPane.YAxis.Title.IsVisible = false;
            zedGraphControl1.GraphPane.Title.IsVisible = false;


            _ChangeTimeCoursePlot = FormChangeTimeCoursePlot.Instance;

            zedGraphControl1.IsAntiAlias = _ChangeTimeCoursePlot.IsAntiAlias;
        }


        public static RoadRunner Simulator
        {
            get { return MainForm.Simulator; }
        }

        public string Label
        {
            get { return label1.Text; }
            set { label1.Text = value; }
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

        private void PlotData(double[,] oData)
        {
            var oRotator = new ColorSymbolRotator();
            zedGraphControl1.GraphPane.CurveList.Clear();
            zedGraphControl1.IsAntiAlias = _ChangeTimeCoursePlot.IsAntiAlias;

            var oColumnNames = new ArrayList(_ChangeTimeCoursePlot.XAxisValues);

            // Assumptions: 
            //
            //      - one column is used exclusively for x data 
            //        this column is usually 0 = time, but maybe changed
            //      - Hence in n columns there are n-1 curves to plut
            //        UNLESS the selected one is not time then we have n-2 curves ... 
            //

            int nSelectedXAxis = _ChangeTimeCoursePlot.SelectedIndex;
            int numCurves = oData.GetLength(1) - 1 - (nSelectedXAxis == 0 ? 0 : 1);


            var oLists = new PointPairList[numCurves];

            int nIndex = 1;
            for (int i = 0; i < numCurves; i++)
            {
                if (nIndex == nSelectedXAxis)
                    nIndex++;
                oLists[i] = new PointPairList();
                for (int j = 0; j < oData.GetLength(0); j++)
                {
                    oLists[i].Add(oData[j, nSelectedXAxis], oData[j, nIndex]);
                }

                zedGraphControl1.GraphPane.AddCurve((string) oColumnNames[nIndex], oLists[i], oRotator.NextColor,
                                                    SymbolType.None);
                nIndex++;
            }

            zedGraphControl1.AxisChange();
            zedGraphControl1.Invalidate();
        }

        public void SetData(double[,] oData)
        {
            _Data = oData;

            PlotData(oData);
        }

        private void cmdSetupGraph_Click(object sender, EventArgs e)
        {
            if (_ChangeTimeCoursePlot.ShowDialog() == DialogResult.OK)
            {
                PlotData(_Data);
            }

            MainForm.Instance.Focus();
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///     Required method for Designer support - do not modify
        ///     the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.zedGraphControl1 = new ZedGraph.ZedGraphControl();
            this.panel4 = new System.Windows.Forms.Panel();
            this.panel5 = new System.Windows.Forms.Panel();
            this.panel6 = new System.Windows.Forms.Panel();
            this.panel7 = new System.Windows.Forms.Panel();
            this.cmdSetupGraph = new System.Windows.Forms.Button();
            this.panel4.SuspendLayout();
            this.panel5.SuspendLayout();
            this.panel6.SuspendLayout();
            this.panel7.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label1.Location = new System.Drawing.Point(0, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(232, 32);
            this.label1.TabIndex = 0;
            this.label1.Text = "Parameter";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // zedGraphControl1
            // 
            this.zedGraphControl1.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.zedGraphControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.zedGraphControl1.Location = new System.Drawing.Point(0, 0);
            this.zedGraphControl1.Name = "zedGraphControl1";
            this.zedGraphControl1.ScrollGrace = 0;
            this.zedGraphControl1.ScrollMaxX = 0;
            this.zedGraphControl1.ScrollMaxY = 0;
            this.zedGraphControl1.ScrollMaxY2 = 0;
            this.zedGraphControl1.ScrollMinX = 0;
            this.zedGraphControl1.ScrollMinY = 0;
            this.zedGraphControl1.ScrollMinY2 = 0;
            this.zedGraphControl1.Size = new System.Drawing.Size(232, 168);
            this.zedGraphControl1.TabIndex = 0;
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.panel7);
            this.panel4.Controls.Add(this.panel6);
            this.panel4.Controls.Add(this.panel5);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel4.Location = new System.Drawing.Point(0, 0);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(232, 232);
            this.panel4.TabIndex = 3;
            // 
            // panel5
            // 
            this.panel5.Controls.Add(this.label1);
            this.panel5.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel5.Location = new System.Drawing.Point(0, 0);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(232, 32);
            this.panel5.TabIndex = 0;
            // 
            // panel6
            // 
            this.panel6.Controls.Add(this.cmdSetupGraph);
            this.panel6.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel6.Location = new System.Drawing.Point(0, 200);
            this.panel6.Name = "panel6";
            this.panel6.Size = new System.Drawing.Size(232, 32);
            this.panel6.TabIndex = 1;
            // 
            // panel7
            // 
            this.panel7.Controls.Add(this.zedGraphControl1);
            this.panel7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel7.Location = new System.Drawing.Point(0, 32);
            this.panel7.Name = "panel7";
            this.panel7.Size = new System.Drawing.Size(232, 168);
            this.panel7.TabIndex = 2;
            // 
            // cmdSetupGraph
            // 
            this.cmdSetupGraph.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdSetupGraph.Location = new System.Drawing.Point(152, 4);
            this.cmdSetupGraph.Name = "cmdSetupGraph";
            this.cmdSetupGraph.TabIndex = 0;
            this.cmdSetupGraph.Text = "...";
            this.cmdSetupGraph.Click += new System.EventHandler(this.cmdSetupGraph_Click);
            // 
            // FormGraphPopup
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.ClientSize = new System.Drawing.Size(232, 232);
            this.Controls.Add(this.panel4);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "FormGraphPopup";
            this.ShowInTaskbar = false;
            this.Text = "FormGraphPopup";
            this.TopMost = true;
            this.panel4.ResumeLayout(false);
            this.panel5.ResumeLayout(false);
            this.panel6.ResumeLayout(false);
            this.panel7.ResumeLayout(false);
            this.ResumeLayout(false);
        }

        #endregion
    }
}