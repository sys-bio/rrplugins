using System;
using System.Collections.Generic;
using System.Drawing.Drawing2D;
using System.Text;
using AutoFrontend.SBWModules;
using SBW;
using ZedGraph;

namespace AutoFrontend
{
    /// <summary>
    ///     Summary description for Util.
    /// </summary>
    internal class Util
    {
        public static double ConvertToDouble(string s, double dDefault)
        {
            try
            {
                return Convert.ToDouble(s);
            }
            catch (Exception)
            {
                return dDefault;
            }
        }

        public static int ConvertToInt(string s, int nDefault)
        {
            try
            {
                return Convert.ToInt32(s);
            }
            catch (Exception)
            {
                return nDefault;
            }
        }

        public static string ConvertToJarnac(string sSBML)
        {
            try
            {
                return
                    HighLevel.call("JarnacLiteConsole", "translator", "string translate(string)",
                                   new DataBlockWriter(new object[] {sSBML})).getString();
            }
            catch
            {
                return "";
            }
        }

        public static string ConvertToSBML(string sJarnac)
        {
            try
            {
                return
                    HighLevel.call("JarnacLiteConsole", "translator", "string translateSBML(string)",
                                   new DataBlockWriter(new object[] {sJarnac})).getString();
            }
            catch
            {
                return "";
            }
        }

        public static string GenerateCSV(double[,] data,
                                         List<string> headers,
                                         string separator)
        {
            var oBuilder = new StringBuilder();

            for (int i = 0; i < headers.Count; i++)
            {
                oBuilder.Append(headers[i]);
                if (i < headers.Count - 1)
                    oBuilder.Append(separator);
            }
            oBuilder.AppendLine();

            WriteDataToBuilder(oBuilder, data, separator);

            return oBuilder.ToString();
        }

        public static string GenerateCSV(MasterPane masterPane, string separator = ", ")
        {
            var sb = new StringBuilder();

            foreach (GraphPane item in masterPane.PaneList)
            {
                sb.Append(item.XAxis.Title.Text);
                sb.Append(separator);
                int numCurves = item.CurveList.Count;
                for (int i = 0; i < numCurves; i++)
                {
                    sb.Append(item.CurveList[i].Label.Text);
                    if (i + 1 < numCurves)
                        sb.Append(separator);
                }
                sb.AppendLine();

                int numPoints = item.CurveList[0].NPts;
                for (int i = 0; i < numPoints; i++)
                {
                    sb.Append(item.CurveList[0].Points[i].X);
                    sb.Append(separator);
                    for (int k = 0; k < numCurves; k++)
                    {
                        sb.Append(item.CurveList[k].Points[i].Y);
                        if (k + 1 < numCurves)
                            sb.Append(separator);
                    }
                    sb.AppendLine();
                }
            }

            return sb.ToString();
        }

        public static string GenerateTex(MasterPane masterPane)
        {
            var sb = new StringBuilder();

            sb.AppendLine("%\\documentclass{article}");
            sb.AppendLine("%\\usepackage{tikz}");
            sb.AppendLine("%\\usepackage{pgf}");
            sb.AppendLine("%\\usepackage{pgfplots}");
            sb.AppendLine("%\\usetikzlibrary{shapes,snakes,arrows}");
            sb.AppendLine("%\\begin{document}");
            sb.AppendLine("%\\begin{center}");

            foreach (GraphPane item in masterPane.PaneList)
            {
                sb.AppendLine("\\begin{tikzpicture}");

                string graphType = GetGraphType(item);

                sb.AppendLine(String.Format("\\begin{{{0}}}[", graphType));
                sb.AppendLine("grid=major,");
                if (!string.IsNullOrEmpty(item.Title.Text)) sb.AppendLine(String.Format("title={0}, ", item.Title.Text));
                else if (!string.IsNullOrEmpty(masterPane.Title.Text) && masterPane.PaneList.IndexOf(item) < 1)
                    sb.AppendLine(String.Format("title={0}, ", masterPane.Title.Text));
                sb.AppendLine(string.Format("ymin={0},ymax={1},xmin={2},xmax={3},", item.YAxis.Scale.Min,
                                            item.YAxis.Scale.Max, item.XAxis.Scale.Min, item.XAxis.Scale.Max));
                if (!string.IsNullOrEmpty(item.XAxis.Title.Text))
                    sb.AppendLine(String.Format("xlabel={0}, ", item.XAxis.Title.Text));
                if (!string.IsNullOrEmpty(item.YAxis.Title.Text))
                    sb.AppendLine(String.Format("ylabel={0}, ", item.YAxis.Title.Text));
                sb.AppendLine("width=10cm, height=8cm,");
                sb.AppendLine("legend style={at={(0.5,-0.15)},anchor=north,legend columns=5},");
                sb.AppendLine("]");

                foreach (CurveItem curve in item.CurveList)
                {
                    sb.AppendLine(String.Format("\\definecolor{{currentcolor{0}}}{{rgb}}{{ {1}, {2}, {3}}}", item.CurveList.IndexOf(curve), ((double)curve.Color.R / 255f), ((double)curve.Color.G / 255f), ((double)curve.Color.B / 255f)));
                    var line = curve as LineItem;
                    if (line == null) continue;
                    string marker = GetMarker(line);
                    string lineStyle = GetLineStyle(line);


                    sb.Append(
                        string.Format("\\addplot[currentcolor{0}, smooth, line width={1}pt,{2}{3}]",
                                      item.CurveList.IndexOf(curve),
                                      line.Line.Width,
                                      lineStyle,
                                      marker));
                    sb.AppendLine(" coordinates {"); //[mark=none]
                    for (int j = 0; j < curve.NPts; j++)
                    {
                        sb.AppendLine(string.Format("({0}, {1})", curve.Points[j].X, curve.Points[j].Y));
                    }
                    sb.AppendLine("};");
                    sb.AppendLine(String.Format("\\addlegendentry{{${0}$}}", curve.Label.Text.Replace("_", "\\_")));
                }
                sb.AppendLine(String.Format("\\end{{{0}}}", graphType));
                sb.AppendLine("\\end{tikzpicture}");
            }
            sb.AppendLine("%\\end{center}");
            sb.AppendLine("%\\end{document}");

            return sb.ToString();
        }

