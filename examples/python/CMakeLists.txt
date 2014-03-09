CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(TEL_PYTHON_EXAMPLES)

FILE (GLOB plugin_examples *.py)

install(    
FILES README.txt ${plugin_examples}
DESTINATION examples/python 	
COMPONENT examples
)

#Install examples
FILE (GLOB basic_examples basic/*.py)
install(    
FILES ${basic_examples} 
DESTINATION examples/python/basic
COMPONENT examples
)

FILE (GLOB minimization parameter_minimization/*.py)
install(    
FILES ${minimization} 
DESTINATION examples/python/parameter_minimization
COMPONENT examples
)

FILE (GLOB minimization_1 parameter_minimization/one_parameter/*.py)
install(    
FILES ${minimization_1} 
DESTINATION examples/python/parameter_minimization/one_parameter
COMPONENT examples
)

FILE (GLOB minimization_2 parameter_minimization/two_parameters/*.py)
install(    
FILES ${minimization_2} 
DESTINATION examples/python/parameter_minimization/two_parameters
COMPONENT examples
)

FILE (GLOB minimization_3 parameter_minimization/monte_carlo/*.py)
install(    
FILES ${minimization_3} 
DESTINATION examples/python/parameter_minimization/monte_carlo
COMPONENT examples
)

FILE (GLOB stat statistics/*.py)
install(    
FILES ${stat} 
DESTINATION examples/python/statistics
COMPONENT examples
)
