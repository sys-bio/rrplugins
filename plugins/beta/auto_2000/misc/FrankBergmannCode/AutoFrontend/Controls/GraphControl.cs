using System;
using System.Collections;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using AutoFrontend.Forms;
using LibRoadRunner;
using SBW;
using ZedGraph;

namespace AutoFrontend.Controls
{
    /// <summary>
    ///     Summary description for GraphControl.
    /// </summary>
    public class GraphControl : UserControl
    {
        private readonly FormGraphPopup _oPopup = new FormGraphPopup();
        internal NameValuePair _CurrentParameter = null;
        private IContainer components;
        private ToolTip toolTip1;
        private ZedGraphControl zedGraphControl1;

        public GraphControl()
        {
            // This call is required by the Windows.Forms Form Designer.
            InitializeComponent();

            _oPopup.StartPosition = FormStartPosition.Manual;

            zedGraphControl1.GraphPane.XAxis.Scale.MaxGrace = 0f;
            zedGraphControl1.GraphPane.XAxis.Scale.MinGrace = 0f;
            zedGraphControl1.GraphPane.YAxis.Scale.MaxGrace = 0f;
            zedGraphControl1.GraphPane.YAxis.Scale.MinGrace = 0f;

            zedGraphControl1.GraphPane.Title.IsVisible = false;
            zedGraphControl1.GraphPane.XAxis.Title.IsVisible = false;
            zedGraphControl1.GraphPane.YAxis.Title.IsVisible = false;

            zedGraphControl1.IsAntiAlias = true;
            zedGraphControl1.IsShowCursorValues = true;

            zedGraphControl1.ContextMenuBuilder += ContextMenuBuilder;

            zedGraphControl1.MouseMove += OnMouseMove;
            zedGraphControl1.Leave += OnLeave;

            zedGraphControl1.MouseUpEvent += OnMouseUpEvent;
        }


        public ZedGraphControl ZedControl
        {
            get { return zedGraphControl1; }
            set { zedGraphControl1 = value; }
        }

        public static RoadRunner Simulator
        {
            get { return MainForm.Simulator; }
        }

        private void ContextMenuBuilder(ZedGraphControl sender, ContextMenuStrip menu, Point mousePt,
                                        ZedGraphControl.ContextMenuObjectState objState)
        {
            // Find the Chart rect that contains the current mouse location
            GraphPane pane = sender.MasterPane.FindChartRect(mousePt);

            // If pane is non-null, we have a valid location.  Otherwise, the mouse is not
            // within any chart rect.
            if (pane != null && pane.XAxis.Title.IsVisible)
            {
                double x, y;
                // Convert the mouse location to X, and Y scale values
                pane.ReverseTransform(mousePt, out x, out y);

                string sParameterName = pane.XAxis.Title.Text;
                _CurrentParameter = new NameValuePair(sParameterName, x);

                menu.Items.Insert(0, new ToolStripSeparator());

                oSBWMenu = new ToolStripMenuItem("Send SBML to");
                updateSBWMenu();
                menu.Items.Insert(0, oSBWMenu);

                var oStartSimulation = new ToolStripMenuItem("Perform a Simulation");
                oStartSimulation.Click += StartSimulation;
                menu.Items.Insert(0, oStartSimulation);

                menu.Items.Insert(0, new ToolStripSeparator());
                menu.Items.Insert(0, new ToolStripMenuItem(String.Format("{0} = {1:F5}", sParameterName, x)));
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

        private void OnClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                var oPos = new Point(e.X, e.Y);
                int nIndex = 0;
                if (zedGraphControl1.GraphPane.Legend.FindPoint(oPos, zedGraphControl1.GraphPane,
                                                                zedGraphControl1.GraphPane.CalcScaleFactor(), out nIndex))
                {
                    zedGraphControl1.GraphPane.CurveList[nIndex].IsVisible =
                        !zedGraphControl1.GraphPane.CurveList[nIndex].IsVisible;
                }
            }
            zedGraphControl1.Refresh();
        }

        private void OnLeave(object sender, EventArgs e)
        {
            _oPopup.Hide();
        }

        private void OnMouseMove(object sender, MouseEventArgs e)
        {
            if (ModifierKeys == Keys.Shift)
            {
                var mousePt = new Point(e.X, e.Y);
                GraphPane pane = zedGraphControl1.MasterPane.FindChartRect(mousePt);
                if (pane != null && pane.XAxis.Title.IsVisible)
                {
                    try
                    {
                        double x, y;
                        // Convert the mouse location to X, and Y scale values
                        pane.ReverseTransform(mousePt, out x, out y);
                        string sParameterName = pane.XAxis.Title.Text;
                        _oPopup.Label = String.Format("{0} = {1:F5}", sParameterName, x);

                        Simulator.setValue(sParameterName, x);

                        //_oPopup.SetData(Simulator.simulateEx(0.0, 10.0, 100));
                        double startTime = MainForm.Instance.SetupControl.SimulationStartTime;
                        double endTime = MainForm.Instance.SetupControl.SimulationEndTime;
                        var numPoints = (int) MainForm.Instance.SetupControl.SimulationNumPoints;
                        _oPopup.SetData(Simulator.simulateEx(startTime, endTime, numPoints));

                        _oPopup.Location = MousePosition;
                        _oPopup.Show();
                    }
                    catch (Exception)
                    {
                        _oPopup.Hide();
                    }
                }
                else
                {
                    _oPopup.Hide();
                }
            }
            else
            {
                _oPopup.Hide();
            }
        }

