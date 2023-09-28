#pragma once
#include <iostream>

struct Options
{
    std::string input_file;
    std::string output_file;
    std::string output_file_o;
    int print_precision;
    int print_precision_o;
    int evaluation_mode;
    long int random_seed;
    int population_size;
    int chromosome_length;
    int max_generations;
    double probability_x;
    double probability_mutation;
};