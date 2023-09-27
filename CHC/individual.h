#pragma once
#include "helpers.h"

class Individual
{
    private:
        int chromosome_length;
        int* chromosome = nullptr;
        double fitness;
        
        //VARIABLES FOR TESTING PROBABILITY ACCURACY
        double mutation_count = 0;
        double total_mutation_attempts = 0;

    public:
        Individual();
        Individual(int);
        ~Individual();

        void set_chromosome_length(int);
        void set_fitness(double);

        int get_chromosome_length();
        int* get_chromosome();
        double get_fitness();
        
        //FUNCTIONS FOR TESTING PROBABILITY ACCURACY
        double get_mutation_percentage();

        void init(int random_seed, int srand_offset);
        void mutate(double probability, int random_seed, int srand_offset);

        //TEST
        void print_ind();
};