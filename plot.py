import os
import sys
import matplotlib.pyplot as plt

energy = int(sys.argv[1])
energy_bin = int(sys.argv[2])
particle = sys.argv[3]
exec('count_list = [' + sys.argv[4] + ']')
mode = sys.argv[5]
output_dir = sys.argv[6]

energy_list = list(range(0, energy, energy_bin))
total_count = sum(count_list)

plt.figure(figsize = (10,5), dpi = 720)
plt.text(0, max(count_list), 'Total Number of ' + particle + ': ' + str(total_count))
plt.bar(energy_list, count_list, width = energy_bin)
plt.title(particle + ' energy spectrum')
plt.xlabel('Energy(MeV)')
plt.ylabel('Count')
plt.yscale(mode)

figure_name = particle + '_energy_spectrum_' + mode + '.png'
plt.savefig(output_dir + '/' + figure_name)

os.system('viu -w=70 ' + output_dir + '/' + figure_name + '>> ' +  output_dir + '/raw_result.out')
os.system('echo "\033[33m[ File : ' + figure_name + ' ] [ Total : ' + str(total_count) + ' ]\033[0m\n" >> ' +  output_dir + '/raw_result.out')
os.system('echo " " >> ' +  output_dir + '/raw_result.out')
