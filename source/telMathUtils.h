#ifndef telMathUtilsH
#define telMathUtilsH
#include <vector>
#include "telExporter.h"
#include "telTelluriumData.h"
//---------------------------------------------------------------------------

namespace tlp
{

using std::vector;
RRP_DECLSPEC TelluriumData      getNormalProbabilityPlot(const TelluriumData& stdPops);
RRP_DECLSPEC TelluriumData      getStandardizedPopulations(const TelluriumData& population);
RRP_DECLSPEC vector<double>     getStandardDeviations(const TelluriumData& population);
RRP_DECLSPEC vector<double>     getMeans(const TelluriumData& residualsData);
RRP_DECLSPEC vector<double>     getValuesInColumn(int col, const TelluriumData& data);
RRP_DECLSPEC double             normsdist(const double x);
RRP_DECLSPEC double             invnormsdist(const double y); // 0 < y < 1;

//Vector double arguments
RRP_DECLSPEC double             getChiSquare(const vector<double>& O, const vector<double>& E, const vector<double>& variances);
RRP_DECLSPEC double             getStandardDeviation(const vector<double>& population);
RRP_DECLSPEC double             getMean(const vector<double>& population);
RRP_DECLSPEC double             erf(double x);
RRP_DECLSPEC double             cdf(double n);

}
#endif
