import roadrunner

try:
    sbmlModel = "sbml_test_0001.xml" 
    # Create a roadrunner instance and create some data
    rr = roadrunner.RoadRunner()
    rr.load(sbmlModel)    
    data = rr.simulate(0, 50, 50) # Want 512 points
    print data
            
except Exception as e:
    print 'Exception: ' + `e`

