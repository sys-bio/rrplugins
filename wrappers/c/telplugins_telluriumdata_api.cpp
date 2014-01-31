#pragma hdrstop
#include "rr/rrRoadRunner.h"
#include "telOSSpecifics.h"
#include "telplugins_telluriumdata_api.h"
#include "tel_macros.h"
#include "telplugins_utilities.h"
#include "telplugins_cpp_support.h"
#include "telStringUtils.h"
#include "telTelluriumData.h"

namespace tlpc
{
using rr::RoadRunner;
using namespace std;
using tlp::TelluriumData;
using tlp::StringList;
using tlpc::createText;

TELHandle tlp_cc getRoadRunnerDataHandle(TELHandle handle)
{
    start_try
        RoadRunner* rri = castHandle< RoadRunner >(handle, __FILE__);
        return rri->getSimulationResult();
    catch_ptr_macro
}

bool tlp_cc getTelluriumDataElement(TELHandle handle, int row, int col, double* value)
{
    start_try
        TelluriumData* rrData = castHandle< TelluriumData >(handle, __FILE__);
        *value = rrData->getDataElement(row, col);
        return true;
    catch_bool_macro
}

bool tlp_cc setTelluriumDataElement(TELHandle handle, int row, int col, double value)
{
    start_try
        TelluriumData* rrData = castHandle< TelluriumData >(handle, __FUNC__);
        rrData->setDataElement(row, col, value);
        return true;
    catch_bool_macro
}

bool tlp_cc getTelluriumDataWeight(TELHandle handle, int row, int col, double* value)
{
    start_try
        TelluriumData* rrData = castHandle< TelluriumData >(handle, __FUNC__);

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

bool tlp_cc setTelluriumDataWeight(TELHandle handle, int row, int col, double value)
{
    start_try
        TelluriumData* rrData = castHandle< TelluriumData >(handle, __FUNC__);
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

bool tlp_cc hasWeights(TELHandle handle, bool* value)
{
    start_try
        TelluriumData* Data = castHandle< TelluriumData >(handle, __FUNC__);
        (*value) = Data->hasWeights();
        return true;
    catch_bool_macro
}

bool tlp_cc allocateWeights(TELHandle handle, bool* success)
{
    start_try
        TelluriumData* Data = castHandle< TelluriumData > (handle, __FUNC__);
        Data->allocateWeights();
        (*success) = Data->hasWeights();
        return true;
    catch_bool_macro
}

char* tlp_cc getTelluriumDataColumnHeader(TELHandle handle)
{
    start_try
        TelluriumData* data = castHandle< TelluriumData >(handle, __FUNC__);
        return tlpc::createText(data->getColumnNamesAsString());
    catch_ptr_macro
}

char* tlp_cc getTelluriumDataColumnHeaderByIndex(TELHandle handle, int index)
{
    start_try
        TelluriumData* data = castHandle< TelluriumData >(handle, __FUNC__);
        StringList cols = data->getColumnNames();        
        return createText(cols[index]);
    catch_ptr_macro
}

bool tlp_cc setTelluriumDataColumnHeader(TELHandle handle, char* hdr)
{
    start_try
        TelluriumData* data = castHandle< TelluriumData >(handle, __FUNC__);
        StringList hdrList(hdr, ", ");
        return data->setColumnNames(hdrList);
    catch_bool_macro
}

bool tlp_cc setTelluriumDataColumnHeaderByIndex(TELHandle handle, int index, char* hdr)
{
    start_try
        TelluriumData* data = castHandle< TelluriumData >(handle, __FUNC__);
        return data->setColumnName(index, hdr);
    catch_bool_macro
}

int tlp_cc getTelluriumDataNumRows(TELHandle handle)
{
    start_try
        TelluriumData* data = castHandle< TelluriumData >(handle, __FUNC__);
        return data->rSize();
    catch_int_macro
}

int tlp_cc getTelluriumDataNumCols(TELHandle handle)
{
    start_try
        TelluriumData* data = castHandle< TelluriumData >(handle, __FUNC__);
        return data->cSize();
    catch_int_macro
}

TELHandle tlp_cc createTelluriumData(int nRows, int nCols, char* colNames)
{
    start_try
        TelluriumData* data = new TelluriumData(nRows, nCols);
        gHM.registerHandle(data, typeid(data).name());
        if (colNames)
        {
            string cNames(colNames);
            StringList colNames(cNames, ",");
            data->setColumnNames(colNames);
        }
        return data;
    catch_ptr_macro
}

bool tlp_cc freeTelluriumData(TELHandle handle)
{
    start_try
        TelluriumData* data = castHandle< TelluriumData >(handle, __FUNC__);
        delete data;
        return true;
    catch_bool_macro
}

bool tlp_cc writeTelluriumDataToFile(TELHandle handle, char* fName)
{
    start_try
        TelluriumData* data = castHandle< TelluriumData >(handle, __FUNC__);
        return data->writeTo(fName);
    catch_bool_macro
}

bool tlp_cc readTelluriumDataFromFile(TELHandle handle, char* fName)
{
    start_try
        TelluriumData* data = castHandle< TelluriumData >(handle, __FUNC__);
        //Check if file exists first        
        return data->readFrom(fName);
    catch_bool_macro

}

}
