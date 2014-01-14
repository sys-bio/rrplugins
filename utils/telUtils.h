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
#include "rr/rrLogger.h"
#include "telStringUtils.h"
#include "telUtilsExporter.h"
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

TLPUTILS_DS bool            cleanFolder(const string& folder, const string& baseName,  const std::vector<std::string>& extensions);
TLPUTILS_DS string          getTime();
TLPUTILS_DS string          getDateTime();
TLPUTILS_DS string          getMD5(const string& text);
TLPUTILS_DS void            sleep(int ms);

//Misc.
/*!
\brief indexOf returns the index of an element in the vector. If not found, or if vector size is zero, it returns -1.
*/
TLPUTILS_DS int             indexOf(const std::vector<std::string>& vec, const std::string& elem );
TLPUTILS_DS bool            isNaN(const double& aNum);
TLPUTILS_DS bool            isNullOrEmpty(const string& str);    //Can't be null, but empty
TLPUTILS_DS void            pause(bool doIt = true, const string& msg = "");

//String utilities
TLPUTILS_DS string          removeTrailingSeparator(const string& fldr, const char sep = gPathSeparator);//"\\");

//File  Utilities
TLPUTILS_DS int             populateFileSet(const string& modelsFolder, set<string>& models);
TLPUTILS_DS bool            fileExists(const string& fileN);
TLPUTILS_DS bool            folderExists(const string& folderN);
TLPUTILS_DS bool            createFolder(const string& path);

TLPUTILS_DS string          getParentFolder(const string& path);
TLPUTILS_DS string          getCurrentExeFolder();
TLPUTILS_DS string          getUsersTempDataFolder();
TLPUTILS_DS string          getCWD();
TLPUTILS_DS const char      getPathSeparator();

TLPUTILS_DS vector<string>  getLinesInFile(const string& fName);
TLPUTILS_DS string          getFileContent(const string& fName);
TLPUTILS_DS void            createTestSuiteFileNameParts(int caseNr, const string& postFixPart, string& FilePath, string& modelFileName, string& settingsFileName);
TLPUTILS_DS string          getTestSuiteSubFolderName(int caseNr);

//CArray utilities
TLPUTILS_DS bool            copyCArrayToStdVector(const int* src,     vector<int>& dest, int size);
TLPUTILS_DS bool            copyCArrayToStdVector(const double* src,  vector<double>& dest, int size);
TLPUTILS_DS bool            copyValues(vector<double>& dest, double* source, const int& nrVals, const int& startIndex);
TLPUTILS_DS bool            copyCArrayToStdVector(const bool* src,    vector<bool>& dest, int size);
TLPUTILS_DS bool            copyStdVectorToCArray(const vector<double>& src, double* dest,  int size);
TLPUTILS_DS bool            copyStdVectorToCArray(const vector<bool>&   src,  bool*  dest,  int size);
TLPUTILS_DS double*         createVector(const vector<double>& vec);
TLPUTILS_DS vector<double>  createVector(const double* src, const int& size);

#if defined(_WIN32) || defined(__WIN32__)
TLPUTILS_DS HINSTANCE       loadDLL(const string& dll);
TLPUTILS_DS bool            unLoadDLL(HINSTANCE dllHandle);
TLPUTILS_DS FARPROC         getFunctionPtr(const string& funcName, HINSTANCE DLLHandle);
TLPUTILS_DS string          getWINAPIError(DWORD errorCode, LPTSTR lpszFunction);
#endif

#undef CreateFile
TLPUTILS_DS bool            createFile(const string& fName, std::ios_base::openmode mode = std::ios::trunc );

} // rr Namespace
#endif
