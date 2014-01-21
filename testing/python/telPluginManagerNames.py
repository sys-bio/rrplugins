import roadrunner
import telplugins as tel

try:    
    for i in range(1):
        noisePlugin = tel.Plugin ("tel_add_noise")    
        print noisePlugin.listOfPlugins()

    if tel.tpc.hasLoadPluginErrors(tel._pluginManager):
        print tel.tpc.getPluginLoadErrors(tel._pluginManager)    
except Exception as e:
    print 'Problem: ' + `e`