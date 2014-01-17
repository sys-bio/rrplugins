import telplugins as tel

p = tel.Plugin ("tel_add_noise")

data = p.loadDataSeries ("testData.dat")

p.plotDataSeries (data)

p.InputData = data
p.Sigma = 0.00005

p.execute()

p.plotDataSeries (p.InputData)