from telplugins import *

# Create a plugin manager

print 'The plugin manager will look for \
plugins in the following folder: ' + gDefaultPluginsPath

pm = createPluginManager()

# Load plugins from the plugin folder
result = loadPlugins(pm)
if not result:
    print 'Failed to load any plugins'
    print getLastError()
    exit()

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

print `unLoadPlugins(pm)`
print "done"
