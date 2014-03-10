Folder containing example/demo scripts on how to use plugins.

The following folders are currently part of the Tellurium plugin distribution
== basic ==
    Contain various scripts deomonstrating basic interaction with the plugin system

== parameter_minimization ==
    Scripts and examples using minimization plugins

== statistics ==
    Scripts showing how to use various statistic features of plugins


In addition, this current folder contain one example script for each released plugin:

* telTestModel.py                   - Demonstrate usage of the TestModel plugin
* telAddNoise.py                    - Demonstrate usage of the AddNoise plugin
* telChiSquare.py                   - Demonstrate usage of the ChiSquare plugin
* telLevenbergMarquardt.py          - Demonstrate usage of the Levenberg-Marquardt plugin
* telNelderMead.py                  - Demonstrate usage of the Nelder-Mead plugin

Info: Each of the above examples will attempt to open the plugins embedded PDF documentation on exit. 

==============================================================================================
OBSERVE: Make sure you have properly installed Tellurium plugins in your python environment 
before running any of these scripts. A good test is to execute 'import telplugins', with no quotes, at your python 
prompt. It should come back with no message.
==============================================================================================