        public static string GenerateTex(double[,] data, List<string> headers)
        {
            var sb = new StringBuilder();

            //sb.AppendLine("\\usepackage{tikz}");
            //sb.AppendLine("\\usepackage{pgf}");
            //sb.AppendLine("\\usepackage{pgfplots}");
            //sb.AppendLine();
            //sb.AppendLine("\\begin{document}");
            //sb.AppendLine("\\begin{center}");
            sb.AppendLine("\\begin{tikzpicture}");
            sb.AppendLine("\\begin{axis}[");
            sb.AppendLine("grid=major,");
            sb.AppendLine("]");

            for (int i = 1; i < headers.Count; i++)
            {
                sb.AppendLine("\\addplot coordinates {"); //[mark=none]
                for (int j = 0; j < data.GetLength(0); j++)
                {
                    sb.AppendLine(string.Format("({0}, {1})", data[j, 0], data[j, i]));
                }
                sb.AppendLine("};");
                sb.AppendLine(String.Format("\\addlegendentry{{${0}$}}", headers[i].Replace("_", "\\_")));
            }


            sb.AppendLine("\\end{axis}");
            sb.AppendLine("\\end{tikzpicture}");

            //sb.AppendLine("\\end{center}");
            //sb.AppendLine("\\end{document}");
            return sb.ToString();
        }

        private static string GetGraphType(GraphPane item)
        {
            string graphType;

            if (item.XAxis.Type == AxisType.Log && item.YAxis.Type == AxisType.Linear)
            {
                graphType = "semilogxaxis";
            }
            else if (item.XAxis.Type == AxisType.Linear && item.YAxis.Type == AxisType.Log)
            {
                graphType = "semilogyaxis";
            }
            else if (item.XAxis.Type == AxisType.Log && item.YAxis.Type == AxisType.Log)
            {
                graphType = "loglogaxis";
            }
            else
            {
                graphType = "axis";
            }
            return graphType;
        }

        private static string GetLineStyle(LineItem line)
        {
            string lineStyle;

            switch (line.Line.Style)
            {
                case DashStyle.Dash:
                case DashStyle.DashDot:
                    lineStyle = "dashed,";
                    break;
                case DashStyle.DashDotDot:
                case DashStyle.Dot:
                    lineStyle = "dotted,";
                    break;
                case DashStyle.Solid:
                default:
                    lineStyle = "";
                    break;
            }
            return lineStyle;
        }

        private static string GetMarker(LineItem line)
        {
            string marker;
            switch (line.Symbol.Type)
            {
                case SymbolType.Circle:
                    marker = "mark=o,";
                    break;
                case SymbolType.Diamond:
                    marker = "mark=diamond,";
                    break;
                case SymbolType.HDash:
                    marker = "mark=-,";
                    break;
                case SymbolType.Plus:
                    marker = "mark=+,";
                    break;
                case SymbolType.Square:
                    marker = "mark=square,";
                    break;
                case SymbolType.Star:
                    marker = "mark=star,";
                    break;
                case SymbolType.Triangle:
                    marker = "mark=triangle,";
                    break;
                case SymbolType.VDash:
                    marker = "mark=|,";
                    break;
                case SymbolType.XCross:
                    marker = "mark=x,";
                    break;
                case SymbolType.Default:
                case SymbolType.None:
                default:
                    marker = "";
                    break;
            }
            return marker;
        }

        public static string GetSBMLForParameter(NameValuePair oParameter)
        {
            SBMLSupport.loadSBML(MainForm.Simulator.getSBML());
            SBMLSupport.setValue(oParameter.Name, (double) oParameter.Value);
            return SBMLSupport.getSBML();
        }

        public static void SentToSimulator(string sSBML)
        {
            try
            {
                HighLevel.send("edu.kgi.roadRunner.sim Simulation Service", "wrapper", "void doAnalysis(string)",
                               new DataBlockWriter(new object[] {sSBML}));
            }
            catch
            {
            }
        }

        private static void WriteDataToBuilder(StringBuilder builder,
                                               double[,] data,
                                               string separator)
        {
            WriteDataToBuilder(builder, data, separator, "G17");
        }

        public static void WriteDataToBuilder(StringBuilder builder, double[][] data, string separator, string format)
        {
            if (builder == null || data == null || data.Length == 0 || String.IsNullOrEmpty(separator))
                return;

            for (int i = 0; i < data.Length; i++)
            {
                for (int j = 0; j < data[i].Length; j++)
                {
                    builder.Append(data[i][j].ToString(format));
                    if (j + 1 < data[i].Length)
                        builder.Append(separator);
                }
                builder.Append("\n");
            }
        }

        private static void WriteDataToBuilder(StringBuilder builder,
                                               double[,] data,
                                               string separator, string format)
        {
            if (builder == null || data == null || data.Length == 0 || String.IsNullOrEmpty(separator))
                return;

            for (int i = 0; i < data.GetLength(0); i++)
            {
                for (int j = 0; j < data.GetLength(1); j++)
                {
                    builder.Append(data[i, j].ToString(format));
                    if (j + 1 < data.GetLength(1))
                        builder.Append(separator);
                }
                builder.Append("\n");
            }
        }
    }
}