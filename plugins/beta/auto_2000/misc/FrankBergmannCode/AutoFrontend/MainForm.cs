using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Globalization;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using AutoFrontend.Controls;
using AutoFrontend.Forms;
using AutoFrontend.Properties;
using LibAutoCSharp;
using LibRoadRunner;
using SBW;
using ZedGraph;

namespace AutoFrontend
{
    /// <summary>
    ///     Summary description for Form1.
    /// </summary>
    public partial class MainForm : Form
    {
        private static ModelState _InitialState;
        internal static MainForm _Instance = null;
        private MenuItem changeBifurcationPlot;
        private Button cmdAssignAdvanced;
        private Button cmdParseConfig;
        private IContainer components;
        private MenuItem menuItem2;

        static MainForm()
        {
            Simulator = new RoadRunner();
            SelectForm = null;
        }

        public MainForm()
        {
            CurrentModel = null;
            CurrentResult = null;
            CultureInfo culture = CultureInfo.CreateSpecificCulture("en");
            culture.NumberFormat.NumberDecimalSeparator = ".";
            Thread.CurrentThread.CurrentCulture = culture;

            InitializeComponent();

            Icon = Resources.ICON_Auto;

            SelectForm = new FormSelectVariables();

            AllowDrop = true;

            DragDrop += OnDragDrop;
            DragEnter += OnDragEnter;

            ChangeBifurcationPlot = new FormChangeBifurcationPlot(graphControl1.ZedControl);
            graphControl1.ZedControl.MouseDoubleClick += GraphDoubleClick;
        }

        public FormChangeBifurcationPlot ChangeBifurcationPlot { get; set; }

        public AutoResult CurrentResult { get; set; }

        public static FormSelectVariables SelectForm { get; set; }

        public static RoadRunner Simulator { get; set; }

        public IModel CurrentModel { get; set; }

        internal static string SBML { get; set; }

        public static ModelState InitialState
        {
            get { return _InitialState; }
            set { _InitialState = value; }
        }

        internal static MainForm Instance
        {
            get
            {
                if (_Instance == null)
                    _Instance = new MainForm();
                return _Instance;
            }
        }

        public SetupControl SetupControl
        {
            get { return setupControl1; }
        }

        
        private void AddNthCurveToGraph(int i, IList<double[]> series, string label, Color lineColor)
        {
            var line = graphControl1.ZedControl.GraphPane.AddCurve(label, series[0],
                                                                         series[1 + i], lineColor,
                                                                         SymbolType.None);
            line.Line.Width = 2f;
            line.Line.IsSmooth = true;
        }

        private void AddNthSegmentedCurveToGraph(int i, IEnumerable<PointPairList> thickSegments, IList<double[]> series, string label,
                                                 Color lineColor)
        {
            foreach (var list in thickSegments)
            {
                var thickLine = graphControl1.ZedControl.GraphPane.AddCurve(label,
                                                                                  list,
                                                                                  lineColor, SymbolType.None);
                thickLine.Line.Width = 4f;
                thickLine.Line.IsSmooth = true;
                thickLine.Label.IsVisible = false;
            }

            var thinLine = graphControl1.ZedControl.GraphPane.AddCurve(label, series[0],
                                                                             series[i + 1], lineColor,
                                                                             SymbolType.None);
            thinLine.Line.Width = 1f;
            thinLine.Line.Style = DashStyle.Dash;
            thinLine.Line.IsSmooth = true;
        }

