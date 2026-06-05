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
    const long double eps = 1.e-12;
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
    long double step = abs (b - a) / (points - 1);
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

void compute_interpolant_on_grid (
    const long double *x,
    const long double *y,
    const long double *grid,
    long double* L_out,
    size_t grid_size,
    long double a,
    long double step,
    size_t K,
    size_t N) {

    for (size_t i = 0; i < grid_size; ++i) {
        size_t interval = find_interval (grid[i], a, step, K);
        size_t start_idx = (interval - 1) * (N - 1);
        size_t end_idx   = interval * (N - 1);
        L_out[i] = get_polynoms_value_in_the_point (x, y, grid[i], start_idx, end_idx);
    }
}

void compute_error_norms (
    const long double *f_vals,
    const long double *L_vals,
    size_t n,
    long double abs_err[3],
    long double rel_err[3]) {

    long double sum_abs = 0.0, sum_sq = 0.0, max_abs = 0.0;
    long double sum_f_abs = 0.0, sum_f_sq = 0.0, max_f = 0.0;

    for (size_t i = 0; i < n; ++i) {
        long double diff = abs (f_vals[i] - L_vals[i]);
        long double f_abs = abs (f_vals[i]);

        sum_abs += diff;
        sum_sq += diff * diff;
        if (diff > max_abs) max_abs = diff;

        sum_f_abs += f_abs;
        sum_f_sq += f_abs * f_abs;
        if (f_abs > max_f) max_f = f_abs;
    }

    abs_err[0] = sum_abs;
    abs_err[1] = sqrt (sum_sq);
    abs_err[2] = max_abs;

    rel_err[0] = sum_abs / sum_f_abs;
    rel_err[1] = abs_err[1] / sqrt (sum_f_sq);
    rel_err[2] = max_abs / max_f;
}

void export_plot_data (
    const char *filename,
    size_t M,
    const long double *x,
    const long double *y,
    size_t M_viz,
    const long double *grid,
    const long double *f_grid,
    const long double *L_grid)
{
    ofstream file (filename);
    if (!file.is_open()) {
        cerr << "Error: can't open file" << filename << endl;
        return;
    }
    file << M << '\n' << M_viz << '\n';
    for (size_t i = 0; i < M; ++i) file << x[i] << ' ';
    file << '\n';
    for (size_t i = 0; i < M; ++i) file << y[i] << ' ';
    file << '\n';
    for (size_t i = 0; i < M_viz; ++i) file << grid[i] << ' ';
    file << '\n';
    for (size_t i = 0; i < M_viz; ++i) file << f_grid[i] << ' ';
    file << '\n';
    for (size_t i = 0; i < M_viz; ++i) file << L_grid[i] << ' ';
    file << std::endl;
    file.close();
}