# cf_252_neutron_source_gen.py
from WattFissionSpectrum import WFS
from a, b, max_theta import wfs_config
from random import random
import math as m
import sys

def random_uniform_cone(max_theta):
  u = random()
  phi = 2*m.pi*u
  v = random()
  theta = np.arccos(1-(1-np.cos(max_theta))*v)
  x   = np.sin(theta)*np.cos(phi)
  y   = np.sin(theta)*np.sin(phi)
  z   = np.cos(theta)
  return x, y, z

min_E = 0
max_E = int(sys.argv[1])/1000
bins = int(int(sys.argv[1])/int(sys.argv[2]))
num = int(sys.argv[3])

wfs = WFS(a, b, min_E, max_E, bins)

result = """
# Can be run in batch, without graphic
# or interactively: Idle> /control/execute run_wfs.mac
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
""" %(wfs.random(), vx, vy, vz)

print(result)
