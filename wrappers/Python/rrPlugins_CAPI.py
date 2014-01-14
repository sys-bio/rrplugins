##@Module rrPlugins_CAPI
#This module allows access to the rrplugins_api.dll from python"""
import os
import sys
import numpy as np
import roadrunner
import tempfile
import time
from ctypes import *
import matplotlib.pyplot as plot
from rrPluginUtils import *

"""
CTypes Python Bindings to the RoadRunner Plugin API.

Currently this is a fairly raw implementation with few Pythonic refinements
"""

__version__ = "1.0.0"

# Get folder of where rrplugins_CAPI shared library is installed and construct an absolute path to
# the plugins from that.

sharedLib='rrplugins_c_api'
dirPath = getPathToParentFolderOf(sharedLib)

if os.path.exists(dirPath):
    gDefaultPluginsPath  = dirPath + os.sep + 'plugins'
else:
    print '==== WARNING: Roadrunner plugin folder could not be found =====\n'
    gDefaultPluginsPath = ''

rrpLib=None
try:
    if sys.platform.startswith('win32'):
        sharedLib = sharedLib + '.dll'
        rrpLib=CDLL(sharedLib)
    elif sys.platform.startswith('Linux'):
        sharedLib = sharedLib + '.a'
        rrpLib = cdll.LoadLibrary(sharedLib)
except:
    print 'ERROR: Unable to locate shared library: ' + sharedLib
    exit()


# Experimental parameter object class
# Usage:
# p = rrPlugins.PropertyObject ("k1", "hint", 0.1)
# p.value = 0.5
# print p.name

#class PropertyObject:
#    _parameterHandle = -1

#    def __getValue (self):
#        return getPropertyValue (self._parameterHandle)

#    def __setValue (self, value):
#       if type (value) is int:
#           setIntProperty (self._parameterHandle, value)
#       if type (value) is float:
#           setDoubleProperty (self._parameterHandle, value)
#       if type (value) is str:
#           setStringProperty (self._parameterHandle, value)
#    value = property (__getValue, __setValue)

#    def __getName (self):
#        return getPropertyName(self._parameterHandle)
#    name = property (__getName)

#    def __getHint (self):
#        return getPropertyHint(self._parameterHandle)
#    hint = property (__getHint)

#    def __getType (self):
#        return getPropertyType(self._parameterHandle)
#    pType = property (__getType)

#    def __init__(self, name, hint, value):
#      if type (value) is int:
#        self._parameterHandle = createProperty (name, "int", hint)
#      if type (value) is float:
#        self._parameterHandle = createProperty (name, "double", hint)
#      if type (value) is str:
#        self._parameterHandle = createProperty (name, "string", hint)
#      self.__setValue (value)

#    def __getHandle (self):
#        return self._parameterHandle

#    handle = property (__getHandle)


#=======================rrp_api========================#
#Type of plugin events, first argument is return type

## \brief Plugin function event type definition
## This is a helper object that a client can use as an argument to a roadrunner plugin.
## The exact number of plugins functions required arguments, and their type, is plugin dependent. A client of the
## the plugin needs to get this information from the plugin specific documentation.
## An example of using NotifyEvent is shown below. The NotifyEvent takes no arguments.
##@code
##def myPluginFunction():
##    print 'The plugin can call this function!'
## #The user can assign this function as a plugin event to monitor the start of the plugin as follows.
## #Note, make sure you assign the event to a variable (c_event) so that the Python garbage
## #collector doesn't delete it
## c_event = NotifyEvent(myPluginFunction)
## assignOnStartedEvent(plugin,  c_event)
##@endcode
## \ingroup plugins
NotifyEvent  = CFUNCTYPE(None)
NotifyEventEx  = CFUNCTYPE(None, c_void_p)

## \brief Create a new instance of a plugin manager.
## \brief A PluginManager manages a collection of plugins, loaded and unloaded by
##  the load and unload API functions respectively.
## \param pluginDir Full path to folder containing plugins. If None, uses default folder.
## \return On success, a handle to a Plugin manager, on failure, None.
##
## @code
## pm = rrPlugins.createPluginManager()
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugin_manager

rrpLib.createPluginManager.restype = c_void_p
def createPluginManager(pluginDir = None):
    if pluginDir == None:
        pluginDir = gDefaultPluginsPath
    return rrpLib.createPluginManager(pluginDir)

## \brief Free the plugin manager. A call to this function will also unload any loaded plugins.
## \param pm Handle to a plugin manager.
## \return true if success, false otherwise.
##
## \ingroup plugin_manager
rrpLib.freePluginManager.restype = c_bool
def freePluginManager(pm):
    return rrpLib.freePluginManager(pm)

##
## \brief Load plugins. The function will look in the default plugin folder for plugins, and load them.
## \param pm Handle to a PluginManager instance
## \return Returns true if Plugins are loaded, false otherwise
##
## @code sucess = rrPlugins.loadPlugins (pm)
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugin_manager
##
rrpLib.loadPlugins.restype = c_bool
def loadPlugins(pm):
    return rrpLib.loadPlugins(pm)

##
## \brief Unload all plugins.
## \param pm Handle to a PluginManager instance
## \return Returns true if Plugins are unloaded succesfully, false otherwise
##
## \ingroup plugin_manager
##
rrpLib.unLoadPlugins.restype = c_bool
def unLoadPlugins(pm):
    return rrpLib.unLoadPlugins(pm)

##
## \brief Load a particular plugin
## \param pm Handle to a PluginManager instance
## \param pluginName Name of the plugin to load. The plugin name is the plugin's shared library name, without path and extension.
## The library names for the plugins can be obtained by calling getPluginNames()
## \return Returns a handle to a plugin, None if unsuccesful
##
## @code
## lmPlugin = rrPlugins.loadPlugin(pm, "rrp_lm")
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugin_manager
##
def loadPlugin(pm, pluginName):
    return rrpLib.loadPlugin(pm, pluginName)

##
## \brief Unload a particular plugin
## \param pm Handle to a PluginManager instance
## \param pHandle Handle to a Plugin instance
## \return Returns true if the Plugin are unloaded succesfully, false otherwise
## \ingroup plugin_manager
##
def unLoadPlugin(pm, pHandle):
    return rrpLib.unLoadPlugin(pm, pHandle)

## \brief Get number of loaded plugins.
## \param pm Handle to a PluginManager instance
## \return Returns the number of loaded plugins, -1 if a problem is encountered. Call rrPlugins.getLastError() to obtain error message.
## \ingroup plugin_manager
rrpLib.getNumberOfPlugins.restype = c_int
def getNumberOfPlugins(pm):
    return rrpLib.getNumberOfPlugins(pm)

