#include "test.h"

void test_nine_variables_in_random_choice(int runs, int bit_length)
{
    int neg = 0;
    int zero = 0;
    int one = 0;
    int two = 0;
    int three = 0;
    int four = 0;
    int five = 0;
    int six = 0;
    int seven = 0;
    int eight = 0;
    int nine = 0;

    for(int i = 0; i < runs; i++)
    {
        switch(random_index_in_range(0, 10, 1991, i))
        {
            case -1:
                neg++;
                break;
            case 0:
                zero++;
                break;
            case 1:
                one++;
                break;
            case 2:
                two++;
                break;
            case 3:
                three++;
                break;
            case 4:
                four++;
                break;
            case 5:
                five++;
                break;
            case 6:
                six++;
                break;
            case 7:
                seven++;
                break;
            case 8:
                eight++;
                break;
            case 9:
                nine++;
                break;
        }
    }

    std::cout << "neg = " << (double)neg/runs << std::endl;
    std::cout << "zero = " << (double)zero/runs << std::endl;
    std::cout << "one = " << (double)one/runs << std::endl;
    std::cout << "two = " << (double)two/runs << std::endl;
    std::cout << "three = " << (double)three/runs << std::endl;
    std::cout << "four = " << (double)four/runs << std::endl;
    std::cout << "five = " << (double)five/runs << std::endl;
    std::cout << "six = " << (double)six/runs << std::endl;
    std::cout << "seven = " << (double)seven/runs << std::endl;
    std::cout << "eight = " << (double)eight/runs << std::endl;
    std::cout << "nine = " << (double)nine/runs << std::endl;
}