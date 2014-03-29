#-------------------------------------------------------------------------------
# Purpose: Example demonstrating how to setup and use the TestModel plugin
# This example also shows how to plot data and how to view a plugins 
# embedded manual 
#
# Author: Totte Karlsson (totte@dunescientific.com)
#-------------------------------------------------------------------------------
import teplugins as tel

try:    
    modelPlugin = tel.Plugin("tel_test_model")            
    
    #Test model plugin depends on the add_noise plugin
    noisePlugin = tel.Plugin("tel_add_noise")
    
    #Generate internal test data
    modelPlugin.execute()
    test_data = modelPlugin.TestData
    test_data_with_noise = modelPlugin.TestDataWithNoise
        
    test_data.plot()
    test_data_with_noise.plot()
        
    #modelPlugin.viewManual()   
    print 'Plugin version: ' + `modelPlugin.getVersion()`
             
except Exception as e:
    print 'Problem: ' + `e`