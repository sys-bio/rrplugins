#pragma hdrstop
#include "telPluginUtils.h"
#include "../utils/telStringList.h"
//---------------------------------------------------------------------------
namespace tlp
{
using namespace std;


tlp::StringList getRecordsAsStrings(const vector<rr::SelectionRecord>& _sels)
{
    tlp::StringList sels;
    for(int i = 0; i < _sels.size(); i++)
    {
        sels.add(_sels[i].to_string());
    }
    return sels;
}

}
