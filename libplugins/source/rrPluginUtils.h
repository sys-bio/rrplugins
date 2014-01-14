/**
 * @file rrPluginUtils.h
 * @brief Utility functions for the plugin framework
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
 * <hr>
*/
#ifndef rrPluginUtilsH
#define rrPluginUtilsH
#include <vector>
#include <string>
#include <sstream>
#include "rrpExporter.h"
#include "rrStringList.h"
#include "rrSelectionRecord.h"
#include "rrUtils.h"
//---------------------------------------------------------------------------

namespace rrp
{

using std::vector;
using std::string;

/**
    \brief Takes a vector of SelectionRecords and returns their representation as
    a StringList
*/
RRP_DECLSPEC rr::StringList      getRecordsAsStrings(const vector<rr::SelectionRecord>& recs);


/**
    \brief Template format function. A "{0}" occurence in the src string is substituted with the 
    value in arg1. The new string with the substition is returned.
*/
template <class T>
string formatN(const string& src, const T& arg1)
{
    string newString(src);
    string tok1("{0}");
    newString = substituteN(newString, tok1, arg1);
    return newString;
}

/**
    \brief Template format function. A "{i}" occurence in the src string, where i = 0 or 1, is substituted with the 
    values in arg1 and arg2, respectively. The new string with the substitions is returned.
*/
template <class A, class B>
string formatN(const string& src, const A& arg1, const B& arg2)
{
    string newString(src);
    string tok1("{0}"), tok2("{1}");

    newString = substituteN(newString, tok1, arg1);
    newString = substituteN(newString, tok2, arg2);
    return newString;
}

/**
    \brief Template format function. A "{i}" occurence in the src string, where i = 0, 1 or 2, is substituted with the 
    values in arg1, arg2 and arg3, respectively. The new string with the substitions is returned.
*/
template <class A, class B, class C>
string formatN(const string& src, const A& arg1, const B& arg2, const C& arg3)
{
    string newString(src);
    string tok1("{0}"), tok2("{1}"), tok3("{2}");

    newString = substituteN(newString, tok1, arg1, -1);
    newString = substituteN(newString, tok2, arg2, -1);
    newString = substituteN(newString, tok3, arg3, -1);
    return newString;
}

/**
    \brief Template format function. A "{i}" occurence in the src string, where i = 0, 1, 2 or 3, is substituted with the 
    values in arg1.. trough arg4, respectively. The new string with the substitions is returned.
*/
template <class A, class B, class C, class D>
string formatN(const string& src, const A& arg1, const B& arg2, const C& arg3, const D& arg4)
{
    string newString(src);
    string  tok1("{0}"), tok2("{1}"), tok3("{2}"),
            tok4("{3}");

    newString = substituteN(newString, tok1, arg1, -1);
    newString = substituteN(newString, tok2, arg2, -1);
    newString = substituteN(newString, tok3, arg3, -1);
    newString = substituteN(newString, tok4, arg4, -1);
    return newString;
}

/**
    \brief Template format function. A "{i}" occurence in the src string, where i = 0, 1, ..., 4, is substituted with the 
    values in arg1.. trough arg5, respectively. The new string with the substitions is returned.
*/
template <class A, class B, class C, class D, class E>
string formatN(const string& src, const A& arg1, const B& arg2, const C& arg3, const D& arg4, const E& arg5)
{
    string newString(src);
    string  tok1("{0}"), tok2("{1}"), tok3("{2}"),
            tok4("{3}"), tok5("{4}");

    newString = substituteN(newString, tok1, arg1);
    newString = substituteN(newString, tok2, arg2, -1);
    newString = substituteN(newString, tok3, arg3, -1);
    newString = substituteN(newString, tok4, arg4, -1);
    newString = substituteN(newString, tok5, arg5, -1);
    return newString;
}

/**
    \brief Template format function. A "{i}" occurence in the src string, where i = 0, 1, ..., 5, is substituted with the 
    values in arg1 trough arg5, respectively. The new string with the substitions is returned.
*/
template <class A, class B, class C, class D, class E, class F>
string formatN(const string& src, const A& arg1, const B& arg2, const C& arg3, const D& arg4, const E& arg5, const F& arg6)
{
    string newString(src);
    string  tok1("{0}"), tok2("{1}"), tok3("{2}"),
            tok4("{3}"), tok5("{4}"), tok6("{5}");

    newString = substituteN(newString, tok1, arg1, -1);
    newString = substituteN(newString, tok2, arg2, -1);
    newString = substituteN(newString, tok3, arg3, -1);
    newString = substituteN(newString, tok4, arg4, -1);
    newString = substituteN(newString, tok5, arg5, -1);
    newString = substituteN(newString, tok6, arg6, -1);

    return newString;
}

/**
    \brief Template format function. A "{i}" occurence in the src string, where i = 0, 1, ..., 6, is substituted with the 
    values in arg1 trough arg7, respectively. The new string with the substitions is returned.
*/
template <class A, class B, class C, class D, class E, class F, class G>
string formatN(const string& src, const A& arg1, const B& arg2, const C& arg3, const D& arg4, const E& arg5, const F& arg6, const G& arg7)
{
    string newString(src);
    string  tok1("{0}"), tok2("{1}"), tok3("{2}"),
            tok4("{3}"), tok5("{4}"), tok6("{5}"),
            tok7("{6}");

    newString = substituteN(newString, tok1, arg1, -1);
    newString = substituteN(newString, tok2, arg2, -1);
    newString = substituteN(newString, tok3, arg3, -1);
    newString = substituteN(newString, tok4, arg4, -1);
    newString = substituteN(newString, tok5, arg5, -1);
    newString = substituteN(newString, tok6, arg6, -1);
    newString = substituteN(newString, tok7, arg7, -1);

    return newString;
}

/**
    \brief Template format function. A "{i}" occurence in the src string, where i = 0, 1, ..., 7, is substituted with the 
    values in arg1 trough arg8, respectively. The new string with the substitions is returned.
*/
template <class A, class B, class C, class D, class E, class F, class G, class H>
string formatN(const string& src, const A& arg1, const B& arg2, const C& arg3, const D& arg4, const E& arg5, const F& arg6, const G& arg7, const H& arg8)
{
    string newString(src);
    string  tok1("{0}"), tok2("{1}"), tok3("{2}"),
            tok4("{3}"), tok5("{4}"), tok6("{5}"),
            tok7("{6}"), tok8("{7}");

    newString = substituteN(newString, tok1, arg1, -1);
    newString = substituteN(newString, tok2, arg2, -1);
    newString = substituteN(newString, tok3, arg3, -1);
    newString = substituteN(newString, tok4, arg4, -1);
    newString = substituteN(newString, tok5, arg5, -1);
    newString = substituteN(newString, tok6, arg6, -1);
    newString = substituteN(newString, tok7, arg7, -1);
    newString = substituteN(newString, tok8, arg8, -1);

    return newString;
}

/**
    \brief Template function, substituting an occurence of a string, target, in the source string, with another string, item. The howMany argument
    limits the number of substitutions. A value of -1 causes all occurences to be substituted. 
    The new string with the substitions is returned.
*/
template <class T>
inline string substituteN(const string& source, const string& target, const T& item, const int& howMany= -1)
{
    return rr::substitute(source, target, rr::toString(item), howMany);
}

/**
    \brief Template function, substituting an occurence of a string, target, within the source string, with another, item. The howMany argument
    limits the number of substitutions. A value of -1 causes all occurences to be substituted. 
    The new string with the substitions is returned.
*/
template<>
inline string substituteN<double>(const string& source, const string& target, const double& item, const int& howMany)
{
    return rr::substitute(source, target, rr::toString(item, "%G"), howMany);
}

}
#endif
