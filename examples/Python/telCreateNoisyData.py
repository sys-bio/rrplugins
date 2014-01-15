import roadrunner
import telplugins as tel

try:
    noisePlugin = tel.Plugin ("tel_add_noise")
    
    print noisePlugin.listOfProperties()
    
    # Create a roadrunner instance
    rr = roadrunner.RoadRunner()
    rr.load("sbml_test_0001.xml")
    
    # Generate data
    rr.simulate(0, 10, 511) # Want 512 points
    
    # The plugin will need a handle to the underlying roadrunner data
    d = tel.getRoadRunnerData (rr)
    
    noisePlugin.InputData = d
    
    # Get parameter for the 'size' of the noise
    noisePlugin.Sigma = 3.e-5
    
    noisePlugin.execute ()
    
    numpydata = noisePlugin.InputData.AsNumpy;
    
    data = numpydata[:,[0,2]]
    tel.telplugins.plot (data, myColor="blue", myLinestyle="-", myMarker="", myLabel="S1")
    
    tel.show()
    
    d.writeDataSeries ("testData2.dat")
    
    d.readDataSeries ("testData2.dat")
    print "done"
    
except Exception as e:
    print 'Exception: ' + `e`