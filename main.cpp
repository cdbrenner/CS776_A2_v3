#include "ga.h"
#include "test.h"

int main(int argc, char* argv[])
{
    for(int i = 5; i <= 5; i++)
    {
        GA ga(argc, argv, i);

        ga.init(i);
        ga.run(i);
    }

}