## \brief Function to retrieve the names of all currently loaded plugins.
## \param pm Handle to a PluginManager instance
## \return Returns names for all loaded plugins as a string, None otherwise
##
## @code
## names = rrPlugins.getPluginNames(pm)
## print names
## ['AddNoise', 'Levenberg-Marquardt']
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugin_manager
rrpLib.getPluginNames.restype = c_char_p
def getPluginNames(pm):
    names = rrpLib.getPluginNames(pm)
    res = names
    rrpLib.freeText(c_char_p(names))
    if not res:
        return list()
    return res.split(",")

## \brief Function to retrieve the library names of all currently loaded plugins.
## \param pm Handle to a PluginManager instance
## \return Returns library names for all loaded plugins as a string, None otherwise
##
## @code
## names = rrPlugins.getPluginLibraryNames(pm)
## print names
## ['rrp_add_noise', 'rrp_lm']
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugin_manager
rrpLib.getPluginLibraryNames.restype = c_char_p
def getPluginLibraryNames(pm):
    names = rrpLib.getPluginLibraryNames(pm)
    if not names:
        return list()
    return names.split(",")

## \brief getFirstPlugin retrieves the "first" plugin in the plugin managers internal list of plugins.
## This function is typically used together with the getNextPlugin and the getPreviousPlugin functions.
## \param pm Handle to a PluginManager instance
## \return Returns a handle to a plugin. Returns None if the plugin is not found
## \ingroup plugin_manager
rrpLib.getFirstPlugin.restype = c_void_p
def getFirstPlugin(pm):
    return rrpLib.getFirstPlugin(pm)

## \brief getNextPlugin retrieves the "next" plugin in the plugin managers internal list of plugins. This function
## is typically used together with the getFirstPlugin and getPreviousPlugin functions.
## \param pm Handle to a PluginManager instance
## \return Returns a handle to a plugin. Returns None if the plugin is not found
## \ingroup plugin_manager
rrpLib.getNextPlugin.restype = c_void_p
def getNextPlugin(pm):
    return rrpLib.getNextPlugin(pm)

## \brief getPreviousPlugin retrieves the "previous" plugin in the plugin managers internal list of plugins. This function
##    is typically used together with the getFirstPlugin and getNextPlugin functions.
## \param pm Handle to a PluginManager instance
## \return Returns a handle to a plugin. Returns None if the plugin is not found
## \ingroup plugin_manager
rrpLib.getPreviousPlugin.restype = c_void_p
def getPreviousPlugin(pm):
    return rrpLib.getPreviousPlugin(pm)

## \brief getCurrentPlugin retrieves the "current" plugin in the plugin managers internal list of plugins. This function
##    is typically used together with the getFirst, Next and getPreviousPlugin functions.
## \param pm Handle to a PluginManager instance
## \return Returns a handle to a plugin. Returns None if the plugin is not found
## \ingroup plugin_manager
rrpLib.getCurrentPlugin.restype = c_void_p
def getCurrentPlugin(pm):
    return rrpLib.getCurrentPlugin(pm)


## \brief Get the plugin handle for the named plugin
## \param pm Handle to a PluginManager instance
## \param pluginName A string that holds the name of the plugin
## \return Returns a handle to a plugin, with name as supplied in the property pluginName.
## Returns None if the plugin is not found
## \ingroup plugin_manager
rrpLib.getPlugin.restype = c_void_p
def getPlugin(pm, pluginName):
    return rrpLib.getPlugin(pm, c_char_p(pluginName))


#---------- PLUGIN HANDLING FUNCTIONS ============================================
## \brief Get the name of a Plugin
## \param pluginHandle Handle to a plugin
## \return Returns the internal name of a plugin. None otherwise
##
## @code
## name = rrPlugins.getPluginName(pluginHandle)
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugins
rrpLib.getPluginName.restype = c_char_p
def getPluginName(pluginHandle):
    return rrpLib.getPluginName(pluginHandle)

## \brief Get the Category of a Plugin. This is assigned by the pluging developer
## \param pluginHandle Handle to a plugin
## \return Returns a string if successful, None otherwise
##
## @code
## name = rrPlugins.getPluginCategory(pluginHandle)
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugins
rrpLib.getPluginCategory.restype = c_char_p
def getPluginCategory(pluginHandle):
    data =  rrpLib.getPluginCategory(pluginHandle)
    res = data
    rrpLib.freeText(data)
    return res

## \brief Get the Description of a Plugin. This is assigned by the pluging developer
## \param pluginHandle Handle to a plugin
## \return Returns a string if successful, None otherwise
##
## @code
## name = rrPlugins.getPluginDescription(pluginHandle)
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugins
rrpLib.getPluginDescription.restype = c_char_p
def getPluginDescription(pluginHandle):
    data =  rrpLib.getPluginDescription(pluginHandle)
    res = data
    rrpLib.freeText(data)
    return res

## \brief Get a plugins Hint. A plugins hint is a short description on what the plugin is doing.This is assigned by the pluging developer
## \param pluginHandle Handle to a plugin
## \return Returns a string if successful, None otherwise
##
## @code
## name = rrPlugins.getPluginHint(pluginHandle)
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugins
rrpLib.getPluginHint.restype = c_char_p
def getPluginHint(pluginHandle):
    data =  rrpLib.getPluginHint(pluginHandle)
    res = data
    rrpLib.freeText(data)
    return res

## \brief Returns information about a Plugin.
## \param pluginHandle Handle to a plugin
## \return Returns information as a string for the plugin, None otherwise
## \ingroup plugins
rrpLib.getPluginInfo.restype = c_char_p
def getPluginInfo(pluginHandle):
    return rrpLib.getPluginInfo(pluginHandle)

## \brief Get Plugin manual as PDF. A plugin may embedd a help manual as a PDF.
## Use the function getPluginManualNrOfBytes to get the exact length of this string.
## \param pluginHandle Handle to a plugin
## \return Returns the plugin's manual pdf file as a unsigned char*. If not available, returns None.
##
## @code
## ptr = getPluginManualAsPDF(pluginHandle)
## numOfBytes = getPluginManualNrOfBytes(pluginHandle)
## manual = cast(ptr, POINTER(c_char * numOfBytes))[0]
## if numOfBytes == 0:
##    print 'This plugin does not have a manual.'
##    exit()
## outFName = getPluginName (pluginHandle) + '.pdf'
## with open(outFName, 'wb') as output:
##    output.write(manual)
## os.system('start ' + outFName)
##
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugins
rrpLib.getPluginManualAsPDF.restype =  POINTER(c_ubyte)
def getPluginManualAsPDF(pluginHandle):
    return rrpLib.getPluginManualAsPDF(pluginHandle)

## \brief Get the byte size for the PDF manual.
## \param pluginHandle Handle to a plugin
## \return Returns the number of bytes in the plugin's manual pdf file as an unsigned int.
## \ingroup plugins
def getPluginManualNrOfBytes(pluginHandle):
    return rrpLib.getPluginManualNrOfBytes(pluginHandle)


