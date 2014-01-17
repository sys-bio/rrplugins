CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(TEL_PYTHON_EXAMPLES)

FILE (GLOB examples *.py)

install(    
FILES ${examples} 
    README.txt 
    testData.dat 
    bistable.xml 
    sbml_test_0001.xml 
    lmFitTestModel.xml
DESTINATION python_examples 	
COMPONENT plugins_api
)

#if(BUILD_TEST_TOOLS)
#install(    
#FILES runAllPythonExamples.sh 
#DESTINATION python_examples 	
#COMPONENT plugins_api
#)
endif()