        private bool OnMouseUpEvent(ZedGraphControl sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                int nIndex = 0;
                var oPos = new Point(e.X, e.Y);
                string sTag = null;
                if (sender.GraphPane.Legend.FindPoint(oPos, sender.GraphPane, sender.GraphPane.CalcScaleFactor(),
                                                      out nIndex))
                {
                    sTag = sender.GraphPane.CurveList[nIndex].Label.Text;
                }

                if (sTag != null)
                {
                    for (int i = 0; i < sender.GraphPane.CurveList.Count; i++)
                    {
                        if (sender.GraphPane.CurveList[i].Label.Text == sTag)
                        {
                            sender.GraphPane.CurveList[i].IsVisible = !sender.GraphPane.CurveList[i].IsVisible;
                        }
                    }

                    for (int i = 0; i < sender.GraphPane.GraphObjList.Count; i++)
                    {
                        GraphObj current = sender.GraphPane.GraphObjList[i];
                        if (current.Tag is TagData)
                        {
                            var data = current.Tag as TagData;
                            if (data.Label == sTag)
                            {
                                current.IsVisible = !current.IsVisible;
                            }
                        }
                    }
                }


                sender.Refresh();
            }
            return false;
        }

        private void StartSimulation(object sender, EventArgs e)
        {
            if (_CurrentParameter == null) return;

            try
            {
                Util.SentToSimulator(Util.GetSBMLForParameter(_CurrentParameter));
            }
            catch (Exception)
            {
                //
            }
        }

        #region // SBW Menu

        private Hashtable oAnalyzers;
        private ToolStripMenuItem oSBWMenu;

        private void oItem_Click(object sender, EventArgs e)
        {
            try
            {
                var oTemp = (SBWAnalyzer) oAnalyzers[((MenuItem) sender).Text];
                var oModule = new Module(oTemp.ModuleName);
                Service oService = oModule.getService(oTemp.ServiceName);
                oService.getMethod("void doAnalysis(string)").Send(Util.GetSBMLForParameter(_CurrentParameter));
            }
            catch (SBWException ex)
            {
                MessageBox.Show(
                    String.Format("An error while calling the Analyzer.{0}{0}{0}({1}{0}{1})", Environment.NewLine,
                                  ex.Message, ex.DetailedMessage),
                    "Error calling the Analyzer", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (Exception)
            {
            }
        }

        private void updateSBWMenu()
        {
            if (!MainForm.IsSBWAvailable)
                return;
            try
            {
                bool bWasConnected = LowLevel.SBWGetConnectionStatus();
                if (!bWasConnected)
                    LowLevel.SBWConnect();

                oSBWMenu.DropDownItems.Clear();
                oAnalyzers = new Hashtable();
                var oBroker = new Module("BROKER");
                Service oService = oBroker.getService("BROKER");
                Method oMethod = oService.getMethod("{}[] findServices(string,boolean)");
                ArrayList[] oList = oMethod.Call("/Analysis", true).get1DListArray();

                var oModules = new SortedList(CaseInsensitiveComparer.Default);

                foreach (ArrayList list in oList)
                {
                    try
                    {
                        var uniqueName = (string) list[2];
                        if (oModules.Contains(uniqueName))
                            uniqueName += String.Format(" ({0})", list[0]);
                        oModules.Add(uniqueName, list);
                    }
                    catch (Exception)
                    {
                    }
                }

                foreach (DictionaryEntry entry in oModules)
                {
                    var sKey = (string) entry.Key;
                    var list = (ArrayList) entry.Value;
                    if ("AutoCSharp" != (string) list[0])
                    {
                        var uniqueName = (string) list[2];
                        if (oAnalyzers.Contains(uniqueName))
                            uniqueName += String.Format(" ({0})", list[0]);
                        var oItem = new ToolStripMenuItem(uniqueName);

                        oAnalyzers.Add(uniqueName, new SBWAnalyzer((string) list[0], (string) list[1]));

                        oItem.Click += oItem_Click;
                        oSBWMenu.DropDownItems.Add(oItem);
                    }
                }


                if (!bWasConnected)
                    LowLevel.SBWDisconnect();
            }
            catch (Exception)
            {
            }
        }

        private class SBWAnalyzer
        {
            public SBWAnalyzer(string sModule, string sService)
            {
                ModuleName = sModule;
                ServiceName = sService;
            }

            public string ModuleName { get; set; }

            public string ServiceName { get; set; }
        }

        #endregion

        #region Component Designer generated code

        /// <summary>
        ///     Required method for Designer support - do not modify
        ///     the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.zedGraphControl1 = new ZedGraph.ZedGraphControl();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.SuspendLayout();
            // 
            // zedGraphControl1
            // 
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
            this.zedGraphControl1.Size = new System.Drawing.Size(672, 488);
            this.zedGraphControl1.TabIndex = 0;
            // 
            // GraphControl
            // 
            this.Controls.Add(this.zedGraphControl1);
            this.Name = "GraphControl";
            this.Size = new System.Drawing.Size(672, 488);
            this.ResumeLayout(false);
        }

        #endregion
    }
}