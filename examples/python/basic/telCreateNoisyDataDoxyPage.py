import roadrunner
import telplugins as tel

noisePlugin = tel.Plugin ("tel_add_noise")

print noisePlugin.name()
print noisePlugin.hint()
print noisePlugin.description()

print noisePlugin.listOfProperties()
modelPlugin= tel.Plugin("tel_test_model")        
test_model = modelPlugin.Model

# Create a roadrunner instance
rr = roadrunner.RoadRunner()
rr.load(test_model)

# Generate data
data = rr.simulate(0, 10, 511) # Want 512 points

# The plugin will need a handle to the underlying roadrunner data
d = tel.getDataSeries (data)

noisePlugin.InputData = d

# Get parameter for the 'size' of the noise
noisePlugin.Sigma = 1.e-5

noisePlugin.execute ()

noisePlugin.InputData.plot ()
tel.show()

print "done"
