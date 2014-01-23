#pragma hdrstop
#include "rr/rrLogger.h"
#include "add_noise.h"
#include "rr/rrRoadRunner.h"
#include "telTelluriumData.h"
#include "noise.h"
#include "add_noise_doc.h"

//---------------------------------------------------------------------------
namespace addNoise
{


AddNoise::AddNoise(rr::RoadRunner* aRR, PluginEvent fn1, PluginEvent fn2, PluginEvent fn3)
:
CPPPlugin(  "AddNoise",                 "Signal Processing",    aRR,    NULL),  //Construct Base
mNoiseType(         ntGaussian,         "NoiseType",   "Type of noise (Gaussian = 0, Psychological = 1)."),
mSigma(             1,                  "Sigma",       "Size of applied noise"),
mData(              TelluriumData(),    "InputData",    "Pointer to TelluriumData to apply noise to"),
mProgress(          0,                  "Progress",     "Indicate progress in (0-100%)"),
mAddNoiseWorker(*this)
{
    mVersion = "1.0";

    //Setup the plugins capabilities
    mProperties.add(&mNoiseType);
    mProperties.add(&mSigma);
    mProperties.add(&mData);

    mProperties.add(&mProgress);

    mHint ="Add Gaussian Noise to RoadRunner Data";
    mDescription="The AddNoise plugin adds Gaussian noise to synthetic data. The amount of noise is controlled \
by the plugins Sigma property. Specifically, noise is generated for each single data value, with a probability corresponding to a Gaussian distribution centered around the value, and with a variance equal to (sigma^2). \
The Plugin accepts Tellurium data as input, in the \"InputData\" property. \
Currently only Gaussian noise is supported. \
The progress of the application of noise can be read in the Progress property. \
Noise will not be generated onto the first column of data, if its column label is equal to \"Time\", (not case sensitive). \
The AddNoise plugin was developed at the University of Washington by Totte Karlsson, 2012-2014.";
}

AddNoise::~AddNoise()
{}

unsigned char* AddNoise::getManualAsPDF() const
{
    return pdf_doc;
}

unsigned int AddNoise::getPDFManualByteSize()
{
    return sizeofPDF;
}

bool AddNoise::isWorking() const
{
    return mAddNoiseWorker.isRunning();
}

bool AddNoise::execute(bool inThread)
{
    Log(lDebug)<<"Executing the AddNoise plugin by Totte Karlsson";

    //go away and carry out the work in a thread
    return mAddNoiseWorker.start(inThread);
}

// Plugin factory function
Plugin* plugins_cc createPlugin()
{
    //allocate a new object and return it
    return new AddNoise;
}

const char* plugins_cc getImplementationLanguage()
{
    return "CPP";
}

}


