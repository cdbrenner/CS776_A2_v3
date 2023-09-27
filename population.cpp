#include "population.h"

Population::Population()
{
    average = min = max = sum_fitness = -1;

    //TEST
    for(int i = 0; i < options.population_size; i++)
    {
        proportional_fitnesses[i] = 0;
    }
    for(int i = 0; i < options.population_size; i++)
    {
        member_chosen_count[i] = 0;
    }
}

//FOR PROGRAMS REQUIRING ONLY A SINGLE INITIAL POPULATION
Population::Population(Options options)
{
    this->options = options;
    average = min = max = sum_fitness = -1;
    members = new Individual[this->options.population_size];
    for(int i = 0; i < this->options.population_size; i++)
    {
        members[i].set_chromosome_length(this->options.chromosome_length);
        members[i].init(options.random_seed, i);

        //TEST
        // members[i].print_ind();
    }
}

//FOR PROGRAMS REQUIRING MULTIPLE INITIAL POPULATIONS
Population::Population(Options options, int srand_offset)
{
    this->options = options;
    average = min = max = sum_fitness = -1;
    members = new Individual[this->options.population_size];
    for(int i = 0; i < this->options.population_size; i++)
    {
        members[i].set_chromosome_length(this->options.chromosome_length);
        members[i].init(options.random_seed, srand_offset*options.population_size + i);

        //TEST
        // members[i].print_ind();
    }
}

Population::~Population()
{
    if(members != nullptr)
    {
        delete[] members;

        //TEST
        // delete[] proportional_fitnesses;
        // delete[] member_chosen_count;
    }
}

void Population::set_options(Options options)
{
    this->options = options;
}

//FOR PROGRAMS REQUIRING ONLY A SINGLE INITIAL POPULATION
void Population::set_members()
{
    members = new Individual[this->options.population_size];
    for(int i = 0; i < this->options.population_size; i++)
    {
        members[i].set_chromosome_length(this->options.chromosome_length);
        members[i].init(options.random_seed, i);

        //TEST
        // members[i].print_ind();
    }
}

//FOR PROGRAMS REQUIRING MULTIPLE INITIAL POPULATIONS
void Population::set_members(int srand_offset)
{
    members = new Individual[this->options.population_size];
    for(int i = 0; i < this->options.population_size; i++)
    {
        members[i].set_chromosome_length(this->options.chromosome_length);
        members[i].init(options.random_seed, srand_offset*options.population_size + i);

        //TEST
        // members[i].print_ind();
    }
}

Individual* Population::get_members()
{
    return members;
}

void Population::get_member_chosen_stats()
{
    double total = 0;
    for(int i = 0; i < options.population_size; i++)
    {
        //TEST
        std::cout << "MEM_CHOSEN_COUNT[" << i << "] = " << member_chosen_count[i] <<std::endl;

        total += member_chosen_count[i];
    }

    std::cout << "total = " << total << std::endl;

    for(int i = 0; i < options.population_size; i++)
    {
        std::cout << "Member[" << i << "] fitness-frac = " << proportional_fitnesses[i] << std::endl;
        std::cout << "Member[" << i << "] occurence rate = " << member_chosen_count[i]/total << std::endl;
    }
}

//choice chooses which objective function to evaluate
void Population::evaluate(int choice, int random_seed, int srand_offset)
{
    double fitness = -1;
    for(int i = 0; i < options.population_size; i++)
    {
        //TEST
        // std::cout << "POPULATION CALL TO EVAL = " << i << std::endl;

        fitness = eval(members[i], choice, random_seed, srand_offset + i);

        //TEST
        // std::cout << "FITNESS FROM EVAL = " << fitness << std::endl;

        members[i].set_fitness(fitness);

        //TEST
        // std::cout << "AFTER SETTING FITNESS, MEM[" << i << "] = " << members[i].get_fitness() << std::endl;
    }
}

void Population::stats()
{
    sum_fitness = 0;
    min = max = members[0].get_fitness();
    double fitness = -1;
    for(int i = 0; i < options.population_size; i++)
    {
        fitness = members[i].get_fitness();

        //TEST
        // std::cout << "FITNESS OF MEM[" << i << "] = " << fitness << std::endl;

        sum_fitness += fitness;
        fitness < min ? min = fitness : 0;
        fitness > max ? max = fitness : 0;
    }
    average = sum_fitness/options.population_size;

        //TEST
        // std::cout << "SUM FITNESS = " << sum_fitness << std::endl;
}

