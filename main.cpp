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

    for(int i = 1; i <= 1; i++)
    {
        GA ga(argc, argv, i, count - 1);

        report_averager(count, ga.options.output_file, ga.options.ave_file, ga.options.print_precision, ga.options.max_generations);
        report_averager(count, ga.options.output_file_o, ga.options.ave_file_o, ga.options.print_precision_o, ga.options.max_generations);
    }

}