        public void AddWaterMark(string sMessage)
        {
            graphControl1.ZedControl.GraphPane.GraphObjList.Add(GetWaterMark(sMessage));
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

        private static IList<PointPairList> FindNthThickSegments(int i, AutoResult result, IList<double[]> series)
        {
            var oThickSegments = new List<PointPairList>();

            int nLast = 0;
            int nLastDir = -1;
            for (int j = 0; j < result.Positions.Count; j++)
            {
                IntPair oPos = result.Positions[j];
                int nCurrentSliceLength = oPos.Key - 1 - nLast;
                var oXSlice = new double[nCurrentSliceLength];
                var oYSlice = new double[nCurrentSliceLength];

                Array.Copy(series[0], nLast, oXSlice, 0, nCurrentSliceLength);
                Array.Copy(series[i + 1], nLast, oYSlice, 0, nCurrentSliceLength);
                nLastDir = oPos.Value;

                if (nLastDir > 0)
                {
                    oThickSegments.Add(new PointPairList(oXSlice, oYSlice));
                }

                nLast = oPos.Key;
            }

            if (nLast < series[0].Length)
            {
                int nLastSliceLength = series[0].Length - nLast;

                var oXSlice = new double[nLastSliceLength];
                var oYSlice = new double[nLastSliceLength];

                Array.Copy(series[0], nLast, oXSlice, 0, nLastSliceLength);
                Array.Copy(series[i + 1], nLast, oYSlice, 0, nLastSliceLength);

                if (nLastDir*-1 > 0)
                {
                    oThickSegments.Add(new PointPairList(oXSlice, oYSlice));
                }
            }
            return oThickSegments;
        }

        private string GenerateCsv(string separator = ", ")
        {
            if (CurrentResult != null && CurrentResult.Data != null && CurrentResult.Data.Count > 0)
                return CurrentResult.Data.GenerateCSV(setupControl1.Parameter, Simulator.GetFloatingSpeciesNamesArray(),
                                                      separator);
            return "";
        }

        private string GetCurrentData(bool useTab = false)
        {
            string separartor = useTab ? "\t" : ", ";

            return GenerateCsv(separartor);
        }

        private string GetNthName(int i)
        {
            try
            {
                string sLabel = "var" + i;
                if (CurrentModel != null && i < Simulator.getNumberOfFloatingSpecies())
                {
                    sLabel = (string) Simulator.getFloatingSpeciesNames()[i];
                }
                return sLabel;
            }
            catch (Exception)
            {
                return "";
            }
        }

        private GraphObj GetWaterMark(string sMessage)
        {
            var text = new TextObj(sMessage, 0.5F, 0.5F)
                {
                    Location = {CoordinateFrame = CoordType.PaneFraction},
                    FontSpec =
                        {
                            Angle = 30.0F,
                            FontColor = Color.FromArgb(70, 255, 100, 100),
                            IsBold = true,
                            Size = 100,
                            Border = {IsVisible = false},
                            Fill = {IsVisible = false}
                        }
                };
            text.Location.AlignH = AlignH.Center;
            text.Location.AlignV = AlignV.Center;
            text.ZOrder = ZOrder.A_InFront;
            return text;
        }

        private void GraphDoubleClick(object sender, MouseEventArgs e)
        {
            object graphObject;
            int index;

            graphControl1.ZedControl.GraphPane.FindNearestObject(new PointF(e.X, e.Y),
                                                                 graphControl1.ZedControl.CreateGraphics(),
                                                                 out graphObject, out index);
            if (graphObject != null)
            {
                object tag = null;
                if (graphObject is TextObj)
                    tag = (graphObject as TextObj).Tag;
                else if (graphObject is EllipseObj)
                    tag = (graphObject as EllipseObj).Tag;

                if (tag != null)
                {
                    IntTripple tripple = (tag as TagData).Tripple;
                    if (tripple != null)
                    {
                        RunContinuationForTripple(tripple);
                    }
                }
            }
        }

        private void LoadFile(string sFileName)
        {
            var oReader = new StreamReader(sFileName);
            string sSBML = oReader.ReadToEnd();
            oReader.Close();

            string fileExtension = new FileInfo(sFileName).Extension.ToUpper();
            if (fileExtension == ".JAN" || fileExtension == "JAN")
                sSBML = Util.ConvertToSBML(sSBML);


            setupControl1.MaxSteps = 1000;
            setupControl1.StartValue = 0.01;
            setupControl1.EndValue = 30;
            setupControl1.DirectionPositive = true;

            ResetAuto();

            loadSBML(sSBML);

            SetTitle(sFileName);
        }

        private void OnCopyClick(object sender, EventArgs e)
        {
            try
            {
                Clipboard.SetText(GenerateCSV(CurrentPlot, setupControl1.Parameter, "\t"));
            }
            catch 
            {
            }
        }

        private void OnDragDrop(object sender, DragEventArgs e)
        {
            try
            {
                var sFilenames = (string[]) e.Data.GetData(DataFormats.FileDrop);
                var oInfo = new FileInfo(sFilenames[0]);
                if (oInfo.Extension.ToLower().EndsWith("xml") || oInfo.Extension.ToLower().EndsWith("sbml") ||
                    oInfo.Extension.ToLower().EndsWith("jan"))
                {
                    LoadFile(sFilenames[0]);
                }
            }
            catch 
            {
            }
        }

        private void OnDragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                var sFilenames = (string[]) e.Data.GetData(DataFormats.FileDrop);
                var oInfo = new FileInfo(sFilenames[0]);
                if (oInfo.Extension.ToLower().EndsWith("xml") || oInfo.Extension.ToLower().EndsWith("sbml") ||
                    oInfo.Extension.ToLower().EndsWith("jan"))
                {
                    e.Effect = DragDropEffects.Copy;
                    return;
                }
            }
            e.Effect = DragDropEffects.None;
        }

