#include "helpers.h"

int flip(float probability, int random_seed, int offset)
{
    //TEST
    // std::cout << "offset = " << offset << std::endl;

    srand(random_seed + offset);
    // sleep(1);

    //TEST
    // int random = rand();
    // std::cout << "random = " << random << std::endl;

    return (rand() < probability*RAND_MAX ? 1 : 0);
}

int random_index_in_range(int low, int high, int random_seed, int offset)
{
    srand(random_seed + offset);
    return low + rand()%(high - low);
}