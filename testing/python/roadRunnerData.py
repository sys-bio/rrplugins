import  telplugins_c_api as c


try:
    
    rrDataH = c.createRoadRunnerData(4,2)    
    nrRows = c.getRoadRunnerDataNumRows(rrDataH)
    nrCols = c.getRoadRunnerDataNumCols(rrDataH)
    
    nr = 1
    for row in range(nrRows):        
        for col in range(nrCols):            
            c.setRoadRunnerDataElement(rrDataH, row, col, nr)
            nr = nr + 1            
        
    for row in range(nrRows):        
        for col in range(nrCols):
            val = c.getRoadRunnerDataElement(rrDataH, row, col)
            print '( ' + `val` + ' )'
             
             
## Weights
    if c.hasWeights(rrDataH) is False:
        print 'allocating weights'
        c.allocateWeights(rrDataH)
    
    
    print 'Weights======== '
    for row in range(nrRows):        
        for col in range(nrCols):
            val = c.getRoadRunnerDataWeight(rrDataH, row, col)
            print '( ' + `val` + ' )'
                
        
                        
except Exception as e:
    print 'There was an exception: ' + `e`
        







