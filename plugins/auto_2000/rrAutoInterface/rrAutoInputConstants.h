#ifndef rrAutoInputConstantsH
#define rrAutoInputConstantsH
#include <vector>
#include <string>
#include "rrProperties.h"
#include "rrProperty.h"
#include "rrRRAutoExporter.h"
//---------------------------------------------------------------------------

namespace rrauto
{
class SetupControl;
class RRAuto;
using std::vector;
using std::string;

class RRA_DECLSPEC InputConstants
{
    friend SetupControl;
    friend RRAuto;
    public:
        // NDIM: dimension of the system of equations, as specified in the user-supplied subroutine 'func'
        int             NDIM;

        /// IPS: Constant defining the problem type (-2 -> 14) : 1 : stationary states 2 : periodic solutions 4 : BVP
        int             IPS;

        /// Restart label
        int             IRS;

        /// Locate limit points (folds)
        int             ILP;

        /// the number of free parameters
        int             NICP;

        /// the free parameters
        vector<int>     ICP;

        /// the number of mesh intervals
        int             NTST;

        /// the number of collocation points per mesh interval
        int             NCOL;

        /// Mesh adaption:
        ///     0 :fixedmesh
        ///   > 0 : adapt mesh every IAD continuation steps
        int             IAD;

        /// Detection of branch points:
        ///   0 : don’t detect
        ///   1 : detect for algebraic problems
        ///   2 : detect for all problems
        int             ISP;

        /// At a restart solution:
        ///   1 : just follow the branch
        ///  -1 : switch branches (for BPs in BVPs)
        ///   2 : two-parameter continuation (LPs, HBs, PDs, TRs)
        int             ISW;

        /// The ”principal solution measure”
        /// (the second real column in the bifurcation diagram file):
        ///      0 : the L2 norm
        ///   != 0 : other measures (see manual)
        int             IPLT;

        /// the number of boundary conditions (for BVP)
        int             NBC;

        /// the number of integral constraints (for BVP)
        int             NINT;

        /// maximum number of continuation step along any branch
        int             NMX;

        /// bifurcation diagram lower limit for the “first” parameter
        rrp::Property<double>    RL0;

        /// bifurcation diagram upper limit for the “first” parameter
        rrp::Property<double>    RL1;

        /// bifurcation diagram lower limit for the “principal solution measure”
        double          A0;

        /// bifurcation diagram upper limit for the “principal solution measure”
        double          A1;

        /// Save the solution in the solution file every NPR continuation steps
        int             NPR;

        /// For algebraic problems: Maximum number of branch switches (if negative only one “leg” will be computed)
        int             MXBF;

        /// Controls the diagnostic file output (normal value is 2; see manual)
        int             IID;

        /// maximum number of iterations for detecting “special” solutions
        int             ITMX;

        /// maximum number of Newton+Chord iterations
        int             ITNW;

        /// maximum number of Newton iterations
        int             NWTN;

        /// Jacobian supplied ?
        int             JAC;

        /// Newton/Chord convergence tolerance for free parameters
        double          EPSL;

        /// Newton/Chord convergence tolerance for solutions
        double          EPSU;

        /// Continuation step size tolerance when locating special solutions
        double          EPSS;

        /// Nominal continuation step size
        double          DS;

        /// Minimum continuation step size
        double          DSMIN;

        /// Maximum continuation step size
        double          DSMAX;

        /// Adapt the continuation step size every IADS steps
        int             IADS;

        /// the number of modified parameter “weights” (for BVP)
        int             NTHL;

        /// <summary>
        /// parameter index, parameter weight (e.g., ICP(11)=0 means PAR(11) is excluded from the step size)
        /// </summary>
        vector<int>     THL;

        /// the number of modified solution component “weights” (for BVP)
        int             NTHU;

        /// component index, component weight
        vector<int>     THU;

        /// the number of “user output points” specified
        int             NUZR;

        /// parameter index, parameter value (if I is negative the continuation stops at the parameter value)
        vector<int>     UZR;

        string          GetICP();

