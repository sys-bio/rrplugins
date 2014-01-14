#pragma hdrstop
#include "rrPluginUtils.h"
#include "rrStringList.h"
//---------------------------------------------------------------------------
namespace rrp
{
using namespace std;


rr::StringList getRecordsAsStrings(const vector<rr::SelectionRecord>& _sels)
{
    rr::StringList sels;
    for(int i = 0; i < _sels.size(); i++)
    {
        sels.add(_sels[i].to_string());
    }
    return sels;
}

}
