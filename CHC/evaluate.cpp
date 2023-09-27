#include "evaluate.h"

void deleter(double* variables)
{
    if(variables != nullptr)
        delete[] variables;
}

double eval(Individual& individual, int choice, int random_seed, int srand_offset)
{
    double fitness;

    switch(choice)
    {
        case 1:
            fitness = deJong_F1(individual);
            break;
        case 2:
            fitness = deJong_F2(individual);
            break;
        case 3:
            fitness = deJong_F3(individual);
            break;
        case 4:
            fitness = deJong_F4(individual, random_seed, srand_offset);
            break;
        case 5:
            fitness = deJong_F5(individual);
            break;
    }

    return fitness;
}

double* decode(Individual& individual, int bit_length, double scaler)
{
    int variable_count = individual.get_chromosome_length()/bit_length;

    double* variables = new double[variable_count];

    for(int j = 0; j < variable_count; j++)
    {
        double variable_sum = 0;
        double variable_sign = 0;
        for(int i = 0; i < bit_length; i++)
        {
            if(i == 0)
            {
                individual.get_chromosome()[(j*bit_length) + i] == 1 ? variable_sign = 1 : variable_sign = -1;
            }
            else
            {
                individual.get_chromosome()[(j*bit_length) + i] == 1 ? variable_sum += pow(2,bit_length - (i+1)) : 0;
            }
        }
        variable_sum /= scaler;
        variable_sum *= variable_sign;
        variables[j] = variable_sum;
    }
    
    return variables;
}

//MAXIMUM FITNESS SHOULD BE ~78.64
double deJong_F1(Individual& individual)
{
    double fitness;
    double *variables = decode(individual, 9, 99.8046875);

    double objective_function = pow(variables[0],2) + pow(variables[1],2) + pow(variables[2],2);

    fitness = (double)78.6432 - objective_function;

    deleter(variables);

    return fitness;
}

//MAXIMUM FITNESS SHOULD BE 3905.93
double deJong_F2(Individual& individual)
{
    double fitness;
    double *variables = decode(individual, 11, 999.51171875);

    double objective_function = 100*pow(pow(variables[0],2)-variables[1], 2) + pow(1 - variables[0], 2);

    fitness = (double)3905.9262268416 - objective_function;
    // fitness = (double)1/(objective_function + 1);

    deleter(variables);

    return fitness;
}

//MAXIMUM FITNESS SHOULD BE 55.6
double deJong_F3(Individual& individual)
{
    double fitness;
    double *variables = decode(individual, 9, 99.8046875);

    double objective_function = floor(variables[0]) + floor(variables[1]) + floor(variables[2]) + floor(variables[3]) + floor(variables[4]);

    fitness = (double)25.6 - objective_function;

    deleter(variables);

    return fitness;
}

double deJong_F4(Individual& individual, int random_seed, int srand_offset)
{
    srand(random_seed + srand_offset);
    double fitness;
    double *variables = decode(individual, 7, 99.21875);

    double objective_function_pt1 = 0;
    for(int i = 0; i < 30; i++)
    {
        objective_function_pt1 += (i+1)*pow(variables[i],4);
    }

    double objective_function_pt2 = 0;
    for(int i = 0; i < 12; i++)
    {
        objective_function_pt2 += (double)rand()/RAND_MAX*12.47;
    }

    double objective_function = objective_function_pt1 + objective_function_pt2;

    fitness = (double)1/(objective_function + 1);

    deleter(variables);

    return fitness;
}

double deJong_F5(Individual& individual)
{
    int a[2][25] = {{-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32},
                        {-32,-32,-32,-32,-32,-16,-16,-16,-16,-16,0,0,0,0,0,16,16,16,16,16,32,32,32,32,32}};

    double fitness;
    double *variables = decode(individual, 16, 999.9847412109375);

    double objective_function_pt1[2][25];
    for(int j = 0; j < 25; j++)
    {
        for(int i = 0; i < 2; i++)
            objective_function_pt1[i][j] = pow(variables[i] - a[i][j],6);
    }

    double objective_function_pt2 = 0;
    for(int j = 1; j <= 25; j++)
        objective_function_pt2 += 1/(j + objective_function_pt1[0][j-1] + objective_function_pt1[1][j-1]);

    double objective_function = 0.002 + objective_function_pt2;

    fitness = (double)1/(objective_function + 1);

    deleter(variables);

    return fitness;

}