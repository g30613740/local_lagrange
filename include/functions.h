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

#endif