# Show that add noise plugin correctly computes Sigma (standard deviation)

import telplugins as tel
import numpy
import math

p = tel.Plugin ("tel_add_noise")

n = 80000
timeSeries = numpy.zeros (shape=(n,2))
for i in range (n):
    timeSeries[i] = [i, 1]

data = tel.DataSeries.fromNumPy (timeSeries)

p.InputData = data
p.Sigma = 0.25

p.execute()

values = p.InputData.toNumpy

print "mean=", numpy.mean (values[:,1])
print "std=", numpy.std (values[:,1])



