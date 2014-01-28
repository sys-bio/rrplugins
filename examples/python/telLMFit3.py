import roadrunner
import matplotlib.pyplot as plt
import scipy.stats as stats
import telplugins as tel
import ctypes as ct

try:
    def pluginIsProgressing(lm):
        lmObject = ct.cast(lm, ct.py_object).value
        print 'Iteration, Norm = ' + `lmObject.getProperty("NrOfIter")` + ',' + `lmObject.getProperty("Norm")` #Retrieve plugin parameters
        
    sbmlModel = "sbml_test_0001.xml" 
    # Create a roadrunner instance and create some data
    rr = roadrunner.RoadRunner()
    rr.load(sbmlModel)    
    data = rr.simulate(0, 10, 15000) # Want 512 points

    #Add noise to the data
    noisePlugin = tel.Plugin ("tel_add_noise")

    # Get the dataseries from data returned by roadrunner
    d = tel.getDataSeries (data)

    # Assign the dataseries to the plugin inputdata
    noisePlugin.InputData = d

    # Set parameter for the 'size' of the noise
    noisePlugin.Sigma = 3.e-6

    # Add the noise
    noisePlugin.execute()
    fName = 'testData3.dat'
    noisePlugin.InputData.writeDataSeries (fName)    
    #===================================================================
    
    lm = tel.Plugin ("tel_lm")
    experimentalData = tel.DataSeries.readDataSeries (fName)    
    #experimentalData = tel.DataSeries.readDataSeries (fName)   
    lm.ExperimentalData = experimentalData;
    lm.SBML = lm.readAllText(sbmlModel)
    
    # Add the parameters that we're going to fit and the initial value
    lm.InputParameterList = ["k1", 0.2]   
    lm.FittedDataSelectionList = "[S1] [S2]"
    lm.ExperimentalDataSelectionList = "[S1] [S2]"
    
    lm.OnProgress (pluginIsProgressing)
    
    # Execute lmfit plugin
    res = lm.execute()
    
    # Get the experimental data as a numpy array
    experimentalData = experimentalData.toNumpy
    
    # Get the fitted and residual data
    fittedData = lm.FittedData.toNumpy
    residuals  = lm.Residuals.toNumpy
    
##    tel.telplugins.plot (fittedData[:,[0,1]], myColor="blue", myLinestyle="-", myMarker="", myLabel="S1 Fitted")
##    tel.telplugins.plot (fittedData[:,[0,2]], myColor="blue", myLinestyle="-", myMarker="", myLabel="S2 Fitted")
##    tel.telplugins.plot (residuals[:,[0,1]], myColor="blue", myLinestyle="None", myMarker="x", myLabel="S1 Residual")
##    tel.telplugins.plot (residuals[:,[0,2]], myColor="red", myLinestyle="None", myMarker="x", myLabel="S2 Residual")
##    tel.telplugins.plot (experimentalData[:,[0,1]], myColor="red", myLinestyle="", myMarker="*", myLabel="S1 Data")
##    tel.telplugins.plot (experimentalData[:,[0,2]], myColor="blue", myLinestyle="", myMarker="*", myLabel="S2 Data")
##    tel.plt.show()
    
    
    residuals = residuals[:,[1,2]]
##    print residuals
##    
##    #Plot as a histogram
    plt.hist(residuals, 50, normed=True)
    plt.show()
##        
    stdResiduals = lm.StandardizedResiduals.toNumpy
    stdResiduals = stdResiduals[:,[1,2]]        
    plt.hist(stdResiduals, 50, normed=True)
    plt.show()
##    
    
except Exception as e:
    print 'Exception: ' + `e`

