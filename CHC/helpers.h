#pragma once
#include <iostream>
#include <unistd.h>

int flip(float probability, int random_seed, int offset);
int random_index_in_range(int low, int high, int random_seed, int offset);