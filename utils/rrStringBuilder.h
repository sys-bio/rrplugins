#ifndef rrStringBuilderH
#define rrStringBuilderH
#include <sstream>
#include <string>
#include "rrConstants.h"
#include "rrExporter.h"

using std::stringstream;
using std::string;

namespace rr
{
using rr::gEmptyString;

/**
 * @internal
 * @deprecated
 */
class RR_DECLSPEC StringBuilder
{
    protected:
        stringstream                 mStringing;

    public:
                                    StringBuilder(const string& aStr = gEmptyString);
        stringstream&               operator<<(const string& str);
        stringstream&               operator<<(const char& ch);
        stringstream&               operator<<(const int& ch);
        string                      ToString();

        void                        NewLine(const string& line = gEmptyString);
        void                        AppendLine(const string& line = gEmptyString);
        void                        Line(const string& line);
        void                        TLine(const string& line, const int& tabs = 1);
        void                        Clear();
};

}

#endif