## \brief If a plugin has a built-in PDF manual, display it.
## \param pluginHandle Handle to a plugin
## \return Returns False if the plugin has no manual
##
## @code
## success = displayPluginManual(pluginHandle)
##
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugins
def displayPluginManual(pluginHandle):
    ptr = getPluginManualAsPDF(pluginHandle)
    numOfBytes = getPluginManualNrOfBytes(pluginHandle)
    manual = cast(ptr, POINTER(c_char * numOfBytes))[0]
    if numOfBytes == 0:
       print 'This plugin does not have a manual.'
       return False
    outFName = tempfile.gettempdir() + '\\' + getPluginName (pluginHandle) + '.pdf'
    print outFName
    with open(outFName, 'wb') as output:
      output.write(manual)
    os.system('start ' + outFName)

## \brief Assign a roadrunner instance handle for the plugin to use.
##    A plugin may use an externally created roadrunner instance for its internal work.
##  \param pluginHandle Handle to a plugin
##  \param rrHandle Handle to a roadrunner instance
##  \return Returns true or false indicating success/failure
## \ingroup plugins
rrpLib.assignRoadRunnerInstance.restype = c_bool
def assignRoadRunnerInstance(pluginHandle, rrHandle):
    return rrpLib.assignRoadRunnerInstance(pluginHandle, rrHandle)

## \brief The executePlugin function is called to start the plugin so that it can carry out its
## function. The call is plugin dependent meaning that it could result in a calculation, starting up a GUI etc.
## \param pluginHandle Handle to a plugin
## \return Returns true or false indicating success/failure
## \note The execute function is a regular blocking function, meaning it won't return to the caller until the task is complete.
## If the plugin is asked to carry out a lengthy calculation, consider using
## the executePluginEx function that has the option to execute the plugin code in the background (in a thread);
## \ingroup plugins
rrpLib.executePlugin.restype = c_bool
def executePlugin(pluginHandle):
    return rrpLib.executePlugin(pluginHandle)

## \brief The executePluginEx is similar to the executePlugin function, except it takes one extra argument.
## \param pluginHandle Handle to a plugin
## \param inAThread bool indicating if the plugin should be executed in the background (in a thread)
## \return Returns true or false indicating success/failure
## \ingroup plugins
rrpLib.executePluginEx.restype = c_bool
def executePluginEx(pluginHandle, inAThread=False):
    return rrpLib.executePluginEx(pluginHandle, c_bool(inAThread))

## \brief Get status information from a plugin. This call is plugin dependent, see the plugin documentation for details
## \param pluginHandle Handle to a plugin
## \return Returns plugin status if available, as a string. None otherwise
## \ingroup plugins
rrpLib.getPluginStatus.restype = c_char_p
def getPluginStatus(pluginHandle):
    return rrpLib.getPluginStatus(pluginHandle)

## \brief Returns a plugins result, as a string. This is plugin dependent, and a plugin designer may, or may not, implement
## this function. See the plugin documentation for details.
## \note If a plugin wants to returns specific result, e.g. an Array, or a a float, these are better communicated
## through the use of Plugin properties.
## \param pluginHandle Handle to a plugin
## \return Returns a plugins result if available. None otherwise
## \ingroup plugins
rrpLib.getPluginResult.restype = c_char_p
def getPluginResult(pluginHandle):
    return rrpLib.getPluginResult(pluginHandle)

## \brief Reset a Plugin. Plugin dependent. A reset function should bring the internal state of a plugin to a known state
## \param pluginHandle Handle to a plugin
## \return Returns true or false indicating success/failure
## \ingroup plugins
rrpLib.resetPlugin.restype = c_bool
def resetPlugin(pluginHandle):
    return rrpLib.resetPlugin(pluginHandle)

## \brief Check if a plugin is actively working. This function is used when the work in the plugin is
## executed in a thread (see executeEx). The isPluginWorking will return true as long work is being active
## and false when the work is done. This is useful in UI environments. Also, see the various event types on
## how to get status back from a plugin during its execution.
## \param pluginHandle Handle to a plugin
## \return Returns true or false indicating if the plugin is busy or not
## \ingroup plugins
rrpLib.isPluginWorking.restype = c_bool
def isPluginWorking(pluginHandle):
    return rrpLib.isPluginWorking(pluginHandle)

## \brief Terminate any work that is in progress in a plugin. If the plugins worker is executed in a thread, this function
## will signal the internals of the plugin to terminate. This function is used when a plugins work is executed in a thread.
## \param pluginHandle Handle to a plugin
## \return Returns true or false indicating success/failure
## \ingroup plugins
rrpLib.terminateWork.restype = c_bool
def terminateWork(pluginHandle):
    return rrpLib.terminateWork(pluginHandle)

## \brief Check if the work of a plugin is currently being terminated. This function is useful when a plugin is executed in a thread.
## \param pluginHandle Handle to the plugin
## \return Returns true or false indicating if the work within the plugin is in the process of being terminated
## \ingroup plugins
rrpLib.isBeingTerminated.restype = c_bool
def isBeingTerminated(pluginHandle):
    return rrpLib.isBeingTerminated(pluginHandle)

## \brief Query a plugin if work was terminated succesfully. This function may be used in combination with
## the terminateWork, and isBeingTerminated functions.
## \param pluginHandle Handle to the plugin
## \return Returns true or false indicating if the work in the plugin was terminated or not
## \ingroup plugins
rrpLib.wasTerminated.restype = c_bool
def wasTerminated(pluginHandle):
    return rrpLib.wasTerminated(pluginHandle)

## \brief Assigns a plugins OnStartedEvent function.Plugin dependent. Intended usage is to report back on plugin initialization.
## \param pluginHandle Handle to a plugin
## \param pluginEvent Function pointer to OnEvent routine
## \param userData1 void* pointer to user data.
## \param userData2 void* pointer to user data.
## \return Returns true or false indicating success/failure
## \ingroup plugins
rrpLib.assignOnStartedEvent.args =[c_void_p, NotifyEvent, c_void_p]
def assignOnStartedEvent(pluginHandle, pluginEvent, userData1 = None, userData2 = None):
    return rrpLib.assignOnStartedEvent(pluginHandle, pluginEvent, userData1, userData2)

## \brief Assigns a plugins OnProgressEvent function. Plugin dependent. Intended usage is to report back progress
## \param pluginHandle Handle to a pluginevent routine
## \param userData1 void* pointer to user data.
## \param userData2 void* pointer to user data.
## \return Returns true or false indicating success/failure
## \ingroup plugins
rrpLib.assignOnProgressEvent.args =[c_void_p, c_void_p, c_void_p]
def assignOnProgressEvent(pluginHandle, pluginEvent, userData1 = None, userData2 = None):
    return rrpLib.assignOnProgressEvent(pluginHandle, pluginEvent, userData1, userData2)

