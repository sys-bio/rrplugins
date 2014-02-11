import roadrunner
import telplugins as tel

try:
    #Read some 'experimental' data   
    expData = tel.DataSeries()
    
    #This does not look right.. but it works..
    expData = expData.readDataSeries('ExperimentalData.dat')   
    expData.plot()
    
    modelPlugin = tel.Plugin("tel_sbml_model")   
    sbml_model  = modelPlugin.Model
    
    # Create a roadrunner instance and create some MODEL data
    rr = roadrunner.RoadRunner()
    rr.load(sbml_model)
    
    #Simulate using the same numbers as in the 'Experimental data    
    data = rr.simulate(0, 4.5, 200) # Want 512 points

    roadrunner.plot(data)
    
    #Get chi square
    chiSquare =  tel.Plugin("tel_chisquare")
    
    chiSquare.ExperimentalData = expData
    chiSquare.ModelData = tel.getDataSeries(data)
    chiSquare.NrOfModelParameters = 1
    
    if not chiSquare.execute():
        raise Exception( tel.getLastError() )
    
    print chiSquare.ChiSquare.cols
    print chiSquare.ChiSquare.rows
    print chiSquare.ChiSquare.getElement(0,1)
    print chiSquare.ReducedChiSquare.getElement(0,1)        
    
    print "done"

except Exception as e:
    print 'Problem: ' + `e`