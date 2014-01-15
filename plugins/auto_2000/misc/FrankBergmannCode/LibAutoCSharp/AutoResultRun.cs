using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;

namespace LibAutoCSharp
{
    public class AutoResultRun
    {

        private IntPairCollection _Positions = new IntPairCollection();
        public IntPairCollection Positions
        {
            get { return _Positions; }
            set { _Positions = value; }
        }

        private int _NumVariables;
        public int NumVariables
        {
            get { return _NumVariables; }
            set { _NumVariables = value; }
        }

        public int NumPoints
        {
            get { return Data.Count; }
        }

        private IntTrippleCollection _Labels = new IntTrippleCollection();
        public IntTrippleCollection Labels
        {
            get { return _Labels; }
            set { _Labels = value; }
        }

        DataPointCollection _Data = new DataPointCollection();

        public DataPointCollection Data
        {
            get
            {
                return _Data;
            }
            set
            {
                _Data = value;
            }
        }
        public List<double[]> DataSeries
        {
            get
            {
                var oSeries = new List<double[]>();
                var oParSeries = new double[Data.Count];

                if (Data.Count > 0)
                {

                    var oVariableSeries = new double[Data[0].NumVariables][];

                    for (int j = 0; j < oVariableSeries.Length; j++)
                        oVariableSeries[j] = new double[Data.Count];

                    for (int i = 0; i < Data.Count; i++)
                    {
                        oParSeries[i] = Data[i].Par;

                        for (int j = 0; j < oVariableSeries.Length; j++)
                        {
                            try
                            {
                                oVariableSeries[j][i] = Data[i].Variables[j];
                            }
                            catch
                            {
                            }
                        }
                    }
                    oSeries.Add(oParSeries);
                    for (int j = 0; j < oVariableSeries.Length; j++)
                        oSeries.Add(oVariableSeries[j]);
                }
                return oSeries;
            }
        }

        public AutoResultRun()
        {

        }
    }
}
