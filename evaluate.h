#pragma once
#include <cmath>
#include <random>
#include "individual.h"

void deleter(double*);
double eval(Individual&, int, int random_seed, int srand_offset);
double eval_o(Individual&, int, int random_seed, int srand_offset);
double* decode(Individual&, int, double);

//RETURN FITNESS OF FITNESS FUNCTION
double deJong_F1(Individual&);
double deJong_F2(Individual&);
double deJong_F3(Individual&);
double deJong_F4(Individual&, int random_seed, int srand_offset);
double deJong_F5(Individual&);

//RETURN OBJECTIVE_VALUE OF OBJECTIVE FUNCTION
double deJong_F1_o(Individual&);
double deJong_F2_o(Individual&);
double deJong_F3_o(Individual&);
double deJong_F4_o(Individual&, int random_seed, int srand_offset);
double deJong_F5_o(Individual&);