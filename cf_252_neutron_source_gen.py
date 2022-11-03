# cf_252_neutron_source_gen.py
from WattFissionSpectrum import WFS
import matplotlib.pyplot as plt
from random import random
import math as m
import sys

def random_uniform_cone(max_theta):
  u = random()
  theta = max_theta * u
  v = random()
  phi = np.arccos(2*v-1)
  x   = np.sin(theta)*np.cos(phi)
  y   = np.sin(theta)*np.sin(phi)
  z   = np.cos (theta)
  return x, y, z

max_theta = int(sys.argv[1])
num = int(sys.argv[2])

a = 1.18
b = 1.03419
min_E = 0
max_E = 10
bins = 1000
cf252 = WFS(a, b, min_E, max_E, bins)

result = """
# Can be run in batch, without graphic
# or interactively: Idle> /control/execute run_cf252.mac
# Verbose
/control/verbose 0
/run/verbose 0
/event/verbose 0
/tracking/verbose 0"""

for i in range(num):
  vx, vy, vz = random_uniform_cone(max_theta)

  result += """
/gun/particle neutron
/gun/energy %s MeV
/gun/position 0 0 -1.0 m
/gun/direction %s %s %s
/run/beamOn 1
""" %(cf252.random(), vx, vy, vz)

  plt.scatter(vx, vy)
plt.show()

print(result)
