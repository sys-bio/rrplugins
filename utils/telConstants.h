#ifndef telConstantsH
#define telConstantsH
#include <limits>
#include <string>
#include <cstdlib>
#include "telUtilsExporter.h"

typedef unsigned int    u_int;

namespace tlp
{

//Useful constants...
TLPUTILS_DS extern const char     gPathSeparator;
TLPUTILS_DS extern const std::string gExeSuffix;

TLPUTILS_DS extern const char* 			gDoubleFormat;
TLPUTILS_DS extern const char* 			gIntFormat;
TLPUTILS_DS extern const char* 			gComma;
TLPUTILS_DS extern const std::string 	gDefaultSupportCodeFolder;
TLPUTILS_DS extern const std::string 	gDefaultCompiler;
TLPUTILS_DS extern const std::string 	gDefaultTempFolder;
TLPUTILS_DS extern const std::string 	gNoneString;
TLPUTILS_DS extern const std::string	gEmptyString;

//Messages
TLPUTILS_DS extern const std::string gEmptyModelMessage;


// Constants
TLPUTILS_DS extern const char     gTab;
TLPUTILS_DS extern const char     gNL;
TLPUTILS_DS extern const double    gDoubleNaN;
TLPUTILS_DS extern const float  gFloatNaN;
TLPUTILS_DS extern const int    gMaxPath;

// Enums...
enum SBMLType {stCompartment = 0, stSpecies, stParameter};    //Species clashes with class Species, prefix enums with st, for SbmlType

}
#endif
