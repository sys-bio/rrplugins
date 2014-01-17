from telplugins import *

try:    
    # Create a plugin manager
    pm = createPluginManager()
        
    # Load plugins from the plugin folder
    result = loadPlugins(pm)
    
    print 'Number of Plugins: ' + `getNumberOfPlugins(pm)`
    print 'Plugin Names: ' + `getPluginNames(pm)`
    
    #Go trough all plugins and print information
    aPlugin = getFirstPlugin(pm)
    while True:
        if aPlugin == None:
            break            
        print '=========================================='
        print 'PluginName: ' + `getPluginName(aPlugin)`
        print 'Plugin Description: \n'
        print getPluginDescription(aPlugin)
        print '\nPluginParameters: ' + `getListOfPluginPropertyNames(aPlugin)`                    
        
        #get next plugin
        aPlugin = getNextPlugin(pm)
    
    unLoadPlugins(pm)    
    
except Exception as e:
    print 'There was a problerm: ' + `e`    
