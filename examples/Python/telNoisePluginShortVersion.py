import telplugins as tel

p = tel.Plugin ("tel_add_noise")

p.Sigma = 0.00005

data = p.loadDataSeries ("testData.dat")
p.plotDataSeries (data)

p.InputData = data

p.execute()

p.plotDataSeries (p.InputData)