using System;

using System.Runtime.InteropServices;

namespace LibAutoCSharp
{
	//[UnmanagedFunctionPointerAttribute(CallingConvention.StdCall, CharSet = CharSet.Ansi, SetLastError = false)]
	public delegate void FuncCallBack2
	(IntPtr u,             
	IntPtr par,             
	IntPtr f);

	//[UnmanagedFunctionPointerAttribute(CallingConvention.StdCall, CharSet = CharSet.Ansi, SetLastError = false)]
	public delegate int FuncCallBack
	(int ndim,
	IntPtr u,
	IntPtr icp,
	IntPtr par,
	int ijac,
	IntPtr f,
	IntPtr dfdu,
	IntPtr dfdp);   	
    
	//[UnmanagedFunctionPointerAttribute(CallingConvention.StdCall, CharSet = CharSet.Ansi, SetLastError = false)]
	public delegate int StpntCallBack(int ndim, double t, IntPtr u, IntPtr par);

	//[UnmanagedFunctionPointerAttribute(CallingConvention.StdCall, CharSet = CharSet.Ansi, SetLastError = false)]
	public delegate int BcndCallBack(int ndim, IntPtr par, IntPtr icp, int nbx, IntPtr u0, IntPtr u1, int ijac, IntPtr fb, IntPtr dbc);


	//[UnmanagedFunctionPointerAttribute(CallingConvention.StdCall, CharSet = CharSet.Ansi, SetLastError = false)]
	public delegate int IcndCallBack(int ndim, IntPtr par, IntPtr icp, int nint, IntPtr u, IntPtr uold, IntPtr udot, IntPtr upold, int ijac, IntPtr fi, IntPtr dint);

	//[UnmanagedFunctionPointerAttribute(CallingConvention.StdCall, CharSet = CharSet.Ansi, SetLastError = false)]
	public delegate int FoptCallBack(int ndim, IntPtr u, IntPtr icp, IntPtr par, int ijac, IntPtr fs, IntPtr dfdu, IntPtr dfdp);

	//[UnmanagedFunctionPointerAttribute(CallingConvention.StdCall, CharSet = CharSet.Ansi, SetLastError = false)]
	public delegate int PvlsCallBack(int ndim, IntPtr u, IntPtr par);


	public class AutoInterface
	{
		private const string AutoLibrary = "LibAuto";

		[DllImport(AutoLibrary, EntryPoint = "setCallbackFunc2", ExactSpelling = false,
			 CharSet = CharSet.Ansi, SetLastError = false, CallingConvention=CallingConvention.StdCall)]
		public static extern void setCallbackFunc2(FuncCallBack2 cb);

		[DllImport(AutoLibrary, EntryPoint = "setCallbackStpnt", ExactSpelling = false,
			 CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
		public static extern void setCallbackStpnt(StpntCallBack cb);

        [DllImport(AutoLibrary, CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
		public static extern void setCallbackBcnd(BcndCallBack cb);
        [DllImport(AutoLibrary, CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
		public static extern void setCallbackIcnd(IcndCallBack cb);
        [DllImport(AutoLibrary, CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
		public static extern void setCallbackFopt(FoptCallBack cb);
        [DllImport(AutoLibrary, CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
		public static extern void setCallbackPvls(PvlsCallBack cb);

		[DllImport(AutoLibrary, EntryPoint = "CallAuto", ExactSpelling = false,
			 CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
		
        public static extern void CallAuto();

		[DllImport(AutoLibrary, EntryPoint = "SetAutoNumParameters", ExactSpelling = false,
			 CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]  
		public static extern void SetAutoNumParameters(int numParameters);

		[DllImport(AutoLibrary, EntryPoint = "getFort7File", ExactSpelling = false,
			 CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
		public static extern string getFort7File(out int length);

        [DllImport(AutoLibrary, EntryPoint = "getFort8File", ExactSpelling = false,
             CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
        public static extern string getFort8File(out int length);

        [DllImport(AutoLibrary, EntryPoint = "getFort9File", ExactSpelling = false,
             CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
        public static extern string getFort9File(out int length);

		[DllImport(AutoLibrary, EntryPoint = "setFort2File", ExactSpelling = false,
			 CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
		public static extern void setFort2File(string sContent, int length);

        [DllImport(AutoLibrary, EntryPoint = "setFort3File", ExactSpelling = false,
             CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
        public static extern void setFort3File(string sContent, int length);

        [DllImport(AutoLibrary, EntryPoint = "setFort7File", ExactSpelling = false,
             CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
        public static extern void setFort7File(string sContent, int length);

        [DllImport(AutoLibrary, EntryPoint = "setFort8File", ExactSpelling = false,
             CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
        public static extern void setFort8File(string sContent, int length);

        [DllImport(AutoLibrary, EntryPoint = "GetLastMessage", ExactSpelling = false,
          CharSet = CharSet.Ansi, SetLastError = false, CallingConvention = CallingConvention.StdCall)]
        private static extern IntPtr GetLastMessagePtr();

        public static string GetLastMessage()
        {
            IntPtr pointer = GetLastMessagePtr();
            if (pointer == IntPtr.Zero)
                return null;
            return Marshal.PtrToStringAnsi(pointer);
        }
           		
	}
}