        private string GenerateCSV(List<PlotInfo> currentPlot, string parameter, string separator)
        {
            bool hasThick = false;
            var sb = new StringBuilder();
            sb.AppendFormat("\"{0}\"", parameter);
            sb.Append(separator);
            for (int i = 0; i < currentPlot.Count; i++)
            {
                var current = currentPlot[i];
                if (current.ThickSegments != null && current.ThickSegments.Count > 0)
                {
                    hasThick = true;
                    sb.AppendFormat("\"{0}\"", current.Label + " unstable");
                    sb.Append(separator);
                    sb.AppendFormat("\"{0}\"", current.Label + " stable");
                }
                else
                    sb.Append(current.Label);
                if (i + 1 < currentPlot.Count)
                    sb.Append(separator);
            }
            sb.AppendLine();

            int numPoints = currentPlot[0].MainCurve.Count;
            for (int i = 0; i < numPoints; i++)
            {
                double currentX = currentPlot[0].MainCurve[i].X;
                sb.AppendFormat("\"{0}\"", currentX);
                sb.Append(separator);
                for (int j = 0; j < currentPlot.Count; j++)
                {
                    var current = currentPlot[j];
                    if (hasThick)
                    {
                        sb.AppendFormat("\"{0}\"", current.MainCurve[i].Y);
                        sb.Append(separator);
                        bool found = false;
                        foreach (var item in current.ThickSegments)
                        {
                            var pair = item.Find(p => p.X == currentX);
                            if (pair != null)
                            {
                                sb.AppendFormat("\"{0}\"", pair.Y);
                                found = true;
                                break;
                            }
                        }
                        if (!found)
                            sb.Append("\"\"");
                    }
                    else
                        sb.AppendFormat("\"{0}\"", current.MainCurve[i].Y);
                    if (j + 1 < currentPlot.Count)
                        sb.Append(separator);
                }
                sb.AppendLine();
            }

            return sb.ToString();
        }
        private void OnExportClicked(object sender, EventArgs e)
        {
            var dialog = new SaveFileDialog
                {
                    Title = "Export current plot",
                    Filter = "CSV files|*.tab;*.csv|All files|*.*"
                };
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                string fileName = dialog.FileName;
                string lower = fileName.ToLowerInvariant();
                if (lower.EndsWith(".tex"))
                    File.WriteAllText(fileName, Util.GenerateTex(graphControl1.ZedControl.MasterPane));
                else
                    File.WriteAllText(fileName,
                                      GenerateCSV(CurrentPlot, setupControl1.Parameter,
                                                       lower.EndsWith(".tab") ? "\t" : ","));
                //File.WriteAllText(fileName, GetCurrentData(lower.EndsWith(".tab")));
            }
        }

        private void OnFormLoad(object sender, EventArgs e)
        {
            updateSBWMenu();


            //HACK: Add this for debug
            //this.tabControl1.Controls.Add(this.tabCode);
            //this.tabControl1.Controls.Add(this.tabSBML);
        }

        internal void OpenSBML()
        {
            cmdLoad_Click(this, EventArgs.Empty);
        }

        private void PlotResults(AutoResult oResult)
        {
            graphControl1.ZedControl.GraphPane.CurveList.Clear();
            var oRot = new ColorSymbolRotator();
            CurrentPlot = new List<PlotInfo>();

            foreach (AutoResultRun run in oResult.AllRuns)
            {                
                var series = run.DataSeries;

                if (series.Count < 2) continue;


                if (series[0].Length < 10) continue;

                for (int i = 0; i < series.Count - 1; i++)
                {
                    var sLabel = GetNthName(i);
                    var oLineColor = oRot.NextColor;
                    var info = new PlotInfo {
                        Label = sLabel, 
                        MainCurve = new PointPairList(series[0], series[i+1])
                    };

                    if (oResult.Positions.Count == 0)
                    {
                        AddNthCurveToGraph(i, series, sLabel, oLineColor);
                    }
                    else
                    {
                        var thickSegments = FindNthThickSegments(i, oResult, series);
                        AddNthSegmentedCurveToGraph(i, thickSegments, series, sLabel, oLineColor);
                        info.ThickSegments = thickSegments;
                    }
                    CurrentPlot.Add(info);
                }


                foreach (IntTripple tripple in oResult.Labels)
                {
                    for (int i = 0; i < series.Count - 1; i++)
                    {
                        int currentPos = UtilLib.FindClosestStablePoint(tripple.Key, oResult.Positions);

                        double x = series[0][currentPos];
                        double y = series[1 + i][currentPos];
                        var text = new TextObj(UtilLib.ConvertIntTypeToShortString(tripple.Value2), x, y);
                        text.Tag = new TagData {Series = 1 + i, Tripple = tripple, Label = GetNthName(i)};

                        graphControl1.ZedControl.GraphPane.GraphObjList.Add(text);
                    }
                }
            }

            graphControl1.ZedControl.GraphPane.XAxis.Scale.MaxGrace = 0f;
            graphControl1.ZedControl.GraphPane.XAxis.Scale.MinGrace = 0f;
            graphControl1.ZedControl.GraphPane.YAxis.Scale.MaxGrace = 0f;
            graphControl1.ZedControl.GraphPane.YAxis.Scale.MinGrace = 0f;

            SetParameterAxisTitle();

            graphControl1.ZedControl.AxisChange();
            tabControl1.Refresh();
        }

        public List<PlotInfo> CurrentPlot { get; set; }

        public class PlotInfo
        {
            public string Label { get; set; }
            public PointPairList MainCurve { get; set;}
            public IList<PointPairList> ThickSegments { get; set; }
        }

        public void RemoveWartermark()
        {
            graphControl1.ZedControl.GraphPane.GraphObjList.Clear();
        }

        private void ResetAuto()
        {
            string[] files = Directory.GetFiles(UtilLib.GetTempPath(), "fort.*");
            foreach (string file in files)
            {
                try
                {
                    File.Delete(file);
                }
                catch (Exception)
                {
                }
            }
        }

        private void ResetSetupControl()
        {
            setupControl1.MaxSteps = 1000;
            setupControl1.StartValue = 0.01;
            setupControl1.EndValue = 30;
            setupControl1.DirectionPositive = true;
        }

        internal void RunAuto()
        {
            Cursor originalCursor = Cursor;
            try
            {
                Cursor = Cursors.WaitCursor;

                if (string.IsNullOrEmpty(SBML))
                    OpenSBML();

                ResetAuto();
                setupControl1.RunContinuation = false;
                SetupAuto();


                AutoInterface.setFort2File(txtConfig.Text, txtConfig.Text.Length);

                if (setupControl1.CurrentConfig.IPS != 1)
                {
                    if (
                        MessageBox.Show(
                            "Currently only IPS = 1 is supported, any other value will make the library unstable. It is recommendet that you Quit (yes).",
                            "Unsupported Values", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                    {
                        return;
                    }
                }


                AutoInterface.CallAuto();

                CurrentResult = new AutoResult();
                txtResult.Text = CurrentResult.Fort7;

                RemoveWartermark();
                if (CurrentResult.ErrorOccured)
                {
                    AddWaterMark("Auto\ndid not\nreturn\nresults.");
                }
                else if (CurrentResult.NumPoints < 10)
                {
                    AddWaterMark("Not\nenough\npoints\nreturned.");
                }

                PlotResults(CurrentResult);


                //if (setupControl1.ReloadAfterRun)
                //{
                //    try
                //    {
                //        //Simulator.loadSBML(SBML);
                //        cmdSendToAuto_Click(this, EventArgs.Empty);
                //    }
                //    catch (Exception)
                //    {
                //        //
                //    }
                //}
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "An Error occured while running Auto", MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
            finally
            {
                Cursor = originalCursor;
            }
        }

        private void RunContinuationForTripple(IntTripple tripple)
        {
            try
            {
                if (SBML == null || SBML.Length == 0)
                    return;

                string fort8 = AutoResult.NewFort8; //.Replace(" 7 ", " 12 ");
                //string fort7 = AutoResult.NewFort7;

                ResetAuto();

                setupControl1.RunContinuation = true;
                setupControl1.Label = tripple.Value1;

                string originalConfig = setupControl1.CurrentConfig.ToInputString();

                //setupControl1.CurrentConfig.IPS = 2;                
                setupControl1.CurrentConfig.IRS = tripple.Value1;
                //setupControl1.CurrentConfig.ILP = 1;

                setupControl1.CurrentConfig.NICP = 2;
                setupControl1.CurrentConfig.ICP.Clear();
                setupControl1.CurrentConfig.ICP.Add(0);
                setupControl1.CurrentConfig.ICP.Add(10);

                //setupControl1.CurrentConfig.NCOL = 4;
                //setupControl1.CurrentConfig.IAD = 3;
                //setupControl1.CurrentConfig.ISP = 1;
                //setupControl1.CurrentConfig.ISW = 1;

                setupControl1.CurrentConfig.MXBF = 10;

                setupControl1.CurrentConfig.NTHL = 1;
                setupControl1.CurrentConfig.THL.Add(new IntDoublePair(10, 0));

                txtConfig.Text = setupControl1.Configuration;

                SetupAuto();

                AutoInterface.setFort2File(txtConfig.Text, txtConfig.Text.Length);

                AutoInterface.setFort3File(fort8, fort8.Length);

                if (setupControl1.CurrentConfig.IPS != 1)
                {
                    if (
                        MessageBox.Show(
                            "Currently only IPS = 1 is supported, any other value will make the library unstable. It is recommendet that you Quit (yes).",
                            "Unsupported Values", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                    {
                        return;
                    }
                }


                AutoInterface.CallAuto();
                string lastMessage = AutoInterface.GetLastMessage();

                //fort7 = fort7 + AutoResult.NewFort7;
                //AutoInterface.setFort7File(fort7, fort7.Length);

                fort8 = fort8 + AutoResult.NewFort8;
                AutoInterface.setFort8File(fort8, fort8.Length);

                CurrentResult = new AutoResult();
                txtResult.Text = CurrentResult.Fort7;

                RemoveWartermark();
                if (CurrentResult.ErrorOccured && CurrentResult.NumPoints < 10)
                {
                    AddWaterMark("Auto\ndid not\nreturn\nresults.");
                }
                else if (CurrentResult.NumPoints < 10)
                {
                    AddWaterMark("Not\nenough\npoints\nreturned.");
                }


                setupControl1.CurrentConfig = AutoInputConstants.FromContent(originalConfig);


                if (!string.IsNullOrEmpty(lastMessage))
                {
                    RemoveWartermark();
                    AddWaterMark(lastMessage);
                    return;
                }


                PlotResults(CurrentResult);


                if (setupControl1.ReloadAfterRun)
                {
                    try
                    {
                        //Simulator.loadSBML(SBML);
                        cmdSendToAuto_Click(this, EventArgs.Empty);
                    }
                    catch (Exception)
                    {
                        //
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "An Error occured while running Auto", MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        private void SetParameterAxisTitle()
        {
            if (CurrentModel != null)
            {
                graphControl1.ZedControl.GraphPane.XAxis.Title.IsVisible = true;
                if (SelectForm.NumSelectedParameters > 0)
                    graphControl1.ZedControl.GraphPane.XAxis.Title.Text =
                        (string) Simulator.getGlobalParameterNames()[SelectForm.SelectedParameters[0]];
                else if (SelectForm.NumSelectedBoundaries > 0)
                    graphControl1.ZedControl.GraphPane.XAxis.Title.Text =
                        (string) Simulator.getBoundarySpeciesNames()[SelectForm.SelectedBoundarySpecies[0]];
                else
                    graphControl1.ZedControl.GraphPane.XAxis.Title.IsVisible = false;
            }
            else
            {
                graphControl1.ZedControl.GraphPane.XAxis.Title.IsVisible = false;
            }
        }

        private void SetTitle(string fileName)
        {
            Text = "Auto2000 C# ";
            if (!string.IsNullOrWhiteSpace(fileName))
            {
                Text += string.Format(" - [{0}]", Path.GetFileName(fileName));
            }
        }

        private void SetupAuto()
        {
            if (CurrentModel == null)
                ExampleAutoSetup();
            else
            {
                //InitialState.AssignToModel(Simulator.model);
                //Simulator.loadSBML(SBML);
                Simulator.reset();


                if (setupControl1.DirectionPositive)
                    Simulator.setValue(setupControl1.Parameter, setupControl1.StartValue);
                else
                    Simulator.setValue(setupControl1.Parameter, setupControl1.EndValue);

                try
                {
                    setupControl1.CalculateSteadyStateIfNecessary();
                }
                catch
                {
                    // maybe being at steady state is not all that counts
                }
                if (!chkTakeAsIs.Checked)
                    txtConfig.Text = setupControl1.Configuration;
                SetupUsingModel(CurrentModel);
            }

            SelectForm.Parameters = new ArrayList(new object[] {setupControl1.Parameter});
        }

        private void button1_Click(object sender, EventArgs e)
        {
            LoadFile("d:/Frank/SBML Models/BorisEjb.xml");
            SelectForm.InitializeFromModel(CurrentModel);
            SelectForm.ShowDialog();
        }

        private void changeBifurcationPlot_Click(object sender, EventArgs e)
        {
            ChangeBifurcationPlot.StartPosition = FormStartPosition.CenterParent;
            ChangeBifurcationPlot.Show();
        }

        private void cmdAssignAdvanced_Click(object sender, EventArgs e)
        {
            try
            {
                AutoInputConstants constants = AutoInputConstants.FromContent(txtConfig.Text);
                txtConfig.Text = constants.ToInputString();

                setupControl1.CurrentConfig = constants;

                setupControl1.MaxSteps = constants.NMX;
                setupControl1.MaxBifurcations = constants.MXBF;
                setupControl1.StartValue = constants.RL0;
                setupControl1.EndValue = constants.RL1;

                setupControl1.DirectionPositive = (constants.DS >= 0);
            }
            catch (Exception)
            {
            }
        }

        private void cmdLoad_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                LoadFile(openFileDialog1.FileName);
            }
        }

        private void cmdParseConfig_Click(object sender, EventArgs e)
        {
            try
            {
                AutoInputConstants constants = AutoInputConstants.FromContent(txtConfig.Text);
                txtConfig.Text = constants.ToInputString();
            }
            catch (Exception)
            {
            }
        }

        private void cmdSendToAuto_Click(object sender, EventArgs e)
        {
            try
            {
                // selected value
                string sTemp = setupControl1.Parameter;
                loadSBML(Util.ConvertToSBML(txtJarnac.Text));
                if (setupControl1.Contains(sTemp))
                    setupControl1.Parameter = sTemp;
            }
            catch (SBWException ex)
            {
                MessageBox.Show(ex.Message + Environment.NewLine + Environment.NewLine + ex.DetailedMessage,
                                "Loading the model failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch
            {
            }
        }

        public void doAnalysis(string sSBML)
        {
            Invoke(new VoidDelegate(ResetSetupControl));

            loadSBML(sSBML);
        }

        public void loadSBML(string sSBML)
        {
            if (InvokeRequired)
            {
                Invoke(new VoidStringDelegate(loadSBML), new object[] {sSBML});
            }
            else
            {
                try
                {
                    if (sSBML.Contains("jd:") && !sSBML.Contains("xmlns:jd = "))
                    {
                        sSBML = sSBML.Replace("xmlns:jd2", "xmlns:jd = \"http://www.sys-bio.org/sbml\" xmlns:jd2");
                    }
                    chkTakeAsIs.Checked = false;
                    Simulator.model = null;
                    Simulator.modelLoaded = false;
                    Simulator.loadSBML(sSBML);
                    CurrentModel = Simulator.model;

                    _InitialState = new ModelState(CurrentModel);

                    txtCode.Text = Simulator.getCSharpCode();

                    SelectForm.InitializeFromModel(CurrentModel);

                    var oList = new ArrayList(new[] {"Time"});
                    oList.AddRange(Simulator.getFloatingSpeciesNames());

                    FormChangeTimeCoursePlot.Instance.XAxisValues = oList.ToArray();

                    if (CurrentModel != null)
                    {
                        setupControl1.Parameters = SelectForm.Parameters.ToArray();
                    }
                    else
                    {
                        setupControl1.ParameterAvailable = false;
                    }


                    //_SelectForm.Show();
                    //_SelectForm.Focus();

                    SBML = sSBML;

                    txtSBML.Text = SBML;
                    txtJarnac.Text = Util.ConvertToJarnac(sSBML);

                    SetTitle("SBML.xml");
                }
                catch (SBWException ex)
                {
                    MessageBox.Show(ex.Message + Environment.NewLine + Environment.NewLine + ex.DetailedMessage,
                                    "Loading the model failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void mnuExit_Click(object sender, EventArgs e)
        {
            Close();
        }

        #region // SBW Menu

        private Hashtable oAnalyzers;

        private void oItem_Click(object sender, EventArgs e)
        {
            try
            {
                if ((SBML == null) || SBML == "")
                {
                    MessageBox.Show("There is no model to analyze. Load a model first.", "No Model loaded",
                                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                var oTemp = (SBWAnalyzer) oAnalyzers[((MenuItem) sender).Text];
                var oModule = new Module(oTemp.ModuleName);
                Service oService = oModule.getService(oTemp.ServiceName);
                oService.getMethod("void doAnalysis(string)").Send(SBML);
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
            if (!IsSBWAvailable)
                return;
            try
            {
                bool bWasConnected = LowLevel.SBWGetConnectionStatus();
                if (!bWasConnected)
                    LowLevel.SBWConnect();

                oSBWMenu.MenuItems.Clear();
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
                            uniqueName += " (" + list[0] + ")";
                        var oItem = new MenuItem(uniqueName);

                        oAnalyzers.Add(uniqueName, new SBWAnalyzer((string) list[0], (string) list[1]));

                        oItem.Click += oItem_Click;
                        oSBWMenu.MenuItems.Add(oItem);
                    }
                }


                if (!bWasConnected)
                    LowLevel.SBWDisconnect();
            }
            catch (Exception)
            {
            }

            if (oAnalyzers.Count == 0)
            {
                IsSBWAvailable = false;
                oSBWMenu.Visible = false;
            }
        }

        internal static bool IsSBWAvailable { get; set;}

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

        //ContextMenu oSBWMenu = new ContextMenu();

        #endregion

        #region // Oscli Example Hard Coded

        private static int BoundaryCallback(int ndim, IntPtr par, IntPtr icp, int nbx, IntPtr u0, IntPtr u1, int ijac,
                                            IntPtr fb, IntPtr dbc)
        {
            return 0;
        }

        internal static void ExampleAutoSetup()
        {
            FuncCallBack2 oFunc2 = FunctionCallback2;
            StpntCallBack oStpnt = StpntCallback;
            BcndCallBack oBcnd = BoundaryCallback;

            AutoInterface.SetAutoNumParameters(36);
            AutoInterface.setCallbackFunc2(oFunc2);
            AutoInterface.setCallbackStpnt(oStpnt);
            AutoInterface.setCallbackBcnd(oBcnd);
        }

        protected internal int FunctionCallback(int ndim, IntPtr u, IntPtr icp, IntPtr par, int ijac, IntPtr f,
                                                IntPtr dfdu, IntPtr dfdp)
        {
            // pp2 example actually 

            //Console.WriteLine("start function callback");

            var oPar = new double[10];
            var oU = new double[ndim];
            var oF = new double[ndim];
            var oRate = new double[4];

            Marshal.Copy(par, oPar, 0, 10);
            Marshal.Copy(u, oU, 0, ndim);

            var oGp = new double[7];
            for (int i = 0; i < 7; i++)
            {
                oGp[i] = oPar[i];
            }

            //double[] oBp = new double[3];
            //for (int i = 0; i < 3; i++)
            //{
            //    oBp[i] = oPar[7 + i];
            //}


            oRate[0] = oGp[0];
            oRate[1] = oGp[1]*oU[0];
            oRate[2] = (oGp[2]*oU[0] - oGp[3]*oU[1])*(1.0 + oGp[4]*Math.Pow(oU[1], oGp[5]));
            oRate[3] = oGp[6]*oU[1];

            oF[0] = +oRate[0] - oRate[1] - oRate[2];
            oF[1] = +oRate[2] - oRate[3];

            //double e = Math.Exp(-oPar[2] * oU[0]);
            //oF[0] = oPar[1] * oU[0] * (1 - oU[0]) - oU[0] * oU[1] - oPar[0] * (1 - e);
            //oF[1] = -oU[1] + oPar[3] * oU[0] * oU[1];

            //oF = new double[]{ oU[1], oPar[0] } ;
            Marshal.Copy(oF, 0, f, 2);

            //  if (nCount-- < 1)
            //    System.Diagnostics.Debugger.Break();

            //System.Threading.Thread.Sleep(10);
            //Console.WriteLine("leave function callback");
            return 0;
        }

        private static void FunctionCallback2(IntPtr u, IntPtr par, IntPtr f)
        {
            // pp2 example actually 

            //Console.WriteLine("start function callback");

            var oPar = new double[10];
            var oU = new double[2];
            var oF = new double[2];
            var oRate = new double[4];

            Marshal.Copy(par, oPar, 0, 10);
            Marshal.Copy(u, oU, 0, 2);

            var oGp = new double[7];
            for (int i = 0; i < 7; i++)
            {
                oGp[i] = oPar[i];
            }

            //double[] oBp = new double[3];
            //for (int i = 0; i < 3; i++)
            //{
            //    oBp[i] = oPar[7 + i];
            //}


            oRate[0] = oGp[0];
            oRate[1] = oGp[1]*oU[0];
            oRate[2] = (oGp[2]*oU[0] - oGp[3]*oU[1])*(1.0 + oGp[4]*Math.Pow(oU[1], oGp[5]));
            oRate[3] = oGp[6]*oU[1];

            oF[0] = +oRate[0] - oRate[1] - oRate[2];
            oF[1] = +oRate[2] - oRate[3];

            //double e = Math.Exp(-oPar[2] * oU[0]);
            //oF[0] = oPar[1] * oU[0] * (1 - oU[0]) - oU[0] * oU[1] - oPar[0] * (1 - e);
            //oF[1] = -oU[1] + oPar[3] * oU[0] * oU[1];

            //oF = new double[]{ oU[1], oPar[0] } ;
            Marshal.Copy(oF, 0, f, 2);

            //  if (nCount-- < 1)
            //    System.Diagnostics.Debugger.Break();

            //System.Threading.Thread.Sleep(10);
            //Console.WriteLine("leave function callback");            
        }

        private static int StpntCallback(int ndim, double t, IntPtr u, IntPtr par)
        {
            //double[] oPar = new double[] { -.9, .5, -.6, .6, .328578, .933578}; 
            //double[] oU = new double[] {0.0, 0.0, 0.0};

            //Marshal.Copy(oPar, 0, par, 6);
            //Marshal.Copy(oU, 0, u, 3);


            // pp2 example

            //double[] oPar = new double[] { 0.0, 3.0, 5.0, 3.0}; 
            //double[] oU = new double[] {0.0, 0.0};

            var oPar = new[] {1.0, 0.0, 1.0, 0.0, 1.0, 3.0, 5.0, 1.0, 0.0, 0.0};
            var oU = new[] {0.992063492063492, 0.2};


            Marshal.Copy(oPar, 0, par, 10);
            Marshal.Copy(oU, 0, u, oU.Length);

            return 0;
        }

        #endregion

        #region // Callback Functions for Current SBML model

        private static StpntCallBack _InitializationCallBack;
        private static FuncCallBack2 _FunctionCallBack;
        //static BcndCallBack _BCNDCallBack;
        //static IcndCallBack _IcndCallBack;
        //static FoptCallBack _FoptCallBack;
        //static PvlsCallBack _PvlsCallBack; 

        private int nDim;

        private bool ContainsNaN(double[] variableTemp)
        {
            for (int i = 0; i < variableTemp.Length; i++)
            {
                if (double.IsNaN(variableTemp[i]))
                    return true;
            }
            return false;
        }


        private int ModelBcndCallBack(int ndim, IntPtr par, IntPtr icp, int nbx, IntPtr u0, IntPtr u1, int ijac,
                                      IntPtr fb, IntPtr dbc)
        {
            return 0;
        }

        public int ModelFoptCallBack(int ndim, IntPtr u, IntPtr icp, IntPtr par, int ijac, IntPtr fs, IntPtr dfdu,
                                     IntPtr dfdp)
        {
            return 0;
        }

        private void ModelFunctionCallback(IntPtr oVariables, IntPtr par, IntPtr oResult)
        {
            int numBoundaries = SelectForm.NumSelectedBoundaries;
            int numParameters = SelectForm.NumSelectedParameters;

            if (numBoundaries > 0)
            {
                var oBoundary = new double[numBoundaries];
                Marshal.Copy(par, oBoundary, 0, numBoundaries);
                int[] oSelectedBoundary = SelectForm.SelectedBoundarySpecies;
                for (int i = 0; i < numBoundaries; i++)
                {
                    Simulator.setBoundarySpeciesByIndex(oSelectedBoundary[i],
                                                        (double.IsNaN(oBoundary[i])
                                                             ? oSelectedBoundary[i]
                                                             : oBoundary[i]));
                }
            }

            if (numParameters > 0)
            {
                var oParameters = new double[numParameters];
                Marshal.Copy(par, oParameters, numBoundaries, numParameters);
                int[] oSelectedParameters = SelectForm.SelectedParameters;
                for (int i = 0; i < numParameters; i++)
                {
                    Simulator.setGlobalParameterByIndex(oSelectedParameters[i],
                                                        (double.IsNaN(oParameters[i])
                                                             ? oSelectedParameters[i]
                                                             : oParameters[i]));
                }
            }


            var variableTemp = new double[CurrentModel.y.Length];
            var min = Math.Min(CurrentModel.y.Length, nDim);

            Marshal.Copy(oVariables, variableTemp, 0, min);

            bool containsNaN = ContainsNaN(variableTemp);
            if (!containsNaN)
            {
                CurrentModel.y = variableTemp;
            }

            //Console.WriteLine("Eval");
            //PrintArray(CurrentModel.y, Console.Out);

            CurrentModel.convertToAmounts();
            CurrentModel.evalModel(CurrentModel.time, CurrentModel.y);
            //Simulator.oneStep(0.0, 0.01);

            min = Math.Min(CurrentModel.dydt.Length, nDim);

            Marshal.Copy(CurrentModel.dydt, 0, oResult, min);


            //PrintArray(CurrentModel.y, Console.Out);
            //PrintArray(CurrentModel.dydt, Console.Out);
        }

        private int ModelIcndCallBack(int ndim, IntPtr par, IntPtr icp, int nint, IntPtr u, IntPtr uold, IntPtr udot,
                                      IntPtr upold, int ijac, IntPtr fi, IntPtr dint)
        {
            return 0;
        }

        private int ModelInitializationCallback(int ndim, double t, IntPtr u, IntPtr par)
        {
            nDim = ndim;

            int numBoundaries = SelectForm.NumSelectedBoundaries;
            int numParameters = SelectForm.NumSelectedParameters;

            var oBoundary = new double[numBoundaries];
            var oGlobalParameters = new double[numParameters];

            if (numBoundaries > 0)
            {
                int[] oSelectedBoundary = SelectForm.SelectedBoundarySpecies;
                for (int i = 0; i < numBoundaries; i++)
                {
                    oBoundary[i] = Simulator.getBoundarySpeciesByIndex(oSelectedBoundary[i]);
                }
            }


            if (numParameters > 0)
            {
                int[] oSelectedParameters = SelectForm.SelectedParameters;
                for (int i = 0; i < numParameters; i++)
                {
                    oGlobalParameters[i] = Simulator.getGlobalParameterByIndex(oSelectedParameters[i]);
                }
            }

            var oParameters = new double[numBoundaries + numParameters];

            Array.Copy(oBoundary, oParameters, oBoundary.Length);
            Array.Copy(oGlobalParameters, 0, oParameters, oBoundary.Length, oGlobalParameters.Length);

            Marshal.Copy(oParameters, 0, par, oParameters.Length);

            Marshal.Copy(CurrentModel.y, 0, u, Math.Min(CurrentModel.y.Length, ndim));

            return 0;
        }

        public int ModelPvlsCallBack(int ndim, IntPtr u, IntPtr par)
        {
            return 0;
        }

        private static void PrintArray(double[] p, TextWriter textWriter)
        {
            for (int i = 0; i < p.Length; i++)
            {
                textWriter.Write(p[i]);
                if (i < p.Length - 1)
                    textWriter.Write(", ");
            }
            textWriter.WriteLine();
        }

        internal void SetupUsingModel(IModel oCurrentModel)
        {
            if (oCurrentModel == null)
                throw new ArgumentNullException("oCurrentModel", "Need to load SBML file first.");

            setupControl1.CurrentConfig.NDIM = oCurrentModel.y.Length;

            _InitializationCallBack = ModelInitializationCallback;
            _FunctionCallBack = ModelFunctionCallback;
            //_BCNDCallBack = new BcndCallBack(ModelBcndCallBack);
            //_IcndCallBack = new IcndCallBack(ModelIcndCallBack);
            //_FoptCallBack = new FoptCallBack(ModelFoptCallBack);
            //_PvlsCallBack = new PvlsCallBack(ModelPvlsCallBack);


            AutoInterface.setCallbackStpnt(_InitializationCallBack);
            AutoInterface.setCallbackFunc2(_FunctionCallBack);
            //AutoInterface.setCallbackBcnd(_BCNDCallBack);
            //AutoInterface.setCallbackIcnd(_IcndCallBack);
            //AutoInterface.setCallbackFopt(_FoptCallBack);
            //AutoInterface.setCallbackPvls(_PvlsCallBack);
        }

        #endregion
    }
}