CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(TEL_PYTHON_EXAMPLES)


#ROOT folder files
FILE (GLOB plugin_examples *.py)
install(    
FILES README.txt ${plugin_examples}
DESTINATION examples/python 	
COMPONENT examples
)

add_subdirectory(basic)
#add_subdirectory(parameter_minimization)
#add_subdirectory(parameter_minimization/one_parameter)
#add_subdirectory(parameter_minimization/two_parameters)
#add_subdirectory(parameter_minimization/monte_carlo)
#add_subdirectory(parameter_minimization/statistics)

