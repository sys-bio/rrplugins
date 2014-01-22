import  telplugins as c
import random
 
def printData(telData):
    for row in range(nrRows):
        rowLine = ''        
        for col in range(nrCols):
            if row == 0 and col ==0:
                print colHdr                
            rowLine = rowLine +  `c.getTelluriumDataElement(telDataH, row, col)` + ' '
        print rowLine
    
def printDataWeights(telData):
    for row in range(nrRows):
        rowLine = ''        
        for col in range(nrCols):
            if row == 0 and col ==0:
                print colHdr                
            rowLine = rowLine +  `c.getTelluriumDataWeight(telDataH, row, col)` + ' '
        print rowLine


#=============================================================
try:
    telDataH = c.createTelluriumData(4,2)    
    nrRows = c.getTelluriumDataNumRows(telDataH)
    nrCols = c.getTelluriumDataNumCols(telDataH)
    colHdr = c.getTelluriumDataColumnHeader(telDataH)
    
    #Setup some numbers
    nr = 1.1    
    for row in range(nrRows):        
        for col in range(nrCols):            
            c.setTelluriumDataElement(telDataH, row, col, nr)
            nr = nr + 1            
        
    #Print the data        
    printData(telDataH)             
             
    ## Weights ===================
    if c.hasWeights(telDataH) is False:
        print 'allocating weights'
        c.allocateWeights(telDataH)
        
    print 'Weights======== '
    printDataWeights(telDataH)
                
    #Change weights
    for row in range(nrRows):        
        for col in range(nrCols):           
            randomNr = random.random() 
            c.setTelluriumDataWeight(telDataH, row, col, randomNr)                        
    printDataWeights(telDataH)        
    
    #===== Column header
    print 'ColumnHeader is:' + `c.getTelluriumDataColumnHeader(telDataH)`    
    c.setTelluriumDataColumnHeader(telDataH, 'A,B')
    print 'ColumnHeader is:' + `c.getTelluriumDataColumnHeader(telDataH)`

    #This should fail
    c.setTelluriumDataColumnHeader(telDataH, 'A,B,C')
    print 'ColumnHeader is:' + `c.getTelluriumDataColumnHeader(telDataH)`
    
    c.setTelluriumDataColumnHeaderByIndex(telDataH, 0, 'R')
    print 'ColumnHeader is:' + `c.getTelluriumDataColumnHeader(telDataH)`
    print 'ColumnHeader index 0 is:' + `c.getTelluriumDataColumnHeaderByIndex(telDataH, 0)`
                            
except Exception as e:
    print 'There was an exception: ' + `e`
        







