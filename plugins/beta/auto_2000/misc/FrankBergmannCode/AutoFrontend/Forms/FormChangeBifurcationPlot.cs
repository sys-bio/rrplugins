using System;
using System.Windows.Forms;
using ZedGraph;

namespace AutoFrontend.Forms
{
    public partial class FormChangeBifurcationPlot : Form
    {
        public FormChangeBifurcationPlot(ZedGraphControl control)
        {
            InitializeComponent();
            ZedControl = control;

            chkXAuto.CheckedChanged += chkXAuto_CheckedChanged;
            chkYAuto.CheckedChanged += chkYAuto_CheckedChanged;
        }


        public ZedGraphControl ZedControl { get; set; }

        private void ApplyChangesToGraphControl(ZedGraphControl graphControl)
        {
            if (chkLogX.Checked)
                graphControl.GraphPane.XAxis.Type = AxisType.Log;
            else
                graphControl.GraphPane.XAxis.Type = AxisType.Linear;


            if (chkLogY.Checked)
                graphControl.GraphPane.YAxis.Type = AxisType.Log;
            else
                graphControl.GraphPane.YAxis.Type = AxisType.Linear;


            graphControl.IsAntiAlias = chkAntiAlias.Checked;

            if (chkXAuto.Checked)
            {
                graphControl.GraphPane.XAxis.Scale.MaxAuto = chkXAuto.Checked;
                graphControl.GraphPane.XAxis.Scale.MinAuto = chkXAuto.Checked;
            }
            else
            {
                graphControl.GraphPane.XAxis.Scale.Min = Util.ConvertToDouble(txtMinX.Text,
                                                                              graphControl.GraphPane.XAxis.Scale.Min);
                graphControl.GraphPane.XAxis.Scale.Max = Util.ConvertToDouble(txtMaxX.Text,
                                                                              graphControl.GraphPane.XAxis.Scale.Max);
            }

            if (chkYAuto.Checked)
            {
                graphControl.GraphPane.YAxis.Scale.MaxAuto = chkYAuto.Checked;
                graphControl.GraphPane.YAxis.Scale.MinAuto = chkYAuto.Checked;
            }
            else
            {
                graphControl.GraphPane.YAxis.Scale.Min = Util.ConvertToDouble(txtMinY.Text,
                                                                              graphControl.GraphPane.YAxis.Scale.Min);
                graphControl.GraphPane.YAxis.Scale.Max = Util.ConvertToDouble(txtMaxY.Text,
                                                                              graphControl.GraphPane.YAxis.Scale.Max);
            }

            graphControl.AxisChange();
            graphControl.Refresh();
        }

        private void FormChangeBifurcationPlot_FormClosing(object sender, FormClosingEventArgs e)
        {
            Hide();
            e.Cancel = true;
        }

        private void FormChangeBifurcationPlot_Load(object sender, EventArgs e)
        {
            InitializeFromControl(ZedControl);
        }

        private void FormChangeBifurcationPlot_VisibleChanged(object sender, EventArgs e)
        {
            if (Visible)
                InitializeFromControl(ZedControl);
        }

        private void InitializeFromControl(ZedGraphControl graphControl)
        {
            chkXAuto.Checked = graphControl.GraphPane.XAxis.Scale.MaxAuto & graphControl.GraphPane.XAxis.Scale.MinAuto;
            chkYAuto.Checked = graphControl.GraphPane.YAxis.Scale.MaxAuto & graphControl.GraphPane.YAxis.Scale.MinAuto;

            chkLogX.Checked = (graphControl.GraphPane.XAxis.Scale.IsLog);
            chkLogY.Checked = (graphControl.GraphPane.YAxis.Scale.IsLog);

            chkAntiAlias.Checked = graphControl.IsAntiAlias;

            txtMinX.Text = graphControl.GraphPane.XAxis.Scale.Min.ToString();
            txtMaxX.Text = graphControl.GraphPane.XAxis.Scale.Max.ToString();

            txtMinY.Text = graphControl.GraphPane.YAxis.Scale.Min.ToString();
            txtMaxY.Text = graphControl.GraphPane.YAxis.Scale.Max.ToString();
        }

        private void chkXAuto_CheckedChanged(object sender, EventArgs e)
        {
            txtMaxX.Enabled = !chkXAuto.Checked;
            txtMinX.Enabled = !chkXAuto.Checked;
        }

        private void chkYAuto_CheckedChanged(object sender, EventArgs e)
        {
            txtMaxY.Enabled = !chkYAuto.Checked;
            txtMinY.Enabled = !chkYAuto.Checked;
        }

        private void cmdApply_Click(object sender, EventArgs e)
        {
            ApplyChangesToGraphControl(ZedControl);
        }

        private void cmdCancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void cmdOK_Click(object sender, EventArgs e)
        {
            cmdApply_Click(sender, e);
            Close();
        }
    }
}