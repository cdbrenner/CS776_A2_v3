#pragma once
#include <fstream>
#include <iomanip>
#include "helpers.h"
#include "options.h"
#include "individual.h"
#include "evaluate.h"

class Population
{
    private:
        Options options;
        Individual* members = nullptr;
        double average, max, min, sum_fitness;
        double average_objective, max_objective, min_objective, sum_objective;

        //MEMBERS FOR TESTING PROBABILITY ACCURACY
        double proportional_fitnesses[4];
        double member_chosen_count[4];

    public:
        Population();
        Population(Options);
        Population(Options, int);
        ~Population();

        void set_options(Options);
        void set_members();
        void set_members(int);

        Individual* get_members();

        //FUNCTIONS FOR TESTING PROBABILITY ACCURACY
        // void set_proportional_fitnesses();
        // void set_member_chosen_count();
        void get_member_chosen_stats();

        void evaluate(int choice, int random_seed, int srand_offset);
        void evaluate_o(int choice, int random_seed, int srand_offset);
        void stats();
        void stats_o();
        void report(int);
        void report_o(int);
        void generation(Population* child, int srand_offset);
        void CHC_generation(Population* child, Population* temp);
        int proportional_selection(int srand_offset);
        void xover_mutate(Individual*,Individual*,Individual*,Individual*, int);
        void one_point_xover(Individual*,Individual*,Individual*,Individual*, int);

        //TEST
        void print_pop();
};