#include "percolation.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <iomanip>

void run_full_study(std::mt19937 &gen) {
    std::vector<int> L_values = {32, 64, 128, 256, 512};
    std::vector<double> p_values;
    
    // Generate p values from 0 to 1 with 0.05 intervals
    for (double p = 0.0; p <= 1.0; p += 0.05) {
        p_values.push_back(p);
    }
    // Add additional p values around critical point
    std::vector<double> extra_p = {0.52, 0.54, 0.56, 0.58, 0.61, 0.62, 0.63, 0.67, 0.68};
    for (auto p : extra_p) {
        p_values.push_back(p);
    }
    
    std::ofstream profiling_report("data/profiling-report.txt");
    profiling_report << "# L\tp\tTrials\tTime(ms)\tPercolation_Prob\tAvg_Cluster_Size\tStd_Dev\n";
    
    std::cout << "Starting full percolation study...\n";
    std::cout << "Testing " << L_values.size() << " L values with " << p_values.size() << " p values each\n";
    
    for (int L : L_values) {
        std::cout << "\nProcessing L = " << L << "...\n";
        
        std::vector<double> L_probabilities;
        std::vector<double> L_percolation_probs;
        std::vector<double> L_avg_sizes;
        std::vector<double> L_times;
        
        for (double p : p_values) {
            int trials = (L <= 128) ? 100 : 50; // More trials for smaller systems
            
            auto start_time = std::chrono::high_resolution_clock::now();
            
            // Calculate statistics
            double perc_prob = calculate_percolation_probability(L, p, trials, gen);
            auto analysis = run_probability_analysis(p, L, trials);
            
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            
            L_probabilities.push_back(p);
            L_percolation_probs.push_back(perc_prob);
            L_avg_sizes.push_back(analysis.average_cluster_size);
            L_times.push_back(duration.count());
            
            // Write to profiling report
            profiling_report << L << "\t" << p << "\t" << trials << "\t" 
                           << duration.count() << "\t" << perc_prob << "\t" 
                           << analysis.average_cluster_size << "\t" 
                           << analysis.std_deviation << "\n";
            
            if (static_cast<int>(p * 100) % 10 == 0) {
                std::cout << "  p = " << std::fixed << std::setprecision(2) << p 
                         << ", P(p,L) = " << std::setprecision(4) << perc_prob 
                         << ", Time = " << duration.count() << "ms\n";
            }
        }
        
        // Save results for this L value
        std::string filename = "data/study_L" + std::to_string(L) + ".txt";
        std::ofstream L_file(filename);
        L_file << "# p\tPercolation_Prob\tAvg_Cluster_Size\tTime_ms\n";
        for (size_t i = 0; i < L_probabilities.size(); i++) {
            L_file << L_probabilities[i] << "\t" << L_percolation_probs[i] << "\t" 
                   << L_avg_sizes[i] << "\t" << L_times[i] << "\n";
        }
        L_file.close();
        std::cout << "  Results saved to " << filename << "\n";
    }
    
    profiling_report.close();
    std::cout << "\nFull study completed. Profiling report saved to data/profiling-report.txt\n";
}

void run_single_test(int L, double p, std::mt19937 &gen) {
    std::cout << "Running single percolation test: L = " << L << ", p = " << p << "\n";
    
    auto start_time = std::chrono::high_resolution_clock::now();
    auto matrix = fill_matrix(L, p, gen);
    auto id_matrix = Hoshen_Kopelman(matrix, L);
    auto end_time = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    
    save_matrix_data(id_matrix, L, "data/matrix_data.txt");
    
    auto result = check_if_percolant(id_matrix, L);
    auto stats = analyze_percolation(id_matrix, L);
    
    std::cout << "Results:\n";
    std::cout << "  System percolates: " << (result[0] == 1 ? "Yes" : "No") << "\n";
    std::cout << "  Total clusters: " << stats.total_clusters << "\n";
    std::cout << "  Largest cluster size: " << stats.largest_cluster_size << "\n";
    std::cout << "  Mean cluster size: " << std::fixed << std::setprecision(2) << stats.mean_size << "\n";
    std::cout << "  Standard deviation: " << std::setprecision(2) << stats.std_deviation << "\n";
    std::cout << "  Computation time: " << duration.count() << " µs\n";
    
    if (result[0] == 1) {
        std::cout << "  Percolating cluster detected!\n";
        print_sizes(id_matrix, L);
    }
    
    std::cout << "Matrix data saved to data/matrix_data.txt\n";
}

int main(int argc, char **argv) {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    if (argc == 1) {
        // No arguments - run full study
        run_full_study(gen);
    }
    else if (argc == 3) {
        // Two arguments - run single test
        int L = atoi(argv[1]);
        double p = atof(argv[2]);
        run_single_test(L, p, gen);
    }
    return 0;
}