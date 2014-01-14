#ifndef telStringUtilsH
#define telStringUtilsH
#include <string>
#include <list>
#include <vector>
#include <complex>
#include "telConstants.h"
#include "telUtils.h"
#include "telExporter.h"

namespace tlp
{
using std::string;
using std::list;
using std::vector;
using std::complex;

RRP_DECLSPEC char*   			createText(const string& str);
RRP_DECLSPEC char*   			createText(const int& count);
RRP_DECLSPEC bool   				freeText(char* str);
RRP_DECLSPEC string              replaceWord(const string& str1, const string& str2, const string& theString);
RRP_DECLSPEC bool                convertFunctionCallToUseVarArgsSyntax(const string& funcName, string& expression);
RRP_DECLSPEC string              removeChars(const string& str, const string& chars);
RRP_DECLSPEC bool                isUnwantedChar(char ch); //Predicate for find_if algorithms..
RRP_DECLSPEC size_t              findMatchingRightParenthesis(const string& expression, const size_t startFrom);
RRP_DECLSPEC int                 getNumberOfFunctionArguments(const string& expression);
RRP_DECLSPEC string              tabs(const int& nr);
RRP_DECLSPEC string              NL();

RRP_DECLSPEC string				toUpperOrLowerCase(const string& inStr, int (*func)(int));
RRP_DECLSPEC string 				toUpper(const string& str);
RRP_DECLSPEC string 				toLower(const string& str);

RRP_DECLSPEC string              getFilePath(const string& fileN);
RRP_DECLSPEC string              getFileName(const string& fileN);
RRP_DECLSPEC string              getFileNameNoExtension(const string& fileN);
RRP_DECLSPEC string              getFileExtension(const string& fileN);

RRP_DECLSPEC string              changeFileExtensionTo(const string& theFileName, const string& newExtension);

RRP_DECLSPEC int 				compareNoCase(const string& str1, const string& str2);
RRP_DECLSPEC string              trim(const string& str, const char& toTrim = ' ');
RRP_DECLSPEC bool                startsWith(const string& src, const string& sub);
RRP_DECLSPEC bool                endsWith(const string& src, const string& sub);

//Can't use va_arg for non pod data.. :(
RRP_DECLSPEC string              joinPath(const string& p1, const string& p2, const char pathSeparator = gPathSeparator);
RRP_DECLSPEC string              joinPath(const string& p1, const string& p2, const string& p3, const char pathSeparator = gPathSeparator);
RRP_DECLSPEC string              joinPath(const string& p1, const string& p2, const string& p3, const string& p4, const char pathSeparator = gPathSeparator);
RRP_DECLSPEC string              joinPath(const string& p1, const string& p2, const string& p3, const string& p4, const string& p5, const char pathSeparator = gPathSeparator);

//conversions
RRP_DECLSPEC string              intToStr(const int& nt);
RRP_DECLSPEC int                 strToInt(const string& nt);
RRP_DECLSPEC string              dblToStr(const double& nt);
RRP_DECLSPEC double              strToDbl(const string& nt);
RRP_DECLSPEC vector<string>      splitString(const string &text, const string &separators);
RRP_DECLSPEC vector<string>      splitString(const string& input, const char& delimiters);
RRP_DECLSPEC int                 toInt(const string& str);
RRP_DECLSPEC bool                toBool(const string& str);
RRP_DECLSPEC double              toDouble(const string& str);
RRP_DECLSPEC complex<double>     toComplex(const string& str);

RRP_DECLSPEC string              toString(const bool& b);
RRP_DECLSPEC string              toString(const double& d, const string& format = gDoubleFormat);
RRP_DECLSPEC string              toString(const unsigned int& n, const string& format = gIntFormat, const int nBase=10);
RRP_DECLSPEC string              toString(const int& n, const string& format = gIntFormat, const int nBase=10);
RRP_DECLSPEC string              toString(const long n, const int nBase=10);
RRP_DECLSPEC string              toString(const unsigned long n, const int nBase=10);
RRP_DECLSPEC string              toString(const unsigned short n, const int nBase=10);
RRP_DECLSPEC string              toString(const short n, const int nBase=10);
RRP_DECLSPEC string              toString(const char n);
RRP_DECLSPEC string              toString(const unsigned char n);
RRP_DECLSPEC string              toString(const string& s);
RRP_DECLSPEC string              toString(const char* str);
RRP_DECLSPEC string              toString(const vector<string>& vec, const string& sep = ", ");

RRP_DECLSPEC string              format(const string& src, const int& arg);
RRP_DECLSPEC string              format(const string& str, const int& arg1);
RRP_DECLSPEC string              format(const string& str1, const int& arg1, const double& arg2);

RRP_DECLSPEC string              format(const string& src, const string& arg);
RRP_DECLSPEC string              format(const string& src, const string& arg1, const string& arg2, const string& arg3);
RRP_DECLSPEC string              format(const string& src, const string& arg1, const string& arg2);
RRP_DECLSPEC string              format(const string& src, const string& arg1, const int& arg2);
RRP_DECLSPEC string              format(const string& src, const string& arg1, const int& arg2, const string& arg3);
RRP_DECLSPEC string              format(const string& str1, const string& str2);
RRP_DECLSPEC string              format(const string& str1, const string& arg1, const string& arg2);
RRP_DECLSPEC string              format(const string& str1, const string& arg1, const int& arg2);
RRP_DECLSPEC string              format(const string& str1, const string& arg1, const int& arg2, const string& arg3);
RRP_DECLSPEC string              format(const string& str1, const string& arg1, const string& arg2, const string& arg3);
RRP_DECLSPEC string              format(const string& str1, const string& arg1, const string& arg2, const string& arg3, const string& arg4);
RRP_DECLSPEC string              format(const string& str1, const string& arg1, const string& arg2, const string& arg3, const string& arg4, const string& arg5);

RRP_DECLSPEC string              format(const string& str1, const unsigned int& arg1, const string& arg2);

RRP_DECLSPEC string              format(const string& str1, const unsigned int& arg1, const string& arg2, const string& arg3);

RRP_DECLSPEC string              format(const string& str1, const unsigned int& arg1, const unsigned int& arg2, const string& arg3, const string& arg4);

RRP_DECLSPEC string              append(const string& str);
RRP_DECLSPEC string              append(const int& str);
RRP_DECLSPEC string              append(const unsigned int& str);
RRP_DECLSPEC string              append(const string& s1, const string& s2);
RRP_DECLSPEC string              append(const string& s1, const string& s2, const string& s3);
RRP_DECLSPEC string              append(const string& s1, const unsigned int& s2, const string& s3);
RRP_DECLSPEC string              append(const string& s1, const unsigned int& s2, const string& s3, const string& s4);

RRP_DECLSPEC string              substitute(const string& src, const string& thisOne, const string& withThisOne, const int& howMany = -1);
RRP_DECLSPEC string              substitute(const string& src, const string& thisOne, const int& withThisOne, const int& howMany = -1);
//RRP_DECLSPEC string              substitute(const string& src, const string& thisOne, const double& withThisOne, const int& howMany = -1);
RRP_DECLSPEC string              removeNewLines(const string& str, const int& howMany = -1);
}
#endif
