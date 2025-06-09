#include "percolation.h"
#include <fstream>
#include <functional>
#include <random>
#include <iostream>
#include <unordered_map>

std::vector<std::vector<int>> fill_matrix(int const L, double const p, std::mt19937 &gen) {
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::vector<std::vector<int>> matrix(L, std::vector<int>(L, 0));
    for(int ii = 0; ii < L; ++ii) {
        for(int jj = 0; jj < L; ++jj) {
            if(dis(gen) <= p) {
                matrix[ii][jj] = 1;
            }
        }
    }
    return matrix;
}

std::vector<std::vector<int>> Hoshen_Kopelman(std::vector<std::vector<int>> matrix, int const L) {
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;
    int id_label = 1;  // ← Cambiar de 2 a 1
    
    std::function<int(int)> find = [&](int x) -> int {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;  // Inicializar si no existe
            rank[x] = 0;
        }
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };
    
    auto unite = [&](int x, int y) -> void {
        int px = find(x);
        int py = find(y);
        if (px == py) return;
        
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    };
    
    for(int ii = 0; ii < L; ii++) {
        for(int jj = 0; jj < L; jj++) {
            if (matrix[ii][jj] != 0) {
                std::vector<int> neighbors;
                
                if (ii > 0 && matrix[ii-1][jj] != 0) {
                    neighbors.push_back(matrix[ii-1][jj]);
                }
                
                if (jj > 0 && matrix[ii][jj-1] != 0) {
                    neighbors.push_back(matrix[ii][jj-1]);
                }
                
                if (neighbors.empty()) {
                    matrix[ii][jj] = id_label;
                    parent[id_label] = id_label;
                    rank[id_label] = 0;
                    id_label++;
                } else {
                    matrix[ii][jj] = neighbors[0];
                    
                    for (size_t k = 1; k < neighbors.size(); k++) {
                        unite(neighbors[0], neighbors[k]);
                    }
                }
            }
        }
    }
    
    for(int ii = 0; ii < L; ii++) {
        for(int jj = 0; jj < L; jj++) {
            if (matrix[ii][jj] != 0) {
                matrix[ii][jj] = find(matrix[ii][jj]);
            }
        }
    }
    
    return matrix;
}

std::vector<int> check_if_percolant(std::vector<std::vector<int>> const & matrix, int const L) {
    std::vector<int> results(1, 0);
    int is_unique;
    
    // Check horizontal percolation (left to right)
    for(int ii0 = 0; ii0 < L; ++ii0) {
        for(int iif = 0; iif < L; ++iif) {
            is_unique = 1;
            if ((matrix[ii0][0] == matrix[iif][L-1]) && (matrix[ii0][0] != 0)) {
                results[0] = 1;
                for (auto x : results) {
                    if (x == matrix[ii0][0]) {
                        is_unique = 0;
                    }
                }
                if (is_unique == 1) {
                    results.push_back(matrix[ii0][0]);
                }
            }
        }
    }
    
    // Check vertical percolation (top to bottom)
    for(int jj0 = 0; jj0 < L; ++jj0) {
        for(int jjf = 0; jjf < L; ++jjf) {
            is_unique = 1;
            if ((matrix[0][jj0] == matrix[L-1][jjf]) && (matrix[0][jj0] != 0)) {
                results[0] = 1;
                for (auto x : results) {
                    if (x == matrix[0][jj0]) {
                        is_unique = 0;
                    }
                }
                if (is_unique == 1) {
                    results.push_back(matrix[0][jj0]);
                }
            }
        }
    }
    return results;
}

int count(std::vector<std::vector<int>> const & matrix, int const L, int const index_to_count) {
    int n_elements = 0;
    for(int ii = 0; ii < L; ++ii) {
        for(int jj = 0; jj < L; ++jj) {
            if (matrix[ii][jj] == index_to_count) {
                ++n_elements;
            }
        }
    }
    return n_elements;
}

std::vector<int> cluster_sizes(std::vector<std::vector<int>> const & matrix, int const L) {
    auto result = check_if_percolant(matrix, L);
    result.erase(result.begin());
    std::vector<int> element_sizes;
    for (auto x : result) {
        element_sizes.push_back(count(matrix, L, x));
    }
    return element_sizes;
}

void print_matrix(std::vector<std::vector<int>> const & matrix, int const L) {
    for(int ii = 0; ii < L; ++ii) {
        for(int jj = 0; jj < L; ++jj) {
            std::cout << ii << "\t" << jj << "\t" << matrix[ii][jj] << "\n";
        }
    }
}

void print_sizes(std::vector<std::vector<int>> const & matrix, int const L) {
    auto result = check_if_percolant(matrix, L);
    result.erase(result.begin());
    std::vector<int> element_sizes;
    for (auto x : result) {
        element_sizes.push_back(count(matrix, L, x));
    }
    for (int i = 0; i < element_sizes.size(); i++) {
        std::cout << element_sizes[i] << "\n";
    }
}

void save_matrix_data(std::vector<std::vector<int>> const & matrix, int const L, const std::string& filename) {
    std::ofstream file(filename);
    for(int ii = 0; ii < L; ++ii) {
        for(int jj = 0; jj < L; ++jj) {
            file << ii << "\t" << jj << "\t" << matrix[ii][jj] << "\n";
        }
    }
    file.close();
}