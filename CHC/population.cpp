#include "population.h"

Population::Population()
{
    average = min = max = sum_fitness = -1;
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
    }
}

Population::~Population()
{
    if(members != nullptr)
    {
        delete[] members;
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
        fitness = eval(members[i], choice, random_seed, srand_offset + i);
        members[i].set_fitness(fitness);
    }
}

//choice chooses which objective function to evaluate
void Population::evaluate_o(int choice, int random_seed, int srand_offset)
{
    double objective_value = -1;
    for(int i = 0; i < options.population_size; i++)
    {
        objective_value = eval_o(members[i], choice, random_seed, srand_offset + i);
        members[i].set_objective_value(objective_value);
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

        sum_fitness += fitness;
        fitness < min ? min = fitness : 0;
        fitness > max ? max = fitness : 0;
    }
    average = sum_fitness/options.population_size;
}

void Population::stats_o()
{
    sum_objective = 0;
    min_objective = max_objective = members[0].get_objective_value();
    double objective_value = -1;
    for(int i = 0; i < options.population_size; i++)
    {
        objective_value = members[i].get_objective_value();

        sum_objective += objective_value;
        objective_value < min_objective ? min_objective = objective_value : 0;
        objective_value > max_objective ? max_objective = objective_value : 0;
    }
    average_objective = sum_objective/options.population_size;
}

void Population::report(int generation)
{
    if(options.GA_iteration == 0)
    {
        std::ofstream out(options.output_file, std::ios::app);
        out << std::fixed << std::setprecision(options.print_precision) << generation << ",\t\t" << min << ",\t\t" << average << ",\t\t" << max << "," << std::endl;
        out.close();
    }
    else
    {
        std::string temp;
        std::string min_prev_str;
        std::string ave_prev_str;
        std::string max_prev_str;
        std::ifstream in(options.input_file);
        for(int i = 0; i < generation + 1; i++)
        {
            getline(in,temp);
        }
        getline(in,temp,',');
        getline(in,min_prev_str,',');
        getline(in,ave_prev_str,',');
        getline(in,max_prev_str,',');
        double min_prev = atof(min_prev_str.c_str());
        double ave_prev = atof(ave_prev_str.c_str());
        double max_prev = atof(max_prev_str.c_str());

        std::ofstream out(options.output_file, std::ios::app);
        out << std::fixed << std::setprecision(options.print_precision) << generation << ",\t\t" << min + min_prev << ",\t\t" << average + ave_prev << ",\t\t" << max + max_prev << "," << std::endl;
        out.close();
    }
}

void Population::report_o(int generation)
{
    if(options.GA_iteration == 0)
    {
        std::ofstream out(options.output_file_o, std::ios::app);
        out << std::fixed << std::setprecision(options.print_precision_o) << generation << ",\t\t" << min_objective << ",\t\t" << average_objective << ",\t\t" << max_objective << "," << std::endl;
        out.close();
    }
    else
    {
        std::string temp;
        std::string min_prev_str;
        std::string ave_prev_str;
        std::string max_prev_str;
        std::ifstream in(options.input_file_o);
        for(int i = 0; i < generation + 1; i++)
        {
            getline(in,temp);
        }
        getline(in,temp,',');
        getline(in,min_prev_str,',');
        getline(in,ave_prev_str,',');
        getline(in,max_prev_str,',');
        double min_prev = atof(min_prev_str.c_str());
        double ave_prev = atof(ave_prev_str.c_str());
        double max_prev = atof(max_prev_str.c_str());

        std::ofstream out(options.output_file_o, std::ios::app);
        out << std::fixed << std::setprecision(options.print_precision_o) << generation << ",\t\t" << min_objective + min_prev << ",\t\t" << average_objective + ave_prev << ",\t\t" << max_objective + max_prev << "," << std::endl;
        out.close();
    }
}

void Population::generation(Population* child, int srand_offset)
{
    int parent_index_1, parent_index_2, child_index_1, child_index_2;
    Individual *parent_1, *parent_2, *child_1, *child_2;
    for(int i = 0; i < options.population_size; i += 2)
    {   
        parent_index_1 = proportional_selection(srand_offset*options.population_size + i);
        parent_index_2 = proportional_selection(srand_offset*options.population_size + i + 1);

        child_index_1 = i;
        child_index_2 = i+1;

        parent_1 = &members[parent_index_1];
        parent_2 = &members[parent_index_2];
        child_1 = &(child->members[child_index_1]);
        child_2 = &(child->members[child_index_2]);

        xover_mutate(parent_1, parent_2, child_1, child_2, srand_offset*options.population_size + i);
    }

}

void Population::CHC_generation(Population* child, Population* temp)
{
    int index = -1;
    for(int j = 0; j < options.population_size; j++)
    {
        double fitness = 0;
        for(int i = 0; i < options.population_size*2; i++)
        {
            if(i < options.population_size)
            {
                if(members[i].get_fitness() >= fitness)
                {
                    fitness = members[i].get_fitness();
                    index = i;
                }
            }
            else
            {
                if(child->get_members()[i - options.population_size].get_fitness() >= fitness)
                {
                    fitness = child->get_members()[i - options.population_size].get_fitness();
                    index = i;
                }
            }
        }

        if(index < options.population_size)
        {
            temp->members[j] = members[index];
            members[index].set_fitness(-1);
        }
        else
        {
            temp->members[j] = child->get_members()[index - options.population_size];
            child->get_members()[index - options.population_size].set_fitness(-1);
        }
    }

    for(int i = 0; i < options.population_size; i++)
    {
        child->get_members()[i] = temp->members[i];
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

    if(flip(options.probability_x, options.random_seed, srand_offset))
        one_point_xover(parent_1, parent_2, child_1, child_2, srand_offset);

    child_1->mutate(options.probability_mutation, options.random_seed, srand_offset);
    child_2->mutate(options.probability_mutation, options.random_seed, srand_offset);
    
}

void Population::one_point_xover(Individual* parent_1, Individual* parent_2, Individual* child_1, Individual* child_2, int srand_offset)
{
    int index = random_index_in_range(0, options.chromosome_length, options.random_seed, srand_offset);

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