## \brief Assigns a plugins OnFinishedEvent function. Plugin dependent. Intended usage is to report back on plugin finalization.

## \param pluginHandle Handle to a plugin
## \param pluginEvent Function pointer to event routine
## \param userData1 void* pointer to user data.
## \param userData2 void* pointer to user data.
## \return Returns true or false indicating success/failure
## \ingroup plugins
rrpLib.assignOnFinishedEvent.args =[c_void_p, NotifyEvent, c_void_p]
def assignOnFinishedEvent(pluginHandle, pluginEvent, userData1 = None, userData2 = None):
    return rrpLib.assignOnFinishedEvent(pluginHandle, pluginEvent, userData1, userData2)

#### \brief Hand external data to a plugin: THIS METHOD IS UNDER REVIEW
#### \param pluginHandle Handle to a plugin
#### \param userData void* pointer to user data. Plugin dependent, see the specific documentation on the plugin for details.
#### \return Returns true or false indicating success/failure
#### \ingroup plugins
##rrpLib.assignPluginInput.restype = c_bool
##def assignPluginInput(pluginHandle, userData):
##    return rrpLib.assignPluginInput(pluginHandle, c_void_p(userData))

## \brief Get the roadrunner instance handle from plugin assuming the plugin has one
## \param pluginHandle Handle to a Plugin instance
## \return Returns a handle to a rrInstance if available, returns None otherwise
## \ingroup plugins
rrpLib.getRRHandleFromPlugin.restype = c_void_p
def getRRHandleFromPlugin(pluginHandle):
    return rrpLib.getRRHandleFromPlugin(pluginHandle)

#================ Plugin Property functionality ======================
## \brief Get a handle to the list of properties for a plugin
## \param pluginHandle Handle to a plugin
## \return Returns a handle to a list of Properties on success, None otherwise
## \ingroup plugin_properties
rrpLib.getPluginProperties.restype = c_void_p
def getPluginProperties(pluginHandle):
    return rrpLib.getPluginProperties(pluginHandle)

## \brief Get a list of property names in a plugin
## \param pluginHandle Handle to a plugin
## \return Returns the netire list of top level property names, None otherwise
## \ingroup plugin_properties
rrpLib.getListOfPluginPropertyNames.restype = c_char_p
def getListOfPluginPropertyNames(pluginHandle):
    paraNames =  rrpLib.getListOfPluginPropertyNames(pluginHandle)
    if not paraNames:
        return list()
    else:
        names = paraNames.split(',')
        return names

## \brief Clear a list of properties. Some properties exposed by plugins are lists that can hold other properties. New property can be
## added to these lists. clearPropertyList can be used to clear the list is a new list needs to be constructed.
## \param parasHandle Handle to a list of properties
## \return True or false, indicating result. The top level list of properties in a plugin can not be cleared.
## \ingroup plugin_properties
rrpLib.clearPropertyList.restype = c_bool
def clearPropertyList(propertyListHandle):
    handle = getPropertyValueHandle(propertyListHandle)
    return rrpLib.clearPropertyList(handle)

## \brief If the property is a list, this method returns the list of property names in that list
## \param propertyHandle Handle to a property
## \return Returns names for all properties in the list
## \ingroup plugin_properties
rrpLib.getNamesFromPropertyList.restype = c_char_p
def getNamesFromPropertyList(propertyMeterHandle):
    paraType = getPropertyType(propertyMeterHandle)
    if paraType != 'listOfProperties':
        raise 'That is not a valid list property'
    listHandle = getPropertyValueHandle(propertyMeterHandle)
    paras = rrpLib.getNamesFromPropertyList(listHandle)
    if not paras:
        return list()
    else:
        names = paras.split(',')
        return names

## \brief Get a the properties of a plugins in xml format.
## \param pluginHandle Handle to a plugin
## \return Returns a string on success, None otherwise
## \ingroup plugin_properties
rrpLib.getPluginPropertiesAsXML.restype = c_char_p
def getPluginPropertiesAsXML(pluginHandle):
    return rrpLib.getPluginPropertiesAsXML(pluginHandle)

## \brief Get the 'first' property handle to a property in a list of properties
## \param paraListHandle Handle to a propertyList
## \return Returns a handle to a property. Returns None if not found
## \ingroup plugin_properties
def getFirstProperty(paraListHandle):
    handle = getPropertyValueHandle(paraListHandle)
    return rrpLib.getFirstProperty(handle)

## \brief Get the 'next' property handle to a property in a list of properties
## \param paraListHandle Handle to a propertyList
## \return Returns a handle to a property. Returns None if not found
## \ingroup plugin_properties
def getNextProperty(propertyListHandle):
    return rrpLib.getNextProperty(paraListHandle)

## \brief Get a property handle to a property given the name of the property.
## \param pluginHandle Handle to a plugin
## \param propertyName Name of the property
## \return Returns a propertyHandle to a property. Returns None if not found
## \ingroup plugin_properties
def getPluginProperty(pluginHandle, propertyName):
    return rrpLib.getPluginProperty(pluginHandle, propertyName)

## \brief Set the value of a PluginProperty
## \param pluginHandle Handle to a plugin
## \param propertyName Name of property
## \param propertyValue Value of property
## \return true if succesful, false otherwise
## \ingroup plugin_properties
rrpLib.setPluginProperty.restype = c_bool
def setPluginProperty(pluginHandle, propertyName, propertyValue):
    propertyHandle = getPluginProperty(pluginHandle, propertyName)
    if propertyHandle:
        paraType = getPropertyType(propertyHandle)
        if paraType == 'bool':
            return setBoolProperty(propertyHandle, propertyValue)
        if paraType == 'int':
            return setIntProperty(propertyHandle, propertyValue)
        if paraType == 'double':
            return setDoubleProperty(propertyHandle, propertyValue)
        if paraType == 'string':
            return setStringProperty(propertyHandle, propertyValue)
        if paraType == 'std::string': #Behaves the same in the backend
            return setStringProperty(propertyHandle, propertyValue)
        if paraType == 'listOfProperties':
            return setListProperty(propertyHandle, propertyValue)
        if paraType == 'roadRunnerData': #The value of this is a handle
            return setRoadRunnerDataProperty (propertyHandle, propertyValue)
        if paraType == 'StringList':
            return setPropertyByString(propertyHandle, propertyValue)
        else:
           raise TypeError ('Cannot set the value of such property')
    else:
           raise TypeError('Bad Handle')
    return False

