# WattFissionSpectrum.py

import matplotlib.pyplot as plt
import numpy as np

class WFS:
  def __init__(self, a, b, min_E, max_E, bins):
    # MeV
    self.E = np.linspace(min_E, max_E, bins)
    pdf = np.exp(-self.E/a)*np.sinh(np.sqrt(b*self.E))
    self.pdf = pdf/sum(pdf)

  def random(self):
    return np.random.choice(self.E, p=self.pdf)


if __name__ == "__main_":
  a = 1.18
  b = 1.03419
  min_E = 0
  max_E = 10
  bins = 1000
  wfs = WFS(a, b, min_E, max_E, bins)
  
  vals = []
  num = 100000
  for i in range(num):
    val = wfs.random()
    vals.append(val)
  
  
  plt.hist(vals,bins = bins)
  plt.plot(wfs.E, wfs.pdf*num)
  plt.xlim((0,10))
  plt.show()
