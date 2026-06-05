#include "functions.h"

int main () {

    // Parameters
    const long double a = -3.14, b = 3.14;
    const size_t num_intervals = 10;
    const size_t nodes_per_interval = 15;  // polynom degree = nodes_per_interval - 1

    const long double interval_len = (b - a) / num_intervals;
    const size_t total_nodes = num_intervals * nodes_per_interval - num_intervals + 1;

    // vizualisation
    const size_t viz_points = 100;

    // degree for errors (step = h / 100)
    const size_t error_grid_size = 100 * (total_nodes - 1) + 1;

    // create interpolation nodes
    long double* x = create_uniform_grid (a, b, total_nodes);
    long double* y = new long double [total_nodes];
    fill_function_values (x, y, total_nodes);

    // grid for vizualisation
    long double* viz_grid = create_uniform_grid(a, b, viz_points);
    long double* L_viz = new long double[viz_points];
    compute_interpolant_on_grid(x, y, viz_grid, L_viz, viz_points,
                                a, interval_len, num_intervals, nodes_per_interval);

    // grid for errors vizualisation
    long double* error_grid_points = create_uniform_grid(a, b, error_grid_size);
    long double* f_error = new long double[error_grid_size];
    fill_function_values(error_grid_points, f_error, error_grid_size);

    long double* L_error = new long double[error_grid_size];
    compute_interpolant_on_grid(x, y, error_grid_points, L_error, error_grid_size,
                                a, interval_len, num_intervals, nodes_per_interval);

    // evaluating errors
    long double abs_err[3], rel_err[3];
    compute_error_norms(f_error, L_error, error_grid_size, abs_err, rel_err);

    std::cout << "Absolute error  (1)  = " << abs_err[0] << "\n"
              << "Absolute error  (2)  = " << abs_err[1] << "\n"
              << "Absolute error (inf) = " << abs_err[2] << "\n"
              << "Relative error  (1)  = " << rel_err[0] << "\n"
              << "Relative error  (2)  = " << rel_err[1] << "\n"
              << "Relative error (inf) = " << rel_err[2] << std::endl;

    // data for plot creating
    long double* f_viz = new long double[viz_points];
    fill_function_values(viz_grid, f_viz, viz_points);

    export_plot_data("parameters.txt",
                     total_nodes, x, y,
                     viz_points, viz_grid, f_viz, L_viz);

    // calling Python script
    system("python3 scripts/create_plot.py");

    // free up resources
    delete [] x; delete[] y;
    delete [] viz_grid; delete [] L_viz; delete [] f_viz;
    delete [] error_grid_points; delete [] f_error; delete [] L_error;

    return 0;
}