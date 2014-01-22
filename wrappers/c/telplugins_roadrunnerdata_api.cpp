#pragma hdrstop
#include "telplugins_roadrunnerdata_api.h"
#include "tel_macros.h"
#include "telplugins_utilities.h"
#include "telplugins_cpp_support.h"
#include "telStringUtils.h"
#include "rr/rrRoadRunner.h"
#include "telTelluriumData.h"

namespace tlpc
{
using namespace std;
using namespace tlp;
using tlp::TelluriumData;

RRDataHandle tlp_cc getTelluriumDataHandle(RRHandle handle)
{
    start_try
        RoadRunner* rri = castToRoadRunner(handle);
        return rri->getSimulationResult();
    catch_ptr_macro
}

bool tlp_cc getTelluriumDataElement(RRDataHandle data, int row, int col, double* value)
{
    start_try
        TelluriumData* rrData = castToTelluriumData(data);
        *value = rrData->getDataElement(row, col);        
        return true;
    catch_bool_macro
}

bool tlp_cc setTelluriumDataElement(RRDataHandle data, int row, int col, double value)
{
    start_try
        TelluriumData* rrData = castToTelluriumData(data);
        rrData->setDataElement(row, col, value);        
        return true;
    catch_bool_macro
}

bool tlp_cc getTelluriumDataWeight(RRDataHandle data, int row, int col, double* value)
{
    start_try
        TelluriumData* rrData = castToTelluriumData(data);

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

bool tlp_cc setTelluriumDataWeight(RRDataHandle data, int row, int col, double value)
{
    start_try
        TelluriumData* rrData = castToTelluriumData(data);
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
        TelluriumData* Data = castToTelluriumData(rrData);
        (*value) = Data->hasWeights();
        return true;
    catch_bool_macro
}

bool tlp_cc allocateWeights(RRDataHandle rrData, bool* success)
{
    start_try
        TelluriumData* Data = castToTelluriumData(rrData);
        Data->allocateWeights();
        (*success) = Data->hasWeights();
        return true;
    catch_bool_macro
}

char* tlp_cc getTelluriumDataColumnHeader(RRDataHandle rrData)
{
    start_try
        TelluriumData* data = castToTelluriumData(rrData);
        return createText(data->getColumnNamesAsString());
    catch_ptr_macro
}

char* tlp_cc getTelluriumDataColumnHeaderByIndex(RRDataHandle rrData, int index)
{
    start_try
        TelluriumData* data = castToTelluriumData(rrData);
        StringList cols = data->getColumnNames();        
        return createText(cols[index]);
    catch_ptr_macro
}

bool tlp_cc setTelluriumDataColumnHeader(RRDataHandle rrData, char* hdr)
{
    start_try
        TelluriumData* data = castToTelluriumData(rrData);
        StringList hdrList(hdr, ", ");
        return data->setColumnNames(hdrList);
    catch_bool_macro
}

bool tlp_cc setTelluriumDataColumnHeaderByIndex(RRDataHandle rrData, int index, char* hdr)
{
    start_try
        TelluriumData* data = castToTelluriumData(rrData);        
        return data->setColumnName(index, hdr);
    catch_bool_macro
}

int tlp_cc getTelluriumDataNumRows(RRDataHandle rrData)
{
    start_try
        TelluriumData* data = castToTelluriumData(rrData);
        return data->rSize();
    catch_int_macro
}

int tlp_cc getTelluriumDataNumCols(RRDataHandle rrData)
{
    start_try
        TelluriumData* data = castToTelluriumData(rrData);
        return data->cSize();
    catch_int_macro
}

RRDataHandle tlp_cc createTelluriumData(int nRows, int nCols, char* colNames)
{
    start_try
        TelluriumData* data = new TelluriumData(nRows, nCols);
        if (colNames)
        {
            string cNames(colNames);
            StringList colNames(cNames, ",");
            data->setColumnNames(colNames);
        }
        return data;
    catch_ptr_macro
}

bool tlp_cc freeTelluriumData(RRDataHandle rrData)
{
    start_try
        TelluriumData* data = castToTelluriumData(rrData);
        delete data;
        return true;
    catch_bool_macro
}

bool tlp_cc writeTelluriumDataToFile(RRDataHandle rrData, char* fName)
{
    start_try
        TelluriumData* data = castToTelluriumData(rrData);
        return data->writeTo(fName);
    catch_bool_macro
}

bool tlp_cc readTelluriumDataFromFile(RRDataHandle rrData, char* fName)
{
    start_try
        TelluriumData* data = castToTelluriumData(rrData);
        return data->readFrom(fName);
    catch_bool_macro

}

}
