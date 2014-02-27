from telplugins import *

try:  
    sbmlModel ="bistable.xml"                   
    
    #Get an auto2000 plugin object
    auto = Plugin("tel_auto2000")
          
    #Load Auto plugin
    if not auto.plugin:
        print 'LastError: ' + getLastError()
        exit()
    
    info = getPluginInfo(auto.plugin)
    if info == None:
        print getLastError()
        
    print auto._propertyNames
    #Set Auto Propertys
    auto.setProperty("ScanDirection", "Negative")
    auto.setProperty("SBML", readAllText(sbmlModel))
        
    #True for debugging
    auto.setProperty("KeepTempFiles", True)
    auto.setProperty("PrincipalContinuationParameter", "k3")
    auto.setProperty("PCPLowerBound", 0.1)
    auto.setProperty("PCPUpperBound", 1.2)  
           
    #Execute the plugin
    auto.execute()
    
    print 'Bifurcation Diagram ========================' 
    print auto.BiFurcationDiagram
    
    print "done"

except Exception as e:
    print "There was a problem: " + `e`
