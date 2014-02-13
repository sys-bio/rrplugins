import roadrunner
import telplugins as tel
import matplotlib.pyplot as plt

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
    data = rr.simulate(0, 10, 14) 

    #roadrunner.plot(data)
    
    #Get chi square
    chiPlugin =  tel.Plugin("tel_chisquare")
    
    chiPlugin.ExperimentalData = expData
    chiPlugin.ModelData = tel.getDataSeries(data)
        
    #Plot Experimental data
    exNP = chiPlugin.ExperimentalData.toNumpy
    x1 = exNP[:,[0]];    y1 = exNP[:,[1]];   y2 = exNP[:,[2]]    
    plt.plot(x1,y1, 'o', x1, y2, 'o')        
        
    
    #Simulated data
    model = chiPlugin.ModelData.toNumpy
    x1 = model[:,[0]];    y1 = model[:,[1]];   y2 = model[:,[2]]    
    plt.plot(x1,y1, '-r', x1, y2, '-b')        
    plt.show()    
    
      
    chiPlugin.NrOfModelParameters = 1
    
    if not chiPlugin.execute():
        raise Exception( tel.getLastError() )

    
    print chiPlugin.ChiSquare.cols
    print chiPlugin.ChiSquare.rows
    print chiPlugin.ChiSquare.getElement(0,1)
    print chiPlugin.ReducedChiSquare.getElement(0,1)        
    #
    print "done"

except Exception as e:
    print 'Problem: ' + `e`