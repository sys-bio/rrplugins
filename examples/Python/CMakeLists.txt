CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(RR_PYTHON_EXAMPLES)

set(examples 	
telPluginTester.py
telBifurcation.py
telEvents.py
telPluginDocumentation.py
telPluginProperties.py
telPluginPropertyLists.py
telLevenbergMarquardt.py
telLevenbergMarquardtShortVersion.py
telNoisePlugin.py
telTwoPlugins.py
telCreateNoisyData.py
telReadDataFromFile.py
)

install(    
FILES ${examples} README.txt testData.dat sbml_test_0001.xml lmFitTestModel.xml
DESTINATION python_examples 	
COMPONENT plugins_api
)


if(BUILD_TEST_TOOLS)
install(    
FILES runAllPythonExamples.sh 
DESTINATION python_examples 	
COMPONENT plugins_api
)
endif()

