#include "../include/percolation.h"
#include <fstream>
#include <numeric>

double calculate_percolation_probability(int const L, double const p, int const trials, std::mt19937 &gen) {
    int percolating_count = 0;
    
    for(int trial = 0; trial < trials; trial++) {
        auto matrix = fill_matrix(L, p, gen);
        auto id_matrix = Hoshen_Kopelman(matrix, L);
        auto result = check_if_percolant(id_matrix, L);
        
        if(result[0] == 1) {
            percolating_count++;
        }
    }
    
    return static_cast<double>(percolating_count) / trials;
}

double calculate_average_cluster_size(int const L, double const p, int const trials, std::mt19937 &gen) {
    double total_size = 0.0;
    int percolating_count = 0;
    
    for(int trial = 0; trial < trials; trial++) {
        auto matrix = fill_matrix(L, p, gen);
        auto id_matrix = Hoshen_Kopelman(matrix, L);
        auto result = check_if_percolant(id_matrix, L);
        
        if(result[0] == 1) {
            auto sizes = cluster_sizes(id_matrix, L);
            for(auto size : sizes) {
                total_size += size;
                percolating_count++;
            }
        }
    }
    
    return percolating_count > 0 ? total_size / percolating_count : 0.0;
}

std::pair<double, double> calculate_cluster_statistics(std::vector<std::vector<int>> const & matrix, int const L) {
    auto result = check_if_percolant(matrix, L);
    
    if(result[0] == 0) {
        return std::make_pair(0.0, 0.0);
    }
    
    result.erase(result.begin());
    std::vector<int> element_sizes;
    
    for (auto x : result) {
        element_sizes.push_back(count(matrix, L, x));
    }
    
    if(element_sizes.empty()) {
        return std::make_pair(0.0, 0.0);
    }
    
    // Calculate mean
    double sum = std::accumulate(element_sizes.begin(), element_sizes.end(), 0.0);
    double mean = sum / element_sizes.size();
    
    // Calculate standard deviation
    double variance = 0.0;
    for(auto size : element_sizes) {
        variance += std::pow(size - mean, 2);
    }
    variance /= element_sizes.size();
    double std_dev = std::sqrt(variance);
    
    return std::make_pair(mean, std_dev);
}

void save_probability_results(const std::vector<double>& probabilities, const std::vector<double>& percolation_probs, const std::string& filename) {
    std::ofstream file(filename);
    file << "# Probability\tPercolation_Probability\n";
    
    for(size_t i = 0; i < probabilities.size(); i++) {
        file << probabilities[i] << "\t" << percolation_probs[i] << "\n";
    }
    file.close();
}