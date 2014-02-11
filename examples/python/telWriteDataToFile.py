import roadrunner
from telplugins import *

try:
    # Create a roadrunner instance and create some data
    rr = roadrunner.RoadRunner()
    rr.load("sbml_test_0001.xml")    
    data = rr.simulate(0, 4.5, 200)

    #Add some noise to the data
    noisePlugin = Plugin ("tel_add_noise")

    # Get the dataseries from data returned by roadrunner
    d = getDataSeries (data)

    # Assign the dataseries to the plugin inputdata
    noisePlugin.InputData = d

    # Set parameter for the 'size' of the noise
    sigma = 1e-6
    noisePlugin.Sigma = sigma
        
    # Add the noise
    noisePlugin.execute()

    # Get the data to plot
    theData = noisePlugin.InputData
    theData.plot()
            
    # Need to add weight stuff to DataSeries class?            
    dataHandle = theData._data
    if not hasWeights(dataHandle):
        allocateWeights(dataHandle)
                    
    #Populate weights, using the sigma above
    hdrs = list(theData.getColumnHeaders().split(','))
    
    for c in range(theData.cols):
        for r in range(theData.rows):    
            if hdrs[c].lower() != "Time".lower():
                weight = theData.getWeight(r,c)
                theData.setWeight(r,c, sigma * sigma)                
    
    noisePlugin.InputData.writeDataSeries("myExperimentalData.dat")
    print "done"

except Exception as e:
    print 'Problem: ' + `e`
