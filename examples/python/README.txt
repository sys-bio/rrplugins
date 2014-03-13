Folder containing example/demo scripts demonstrating plugin usage.

In addition, this current folder contain one example script for each released plugin:

* telTestModel.py                   - Demonstrate usage of the TestModel plugin
* telAddNoise.py                    - Demonstrate usage of the AddNoise plugin
* telChiSquare.py                   - Demonstrate usage of the ChiSquare plugin
* telLevenbergMarquardt.py          - Demonstrate usage of the Levenberg-Marquardt plugin
* telNelderMead.py                  - Demonstrate usage of the Nelder-Mead plugin

Info: Each of the above examples will attempt to open the plugins embedded PDF documentation on exit. 

The following folders contain various scripts, organized into categories. 
== basic ==
    Contain various scripts demonstrating basic interaction with the plugin system

== parameter_minimization ==
    Scripts and examples using minimization plugins

== statistics ==
    Scripts demonstrating various statistic features, e.g. Q_Q plots and noise statistics.

Any questions should be addressed to Totte Karlsson (totte@dunescientific.com)

==============================================================================================
OBSERVE: Make sure you have properly installed Tellurium plugins in your python environment 
before running any of these scripts. A good test is to execute 'import telplugins', with no quotes, at your python 
prompt. It should come back with no message.
==============================================================================================
