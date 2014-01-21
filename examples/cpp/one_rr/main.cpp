#include <iostream>

#include "rr/rrRoadRunner.h"
#include "rr/rrException.h"
#include "rr/rrUtils.h"
#include "rr/rrLogger.h"
#include "rr/C/rrc_api.h"
#include "telplugins_c_api.h"
using namespace rr;
using namespace rrc;
using namespace tlpc;
using namespace std;
int main(int argc, char** argv)
{
    const char* rootPath = "..";

    try
    {
        gLog.setLevel(lInfo);
        string tmpFolder = joinPath(rootPath, "temp");

        const string modelFile = joinPath(rootPath, "models", "sbml_test_0001.xml");

        
        RoadRunner rr1("", tmpFolder);
        LoadSBMLOptions opt;

        //opt.modelGeneratorOpt |= LoadSBMLOptions::RECOMPILE;
        
        if(!rr1.load(modelFile, &opt))
        {
            Log(Logger::LOG_ERROR)<<"There was a problem loading model in file: "<<modelFile;
            throw(Exception("Bad things in loadSBMLFromFile function"));
        }

        SimulateOptions  simOpt;
        simOpt.start = 0;
        simOpt.start = 10;
        simOpt.steps= 511;

        
        rr1.simulate(&simOpt);

        rrc::RRDataHandle dataHandle = getTelluriumDataHandle(&rr1);

        int nrRows = getTelluriumDataNumRows(dataHandle);
        int nrCols = getTelluriumDataNumCols(dataHandle);
        char* colHeader = getTelluriumDataColumnHeader(dataHandle);

        cout<<"NrRows: "<<nrRows<<endl;
        cout<<"NrCols "<<nrCols<<endl;
        cout<<"Headaer: "<<colHeader<<endl;
        //for(int row = 0; row < nrRows; row++)
        //{
        //    cout<<"row: "<<row<<"\t";
        //    for(int col = 0; col < nrCols; col++)
        //    {
        //        double value;    
        //        //getTelluriumDataElement(dataHandle, row, col, &value);
        //        //cout<<value<<"\t";            
        //    }
        //    cout<<endl;
        //}

    }
    catch(const Exception& ex)
    {

        Log(Logger::LOG_ERROR)<<"There was a  problem: "<<ex.getMessage();
    }

    return 0;
}




