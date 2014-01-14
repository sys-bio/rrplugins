#pragma hdrstop
#include "rrUtils.h"
#include "rrRRAuto.h"
#include "rrExecutableModel.h"
#include "../libAuto/vsAuto.h"
#include "rrLogger.h"
#include "rrStringList.h"
#include "rrPluginUtils.h"

namespace rrauto
{
using namespace rr;
using namespace rrp;
using namespace autolib;

//Statics
RoadRunner*     RRAuto::mRR = NULL;
SetupControl    RRAuto::mAutoSetup;
string          RRAuto::mSelectedParameter = gEmptyString;

RRAuto::RRAuto(RoadRunner* rr)
{
    mRR = rr;
}

RRAuto::~RRAuto()
{}

void RRAuto::assignRoadRunner(RoadRunner* rrInstance)
{
    mRR = rrInstance;
}

bool RRAuto::selectParameter(const string& para)
{
    mSelectedParameter = para;
//    mAutoSetup.mParameter = &para;
    return false;
}

bool RRAuto::setStartParameterValue(const double& val)
{
    mAutoSetup.mInputConstants.RL0 = val;
    return false;
}

bool RRAuto::setEndParameterValue(const double& val)
{
    mAutoSetup.mInputConstants.RL1 = val;
    return false;
}

bool RRAuto::setScanDirection(ScanDirection val)
{
    mAutoSetup.mDirectionPositive = (val == sdPositive) ? true : false;

    if(mAutoSetup.mDirectionPositive)
    {
        mAutoSetup.mInputConstants.DS = fabs(mAutoSetup.mInputConstants.DS);
    }
    else
    {
        mAutoSetup.mInputConstants.DS = -1 * fabs(mAutoSetup.mInputConstants.DS);
    }
    return false;
}

bool RRAuto::setTempFolder(const string& fldr)
{
    if(folderExists(fldr))
    {
        mTempFolder = fldr;
        return true;
    }
    else
    {
        return false;
    }
}

string RRAuto::getTempFolder()
{
    return mTempFolder;
}

bool RRAuto::run()
{
    if(!mRR)
    {
        return false;
    }

    reset();

    mAutoSetup.mRunContinuation = false;
    double parValue = (mAutoSetup.mDirectionPositive == true)
                    ? mAutoSetup.mInputConstants.RL0.getValue() : mAutoSetup.mInputConstants.RL1.getValue();

    //Set initial value of Primary cintinuation parameter
    mRR->setValue(mSelectedParameter, parValue);


    if(mAutoSetup.mCalculateSteadyState)
    {
        mRR->steadyState();
    }

    if(!setupUsingCurrentModel())
    {
        return false;
    }

    CallAuto(getTempFolder());
    return true;
}

bool RRAuto::setupUsingCurrentModel()
{
    int ndim = mRR->getSteadyStateSelections().size();
    mAutoSetup.mInputConstants.NDIM = ndim;

    setCallbackStpnt(ModelInitializationCallback);
    setCallbackFunc2(ModelFunctionCallback);

    string temp = mAutoSetup.getConstantsAsString();
    autolib::createFort2File(temp.c_str(), joinPath(getTempFolder(),"fort.2"));
    return true;
}

string RRAuto::getConstantsAsString()
{
    return mAutoSetup.getConstantsAsString();
}

//Called by Auto
int autoCallConv RRAuto::ModelInitializationCallback(long ndim, double t, double* u, double* par)
{
    ExecutableModel* lModel = mRR->getModel();

    int numBoundaries = 0;  //ToDo: to be set from the outside
    int numParameters = 1;  //ToDo: to be set from the outside

    vector<double> oBoundary(numBoundaries);
    vector<double> oGlobalParameters(numParameters);

    if (numBoundaries > 0)
    {
        vector<int> oSelectedBoundary(1);
        oSelectedBoundary[0] = 0;           //ToDo: This need to be set from the outside!
        for (int i = 0; i < numBoundaries; i++)
        {
            oBoundary[i] = mRR->getBoundarySpeciesByIndex(oSelectedBoundary[i]);
        }
    }

    if (numParameters > 0)
    {
        double val  = mRR->getValue(mSelectedParameter);
        oGlobalParameters[0] = val;

//        for (int i = 0; i < numParameters; i++)
//        {
//            oGlobalParameters[i] = mRR->getGlobalParameterByIndex(oSelectedParameters[i]);
//        }
    }

    int oParaSize = numBoundaries + numParameters;
    vector<double> oParameters(oParaSize);

    for(int i = 0; i < numBoundaries; i++)
    {
        oParameters[i] = oBoundary[i];
    }

    //Array.Copy(oGlobalParameters, 0, oParameters, oBoundary.Length, oGlobalParameters.Length);
    for(int i = 0; i < numParameters; i++)
    {
        oParameters[numBoundaries + i] = oGlobalParameters[i];
    }

    //Marshal.Copy(oParameters, 0, par, oParameters.Length);
    for(int i = 0; i < oParaSize; i++)
    {
        par[i] = oParameters[i];
    }

    //Marshal.Copy(CurrentModel.y, 0, u, Math.Min(CurrentModel.y.Length, ndim));

    int nrFloatingSpecies = lModel->getNumFloatingSpecies();
    double* floatCon = new double[nrFloatingSpecies];
    lModel->getFloatingSpeciesConcentrations(nrFloatingSpecies, NULL, floatCon);

    int nMin = min(nrFloatingSpecies, ndim);

    for(int i = 0; i < nMin; i++)
    {
        u[i] = floatCon[i];
    }
    delete [] floatCon;
    return 0;
}


//---------------------------------------------------------------------------
//private int ModelInitializationCallback(int ndim, double t, IntPtr u, IntPtr par)
//        {
//            nDim = ndim;
//
//            int numBoundaries = SelectForm.NumSelectedBoundaries;
//            int numParameters = SelectForm.NumSelectedParameters;
//
//            var oBoundary = new double[numBoundaries];
//            var oGlobalParameters = new double[numParameters];
//
//            if (numBoundaries > 0)
//            {
//                int[] oSelectedBoundary = SelectForm.SelectedBoundarySpecies;
//                for (int i = 0; i < numBoundaries; i++)
//                {
//                    oBoundary[i] = Simulator.getBoundarySpeciesByIndex(oSelectedBoundary[i]);
//                }
//            }
//
//
//            if (numParameters > 0)
//            {
//                int[] oSelectedParameters = SelectForm.SelectedParameters;
//                for (int i = 0; i < numParameters; i++)
//                {
//                    oGlobalParameters[i] = Simulator.getGlobalParameterByIndex(oSelectedParameters[i]);
//                }
//            }
//
//            var oParameters = new double[numBoundaries + numParameters];
//
//            Array.Copy(oBoundary, oParameters, oBoundary.Length);
//            Array.Copy(oGlobalParameters, 0, oParameters, oBoundary.Length, oGlobalParameters.Length);
//
//            Marshal.Copy(oParameters, 0, par, oParameters.Length);
//
//            Marshal.Copy(CurrentModel.y, 0, u, Math.Min(CurrentModel.y.Length, ndim));
//
//            return 0;
//        }

void autoCallConv RRAuto::ModelFunctionCallback(const double* oVariables, const double* par, double* oResult)
{
    int numBoundaries = 0;
    int numParameters = 1;
    ExecutableModel* lModel = mRR->getModel();

    if (numBoundaries > 0)
    {
        vector<double> oBoundary(numBoundaries);
        for(int i = 0; i < numBoundaries; i++)
        {
            oBoundary[i] = par[i];
        }

        vector<int> oSelectedBoundary(1);
        oSelectedBoundary[0] = 0;

        for (int i = 0; i < numBoundaries; i++)
        {
            double val = oBoundary[i];
            mRR->setBoundarySpeciesByIndex(oSelectedBoundary[i], val);
        }

    }

    if (numParameters > 0)
    {
        double* oParameters = new double[numParameters];
//        Marshal.Copy(par, oParameters, numBoundaries, numParameters);
        for(int i = 0; i < numParameters; i ++)
        {
            oParameters[i] = par[i];
        }

        mRR->setValue(mSelectedParameter, oParameters[0]);
//        int[] oSelectedParameters = SelectForm.SelectedParameters;
//        for (int i = 0; i < numParameters; i++)
//        {
//            Simulator.setGlobalParameterByIndex(oSelectedParameters[i],
//                                                (double.IsNaN(oParameters[i])
//                                                     ? oSelectedParameters[i]
//                                                     : oParameters[i]));
//        }
        //delete [] oParameters;
    }
//
//
    static vector<rr::SelectionRecord> selRecs = mRR->getSteadyStateSelections();
    static rr::StringList selList = getRecordsAsStrings(selRecs);
//    vector<string> selList = mRR->getSteadyStateSelections();
//    var variableTemp = new double[CurrentModel.y.Length];

    vector<double> variableTemp(selList.size());
    int ndim = mAutoSetup.mInputConstants.NDIM;
    int nMin = min(selList.size(), ndim);

//    Marshal.Copy(oVariables, variableTemp, 0, Math.Min(CurrentModel.y.Length, nDim));
    for (int i = 0; i < nMin; i++)
    {
        variableTemp[i] = oVariables[i];
    }
    int numFloatingSpecies = lModel->getNumFloatingSpecies();

    {
//        CurrentModel.y = variableTemp;

        double* tempConc = new double[numFloatingSpecies];
        if(!tempConc)
        {
            throw std::runtime_error("Failed to allocate memory in RRAuto ModelFunction CallBack.");
        }

        for(int i = 0; i < numFloatingSpecies; i++)
        {
            if(i < variableTemp.size())
            {
                tempConc[i] = variableTemp[i];
            }
            else
            {
                throw("Big Problem");
            }
        }

        lModel->setFloatingSpeciesConcentrations(numFloatingSpecies, NULL, tempConc);
        delete [] tempConc;
    }

    //PrintArray(CurrentModel.y, Console.Out);
    lModel->convertToAmounts();

    double time         = lModel->getTime();
    int stateVecSize    = lModel->getNumFloatingSpecies() + lModel->getNumRules();
    double* dydts       = new double[stateVecSize];

    lModel->evalModel(time, NULL, dydts);

//    Marshal.Copy(CurrentModel.dydt, 0, oResult, Math.Min(CurrentModel.dydt.Length, nDim));
    nMin = min(stateVecSize, ndim);
    for(int i = 0; i < nMin; i++)
    {
        oResult[i] = dydts[i];
    }
    delete [] dydts;
}

//private void ModelFunctionCallback(IntPtr oVariables, IntPtr par, IntPtr oResult)
//        {
//            int numBoundaries = SelectForm.NumSelectedBoundaries;
//            int numParameters = SelectForm.NumSelectedParameters;
//
//            if (numBoundaries > 0)
//            {
//                var oBoundary = new double[numBoundaries];
//                Marshal.Copy(par, oBoundary, 0, numBoundaries);
//                int[] oSelectedBoundary = SelectForm.SelectedBoundarySpecies;
//                for (int i = 0; i < numBoundaries; i++)
//                {
//                    Simulator.setBoundarySpeciesByIndex(oSelectedBoundary[i],
//                                                        (double.IsNaN(oBoundary[i])
//                                                             ? oSelectedBoundary[i]
//                                                             : oBoundary[i]));
//                }
//            }
//
//            if (numParameters > 0)
//            {
//                var oParameters = new double[numParameters];
//                Marshal.Copy(par, oParameters, numBoundaries, numParameters);
//                int[] oSelectedParameters = SelectForm.SelectedParameters;
//                for (int i = 0; i < numParameters; i++)
//                {
//                    Simulator.setGlobalParameterByIndex(oSelectedParameters[i],
//                                                        (double.IsNaN(oParameters[i])
//                                                             ? oSelectedParameters[i]
//                                                             : oParameters[i]));
//                }
//            }
//
//
//            var variableTemp = new double[CurrentModel.y.Length];
//            Marshal.Copy(oVariables, variableTemp, 0, Math.Min(CurrentModel.y.Length, nDim));
//
//            bool containsNaN = ContainsNaN(variableTemp);
//            if (!containsNaN)
//            {
//                CurrentModel.y = variableTemp;
//            }
//
//            //Console.WriteLine("Eval");
//            //PrintArray(CurrentModel.y, Console.Out);
//
//            CurrentModel.convertToAmounts();
//            CurrentModel.evalModel(CurrentModel.time, CurrentModel.y);
//            //Simulator.oneStep(0.0, 0.01);
//
//            Marshal.Copy(CurrentModel.dydt, 0, oResult, Math.Min(CurrentModel.dydt.Length, nDim));
//
//
//            //PrintArray(CurrentModel.y, Console.Out);
//            //PrintArray(CurrentModel.dydt, Console.Out);
//        }


bool RRAuto::reset()
{
    //Remove temporary files
    return true;
}

} //namespace au
