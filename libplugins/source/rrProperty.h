/**
 * @file rrProperty.h
 * @brief Property implementation
 * @author Totte Karlsson & Herbert M Sauro
 *
 * <--------------------------------------------------------------
 * This file is part of cRoadRunner.
 * See http://code.google.com/p/roadrunnerlib for more details.
 *
 * Copyright (C) 2012-2013
 *   University of Washington, Seattle, WA, USA
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * In plain english this means:
 *
 * You CAN freely download and use this software, in whole or in part, for personal,
 * company internal, or commercial purposes;
 *
 * You CAN use the software in packages or distributions that you create.
 *
 * You SHOULD include a copy of the license in any redistribution you may make;
 *
 * You are NOT required include the source of software, or of any modifications you may
 * have made to it, in any redistribution you may assemble that includes it.
 *
 * YOU CANNOT:
 *
 * redistribute any piece of this software without proper attribution;
*/
#ifndef rrPropertyH
#define rrPropertyH
#include <vector>
#include <string>
#include <sstream>
#include "rrException.h"
#include "rrLogger.h"
#include "rrUtils.h"
#include "rrStringList.h"
#include "rrConstants.h"
#include "rrPropertyBase.h"
#include "rrStringUtils.h"
#include "rrRoadRunnerData.h"
#include "rrProperties.h"
#include "../wrappers/C/rrc_types.h"
//---------------------------------------------------------------------------
namespace rrp
{

    using rr::RoadRunnerData;
    using rr::gNoneString;
    using std::string;
/**
    Template function that returns the name of a particular type, e.g. a value of type int, returns a string "int".
    Each type need to be specialized.
*/
template <class T>
string getPropertyType(const T& val);

/**
    \brief Template class implementing a PluginProperty. 

    The characteristics of a Plugin Property is its type and its value. Various functions assist in setting/getting
    the properties value. Its base class, PropertyBase, encapsulate the properties name, hint and description.

    Of importance is the ability to get a pointer to its internal value, e.g. \a getValuePointer(), or \a getValueHandle(), as it can be used as a
    handle in the derived Plugins C API.
*/
template<class T>
class Property : public PropertyBase
{
    protected:
                                        /** 
                                            \brief The value of the property. 
                                        */
        T                               mValue;

    public:
                                        /**
                                            Property constructor. Creates a property, assigning a value, name and optionally a hint.
                                        */
                                        Property(   const T& value = T(),                const string& name = gNoneString,
                                                    const string& hint = gNoneString,    const string& descr = gNoneString,
                                                    const string& alias = gEmptyString,   bool readonly = false);

                                        /**
                                            Property copy constructor. Creates a property, from another property.
                                        */
                                        Property(const Property<T>& para);

                                        /**
                                            Property destructor. Deallocate any memory allocated by the property.
                                        */
                                       ~Property();
                                        
                                        /**
                                            Property assignment operator. Deep copy of the property on the right side of the assignment.
                                        */
        Property<T>&                    operator=(const Property<T>& rhs);

                                        /**
                                            Set a property value from another properties (as pointer) value.
                                        */
        void                            setValue(T* val);

                                        /**
                                            Set a property value from another properties (as reference) value.
                                        */
        void                            setValue(const T& val);

                                        /**
                                            Set a property value from a string.
                                        */
        void                            setValueFromString(const string& val);

                                        /**
                                            Return the value of a property.
                                        */
        T                               getValue() const;
                                        
                                        /**
                                            Get a reference to a properties value.
                                        */
        T&                              getValueReference();

                                        /**
                                            Get a pointer to a properties value.
                                        */
        T*                              getValuePointer();

                                        /**
                                            Get a handle (void*) to a properties value.
                                        */
        void*                           getValueHandle();

