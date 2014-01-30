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
    data = rr.simulate(0, 10, 5000) # Want 512 points

    print data
    
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
       
    lm.ExperimentalData = experimentalData;
    lm.SBML = lm.readAllText(sbmlModel)
    
    # Add the parameters that we're going to fit and the initial value
    lm.InputParameterList = ["k1", .1]   
    lm.FittedDataSelectionList = "[S1] [S2]"
    lm.ExperimentalDataSelectionList = "[S1] [S2]"
    
    lm.OnProgress (pluginIsProgressing)
    
    # Execute lmfit plugin
    res = lm.execute()
    
    #======== Use the stat plugin to calculate statistics
    stat = tel.Plugin("tel_stat")    
    stat.Residuals = lm.Residuals
    stat.execute()
    
    
    # Get the residuals    
    residuals  = stat.Residuals.toNumpy
    residuals = residuals[:,[1,2]]
    #Plot as a histogram
    plt.hist(residuals, 50, normed=True)
    plt.show()
        
    stdResiduals = stat.StandardizedResiduals.toNumpy
    stdResiduals = stdResiduals[:,[1,2]]            
    plt.hist(stdResiduals, 50, normed=True)
    plt.show()
    

    
    #Plot normal probability plots
    probPlots = stat.NormalProbabilityOfResiduals.toNumpy
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