void Population::report(int generation)
{
    std::ofstream out(options.output_file, std::ios::app);
    out << std::fixed << std::setprecision(options.print_precision) << generation << ",\t\t" << min << ",\t\t" << average << ",\t\t" << max << "," << std::endl;
    out.close();
}

void Population::generation(Population* child, int srand_offset)
{
    int parent_index_1, parent_index_2, child_index_1, child_index_2;
    Individual *parent_1, *parent_2, *child_1, *child_2;
    for(int i = 0; i < options.population_size; i += 2)
    {   
        parent_index_1 = proportional_selection(srand_offset*options.population_size + i);
        parent_index_2 = proportional_selection(srand_offset*options.population_size + i + 1);

        //TEST
        // std::cout << "Gen["<< srand_offset << "]: Parent[" << parent_index_1 << "] & Parent[" << parent_index_2 << "]" << std::endl;

        child_index_1 = i;
        child_index_2 = i+1;

        parent_1 = &members[parent_index_1];
        parent_2 = &members[parent_index_2];
        child_1 = &(child->members[child_index_1]);
        child_2 = &(child->members[child_index_2]);

        //TEST
        // std::cout << "GEN = " << srand_offset << std::endl;
        // std::cout << "INDIVIDUAL = " << i << std::endl;
        // std::cout << "OFFSET = " << srand_offset*options.population_size << std::endl;

        //REAL
        xover_mutate(parent_1, parent_2, child_1, child_2, srand_offset*options.population_size + i);

        //TEST
        // std::cout << "parent population AFTER generation:" << std::endl;
        // print_pop();
        // std::cout << "child population AFTER generation:" << std::endl;
        // child->print_pop();
    }
}

int Population::proportional_selection(int srand_offset)
{
    srand(options.random_seed + srand_offset);
    double random_fraction = (double)rand()/RAND_MAX;
    double limits[options.population_size];
    limits[0] = members[0].get_fitness()/sum_fitness;

    for(int i = 1; i < options.population_size; i++)
        limits[i] = limits[i-1] + members[i].get_fitness()/sum_fitness;

    for(int i = 0; i < options.population_size; i++)
    {
        if(random_fraction <= limits[i])
            return i;
    }

    return -1;
}

void Population::xover_mutate(Individual* parent_1, Individual* parent_2, Individual* child_1, Individual* child_2, int srand_offset)
{
    for(int i = 0; i < options.chromosome_length; i++)
    {
        child_1->get_chromosome()[i] = parent_1->get_chromosome()[i];
        child_2->get_chromosome()[i] = parent_2->get_chromosome()[i];
    }

    //REAL
    if(flip(options.probability_x, options.random_seed, srand_offset))
     one_point_xover(parent_1, parent_2, child_1, child_2, srand_offset);
    //TEST
    // if(flip(options.probability_x, options.random_seed, srand_offset))
    // {
    //     // std::cout << "XOVER!!!" << std::endl;
    //     one_point_xover(parent_1, parent_2, child_1, child_2, srand_offset);
    // }

    child_1->mutate(options.probability_mutation, options.random_seed, srand_offset);
    child_2->mutate(options.probability_mutation, options.random_seed, srand_offset);
    
}

void Population::one_point_xover(Individual* parent_1, Individual* parent_2, Individual* child_1, Individual* child_2, int srand_offset)
{
    int index = random_index_in_range(0, options.chromosome_length, options.random_seed, srand_offset);

    //TEST
    // std::cout << "XOVER INDEX = " << index << std::endl;

    for(int i = index + 1; i < options.chromosome_length; i++)
    {
            child_1->get_chromosome()[i] = parent_2->get_chromosome()[i];
            child_2->get_chromosome()[i] = parent_1->get_chromosome()[i];
    }
}

//TEST
void Population::print_pop()
{
    for(int i = 0; i < options.population_size; i++)
    {
        members[i].print_ind();
    }
}