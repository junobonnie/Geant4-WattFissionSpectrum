#!/bin/bash

echo "                                                                                                          "
echo "          G E A N T 4   C R Y - A U T O - R U N                                   "
echo "          Version 1.0    last modified 2022-06-16                 "
echo "                                                                                                          "
echo "          Copyright (C) 2022~                                                             "
echo "          Developed by Replica                                                    "
echo "                                                                                                          "
echo "          My Github Page:     http://github.com/junobonnie"
echo "                                                                                                          "
energy_bin=10
energy=1000
printf "\033[31m<< 1. Set Parameters >>\033[0m\n\n"
CRY_TEST_DIR=/opt/cry/1.7/cry_v1.7/test
if [ ${1:-'mode1'} == 'mode2' ]; then
        printf '\033[32m[mode2]\033[0m\n\n'
        name=$2
        echo "Set particle name : $name"
        echo ""
        altitude=$3
        echo "Set altitude(m) : $altitude"
        echo ""
        latitude=$4
        echo "Set latitude(deg) : $latitude"
        echo ""
        set_date=$5
        echo "Set date(month-day-year) : $set_date"
        echo ""
        end_event_num=$6
        echo "Set total number of events : $end_event_num"
        echo ""
else
        printf '\033[32m[mode1]\033[0m\n\n'
        echo "Select particle name : "
        PS3=">>> "
        select name in "Neutron" "Proton" "Gamma" "Electron" "Muon" "Pion" "Kaon"
        do
          echo "The one you have selected is: $name"
          break
        done
        echo ""

        echo "Select altitude(m) : "
        PS3=">>> "
        select altitude in "0" "2100" "11300"
        do
          echo "The one you have selected is: $altitude m"
          break
        done
        echo ""

        echo "Set latitude(deg) : "
        printf ">>> "
        read latitude
        echo ""

        echo "Set date(month-day-year) : "
        printf ">>> "
        read set_date
        echo ""

        echo "Set total number of events : "
        printf ">>> "
        read end_event_num
        echo ""
fi

echo "returnNeutrons 0
returnProtons 0
returnGammas 0
returnElectrons 0
returnMuons 0
returnPions 0
returnKaons 0
date $set_date
latitude $latitude
altitude $altitude
subboxLength 5
" > temp

awk '/'"$name"'/{$2="1"}1' temp > setup.file
rm temp

echo "Make setup.file"
ln -s $CRY_TEST_DIR/data .
$CRY_TEST_DIR/testOut setup.file $end_event_num
#mv $CRY_TEST_DIR/shower.out .

echo "Make $CRY_TEST_DIR/shower.out"

python3 cry2mac.py > run_cry.mac

echo "Make run_cry.mac"

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

output_dir=$output_root_dir"/"$name"_"$altitude"m_"$latitude"deg_"$set_date"_"$end_event_num"event_"$(date +%Y-%m-%d-%T)
mkdir -p $output_dir

filename=$output_dir"/raw_result.out"

echo "Simulation running..."
./g4_minimal run_cry.mac > $filename
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
