#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

using namespace std;


long double get_polynoms_value_in_the_point (
    const long double* a_x,
    const long double* a_y,
    const long double point_of_grid,
    const size_t initial_index,
    const size_t final_index);

long double get_value_of_the_math_function_in_the_point (long double point);

size_t find_interval (long double x, long double a, long double step, size_t K);

#endif