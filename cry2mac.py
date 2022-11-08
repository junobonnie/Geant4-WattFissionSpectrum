from particle import Particle

def combine_space(text):
    text = text.strip()
    while '  ' in text:
        text = text.replace('  ', ' ')
    return text

results = '''# Can be run in batch, without graphic
# or interactively: Idle> /control/execute run_cry.mac

# Verbose
/control/verbose 0
/run/verbose 0
/event/verbose 0
/tracking/verbose 0'''
#particles = ['neutron', 'proton', 'pion', 'kaon', '-mu', '-e', 'gamma']
#particles = ['neutron', 'proton', 'neutron', 'neutron', 'mu-', 'e-', 'gamma']
with open('shower.out', 'r') as f:
    lines = f.readlines()
    for line in lines[1:]:
        line = combine_space(line)
        #print(line.split(' '))
        particle_id, k_E, x, y, z, vx, vy, vz = line.split(' ')[2:]
        particle_name = Particle.from_pdgid(particle_id).name
        if particle_name == 'n':
            particle_name = 'neutron'
        results += '''
/gun/particle %s
/gun/energy %s MeV
/gun/position %s %s -0.5 m
/gun/direction %s %s %f
/run/beamOn 1
''' %(particle_name, k_E, x, y, vx, vy, -float(vz))

print(results)
#print(len(lines))
