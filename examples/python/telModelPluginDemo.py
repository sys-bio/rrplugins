import roadrunner
import telplugins as tel

try:
    modelPlugin= tel.Plugin("tel_sbml_model")
    print tel.getLastError()
    
    sbml_model = modelPlugin.Model
    
    # Create a roadrunner instance and create some data
    rr = roadrunner.RoadRunner()
    rr.load(sbml_model)    
    data = rr.simulate(0, 10, 511) # Want 512 points

    roadrunner.plot(data)           
    print "done"

except Exception as e:
    print 'Problem: ' + `e`