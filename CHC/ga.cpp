#include "ga.h"

GA::GA(int argc, char *argv[], int eval_option, int it)
{
    setup_options(argc, argv, eval_option, it);
}

void GA::setup_options(int argc, char *argv[], int eval_option, int it)
{
    std::stringstream ss1;
    std::stringstream ss2;
    std::string temp1;
    std::string temp2;
    int previous = it - 1;
    ss1 << it;
    ss1 >> temp1;
    ss2 << previous;
    ss2 >> temp2;

    options.GA_iteration = it;
    options.random_seed = time(NULL) + it;

    switch(eval_option)
    {
        case 1:
            options.chromosome_length = 27;
            options.population_size = 50;
            options.max_generations = 100;
            options.probability_mutation = 0.001;
            options.probability_x = 0.9;
            options.input_file = "output_deJong_F1_" + temp2 + ".txt";
            options.input_file_o = "output_deJong_F1_O_" + temp2 + ".txt";
            options.output_file = "output_deJong_F1_" + temp1 + ".txt";
            options.output_file_o = "output_deJong_F1_O_" + temp1 + ".txt";
            options.ave_file = "output_deJong_F1_AVE.txt";
            options.ave_file_o = "output_deJong_F1_O_AVE.txt";
            options.print_precision = 2;
            options.print_precision_o = 5;
            break;
        case 2:
            options.chromosome_length = 22;
            options.population_size = 50;
            options.max_generations = 100;
            options.probability_mutation = 0.05;
            options.probability_x = 0.99;
            options.input_file = "output_deJong_F2_" + temp2 + ".txt";
            options.input_file_o = "output_deJong_F2_O_" + temp2 + ".txt";
            options.output_file = "output_deJong_F2_" + temp1 + ".txt";
            options.output_file_o = "output_deJong_F2_O_" + temp1 + ".txt";
            options.ave_file = "output_deJong_F2_AVE.txt";
            options.ave_file_o = "output_deJong_F2_O_AVE.txt";
            options.print_precision = 2;
            options.print_precision_o = 5;
            break;
        case 3:
            options.chromosome_length = 45;
            options.population_size = 500;
            options.max_generations = 1000;
            options.probability_mutation = 0.05;
            options.probability_x = .9;
            options.input_file = "output_deJong_F3_" + temp2 + ".txt";
            options.input_file_o = "output_deJong_F3_O_" + temp2 + ".txt";
            options.output_file = "output_deJong_F3_" + temp1 + ".txt";
            options.output_file_o = "output_deJong_F3_O_" + temp1 + ".txt";
            options.ave_file = "output_deJong_F3_AVE.txt";
            options.ave_file_o = "output_deJong_F3_O_AVE.txt";
            options.print_precision = 2;
            options.print_precision_o = 2;
            break;
        case 4:
            options.chromosome_length = 210;
            options.population_size = 500;
            options.max_generations = 1000;
            options.probability_mutation = 0.05;
            options.probability_x = 0.99;
            options.input_file = "output_deJong_F4_" + temp2 + ".txt";
            options.input_file_o = "output_deJong_F4_O_" + temp2 + ".txt";
            options.output_file = "output_deJong_F4_" + temp1 + ".txt";
            options.output_file_o = "output_deJong_F4_O_" + temp1 + ".txt";
            options.ave_file = "output_deJong_F4_AVE.txt";
            options.ave_file_o = "output_deJong_F4_O_AVE.txt";
            options.print_precision = 5;
            options.print_precision_o = 2;
            break;
        case 5:
            options.chromosome_length = 32;
            options.population_size = 50;
            options.max_generations = 100;
            options.probability_mutation = 0.05;
            options.probability_x = 0.99;
            options.input_file = "output_deJong_F5" + temp2 + ".txt";
            options.input_file_o = "output_deJong_F5_O" + temp2 + ".txt";
            options.output_file = "output_deJong_F5" + temp1 + ".txt";
            options.output_file_o = "output_deJong_F5_O" + temp1 + ".txt";
            options.ave_file = "output_deJong_F5_AVE.txt";
            options.ave_file_o = "output_deJong_F5_O_AVE.txt";
            options.print_precision = 5;
            options.print_precision_o = 5;
            break;
    }
}

void GA::init(int eval_option)
{
    std::ofstream out(options.output_file);
    std::ofstream out_2(options.output_file_o);
    out << "GEN,\t\tMIN,\t\t\tAVE,\t\t\tMAX,\n";
    out_2 << "GEN,\t\tMIN,\t\t\tAVE,\t\t\tMAX,\n";
    out.close();
    out_2.close();

    parent = new Population(options);
    child = new Population(options);
    temp = new Population(options);


    parent->evaluate(eval_option, options.random_seed, 0);
    parent->evaluate_o(eval_option, options.random_seed, 0);
    parent->stats();
    parent->stats_o();
    parent->report(0);
    parent->report_o(0);
}

void GA::run(int eval_option)
{
    for(int i = 1; i < options.max_generations; i++)
    {
        parent->generation(child, i);
        child->evaluate(eval_option, options.random_seed, i*options.population_size);
        child->evaluate_o(eval_option, options.random_seed, i*options.population_size);

        parent->CHC_generation(child, temp);

        child->stats();
        child->stats_o();
        child->report(i);
        child->report_o(i);

        Population *temp = parent;
        parent = child;
        child = temp;
    }

    report_cleanup();
}

void GA::report_cleanup()
{
    if(options.GA_iteration != 0)
    {
        std::remove(options.input_file.c_str());
        std::remove(options.input_file_o.c_str());
    }
}