## \brief Set the value of a property
## \param property handle Handle to a property
## \param paraValue Value of property
## \return true if successful, false otherwise
## \ingroup plugin_properties
def setProperty(propertyHandle, paraValue):
    if propertyHandle:
        paraType = getPropertyType(propertyHandle)
        if paraType == 'bool':
            return setBoolProperty(propertyHandle, paraValue)
        if paraType == 'int':
            return setIntProperty(propertyHandle, paraValue)
        if paraType == 'double':
            return setDoubleProperty(propertyHandle, paraValue)
        if paraType == 'string':
            return setStringProperty(propertyHandle, paraValue)
        if paraType == 'std::string': #Behaves the same in the backend
            return setStringProperty(propertyHandle, paraValue)
        if paraType == 'listOfProperties':
            return setListProperty(propertyHandle, paraValue)
        if paraType == 'roadRunnerData': #The value of this is a handle
            return setRoadRunnerDataProperty(propertyHandle, paraValue)
        if paraType == 'StringList':
            return setPropertyByString(propertyHandle, paraValue)
        else:
           raise TypeError ('Cannot set the value of such property')
    else:
           raise ('Bad Handle')
    return False

## \brief Set the description of a Property
## \param propertyHandle Handle to a Property instance
## \param descr String holding the description
## \return Returns true if successful, false otherwise
## \ingroup plugin_properties
rrpLib.setPropertyDescription.restype = c_bool
def setPropertyDescription(propertyHandle, descr):
    return rrpLib.setPropertyDescription(propertyHandle, descr)

## \brief Get the description of a Property
## \param propertyHandle Handle to a Property instance
## \param descr String holding the description
## \return Returns the description if successful, None otherwise
## \ingroup plugin_properties
rrpLib.getPropertyDescription.restype = c_char_p
def getPropertyDescription(propertyHandle):
    descr = rrpLib.getPropertyDescription(propertyHandle)
    if descr is None:
        return None
    
    val = descr
    rrpLib.freeText(descr)
    return val

## \brief Set the hint property of a Property
## \param propertyHandle Handle to a Property instance
## \param descr String holding the hint text
## \return Returns true if successful, false otherwise
## \ingroup plugin_properties
rrpLib.setPropertyHint.restype = c_bool
def setPropertyHint(propertyHandle, descr):
    return rrpLib.setPropertyHint(propertyHandle, descr)

## \brief Create a Property of type "type" with a name and hint property
##  Valid types include: 'bool', 'int', 'double', 'string', and 'listOfProperties'
## \param name The properties name as a string
## \param the_type  The properties type as string. Possible values: 'bool', 'int', 'double', 'string', and 'listOfProperties'
## \param hint The properties hint as a string.
## \param value This is an optional argument to set the Property (supports int, double and string).
## \return Returns a handle to a new Property, if succesful, None otherwise
##
## @code
## propertyHandle = rrPlugins.createProperty ("k1", string", "A message")
##
##propertyHandle = rrPlugins.createProperty ("k1", "double", "A rate constant", 0.3)
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugin_properties
rrpLib.createProperty.restype = c_void_p
def createProperty(name, the_type, hint="", value=None):
    if value == None:
       return rrpLib.createProperty(name, the_type, hint, value)
    else:
        if the_type == 'string':    #Otherwise underlying string type will be char*, don't
            the_type = 'std::string'
        ptr = rrpLib.createProperty(name, the_type, hint)
        if the_type is "bool":
           setBoolProperty (ptr, value)
        elif the_type is "int":
           setIntProperty (ptr, value)
        elif the_type is "float":
           setDoubleProperty (ptr, value)
        elif the_type is "double":
           setDoubleProperty (ptr, value)
        elif the_type is "string":
           setStringProperty (ptr, value)
        elif the_type is "std::string":
           setStringProperty (ptr, value)

        else:
            print "Error: Can't set the value of Property with type:" + the_type
        return ptr

## \brief Free memory for a Property
## \param propertyHandle Handle to a Property instance
## \return Returns true if successful, false otherwise
## \ingroup plugin_properties
rrpLib.freeProperty.restype = c_bool
def freeProperty(propertyHandle):
    return rrpLib.freeProperty(propertyHandle)


## \brief Add a Property to a list of Property.
## Some plugins may have Property that
## require list of Property to be specified. For example when deciding what kinetic Property to fit in a model, the list
## of kinetic Property can be pass to the plugin as a list. This method can be used to add the names of the kinetic Property
## to the list.
## \param list A Handle to a Property with type listOfProperty
## \param propertyHandle Handle to the Property to add to the list(see createProperty)
## \return Returns a Boolean indicating success
##
## @code
## paraList = getPluginProperty(plHandle, "SpeciesList");
## newProperty = createProperty("k1", "double", "A Hint", 0.2)
## addPropertyToList(paraList, newProperty)
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugin_properties
rrpLib.addPropertyToList.restype = c_bool
def addPropertyToList(propertyHandle, addMe):
    #Make sure the Property is of type list
    if getPropertyType(propertyHandle) == 'listOfProperties':
        listHandle = getPropertyValue(propertyHandle)
        return rrpLib.addPropertyToList(listHandle, addMe)
    else:
        return False

## \brief Set a Property by a string
## \param propertyHandle to a Property instance
## \param value Pointer to string holding the value to assign to the Property, e.g. "0.01" to set a double to 0.01
## \return Returns true if successful, false otherwise
## \ingroup plugin_properties
rrpLib.setPropertyByString.restype = c_bool
def setPropertyByString(PropertyHandle, value):
    return rrpLib.setPropertyByString(PropertyHandle, value)

## \brief Get inforamtion on a Property
## \param propertyHandle Handle to a Property instance
## \return Returns informational text about the Property if successful, None otherwise
## \ingroup plugin_properties
rrpLib.getPropertyInfo.restype = c_char_p
def getPropertyInfo(propertyHandle):
    return rrpLib.getPropertyInfo(propertyHandle)

## \brief Get a Property value in the form of a string
## \param propertyHandle to a Property instance
## \return Returns the Properties value if successful, None otherwise
## \ingroup plugin_properties
rrpLib.getPropertyValueAsString.restype = c_char_p
def getPropertyValueAsString(propertyHandle):
    return rrpLib.getPropertyValueAsString(propertyHandle)

## \brief Get a handle to a Property value. Such properties could be any type, including a list of Properties.
## Use getlistProperty(propertyaHandle) instead.
## \param propertyHandle to a Property instance
## \return Returns a Handle to the property value if successful, None otherwise
#
## @code
## propertyHandle = rrPlugins.getPropertyValueHandle (prophandle)
## @endcode
## \htmlonly  <br/>
## \endhtmlonly
## \ingroup plugin_properties
rrpLib.getPropertyValueHandle.restype = c_void_p
def getPropertyValueHandle(propertyHandle):
    return rrpLib.getPropertyValueHandle(propertyHandle)

