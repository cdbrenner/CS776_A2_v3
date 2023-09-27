#pragma once
#include <cmath>
#include "individual.h"

void deleter(double*);
double eval(Individual&, int, int random_seed, int srand_offset);
double* decode(Individual&, int, double);
double deJong_F1(Individual&);
double deJong_F2(Individual&);
double deJong_F3(Individual&);
double deJong_F4(Individual&, int random_seed, int srand_offset);
double deJong_F5(Individual&);