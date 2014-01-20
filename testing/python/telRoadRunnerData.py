import  telplugins as c
 

try:
    
    rrDataH = c.createRoadRunnerData(4,2)    
    nrRows = c.getRoadRunnerDataNumRows(rrDataH)
    nrCols = c.getRoadRunnerDataNumCols(rrDataH)
    colHdr = c.getRoadRunnerDataColumnHeader(rrDataH)
    
    nr = 1
    
    for row in range(nrRows):        
        for col in range(nrCols):            
            c.setRoadRunnerDataElement(rrDataH, row, col, nr)
            nr = nr + 1            
        
    #Print the data        
    for row in range(nrRows):
        rowLine = ''        
        for col in range(nrCols):
            if row == 0 and col ==0:
                print colHdr
                
            rowLine = rowLine +  `c.getRoadRunnerDataElement(rrDataH, row, col)` + ' '
        print rowLine
             
             
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
        







