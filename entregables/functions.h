#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

std::vector<std::vector<int>> fill_matrix(int const L, double const p, std::mt19937 &gen);
std::vector<std::vector<int>> Hoshen_Kopelman(std::vector<std::vector<int>> matrix, int const L);
std::vector<std::vector<int>> merge_clusters(std::vector<std::vector<int>> & matrix, int const L, int const id_toe, int const id_tor);
void print_matrix(std::vector<std::vector<int>> const & matrix, int const L);
std::vector<int> check_if_percolant(std::vector<std::vector<int>> const & matrix, int const L);
int count(std::vector<std::vector<int>> const & matrix, int const L, int const index_to_count);
void print_sizes(std::vector<std::vector<int>> const & matrix, int const L);