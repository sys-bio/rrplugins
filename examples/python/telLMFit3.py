import roadrunner
import numpy as np
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
    data = rr.simulate(0, 10, 1500) # Want 512 points

    #Add noise to the data
    noisePlugin = tel.Plugin ("tel_add_noise")

    # Get the dataseries from data returned by roadrunner
    d = tel.getDataSeries (data)

    # Assign the dataseries to the plugin inputdata
    noisePlugin.InputData = d

    # Set parameter for the 'size' of the noise
    noisePlugin.Sigma = 3.e-26

    # Add the noise
    noisePlugin.execute()
    fName = 'testData3.dat'
    noisePlugin.InputData.writeDataSeries (fName)    
    
    #===================================================================
    
    lm = tel.Plugin ("tel_lm")
    experimentalData = tel.DataSeries.readDataSeries (fName)    
       
    lm.ExperimentalData = experimentalData;
    lm.SBML = lm.readAllText(sbmlModel)
    
    # Add the parameters that we're going to fit and the initial value
    lm.InputParameterList = ["k1", .1]   
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
##    
##    
##    # Get the fitted and residual data
##    fittedData = lm.FittedData.toNumpy
##    residuals  = lm.Residuals.toNumpy       
##    residuals = residuals[:,[1,2]]
##    
##    #Plot as a histogram
##    plt.hist(residuals, 50, normed=True)
##    plt.show()
##        
    stdResiduals = lm.StandardizedResiduals.toNumpy
    stdResiduals = stdResiduals[:,[1,2]]            
    plt.hist(stdResiduals, 50, normed=True)
    plt.show()
    
    lm.StandardizedResiduals = tel.DataSeries.fromNumPy(stdResiduals)
    
    #Plot normal probability plots
    probPlots = lm.NormalProbabilityOfResiduals.toNumpy
    print probPlots
    
    x1 = probPlots[:,[0]]
    y1 = probPlots[:,[1]]    
        
    x2 = probPlots[:,[2]]
    y2 = probPlots[:,[3]]    
    
    lineX = np.arange(-5, 5, .1)
    lineY = lineX
    plt.plot(lineX, lineY, '-r')         
    plt.plot(x1,y1, 'o')
    plt.plot(x2,y2, 'x')    
    #plt.scatter(x,y)    
    plt.show()
        
except Exception as e:
    print 'Exception: ' + `e`

