#pragma hdrstop
#include "telLogger.h"
#include "telplugins_logging_api.h"
#include "telplugins_cpp_support.h"
//---------------------------------------------------------------------------

namespace tlpc
{
using namespace std;
using namespace tlp;

bool tlp_cc tlpEnableLoggingToConsole()
{
    start_try
        Logger::enableConsoleLogging();
        return true;
    catch_bool_macro
}

bool tlp_cc tlpDisableLoggingToConsole()
{
    start_try
        Logger::disableConsoleLogging();
        return true;
    catch_bool_macro
}

bool tlp_cc tlpEnableLoggingToFile(char* fName)
{
    start_try
//        char* tempFolder = getTempFolder(handle);
        string logFile = string(fName);//joinPath(tempFolder, "RoadRunner.log") ;
//        tel::freeText(tempFolder);

        Logger::enableFileLogging(logFile);
        return true;
    catch_bool_macro
}

bool tlp_cc tlpDisableLoggingToFile()
{
    start_try
        Logger::disableFileLogging();
        return true;
    catch_bool_macro
}

bool tlp_cc tlpSetLogLevel(const char* _lvl)
{
    start_try
        Logger::Level lvl = Logger::stringToLevel(_lvl);
        Logger::setLevel(lvl);
        return true;
    catch_bool_macro
}

char* tlp_cc tlpGetLogLevel()
{
    start_try
        string level = Logger::getCurrentLevelAsString();
        char* lvl = tlp::createText(level.c_str());
        return lvl;
    catch_ptr_macro
}

char* tlp_cc tlpGetLogFileName()
{
    start_try
        return tlp::createText(Logger::getFileName().c_str());
    catch_ptr_macro
}

void tlp_cc tlpLogMsg(CLogLevel lvl, const char* msg)
{
    start_try
        if(msg)
        {
            Log((LogLevel) lvl)<<msg;
        }
        else
        {
            Log((LogLevel) lvl)<<"You passed a NULL message pointer to logMsg";
        }
    catch_void_macro
}

}
