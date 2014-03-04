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

FILE (GLOB minimization_1 parameter_minimization/one_parameter/*.py)
install(    
FILES ${minimization_1} 
DESTINATION python_examples/parameter_minimization/one_parameter
COMPONENT plugins_api
)

FILE (GLOB minimization_2 parameter_minimization/two_parameters/*.py)
install(    
FILES ${minimization_2} 
DESTINATION python_examples/parameter_minimization/two_parameters
COMPONENT plugins_api
)

FILE (GLOB minimization_3 parameter_minimization/monte_carlo/*.py)
install(    
FILES ${minimization_3} 
DESTINATION python_examples/parameter_minimization/monte_carlo
COMPONENT plugins_api
)

FILE (GLOB stat statistics/*.py)
install(    
FILES ${stat} 
DESTINATION python_examples/statistics
COMPONENT plugins_api
)



