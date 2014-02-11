import roadrunner
import numpy as np
import matplotlib.pyplot as plt
import telplugins as tel

try:
    #Read some 'experimental' data   
    expData = tel.DataSeries()
    
    #This does not look right.. but it works..
    expData = expData.readDataSeries('ExperimentalData.dat')   
        
    modelPlugin = tel.Plugin("tel_sbml_model")   
    sbml_model  = modelPlugin.Model
    
    # Create a roadrunner instance and create some MODEL data
    rr = roadrunner.RoadRunner()
    rr.load(sbml_model)
    
    #Simulate using the same numbers as in the 'Experimental data
    x = np.array([])
    y = np.array([])     
    for k in np.arange(0.8, 1.3, .01):      
          
        rr.setValue("k1", k)   
        rr.reset() 
        data = rr.simulate(0, 4.5, 200) # Want 512 points
        #roadrunner.plot(data)
    
        #Get chi square
        chiSquare =  tel.Plugin("tel_chisquare")
    
        chiSquare.ExperimentalData = expData
        chiSquare.ModelData = tel.getDataSeries(data)
        chiSquare.NrOfModelParameters = 1
    
        if not chiSquare.execute():
            raise Exception( tel.getLastError() )
               
        redChi = chiSquare.ReducedChiSquare.getElement(0,1)               
        print  'k, chisquare = ' + `k` +', '+  `redChi` 
        x = np.append(x, k) 
        y = np.append(y, redChi)         
    
    plt.plot(x,y, '-o', label="Reduced ChiSquare")
    plt.legend()
    plt.xlabel("k1")
    
    plt.show()
    print "done"

except Exception as e:
    print 'Problem: ' + `e`