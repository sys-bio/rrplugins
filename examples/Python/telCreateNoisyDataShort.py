import roadrunner
from rrPlugins_CAPI import *
import rrPlugins as rrp

noisePlugin = rrp.Plugin ("rrp_add_noise")

print noisePlugin.listOfProperties()

# Create a roadrunner instance
rr = roadrunner.RoadRunner()
rr.load("sbml_test_0001.xml")

# Generate data
rr.simulate(0, 10, 511) # Want 512 points

# Get the dataseries from roadrunner
d = rrp.getRoadRunnerData (rr)

# Assign the dataseries to the plugin inputdata
noisePlugin.InputData = d

# Set parameter for the 'size' of the noise
noisePlugin.Sigma = 3.e-5

# Add the noise
noisePlugin.execute ()

# Get the data to plot
numpydata = noisePlugin.InputData.AsNumpy;

rrp.plot (numpydata[:,[0,1]], myColor="blue", myLinestyle="-", myMarker="", myLabel="S1 Fitted")
rrp.show()

d.writeDataSeries ("testData2.dat")

d.readDataSeries ("testData2.dat")
print "done"
