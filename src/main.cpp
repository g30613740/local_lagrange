#include "functions.h"

int main () {

	// I. Parameters of the program. //
    const long double a = -3.14, b = 3.14;  // segment boundaries
    const size_t K = 10;                    // number of partitioning intervals
    const size_t N = 15;                    // number of nodes per interval (degree of polynomial = N-1)

    const long double K_grid_of_intervals = abs (a - b) / K ;

    const size_t M = K * N - K + 1;
    const long double h = abs (a - b) / (M - 1);

    // parameters of grid for plot creating //
    const size_t M_viz = 100;  // number of points for plotting graphs
    const long double grids_step = abs (a - b) / (M_viz - 1);

    // parameters for errors evaluating //
    const long double error_grids_step = h / 100;
    const size_t number_of_points_of_error_grid_step = M + 99 * (M - 1);

    // II. Memory allocation. //

    // arrays for Lagrange's polynom creating //
    long double *x = new long double [M];
    long double *y = new long double [M];
    // arrays for Lagrange's polynom creating and vizualisation //
    long double *grid = new long double [M_viz];
    long double *L = new long double [M_viz];
    // arrays for errors evaluating //
    long double *error_grid = new long double [number_of_points_of_error_grid_step];
    long double *values_of_the_math_function_in_the_points_of_error_grid = new long double [number_of_points_of_error_grid_step];
    long double *values_of_the_Lagranges_polynom_in_the_points_of_error_grid = new long double [number_of_points_of_error_grid_step];

    // III. Resources filling for creating Lagrange's polynom and creating Lagrange's polynom. //
    x[0] = a;
    y[0] = get_value_of_the_math_function_in_the_point (a);
    for (size_t i = 1; i < M; ++i) {
        x[i] = x[i-1] + h;
        y[i] = get_value_of_the_math_function_in_the_point (x[i]);
    }

    grid[0] = a;
    for (size_t i = 1; i < M_viz; ++i)
        grid[i] = grid[i-1] + grids_step;

    for (size_t i = 0; i < M_viz; ++i) {
        // where is grid[i]? what are the indexes of interpolation for grid[i]?
        // grid[i] is on the one of the Ks interval
        size_t initial_index_of_interpolation = 0;
        size_t final_index_of_interpolation = 0;
        // cout << "i = " << i << endl;
        for (size_t j = 1; j < K + 1; ++j) {
            // if (grid[i] - 1.0e-10 < j * K_grid_of_intervals) {
            if (grid[i] < j * K_grid_of_intervals) {
                // cout << "grid[i] = " << grid[i] << endl;
                // cout << "j * K_grid_of_intervals = " << j << " * " << K_grid_of_intervals << " = " << j * K_grid_of_intervals << endl;
                initial_index_of_interpolation = (j - 1) * (N - 1);
                final_index_of_interpolation = j * (N - 1);
                break;
            }
        }
        // cout << "initial_index_of_interpolation = " << initial_index_of_interpolation << endl;
        // cout << "final_index_of_interpolation = " << final_index_of_interpolation << endl;
        L[i] = get_polynoms_value_in_the_point (x, y, grid[i], initial_index_of_interpolation, final_index_of_interpolation);
    }

    // is values in the nodes f(x) (just values y[i]) are equal values in nodes of L(x)? //
    // for (size_t i = 0; i < M; ++i) {
    //     size_t initial_index_of_interpolation;
    //     size_t final_index_of_interpolation;
    //     cout << "i = " << i << endl;
    //     for (size_t j = 1; j < K + 1; ++j) {
    //         if (x[i] < j * K_grid_of_intervals) {
    //             cout << "x[i] = " << x[i] << endl;
    //             cout << "j * K_grid_of_intervals = " << j << " * " << K_grid_of_intervals << " = " << j * K_grid_of_intervals << endl;
    //             initial_index_of_interpolation = (j - 1) * (N - 1);
    //             final_index_of_interpolation = j * (N - 1);
    //             break;
    //         }
    //     }
    //     cout << "initial_index_of_interpolation = " << initial_index_of_interpolation << endl;
    //     cout << "final_index_of_interpolation = " << final_index_of_interpolation << endl;
    //     cout << get_polynoms_value_in_the_point (x, y, x[i], initial_index_of_interpolation, final_index_of_interpolation) << " v " << y[i] << "\n\n";
    // }

    // IV. Evaluating errors. //

    error_grid[0] = a;
    values_of_the_math_function_in_the_points_of_error_grid[0] = get_value_of_the_math_function_in_the_point (a);
    for (size_t i = 1; i < number_of_points_of_error_grid_step; ++i) {
        error_grid[i] = error_grid[i-1] + error_grids_step;
        values_of_the_math_function_in_the_points_of_error_grid[i] = get_value_of_the_math_function_in_the_point (error_grid[i]);
    }
    for (size_t i = 0; i < number_of_points_of_error_grid_step; ++i) {
        // where is grid[i]? what are the indexes of interpolation for grid[i]?
        // grid[i] is on the one of the Ks interval
        size_t initial_index_of_interpolation = 0;
        size_t final_index_of_interpolation = 0;
        // cout << "i = " << i << endl;
        for (size_t j = 1; j < K + 1; ++j) {
            if (error_grid[i] - 1.0e-10 < j * K_grid_of_intervals) {
                // cout << "grid[i] = " << grid[i] << endl;
                // cout << "j * K_grid_of_intervals = " << j << " * " << K_grid_of_intervals << " = " << j * K_grid_of_intervals << endl;
                initial_index_of_interpolation = (j - 1) * (N - 1);
                final_index_of_interpolation = j * (N - 1);
                break;
            }
        }
        // cout << "initial_index_of_interpolation = " << initial_index_of_interpolation << endl;
        // cout << "final_index_of_interpolation = " << final_index_of_interpolation << endl;
        values_of_the_Lagranges_polynom_in_the_points_of_error_grid[i] = get_polynoms_value_in_the_point (x, y, error_grid[i], initial_index_of_interpolation, final_index_of_interpolation);
    }
    long double abs_error_1 = 0.0, abs_error_2 = 0.0, abs_error_inf = abs (values_of_the_math_function_in_the_points_of_error_grid[0] - values_of_the_Lagranges_polynom_in_the_points_of_error_grid[0]);
    long double norm_f_1 = 0.0, norm_f_2 = 0.0, norm_f_inf = values_of_the_math_function_in_the_points_of_error_grid[0];
    for (size_t i = 0; i < number_of_points_of_error_grid_step; ++i) {
        long double difference = abs (values_of_the_math_function_in_the_points_of_error_grid[i] - values_of_the_Lagranges_polynom_in_the_points_of_error_grid[i]);
        abs_error_1 += difference;
        abs_error_2 += pow (difference, 2);
        if (abs_error_inf < difference)
            abs_error_inf = difference;

        norm_f_1 += abs (values_of_the_math_function_in_the_points_of_error_grid[i]);
        norm_f_2 += pow (abs (values_of_the_math_function_in_the_points_of_error_grid[i]), 2);
        if (norm_f_inf < values_of_the_math_function_in_the_points_of_error_grid[i])
            norm_f_inf = values_of_the_math_function_in_the_points_of_error_grid[i];
    }
    abs_error_2 = sqrt (abs_error_2);
    norm_f_2 = sqrt (norm_f_2);
    cout << "Absolute error  (1)  = " << abs_error_1 << endl;
    cout << "Absolute error  (2)  = " << abs_error_2 << endl;
    cout << "Absolute error (inf) = " << abs_error_inf << endl;
    cout << "Relative error  (1)  = " << abs_error_1 / norm_f_1 << endl;
    cout << "Relative error  (2)  = " << abs_error_2 / norm_f_2 << endl;
    cout << "Relative error (inf) = " << abs_error_inf / norm_f_inf << endl;

    // V. Creating plot. //

    // export data to the file //
    ofstream file;
    file.open ("parameters.txt");
    
    file << M << '\n' << M_viz << '\n';
    // extracting nodes of interpolation //
    for (size_t i = 0; i < M; ++i) {
        file << x[i] << ' ';
    }
    file << '\n';
    for (size_t i = 0; i < M; ++i) {
        file << y[i] << ' ';
    }
    file << '\n';
    // extracting data for plot creating //
    for (size_t i = 0; i < M_viz; ++i) {
        file << grid[i] << ' ';
    }
    file << '\n';
    for (size_t i = 0; i < M_viz; ++i) {
        file << get_value_of_the_math_function_in_the_point (grid[i]) << ' ';
    }
    file << '\n';
    for (size_t i = 0; i < M_viz; ++i) {
        file << L[i] << ' ';
    }
    file << endl;
    
    file.close ();

    // start Python for create plot //
    string comand_and_filename = "python3 scripts/create_plot.py"; // start Python
    system (comand_and_filename.c_str ());                 // calling Python

    // VI. Freeing up resources. //
    delete [] x;
    delete [] y;
    delete [] grid;
    delete [] L;
    delete [] error_grid;
    delete [] values_of_the_math_function_in_the_points_of_error_grid;
    delete [] values_of_the_Lagranges_polynom_in_the_points_of_error_grid;

    return 0;
}