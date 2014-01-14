""" 
Usage:
   python install_telplugins.py
   This file will install files needed to 
   use Tellurium plugins from Python. Specifically, it will install a module named
   telplugins in the systems Python sitepackage folder
"""
import site
import shutil
import os.path
import os

telPackage = 'telplugins'
def rmplugins(path):
    print('deleting ' + telPackage +' from ' + path)

    files = ['telPlugins', 'telPlugins_CAPI', 'telPluginUtils', 'telFindSharedLib']
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
		
    shutil.rmtree(os.path.join(path, telPackage), ignore_errors=True)

splist = site.getsitepackages()
spFolder = ''
	
for s in splist:
    if s.find('site-packages') > 0:
        spFolder = s
    	rmplugins(spFolder)
		
print('installing ' + telPackage +' to site packages dir: ' + spFolder)

destination = os.path.join(spFolder, telPackage)

#Figure out where we are
cwd = os.path.dirname(os.path.abspath(__file__))

src = os.path.abspath(os.path.join(cwd, telPackage))

print('src directory is :' + src)
print("destination directory is: " + destination)

#Copy the content of the module
shutil.copytree(src, destination)

