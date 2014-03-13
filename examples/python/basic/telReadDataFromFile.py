from telplugins import *

try:    
    #Make sure the file testData.dat exists 
    #You can generate a testData.dat file by executing the telCreateNoisyData.py example script
    dataSeries =  DataSeries.readDataSeries("testData.dat")    
    dataSeries.plot()           
    
    print "done"
except Exception as e:
    print 'Exception: ' + `e`
