#pragma hdrstop
#include <sstream>
#include "psArrayedParameter.h"

using namespace std;
ostream& operator << (ostream& st, ArrayedParameter& pm)
{
    st<<"Name="<<pm.mLabel<<"\n";
    st<<"InitialValue="<<pm.mInitialValue<<"\n";
    st<<"Increment="<<pm.mIncrement<<"\n";
    st<<"NumberOfIncrements="<<pm.mNumberOfIncrements<<"\n";
    return st;
}

string  ArrayedParameter::asString() const
{
    stringstream ss;
    ss << (this);
    return ss.str();
}
