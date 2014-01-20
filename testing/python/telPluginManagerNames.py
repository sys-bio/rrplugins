import roadrunner
import telplugins as tel

try:
    for i in range(1):
        noisePlugin = tel.Plugin ("tel_add_noise")    
        print noisePlugin.listOfPlugins()
    
except Exception as e:
    print 'Problem: ' + `e`