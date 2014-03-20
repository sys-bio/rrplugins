#ifndef telAutoUtilsH
#define telAutoUtilsH
#include <vector>
#include "telStringList.h"
#include "rr/rrRoadRunner.h"
//---------------------------------------------------------------------------

namespace telauto
{

using std::vector;
/**
    \brief Takes a vector of SelectionRecords and returns their representation as
    a StringList
*/
tlp::StringList     getRecordsAsStrings(const vector< rr::SelectionRecord >& folder);

}
#endif
