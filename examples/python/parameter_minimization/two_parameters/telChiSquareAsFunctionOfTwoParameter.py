import numpy as np
import matplotlib.pyplot as plt
import roadrunner
import telplugins as tel

def chiFun(k1,k2):
    rr.reset()
    rr.setValue("k1", k1)
    rr.setValue("k2", k2)          
    data = rr.simulate(timeStart, timeEnd, nrPoints - 1)            
    chiSquare.ModelData = tel.getDataSeries(data)
    
    if not chiSquare.execute():
        raise Exception( tel.getLastError() )
           
    return chiSquare.ReducedChiSquare.getElement(0,1)                   
            
try:
    #Read some 'experimental' data   
    expData = tel.DataSeries()
    
    #This does not look right.. but it works..
    expData = expData.readDataSeries('ExperimentalData.dat')   
            
    sbml_model = 'two_parameters.xml'            

    # Create a roadrunner instance and create some MODEL data
    rr = roadrunner.RoadRunner()
    rr.load(sbml_model)

    #Get chi square plugin and set it up
    chiSquare =  tel.Plugin("tel_chisquare")    
    chiSquare.ExperimentalData = expData    
    chiSquare.NrOfModelParameters = 2
    
    #Simulate using the same numbers as in the 'Experimental data             
    k1Start = 0.4 ;  k1End = 2.5    
    k2Start = 0.4 ;  k2End = 5
    timeStart = 0;  timeEnd = 1.5 ;  nrPoints = 15
             
    X = np.linspace(k1Start, k1End, 125)
    Y = np.linspace(k2Start, k2End, 125)
    nrX = len(X) ; nrY = len(Y)
    print 'nrPoints = ' + `nrX * nrY`
    
    Z = np.zeros([nrX, nrY])            
    for row in range(nrX):    
        for col in range(nrY):
            print 'row,col = ' + `row` + ", " + `col`
            Z[row,col] = chiFun(X[row], Y[col])                                                     
                                
    X, Y = np.meshgrid(X, Y)        
        
    CS = plt.contour(X, Y, Z, 200)
    plt.clabel(CS, inline=1, fontsize=10)        
    plt.title('Reduced ChiSquare for SBML model with two parameters')

    plt.show()                                                
    print "done"

except Exception as e:
    print 'Problem: ' + `e`