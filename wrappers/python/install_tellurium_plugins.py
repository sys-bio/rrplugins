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
    
    print('Installing Tellurium plugins to folder: ' + spFolder)   
    #clean destination folder   
    cleanFolder(spFolder)

    #Figure what to copy        
    currentFolder = os.path.dirname(os.path.abspath(__file__))
    pyFilesFolder = os.path.join(currentFolder, 'site-packages', telPackageName)    
    pyFiles = glob.glob(os.path.join(pyFilesFolder, '*.py'))
    
    #Plugins 
    pluginsFolder = os.path.join(currentFolder,  'plugins')   
    plugins = glob.glob(os.path.join(pluginsFolder, '*.dll'))
                       
    #Copy the dlls that are in ..\bin folder
    #Binaries       
    binFolder = os.path.join(currentFolder, 'bin')   
    bins = glob.glob(os.path.join(binFolder, '*.dll'))
    
       
    rootFiles = pyFiles + bins
    
    if not os.path.exists(spFolder):
        os.makedirs(spFolder)
                    
    #Copy root files
    for file in rootFiles:
        print 'Copying file: ' + file + ' -> ' + spFolder 
        shutil.copy(file, spFolder)
    
    #Copy plugins
    destPluginFolder = spFolder #Copy plugins into the same folder as the other dll's :( os.path.join(spFolder, 'plugins')
    
    if not os.path.exists(destPluginFolder):
        os.makedirs(destPluginFolder)
            
    for file in plugins:
        print 'Copying file: ' + file + ' -> ' + destPluginFolder
        shutil.copy(file, destPluginFolder)
    
except Exception as e:
    print 'There was a problem installing Tellurium plugins: ' + `e`

