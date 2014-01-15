using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Threading;
using System.Windows.Forms;
using System.Data;
using System.IO;
using System.Runtime.InteropServices;

using LibAutoCSharp;
using LibRoadRunner;
using ZedGraph;
using SBW;

using AutoFrontend.Forms;

namespace AutoFrontend
{

    /// <summary>
    /// Summary description for Form1.
    /// </summary>
    public partial class MainForm : System.Windows.Forms.Form
    {
        
        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            LibAutoCSharp.AutoInputConstants autoInputConstants1 = new LibAutoCSharp.AutoInputConstants();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.button1 = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.cmdLoad = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabRun = new System.Windows.Forms.TabPage();
            this.panel7 = new System.Windows.Forms.Panel();
            this.graphControl1 = new AutoFrontend.Controls.GraphControl();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.panel6 = new System.Windows.Forms.Panel();
            this.setupControl1 = new AutoFrontend.Controls.SetupControl();
            this.tabAdvanced = new System.Windows.Forms.TabPage();
            this.panel8 = new System.Windows.Forms.Panel();
            this.panel10 = new System.Windows.Forms.Panel();
            this.txtConfig = new AutoFrontend.Controls.CodeTextBox();
            this.panel9 = new System.Windows.Forms.Panel();
            this.cmdAssignAdvanced = new System.Windows.Forms.Button();
            this.cmdParseConfig = new System.Windows.Forms.Button();
            this.chkTakeAsIs = new System.Windows.Forms.CheckBox();
            this.tabJarnac = new System.Windows.Forms.TabPage();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel5 = new System.Windows.Forms.Panel();
            this.txtJarnac = new AutoFrontend.Controls.CodeTextBox();
            this.panel4 = new System.Windows.Forms.Panel();
            this.cmdSendToAuto = new System.Windows.Forms.Button();
            this.tabFort7 = new System.Windows.Forms.TabPage();
            this.txtResult = new AutoFrontend.Controls.CodeTextBox();
            this.tabCode = new System.Windows.Forms.TabPage();
            this.txtCode = new AutoFrontend.Controls.CodeTextBox();
            this.tabSBML = new System.Windows.Forms.TabPage();
            this.txtSBML = new AutoFrontend.Controls.CodeTextBox();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.mainMenu1 = new System.Windows.Forms.MainMenu(this.components);
            this.menuItem1 = new System.Windows.Forms.MenuItem();
            this.mnuOpen = new System.Windows.Forms.MenuItem();
            this.mnuExport = new System.Windows.Forms.MenuItem();
            this.menuItem3 = new System.Windows.Forms.MenuItem();
            this.mnuExit = new System.Windows.Forms.MenuItem();
            this.menuItem2 = new System.Windows.Forms.MenuItem();
            this.changeBifurcationPlot = new System.Windows.Forms.MenuItem();
            this.oSBWMenu = new System.Windows.Forms.MenuItem();
            this.codeTextBox1 = new AutoFrontend.Controls.CodeTextBox();
            this.menuItem4 = new System.Windows.Forms.MenuItem();
            this.mnuCopyCSV = new System.Windows.Forms.MenuItem();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabRun.SuspendLayout();
            this.panel7.SuspendLayout();
            this.panel6.SuspendLayout();
            this.tabAdvanced.SuspendLayout();
            this.panel8.SuspendLayout();
            this.panel10.SuspendLayout();
            this.panel9.SuspendLayout();
            this.tabJarnac.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel5.SuspendLayout();
            this.panel4.SuspendLayout();
            this.tabFort7.SuspendLayout();
            this.tabCode.SuspendLayout();
            this.tabSBML.SuspendLayout();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(144, 8);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "button1";
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.cmdLoad);
            this.panel1.Controls.Add(this.button1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel1.Location = new System.Drawing.Point(0, 566);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(760, 40);
            this.panel1.TabIndex = 1;
            this.panel1.Visible = false;
            // 
            // cmdLoad
            // 
            this.cmdLoad.Location = new System.Drawing.Point(16, 8);
            this.cmdLoad.Name = "cmdLoad";
            this.cmdLoad.Size = new System.Drawing.Size(75, 23);
            this.cmdLoad.TabIndex = 1;
            this.cmdLoad.Text = "&Load";
            this.cmdLoad.Click += new System.EventHandler(this.cmdLoad_Click);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.tabControl1);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 0);
            this.panel2.Name = "panel2";
            this.panel2.Padding = new System.Windows.Forms.Padding(3);
            this.panel2.Size = new System.Drawing.Size(760, 566);
            this.panel2.TabIndex = 2;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabRun);
            this.tabControl1.Controls.Add(this.tabAdvanced);
            this.tabControl1.Controls.Add(this.tabJarnac);
            this.tabControl1.Controls.Add(this.tabFort7);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(3, 3);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(754, 560);
            this.tabControl1.TabIndex = 0;
            // 
            // tabRun
            // 
            this.tabRun.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.tabRun.Controls.Add(this.panel7);
            this.tabRun.Controls.Add(this.splitter1);
            this.tabRun.Controls.Add(this.panel6);
            this.tabRun.Location = new System.Drawing.Point(4, 22);
            this.tabRun.Name = "tabRun";
            this.tabRun.Padding = new System.Windows.Forms.Padding(3);
            this.tabRun.Size = new System.Drawing.Size(746, 534);
            this.tabRun.TabIndex = 0;
            this.tabRun.Text = "Run AUTO";
            // 
            // panel7
            // 
            this.panel7.Controls.Add(this.graphControl1);
            this.panel7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel7.Location = new System.Drawing.Point(206, 3);
            this.panel7.Name = "panel7";
            this.panel7.Size = new System.Drawing.Size(537, 528);
            this.panel7.TabIndex = 2;
            // 
            // graphControl1
            // 
            this.graphControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.graphControl1.Location = new System.Drawing.Point(0, 0);
            this.graphControl1.Name = "graphControl1";
            this.graphControl1.Size = new System.Drawing.Size(537, 528);
            this.graphControl1.TabIndex = 0;
            // 
            // splitter1
            // 
            this.splitter1.Location = new System.Drawing.Point(203, 3);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(3, 528);
            this.splitter1.TabIndex = 1;
            this.splitter1.TabStop = false;
            // 
            // panel6
            // 
            this.panel6.Controls.Add(this.setupControl1);
            this.panel6.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel6.Location = new System.Drawing.Point(3, 3);
            this.panel6.Name = "panel6";
            this.panel6.Size = new System.Drawing.Size(200, 528);
            this.panel6.TabIndex = 0;
            // 
            // setupControl1
            // 
            this.setupControl1.CalculateSteadyState = true;
            autoInputConstants1.A0 = 0D;
            autoInputConstants1.A1 = 10000D;
            autoInputConstants1.DS = 0.001D;
            autoInputConstants1.DSMAX = 0.1D;
            autoInputConstants1.DSMIN = 1E-05D;
            autoInputConstants1.EPSL = 1E-08D;
            autoInputConstants1.EPSS = 1E-06D;
            autoInputConstants1.EPSU = 1E-08D;
            autoInputConstants1.IAD = 3;
            autoInputConstants1.IADS = 1;
            autoInputConstants1.IID = 0;
            autoInputConstants1.ILP = 1;
            autoInputConstants1.IPLT = 0;
            autoInputConstants1.IPS = 1;
            autoInputConstants1.IRS = 0;
            autoInputConstants1.ISP = 1;
            autoInputConstants1.ISW = 1;
            autoInputConstants1.ITMX = 8;
            autoInputConstants1.ITNW = 5;
            autoInputConstants1.JAC = 0;
            autoInputConstants1.MXBF = -1;
            autoInputConstants1.NBC = 0;
            autoInputConstants1.NCOL = 3;
            autoInputConstants1.NDIM = 2;
            autoInputConstants1.NICP = 1;
            autoInputConstants1.NINT = 0;
            autoInputConstants1.NMX = 1000;
            autoInputConstants1.NPR = 50;
            autoInputConstants1.NTHL = 0;
            autoInputConstants1.NTHU = 0;
            autoInputConstants1.NTST = 15;
            autoInputConstants1.NUZR = 0;
            autoInputConstants1.NWTN = 3;
            autoInputConstants1.RL0 = 0.01D;
            autoInputConstants1.RL1 = 30D;
            this.setupControl1.CurrentConfig = autoInputConstants1;
            this.setupControl1.DirectionPositive = true;
            this.setupControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.setupControl1.EndValue = 30D;
            this.setupControl1.Label = 0;
            this.setupControl1.Location = new System.Drawing.Point(0, 0);
            this.setupControl1.MaxBifurcations = -1;
            this.setupControl1.MaxSteps = 1000;
            this.setupControl1.Name = "setupControl1";
            this.setupControl1.Parameter = "";
            this.setupControl1.ParameterAvailable = false;
            this.setupControl1.Parameters = new object[0];
            this.setupControl1.RunContinuation = false;
            this.setupControl1.SimulationEndTime = 10D;
            this.setupControl1.SimulationNumPoints = 100D;
            this.setupControl1.SimulationStartTime = 0D;
            this.setupControl1.Size = new System.Drawing.Size(200, 528);
            this.setupControl1.StartValue = 0.01D;
            this.setupControl1.TabIndex = 0;
            // 
            // tabAdvanced
            // 
            this.tabAdvanced.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.tabAdvanced.Controls.Add(this.panel8);
            this.tabAdvanced.Location = new System.Drawing.Point(4, 22);
            this.tabAdvanced.Name = "tabAdvanced";
            this.tabAdvanced.Padding = new System.Windows.Forms.Padding(3);
            this.tabAdvanced.Size = new System.Drawing.Size(746, 513);
            this.tabAdvanced.TabIndex = 5;
            this.tabAdvanced.Text = "Advanced Configuration";
            // 
            // panel8
            // 
            this.panel8.Controls.Add(this.panel10);
            this.panel8.Controls.Add(this.panel9);
            this.panel8.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel8.Location = new System.Drawing.Point(3, 3);
            this.panel8.Name = "panel8";
            this.panel8.Size = new System.Drawing.Size(740, 507);
            this.panel8.TabIndex = 1;
            // 
            // panel10
            // 
            this.panel10.Controls.Add(this.txtConfig);
            this.panel10.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel10.Location = new System.Drawing.Point(0, 32);
            this.panel10.Name = "panel10";
            this.panel10.Size = new System.Drawing.Size(740, 475);
            this.panel10.TabIndex = 1;
            // 
            // txtConfig
            // 
            this.txtConfig.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtConfig.Font = new System.Drawing.Font("Courier New", 11F);
            this.txtConfig.Location = new System.Drawing.Point(0, 0);
            this.txtConfig.MaxLength = 0;
            this.txtConfig.Multiline = true;
            this.txtConfig.Name = "txtConfig";
            this.txtConfig.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtConfig.Size = new System.Drawing.Size(740, 475);
            this.txtConfig.TabIndex = 0;
            this.txtConfig.WordWrap = false;
            // 
            // panel9
            // 
            this.panel9.Controls.Add(this.cmdAssignAdvanced);
            this.panel9.Controls.Add(this.cmdParseConfig);
            this.panel9.Controls.Add(this.chkTakeAsIs);
            this.panel9.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel9.Location = new System.Drawing.Point(0, 0);
            this.panel9.Name = "panel9";
            this.panel9.Size = new System.Drawing.Size(740, 32);
            this.panel9.TabIndex = 0;
            // 
            // cmdAssignAdvanced
            // 
            this.cmdAssignAdvanced.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdAssignAdvanced.Location = new System.Drawing.Point(581, 4);
            this.cmdAssignAdvanced.Name = "cmdAssignAdvanced";
            this.cmdAssignAdvanced.Size = new System.Drawing.Size(75, 23);
            this.cmdAssignAdvanced.TabIndex = 2;
            this.cmdAssignAdvanced.Text = "Assign";
            this.cmdAssignAdvanced.UseVisualStyleBackColor = true;
            this.cmdAssignAdvanced.Click += new System.EventHandler(this.cmdAssignAdvanced_Click);
            // 
            // cmdParseConfig
            // 
            this.cmdParseConfig.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdParseConfig.Location = new System.Drawing.Point(662, 4);
            this.cmdParseConfig.Name = "cmdParseConfig";
            this.cmdParseConfig.Size = new System.Drawing.Size(75, 23);
            this.cmdParseConfig.TabIndex = 1;
            this.cmdParseConfig.Text = "Parse";
            this.cmdParseConfig.UseVisualStyleBackColor = true;
            this.cmdParseConfig.Click += new System.EventHandler(this.cmdParseConfig_Click);
            // 
            // chkTakeAsIs
            // 
            this.chkTakeAsIs.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chkTakeAsIs.Location = new System.Drawing.Point(8, 4);
            this.chkTakeAsIs.Name = "chkTakeAsIs";
            this.chkTakeAsIs.Size = new System.Drawing.Size(384, 24);
            this.chkTakeAsIs.TabIndex = 0;
            this.chkTakeAsIs.Text = "Use Advanced Configuration as is (don\'t overwrite settings)";
            // 
            // tabJarnac
            // 
            this.tabJarnac.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.tabJarnac.Controls.Add(this.panel3);
            this.tabJarnac.Location = new System.Drawing.Point(4, 22);
            this.tabJarnac.Name = "tabJarnac";
            this.tabJarnac.Padding = new System.Windows.Forms.Padding(3);
            this.tabJarnac.Size = new System.Drawing.Size(746, 513);
            this.tabJarnac.TabIndex = 1;
            this.tabJarnac.Text = "Model";
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.panel5);
            this.panel3.Controls.Add(this.panel4);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(3, 3);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(740, 507);
            this.panel3.TabIndex = 1;
            // 
            // panel5
            // 
            this.panel5.Controls.Add(this.txtJarnac);
            this.panel5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel5.Location = new System.Drawing.Point(0, 0);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(740, 467);
            this.panel5.TabIndex = 1;
            // 
            // txtJarnac
            // 
            this.txtJarnac.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtJarnac.Font = new System.Drawing.Font("Courier New", 11F);
            this.txtJarnac.Location = new System.Drawing.Point(0, 0);
            this.txtJarnac.MaxLength = 0;
            this.txtJarnac.Multiline = true;
            this.txtJarnac.Name = "txtJarnac";
            this.txtJarnac.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtJarnac.Size = new System.Drawing.Size(740, 467);
            this.txtJarnac.TabIndex = 0;
            this.txtJarnac.WordWrap = false;
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.cmdSendToAuto);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel4.Location = new System.Drawing.Point(0, 467);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(740, 40);
            this.panel4.TabIndex = 0;
            // 
            // cmdSendToAuto
            // 
            this.cmdSendToAuto.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cmdSendToAuto.Location = new System.Drawing.Point(8, 8);
            this.cmdSendToAuto.Name = "cmdSendToAuto";
            this.cmdSendToAuto.Size = new System.Drawing.Size(104, 23);
            this.cmdSendToAuto.TabIndex = 0;
            this.cmdSendToAuto.Text = "Send to AUTO";
            this.cmdSendToAuto.Click += new System.EventHandler(this.cmdSendToAuto_Click);
            // 
            // tabFort7
            // 
            this.tabFort7.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.tabFort7.Controls.Add(this.txtResult);
            this.tabFort7.Location = new System.Drawing.Point(4, 22);
            this.tabFort7.Name = "tabFort7";
            this.tabFort7.Padding = new System.Windows.Forms.Padding(3);
            this.tabFort7.Size = new System.Drawing.Size(746, 513);
            this.tabFort7.TabIndex = 2;
            this.tabFort7.Text = "Raw Result";
            // 
            // txtResult
            // 
            this.txtResult.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtResult.Font = new System.Drawing.Font("Courier New", 11F);
            this.txtResult.Location = new System.Drawing.Point(3, 3);
            this.txtResult.MaxLength = 0;
            this.txtResult.Multiline = true;
            this.txtResult.Name = "txtResult";
            this.txtResult.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtResult.Size = new System.Drawing.Size(740, 507);
            this.txtResult.TabIndex = 0;
            this.txtResult.WordWrap = false;
            // 
            // tabCode
            // 
            this.tabCode.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.tabCode.Controls.Add(this.txtCode);
            this.tabCode.Location = new System.Drawing.Point(4, 22);
            this.tabCode.Name = "tabCode";
            this.tabCode.Padding = new System.Windows.Forms.Padding(3);
            this.tabCode.Size = new System.Drawing.Size(746, 534);
            this.tabCode.TabIndex = 3;
            this.tabCode.Text = "(Debug Code)";
            // 
            // txtCode
            // 
            this.txtCode.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtCode.Font = new System.Drawing.Font("Courier New", 11F);
            this.txtCode.Location = new System.Drawing.Point(3, 3);
            this.txtCode.MaxLength = 0;
            this.txtCode.Multiline = true;
            this.txtCode.Name = "txtCode";
            this.txtCode.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtCode.Size = new System.Drawing.Size(740, 528);
            this.txtCode.TabIndex = 0;
            this.txtCode.WordWrap = false;
            // 
            // tabSBML
            // 
            this.tabSBML.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.tabSBML.Controls.Add(this.txtSBML);
            this.tabSBML.Location = new System.Drawing.Point(4, 22);
            this.tabSBML.Name = "tabSBML";
            this.tabSBML.Padding = new System.Windows.Forms.Padding(3);
            this.tabSBML.Size = new System.Drawing.Size(746, 534);
            this.tabSBML.TabIndex = 4;
            this.tabSBML.Text = "(Debug SBML)";
            // 
            // txtSBML
            // 
            this.txtSBML.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtSBML.Font = new System.Drawing.Font("Courier New", 11F);
            this.txtSBML.Location = new System.Drawing.Point(3, 3);
            this.txtSBML.MaxLength = 0;
            this.txtSBML.Multiline = true;
            this.txtSBML.Name = "txtSBML";
            this.txtSBML.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtSBML.Size = new System.Drawing.Size(740, 528);
            this.txtSBML.TabIndex = 0;
            this.txtSBML.WordWrap = false;
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.DefaultExt = "xml";
            this.openFileDialog1.Filter = "All supported files (SBML and Jarnac)|*.xml;*.sbml;*.jan|SBML files|*.xml;*.sbml|" +
    "Jarnac files|*.jan|All files|*.*";
            this.openFileDialog1.Title = "Load Model file";
            // 
            // mainMenu1
            // 
            this.mainMenu1.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuItem1,
            this.menuItem2,
            this.oSBWMenu});
            // 
            // menuItem1
            // 
            this.menuItem1.Index = 0;
            this.menuItem1.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.mnuOpen,
            this.mnuExport,
            this.menuItem4,
            this.mnuCopyCSV,
            this.menuItem3,
            this.mnuExit});
            this.menuItem1.Text = "&File";
            // 
            // mnuOpen
            // 
            this.mnuOpen.Index = 0;
            this.mnuOpen.Shortcut = System.Windows.Forms.Shortcut.CtrlO;
            this.mnuOpen.Text = "&Open";
            this.mnuOpen.Click += new System.EventHandler(this.cmdLoad_Click);
            // 
            // mnuExport
            // 
            this.mnuExport.Index = 1;
            this.mnuExport.Shortcut = System.Windows.Forms.Shortcut.CtrlE;
            this.mnuExport.Text = "&Export";
            this.mnuExport.Click += new System.EventHandler(this.OnExportClicked);
            // 
            // menuItem3
            // 
            this.menuItem3.Index = 4;
            this.menuItem3.Text = "-";
            // 
            // mnuExit
            // 
            this.mnuExit.Index = 5;
            this.mnuExit.Shortcut = System.Windows.Forms.Shortcut.CtrlQ;
            this.mnuExit.Text = "E&xit";
            this.mnuExit.Click += new System.EventHandler(this.mnuExit_Click);
            // 
            // menuItem2
            // 
            this.menuItem2.Index = 1;
            this.menuItem2.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.changeBifurcationPlot});
            this.menuItem2.Text = "&Edit";
            // 
            // changeBifurcationPlot
            // 
            this.changeBifurcationPlot.Index = 0;
            this.changeBifurcationPlot.Text = "Change Bifurcation Plot Settings";
            this.changeBifurcationPlot.Click += new System.EventHandler(this.changeBifurcationPlot_Click);
            // 
            // oSBWMenu
            // 
            this.oSBWMenu.Index = 2;
            this.oSBWMenu.Text = "&SBW";
            // 
            // codeTextBox1
            // 
            this.codeTextBox1.Font = new System.Drawing.Font("Courier New", 10F);
            this.codeTextBox1.Location = new System.Drawing.Point(416, 104);
            this.codeTextBox1.MaxLength = 0;
            this.codeTextBox1.Multiline = true;
            this.codeTextBox1.Name = "codeTextBox1";
            this.codeTextBox1.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.codeTextBox1.Size = new System.Drawing.Size(100, 200);
            this.codeTextBox1.TabIndex = 0;
            this.codeTextBox1.Text = "codeTextBox1";
            this.codeTextBox1.WordWrap = false;
            // 
            // menuItem4
            // 
            this.menuItem4.Index = 2;
            this.menuItem4.Text = "-";
            // 
            // mnuCopyCSV
            // 
            this.mnuCopyCSV.Index = 3;
            this.mnuCopyCSV.Shortcut = System.Windows.Forms.Shortcut.CtrlC;
            this.mnuCopyCSV.Text = "Copy CSV to Clipboard";
            this.mnuCopyCSV.Click += new System.EventHandler(this.OnCopyClick);
            // 
            // MainForm
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(760, 606);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Menu = this.mainMenu1;
            this.MinimumSize = new System.Drawing.Size(776, 645);
            this.Name = "MainForm";
            this.Text = "Auto2000 C# ";
            this.Load += new System.EventHandler(this.OnFormLoad);
            this.panel1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.tabRun.ResumeLayout(false);
            this.panel7.ResumeLayout(false);
            this.panel6.ResumeLayout(false);
            this.tabAdvanced.ResumeLayout(false);
            this.panel8.ResumeLayout(false);
            this.panel10.ResumeLayout(false);
            this.panel10.PerformLayout();
            this.panel9.ResumeLayout(false);
            this.tabJarnac.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.panel5.ResumeLayout(false);
            this.panel5.PerformLayout();
            this.panel4.ResumeLayout(false);
            this.tabFort7.ResumeLayout(false);
            this.tabFort7.PerformLayout();
            this.tabCode.ResumeLayout(false);
            this.tabCode.PerformLayout();
            this.tabSBML.ResumeLayout(false);
            this.tabSBML.PerformLayout();
            this.ResumeLayout(false);

        }
        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Button cmdLoad;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabRun;
        private System.Windows.Forms.TabPage tabJarnac;
        private System.Windows.Forms.TabPage tabFort7;
        private System.Windows.Forms.TabPage tabCode;
        private System.Windows.Forms.TabPage tabSBML;
        private AutoFrontend.Controls.CodeTextBox codeTextBox1;
        private AutoFrontend.Controls.CodeTextBox txtResult;
        private AutoFrontend.Controls.CodeTextBox txtCode;
        private AutoFrontend.Controls.CodeTextBox txtSBML;
        private AutoFrontend.Controls.CodeTextBox txtJarnac;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.Button cmdSendToAuto;
        private System.Windows.Forms.TabPage tabAdvanced;
        private AutoFrontend.Controls.CodeTextBox txtConfig;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.Splitter splitter1;
        private System.Windows.Forms.Panel panel7;
        private AutoFrontend.Controls.GraphControl graphControl1;
        private AutoFrontend.Controls.SetupControl setupControl1;
        private System.Windows.Forms.MainMenu mainMenu1;
        private System.Windows.Forms.MenuItem menuItem1;
        private System.Windows.Forms.MenuItem mnuOpen;
        private System.Windows.Forms.MenuItem menuItem3;
        private System.Windows.Forms.MenuItem mnuExit;
        private System.Windows.Forms.Panel panel8;
        private System.Windows.Forms.Panel panel9;
        private System.Windows.Forms.Panel panel10;
        private System.Windows.Forms.CheckBox chkTakeAsIs;
        private System.Windows.Forms.MenuItem oSBWMenu;
        private MenuItem mnuExport;
        private MenuItem menuItem4;
        private MenuItem mnuCopyCSV;

    }
}
