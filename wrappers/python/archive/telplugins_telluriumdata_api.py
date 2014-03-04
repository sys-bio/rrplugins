##@Module telPlugins_roadrunnerdata_api
#This module give access to roadrunnerdata functions"""
import os
import sys
import numpy as np
import roadrunner
import tempfile
import time
from ctypes import *
import matplotlib.pyplot as plot
from telpluginutils import *

"""
CTypes Python Bindings to the TelluriumData API.
"""
__version__ = "0.8.0"

# Get folder of where the shared library is installed and construct an absolute path to
sharedLib='telplugins_c_api'

telLib=None
try:
    if sys.platform.startswith('win32'):
        sharedLib = sharedLib + '.dll'
        telLib=CDLL(sharedLib)
    elif sys.platform.startswith('Linux'):
        sharedLib = sharedLib + '.a'
        telLib = cdll.LoadLibrary(sharedLib)
except:
    print 'ERROR: Unable to locate shared library: ' + sharedLib
    exit()


## \brief Retrieve a handle to RoadRunners internal data object
## \param rrInstance A RoadRunner instance, as returned from roadrunner.RoadRunner()
## \return Returns a handle to roadrunners internal data object
## \ingroup utilities
def getTelluriumDataHandle(rrInstance):
    rrHandle = cast(int(rrInstance.this), c_void_p)
    return telLib.getTelluriumDataHandle(rrHandle)

## \brief Get column header in roadrunner data
## \param rrDataHandle A handle to a roadrunner data object
## \return Returns a numpy data object
## \ingroup utilities

telLib.getTelluriumDataColumnHeader.restype = c_char_p
def getTelluriumDataColumnHeader(rrDataHandle):
    hdr = telLib.getTelluriumDataColumnHeader(rrDataHandle)

    if hdr:
        res = hdr
        telLib.freeText(hdr)
        return res.split(',')
    else:
        return None

## \brief Write TelluriumData to a file
## \param rrDataHandle A handle to roadunnerdata
## \param fName Name of output file, including path. If no path is given, the file is written to the
## current working directory
## \return Returns True or false indicating result
## \ingroup utilities
telLib.writeTelluriumDataToFile.restype = c_bool
def writeTelluriumData(rrDataHandle, fName):
    return telLib.writeTelluriumDataToFile(rrDataHandle, fName)

## \brief Read TelluriumData from a file
## \param rrDataHandle A handle to roadunnerdata
## \param fName Name of input file, including path. If no path is given, the file is read
## in current working directory
## \return Returns True or false indicating result
## \ingroup utilities
telLib.readTelluriumDataFromFile.restype = c_bool
def readTelluriumData(rrDataHandle, fName):
    return telLib.readTelluriumDataFromFile(rrDataHandle, fName)

## \brief Create TelluriumData from a file
## \param fName Name of input file, including path. If no path is given, the file is read
## in current working directory
## \return Returns a handle to RoadRunner data if successful, None otherwise
## \note Use the freeTelluriumData to free memory allocated by the returned data
## \ingroup utilities
telLib.createTelluriumData.restype = c_void_p
def createTelluriumDataFromFile(fName):
    #Create a RoadRunner data object
    rrDataHandle = telLib.createTelluriumData(0,0,"")
    if telLib.readTelluriumDataFromFile(rrDataHandle, fName) == False:
        print 'Failed to read data'
    return rrDataHandle

## \brief Free TelluriumData
## \param dataHandle Handle to a roadrunner data object
## \return Returns True or false indicating result
## \ingroup utilities
telLib.freeTelluriumData.restype = c_bool
def freeTelluriumData(rrDataHandle):
    return telLib.freeTelluriumData(rrDataHandle)


