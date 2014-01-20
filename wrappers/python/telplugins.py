##@Module telPlugins_C_API

## Wrapper around C API to help avoid use of handle.
# An example is given at the end of the code.

import telplugins_c_api as tpc
import matplotlib.pyplot as plt
import os.path
import ctypes

__version__ = "0.6.5"

## \brief DataSeries class for handling roadrunner data types
class DataSeries(object):

    _data = 0
    _myData = False
    ## \brief Constructor for DataSeries class 
    ##@code
    ## d = DataSeries()
    ## d = DataSeries (rr)
    ##@endcode
    def __init__ (self, handle=None, myData = False):
        if handle == None:
           self._myData = True
           self._data = tpc.telLib.createTelluriumData(0, 0, "")           
        else:   
           self._data = handle
           self._myData = myData 
           

    @classmethod
    def fromNumPy(cls, numPyData):
        
        if len (numPyData.shape) != 2:
            raise ValueError ('fromNumPy only accepts two dimensional arrays')
            
        nrCols  = numPyData.shape[1]
        nrRows  = len(numPyData)   
        # If there are no column names then make some up                     
        if numPyData.dtype.names == None:
            colHdr = []
            for i in range (nrCols):
                colHdr.append ('x' + str (i))               
        else:
           colHdr  = numPyData.dtype.names 

        columnStr = str(colHdr).strip('[]')
        dataHandle = tpc.telLib.createTelluriumData(nrRows,nrCols, columnStr)        
                
        #Copy the data
        for row in range(nrRows):
            for col in range(nrCols):                
                val = numPyData[row][col] 
                tpc.setTelluriumDataElement(dataHandle, row, col, val)        
        return cls(dataHandle, True)
    
    def __del__ (self):
        if (self._data != 0):
            try:
                if self._myData == True:
                    tpc.freeTelluriumData (self._data)
                #else:                    
                #    print 'not freeing data'
            except:
                print "Failed freeing data in DataSeries"
            self._data = 0

    def __getHandle (self):
        return self._data
        
    # Use x.rows to get the number of rows    
    def __getNumberOfRows (self):
        return tpc.telLib.getTelluriumDataNumRows(self._data)
    # Use x.toNumpy to get NumPy array
    def __toNumpy (self):
        return tpc.getNumpyData (self._data)

    # Use x.cols to get the number of columns    
    def __getNumberOfColumns (self):
        return tpc.telLib.getTelluriumDataNumCols(self._data)
     
    # Use x.toNumpy to get NumPy array
    def __toNumpy (self):
        return tpc.getNumpyData (self._data)

    ## \brief Retrive the column headers as a list
    ##@code
    ## print d.getColumnHeaders()
    ##@endcode
    def getColumnHeaders (self):
        value = tpc.telLib.getTelluriumDataColumnHeader(self._data)
        if value == None:
           value = []
        return value

    ## \brief Get a specific element from a dataseries
    ##@code
    ## print d.getElement (1,2)
    ##@endcode       
    def getElement (self, row, col):
        rowCount = tpc.telLib.getTelluriumDataNumRows(self._data)
        colCount = tpc.telLib.getTelluriumDataNumCols(self._data)
        if (row < 0) or (col < 0):
            raise Exception("DataSeries indices must be positive")
        if row >= rowCount:
            raise Exception("Row index out of bounds in dataseries element access")
        if col >= colCount:
            raise Exception("Column index out of bounds in dataseries element access")

        val = ctypes.c_double()
        if tpc.telLib.getTelluriumDataElement(self._data, row, col, ctypes.byref(val)) == True:
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
    @classmethod      
    def readDataSeries(cls, fileName):
        if not os.path.isfile (fileName):
            raise Exception ("File not found: " + fileName)
        data = tpc.createTelluriumDataFromFile (fileName)
        return cls (data, True)

    ## \brief Write a dataseries to a file
    ##@code
    ## d.writeDataSeries ("myDataSeries.txt")
    ##@endcode       
    def writeDataSeries(self, fileName):
        tpc.writeTelluriumData(self._data, fileName)

    ## \brief Plot a dataseries as a graph
    ##@code
    ## d.plot()
    ##@endcode       
    def plot (self):
         hdr = tpc.getTelluriumDataColumnHeader(self._data)
         npData = tpc.getNumpyData(self._data)
         tpc.plotTelluriumData(npData, hdr)

    data = property (__getHandle)

    ## \brief Return a numpy array from a data series
    ##@code
    ## myarray = d.toNumpy
    ##@endcode         
    toNumpy = property (__toNumpy)
    
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

