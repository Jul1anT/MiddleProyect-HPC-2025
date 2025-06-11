#include "percolation.h"
#include <fstream>
#include <numeric>
#include <algorithm>
#include <unordered_set>

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
    int percolating_trials = 0;
    
    for(int trial = 0; trial < trials; trial++) {
        auto matrix = fill_matrix(L, p, gen);
        auto id_matrix = Hoshen_Kopelman(matrix, L);
        auto result = check_if_percolant(id_matrix, L);
        
        if(result[0] == 1) {
            percolating_trials++;
            result.erase(result.begin());
            
            for(auto cluster_id : result) {
                total_size += count(id_matrix, L, cluster_id);
            }
        }
    }
    
    return (percolating_trials > 0) ? total_size / percolating_trials : 0.0;
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
    
    double sum = std::accumulate(element_sizes.begin(), element_sizes.end(), 0.0);
    double mean = sum / element_sizes.size();
    
    double variance = 0.0;
    for(auto size : element_sizes) {
        variance += std::pow(size - mean, 2);
    }
    variance /= element_sizes.size();
    double std_dev = std::sqrt(variance);
    
    return std::make_pair(mean, std_dev);
}

PercolationStats analyze_percolation(std::vector<std::vector<int>> const & matrix, int const L) {
    PercolationStats stats;
    
    auto result = check_if_percolant(matrix, L);
    stats.percolates = (result[0] == 1);
    
    std::unordered_set<int> unique_clusters;
    int max_cluster_size = 0;
    
    for(int ii = 0; ii < L; ii++) {
        for(int jj = 0; jj < L; jj++) {
            if(matrix[ii][jj] != 0) {
                unique_clusters.insert(matrix[ii][jj]);
            }
        }
    }
    
    stats.total_clusters = unique_clusters.size();
    
    std::vector<int> cluster_size_list;
    for(auto cluster_id : unique_clusters) {
        int size = count(matrix, L, cluster_id);
        cluster_size_list.push_back(size);
        max_cluster_size = std::max(max_cluster_size, size);
    }
    
    stats.largest_cluster_size = max_cluster_size;
    
    if(!cluster_size_list.empty()) {
        double sum = std::accumulate(cluster_size_list.begin(), cluster_size_list.end(), 0.0);
        stats.mean_size = sum / cluster_size_list.size();
        
        double variance = 0.0;
        for(auto size : cluster_size_list) {
            variance += std::pow(size - stats.mean_size, 2);
        }
        variance /= cluster_size_list.size();
        stats.std_deviation = std::sqrt(variance);
    } else {
        stats.mean_size = 0.0;
        stats.std_deviation = 0.0;
    }
    
    return stats;
}

ProbabilityAnalysis run_probability_analysis(double p, int L, int trials) {
    ProbabilityAnalysis analysis;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    analysis.percolation_probability = calculate_percolation_probability(L, p, trials, gen);
    
    double total_avg_size = 0.0;
    std::vector<double> avg_sizes;
    int valid_trials = 0;
    
    for(int trial = 0; trial < trials; trial++) {
        auto matrix = fill_matrix(L, p, gen);
        auto id_matrix = Hoshen_Kopelman(matrix, L);
        auto stats = calculate_cluster_statistics(id_matrix, L);
        
        if(stats.first > 0) {
            avg_sizes.push_back(stats.first/(L*L));
            total_avg_size += stats.first;
            valid_trials++;
        }
    }
    
    if(valid_trials > 0) {
        analysis.average_cluster_size = total_avg_size / (valid_trials*L*L);
        
        double variance = 0.0;
        for(auto avg : avg_sizes) {
            variance += std::pow(avg - analysis.average_cluster_size, 2);
        }
        variance /= valid_trials;
        analysis.std_deviation = std::sqrt(variance);
    } else {
        analysis.average_cluster_size = 0.0;
        analysis.std_deviation = 0.0;
    }
    
    return analysis;
}

void save_probability_results(const std::vector<double>& probabilities, const std::vector<double>& percolation_probs, const std::string& filename) {
    std::ofstream file(filename);
    file << "# Probability\tPercolation_Probability\n";
    
    for(size_t i = 0; i < probabilities.size(); i++) {
        file << probabilities[i] << "\t" << percolation_probs[i] << "\n";
    }
    file.close();
}