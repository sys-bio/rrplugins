import roadrunner
import telplugins as tel

##================
## Running this script in a internal python engine session causes a CRASH after a few iterations
## Running in remote session seem to be ok..
##===============

# Create a roadrunner instance
rr = roadrunner.RoadRunner()
rr.load("sbml_test_0001.xml")

# Generate data
rr.simulate(0, 10, 511) # Want 512 points

### Get the dataseries from roadrunner
d = tel.getRoadRunnerData (rr)

