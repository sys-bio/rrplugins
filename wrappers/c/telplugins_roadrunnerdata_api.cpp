#pragma hdrstop
#include "telplugins_roadrunnerdata_api.h"
#include "tel_macros.h"
#include "telplugins_utilities.h"
#include "telplugins_cpp_support.h"
#include "telStringUtils.h"
#include "rr/rrRoadRunner.h"
#include "rr/rrRoadRunnerData.h"

namespace tlpc
{
using namespace std;
using namespace tlp;
using rr::RoadRunnerData;

RRDataHandle tlp_cc getRoadRunnerDataHandle(RRHandle handle)
{
    start_try
        RoadRunner* rri = castToRoadRunner(handle);
        return rri->getSimulationResult();
    catch_ptr_macro
}

bool tlp_cc getRoadRunnerDataElement(RRDataHandle data, int row, int col, double* value)
{
    start_try
        RoadRunnerData* rrData = castToRoadRunnerData(data);
        *value = rrData->getDataElement(row, col);        
        return true;
    catch_bool_macro
}

bool tlp_cc setRoadRunnerDataElement(RRDataHandle data, int row, int col, double value)
{
    start_try
        RoadRunnerData* rrData = castToRoadRunnerData(data);
        rrData->setDataElement(row, col, value);        
        return true;
    catch_bool_macro
}

bool tlp_cc getRoadRunnerDataWeight(RRDataHandle data, int row, int col, double* value)
{
    start_try
        RoadRunnerData* rrData = castToRoadRunnerData(data);

        if(rrData->hasWeights())
        {
            (*value) = rrData->getWeight(row, col);            
            return true;
        }
        else
        {
            return false;
        }
    catch_bool_macro
}

bool tlp_cc setRoadRunnerDataWeight(RRDataHandle data, int row, int col, double value)
{
    start_try
        RoadRunnerData* rrData = castToRoadRunnerData(data);
        if(rrData->hasWeights())
        {
            rrData->setWeight(row, col, value);            
            return true;
        }
        else
        {
            return false;
        }
    catch_bool_macro
}

bool tlp_cc hasWeights(RRDataHandle rrData, bool* value)
{
    start_try
        RoadRunnerData* Data = castToRoadRunnerData(rrData);
        (*value) = Data->hasWeights();
        return true;
    catch_bool_macro
}

bool tlp_cc allocateWeights(RRDataHandle rrData, bool* success)
{
    start_try
        RoadRunnerData* Data = castToRoadRunnerData(rrData);
        Data->allocateWeights();
        (*success) = Data->hasWeights();
        return true;
    catch_bool_macro
}

char* tlp_cc getRoadRunnerDataColumnHeader(RRDataHandle rrData)
{
    start_try
        RoadRunnerData* data = castToRoadRunnerData(rrData);
        return createText(data->getColumnNamesAsString());
    catch_ptr_macro
}

int tlp_cc getRoadRunnerDataNumRows(RRDataHandle rrData)
{
    start_try
        RoadRunnerData* data = castToRoadRunnerData(rrData);
        return data->rSize();
    catch_int_macro
}

int tlp_cc getRoadRunnerDataNumCols(RRDataHandle rrData)
{
    start_try
        RoadRunnerData* data = castToRoadRunnerData(rrData);
        return data->cSize();
    catch_int_macro
}

RRDataHandle tlp_cc createRoadRunnerData(int nRows, int nCols, char* colNames)
{
    start_try
        RoadRunnerData* data = new RoadRunnerData(nRows, nCols);
        if (colNames)
        {
            string cNames(colNames);
            StringList colNames(cNames, ",");
            data->setColumnNames(colNames);
        }
        return data;
    catch_ptr_macro
}

bool tlp_cc freeRoadRunnerData(RRDataHandle rrData)
{
    start_try
        RoadRunnerData* data = castToRoadRunnerData(rrData);
        delete data;
        return true;
    catch_bool_macro
}

bool tlp_cc writeRoadRunnerDataToFile(RRDataHandle rrData, char* fName)
{
    start_try
        RoadRunnerData* data = castToRoadRunnerData(rrData);
        return data->writeTo(fName);
    catch_bool_macro
}

bool tlp_cc readRoadRunnerDataFromFile(RRDataHandle rrData, char* fName)
{
    start_try
        RoadRunnerData* data = castToRoadRunnerData(rrData);
        return data->readFrom(fName);
    catch_bool_macro

}

}