## \brief Get the name of a Property
## \param propertyHandle to a Property instance
## \return Returns the Properties name if successful, None otherwise
## \ingroup plugin_properties
rrpLib.getPropertyName.restype = c_char_p
def getPropertyName(propertyHandle):
    return rrpLib.getPropertyName(propertyHandle)

## \brief Get the hint text for a Property
## \param propertyHandle to a Property instance
## \return Returns the hint value for a Property if successful, None otherwise
## \ingroup plugin_properties
rrpLib.getPropertyHint.restype = c_char_p
def getPropertyHint(propertyHandle):
    return rrpLib.getPropertyHint(propertyHandle)

## \brief Get the type of a property
## \param propertyHandle to a Property instance
## \return Returns the Properties type as a string if successful, None otherwise
## \ingroup plugin_properties
rrpLib.getPropertyType.restype = c_char_p
def getPropertyType(propertyHandle):
    return rrpLib.getPropertyType(propertyHandle)

## \brief Get the Boolean value for a property
## \param propertyHandle to a property instance
## \return Returns a Boolean value. Throws an exception if the property type is not a Boolean
## \ingroup plugin_properties
rrpLib.getBoolProperty.restype = c_bool
def getBoolProperty (propertyHandle):
    if getPropertyType (propertyHandle) == "bool":
        val = c_bool()
        if rrpLib.getBoolProperty (propertyHandle, byref(val)) == True:
            return val.value
        else:
            raise ('Property value could not be retrieved')
    else:
       raise TypeError ('Property is not a Boolean type')

## \brief Set a boolean property
## \param propertyHandle to a property instance
## \param value to assign to the property.
## \return Returns true if successful, false otherwise
## \ingroup plugin_properties
rrpLib.setBoolProperty.restype = c_bool
def setBoolProperty(propertyHandle, value):
    return rrpLib.setBoolProperty (propertyHandle, c_bool(value))

## \brief Get the integer value for a property
## \param propertyHandle to a property instance
## \return Returns an integer value. Throws an exception if the property type is not an integer
## \ingroup plugin_properties
rrpLib.getIntProperty.restype = c_int
def getIntProperty (propertyHandle):
    if getPropertyType (propertyHandle) == "int":
        val = c_int()
        if rrpLib.getIntProperty (propertyHandle, byref(val)) == True:
            return val.value
        else:
            raise ('Property value could not be retrieved')
    else:
       raise TypeError ('Property is not an integer type')

## \brief Set an integer property
## \param propertyHandle to a property instance
## \param value to assign to the property.
## \return Returns true if successful, false otherwise
## \ingroup plugin_properties
rrpLib.setIntProperty.restype = c_bool
def setIntProperty(propertyHandle, value):
    return rrpLib.setIntProperty(propertyHandle, c_int(value))


## \brief Get the double value for a property
## \param propertyHandle to a property instance
## \return Returns a double value. Throws an exception if the property type is not a double
## \ingroup plugin_properties
rrpLib.getDoubleProperty.restype = c_bool
def getDoubleProperty (propertyHandle):
    if getPropertyType (propertyHandle) == "double":
        val = c_double()
        if rrpLib.getDoubleProperty (propertyHandle, byref(val)) == True:
            return val.value
        else:
            raise ('Property value could not be retrieved')
    else:
       raise TypeError ('Property is not a double type')

## \brief Set the value for a double property
## \param propertyHandle Is a property instance
## \param value to assign to the property.
## \return Returns true if successful, false otherwise
## \ingroup plugin_properties
rrpLib.setDoubleProperty.restype = c_bool
def setDoubleProperty(propertyHandle, value):
    return rrpLib.setDoubleProperty(propertyHandle, c_double(value))

## \brief Get the string value for a property
## \param propertyHandle to a property instance
## \return Returns a string value. Throws an exception if the property type is not a string
## \ingroup plugin_properties
rrpLib.getStringProperty.restype = c_bool
def getStringProperty (propertyHandle):
    if getPropertyType (propertyHandle) == "string" or getPropertyType (propertyHandle) == "std::string":
        val = c_char_p()
        if rrpLib.getStringProperty (propertyHandle, byref(val)) == True:
            return val.value
        else:
            raise ('Property value could not be retrieved')
    else:
       raise TypeError ('Property is not a string type')

## \brief Set a string property
## \param propertyHandle Handle to a Property instance
## \param value Value to assign to the property.
## \return Returns true if successful, false otherwise
## \ingroup plugin_properties
rrpLib.setStringProperty.restype = c_bool
def setStringProperty(propertyHandle, value):
    return rrpLib.setStringProperty(propertyHandle, c_char_p(value))

## \brief Get the list value for a property
## \param propertyHandle to a property instance
## \return Returns a handle to a ListProperty. Throws an exception of the property type is not a list of properties
## \ingroup plugin_properties
rrpLib.getListProperty.restype = c_bool
def getListProperty (propertyHandle):
    if getPropertyType (propertyHandle) == "listOfProperty":
        return getPropertyValueHandle(propertyHandle)
    else:
       raise TypeError ('Property is not a list type')

## \brief Set a list Property
## \param propertyHandle to a Property instance
## \param value Value to assign to the property (must be a handle to a Property of listOfProperties.
## \return Returns true if successful, false otherwise
## \ingroup plugin_properties
rrpLib.setListProperty.restype = c_bool
def setListProperty(propertyHandle, value):
    handle = getPropertyValueHandle(value)
    return rrpLib.setListProperty(propertyHandle, c_void_p(handle))

## \brief Get the value of a roadRunnerData property
## \param propertyHandle A Handle to a property
## \return Returns the value of the property if succesful, None otherwise
## \ingroup plugin_properties
def getRoadRunnerDataProperty(propertyHandle):
        return getPropertyValue(propertyHandle)

## \brief Set a roadRunnerData property
## \param propertyHandle Handle to a Property instance
## \param value Value to assign to the property (must be a handle to roadRunnerData.
## \return Returns true if successful, false otherwise
## \ingroup plugin_properties
rrpLib.setRoadRunnerDataProperty.restype = c_bool
def setRoadRunnerDataProperty(propertyHandle, value):
    return rrpLib.setRoadRunnerDataProperty(propertyHandle, c_void_p(value))

