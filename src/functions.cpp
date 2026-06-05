#include "functions.h"

// константный метод. Принято: если передача по указателю, то будет меняться
// надо передавать по константной ссылке
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
