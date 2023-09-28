//TESTS IN MUTATE - & TEST FUNCTIONS EXIST

#include "individual.h"

Individual::Individual()
{
    chromosome_length = -1;
    fitness = -1;
}

Individual::Individual(int length)
{
    chromosome_length = length;
    fitness = -1;
}

Individual::~Individual()
{
    if(chromosome != nullptr)
        delete[] chromosome;
}

void Individual::set_chromosome_length(int length)
{
    chromosome_length = length;
}

void Individual::set_fitness(double fitness)
{
    this->fitness = fitness;
}

void Individual::set_objective_value(double objective_value)
{
    this->objective_value = objective_value;
}

int Individual::get_chromosome_length()
{
    return chromosome_length;
}

int* Individual::get_chromosome()
{
    return chromosome;
}

double Individual::get_fitness()
{
    return fitness;
}

double Individual::get_objective_value()
{
    return objective_value;
}

double Individual::get_mutation_percentage()
{
    return mutation_count/total_mutation_attempts;
}

void Individual::init(int random_seed, int srand_offset)
{
    chromosome = new int[chromosome_length];
    for(int i = 0; i < chromosome_length; i++)
    {
        chromosome[i] = flip(0.5f, random_seed, srand_offset*chromosome_length + i);
    }
}

void Individual::mutate(double probability, int random_seed, int srand_offset)
{
    //REAL
    for(int i = 0; i < chromosome_length; i++)
    {
        flip(probability, random_seed, srand_offset*chromosome_length + i) ? chromosome[i] = 1 - chromosome[i] : 0;
    }
    //TEST
    // char temp;
    // for(int i = 0; i < chromosome_length; i++)
    // {
    //     if(flip(probability, srand_offset*chromosome_length + i))
    //     {
    //         std::cout << "MUTATE!!!" << std::endl;
    //         std::cout << "MUTATE INDEX = " << i << std::endl;
    //         // std::cin >> temp;
    //         chromosome[i] = 1 - chromosome[i];
    //         // mutation_count++;
    //     }
    //     // total_mutation_attempts++;
    // }
}

//TEST
void Individual::print_ind()
{
    int one = 0;
    int zero = 0;
    for(int i = 0; i < chromosome_length; i++)
    {
        if(i != chromosome_length - 1)
        {
            std::cout << chromosome[i];
            chromosome[i] == 1 ? one++ : zero++;
        }
        else
        {
            chromosome[i] == 1 ? one++ : zero++;
            std::cout << chromosome[i] << std::endl;
        }
    }
    // std::cout << "1s: " << (float)one/chromosome_length << std::endl;
    // std::cout << "0s: " << (float)zero/chromosome_length << std::endl;
}