import os
import roadrunner
import matplotlib.pyplot as plot
import numpy
import ctypes
from rrplugins import *

#Create a plugin manager
pm = createPluginManager()

def pluginStarted():
    print 'The plugin was started'

def pluginIsProgressing(val):
    pluginHandle = cast(val, ctypes.py_object).value    
    prop = getPluginProperty(pluginHandle, "Progress")
    print '\nPlugin progress:' + `getPropertyValue(prop)` +' %'

def pluginIsFinished():
    print 'The plugin did finish'

try:
    #Create a roadrunner instance
    rr = roadrunner.RoadRunner()
    
    #Check if model file exists
    sbmlModel ="../../models/bistable.xml"
    if os.path.exists(sbmlModel):
        model = open(sbmlModel, 'r').read()
        rr.load(model)
    else:
        print "The sbml model file: " + sbmlModel +" can't be found"
        exit()
    
    timeStart = 0
    timeEnd = 10
    numPoints = 500
    rr.simulate(timeStart, timeEnd, numPoints)
    
    #Load the 'noise' plugin in order to add some noise to the data
    pluginHandle = loadPlugin(pm, "rrp_add_noise")
    
    print getPluginInfo(pluginHandle)
    
    #get parameter for noise 'size'
    sigmaHandle = getPluginProperty(pluginHandle, "Sigma")
    
    aSigma = getPropertyValueAsString(sigmaHandle)
    print 'Current sigma is ' + aSigma
    
    #set size of noise
    setProperty(sigmaHandle, 0.02)
    
    cb_func1 =  NotifyEvent(pluginStarted)
    assignOnStartedEvent(pluginHandle,  cb_func1)
    
    progressEvent =  NotifyEventEx(pluginIsProgressing)
    
    #The ID of the plugin is passed as the last argument in the assignOnProgressEvent. 
    #The plugin ID is later on retrieved in the plugin Event handler, see above
    theId = id(pluginHandle)
    assignOnProgressEvent(pluginHandle, progressEvent, theId)
       
    cb_func3 =  NotifyEvent(pluginIsFinished)
    assignOnFinishedEvent(pluginHandle, cb_func3)
    
    #Assign data to the plugin
    pluginData = getPluginProperty(pluginHandle,"InputData")
    setProperty(pluginData, getRoadRunnerDataHandle(rr))
    
    #Execute the noise plugin which will add some noise to the (internal) data
    executePluginEx(pluginHandle)
    
    #Retrieve data from plugin
    
    rrData = getNumpyData(getProperty(pluginData))
    colNames = getRoadRunnerDataColumnHeader(getProperty(pluginData))
    plotRoadRunnerData(rrData, colNames)
    unLoadPlugins(pm)
    unLoadAPI()
    print "done"
    
except Exception as e:    
    print 'Exception: ' + `e`    