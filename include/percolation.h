#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <cmath>

// Core percolation functions
std::vector<std::vector<int>> fill_matrix(int const L, double const p, std::mt19937 &gen);
std::vector<std::vector<int>> Hoshen_Kopelman(std::vector<std::vector<int>> matrix, int const L);
std::vector<std::vector<int>> merge_clusters(std::vector<std::vector<int>> & matrix, int const L, int const id_toe, int const id_tor);

// Analysis functions
std::vector<int> check_if_percolant(std::vector<std::vector<int>> const & matrix, int const L);
int count(std::vector<std::vector<int>> const & matrix, int const L, int const index_to_count);
std::vector<int> cluster_sizes(std::vector<std::vector<int>> const & matrix, int const L);

// Utility functions
void print_matrix(std::vector<std::vector<int>> const & matrix, int const L);
void print_sizes(std::vector<std::vector<int>> const & matrix, int const L);

// Statistics functions
double calculate_percolation_probability(int const L, double const p, int const trials, std::mt19937 &gen);
double calculate_average_cluster_size(int const L, double const p, int const trials, std::mt19937 &gen);
std::pair<double, double> calculate_cluster_statistics(std::vector<std::vector<int>> const & matrix, int const L);

// Data output functions
void save_matrix_data(std::vector<std::vector<int>> const & matrix, int const L, const std::string& filename);
void save_probability_results(const std::vector<double>& probabilities, const std::vector<double>& percolation_probs, const std::string& filename);