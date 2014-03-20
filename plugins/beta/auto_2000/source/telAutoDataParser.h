#ifndef telAutoDataParserH
#define telAutoDataParserH
#include <vector>
#include "telTelluriumData.h"
#include "telStringList.h"
#include "telConstants.h"
#include "telAutoConstants.h"
//---------------------------------------------------------------------------

using tlp::StringList;
class AutoDataParser
{
    public:
                                                AutoDataParser(const string& input = tlp::gEmptyString);
                                               ~AutoDataParser();
        //Data input
        bool                                    setInputData(const string& data);
        int                                     getNumberOfDataPoints();
        int                                     getNumberOfBifurcationPoints();
        string                                  getBiFurcationDiagram();
        StringList                              getDataFileHeader();
        StringList                              getRawSolutionData();
        StringList                              getBiFurcationPoints();
        tlp::TelluriumData                      getSolutionData();
        bool                                    parse(const string& input = tlp::gEmptyString);
        telauto::ScanDirection                  getScanDirection();

    protected:
        string                                  mBiFurcationDiagram;
        tlp::StringList                         mDataHeader;
        tlp::StringList                         mSolutionSummary;
        tlp::StringList                         mBiFurcationPoints;
        tlp::StringList                         mRawSolutionData;
        tlp::TelluriumData                      mSolutionData;
        void                                    resetOutput();
        int                                     getNrOfSolutions();
        string                                  getDataHeaderLine();

};

namespace tlp
{
//template<>
//inline std::string Property< rrauto::ScanDirection >::getType() const
//{
//    return "ScanDirection";
//}
//
//template<>
//inline string Property< rrauto::ScanDirection >::getValueAsString() const
//{
//    return mValue == rrauto::sdPositive ? "Positive" : "Negative";
//}
//
//template<>
//inline void Property< rrauto::ScanDirection >::setValueFromString(const string& val)
//{
//    mValue = compareNoCase(val, "Positive") == 0 ? rrauto::sdPositive : rrauto::sdNegative;
//}
//
//template<>
//inline void Property< rrauto::ScanDirection >::setValue(const rrauto::ScanDirection& val)
//{
//    mValue = (val);
//}
}



#endif
