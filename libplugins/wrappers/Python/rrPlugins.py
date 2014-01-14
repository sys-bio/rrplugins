##@Module rrPlugins_CAPI

## Wrapper around C API to help avoid use of handle.
# An example is given at the end of the code.

import rrPlugins_CAPI as rrp
import matplotlib.pyplot as plt
import os.path
import ctypes

__version__ = "0.6.3"

## \brief DataSeries class for handling roadrunner data types

class DataSeries(object):

    _data = 0

    ## \brief Constructor for DataSeries class 
    ##@code
    ## d = DataSeries()
    ## d = DataSeries (rr)
    ##@endcode
    def __init__ (self, handle=None):
        if handle == None:
           self._data = rrp.rrpLib.createRoadRunnerData(0,0,"")
        else:   
           self._data = handle

    def __del__ (self):
        if (self._data != 0):
            try:
               rrp.freeRoadRunnerData (self._data)
            except:
                print "Exception"
            self._data = 0

    def __getHandle (self):
        return self._data
        
    # Use x.rows to get the number of rows    
    def __getNumberOfRows (self):
        return rrp.rrpLib.getRoadRunnerDataNumRows(self._data)

    # Use x.cols to get the number of columns    
    def __getNumberOfColumns (self):
        return rrp.rrpLib.getRoadRunnerDataNumCols(self._data)
        
    ## \brief Retrive the column headers as a list
    ##@code
    ## print d.getColumnHeaders()
    ##@endcode
    def getColumnHeaders (self):
        value = rrp.rrpLib.getRoadRunnerDataColumnHeader(self._data)
        if value == None:
           value = []
        return value

    # Use x.AsNumpy to get NumPy array
    def __AsNumpy (self):
        return rrp.getNumpyData (self._data)
        
    ## \brief Get a specific element from a dataseries
    ##@code
    ## print d.getElement (1,2)
    ##@endcode       
    def getElement (self, row, col):
        rowCount = rrp.rrpLib.getRoadRunnerDataNumRows(self._data)
        colCount = rrp.rrpLib.getRoadRunnerDataNumCols(self._data)
        if (row < 0) or (col < 0):
            raise Exception("DataSeries indices must be postive")
        if row >= rowCount:
            raise Exception("Row index out of bounds in dataseries element access")
        if col >= colCount:
            raise Exception("Column index out of bounds in dataseries element access")

        val = ctypes.c_double()
        if rrp.rrpLib.getRoadRunnerDataElement(self._data, row, col, ctypes.byref(val)) == True:
           return val.value
        else:
           # !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                    
           # Is there a getLastError for this?
           raise Exception("Unable to retrieve element")

    ## \brief Set a specific element
    ##@code
    ## d.setElement (1,2, 3.1415)
    ##@endcode       
    def setElement (self, row, col, value):
        raise Exception ("setElement not yet implemented")

    ## \brief Read a dataseries from a file
    ##@code
    ## d.readDataSeries ("myDataSeries.txt")
    ##@endcode       
    def readDataSeries(self, fileName):
        if not os.path.isfile (fileName):
            raise Exception ("File not found: " + fileName)
        self._data = rrp.createRoadRunnerDataFromFile (fileName)

    ## \brief Write a dataseries to a file
    ##@code
    ## d.writeDataSeries ("myDataSeries.txt")
    ##@endcode       
    def writeDataSeries(self, fileName):
        rrp.writeRoadRunnerData(self._data, fileName)

    data = property (__getHandle)

    ## \brief Return a numpy array from a data series
    ##@code
    ## myarray = d.AsNumpy
    ##@endcode         
    AsNumpy = property (__AsNumpy)
    
    ## \brief Return the number of rows in the data series
    ##@code
    ## print d.rows
    ##@endcode         
    rows = property (__getNumberOfRows)

    ## \brief Return the number of columns in the data series
    ##@code
    ## print d.cols
    ##@endcode         
    cols = property (__getNumberOfColumns)


# ------------------------------------------------------------------------

