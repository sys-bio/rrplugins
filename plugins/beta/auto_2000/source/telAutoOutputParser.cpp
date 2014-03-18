#pragma hdrstop
#include "telAutoOutputParser.h"
#include "telTelluriumData.h"
#include "telUtils.h"
#include "telLogger.h"
//---------------------------------------------------------------------------

AutoOutputParser::AutoOutputParser(const string& input)
:
mBiFurcationDiagram(input)
{

}

AutoOutputParser::~AutoOutputParser()
{}

//    //Parse the bifurcation diagram and get the special points
//    StringList diagram(splitString(mTheHost.mBiFurcationDiagram.getValue(),"\n"));
//    StringList& labeledPoints =  *((StringList*) mTheHost.mLabeledSolutionPoints.getValueAsPointer());
//    for(int i = 0; i < diagram.size(); i++)
//    {
//        string line = trim(diagram[i]);
//
//        //Process lines starting with a '1'
//        if(line.size() && line[0] == '1')
//        {
//            StringList dataRecord = splitString(line, " ");
//            //look for special points, i.e. third record not being 0 or 4
//            if(dataRecord.size() > 4)
//            {
//                if(     dataRecord[2] == "1" ||
//                        dataRecord[2] == "2" ||
//                        dataRecord[2] == "3" ||
//                        dataRecord[2] == "5" ||
//                        dataRecord[2] == "6" ||
//                        dataRecord[2] == "7" ||
//                        dataRecord[2] == "8" ||
//                        dataRecord[2] == "-9"
//                    )
//                {
//                 //We have a special point. Add the whole line
//                 labeledPoints.add(line);
//                }
//            }
//        }
//    }


