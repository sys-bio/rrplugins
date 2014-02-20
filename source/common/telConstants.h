#ifndef telConstantsH
#define telConstantsH
#include <limits>
#include <string>
#include <cstdlib>
#include "telExporter.h"

typedef unsigned int    u_int;

namespace tlp
{

//Useful constants...
RRP_DECLSPEC extern const char     gPathSeparator;
RRP_DECLSPEC extern const std::string gExeSuffix;

RRP_DECLSPEC extern const char* 			gDoubleFormat;
RRP_DECLSPEC extern const char* 			gIntFormat;
RRP_DECLSPEC extern const char* 			gComma;
RRP_DECLSPEC extern const std::string 	gDefaultSupportCodeFolder;
RRP_DECLSPEC extern const std::string 	gDefaultCompiler;
RRP_DECLSPEC extern const std::string 	gDefaultTempFolder;
RRP_DECLSPEC extern const std::string 	gNoneString;
RRP_DECLSPEC extern const std::string	gEmptyString;

//Messages
RRP_DECLSPEC extern const std::string gEmptyModelMessage;


// Constants
RRP_DECLSPEC extern const char     gTab;
RRP_DECLSPEC extern const char     gNL;
RRP_DECLSPEC extern const double    gDoubleNaN;
RRP_DECLSPEC extern const float  gFloatNaN;
RRP_DECLSPEC extern const int    gMaxPath;

// Enums...
enum SBMLType {stCompartment = 0, stSpecies, stParameter};    //Species clashes with class Species, prefix enums with st, for SbmlType

}
#endif
