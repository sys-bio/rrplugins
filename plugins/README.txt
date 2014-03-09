This directory contains Tellurium plugins. 

List of Plugins expected in a official Tellurium release:

* tel_add_noise.dll
This plugin can be used to generate Gaussian noise and adding it to Tellurium data. This is useful for generating synthetic data sets to test
various algorithms, e.g. parameter fitting algorithms.

* tel_test_model.dll
This plugin contain an embedded test model. Upon execute(), plugin properties are populated holding test data and test data with noise.


* tel_chisquare.dll
This plugin is used to calculate the chisquare for two data sets.

* tel_levenberg_marquardt.dll
This plugin implements the Levenberg-Marquardt optimizer for fitting multi parameter data to models.


See libroadrunner.org for details.



