from telplugins import *

try:  
    sbmlModel ="bistable.xml"
    sbmlModel ="BIOMD0000000203.xml"                       
    
    #Get an auto2000 plugin object
    auto = Plugin("tel_auto2000")
          
    #Load Auto plugin
    if not auto.plugin:
        print 'LastError: ' + getLastError()
        exit()
    
    info = getPluginInfo(auto.plugin)
    if info == None:
        print getLastError()
        
    print auto.listOfPropertyNames()
    
    #Set Auto Propertys
    #auto.setProperty("ScanDirection", "Negative")
    auto.setProperty("ScanDirection", "Positive")    
    auto.setProperty("SBML", readAllText(sbmlModel))
        
    #True for debugging
    auto.setProperty("KeepTempFiles", True)
    auto.setProperty("PrincipalContinuationParameter", "A")
    auto.setProperty("PCPLowerBound", 10)
    auto.setProperty("PCPUpperBound", 100)
    auto.setProperty("NMX", 5000)  
           
    #Execute the plugin
    auto.execute()
    
    #Get some info 
    # =Bifurcation summary
    print "Summary: " + auto.BiFurcationSummary
    
    pts = auto.BiFurcationPoints
    lbls = auto.BiFurcationLabels
    biData = auto.BiFurcationData
    
    biData.writeDataSeries('r:/temp/autoData.dat')
    
    biDataHdrs = biData.getColumnHeaders()
        
    print pts
    print lbls
    biData.plotBiFurcationDiagram(pts, lbls) 
    
    #print 'Bifurcation Diagram ========================' 
    #print auto.BiFurcationDiagram
    
    print "done"

except Exception as e:
    print "There was a problem: " + `e`
