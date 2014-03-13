This directory contains Tellurium plugins. 

List of Plugins expected in a official Tellurium release:

* tel_test_model.dll 1.0.0 
This plugin contain an embedded test model. Upon execute(), plugin properties are populated holding test data and test data with noise.

* tel_add_noise.dll 1.0.0
This plugin can be used to generate Gaussian noise and adding it to Tellurium data. This is useful for generating synthetic data sets to test
various algorithms, e.g. parameter fitting algorithms.

* tel_chisquare.dll  1.0.0
This plugin is used to calculate the chisquare for two data sets.

* tel_levenberg_marquardt.dll 1.0.0
This plugin implements the Levenberg-Marquardt optimizer for fitting multi parameter data to models.

* tel_nelder_mead.dll Version 0.9.0
This plugin implements the Nelder-Mead optimizer for fitting multi parameter data to models.

See http://tellurium.analogmachine.org/plugins/  for more details.



