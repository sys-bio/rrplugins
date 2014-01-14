CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(RR_PYTHON_EXAMPLES)

set(examples 	
rrPluginTester.py
#rrBifurcationDemo.py
rrEvents.py
rrPluginDocumentation.py
rrPluginProperties.py
rrPluginPropertyLists.py
rrLevenbergMarquardt.py
rrLevenbergMarquardtShortVersion.py
rrNoisePlugin.py
rrTwoPlugins.py
rrCreateNoisyData.py
rrReadDataFromFile.py
)

install(    
FILES ${examples} README.txt testData.dat sbml_test_0001.xml lmFitTestModel.xml
DESTINATION plugins/Examples 	
COMPONENT plugins_api
)


if(BUILD_TEST_TOOLS)
install(    
FILES runAllPythonExamples.sh 
DESTINATION plugins/Examples 	
COMPONENT plugins_api
)
endif()

