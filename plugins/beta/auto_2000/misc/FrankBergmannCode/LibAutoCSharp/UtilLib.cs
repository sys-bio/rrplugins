using System;
using System.Collections;

namespace LibAutoCSharp
{   

	/// <summary>
	/// Summary description for Util.
	/// </summary>
	public class UtilLib
	{
		public static string[] Split(string source, params char[] seperators)
		{
			var oRaw = source.Split(seperators);
			var oList = new ArrayList();
			for (int i = 0; i < oRaw.Length; i++)
			{
				if (oRaw[i] != null && oRaw[i].Trim().Length > 0)
					oList.Add(oRaw[i]);
			}

			var oResult = new string[oList.Count];
			oList.CopyTo(oResult);
			return oResult;

		}

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

        public static double ConvertToDouble(string s)
        {
            try
            {
                return Convert.ToDouble(s);
            }
            catch (Exception)
            {
                return 0.0;
            }
        }

		public static int ConvertToInt(string s, int nDefault)
		{
			try
			{
				return (int)Convert.ToDouble(s);
			}
			catch (Exception)
			{
				return nDefault;
			}
		}

        public static int ConvertToInt(string s)
        {
            try
            {
                return Convert.ToInt32(s);
            }
            catch (Exception)
            {
                return 0;
            }
        }

        public static string ConvertIntTypeToString(int type)
        {
            switch (type)
            {
                case 1: return "Branch Point (algebraic Problem)";
                case 2: return "Fold (algebraic Problem)";
                case 3: return "Hopf Bifurcation (algebraic Problem)";
                case 4: return "Regular Point";
                case -4: return "User requested Point";
                case 5: return "Fold (ODE)";
                case 6: return "Bifurcation Point (ODE)";
                case 7: return "Period Doubling Bifurcation (ODE)";
                case 8: return "Bifurcation to invarient torus (ODE)";
                case 9: return "Normal begin or end";
                case -9: return "Abnormal Termination";
                default: return "No Label";
            }
        }

        public static string ConvertIntTypeToShortString(int type)
        {
            switch (type)
            {
                case 1: return "BP";
                case 2: return "LP";
                case 3: return "HB";
                case 4: return "RG";
                case -4: return "UZ";
                case 5: return "LP";
                case 6: return "BP";
                case 7: return "PD";
                case 8: return "TR";
                case 9: return "EP";
                case -9: return "MX";
                default: return "No Label";
            }
        }

        public static string GetTempPath()
        {
            string sResult = Environment.GetEnvironmentVariable("TEMP");
            if (string.IsNullOrEmpty(sResult)) sResult = "/tmp/";
            return sResult;
        }


        public static int FindClosestStablePoint(int pos, IntPairCollection positions)
        {
            foreach (IntPair pair in positions)
            {
                if ((pos == pair.Key + 1) || (pos == pair.Key - 1)) return pair.Key;
            }
            return pos;
        }
    }
}
