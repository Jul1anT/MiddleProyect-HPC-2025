#include "percolation.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

int main(int argc, char **argv) {
    if(argc < 3) {
        std::cout << "Usage: " << argv[0] << " <L> <p> [mode]\n";
        std::cout << "Modes:\n";
        std::cout << "  single - Run single simulation (default)\n";
        std::cout << "  prob - Calculate percolation probability\n";
        std::cout << "  study - Complete probability study\n";
        return 1;
    }
    
    int const L = atoi(argv[1]);
    double const p = atof(argv[2]);
    std::string mode = (argc > 3) ? argv[3] : "single";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    if(mode == "single") {
        // Single simulation mode
        auto matrix = fill_matrix(L, p, gen);
        auto id_matrix = Hoshen_Kopelman(matrix, L);
        
        // Save matrix data for visualization
        save_matrix_data(id_matrix, L, "data/matrix_data.txt");
        
        // Check if percolating and print results
        auto result = check_if_percolant(id_matrix, L);
        
        if(result[0] == 1) {
            std::cout << "= System percolates!\n";
            auto stats = calculate_cluster_statistics(id_matrix, L);
            std::cout << "= Average cluster size: " << stats.first << "\n";
            std::cout << "= Standard deviation: " << stats.second << "\n";
            
            std::cout << "= Percolating cluster sizes: ";
            print_sizes(id_matrix, L);
        } else {
            std::cout << "= System does not percolate.\n";
        }
    }
    else if(mode == "prob") {
        int trials = 100;
        double prob = calculate_percolation_probability(L, p, trials, gen);
        std::cout << "= Percolation probability for p=" << p << ", L=" << L << ": " << prob << "\n";
        
        double avg_size = calculate_average_cluster_size(L, p, trials, gen);
        std::cout << "= Average percolating cluster size: " << avg_size << "\n";
    }
    else if(mode == "study") {
        std::vector<double> probabilities;
        std::vector<double> percolation_probs;
        
        for(double test_p = 0.0; test_p <= 1.0; test_p += 0.05) {
            int trials = 50; // Reduced for faster execution
            double perc_prob = calculate_percolation_probability(L, test_p, trials, gen);
            
            probabilities.push_back(test_p);
            percolation_probs.push_back(perc_prob);
            
            std::cout << "= p=" << test_p << ", Percolation probability=" << perc_prob << "\n";
        }
        
        // Save results
        save_probability_results(probabilities, percolation_probs, "data/results/probability_study.txt");
        std::cout << "= Results saved to data/results/probability_study.txt\n";
    }
    else {
        std::cout << "= Unknown mode: " << mode << "\n";
        return 1;
    }
    
    return 0;
}