#include <iostream>
#include <vector>
#include <cassert>
#include "percolation.h"

void test_fill_matrix_dimensions() {
    std::mt19937 gen(12345);
    int L = 5;
    double p = 0.5;
    
    auto matrix = fill_matrix(L, p, gen);
    
    assert(L == matrix.size());
    for (const auto& row : matrix) {
        assert(L == row.size());
    }
}

void test_fill_matrix_values() {
    std::mt19937 gen(12345);
    int L = 10;
    
    auto matrix_empty = fill_matrix(L, 0.0, gen);
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            assert(0 == matrix_empty[i][j]);
        }
    }
    
    auto matrix_full = fill_matrix(L, 1.0, gen);
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            assert(1 == matrix_full[i][j]);
        }
    }
}

void test_count_function() {
    std::vector<std::vector<int>> matrix = {
        {2, 0, 2},
        {0, 3, 0},  
        {2, 3, 3}
    };
    int L = 3;
    
    assert(3 == count(matrix, L, 2));
    assert(3 == count(matrix, L, 3));
    assert(3 == count(matrix, L, 0));
    assert(0 == count(matrix, L, 5));
}

void test_percolation() {
    std::vector<std::vector<int>> matrix = {
        {2, 2, 2},
        {0, 0, 0},
        {0, 0, 0}
    };
    int L = 3;
    
    auto result = check_if_percolant(matrix, L);
    assert(1 == result[0]);
    assert(2 == result[1]);
}

void test_no_percolation() {
    std::vector<std::vector<int>> matrix = {
        {2, 0, 0},
        {0, 3, 0},
        {0, 0, 4}
    };
    int L = 3;
    
    auto result = check_if_percolant(matrix, L);
    assert(0 == result[0]);
}


int main() {
    test_fill_matrix_dimensions();
    test_fill_matrix_values();
    test_count_function();
    test_percolation();
    test_no_percolation();
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}