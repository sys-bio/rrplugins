#pragma hdrstop
#include "lmObjectiveFunction.h"
#include "rr/rrRoadRunner.h"
#include "rr/C/rrc_api.h" //Todo: no reason using the roaddrunner C API here, convert and use the CPP api directly
#include "lm.h"

using namespace std;
using namespace lmfit;
using namespace tlp;
using namespace rrc;
//---------------------------------------------------------------------------
/* function evaluation, determination of residues */
void lmObjectiveFunction(const double *par,       //Property vector
              int           m_dat,      //Dimension of residue vector
              const void   *userData,  //Data structure
              double       *fvec,      //residue vector..
              int          *userBreak  //Non zero value means termination
)
{
    const LM    *thePlugin = (const LM*) userData;
    LM*         plugin = const_cast<LM*>(thePlugin);
	const       lmDataStructure* myData = &(thePlugin->mLMData);

    //Check if user have asked for termination..
    if(thePlugin->isBeingTerminated())
    {
        (*userBreak) = -1; //This signals lmfit algorithm to break
        return;
    }

    //Reset RoadRunner
    reset(myData->rrHandle);

    for(int i = 0; i < myData->nrOfParameters; i++)
    {
        setValue(myData->rrHandle, myData->parameterLabels[i], par[i]);
        Log(lDebug)<<myData->parameterLabels[i]<<" = "<<par[i]<<endl;
    }

    rrc::RRDataHandle rrData = NULL;
    rrData = simulateEx(   myData->rrHandle,
                                myData->timeStart,
                                myData->timeEnd,
                                myData->nrOfTimePoints);
    if(!rrData)
    {
        stringstream msg;
        msg << "NULL data returned from RoadRunner simulateEx() function.";
        char* lastError = getLastError();

        if(lastError)
        {
            msg << "\nLast error was: "<<lastError;
        }

        Log(lError)<<msg.str();
        rrc::freeText(lastError);
        return;
    }

    //Don't create RRC data, use rrData directly here
    RRCDataPtr rrcData = createRRCData(rrData);
    //calculate fvec for each specie
    int count = 0;
    for(int i = 0; i < myData->nrOfSpecies; i++)
    {
        fvec[count] = 0;
        for(int j = 0; j < myData->nrOfTimePoints; j++ )
        {
            double modelValue;
            if(!rrc::getRRCDataElement(rrcData, j, i, &modelValue))
            {
                throw("Bad stuff...") ;
            }

            if(!isNaN(myData->experimentalData[i][j]))
            {
                fvec[count] = myData->experimentalData[i][j] - modelValue;

                if(myData->experimentalDataWeights != NULL)
                {
                    if(myData->experimentalDataWeights[i][j] != 0) //Cause the first column is time... :( loks ugly
                    {
                        double weight =  myData->experimentalDataWeights[i][j];
                        fvec[count] = fvec[count] / weight;
                    }
                }
            }
            else
            {
                fvec[count] = 0;
            }
            count++;
        }
    }

    freeRRCData(rrcData);

    if(plugin->hasProgressEvent())
    {
        //Assign data relevant to the progress
        double norm = lm_enorm(m_dat, fvec);
        plugin->mNrOfIter.setValue(plugin->mNrOfIter.getValue() + 1);
        plugin->mNorm.setValue(norm);

        //Add norm to Norms property
        plugin->rNormsData(plugin->mNrOfIter.getValue() -1, 0) = plugin->mNorm.getValue();

        //Pass trough event data
        pair<void*, void*> passTroughData = plugin->getWorkProgressData();
        plugin->WorkProgressEvent(passTroughData.first, passTroughData.second);
    }
}

