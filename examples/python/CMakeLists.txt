CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(TEL_PYTHON_EXAMPLES)


install(    
FILES README.txt 
DESTINATION python_examples 	
COMPONENT plugins_api
)

#Install examples
FILE (GLOB basic_examples basic/*.py)
install(    
FILES ${basic_examples} 
DESTINATION python_examples/basic
COMPONENT plugins_api
)

FILE (GLOB minimization parameter_minimization/*.py)
install(    
FILES ${minimization} 
DESTINATION python_examples/parameter_minimization
COMPONENT plugins_api
)

FILE (GLOB stat statistics/*.py)
install(    
FILES ${stat} 
DESTINATION python_examples/statistics
COMPONENT plugins_api
)



