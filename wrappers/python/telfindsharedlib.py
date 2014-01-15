import sys
import os.path
from os.path import dirname, split, isdir
import win32api

def getPathToParentFolderOf(fName, extension = None):
    """Get the path to parent folder of file (one dir \'back') """
    x = getPathToFile(fName, extension)
    return os.path.abspath(os.path.join(x, os.pardir))                   
        
def getPathToFile(fName, extension=None):
    """searches fname in PATH dirs"""
    if extension == None:
        extension = 'dll'
    fname2 = fName + "." + extension
    found = look_for(fname2)
    if found: 
        return os.path.dirname(found)
    
def look_for(fname):
    """prints paths for fname where fname can be found"""
    files = []
    path = win32api.GetEnvironmentVariable('PATH')
    
    # try paths as described in MSDN
    dirs = [os.getcwd(), win32api.GetSystemDirectory(), win32api.GetWindowsDirectory()] + path.split(';')
    for d in dirs:
        fname2 = os.path.join(d, fname)
        if os.path.exists(fname2):
            if not fname2 in files:
                files.append(fname2)
    if len(files) > 1:
        print '===== SHARED LIBRARY WARNING: There is more than one: ' + fname + ' on the search path!! ====='                        
    if files:
        #print '\n'.join([f for f in files])        
        #Return the first found path
        return files[0]
    else:
        return None       
                 
