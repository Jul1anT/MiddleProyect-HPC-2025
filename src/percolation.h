#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <cmath>

// Core percolation functions
std::vector<std::vector<int>> fill_matrix(int const L, double const p, std::mt19937 &gen);
std::vector<std::vector<int>> Hoshen_Kopelman(std::vector<std::vector<int>> matrix, int const L);

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

struct PercolationStats {
    bool percolates;
    int total_clusters;
    int largest_cluster_size;
    double mean_size;
    double std_deviation;
};
struct ProbabilityAnalysis {
    double percolation_probability;
    double average_cluster_size;
    double std_deviation;
};

PercolationStats analyze_percolation(std::vector<std::vector<int>> const & matrix, int const L);
ProbabilityAnalysis run_probability_analysis(double p, int L, int trials);

// Data output functions
void save_matrix_data(std::vector<std::vector<int>> const & matrix, int const L, const std::string& filename);
void save_probability_results(const std::vector<double>& probabilities, const std::vector<double>& percolation_probs, const std::string& filename);
