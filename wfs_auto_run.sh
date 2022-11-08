#!/bin/bash

echo "														"
echo "		G E A N T 4   W F S - A U T O - R U N					"
echo "		Version 1.0    last modified 2022-11-08			"
echo "														"
echo "		Copyright (C) 2022~								"
echo "		Developed by Replica							"
echo "														"
echo "		My Github Page:     http://github.com/junobonnie"
echo "														"

printf "\033[31m<< 1. Set Parameters >>\033[0m\n\n"

if [ ${1:-'mode1'} == 'mode2' ]; then
	printf '\033[32m[mode2]\033[0m\n\n'
	name=$2
	echo "Set radionuclide name : $name"
	echo ""
	energy=$3
	echo "Set maximum neutron energy(keV) : $energy"
	echo ""
	energy_bin=$4
	echo "Set energy bin(keV) : $energy_bin"
	echo ""
	end_event_num=$5
	echo "Set total number of events : $end_event_num"
	echo ""
else
	printf '\033[32m[mode1]\033[0m\n\n'
	echo "Set radionuclide name : "
	printf ">>> "
	read name
	echo ""

	echo "Set maximum neutron energy(keV) : "
	printf ">>> "
	read energy
	echo ""

	echo "Set energy bin(keV) : "
	printf ">>> "
	read energy_bin
	echo ""

	echo "Set total number of events : "
	printf ">>> "
	read end_event_num
	echo ""
fi

python3 wfs_neutron_gen2mac.py > run_wfs.mac

echo "Make run_wfs.mac"

echo "#ifndef CONFIGURE_HH
#define CONFIGURE_HH

#include <iostream>
using namespace std;

static const int Maximum_E = $energy;//MeV
static const int E_bin = $energy_bin;//MeV
static const int event_end_num = $end_event_num;
    
static const int particle_num = 10;
"'static const string particle[particle_num] = {"e-", "e+", "mu-", "mu+", "proton", "anti_proton", "neutron", "anti_neutron", "alpha", "gamma"};'"

#endif // CONFIGURE_HH" > ../include/Configure.hh

echo "Make ../include/Configure.hh"

printf "\n\033[31m<< 2. Make from Source Code >>\033[0m\n\n"
echo "Making..."
make -j12

printf "\n\033[31m<< 3. Start Simulation >>\033[0m\n\n"
output_root_dir="results"
mkdir -p $output_root_dir
output_dir=$output_root_dir"/"$name"_"$energy"keV_"$energy_bin"keV_"$end_event_num"event_"$(date +%Y-%m-%d-%T)
mkdir -p $output_dir
filename=$output_dir"/raw_result.out"
echo "Simulation running..."
./g4_minimal run_wfs.mac > $filename
echo "Output file is $filename"

printf "\n\033[31m<< 4. Draw Plots >>\033[0m\n\n"
echo "Drawing..."
echo "" >> $filename
for mode in linear log
do
	for particle in e-: e+: mu-: mu+: proton: anti_proton: neutron: anti_neutron: alpha: gamma:
	do
		value=$(cat $filename | grep -w $particle)
		value=${value//$particle/}
		python3 plot.py $energy $energy_bin ${particle//:/} ${value// /} $mode $output_dir
	done
done

printf "\n\033[31m<< 5. Print Results >>\033[0m\n\n"
is_print="false"
PRE_IFS=$IFS
IFS=''
while read line || [ -n "$line" ]
do
	if [[ $line == e-:* ]]; then
		is_print="true"
	fi
	if [[ $is_print == "true" ]]; then
		echo $line
	fi
done < $filename
IFS=$PRE_IFS
printf "\033[32;5mD O N E "'!!!'"\033[0m\n\n"
