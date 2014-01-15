using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Threading;

namespace LibAutoCSharp
{
    public class AutoResult
    {

        static string Fort7FileName = Path.Combine( UtilLib.GetTempPath() ,"fort.7");
        static string Fort8FileName = Path.Combine( UtilLib.GetTempPath() ,"fort.8");
        static string Fort9FileName = Path.Combine( UtilLib.GetTempPath() ,"fort.9");

        public AutoResult()
            : this(Fort7FileName)
        {
        }

        public AutoResult(string sFileName)
        {
            System.Globalization.CultureInfo culture = System.Globalization.CultureInfo.CreateSpecificCulture("en");
            culture.NumberFormat.NumberDecimalSeparator = ".";
            Thread.CurrentThread.CurrentCulture = culture;
            AllRuns = new AutoResultRunCollection();
            AllRuns.Add(new AutoResultRun()); 
            ReadFort7File(sFileName);
        }

        public void ReadFort7File(string sFileName)
        {
            if (!File.Exists(sFileName))
                throw new ArgumentException("Fort.7 file does not exist ... ");

            try
            {
                StreamReader oReader = new StreamReader(sFileName);

                string sFort7Content = oReader.ReadToEnd();

                oReader.Close();

                AnalyzeFort7File(sFort7Content);
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.Message);
                //
            }

        }

        //Point Types in AUTO.pdf page 20
        //enum PointType
        //{
        //    BranchPoint = 1,        // BP
        //    Fold = 2,               // LP
        //    HopfBifurcation = 3,    // HB
        //}

        private string _Fort7 = "";
        public string Fort7
        {
            get
            {
                return _Fort7;
            }
            set { _Fort7 = value; }
        }

        public static string NewFort7
        {
            get
            {
                if (File.Exists(Fort7FileName))
                    return File.ReadAllText(Fort7FileName);
                return "";
            }
        }

        public static string NewFort8
        {
            get
            {
                if (File.Exists(Fort8FileName))
                    return File.ReadAllText(Fort8FileName);
                return "";
            }
        }

        public static string NewFort9
        {
            get
            {
                if (File.Exists(Fort9FileName))
                    return File.ReadAllText(Fort9FileName);
                return "";
            }
        }

        private bool _ErrorOccured = false;
        public bool ErrorOccured
        {
            get { return _ErrorOccured; }
            set { _ErrorOccured = value; }
        }

        private void AnalyzeFort7File(string sFort7Content)
        {
            _Fort7 = sFort7Content;

            CurrentRun = AllRuns[AllRuns.Count - 1];

            string[] sLines = UtilLib.Split(sFort7Content, '\n');
            int nCount = 0;
            bool readSomething = false;
            foreach (string line in sLines)
            {
                try
                {
                    //if (line.Contains("0    PT  TY LAB"))
                    //{
                    //    AllRuns.Add(new AutoResultRun());
                    //    CurrentRun = AllRuns[AllRuns.Count - 1];
                    //    nCount = 0;
                    //}

                    string[] sColumns = UtilLib.Split(line, ' ');
                    if (sColumns[0].Trim() == "0" || sColumns.Length < 7)
                    {
                        //if (readSomething) break;
                        continue; // skip over comments
                    }


                    int nPoint = UtilLib.ConvertToInt(sColumns[1], 0);
                    if (Data.Count > 1 && Math.Sign(Data[nCount - 1].Point) != Math.Sign(nPoint))
                    {
                        Positions.Add(new IntPair(nCount, nPoint));
                        //System.Diagnostics.Debug.WriteLine("Stability change: " + nCount + " point: " + nPoint);
                    }

                    int nType = UtilLib.ConvertToInt(sColumns[2], 0);
                    int nLabel = UtilLib.ConvertToInt(sColumns[3], 0);



                    if (nType == -9 && !readSomething)
                    {
                        _ErrorOccured = true;
                    }

                    double dPar = UtilLib.ConvertToDouble(sColumns[4], double.NaN);
                    double dL2Norm = UtilLib.ConvertToDouble(sColumns[5], double.NaN);

                    NumVariables = sColumns.Length - 6;
                    var dVariables = new double[NumVariables];
                    for (int i = 0; i < NumVariables; i++)
                    {
                        dVariables[i] = UtilLib.ConvertToDouble(sColumns[6 + i], double.NaN);
                    }

                    Data.Add(new DataPoint(nPoint, nType, nLabel, dPar, dVariables));

                    if (nLabel != 0 && nType != 4 && nType != 9 && nType != -9)
                    {
                        Labels.Add(new IntTripple(Math.Abs(nPoint) - 1, nLabel, nType));
                    }


                    readSomething = true;
                    nCount++;
                }
                catch
                {
                    continue;
                }

            }
        }


        public AutoResultRunCollection AllRuns { get; set; }


        public AutoResultRun CurrentRun { get; set; }

        public List<double[]> DataSeries
        {
            get
            {
                return CurrentRun.DataSeries ;
            }
        }


        public IntTrippleCollection Labels
        {
            get
            {
                return CurrentRun.Labels;
            }
            set
            {
            	CurrentRun.Labels = value;
            }
        }

        public int NumPoints
        {
            get
            {
                return CurrentRun.NumPoints;
            }
        }

        public int NumVariables
        {
            get
            {
                return CurrentRun.NumVariables;
            }
            set
            {
                CurrentRun.NumVariables = value;
            }
        }

        public IntPairCollection Positions
        {
            get
            {
                return CurrentRun.Positions;
            }
            set
            {
            	CurrentRun.Positions = value;
            }
        }
        
        public DataPointCollection Data
        {
            get
            {
                return CurrentRun.Data;
            }
            set
            {
                CurrentRun.Data = value;
            }
        }

    }
}