_pluginManager = tpc.createPluginManager()
_pluginsAlreadyLoaded = False

class Plugin (object):

    _OnProgressList = Event()
    _onProgressEvent = 0
    _propertyNames = []

    ## \brief Create a Plugin instance
    ##@code
    ## myPlugin = Plugin ("tel_add_noise")
    ##@endcode         
    def __init__(self, pluginName):
        self.pluginName = pluginName
        self.plugin = tpc.loadPlugin (_pluginManager, pluginName)
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
           if not tpc.setPluginProperty (self.plugin, name, value.data):
              raise TypeError ("Unable to locate property: ", name)
        else:
           handle  = tpc.getPluginProperty(self.plugin, name);
           if handle == 0:
              raise ValueError ("Unable to locate property: ", name)
           t1 = tpc.getPropertyType (handle)
           if (t1 == "listOfProperties"):
              if isinstance (value, list):
                 if len(value) != 2:
                    raise TypeError ("Expecting two elements in the property list")
                 if not isinstance(value[0], str):
                     raise TypeError("Expecting property name in first element of list")
                 if (not isinstance(value[1], float)) and (isinstance(value[1], int)):
                     raise TypeError("Expecting floating value in second element of list")
                 para1 = tpc.createProperty(value[0], "double", "", value[1])
                 tpc.addPropertyToList (handle, para1)
              else:
                 raise  TypeError ("Expecting a list in setProperty")
           else:
              tpc.setPluginProperty (self.plugin, name, value)

    ## \brief Get the value for a given propoerty in the plugin.
    ##@code
    ## print myPlugin.getProperty("Sigma")
    ##@endcode         
    def getProperty (self, name):
        handle = tpc.getPluginProperty (self.plugin, name)
        if handle == 0:
            raise ValueError ("Property: " + name + " does not exist")
        value = tpc.getProperty (handle)
        if (tpc.getPropertyType(handle) == "roadRunnerData"):
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
        nameList = tpc.getListOfPluginPropertyNames (self.plugin)
        aList = []
        for i in range (0, len (nameList)):
            name = nameList[i]
            handle = tpc.getPluginProperty(self.plugin, nameList[i])
            hint = tpc.getPropertyHint(handle)
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
        nameList = tpc.getListOfPluginPropertyNames (self.plugin)
        aList = []
        for i in range (0, len (nameList)):
            name = nameList[i]
            handle = tpc.getPluginProperty(self.plugin, nameList[i])
            descr = tpc.getPropertyDescription(handle)
            aList.append ([name, descr])
        return aList

    ## \brief List all the property hints in the plugin
    ##@code
    ## print myPlugin.listOfPropertyHints()
    ##@endcode         
    def listOfPropertyHints (self):
        nameList = tpc.getListOfPluginPropertyNames (self.plugin)
        aList = []
        for i in range (0, len (nameList)):
            name = nameList[i]
            handle = tpc.getPluginProperty(self.plugin, nameList[i])
            descr = tpc.getPropertyHint(handle)
            aList.append ([name, descr])
        return aList

    ## \brief List all the property hints in the plugin
    ##@code
    ## print myPlugin.listOfPropertyHints()
    ##@endcode         
    def loadDataSeriesAsNumPy (self, fileName):
        rrDataHandle = tpc.createTelluriumDataFromFile (fileName)
        return tpc.getNumpyData (rrDataHandle)

    def OnProgress (self, f):
        # Make sure garbage collector doens't remove the event pointer
        global _onProgressEvent

        _onProgressEvent =  tpc.NotifyEventEx (f)
        # Pass the address of the self object
        theId = id (self)
        tpc.assignOnProgressEvent(self.plugin, _onProgressEvent, theId, None)

    ## \brief Execute the plugin
    ##@code
    ## print myPlugin.execute()
    ##@endcode         
    def execute (self):
        return tpc.executePlugin (self.plugin)

    def executeEx (self, inThread):
        return tpc.executePluginEx (self.plugin, inThread)

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
        tpc.loadPlugins (self.pluginsManager)

    ## \brief Static method to list all plugins
    ##@code
    ## print Plugin.listOfPlugins()
    ##@endcode         
    @staticmethod
    def listOfPlugins():
        global _pluginsAlreadyLoaded
        # Hack to get round bug in loadPlugins
        if not _pluginsAlreadyLoaded:
           tpc.loadPlugins (_pluginManager)
           _pluginsAlreadyLoaded = True

        aList = []
        names = tpc.getPluginLibraryNames (_pluginManager)
        n = tpc.getNumberOfPlugins (_pluginManager)
        print names
        print n
        # This is a hack to get round thelack of metadata in the plugin
        # Will be resolved in next revision of library
        for i in range (0, n):
            handle = tpc.getPlugin(_pluginManager, names[i])
            info = tpc.getPluginInfo (handle)
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
        tpc.displayPluginManual(self.plugin)

    ## \brief Returns the name of the plugin
    ##@code
    ## print myPlugin.name()
    ##@endcode         
    def name (self):
        return tpc.getPluginName(self.plugin)

    ## \brief Returns the description of the plugin
    ##@code
    ## print myPlugin.description()
    ##@endcode         
    def description (self):
        return tpc.getPluginDescription(self.plugin)

    ## \brief Returns the hint of the plugin
    ##@code
    ## print myPlugin.hint()
    ##@endcode         
    def hint (self):
        return tpc.getPluginHint(self.plugin)

     
    def info (self):
        return tpc.telLib.getPluginInfo(self.plugin)

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

