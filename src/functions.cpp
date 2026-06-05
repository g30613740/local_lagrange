#include "functions.h"


long double get_polynoms_value_in_the_point (
    const long double* a_x,
    const long double* a_y,
    const long double point_of_grid,
    const size_t initial_index,
    const size_t final_index) {

    long double sum = 0.; // value of polynom in given point
    for (size_t i = initial_index; i < final_index + 1; ++i) {
        long double numerator = 1.;
        long double denominator = 1.;
        for (size_t j = initial_index; j < final_index + 1; ++j) {
            if (i != j) {
                numerator *= point_of_grid - a_x[j];
                denominator *= a_x[i] - a_x[j];
            }
        }
        sum += a_y[i] * numerator / denominator; 
    }
    return sum;
}

long double get_value_of_the_math_function_in_the_point (long double point) {
    
    return sin (point);
}

size_t find_interval (long double x, long double a, long double step, size_t K) {
    // Защита от погрешности вычислений: если x очень близко к b
    const long double eps = 1e-12;
    long double right_bound = a + K * step;
    if (x >= right_bound - eps) {
        return K;
    }
    for (size_t j = 1; j < K; ++j) {
        if (x <= a + j * step + eps) {
            return j;
        }
    }
    return K;
}

long double* create_uniform_grid (long double a, long double b, size_t points) {

    if (points < 2) return nullptr;
    long double *grid = new long double [points];
    long double step = abs(b - a) / (points - 1);
    grid[0] = a;
    for (size_t i = 1; i < points; ++i) {
        grid[i] = grid[i-1] + step;
    }
    return grid;
}

void fill_function_values (const long double* x, long double* y, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        y[i] = get_value_of_the_math_function_in_the_point (x[i]);
    }
}