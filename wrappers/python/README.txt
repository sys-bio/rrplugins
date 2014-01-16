libRoadRunners Python PluginAPI using ctypes

The rrPlugins_CAPI.py file is a python wrapper using ctypes and RoadRunners rrplugins_c_api library.
If you import this script in your own script, you will get access to the functionality as documented 
on the RoadRunner website:
http://docs.libroadrunner.org/rrLibPluginsPythonAPI/html/index.html

On top of the API defined by rrPlugins_CAPI.py, another user friendly API is defined, in the file rrPlugins.py.

Necessary files in this folder should be installed to your systems python installations site-packages folder, 
using the install_plugins_win.py script.

==== IMPORTANT NOTES ====
To use rrPlugins.py in your own scripts, or if you are to run the example scripts, 
the following requirements need to be satisfied

1) The roadrunner "bin" folder need to be on your user PATH, or system PATH, 
    e.g. add c:\libroadrunner-1.0.0-win32\bin to the PATH environment variable
    if you unzipped the distribution in the c:\libroadrunner-1.0.0-win32 folder

=================================================================================

=== ADDITIONAL NOTES ====
The Example folder contains Examples illustrating how to get access and use the pluginlibrary and plugins.
See further API documentation on the web, http://libroadrunner.org/ on how to use roadrunner plugins from python.

by Totte Karlsson and Herbert Sauro.