                                        /**
                                            Get a string representation of a properties value.
                                        */
        string                          getValueAsString() const;
};

template<class T>
Property<T>::Property(
    const T& value,         const string& name,
    const string& hint,     const string& descr,
    const string& alias,    bool readonly
)
:
PropertyBase(getPropertyType(value), name, hint, descr, alias, readonly),
mValue(value)
{}

template<class T>
Property<T>::Property(const Property<T>& para)
:
PropertyBase(para)
{
    mValue = para.mValue;
}

template<class T>
Property<T>::~Property()
{}

template<class T>
Property<T>& Property<T>::operator=(const Property<T>& rhs)
{
    PropertyBase::operator= (rhs);
    mValue = rhs.mValue;
    return (*this);
}

/**
    Set a property value
*/
template<class T>
void Property<T>::setValue(const T& val)
{
    mValue = val;
}

template<class T>
T Property<T>::getValue() const
{
    return mValue;
}

template<class T>
string Property<T>::getValueAsString() const
{
    return rr::toString(mValue);
}

template<class T>
T* Property<T>::getValuePointer()
{
    return &(mValue);
}

template<class T>
T& Property<T>::getValueReference()
{
    return mValue;
}

template<class T>
void* Property<T>::getValueHandle()
{
    return (void*) &mValue;
}

//================= SPECIALIZATIONS ====================

//================= BOOL ===============================
/**
    Set a bool properties value, from a string.
*/
template<>
inline void Property<bool>::setValueFromString(const string& val)
{
    mValue = rr::toBool(val);
}

//================= Int ===============================
/**
    Set an int properties value, from a string.
*/
template<>
inline void Property<int>::setValueFromString(const string& val)
{
    mValue = rr::toInt(val);
}

//================= Double ===============================
/**
    Set a double properties value, from a string.
*/
template<>
inline void Property<double>::setValueFromString(const string& val)
{
    mValue = rr::toDouble(val);
}

template<>
inline string Property<double>::getValueAsString() const
{
    return rr::toString(mValue, "%G");
}

//================= std::string ===============================
/**
    Set a string properties value, from a string.
*/
template<>
inline void Property<string>::setValueFromString(const string& str)
{
    mValue = str;
}

//================= vector<string> ===============================
/**
    Set a vector<string> properties value, from a string. This function expects input string
    containing comma delimited values.
*/
template<>
inline void Property< std::vector<string> >::setValueFromString(const string& val)
{
    mValue = rr::splitString(val,", ");
}

//================= rr::StringList ===============================
template<>
inline string Property<rr::StringList>::getValueAsString() const
{
    return mValue.AsString();
}

/**
    Set a StringList properties value, from a string. This function expects input string
    containing comma delimited values.
*/
template<>
inline void Property< rr::StringList >::setValueFromString(const string& val)
{
    mValue = rr::splitString(val,", ");
}

//============= RoadRunner data ===========================
template<>
inline string Property<rr::RoadRunnerData>::getValueAsString() const
{
    std::stringstream rrData;
    rrData << (mValue);
    return rrData.str();
}

/**
    Set a RoadRunner data properties value, from a string.
    \note This is not implemented.
*/
template<>
inline void Property<rr::RoadRunnerData>::setValueFromString(const string& val)
{
}

/**
    Set a property value
*/
template<>
inline void Property<rr::RoadRunnerData>::setValue(const rr::RoadRunnerData& val)
{
    mValue = val;
}

/**
    Set a property value
*/
template<>
inline void Property<rr::RoadRunnerData>::setValue(rr::RoadRunnerData* val)
{
    mValue = (*val);
}

//============ RRStringArray
/**
    Returns a RRStringArrays value as a string.
    \note This is not implemented.
*/
template<>
inline string Property<rrc::RRStringArray>::getValueAsString() const
{
    return string("");
}

/**
    Set the value of a RRStringArray, from a string. This function expects input string
    containing comma delimited values.
*/
template<>
inline void Property<rrc::RRStringArray>::setValueFromString(const string& val)
{
    //Todo.. clear current list first..
    rr::StringList list = rr::splitString(val, ",");
    mValue.Count = list.size();
    for(int i = 0; i < mValue.Count; i++)
    {
        mValue.String[i] = rr::createText(list[i]);
    }
}

//========== Properties container
/**
    Returns a Properties value as a string.
*/
template<>
inline string Property<Properties>::getValueAsString() const
{
    rr::StringList list = mValue.getNames();
    return list.AsString();
}

/**
    Set a property value
*/
template<>
inline void Property<Properties>::setValue(Properties* val)
{
    mValue = (*val);
}

/**
    Set a property value
*/
template<>
inline void Property<Properties>::setValue(const Properties& val)
{
    mValue = val;
}

/**
    Set the value of a Properties container value, from a string.
    \note This is not implemented.
*/
template<>
inline void Property<Properties>::setValueFromString(const string& val)
{
    Log(rr::lError)<<"Trying to set Properties container by a string. This is not implemented!";
}

//===================== Function templates used to retrieve a property's type ===================
/**
    \brief Returns the type as a string.
*/
template<>
inline string getPropertyType(const int& a)
{
    return "int";
}

/**
    \brief Returns the type as a string.
*/
template<>
inline string getPropertyType(const bool& a)
{
    return "bool";
}

/**
    \brief Returns the type as a string.
*/
template<>
inline string getPropertyType(const double& a)
{
    return "double";
}

/**
    \brief Returns the type as a string.
*/
template<>
inline string getPropertyType<string>(const string& a)
{
    return "std::string";
}

/**
    \brief Returns the type as a string.
*/
template<>
inline string getPropertyType< vector<string> >(const vector<string> &a)
{
    return "vector<string>";
}

/**
    \brief Returns the type as a string.
*/
template<>
inline string getPropertyType<rr::StringList>(const rr::StringList& a)
{
    return "StringList";
}

/**
    \brief Returns the type as a string.
*/
template<>
inline string getPropertyType<RoadRunnerData>(const RoadRunnerData& a)
{
    return "roadRunnerData";
}

/**
    \brief Returns the type as a string.
*/
template<>
inline string getPropertyType(const Properties& value)
{
    return "listOfProperties";
}

}

#endif
