#pragma hdrstop
#include "telAutoTelluriumInterface.h"
#include "rr/rrExecutableModel.h"
#include "../libAuto/vsAuto.h"
#include "telLogger.h"
#include "telStringList.h"
#include "telUtils.h"
#include "telAutoUtils.h"

namespace telauto
{
using namespace tlp;
using namespace autolib;

//Statics
RoadRunner*     AutoTellurimInterface::mRR              = NULL;
Properties*     AutoTellurimInterface::mProperties      = NULL;
AutoConstants   AutoTellurimInterface::mAutoConstants;
string          AutoTellurimInterface::mSelectedParameter = gEmptyString;
StringList      AutoTellurimInterface::mModelParameters = StringList();

AutoTellurimInterface::AutoTellurimInterface(RoadRunner* rr)
{
    mRR = rr;
}

AutoTellurimInterface::~AutoTellurimInterface()
{}

void AutoTellurimInterface::assignRoadRunner(RoadRunner* rrInstance)
{
    mRR = rrInstance;
}

void AutoTellurimInterface::assignProperties(Properties* props)
{
    mProperties = props;
    if(mProperties)
    {
        mAutoConstants.populateFrom(mProperties);
    }
    else
    {
        mAutoConstants.reset();
    }
}

bool AutoTellurimInterface::selectParameter(const string& para)
{
    mSelectedParameter = para;
    return false;
}

bool AutoTellurimInterface::setScanDirection(ScanDirection val)
{

    if(val == sdPositive)
    {
        mAutoConstants.DS = fabs(mAutoConstants.DS);
    }
    else
    {
        mAutoConstants.DS = -1 * fabs(mAutoConstants.DS);
    }

    mAutoConstants.mScanDirection = val;
    return true;
}

bool AutoTellurimInterface::setTempFolder(const string& fldr)
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

string AutoTellurimInterface::getTempFolder()
{
    return mTempFolder;
}

bool AutoTellurimInterface::run()
{
    try
    {
        if(!mRR)
        {
            return false;
        }

        //mAutoSetup.mRunContinuation = false;
        double parValue = 0;
        if(mAutoConstants.mScanDirection == sdPositive)
        {
            parValue = mAutoConstants.RL0;
        }
        else
        {
            parValue = mAutoConstants.RL1;
        }

        //Set initial value of Primary continuation parameter
        mRR->setValue(mSelectedParameter, parValue);

//        if(mAutoSetup.mCalculateSteadyState)
//        {
            mRR->steadyState();
//        }

        if(!setupUsingCurrentModel())
        {
            return false;
        }

        CallAuto(getTempFolder());
        return true;
    }
    catch(exception& ex)
    {
        Log(lError) << ex.what();
        throw(Exception(ex.what()));
    }
}

bool AutoTellurimInterface::setupUsingCurrentModel()
{
    int ndim = mRR->getSteadyStateSelections().size();
//    mAutoSetup.mInputConstants.NDIM = ndim;


    mModelParameters = mRR->getGlobalParameterIds();

    setCallbackStpnt(ModelInitializationCallback);
    setCallbackFunc2(ModelFunctionCallback);

    //string temp = mAutoSetup.getConstantsAsString();
    string temp = getConstantsAsString();

    autolib::createFort2File(temp.c_str(), joinPath(getTempFolder(),"fort.2"));
    return true;
}


//Called by Auto
int autoCallConv AutoTellurimInterface::ModelInitializationCallback(long ndim, double t, double* u, double* par)
{
    rr::ExecutableModel* lModel = mRR->getModel();

    int numBoundaries = 0;
    int numParameters = 1;

    vector<double> boundaryValues(numBoundaries);
    vector<double> globalParameters(numParameters);

    if (numBoundaries > 0)
    {
        vector<int> oSelectedBoundary(1);
        oSelectedBoundary[0] = 0;           //ToDo: This need to be set from the outside!
        for (int i = 0; i < numBoundaries; i++)
        {
            boundaryValues[i] = mRR->getBoundarySpeciesByIndex(oSelectedBoundary[i]);
        }
    }

    if (numParameters > 0)
    {
        double val  = mRR->getValue(mSelectedParameter);
//        globalParameters[0] = val;

        for (int i = 0; i < numParameters; i++)
        {
            int selParameter = mModelParameters.indexOf(mSelectedParameter);
            globalParameters[i] = mRR->getGlobalParameterByIndex(selParameter);
        }
    }

    int oParaSize = numBoundaries + numParameters;
    vector<double> parameterValues(oParaSize);

    for(int i = 0; i < numBoundaries; i++)
    {
        parameterValues[i] = boundaryValues[i];
    }

    //Array.Copy(oGlobalParameters, 0, oParameters, oBoundary.Length, oGlobalParameters.Length);
    for(int i = 0; i < numParameters; i++)
    {
        parameterValues[numBoundaries + i] = globalParameters[i];
    }

    //Marshal.Copy(oParameters, 0, par, oParameters.Length);
    for(int i = 0; i < oParaSize; i++)
    {
        par[i] = parameterValues[i];
    }

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

void autoCallConv AutoTellurimInterface::ModelFunctionCallback(const double* oVariables, const double* par, double* oResult)
{
    int numBoundaries = 0;
    int numParameters = 1;
    rr::ExecutableModel* lModel = mRR->getModel();

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
    static tlp::StringList selList = getRecordsAsStrings(selRecs);
//    vector<string> selList = mRR->getSteadyStateSelections();
//    var variableTemp = new double[CurrentModel.y.Length];

    vector<double> variableTemp(selList.size());
//    int ndim = mAutoSetup.mInputConstants.NDIM;
    Property<int>* intProp = dynamic_cast< Property<int>* > (mProperties->getProperty("NDIM"));
    int ndim = intProp->getValue();
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
            throw std::runtime_error("Failed to allocate memory in AutoTellurimInterface ModelFunction CallBack.");
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

    //lModel->evalModel(time, NULL, dydts);
    lModel->getStateVectorRate(time, NULL, dydts);

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


string AutoTellurimInterface::getConstantsAsString()
{
    return mAutoConstants.getConstantsAsString();
}


} //namespace au
