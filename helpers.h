#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <unistd.h>

int flip(float probability, int random_seed, int offset);
int random_index_in_range(int low, int high, int random_seed, int offset);
void report_averager(int iterations, std::string filename, std::string output_name, int precision, int population_size);