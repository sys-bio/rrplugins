#ifndef telStringUtilsH
#define telStringUtilsH
#include <string>
#include <list>
#include <vector>
#include <complex>
#include "telConstants.h"
#include "telUtils.h"
#include "telUtilsExporter.h"

namespace tlp
{
using std::string;
using std::list;
using std::vector;
using std::complex;

TLPUTILS_DS char*   			createText(const string& str);
TLPUTILS_DS char*   			createText(const int& count);
TLPUTILS_DS bool   				freeText(char* str);
TLPUTILS_DS string              replaceWord(const string& str1, const string& str2, const string& theString);
TLPUTILS_DS bool                convertFunctionCallToUseVarArgsSyntax(const string& funcName, string& expression);
TLPUTILS_DS string              removeChars(const string& str, const string& chars);
TLPUTILS_DS bool                isUnwantedChar(char ch); //Predicate for find_if algorithms..
TLPUTILS_DS size_t              findMatchingRightParenthesis(const string& expression, const size_t startFrom);
TLPUTILS_DS int                 getNumberOfFunctionArguments(const string& expression);
TLPUTILS_DS string              tabs(const int& nr);
TLPUTILS_DS string              NL();

TLPUTILS_DS string				toUpperOrLowerCase(const string& inStr, int (*func)(int));
TLPUTILS_DS string 				toUpper(const string& str);
TLPUTILS_DS string 				toLower(const string& str);

TLPUTILS_DS string              getFilePath(const string& fileN);
TLPUTILS_DS string              getFileName(const string& fileN);
TLPUTILS_DS string              getFileNameNoExtension(const string& fileN);
TLPUTILS_DS string              getFileExtension(const string& fileN);

TLPUTILS_DS string              changeFileExtensionTo(const string& theFileName, const string& newExtension);

TLPUTILS_DS int 				compareNoCase(const string& str1, const string& str2);
TLPUTILS_DS string              trim(const string& str, const char& toTrim = ' ');
TLPUTILS_DS bool                startsWith(const string& src, const string& sub);
TLPUTILS_DS bool                endsWith(const string& src, const string& sub);

//Can't use va_arg for non pod data.. :(
TLPUTILS_DS string              joinPath(const string& p1, const string& p2, const char pathSeparator = gPathSeparator);
TLPUTILS_DS string              joinPath(const string& p1, const string& p2, const string& p3, const char pathSeparator = gPathSeparator);
TLPUTILS_DS string              joinPath(const string& p1, const string& p2, const string& p3, const string& p4, const char pathSeparator = gPathSeparator);
TLPUTILS_DS string              joinPath(const string& p1, const string& p2, const string& p3, const string& p4, const string& p5, const char pathSeparator = gPathSeparator);

//conversions
TLPUTILS_DS string              intToStr(const int& nt);
TLPUTILS_DS int                 strToInt(const string& nt);
TLPUTILS_DS string              dblToStr(const double& nt);
TLPUTILS_DS double              strToDbl(const string& nt);
TLPUTILS_DS vector<string>      splitString(const string &text, const string &separators);
TLPUTILS_DS vector<string>      splitString(const string& input, const char& delimiters);
TLPUTILS_DS int                 toInt(const string& str);
TLPUTILS_DS bool                toBool(const string& str);
TLPUTILS_DS double              toDouble(const string& str);
TLPUTILS_DS complex<double>     toComplex(const string& str);

TLPUTILS_DS string              toString(const bool& b);
TLPUTILS_DS string              toString(const double& d, const string& format = gDoubleFormat);
TLPUTILS_DS string              toString(const unsigned int& n, const string& format = gIntFormat, const int nBase=10);
TLPUTILS_DS string              toString(const int& n, const string& format = gIntFormat, const int nBase=10);
TLPUTILS_DS string              toString(const long n, const int nBase=10);
TLPUTILS_DS string              toString(const unsigned long n, const int nBase=10);
TLPUTILS_DS string              toString(const unsigned short n, const int nBase=10);
TLPUTILS_DS string              toString(const short n, const int nBase=10);
TLPUTILS_DS string              toString(const char n);
TLPUTILS_DS string              toString(const unsigned char n);
TLPUTILS_DS string              toString(const string& s);
TLPUTILS_DS string              toString(const char* str);
TLPUTILS_DS string              toString(const vector<string>& vec, const string& sep = ", ");

TLPUTILS_DS string              format(const string& src, const int& arg);
TLPUTILS_DS string              format(const string& str, const int& arg1);
TLPUTILS_DS string              format(const string& str1, const int& arg1, const double& arg2);

TLPUTILS_DS string              format(const string& src, const string& arg);
TLPUTILS_DS string              format(const string& src, const string& arg1, const string& arg2, const string& arg3);
TLPUTILS_DS string              format(const string& src, const string& arg1, const string& arg2);
TLPUTILS_DS string              format(const string& src, const string& arg1, const int& arg2);
TLPUTILS_DS string              format(const string& src, const string& arg1, const int& arg2, const string& arg3);
TLPUTILS_DS string              format(const string& str1, const string& str2);
TLPUTILS_DS string              format(const string& str1, const string& arg1, const string& arg2);
TLPUTILS_DS string              format(const string& str1, const string& arg1, const int& arg2);
TLPUTILS_DS string              format(const string& str1, const string& arg1, const int& arg2, const string& arg3);
TLPUTILS_DS string              format(const string& str1, const string& arg1, const string& arg2, const string& arg3);
TLPUTILS_DS string              format(const string& str1, const string& arg1, const string& arg2, const string& arg3, const string& arg4);
TLPUTILS_DS string              format(const string& str1, const string& arg1, const string& arg2, const string& arg3, const string& arg4, const string& arg5);

TLPUTILS_DS string              format(const string& str1, const unsigned int& arg1, const string& arg2);

TLPUTILS_DS string              format(const string& str1, const unsigned int& arg1, const string& arg2, const string& arg3);

TLPUTILS_DS string              format(const string& str1, const unsigned int& arg1, const unsigned int& arg2, const string& arg3, const string& arg4);

TLPUTILS_DS string              append(const string& str);
TLPUTILS_DS string              append(const int& str);
TLPUTILS_DS string              append(const unsigned int& str);
TLPUTILS_DS string              append(const string& s1, const string& s2);
TLPUTILS_DS string              append(const string& s1, const string& s2, const string& s3);
TLPUTILS_DS string              append(const string& s1, const unsigned int& s2, const string& s3);
TLPUTILS_DS string              append(const string& s1, const unsigned int& s2, const string& s3, const string& s4);

TLPUTILS_DS string              substitute(const string& src, const string& thisOne, const string& withThisOne, const int& howMany = -1);
TLPUTILS_DS string              substitute(const string& src, const string& thisOne, const int& withThisOne, const int& howMany = -1);
//TLPUTILS_DS string              substitute(const string& src, const string& thisOne, const double& withThisOne, const int& howMany = -1);
TLPUTILS_DS string              removeNewLines(const string& str, const int& howMany = -1);
}
#endif
