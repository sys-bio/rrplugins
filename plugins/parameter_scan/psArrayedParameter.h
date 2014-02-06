#ifndef psArrayedParameterH
#define psArrayedParameterH
#include <ostream>
#include <string>
#include "telProperty.h"
//---------------------------------------------------------------------------
using std::string;
using std::ostream;

class ArrayedParameter
{

    public:
        /**
            Output an arrayed parameter as a string to an ostream
        */
        friend ostream&                 operator<<(ostream& os, ArrayedParameter& pm);

        string                          mLabel;
        double                          mCurrentValue;
        double                          mInitialValue;
        double                          mIncrement;
        int                             mNumberOfIncrements;
        string                          asString() const;
};

template<>
inline string tlp::Property< ArrayedParameter >::getValueAsString() const
{
    return mValue.asString();
}

template<>
inline void tlp::Property< ArrayedParameter>::setValueFromString(const string& val)
{
    //mValue = tlp::toBool(val);
}

template<>
inline string tlp::getPropertyType< ArrayedParameter >(const ArrayedParameter& value)
{
    return "arrayedParameter";
}


///**
//    \brief Returns the type as a string.
//*/
//template<>
//inline string getPropertyType< ArrayedParameter >(const ArrayedParameter& value)
//{
//    return "arrayedParameter";
//}
//

#endif
