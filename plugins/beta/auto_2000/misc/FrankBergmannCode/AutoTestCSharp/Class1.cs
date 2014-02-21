using System;

using LibAutoCSharp;

using System.Runtime.InteropServices;


namespace AutoTestCSharp
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class Class1
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			FuncCallBack2 oFunc2 = new FuncCallBack2(FunctionCallback2);			
			StpntCallBack oStpnt = new StpntCallBack(StpntCallback);
			BcndCallBack oBcnd = new BcndCallBack(BoundaryCallback);


			//AutoInterface.SetAutoNumParameters(36);
			AutoInterface.setCallbackFunc2(oFunc2);
			AutoInterface.setCallbackStpnt(oStpnt);
			AutoInterface.setCallbackBcnd(oBcnd);
			//AutoInterface.setFort2File(global::AutoTorCSharp.Properties.Resources.fort, global::AutoTorCSharp.Properties.Resources.fort.Length);            
			AutoInterface.CallAuto();

			int nLength = 0;
			string sResult = AutoInterface.getFort7File(out nLength);
			Console.WriteLine(sResult);
			//Console.WriteLine("done!");
		}
		static int BoundaryCallback(int ndim, IntPtr par, IntPtr icp, int nbx, IntPtr u0, IntPtr u1, int ijac, IntPtr fb, IntPtr dbc)
		{
			return 0;
		}

		static void FunctionCallback2(IntPtr u, IntPtr par, IntPtr f)
		{
			// pp2 example actually 

			//Console.WriteLine("start function callback");

			double[] oPar = new double[10];
			double[] oU = new double[2];
			double[] oF = new double[2];
			double[] oRate = new double[4];

			Marshal.Copy(par, oPar, 0, 10);
			Marshal.Copy(u, oU, 0, 2);

			double[] oGp = new double[7];
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
			oRate[1] = oGp[1] * oU[0];
			oRate[2] = (oGp[2] * oU[0] - oGp[3] * oU[1]) * (1.0 + oGp[4] * Math.Pow(oU[1], oGp[5]));
			oRate[3] = oGp[6] * oU[1];

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

		protected internal int FunctionCallback(int ndim, IntPtr u, IntPtr icp, IntPtr par, int ijac, IntPtr f, IntPtr dfdu, IntPtr dfdp)
		{
			// pp2 example actually 

			//Console.WriteLine("start function callback");

			double[] oPar = new double[10];
			double[] oU = new double[ndim];
			double[] oF = new double[ndim];
			double[] oRate = new double[4];

			Marshal.Copy(par, oPar, 0, 10);
			Marshal.Copy(u, oU, 0, ndim);

			double[] oGp = new double[7];
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
			oRate[1] = oGp[1] * oU[0];
			oRate[2] = (oGp[2] * oU[0] - oGp[3] * oU[1]) * (1.0 + oGp[4] * Math.Pow(oU[1], oGp[5]));
			oRate[3] = oGp[6] * oU[1];

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

		static int StpntCallback(int ndim, double t, IntPtr u, IntPtr par)
		{
			//double[] oPar = new double[] { -.9, .5, -.6, .6, .328578, .933578}; 
			//double[] oU = new double[] {0.0, 0.0, 0.0};

			//Marshal.Copy(oPar, 0, par, 6);
			//Marshal.Copy(oU, 0, u, 3);


			// pp2 example

			//double[] oPar = new double[] { 0.0, 3.0, 5.0, 3.0}; 
			//double[] oU = new double[] {0.0, 0.0};

			double[] oPar = new double[] { 1.0, 0.0, 1.0, 0.0, 1.0, 3.0, 5.0, 1.0, 0.0, 0.0 };
			double[] oU = new double[] { 0.992063492063492, 0.2 };


			Marshal.Copy(oPar, 0, par, 10);
			Marshal.Copy(oU, 0, u, oU.Length);

			return 0;
		}

	}
}
