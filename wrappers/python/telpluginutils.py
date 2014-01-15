import sys
import os.path
from ctypes.util import find_library
from os.path import dirname, split, isdir

def getPathToParentFolderOf(fName, extension = None):
    """Get the path to parent folder of file (one dir \'back') """
    x = find_library(fName)
    x= os.path.dirname(x)
    return os.path.abspath(os.path.join(x, os.pardir))
