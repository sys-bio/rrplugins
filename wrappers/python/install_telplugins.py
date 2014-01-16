""" 
Usage:
   python install_telplugins.py
   This file will install files needed to 
   use Tellurium plugins from Python. Specifically, it will install a module named
   telplugins in the systems Python sitepackage folder and needed dlls and plugin dlls as well
"""
import site
import shutil
import os.path
import os
import glob

DEBUG = 1

def getSitePackagesFolder():
    splist = site.getsitepackages()
    for s in splist:
        if s.find('site-packages') > 0:
            return s

def cleanFolder(path):
    print('Removing folder ' + path)
    shutil.rmtree(path, ignore_errors=True)
   
#============================= 
#Get sitepackages folder
try:
    telPackageName = 'telplugins'
    spFolder = os.path.join(getSitePackagesFolder(), telPackageName)
    if DEBUG: print "spFolder " + spFolder
    
    #clean the folder   
    cleanFolder(spFolder)
    		
    print('Installing Tellurium plugins to folder: ' + spFolder)   
    
    #Figure what to copy        
    currentFolder = os.path.dirname(os.path.abspath(__file__))
    if DEBUG: print "currentFolder " + currentFolder
    pyFilesFolder = os.path.join(currentFolder, telPackageName)
    if DEBUG: print "pyFilesFolder " + pyFilesFolder
    
    pyFiles = glob.glob(os.path.join(pyFilesFolder, '*.py'))
    if DEBUG: print "pyFiles " + str(pyFiles)
                       
    #Copy the dlls that are in ..\bin folder
    #Assume we are installing from a 'release'       
    binFolder = os.path.join(os.path.split(currentFolder)[0],'bin')   
    if DEBUG: print "binFolder " + binFolder
    bins = glob.glob(os.path.join(binFolder, '*.dll'))
    if DEBUG: print "bins " + str(bins)
    
    #Copy the plugins 
    pluginsFolder = os.path.join(os.path.split(currentFolder)[0],'plugins')   
    if DEBUG: print "pluginsFolder " + pluginsFolder
    plugins = glob.glob(os.path.join(pluginsFolder, '*.dll'))
    if DEBUG: print "plugins " + str(plugins)
       
    rootFiles = pyFiles + bins
    
    if not os.path.exists(spFolder):
        os.makedirs(spFolder)
                    
    #Copy root files
    for file in rootFiles:
        print 'Copying file: ' + file + ' -> ' + spFolder 
        shutil.copy(file, spFolder)
    
    #Copy plugins
    destPluginFolder = os.path.join(spFolder, 'plugins')
    if DEBUG: print "destPluginFolder " + destPluginFolder
    
    if not os.path.exists(destPluginFolder):
        os.makedirs(destPluginFolder)
            
    for file in plugins:
        print 'Copying file: ' + file + ' -> ' + destPluginFolder
        shutil.copy(file, destPluginFolder)
    
except Exception as e:
    print 'There was a problem installing Tellurium plugins: ' + `e`

