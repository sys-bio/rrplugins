#ifndef telAutoDataParserH
#define telAutoDataParserH
#include <vector>
#include "telTelluriumData.h"
#include "telStringList.h"
#include "telConstants.h"
#include "telAutoConstants.h"
//---------------------------------------------------------------------------

using tlp::StringList;
using std::vector;

class AutoDataParser
{
    public:
                                                AutoDataParser(const string& input = tlp::gEmptyString);
                                               ~AutoDataParser();
        //Data input
        bool                                    parse(const string& input = tlp::gEmptyString);
        int                                     getNumberOfDataPoints();
        int                                     getNumberOfBifurcationPoints();
        string                                  getBiFurcationDiagram();
        StringList                              getDataFileHeader();
        StringList                              getRawSolutionData();
        vector<int>                             getBiFurcationPoints();
        StringList                              getBiFurcationLabels();
        tlp::TelluriumData                      getSolutionData();

        telauto::ScanDirection                  getScanDirection();

    protected:
        string                                  mBiFurcationDiagram;
        tlp::StringList                         mDataHeader;
        tlp::StringList                         mRawSolutionData;
        tlp::TelluriumData                      mSolutionData;
        vector<int>                             mBiFurcationPoints;
        vector<string>                          mBiFurcationLabels;
        void                                    resetOutput();
        int                                     getNrOfSolutions();
        string                                  getDataHeaderLine();

};

#endif