def getTelluriumData (rr):
    rrDataHandle = tpc.getTelluriumDataHandle(rr)
    return DataSeries (rrDataHandle)

def getDataSeries (numPyData):    
    return DataSeries.fromNumPy(numPyData)

##if __name__=='__main__':
##    ## \brief Load a data series from a file
    ##@code
    ## print myPlugin.loadDataSeries("myDataSeries.txt")
    ##@endcode         
    def loadDataSeries (self, fileName):
        handle = tpc.createTelluriumDataFromFile (fileName)
        return DataSeries(handle)

##    print "Starting Test"
##
##    p = Plugin ("tel_add_noise")
##    p.viewManual()
##    #pl = p.listOfProperties()
##    #for item in pl:
##    #    print item
##
##    p.Sigma = 0.00005
##
##    series = p.loadDataSeries ("..\\Examples\\testData.dat")
##    p.plotDataSeries (series)
##    p.InputData = series
##    p.execute()
##    p.plotDataSeries (p.InputData)
##
##    print "Test Finished"

##\mainpage Python support code for working with RoadRUnner Plugins
##\section Introduction
#Wrapper around the Python Plugin C API to help avoid the use of handles.
#The code fragment below shows briefly how to create a plugin object and access the plugin properties.
#
#@code
##import roadrunner
##from telPlugins_CAPI import *
##import telPlugins as tel
##
##noisePlugin = tel.Plugin ("tel_add_noise")
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
##d = tel.getTelluriumData (rr)
##
##noisePlugin.InputData = d
##
## Get parameter for the 'size' of the noise
##noisePlugin.Sigma = 3.e-5
##
##noisePlugin.execute ()
##
##numpydata = noisePlugin.InputData.toNumpy;
##
##tel.plot (numpydata[:,[0,2]], myColor="blue", myLinestyle="-", myMarker="", myLabel="S1")
##
##tel.show()
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
#p = Plugin("add")
#p.x = 3.4
#p.y = 5.6
#p.execute()
#print p.result
#@endcode
