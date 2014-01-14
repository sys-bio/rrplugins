import rrplugins as rrp

p = rrp.Plugin ("rrp_add_noise")

p.Sigma = 0.00005

data = p.loadDataSeries ("testData.dat")
p.plotDataSeries (data)

p.InputData = data

p.execute()

p.plotDataSeries (p.InputData)