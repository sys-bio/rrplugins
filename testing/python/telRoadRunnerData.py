import  telplugins as c
 

try:
    
    rrDataH = c.createTelluriumData(4,2)    
    nrRows = c.getTelluriumDataNumRows(rrDataH)
    nrCols = c.getTelluriumDataNumCols(rrDataH)
    colHdr = c.getTelluriumDataColumnHeader(rrDataH)
    
    nr = 1
    
    for row in range(nrRows):        
        for col in range(nrCols):            
            c.setTelluriumDataElement(rrDataH, row, col, nr)
            nr = nr + 1            
        
    #Print the data        
    for row in range(nrRows):
        rowLine = ''        
        for col in range(nrCols):
            if row == 0 and col ==0:
                print colHdr
                
            rowLine = rowLine +  `c.getTelluriumDataElement(rrDataH, row, col)` + ' '
        print rowLine
             
             
## Weights
    if c.hasWeights(rrDataH) is False:
        print 'allocating weights'
        c.allocateWeights(rrDataH)
    
    
    print 'Weights======== '
    for row in range(nrRows):        
        for col in range(nrCols):
            val = c.getTelluriumDataWeight(rrDataH, row, col)
            print '( ' + `val` + ' )'
                
        
                        
except Exception as e:
    print 'There was an exception: ' + `e`
        







