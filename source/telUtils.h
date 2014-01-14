#ifndef telUtilsH
#define telUtilsH

#if defined(_WIN32)
    #include <windows.h>
#endif

#include <float.h>    //ms compatible IEEE functions, e.g. _isnan
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include "rr/rrSelectionRecord.h"
#include "rr/rrLogger.h"
#include "telStringList.h"
#include "telStringUtils.h"
#include "telExporter.h"
//---------------------------------------------------------------------------

namespace tlp
{

using std::vector;
using std::string;
using std::set;

enum LogLevel
{
    lAny        = rr::Logger::LOG_ERROR,
    lError      = rr::Logger::LOG_ERROR,
    lWarning    = rr::Logger::LOG_WARNING,
    lInfo       = rr::Logger::LOG_INFORMATION,
    lDebug      = rr::Logger::LOG_DEBUG,
    lDebug1     = rr::Logger::LOG_TRACE,
    lDebug2     = rr::Logger::LOG_TRACE,
    lDebug3     = rr::Logger::LOG_TRACE,
    lDebug4     = rr::Logger::LOG_TRACE,
    lDebug5     = rr::Logger::LOG_TRACE,
    lUser       = rr::Logger::LOG_TRACE
};

RRP_DECLSPEC StringList     getRecordsAsStrings(const vector<rr::SelectionRecord>& folder);
RRP_DECLSPEC bool           cleanFolder(const string& folder, const string& baseName,  const std::vector<std::string>& extensions);
RRP_DECLSPEC string         getTime();
RRP_DECLSPEC string         getDateTime();
RRP_DECLSPEC string         getMD5(const string& text);
RRP_DECLSPEC void           sleep(int ms);

//Misc.
/*!
\brief indexOf returns the index of an element in the vector. If not found, or if vector size is zero, it returns -1.
*/
RRP_DECLSPEC int             indexOf(const std::vector<std::string>& vec, const std::string& elem );
RRP_DECLSPEC bool            isNaN(const double& aNum);
RRP_DECLSPEC bool            isNullOrEmpty(const string& str);    //Can't be null, but empty
RRP_DECLSPEC void            pause(bool doIt = true, const string& msg = "");

//String utilities
RRP_DECLSPEC string          removeTrailingSeparator(const string& fldr, const char sep = gPathSeparator);//"\\");

//File  Utilities
RRP_DECLSPEC int             populateFileSet(const string& modelsFolder, set<string>& models);
RRP_DECLSPEC bool            fileExists(const string& fileN);
RRP_DECLSPEC bool            folderExists(const string& folderN);
RRP_DECLSPEC bool            createFolder(const string& path);

RRP_DECLSPEC string          getParentFolder(const string& path);
RRP_DECLSPEC string          getCurrentExeFolder();
RRP_DECLSPEC string          getUsersTempDataFolder();
RRP_DECLSPEC string          getCWD();
RRP_DECLSPEC const char      getPathSeparator();

RRP_DECLSPEC vector<string>  getLinesInFile(const string& fName);
RRP_DECLSPEC string          getFileContent(const string& fName);
RRP_DECLSPEC void            createTestSuiteFileNameParts(int caseNr, const string& postFixPart, string& FilePath, string& modelFileName, string& settingsFileName);
RRP_DECLSPEC string          getTestSuiteSubFolderName(int caseNr);

//CArray utilities
RRP_DECLSPEC bool            copyCArrayToStdVector(const int* src,     vector<int>& dest, int size);
RRP_DECLSPEC bool            copyCArrayToStdVector(const double* src,  vector<double>& dest, int size);
RRP_DECLSPEC bool            copyValues(vector<double>& dest, double* source, const int& nrVals, const int& startIndex);
RRP_DECLSPEC bool            copyCArrayToStdVector(const bool* src,    vector<bool>& dest, int size);
RRP_DECLSPEC bool            copyStdVectorToCArray(const vector<double>& src, double* dest,  int size);
RRP_DECLSPEC bool            copyStdVectorToCArray(const vector<bool>&   src,  bool*  dest,  int size);
RRP_DECLSPEC double*         createVector(const vector<double>& vec);
RRP_DECLSPEC vector<double>  createVector(const double* src, const int& size);

#if defined(_WIN32) || defined(__WIN32__)
RRP_DECLSPEC HINSTANCE       loadDLL(const string& dll);
RRP_DECLSPEC bool            unLoadDLL(HINSTANCE dllHandle);
RRP_DECLSPEC FARPROC         getFunctionPtr(const string& funcName, HINSTANCE DLLHandle);
RRP_DECLSPEC string          getWINAPIError(DWORD errorCode, LPTSTR lpszFunction);
#endif

#undef CreateFile
RRP_DECLSPEC bool            createFile(const string& fName, std::ios_base::openmode mode = std::ios::trunc );

} // rr Namespace
#endif
