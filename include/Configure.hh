#ifndef CONFIGURE_HH
#define CONFIGURE_HH

#include <iostream>
using namespace std;

static const int Maximum_E = 1000;//MeV
static const int E_bin = 10;//MeV
static const int event_end_num = 100000;
    
static const int particle_num = 10;
static const string particle[particle_num] = {"e-", "e+", "mu-", "mu+", "proton", "anti_proton", "neutron", "anti_neutron", "alpha", "gamma"};

#endif // CONFIGURE_HH
