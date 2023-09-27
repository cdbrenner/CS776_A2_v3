#pragma once
#include "population.h"

class GA
{
    private:
    public:
        Population *parent;
        Population *child;
        Population *temp;
        Options options;

        GA(int argc, char *argv[], int eval_option);

        void setup_options(int argc, char *argv[], int eval_option);

        void init(int eval_option);
        void run(int eval_option);
};