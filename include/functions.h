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


/**
 * Создаёт равномерную сетку на отрезке [a, b]
 * @param a      - левая граница
 * @param b      - правая граница
 * @param points - количество точек (включая концы)
 * @return       - указатель на динамический массив (caller отвечает за delete[])
 */
long double* create_uniform_grid (long double a, long double b, size_t points);


/**
 * Заполняет массив y значениями функции f(x) для каждой точки сетки x
 * @param x   - массив узлов (размера n)
 * @param y   - выходной массив (должен быть выделен)
 * @param n   - размер массивов
 */
void fill_function_values (const long double* x, long double* y, size_t n);


/**
 * Вычисляет значения локального интерполянта Лагранжа во всех точках заданной сетки
 * @param x          - узлы интерполяции (все M точек)
 * @param y          - значения функции в узлах
 * @param grid       - сетка, на которой нужно вычислить L(x)
 * @param L_out      - выходной массив (того же размера, что и grid)
 * @param grid_size  - размер сетки
 * @param a          - левая граница отрезка
 * @param step       - длина локального интервала ( = (b-a)/K )
 * @param K          - количество интервалов
 * @param N          - количество узлов на интервал (степень полинома = N-1)
 */
void compute_interpolant_on_grid (
    const long double *x,
    const long double *y,
    const long double *grid,
    long double *L_out,
    size_t grid_size,
    long double a,
    long double step,
    size_t K,
    size_t N
);


/**
 * Вычисляет абсолютные и относительные погрешности в нормах L1, L2, Linf
 * @param f_vals   - точные значения функции на сетке
 * @param L_vals   - значения интерполянта на той же сетке
 * @param n        - размер сетки
 * @param abs_err  - выходной массив из 3 элементов: [0]=L1, [1]=L2, [2]=Linf
 * @param rel_err  - выходной массив из 3 элементов: относительные ошибки
 */
void compute_error_norms (
    const long double *f_vals,
    const long double *L_vals,
    size_t n,
    long double abs_err[3],
    long double rel_err[3]
);


/**
 * Записывает в файл parameters.txt данные, необходимые для визуализации
 * @param filename - имя файла
 * @param M        - количество узлов интерполяции
 * @param x        - узлы интерполяции
 * @param y        - значения функции в узлах
 * @param M_viz    - количество точек визуализации
 * @param grid     - сетка для визуализации
 * @param f_grid   - значения функции на этой сетке
 * @param L_grid   - значения интерполянта на этой сетке
 */
void export_plot_data (
    const char *filename,
    size_t M,
    const long double *x,
    const long double *y,
    size_t M_viz,
    const long double *grid,
    const long double *f_grid,
    const long double *L_grid
);

#endif