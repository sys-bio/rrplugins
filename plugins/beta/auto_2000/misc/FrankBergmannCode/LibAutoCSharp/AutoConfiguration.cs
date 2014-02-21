using System;
using System.Threading;

namespace LibAutoCSharp
{
	/// <summary>
	/// Summary description for AutoConfiguration.
	/// </summary>

	public class AutoConfiguration
	{

		public static string DefaultConfig
		{
			get
			{
				AutoConfiguration oDefault = new AutoConfiguration(0.0, 10.0, true, 2);
				return oDefault.GenerateConfigFile();
			}
		}

		private double _StartValue;
		public double StartValue
		{
			get { return _StartValue; }
			set { _StartValue = value; }
		}

		private double _Endvalue;
		public double EndValue
		{
			get { return _Endvalue; }
			set { _Endvalue = value; }
		}

		private bool _Direction;
		public bool Direction
		{
			get { return _Direction; }
			set { _Direction = value; }
		}

		private int _NumVariables;
		public int NumVariables
		{
			get { return _NumVariables; }
			set { _NumVariables = value; }
		}

        private int _MaxNumSteps  = 1000;
        public int MaxNumSteps
        {
            get { return _MaxNumSteps; }
            set { _MaxNumSteps = value; }
        }

        private int? _Label;
        public int? Label
        {
            get { return _Label; }
            set { _Label = value; }
        }

		/// <summary>
		/// Initializes a new instance of the AutoConfiguration class.
		/// </summary>
		/// <param name="startValue"></param>
		/// <param name="endvalue"></param>
		/// <param name="direction"></param>
		/// <param name="numVariables"></param>
		public AutoConfiguration(double startValue, double endvalue, bool direction, int numVariables)
            : this(startValue, endvalue, direction, numVariables, 1000)
		{
        }

        /// <summary>
        /// Initializes a new instance of the AutoConfiguration class.
        /// </summary>
        /// <param name="startValue"></param>
        /// <param name="endvalue"></param>
        /// <param name="direction"></param>
        /// <param name="numVariables"></param>
        /// <param name="maxNumSteps"></param>
        public AutoConfiguration(double startValue, double endvalue, bool direction, int numVariables, int maxNumSteps)
            : this(startValue, endvalue, direction, numVariables, maxNumSteps, null)
        {
        }


        /// <summary>
        /// Initializes a new instance of the AutoConfiguration class.
        /// </summary>
        /// <param name="startValue"></param>
        /// <param name="endvalue"></param>
        /// <param name="direction"></param>
        /// <param name="numVariables"></param>
        /// <param name="maxNumSteps"></param>
        /// <param name="label"></param>
        public AutoConfiguration(double startValue, double endvalue, bool direction, int numVariables, int maxNumSteps, int? label) : this()
        {
            _StartValue = startValue;
            _Endvalue = endvalue;
            _Direction = direction;
            _NumVariables = numVariables;
            _MaxNumSteps = maxNumSteps;
            _Label = label;
        }


        public AutoConfiguration()
		{
            System.Globalization.CultureInfo culture = System.Globalization.CultureInfo.CreateSpecificCulture("en");
            culture.NumberFormat.NumberDecimalSeparator = ".";
            Thread.CurrentThread.CurrentCulture = culture;
		}

		public string GenerateConfigFile()
		{
            //return String.Format(
            //    "{1} 1 {6} 1                     NDIM,IPS,IRS,ILP {0}" +
            //    "1 0                         NICP,(ICP(I),I=1 NICP) {0}" +
            //    "15 4 3 1 1 0 0 0            NTST,NCOL,IAD,ISP,ISW,IPLT,NBC,NINT {0}" +
            //    "{5} {2} {3} 0 10000           NMX,RL0,RL1,A0,A1 {0}" +
            //    "50 100 0 8 5 3 0            NPR,MXBF,IID,ITMX,ITNW,NWTN,JAC {0}" +
            //    "1e-008 1e-008 1e-006        EPSL,EPSU,EPSS {0}" +
            //    "{4}0.001 1e-005 0.1 1          DS,DSMIN,DSMAX,IADS{0}" +
            //    "0                           NTHL,(/,I,THL(I)),I=1,NTHL) {0}" +
            //    "0                           NTHU,(/,I,THU(I)),I=1,NTHU) {0}" +
            //    "0                           NUZR,(/,I,PAR(I)),I=1,NUZR){0}{0}{0}",
            //    Environment.NewLine, NumVariables, StartValue, EndValue, (Direction ? "" : "-"), MaxNumSteps, 
            //    (Label.HasValue ? Label.Value : 0)
            //    );

            ApplySettingsToCurrentConfig();

            return CurrentConfig.ToInputString();
		}

        public void ApplySettingsToCurrentConfig()
        {
            CurrentConfig.NDIM = NumVariables;
            CurrentConfig.RL0 = StartValue;
            CurrentConfig.RL1 = EndValue;
            if (Direction)
                CurrentConfig.DS = Math.Abs(CurrentConfig.DS);
            else
                CurrentConfig.DS = Math.Abs(CurrentConfig.DS) * -1;
            CurrentConfig.NMX = MaxNumSteps;

            if (Label.HasValue)
                CurrentConfig.IRS = Label.Value;
            else
                CurrentConfig.IRS = 0;
        }


        private AutoInputConstants _CurrentConfig = AutoInputConstants.DefaultConstants;
        public AutoInputConstants CurrentConfig
        {
            get { return _CurrentConfig; }
            set { _CurrentConfig = value; }
        }


	}
}