## \brief Get the value of a property.
## \param propertyHandle A Handle to a property
## \return Returns the value of the property if succesful, None otherwise
## \ingroup plugin_properties
def getProperty(propertyHandle):
    paraType = getPropertyType(propertyHandle)
    if paraType == 'bool':
        paraVoidPtr = getPropertyValueHandle(propertyHandle)
        ptr = cast(paraVoidPtr, POINTER(c_bool))
        return ptr[0]
    if paraType == 'int':
        paraVoidPtr = getPropertyValueHandle(propertyHandle)
        ptr = cast(paraVoidPtr, POINTER(c_int))
        return ptr[0]
    if paraType == 'double':
        paraVoidPtr = getPropertyValueHandle(propertyHandle)
        ptr = cast(paraVoidPtr, POINTER(c_double))
        return ptr[0]
    if paraType == 'std::string':
        return getPropertyValueAsString(propertyHandle)
    if paraType == 'string':
        return getPropertyValueAsString(propertyHandle)
    if paraType == 'listOfProperties':
        return getPropertyValueHandle(propertyHandle)
    if paraType == 'roadRunnerData': #The value of this is a handle
        ptr = getPropertyValueHandle(propertyHandle)
        return ptr
    else:
       raise TypeError ('Property is not a string type: ', paraType)

## \brief Get the value of a property.
## \param propertyHandle A Handle to a property
## \return Returns the value of the property if succesful, None otherwise
## \note Legacy function. Use getProperty() instead.
## \ingroup plugin_properties
def getPropertyValue(propertyHandle):
    paraType = getPropertyType(propertyHandle)
    if paraType == 'bool':
        paraVoidPtr = getPropertyValueHandle(propertyHandle)
        ptr = cast(paraVoidPtr, POINTER(c_bool))
        return ptr[0]
    if paraType == 'int':
        paraVoidPtr = getPropertyValueHandle(propertyHandle)
        ptr = cast(paraVoidPtr, POINTER(c_int))
        return ptr[0]
    if paraType == 'double':
        paraVoidPtr = getPropertyValueHandle(propertyHandle)
        ptr = cast(paraVoidPtr, POINTER(c_double))
        return ptr[0]
    if paraType == 'std::string':
        return getPropertyValueAsString(propertyHandle)
    if paraType == 'string':
        return getPropertyValueAsString(propertyHandle)
    if paraType == 'listOfProperties':
        return getPropertyValueHandle(propertyHandle)
    if paraType == 'roadRunnerData': #The value of this is a handle
        ptr = getPropertyValueHandle(propertyHandle)
        return ptr
    else:
       raise TypeError ('Property is not a string type')

## \brief Retrieve a handle to RoadRunners internal data object
## \param rrInstance A RoadRunner instance, as returned from roadrunner.RoadRunner()
## \return Returns a handle to roadrunners internal data object
## \ingroup utilities
def getRoadRunnerDataHandle(rrInstance):
    rrHandle = cast(int(rrInstance.this), c_void_p)
    return rrpLib.getRoadRunnerDataHandle(rrHandle)

## \brief Convert roadrunner data to Numpy data
## \param rrDataHandle A handle to a roadrunner data object
## \return Returns a numpy data object
## \ingroup utilities
rrpLib.getRoadRunnerDataElement.restype = c_bool
def getNumpyData(rrDataHandle):
    colHeader = rrpLib.getRoadRunnerDataColumnHeader(rrDataHandle)
    rowCount = rrpLib.getRoadRunnerDataNumRows(rrDataHandle)
    colCount = rrpLib.getRoadRunnerDataNumCols(rrDataHandle)
    resultArray = np.zeros([rowCount, colCount])
    for row in range(rowCount):
        for col in range(colCount):
                val = c_double()
                if rrpLib.getRoadRunnerDataElement(rrDataHandle, row, col, byref(val)) == True:
                    resultArray[row, col] = val.value
                else:
                    print "problem"
    #resultArray = np.append(resultArray, colHeader.split(","))
    #Not sure how to append the col names.
    return resultArray

def plotRoadRunnerData(data, colHeaders):
    nrCols = data.shape[1]
    nrRows = data.shape[0]

    if len(colHeaders) < 1:
        print "bad data"
        return
    xlbl = colHeaders[0]
    nrOfSeries = nrCols -1
    x = data[:,0]

    for serie in range(nrOfSeries):
        ySeries = np.zeros([nrRows])
        ySeries = data[:,serie + 1]
        plot.plot(x, ySeries, "", label=colHeaders[serie +1])

    plot.legend(bbox_to_anchor=(1.05, 1), loc=1, borderaxespad=0.)
    plot.xlabel(xlbl)
    plot.ylabel('Concentration (moles/L)')
    plot.show()
## \brief Get column header in roadrunner data
## \param rrDataHandle A handle to a roadrunner data object
## \return Returns a numpy data object
## \ingroup utilities

rrpLib.getRoadRunnerDataColumnHeader.restype = c_char_p
def getRoadRunnerDataColumnHeader(rrDataHandle):
    hdr = rrpLib.getRoadRunnerDataColumnHeader(rrDataHandle)

    if hdr:
        res = hdr
        rrpLib.freeText(hdr)
        return res.split(',')
    else:
        return None


## \brief Write RoadRunnerData to a file
## \param rrDataHandle A handle to roadunnerdata
## \param fName Name of output file, including path. If no path is given, the file is written to the
## current working directory
## \return Returns True or false indicating result
## \ingroup utilities
rrpLib.writeRoadRunnerDataToFile.restype = c_bool
def writeRoadRunnerData(rrDataHandle, fName):
    return rrpLib.writeRoadRunnerDataToFile(rrDataHandle, fName)


## \brief Read RoadRunnerData from a file
## \param rrDataHandle A handle to roadunnerdata
## \param fName Name of input file, including path. If no path is given, the file is read
## in current working directory
## \return Returns True or false indicating result
## \ingroup utilities
rrpLib.readRoadRunnerDataFromFile.restype = c_bool
def readRoadRunnerData(rrDataHandle, fName):
    return rrpLib.readRoadRunnerDataFromFile(rrDataHandle, fName)

## \brief Create RoadRunnerData from a file
## \param fName Name of input file, including path. If no path is given, the file is read
## in current working directory
## \return Returns a handle to RoadRunner data if successful, None otherwise
## \note Use the freeRoadRunnerData to free memory allocated by the returned data
## \ingroup utilities
rrpLib.createRoadRunnerData.restype = c_void_p
def createRoadRunnerDataFromFile(fName):
    #Create a RoadRunner data object
    rrDataHandle = rrpLib.createRoadRunnerData(0,0,"")
    if rrpLib.readRoadRunnerDataFromFile(rrDataHandle, fName) == False:
        print 'Failed to read data'
    return rrDataHandle

def getText(fName):
    file = open(fName, 'r')
    return file.read()

## \brief Reads the entire contents of a file and returns it as a string
##@code
## str = readAllText ("mytextfile.txt")
##@endcode

def readAllText(fName):
    file = open(fName, 'r')
    str = file.read()
    file.close()
    return str

## \brief Free RoadRunnerData
## \param dataHandle Handle to a roadrunner data object
## \return Returns True or false indicating result
## \ingroup utilities
rrpLib.freeRoadRunnerData.restype = c_bool
def freeRoadRunnerData(rrDataHandle):
    return rrpLib.freeRoadRunnerData(rrDataHandle)

