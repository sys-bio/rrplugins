#ifndef telMathUtilsH
#define telMathUtilsH
#include "telExporter.h"
#include <vector>
#include "telTelluriumData.h"
//---------------------------------------------------------------------------

namespace tlp
{
using std::vector;

RRP_DECLSPEC TelluriumData   getStandardizedPopulations(TelluriumData& population);
RRP_DECLSPEC vector<double>  getStandardDeviations(TelluriumData& population);
RRP_DECLSPEC vector<double>  getMeans(TelluriumData& residualsData);

}

#endif