    public:
                        InputConstants();
        string          getConstantsAsString();
        string              ToInputString();
        rrp::Properties      mInputConstants;
};
}
#endif

//namespace LibAutoCSharp
//{
//    public class AutoInputConstants
//    {
//
//        public static AutoInputConstants DefaultConstants
//        {
//            get
//            {
//                AutoInputConstants input = new AutoInputConstants();
//
//                //"{1} 1 {6} 1                     NDIM,IPS,IRS,ILP {0}" +
//                //"1 0                         NICP,(ICP(I),I=1 NICP) {0}" +
//                //"15 4 3 1 1 0 0 0            NTST,NCOL,IAD,ISP,ISW,IPLT,NBC,NINT {0}" +
//                //"{5} {2} {3} 0 10000           NMX,RL0,RL1,A0,A1 {0}" +
//                //"50 100 0 8 5 3 0            NPR,MXBF,IID,ITMX,ITNW,NWTN,JAC {0}" +
//                //"1e-008 1e-008 1e-006        EPSL,EPSU,EPSS {0}" +
//                //"{4}0.001 1e-005 0.1 1          DS,DSMIN,DSMAX,IADS{0}" +
//                //"0                           NTHL,(/,I,THL(I)),I=1,NTHL) {0}" +
//                //"0                           NTHU,(/,I,THU(I)),I=1,NTHU) {0}" +
//                //"0                           NUZR,(/,I,PAR(I)),I=1,NUZR){0}{0}{0}",
//
//
//                input.NDIM = 3; input.IPS = 1; input.IRS = 0; input.ILP = 1;
//                input.NICP = 1; input.ICP = new IntCollection();
//                input.NTST = 15; input.NCOL = 3; input.IAD = 3; input.ISP = 1; input.ISW = 1; input.IPLT = 0; input.NBC = 0; input.NINT = 0;
//                input.NMX = 1000; input.RL0 = 0; input.RL1 = 100; input.A0 = 0; input.A1 = 10000;
//                input.NPR = 50; input.MXBF = -1; input.IID = 0; input.ITMX = 8; input.ITNW = 5; input.NWTN = 3; input.JAC = 0;
//                input.EPSL = 1e-8; input.EPSU = 1e-8; input.EPSS = 1e-6;
//                input.DS = 0.001; input.DSMIN = 1e-5; input.DSMAX = 0.1; input.IADS = 1;
//                input.NTHL = 0; input.THL = new IntDoublePairCollection();
//                input.NTHU = 0; input.THU = new IntDoublePairCollection();
//                input.NUZR = 0; input.UZR = new IntDoublePairCollection();
//
//                return input;
//            }
//        }
//
//
//        public static AutoInputConstants FromContent(string content)
//        {
//            AutoInputConstants result = AutoInputConstants.DefaultConstants;
//            result.InitializeFromContent(content);
//            return result;
//        }
//
//        public static AutoInputConstants FromFile(string fileName)
//        {
//            AutoInputConstants result = AutoInputConstants.DefaultConstants;
//            result.InitializeFromContent(File.ReadAllText(fileName));
//            return result;
//        }
//
//        public static AutoInputConstants FromStream(Stream stream)
//        {
//            AutoInputConstants result = AutoInputConstants.DefaultConstants;
//            result.InitializeFromStream(stream);
//            return result;
//        }
//
//        public string ToInputString()
//        {
//            StringBuilder builder = new StringBuilder();
//
//
//            string line1 = string.Format("{0} {1} {2} {3}", NDIM, IPS, IRS, ILP);
//            string line2 = GetICP();
//            string line3 = string.Format("{0} {1} {2} {3} {4} {5} {6} {7}", NTST, NCOL, IAD, ISP, ISW, IPLT, NBC, NINT);
//            string line4 = string.Format("{0} {1} {2} {3} {4}", NMX, RL0, RL1, A0, A1);
//            string line5 = string.Format("{0} {1} {2} {3} {4} {5} {6}", NPR, MXBF, IID, ITMX, ITNW, NWTN, JAC);
//            string line6 = string.Format("{0} {1} {2}", EPSL, EPSU, EPSS);
//            string line7 = string.Format("{0} {1} {2} {3}", DS, DSMIN, DSMAX, IADS);
//            string line8 = string.Format("{0}", NTHL);
//            string line9 = string.Format("{0}", NTHU);
//            string line10 = string.Format("{0}", NUZR);
//
//            int maxLength = GetMaxLength(new string[] { line1, line2, line3, line4, line5, line6, line7, line8, line9, line10 });
//
//
//            builder.AppendLine(line1 + WhiteSpaces(line1, maxLength) + " NDIM, IPS, IRS, ILP");
//            builder.AppendLine(line2 + WhiteSpaces(line2, maxLength) + " NICP,(ICP(I),I=1 NICP)");
//            builder.AppendLine(line3 + WhiteSpaces(line3, maxLength) + " NTST,NCOL,IAD,ISP,ISW,IPLT,NBC,NINT");
//            builder.AppendLine(line4 + WhiteSpaces(line4, maxLength) + " NMX,RL0,RL1,A0,A1");
//            builder.AppendLine(line5 + WhiteSpaces(line5, maxLength) + " NPR,MXBF,IID,ITMX,ITNW,NWTN,JAC");
//            builder.AppendLine(line6 + WhiteSpaces(line6, maxLength) + " EPSL,EPSU,EPSS");
//            builder.AppendLine(line7 + WhiteSpaces(line7, maxLength) + " DS,DSMIN,DSMAX,IADS");
//            builder.AppendLine(line8 + WhiteSpaces(line8, maxLength) + " NTHL,((I,THL(I)),I=1,NTHL)");
//            WriteTHL(builder);
//
//            builder.AppendLine(line9 + WhiteSpaces(line9, maxLength) + " NTHU,((I,THU(I)),I=1,NTHU)");
//            WriteTHU(builder);
//
//            builder.AppendLine(line10 + WhiteSpaces(line10, maxLength) + " NUZR,((I,PAR(I)),I=1,NUZR)");
//            WriteUZR(builder);
//
//            builder.AppendLine();
//            builder.AppendLine();
//
//            return builder.ToString();
//        }
//
//        private string WhiteSpaces(string line, int maxLength)
//        {
//            return new string(' ', maxLength - line.Length);
//        }
//
//        private int GetMaxLength(string[] list)
//        {
//            int result = 0;
//            for (int i = 0; i < list.Length; i++)
//            {
//                result = Math.Max(result, list[i].Length);
//            }
//            return result;
//        }
//
//
//        private string GetICP()
//        {
//            StringBuilder builder = new StringBuilder();
//            builder.Append(NICP);
//
//            foreach (int i in ICP)
//            {
//                builder.Append(" " + i);
//            }
//
//            if (ICP.Count == 0) builder.Append(" 0");
//
//            return builder.ToString();
//        }
//
//        private void WriteTHL(StringBuilder builder)
//        {
//            foreach (IntDoublePair i in THL)
//            {
//                builder.AppendLine(i.Key + " " + i.Value);
//            }
//        }
//        private void WriteTHU(StringBuilder builder)
//        {
//            foreach (IntDoublePair i in THU)
//            {
//                builder.AppendLine(i.Key + " " + i.Value);
//            }
//        }
//        private void WriteUZR(StringBuilder builder)
//        {
//            foreach (IntDoublePair i in UZR)
//            {
//                builder.AppendLine(i.Key + " " + i.Value);
//            }
//        }
//
//
//        public AutoInputConstants()
//        {
//            System.Globalization.CultureInfo culture = System.Globalization.CultureInfo.CreateSpecificCulture("en");
//            culture.NumberFormat.NumberDecimalSeparator = ".";
//            Thread.CurrentThread.CurrentCulture = culture;
//            _ICP = new IntCollection();
//            _THL = new IntDoublePairCollection();
//            _THU = new IntDoublePairCollection();
//            _UZR = new IntDoublePairCollection();
//        }
//
//        private int _NDIM;
//        /// <summary>
//        /// dimension of the system of equations
//        /// </summary>
//        public int NDIM
//        {
//            get { return _NDIM; }
//            set { _NDIM = value; }
//        }
//
//        private int _IPS;
//        /// <summary>
//        /// 1 : stationary states 2 : periodic solutions 4 : BVP
//        /// </summary>
//        public int IPS
//        {
//            get { return _IPS; }
//            set { _IPS = value; }
//        }
//
//        private int _IRS;
//        /// <summary>
//        /// Restart label
//        /// </summary>
//        public int IRS
//        {
//            get { return _IRS; }
//            set { _IRS = value; }
//        }
//
//        private int _ILP;
//        /// <summary>
//        /// Locate limit points (folds)
//        /// </summary>
//        public int ILP
//        {
//            get { return _ILP; }
//            set { _ILP = value; }
//        }
//
//        private int _NICP;
//        /// <summary>
//        /// the number of free parameters
//        /// </summary>
//        public int NICP
//        {
//            get { return _NICP; }
//            set { _NICP = value; }
//        }
//
//        private IntCollection _ICP;
//        /// <summary>
//        /// the indices of the free parameters
//        /// </summary>
//        public IntCollection ICP
//        {
//            get { return _ICP; }
//            set { _ICP = value; }
//        }
//
//        private int _NTST;
//        /// <summary>
//        /// the number of mesh intervals
//        /// </summary>
//        public int NTST
//        {
//            get { return _NTST; }
//            set { _NTST = value; }
//        }
//
//        private int _NCOL;
//        /// <summary>
//        /// the number of collocation points per mesh interval
//        /// </summary>
//        public int NCOL
//        {
//            get { return _NCOL; }
//            set { _NCOL = value; }
//        }
//
//        private int _IAD;
//        /// <summary>
//        /// Mesh adaption:
//        /// <pre>
//        ///     0 :fixedmesh
//        ///   > 0 : adapt mesh every IAD continuation steps
//        /// </pre>
//        /// </summary>
//        public int IAD
//        {
//            get { return _IAD; }
//            set { _IAD = value; }
//        }
//
//        private int _ISP;
//        /// <summary>
//        /// Detection of branch points:
//        /// <pre>
//        ///   0 : don’t detect
//        ///   1 : detect for algebraic problems
//        ///   2 : detect for all problems
//        /// </pre>
//        /// </summary>
//        public int ISP
//        {
//            get { return _ISP; }
//            set { _ISP = value; }
//        }
//
//        private int _ISW;
//        /// <summary>
//        /// At a restart solution:
//        /// <pre>
//        ///   1 : just follow the branch
//        ///  -1 : switch branches (for BPs in BVPs)
//        ///   2 : two-parameter continuation (LPs, HBs, PDs, TRs)
//        /// </pre>
//        /// </summary>
//        public int ISW
//        {
//            get { return _ISW; }
//            set { _ISW = value; }
//        }
//
//        private int _IPLT;
//        /// <summary>
//        /// The ”principal solution measure”
//        /// (the second real column in the bifurcation diagram file):
//        /// <pre>
//        ///      0 : the L2 norm
//        ///   != 0 : other measures (see manual)
//        /// </pre>
//        /// </summary>
//        public int IPLT
//        {
//            get { return _IPLT; }
//            set { _IPLT = value; }
//        }
//
//        private int _NBC;
//        /// <summary>
//        /// the number of boundary conditions (for BVP)
//        /// </summary>
//        public int NBC
//        {
//            get { return _NBC; }
//            set { _NBC = value; }
//        }
//
//        private int _NINT;
//        /// <summary>
//        /// the number of integral constraints (for BVP)
//        /// </summary>
//        public int NINT
//        {
//            get { return _NINT; }
//            set { _NINT = value; }
//        }
//
//        private int _NMX;
//        /// <summary>
//        /// maximum number of continuation step along any branch
//        /// </summary>
//        public int NMX
//        {
//            get { return _NMX; }
//            set { _NMX = value; }
//        }
//
//        private double _RL0;
//        /// <summary>
//        /// bifurcation diagram lower limit for the “first” parameter
//        /// </summary>
//        public double RL0
//        {
//            get { return _RL0; }
//            set { _RL0 = value; }
//        }
//
//        private double _RL1;
//        /// <summary>
//        /// bifurcation diagram upper limit for the “first” parameter
//        /// </summary>
//        public double RL1
//        {
//            get { return _RL1; }
//            set { _RL1 = value; }
//        }
//
//        private double _A0;
//        /// <summary>
//        /// bifurcation diagram lower limit for the “principal solution measure”
//        /// </summary>
//        public double A0
//        {
//            get { return _A0; }
//            set { _A0 = value; }
//        }
//
//        private double _A1;
//        /// <summary>
//        /// bifurcation diagram upper limit for the “principal solution measure”
//        /// </summary>
//        public double A1
//        {
//            get { return _A1; }
//            set { _A1 = value; }
//        }
//
//        private int _NPR;
//        /// <summary>
//        /// Save the solution in the solution file every NPR continuation steps
//        /// </summary>
//        public int NPR
//        {
//            get { return _NPR; }
//            set { _NPR = value; }
//        }
//
//        private int _MXBF;
//        /// <summary>
//        /// For algebraic problems: Maximum number of branch switches (if negative only one “leg” will be computed)
//        /// </summary>
//        public int MXBF
//        {
//            get { return _MXBF; }
//            set { _MXBF = value; }
//        }
//
//        private int _IID;
//        /// <summary>
//        /// Controls the diagnostic file output (normal value is 2; see manual)
//        /// </summary>
//        public int IID
//        {
//            get { return _IID; }
//            set { _IID = value; }
//        }
//
//        private int _ITMX;
//        /// <summary>
//        /// maximum number of iterations for detecting “special” solutions
//        /// </summary>
//        public int ITMX
//        {
//            get { return _ITMX; }
//            set { _ITMX = value; }
//        }
//
//        private int _ITNW;
//        /// <summary>
//        /// maximum number of Newton+Chord iterations
//        /// </summary>
//        public int ITNW
//        {
//            get { return _ITNW; }
//            set { _ITNW = value; }
//        }
//
//        private int _NWTN;
//        /// <summary>
//        /// maximum number of Newton iterations
//        /// </summary>
//        public int NWTN
//        {
//            get { return _NWTN; }
//            set { _NWTN = value; }
//        }
//
//        private int _JAC;
//        /// <summary>
//        /// Jacobian supplied ?
//        /// </summary>
//        public int JAC
//        {
//            get { return _JAC; }
//            set { _JAC = value; }
//        }
//
//        private double _EPSL;
//        /// <summary>
//        /// Newton/Chord convergence tolerance for free parameters
//        /// </summary>
//        public double EPSL
//        {
//            get { return _EPSL; }
//            set { _EPSL = value; }
//        }
//
//        private double _EPSU;
//        /// <summary>
//        /// Newton/Chord convergence tolerance for solutions
//        /// </summary>
//        public double EPSU
//        {
//            get { return _EPSU; }
//            set { _EPSU = value; }
//        }
//
//        private double _EPSS;
//        /// <summary>
//        /// Continuation step size tolerance when locating special solutions
//        /// </summary>
//        public double EPSS
//        {
//            get { return _EPSS; }
//            set { _EPSS = value; }
//        }
//
//        private double _DS;
//        /// <summary>
//        /// Nominal continuation step size
//        /// </summary>
//        public double DS
//        {
//            get { return _DS; }
//            set { _DS = value; }
//        }
//
//        private double _DSMIN;
//        /// <summary>
//        /// Minimum continuation step size
//        /// </summary>
//        public double DSMIN
//        {
//            get { return _DSMIN; }
//            set { _DSMIN = value; }
//        }
//
//        private double _DSMAX;
//        /// <summary>
//        /// Maximum continuation step size
//        /// </summary>
//        public double DSMAX
//        {
//            get { return _DSMAX; }
//            set { _DSMAX = value; }
//        }
//
//        private int _IADS;
//        /// <summary>
//        /// Adapt the continuation step size every IADS steps
//        /// </summary>
//        public int IADS
//        {
//            get { return _IADS; }
//            set { _IADS = value; }
//        }
//
//        private int _NTHL;
//        /// <summary>
//        /// the number of modified parameter “weights” (for BVP)
//        /// </summary>
//        public int NTHL
//        {
//            get { return _NTHL; }
//            set { _NTHL = value; }
//        }
//
//        private IntDoublePairCollection _THL;
//        /// <summary>
//        /// parameter index, parameter weight (e.g., ICP(11)=0 means PAR(11) is excluded from the step size)
//        /// </summary>
//        public IntDoublePairCollection THL
//        {
//            get { return _THL; }
//            set { _THL = value; }
//        }
//
//        private int _NTHU;
//        /// <summary>
//        /// the number of modified solution component “weights” (for BVP)
//        /// </summary>
//        public int NTHU
//        {
//            get { return _NTHU; }
//            set { _NTHU = value; }
//        }
//
//        private IntDoublePairCollection _THU;
//        /// <summary>
//        /// component index, component weight
//        /// </summary>
//        public IntDoublePairCollection THU
//        {
//            get { return _THU; }
//            set { _THU = value; }
//        }
//
//        private int _NUZR;
//        /// <summary>
//        /// the number of “user output points” specified
//        /// </summary>
//        public int NUZR
//        {
//            get { return _NUZR; }
//            set { _NUZR = value; }
//        }
//
//        private IntDoublePairCollection _UZR;
//        /// <summary>
//        /// parameter index, parameter value (if I is negative the continuation stops at the parameter value)
//        /// </summary>
//        public IntDoublePairCollection UZR
//        {
//            get { return _UZR; }
//            set { _UZR = value; }
//        }
//
//
//        public void InitializeFromContent(string sContent)
//        {
//            using (MemoryStream stream = new MemoryStream())
//            {
//                StreamWriter writer = new StreamWriter(stream);
//                writer.WriteLine(sContent);
//                writer.Flush();
//                stream.Seek(0, SeekOrigin.Begin);
//                InitializeFromStream(stream);
//            }
//        }
//
//        private void InitializeFromStream(Stream stream)
//        {
//            StreamReader reader = new StreamReader(stream);
//
//            InitializeFromFirstLine(reader.ReadLine());
//            InitializeFromSecondLine(reader.ReadLine());
//            InitializeFromThirdLine(reader.ReadLine());
//            InitializeFromFourthLine(reader.ReadLine());
//            InitializeFromFifthLine(reader.ReadLine());
//            InitializeFromSixthLine(reader.ReadLine());
//            InitializeFromSeventhLine(reader.ReadLine());
//
//
//            InitializeFromEighthLine(reader.ReadLine(), reader);
//            InitializeFromNinethLine(reader.ReadLine(), reader);
//            InitializeFromTenthLine(reader.ReadLine(), reader);
//
//
//            reader.Close();
//        }
//
//        private void InitializeFromTenthLine(string line, StreamReader reader)
//        {
//            string[] values = line.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
//            NUZR = UtilLib.ConvertToInt(values[0], 0);
//            UZR = new IntDoublePairCollection();
//            for (int i = 0; i < NUZR; i++)
//            {
//                string newLine = reader.ReadLine();
//                string[] newValues = newLine.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
//                UZR.Add(new IntDoublePair(UtilLib.ConvertToInt(newValues[0]), UtilLib.ConvertToDouble(newValues[1])));
//            }
//        }
//
//        private void InitializeFromNinethLine(string line, StreamReader reader)
//        {
//            string[] values = line.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
//            NTHU = UtilLib.ConvertToInt(values[0], 0);
//            THU = new IntDoublePairCollection();
//            for (int i = 0; i < NTHU; i++)
//            {
//                string newLine = reader.ReadLine();
//                string[] newValues = newLine.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
//                THU.Add(new IntDoublePair(UtilLib.ConvertToInt(newValues[0]), UtilLib.ConvertToDouble(newValues[1])));
//            }
//        }
//
//
//        private void InitializeFromEighthLine(string line, StreamReader reader)
//        {
//            string[] values = line.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
//            NTHL = UtilLib.ConvertToInt(values[0], 0);
//            THL = new IntDoublePairCollection();
//            for (int i = 0; i < NTHL; i++)
//            {
//                string newLine = reader.ReadLine();
//                string[] newValues = newLine.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
//                THL.Add(new IntDoublePair(UtilLib.ConvertToInt(newValues[0]), UtilLib.ConvertToDouble(newValues[1])));
//            }
//        }
//
//        private void InitializeFromSeventhLine(string line)
//        {
//            string[] values = line.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
//            DS = UtilLib.ConvertToDouble(values[0], DS);
//            DSMIN = UtilLib.ConvertToDouble(values[1], DSMIN);
//            DSMAX = UtilLib.ConvertToDouble(values[2], DSMAX);
//            IADS = UtilLib.ConvertToInt(values[3], IADS);
//        }
//
//        private void InitializeFromSixthLine(string line)
//        {
//            string[] values = line.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
//            EPSL = UtilLib.ConvertToDouble(values[0], EPSL);
//            EPSU = UtilLib.ConvertToDouble(values[1], EPSU);
//            EPSS = UtilLib.ConvertToDouble(values[2], EPSS);
//        }
//
//        private void InitializeFromFifthLine(string line)
//        {
//            string[] values = line.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
//            NPR = UtilLib.ConvertToInt(values[0], NPR);
//            MXBF = UtilLib.ConvertToInt(values[1], MXBF);
//            IID = UtilLib.ConvertToInt(values[2], IID);
//            ITMX = UtilLib.ConvertToInt(values[3], ITMX);
//            ITNW = UtilLib.ConvertToInt(values[4], ITNW);
//            NWTN = UtilLib.ConvertToInt(values[5], NWTN);
//            JAC = UtilLib.ConvertToInt(values[6], JAC);
//        }
//
//        private void InitializeFromFourthLine(string line)
//        {
//            string[] values = line.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
//            NMX = UtilLib.ConvertToInt(values[0], NMX);
//            RL0 = UtilLib.ConvertToDouble(values[1], RL0);
//            RL1 = UtilLib.ConvertToDouble(values[2], RL1);
//            A0 = UtilLib.ConvertToDouble(values[3], A0);
//            A1 = UtilLib.ConvertToDouble(values[4], A1);
//        }
//        private void InitializeFromThirdLine(string line)
//        {
//            string[] values = line.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
//            NTST = UtilLib.ConvertToInt(values[0], NTST);
//            NCOL = UtilLib.ConvertToInt(values[1], NCOL);
//            IAD = UtilLib.ConvertToInt(values[2], IAD);
//            ISP = UtilLib.ConvertToInt(values[3], ISP);
//            ISW = UtilLib.ConvertToInt(values[4], ISW);
//            IPLT = UtilLib.ConvertToInt(values[5], IPLT);
//            NBC = UtilLib.ConvertToInt(values[6], NBC);
//            NINT = UtilLib.ConvertToInt(values[7], NINT);
//
//        }
//        private void InitializeFromSecondLine(string line)
//        {
//            string[] values = line.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
//            NICP = UtilLib.ConvertToInt(values[0], 0);
//            ICP = new IntCollection();
//            for (int i = 0; i < NICP; i++)
//            {
//                ICP.Add(UtilLib.ConvertToInt(values[1 + i], 11));
//            }
//        }
//
//        private void InitializeFromFirstLine(string line)
//        {
//            string[] values = line.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
//            NDIM = UtilLib.ConvertToInt(values[0], NDIM);
//            IPS = UtilLib.ConvertToInt(values[1], IPS);
//            IRS = UtilLib.ConvertToInt(values[2], IRS);
//            ILP = UtilLib.ConvertToInt(values[3], ILP);
//        }
//
//    }
//
//}