## \brief Get last (API) error. This returns the last error if any.
## \return Returns a string with an error success, None otherwise
## \ingroup utilities
rrpLib.getLastPluginError.restype = c_char_p
def getLastError():
    return rrpLib.getLastPluginError()

## \brief Unload the plugins api shared library
## \ingroup utilities
def unLoadAPI():
    windll.kernel32.FreeLibrary(rrpLib._handle)


##\mainpage Front page for RoadRunners PluginLib Python wrapper
#\section Introduction
#Roadrunners plugin library exposes a simple framework for adding functionality to RoadRunner core, by means of
#external plugins.
#The code fragment below shows briefly how to load plugins, check for plugins, and use an individual plugin.
#
#\include rrPluginTester.py
#
# The above code produces the following output:
#@code
##*** Python 2.7.3 (default, Apr 10 2012, 23:31:26) [MSC v.1500 32 bit (Intel)] on win32. ***
##>>>
##*** Remote Interpreter Reinitialized  ***
##>>>
##The plugin manager will look for plugins in the following folder: R:\installs\vs_debug\plugins
##Number of Plugins: 2
##Plugin Names: ['AddNoise', 'Levenberg-Marquardt']
##PluginName: 'AddNoise'
##Name..........................AddNoise
##Author........................Totte Karlsson
##Category......................Signal Processing
##Version.......................1.0
##Copyright.....................Totte Karlsson, Herbert Sauro, Systems Biology, UW 2012
##
##PluginProperties: ['NoiseType', 'Sigma', 'InputData']
##True
##done
##>>>
#@endcode
#    \section plugins_overview Overview
#    The libRoadRunner Plugin API is centered around three important concepts:
#    - A Plugin Manager
#    - Plugins
#    - Plugin Properties
#
#    \section plugins_usage How to use plugins
#    A typical use case of the Plugin API may be as follows:
#
#    -# Client creates a PluginManager.
#    -# Client load plugins using the Plugin Manager.
#    -# Client get a handle to a plugin.
#    -# Client get a handle to a specific property in the plugin.
#    -# Client set the value of the property.
#    -# Client excutes the plugin.
#    -# Client retrieve the value of a plugins property, e.g. a "result" property.
#   \subsection pluginEvents PluginEvent functionality
# In addition to data properties that communicate data between a client and the plugin, the framework also support for a variety of  plugin event functions.
# In short, an event is a regular function that is defined and implemented by the client of a plugin, but executed from within the plugin, during the plugins
# execution.
#
# A single plugin may support of up to three event functions. The intended use of these functions are to signal the events of the following:
#   -# Plugin Initialization
#   -# Plugin Progress
#   -# Plugin Finalization
#
# Each event function support up to two opaque data properties. The plugin documentation needs to provide the exact type of these arguments.
# In it simplest form, a plugin may choose to define an event function taking no arguments at all.
# Below are listed a few properties, characteristics of events in the RoadRunner Plugin framework.
#   -# A plugin event is a regular function defined by the client of the plugin.
#   -# A plugin event function do not return any value.
#   -# The type and number of arguments needed in the plugin event is defined by the plugin (see plugin docs).
#   -# Plugin events are assigned to the plugin before a plugins execute function.
#   -# Assigning events is optional. A plugins internal work should not be affected wether an event is assigned or not.
#   -# Plugin events are blocking functions. If the work in a plugin is executed in a thread, see executeEx, the plugin event
#   will be executed in the same thread as the plugin worker. Depending on your environment and if the plugin event function is executed in a separate
# thread, regular use of thread synchronization measuress may be needed in order to not create an unstable system.
#
#   See the examples page that provide example code on how to use plugins, properties and event functions.
#    \section plugins_writing How to write plugins
#    \note Writing plugins in Python is not yet supported
#
# \section main_section Using rrPlugins.py
# In order to use this wrapper (rrPlugins.py), your systems environmental Python path variable, i.e. PYTHONPATH, needs to include the folder where the wrapper script is located, e.g.
# "c:\\roadrunner-1.0.0\\plugins\\python". Currently, this need to be set manually by the user.
#
# \defgroup plugin_manager Plugin Manager
# \brief Plugin Manager Library Functions
# The Plugin manager loads and manages one or more plugins. Handles to individual plugins are obtained
# by the getFirstPlugin, getNextPlugin etc functions, or the getPlugin(pluginName) function.
#
# The basic approach to using the plugin system is:
#
# 1. Create a plugin manager first
#
# 2. Load the plugins using loadPlugins (all) or loadPlugin (specific one)
#
# 3. Obtain the plugin handle using getPlugin or directly from loadPlugin (singular)
#
# 4. Using the plugin handle, set values to the plugin properties
#
# 5. Run the plugin method execute(pluginHandle)
#
# 6. Retrieve results from plugin properties
# \defgroup plugins Plugin Functions
# \brief Functions operating on Plugin Handles.
#
# \defgroup plugin_properties Plugin Properties
# \brief Plugins Property related functions
# The plugin system supports property objects, these objects contain a variety of information about a given property, these include:
# the name, value, type, hint, and a description. The following types are currently supported, Booleans, integers, doubles, strings,
# list of property objects and the roadRunner data array format. Properties can also be grouped into convenient categories which can be useful
# for GUI applications. Every plugin exposes as a set of properties than can be inspected and set by a host application.
# The list of plugin properties will be called the pluginProperties. Within the pluginProperties are individual property entries.
# As already aluded to, these property entries can store a variety of different data types, incuding additional lists of properties. Such lists
# are popoluated by creating new properties using the createProperty method and then added to the list using the addPropertyToList method.
# In the followng a propertyHandle points to a single property object.
#
# \defgroup utilities Utility Functions
# \brief Functions to help and assist in the use of the Plugins framework

# \defgroup examples Python Example Scripts
# \brief Scripts illuminating concepts regarding RoadRunner Plugins

## \example rrPluginTester.py
## This Example shows
## -# How to create a plugin manager
## -# Get Plugin Names
## -# Get a handle to a plugin
## -# Obtain some info from the plugin

## \example rrPluginProperty.py
## This Example shows
## -# Get a handle to a property in a Plugin
## -# Obtain some info about the property
## -# Getting the value of the property
## -# Setting the value of the property

## \example rrPluginDocumentation.py
## This Example shows
## -# Get a plugin's categories in the form of an XML string
## -# Obtain and view a Plugin's documentation as a PDF (Needs a system PDF reader)

## \example rrEventFunction.py
## This Example shows
## -# How to define Python event functions and passing them to a plugin

## \example rrNoisePlugin.py
## This Example Demonstrate the use of the AddNoise plugin

## \example rrLevenbergMarquardt.py
## This Example Demonstrate the use of the Minimization Plugin, using the Levenberg-Marquardt algorithm.