class Event(object):

    def __init__(self):
        self.handlers = []

    def add(self, handler):
        self.handlers.append(handler)
        return self

    def remove(self, handler):
        self.handlers.remove(handler)
        return self

    def fire(self, sender, earg=None):
        for handler in self.handlers:
            handler(sender, earg)

    __iadd__ = add
    __isub__ = remove
    __call__ = fire



# ------------------------------------------------------------------------

_pluginManager = rrp.createPluginManager()
_pluginsAlreadyLoaded = False

class Plugin (object):

    _OnProgressList = Event()
    _onProgressEvent = 0
    _propertyNames = []

    ## \brief Create a Plugin instance
    ##@code
    ## myPlugin = Plugin ("rrp_add_noise")
    ##@endcode         
    def __init__(self, pluginName):
        self.pluginName = pluginName
        self.plugin = rrp.loadPlugin (_pluginManager, pluginName)
        if not self.plugin:
            return
        else:
            lp = self.listOfProperties()
            for element in lp:
                self._propertyNames.append (element[0])
      
    ## \brief Set a given propoerty in the plugin.
    ##@code
    ## myPlugin.setProperty ("Sigma", 0.1)
    ##@endcode         
    def setProperty(self, name, value):
        if (isinstance (value, DataSeries)):
           if not rrp.setPluginProperty (self.plugin, name, value.data):
              raise TypeError ("Unable to locate property: ", name)
        else:
           handle  = rrp.getPluginProperty(self.plugin, name);
           if handle == 0:
              raise ValueError ("Unable to locate property: ", name)
           t1 = rrp.getPropertyType (handle)
           if (t1 == "listOfProperties"):
              if isinstance (value, list):
                 if len(value) != 2:
                    raise TypeError ("Expecting two elements in the property list")
                 if not isinstance(value[0], str):
                     raise TypeError("Expecting property name in first element of list")
                 if (not isinstance(value[1], float)) and (isinstance(value[1], int)):
                     raise TypeError("Expecting floating value in second element of list")
                 para1 = rrp.createProperty(value[0], "double", "", value[1])
                 rrp.addPropertyToList (handle, para1)
              else:
                 raise  TypeError ("Expecting a list in setProperty")
           else:
              rrp.setPluginProperty (self.plugin, name, value)

    ## \brief Get the value for a given propoerty in the plugin.
    ##@code
    ## print myPlugin.getProperty("Sigma")
    ##@endcode         
    def getProperty (self, name):
        handle = rrp.getPluginProperty (self.plugin, name)
        if handle == 0:
            raise ValueError ("Property: " + name + " does not exist")
        value = rrp.getProperty (handle)
        if (rrp.getPropertyType(handle) == "roadRunnerData"):
            return DataSeries (value)
        else:
           return value

    def __setattr__ (self, name, value):
        if (name in self._propertyNames):
           self.setProperty (name, value)
        else:
            super(Plugin, self).__setattr__(name, value)

    def __getattr__ (self, name):
        if name in self._propertyNames:
          return self.getProperty(name)
        else:  raise AttributeError, name

    ## \brief List all the properties in the plugin
    ##@code
    ## print myPlugin.listOfProperties()
    ##@endcode         
    def listOfProperties (self):
        if not self:
            return []
        nameList = rrp.getListOfPluginPropertyNames (self.plugin)
        aList = []
        for i in range (0, len (nameList)):
            name = nameList[i]
            handle = rrp.getPluginProperty(self.plugin, nameList[i])
            hint = rrp.getPropertyHint(handle)
            aList.append ([name, hint])
        return aList

    ## \brief List all the property descriptions in the plugin
    ##@code
    ## print myPlugin.listOfPropertyDescriptions()
    ##@endcode 
    ##@code
    ## import pprint
    ## print pprint.pprint (na.listOfProperties())  
    ##@endcode    
    def listOfPropertyDescriptions (self):
        nameList = rrp.getListOfPluginPropertyNames (self.plugin)
        aList = []
        for i in range (0, len (nameList)):
            name = nameList[i]
            handle = rrp.getPluginProperty(self.plugin, nameList[i])
            descr = rrp.getPropertyDescription(handle)
            aList.append ([name, descr])
        return aList

    ## \brief List all the property hints in the plugin
    ##@code
    ## print myPlugin.listOfPropertyHints()
    ##@endcode         
    def listOfPropertyHints (self):
        nameList = rrp.getListOfPluginPropertyNames (self.plugin)
        aList = []
        for i in range (0, len (nameList)):
            name = nameList[i]
            handle = rrp.getPluginProperty(self.plugin, nameList[i])
            descr = rrp.getPropertyHint(handle)
            aList.append ([name, descr])
        return aList

    ## \brief List all the property hints in the plugin
    ##@code
    ## print myPlugin.listOfPropertyHints()
    ##@endcode         
    def loadDataSeriesAsNumPy (self, fileName):
        rrDataHandle = rrp.createRoadRunnerDataFromFile (fileName)
        return rrp.getNumpyData (rrDataHandle)

    ## \brief Load a data series from a file
    ##@code
    ## print myPlugin.loadDataSeries("myDataSeries.txt")
    ##@endcode         
    def loadDataSeries (self, fileName):
        handle = rrp.createRoadRunnerDataFromFile (fileName)
        return DataSeries(handle)

    def OnProgress (self, f):
        # Make sure garbage collector doens't remove the event pointer
        global _onProgressEvent

        _onProgressEvent =  rrp.NotifyEventEx (f)
        # Pass the address of the self object
        theId = id (self)
        rrp.assignOnProgressEvent(self.plugin, _onProgressEvent, theId, None)

    ## \brief Execute the plugin
    ##@code
    ## print myPlugin.execute()
    ##@endcode         
    def execute (self):
        return rrp.executePlugin (self.plugin)

    def executeEx (self, inThread):
        return rrp.executePluginEx (self.plugin, inThread)


    def plotDataSeries (self, dataSeries):
        if (isinstance (dataSeries, DataSeries)):
           if dataSeries.data == 0:
              exit()
           hdr = rrp.getRoadRunnerDataColumnHeader(dataSeries.data)
           npData = rrp.getNumpyData(dataSeries.data)
           rrp.plotRoadRunnerData(npData, hdr)
        else:
           raise TypeError ("Expecting DataSeries type")


    ## \brief Read all text from a file
    ##@code
    ## print myplugin.readAllText ("myfile.txt")
    ##@endcode         
    def readAllText(self, fName):
        file = open(fName, 'r')
        str = file.read()
        file.close()
        return str

    def loadPlugins(self):
        rrp.loadPlugins (self.pluginsManager)

    ## \brief Static method to list all plugins
    ##@code
    ## print Plugin.listOfPlugins()
    ##@endcode         
    @staticmethod
    def listOfPlugins():
        global _pluginsAlreadyLoaded
        # Hack to get round bug in loadPlugins
        if not _pluginsAlreadyLoaded:
           rrp.loadPlugins (_pluginManager)
           _pluginsAlreadyLoaded = True

        aList = []
        names = rrp.getPluginLibraryNames (_pluginManager)
        n = rrp.getNumberOfPlugins (_pluginManager)
        # This is a hack to get round thelack of metadata in the plugin
        # Will be resolved in next revision of library
        for i in range (0, n):
            handle = rrp.getPlugin(_pluginManager, names[i])
            info = rrp.getPluginInfo (handle)
            info = info.split ("\n")
            hint = info[2]
            hint = hint.replace("Category......................", "")
            aList.append ([names[i], hint])
        return aList

    ## \brief If a plugin has a manual, view it
    ##@code
    ## myPlugin.viewManual()
    ##@endcode         
    def viewManual (self):
        rrp.displayPluginManual(self.plugin)

    ## \brief Returns the name of the plugin
    ##@code
    ## print myPlugin.name()
    ##@endcode         
    def name (self):
        return rrp.getPluginName(self.plugin)

    ## \brief Returns the description of the plugin
    ##@code
    ## print myPlugin.description()
    ##@endcode         
    def description (self):
        return rrp.getPluginDescription(self.plugin)

    ## \brief Returns the hint of the plugin
    ##@code
    ## print myPlugin.hint()
    ##@endcode         
    def hint (self):
        return rrp.getPluginHint(self.plugin)

     
    def info (self):
        return rrp.rrpLib.getPluginInfo(self.plugin)

