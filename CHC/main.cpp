#include "ga.h"
#include "test.h"

int main(int argc, char* argv[])
{

    int count = 0;
    for(int j = 0; j < 30; j++)
    {
        for(int i = 1; i <= 1; i++)
        {
            GA ga(argc, argv, i, j);

            ga.init(i);
            ga.run(i);
        }
        count++;
    }

    std::cout << count << std::endl;

    for(int i = 1; i <= 1; i++)
    {
        GA ga(argc, argv, i, count - 1);

        report_averager(count, ga.options.output_file, ga.options.ave_file, ga.options.print_precision, ga.options.population_size);
        report_averager(count, ga.options.output_file_o, ga.options.ave_file_o, ga.options.print_precision_o, ga.options.population_size);
    }

}