import ctypes
import telplugins as tel

#Get a lmfit plugin object
chiPlugin       = tel.Plugin("tel_chisquare")
lm              = tel.Plugin("tel_levenberg_marquardt")
modelPlugin     = tel.Plugin("tel_test_model")
addNoisePlugin  = tel.Plugin("tel_add_noise")

#========== EVENT FUNCTION SETUP ===========================
def pluginIsProgressing(dummy):
    # The plugin don't know what a python object is.
    # We need to cast it here, to a proper python object
    
    print 'Iterations = ' + `lm.getProperty("NrOfIter")` \
        + '\tNorm = ' + `lm.getProperty("Norm")`

try:   
    progressEvent =  tel.NotifyEventEx(pluginIsProgressing)     
    tel.assignOnProgressEvent(lm.plugin, progressEvent)
    #============================================================
    
    #Create model data, with and without noise
    modelPlugin.execute()     
    
    #Retrieve a SBML model from plugin               
    test_model = modelPlugin.Model    
    
    #Setup lmfit properties.
    lm.SBML = test_model
    experimentalData = modelPlugin.TestDataWithNoise
    lm.ExperimentalData = experimentalData
    
    # Add the parameters that we're going to fit and a initial 'start' value
    lm.setProperty("InputParameterList", ["k1", .3])
    lm.setProperty("FittedDataSelectionList", "[S1] [S2]")
    lm.setProperty("ExperimentalDataSelectionList", "[S1] [S2]")
    
    # Start minimization
    lm.execute()
    
    print 'Minimization finished. \n==== Result ===='
    
    print 'Hessian Matrix'
    print lm.getProperty("Hessian")    
     
    print tel.getPluginResult(lm.plugin)
    
    # Get the experimental data as a numpy array
    experimentalData = experimentalData.toNumpy
    
    # Get the fitted and residual data
    fittedData = lm.getProperty ("FittedData").toNumpy
    residuals  = lm.getProperty ("Residuals").toNumpy
    
    tel.telplugins.plot(fittedData         [:,[0,1]], "blue", "-",    "",    "S1 Fitted")
    tel.telplugins.plot(fittedData         [:,[0,2]], "blue", "-",    "",    "S2 Fitted")
    tel.telplugins.plot(residuals          [:,[0,1]], "blue", "None", "x",   "S1 Residual")
    tel.telplugins.plot(residuals          [:,[0,2]], "red",  "None", "x",   "S2 Residual")
    tel.telplugins.plot(experimentalData   [:,[0,1]], "red",  "",     "*",   "S1 Data")
    tel.telplugins.plot(experimentalData   [:,[0,2]], "blue", "",     "*",   "S2 Data")
    tel.telplugins.plt.show()
    
except Exception as e:
    print 'Problem.. ' + `e`         