# ----------------------------------------------------------------

def extractColumn (data, index):
    return data[:,index]

def plot (data, myColor="red", myLinestyle="None", myMarker="None", myLabel=""):
    columns = data.shape[1]
    for i in range(columns-1):
        p = plt.plot (data[:,0], data[:,i+1])
        plt.setp (p, color=myColor, marker=myMarker, linestyle = myLinestyle, linewidth=1, label=myLabel)
        plt.legend(bbox_to_anchor=(1.05, 1), loc=1, borderaxespad=0.)
        return p

def show():
    plt.show()

def getRoadRunnerData (rr):
    rrDataHandle = rrp.getRoadRunnerDataHandle(rr)
    return DataSeries (rrDataHandle)

if __name__=='__main__':

    print "Starting Test"

    p = Plugin ("rrp_add_noise")
    p.viewManual()
    #pl = p.listOfProperties()
    #for item in pl:
    #    print item

    p.Sigma = 0.00005

    series = p.loadDataSeries ("..\\Examples\\testData.dat")
    p.plotDataSeries (series)
    p.InputData = series
    p.execute()
    p.plotDataSeries (p.InputData)

    print "Test Finished"

##\mainpage Python support code for working with RoadRUnner Plugins
##\section Introduction
#Wrapper around the Python Plugin C API to help avoid the use of handles.
#The code fragment below shows briefly how to create a plugin object and access the plugin properties.
#
#@code
##import roadrunner
##from rrPlugins_CAPI import *
##import rrPlugins as rrp
##
##noisePlugin = rrp.Plugin ("rrp_add_noise")
##print noisePlugin.name()
##print noisePlugin.hint()
##print noisePlugin.description()
##
##print noisePlugin.listOfProperties()
##
### Create a roadrunner instance
##rr = roadrunner.RoadRunner()
##rr.load("sbml_test_0001.xml")
##
## Generate data
##rr.simulate(0, 10, 511) # Want 512 points
##
## The plugin will need a handle to the underlying roadrunner data
##d = rrp.getRoadRunnerData (rr)
##
##noisePlugin.InputData = d
##
## Get parameter for the 'size' of the noise
##noisePlugin.Sigma = 3.e-5
##
##noisePlugin.execute ()
##
##numpydata = noisePlugin.InputData.AsNumpy;
##
##rrp.plot (numpydata[:,[0,2]], myColor="blue", myLinestyle="-", myMarker="", myLabel="S1")
##
##rrp.show()
##
##d.writeDataSeries ("testData2.dat")
##
##d.readDataSeries ("testData2.dat")
##print "done"
#@endcode
#
##\section Plugins
# Plugin objects are instanciated using Plugin class. For example to instanciate a plugin called myplugin, we would
# use the code:
#@code
#p = Plugin ("myplugin")
#@endcode
#All interactions with plugins are via plugin properties. Values can be set and retrieved via plugin properties.
#For example, if a plugin has a property sigma, we can assign or access the value using the code:
#@code
#p.sigma = 0.1
#print p.sigma
#@endcode
#Plugins have a single method that can be used to excecute the plugin's functionality:
#@code
#p.execute()
#@endcode
#Once a plugin has been executed, any output from the plugin can be retrieved via propoerties. Let's 
#suppose for example there is a plugin all add, which has three properties called, x, y and result. When executed
#the plugin will take the values in x and y, compute the sum and assign it to result. The plugin can therefore
#be used as follows:
#@code
p = Plugin("add")
p.x = 3.4
p.y = 5.6
p.execute()
print p.result
#@endcode
