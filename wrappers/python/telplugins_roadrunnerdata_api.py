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
CTypes Python Bindings to the RoadRunnerData API.
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
def getRoadRunnerDataHandle(rrInstance):
    rrHandle = cast(int(rrInstance.this), c_void_p)
    return telLib.getRoadRunnerDataHandle(rrHandle)

## \brief Get column header in roadrunner data
## \param rrDataHandle A handle to a roadrunner data object
## \return Returns a numpy data object
## \ingroup utilities

telLib.getRoadRunnerDataColumnHeader.restype = c_char_p
def getRoadRunnerDataColumnHeader(rrDataHandle):
    hdr = telLib.getRoadRunnerDataColumnHeader(rrDataHandle)

    if hdr:
        res = hdr
        telLib.freeText(hdr)
        return res.split(',')
    else:
        return None

## \brief Write RoadRunnerData to a file
## \param rrDataHandle A handle to roadunnerdata
## \param fName Name of output file, including path. If no path is given, the file is written to the
## current working directory
## \return Returns True or false indicating result
## \ingroup utilities
telLib.writeRoadRunnerDataToFile.restype = c_bool
def writeRoadRunnerData(rrDataHandle, fName):
    return telLib.writeRoadRunnerDataToFile(rrDataHandle, fName)

## \brief Read RoadRunnerData from a file
## \param rrDataHandle A handle to roadunnerdata
## \param fName Name of input file, including path. If no path is given, the file is read
## in current working directory
## \return Returns True or false indicating result
## \ingroup utilities
telLib.readRoadRunnerDataFromFile.restype = c_bool
def readRoadRunnerData(rrDataHandle, fName):
    return telLib.readRoadRunnerDataFromFile(rrDataHandle, fName)

## \brief Create RoadRunnerData from a file
## \param fName Name of input file, including path. If no path is given, the file is read
## in current working directory
## \return Returns a handle to RoadRunner data if successful, None otherwise
## \note Use the freeRoadRunnerData to free memory allocated by the returned data
## \ingroup utilities
telLib.createRoadRunnerData.restype = c_void_p
def createRoadRunnerDataFromFile(fName):
    #Create a RoadRunner data object
    rrDataHandle = telLib.createRoadRunnerData(0,0,"")
    if telLib.readRoadRunnerDataFromFile(rrDataHandle, fName) == False:
        print 'Failed to read data'
    return rrDataHandle

## \brief Free RoadRunnerData
## \param dataHandle Handle to a roadrunner data object
## \return Returns True or false indicating result
## \ingroup utilities
telLib.freeRoadRunnerData.restype = c_bool
def freeRoadRunnerData(rrDataHandle):
    return telLib.freeRoadRunnerData(rrDataHandle)


