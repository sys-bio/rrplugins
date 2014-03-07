import roadrunner
import telplugins as tel

try:
    #Retrieve a SBML model from plugin        
    modelPlugin= tel.Plugin("tel_test_model")        
    test_model = modelPlugin.Model
    
    # Create a roadrunner instance and create some data
    rr = roadrunner.RoadRunner()
    rr.load(test_model)    
    data = rr.simulate(0, 10, 511) # Want 512 points

    roadrunner.plot(data)           
    print "done"

except Exception as e:
    print 'Problem: ' + `e`