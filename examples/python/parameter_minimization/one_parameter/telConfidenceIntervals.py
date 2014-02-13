# Show that add noise plugin correctly computes Sigma (standard deviation)
import matplotlib.pyplot as plt
import scipy.stats as stats
import telplugins as tel
import numpy as np

conf = 75e-3
mean = 0 #0.573

leftSide = mean - conf
rightSide = mean + conf

mu, sigma = mean, 0.648 # mean and standard deviation
s = np.random.normal(mu , sigma, 1000)

count, bins, ignored = plt.hist(s, 30, normed=True)

plt.plot(bins, 1/(sigma * np.sqrt(2 * np.pi)) * np.exp( - (bins - mu)**2 / (2 * sigma**2) ), linewidth=2, color='r')
plt.show()



