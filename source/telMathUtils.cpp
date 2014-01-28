#pragma hdrstop
#include <math.h>
#include "telMathUtils.h"
#include "rr/rrLogger.h"
#include "telUtils.h"
#include "telException.h"
namespace tlp
{

TelluriumData getStandardizedPopulations(TelluriumData& population)
{
    TelluriumData stdPop(population.rSize(), population.cSize());
    vector<double> stdDeviations = getStandardDeviations(population);

    bool timeIsFirstCol = population.isFirstColumnTime();

    for(int col =0; col <population.cSize(); col++)
    {
        int nonTimeDataIndex = col - (timeIsFirstCol == true) ? 1 : 0;

        for(int dataPtn = 0; dataPtn < population.rSize(); dataPtn++)
        {
            if(timeIsFirstCol == true && col == 0)
            {
                stdPop(dataPtn, col) = population(dataPtn, col);
            }
            else
            {
                stdPop(dataPtn, col) =  population(dataPtn, col) / stdDeviations[nonTimeDataIndex];
            }
        }
        Log(lDebug)<<"Standard deviation: "<<stdDeviations[nonTimeDataIndex];
    }
    return stdPop;
}

vector<double>  getStandardDeviations(TelluriumData& population)
{
    vector<double> means = getMeans(population);

    //check for time column
    bool timeIsFirstCol = population.isFirstColumnTime();

    vector<double> stds;
    for(int col = (timeIsFirstCol == true) ? 1 : 0; col < population.cSize(); col++)
    {
        double sumOfSquaredDifferences  = 0;
        for(int row = 0; row < population.rSize(); row++)
        {
            int meansIndex = col - (timeIsFirstCol == true) ? 1 : 0;
            sumOfSquaredDifferences += pow( population(row, col) - means[meansIndex], 2);
        }
        double variance =  (1. /  (population.rSize() -1) ) * sumOfSquaredDifferences ;
        double stdDev =  sqrt(variance) ;
        Log(lInfo) << "Std Dev = " << stdDev;
        stds.push_back(stdDev);
    }
    return stds;
}

vector<double>  getMeans(TelluriumData& population)
{
    if(population.rSize() < 1)
    {
        throw(Exception("Bad population passed to function getMeans()"));
    }

    vector<double> means;
    //check for time column
    bool timeIsFirstCol = population.isFirstColumnTime();

    for(int col = (timeIsFirstCol == true) ? 1 : 0; col < population.cSize(); col++)
    {
        double mean  = 0;
        for(int row = 0; row < population.rSize(); row++)
        {
            mean += population(row, col);

        }
        means.push_back(mean / population.rSize());
    }
    return means;
}

}

