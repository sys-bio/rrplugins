#pragma hdrstop
#include "rrStringList.h"
#include "c/rrStringBuilder.h"
#include "rrStringUtils.h"
#include "rrAutoInputConstants.h"
#include "rrPluginUtils.h"
//---------------------------------------------------------------------------
namespace rrauto
{
    using namespace rrp;
    using namespace rr;
    using namespace std;

string getWhiteSpaces(string& line, int maxLength);
InputConstants::InputConstants()
:
A0(0),
A1(10000),
DS(0.001),
DSMAX(0.1),
DSMIN(1e-5),
EPSL(1e-8),
EPSS(1e-6),
EPSU(1e-8),
IAD(3),
IADS(1),
ICP(0),
IID(0),
ILP(1),
IPLT(0),
IPS(1),
IRS(0),
ISP(1),
ISW(1),
ITMX(8),
ITNW(5),
JAC(0),
MXBF(-1),
NBC(0 ),
NCOL(3),
NDIM(1),
NICP(1),
NINT(0),
NMX(1000),
NPR(50),
NTHL(0),
NTHU(0),
NTST(15),
NUZR(0),
NWTN(3),
RL0(0.01, "RL0", "Start value for primary continuation parameter"),   //Parameter startValue
RL1(30),     //Parameter endValue
THL(NTHL),
THU(NTHU),
UZR(NUZR)
{
    mInputConstants.add(&RL0);
}

string InputConstants::getConstantsAsString()
{
    return ToInputString();
}

string InputConstants::GetICP()
{
    StringBuilder builder;
    builder << (NICP);

    for(int i = 0; i < ICP.size(); i++)
    {
        builder<<(" " + i);
    }

    if (ICP.size() == 0)
    {
        builder<<(" 0");
    }

    return builder.ToString();
}

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

string InputConstants::ToInputString()
{
    string line1  = formatN("{0} {1} {2} {3}", NDIM, IPS, IRS, ILP);
    string line2  = GetICP();
    string line3  = formatN("{0} {1} {2} {3} {4} {5} {6} {7}", NTST, NCOL, IAD, ISP, ISW, IPLT, NBC, NINT);
    string line4  = formatN("{0} {1} {2} {3} {4}", NMX, RL0.getValue(), RL1.getValue(), A0, A1);
    string line5  = formatN("{0} {1} {2} {3} {4} {5} {6}", NPR, MXBF, IID, ITMX, ITNW, NWTN, JAC);
    string line6  = formatN("{0} {1} {2}", EPSL, EPSU, EPSS);
    string line7  = formatN("{0} {1} {2} {3}", DS, DSMIN, DSMAX, IADS);
    string line8  = formatN("{0}", NTHL);
    string line9  = formatN("{0}", NTHU);
    string line10 = formatN("{0}", NUZR);

    StringList lines;
    lines.add(line1);
    lines.add(line2);
    lines.add(line3);
    lines.add(line4);
    lines.add(line5);
    lines.add(line6);
    lines.add(line7);
    lines.add(line8);
    lines.add(line8);
    lines.add(line10);

    int maxLength = lines.getLongest().size();
    StringBuilder builder;
    builder << (line1 + getWhiteSpaces(line1, maxLength) + " NDIM, IPS, IRS, ILP") << endl;
    builder << (line2 + getWhiteSpaces(line2, maxLength) + " NICP,(ICP(I),I=1 NICP)")<< endl;
    builder << line3 << getWhiteSpaces(line3, maxLength);
    builder << " NTST,NCOL,IAD,ISP,ISW,IPLT,NBC,NINT"<< endl;
    builder << (line4 + getWhiteSpaces(line4, maxLength) + " NMX,RL0,RL1,A0,A1")<< endl;
    builder << (line5 + getWhiteSpaces(line5, maxLength) + " NPR,MXBF,IID,ITMX,ITNW,NWTN,JAC")<< endl;
    builder << (line6 + getWhiteSpaces(line6, maxLength) + " EPSL,EPSU,EPSS")<< endl;
    builder << (line7 + getWhiteSpaces(line7, maxLength) + " DS,DSMIN,DSMAX,IADS")<< endl;
    builder << (line8 + getWhiteSpaces(line8, maxLength) + " NTHL,((I,THL(I)),I=1,NTHL)")<< endl;
//    WriteTHL(builder);

    builder << (line9 + getWhiteSpaces(line9, maxLength) + " NTHU,((I,THU(I)),I=1,NTHU)") << endl;
//    WriteTHU(builder);

    builder << (line10 + getWhiteSpaces(line10, maxLength) + " NUZR,((I,PAR(I)),I=1,NUZR)") << endl;
//    WriteUZR(builder);

    builder << "\n";
    builder << "\n";

    string aStr = builder.ToString();
    return aStr;
}

string getWhiteSpaces(string& line, int maxLength)
{
    int nrSpaces =  maxLength - line.size();
    return string(nrSpaces, ' ');
}

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
}
