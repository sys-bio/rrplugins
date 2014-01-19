
# Example of creating a new dataseries, adding noise and plotting

import telplugins as tel
import numpy
import math

p = tel.Plugin ("tel_add_noise")

n = 100
timeSeries = numpy.zeros (shape=(n,2))
for i in range (n):
    timeSeries[i] = [i, math.sin (i/4.0)]

data = tel.DataSeries.fromNumPy (timeSeries)

data.plot ()

p.InputData = data
p.Sigma = 0.25

p.execute()

p.InputData.plot()