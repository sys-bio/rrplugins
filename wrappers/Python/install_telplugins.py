""" 
Usage:
   python install_rrplugins.py
   This file will install files needed to 
   use roadrunner plugins from Python. Specifically, it will install a module named
   rrplugins in the systems Python sitepackage folder
"""
import site
import shutil
import os.path
import os

rrPackage = 'rrplugins'
def rmrrplugins(path):
    print('deleting ' + rrPackage +' from ' + path)

    files = ['rrPlugins', 'rrPlugins_CAPI', 'rrPluginUtils', 'rrFindSharedLib']
    for file in files:
        try:
            fName = file + '.py'
            os.remove(os.path.join(path, fName))
        except:
		  pass	
        
    for file in files:
        try:        
            fName = file + '.pyd'
            os.remove(os.path.join(path, fName))
        except:
		  pass
		
    shutil.rmtree(os.path.join(path, rrPackage), ignore_errors=True)

splist = site.getsitepackages()
spFolder = ''
	
for s in splist:
    if s.find('site-packages') > 0:
        spFolder = s
    	rmrrplugins(spFolder)
		
print('installing ' + rrPackage +' to site packages dir: ' + spFolder)

destination = os.path.join(spFolder, rrPackage)

#Figure out where we are
cwd = os.path.dirname(os.path.abspath(__file__))

src = os.path.abspath(os.path.join(cwd, rrPackage))

print('src directory is :' + src)
print("destination directory is: " + destination)

#Copy the content of the module
shutil.copytree(src, destination)

