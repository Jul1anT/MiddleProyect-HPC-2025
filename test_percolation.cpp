#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include "functions.h"

// Simple test framework
#define ASSERT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            std::cerr << "FAIL: " << __func__ << " line " << __LINE__ \
                      << " - Expected: " << (expected) << ", Got: " << (actual) << std::endl; \
            return false; \
        } \
    } while(0)

#define ASSERT_TRUE(condition) \
    do { \
        if (!(condition)) { \
            std::cerr << "FAIL: " << __func__ << " line " << __LINE__ \
                      << " - Expected true, got false" << std::endl; \
            return false; \
        } \
    } while(0)

#define ASSERT_FALSE(condition) \
    do { \
        if ((condition)) { \
            std::cerr << "FAIL: " << __func__ << " line " << __LINE__ \
                      << " - Expected false, got true" << std::endl; \
            return false; \
        } \
    } while(0)

#define ASSERT_NEAR(expected, actual, tolerance) \
    do { \
        if (std::abs((expected) - (actual)) > (tolerance)) { \
            std::cerr << "FAIL: " << __func__ << " line " << __LINE__ \
                      << " - Expected: " << (expected) << ", Got: " << (actual) \
                      << ", Difference: " << std::abs((expected) - (actual)) << std::endl; \
            return false; \
        } \
    } while(0)

bool test_fill_matrix_dimensions() {
    std::mt19937 gen(12345);
    int L = 5;
    double p = 0.5;
    
    auto matrix = fill_matrix(L, p, gen);
    
    ASSERT_EQ(L, matrix.size());
    for (const auto& row : matrix) {
        ASSERT_EQ(L, row.size());
    }
    
    std::cout << "PASS: test_fill_matrix_dimensions" << std::endl;
    return true;
}

bool test_fill_matrix_values() {
    std::mt19937 gen(12345);
    int L = 10;
    
    // Test with p = 0.0 (no filled sites)
    auto matrix_empty = fill_matrix(L, 0.0, gen);
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            ASSERT_EQ(0, matrix_empty[i][j]);
        }
    }
    
    // Test with p = 1.0 (all sites filled)
    auto matrix_full = fill_matrix(L, 1.0, gen);
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            ASSERT_EQ(1, matrix_full[i][j]);
        }
    }
    
    std::cout << "PASS: test_fill_matrix_values" << std::endl;
    return true;
}

bool test_count_function() {
    // Create a simple test matrix
    std::vector<std::vector<int>> matrix = {
        {2, 0, 2},
        {0, 3, 0},  
        {2, 3, 3}
    };
    int L = 3;
    
    ASSERT_EQ(3, count(matrix, L, 2));
    ASSERT_EQ(3, count(matrix, L, 3));
    ASSERT_EQ(3, count(matrix, L, 0));
    ASSERT_EQ(0, count(matrix, L, 5)); // Non-existent value
    
    std::cout << "PASS: test_count_function" << std::endl;
    return true;
}

bool test_simple_percolation() {
    // Create a matrix that percolates horizontally
    std::vector<std::vector<int>> matrix = {
        {2, 2, 2},
        {0, 0, 0},
        {0, 0, 0}
    };
    int L = 3;
    
    auto result = check_if_percolant(matrix, L);
    ASSERT_EQ(1, result[0]); // Should percolate
    ASSERT_EQ(2, result[1]); // Cluster ID that percolates
    
    std::cout << "PASS: test_simple_percolation" << std::endl;
    return true;
}

bool test_no_percolation() {
    // Create a matrix that doesn't percolate
    std::vector<std::vector<int>> matrix = {
        {2, 0, 0},
        {0, 3, 0},
        {0, 0, 4}
    };
    int L = 3;
    
    auto result = check_if_percolant(matrix, L);
    ASSERT_EQ(0, result[0]); // Should not percolate
    
    std::cout << "PASS: test_no_percolation" << std::endl;
    return true;
}

bool test_merge_clusters() {
    std::vector<std::vector<int>> matrix = {
        {2, 3, 3},
        {2, 0, 3},
        {2, 0, 0}
    };
    int L = 3;
    
    // Merge cluster 3 into cluster 2
    merge_clusters(matrix, L, 3, 2);
    
    // All 3's should now be 2's
    std::vector<std::vector<int>> expected = {
        {2, 2, 2},
        {2, 0, 2},
        {2, 0, 0}
    };
    
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            ASSERT_EQ(expected[i][j], matrix[i][j]);
        }
    }
    
    std::cout << "PASS: test_merge_clusters" << std::endl;
    return true;
}

bool test_hoshen_kopelman_simple() {
    // Test a simple case with known result
    std::vector<std::vector<int>> input = {
        {1, 0, 1},
        {1, 1, 0},
        {0, 1, 1}
    };
    int L = 3;
    
    auto result = Hoshen_Kopelman(input, L);
    
    // Check that connected components have same ID
    ASSERT_EQ(result[0][0], result[1][0]); // (0,0) and (1,0) should be connected
    ASSERT_EQ(result[1][0], result[1][1]); // (1,0) and (1,1) should be connected
    ASSERT_EQ(result[1][1], result[2][1]); // (1,1) and (2,1) should be connected
    ASSERT_EQ(result[2][1], result[2][2]); // (2,1) and (2,2) should be connected
    
    // All non-zero elements should have same ID (all connected)
    int cluster_id = result[0][0];
    ASSERT_EQ(cluster_id, result[0][2]);
    ASSERT_EQ(cluster_id, result[1][0]);
    ASSERT_EQ(cluster_id, result[1][1]);
    ASSERT_EQ(cluster_id, result[2][1]);
    ASSERT_EQ(cluster_id, result[2][2]);
    
    std::cout << "PASS: test_hoshen_kopelman_simple" << std::endl;
    return true;
}

bool test_analyze_percolation() {
    // Create a test matrix with known properties
    std::vector<std::vector<int>> matrix = {
        {2, 2, 2},
        {0, 0, 0},
        {3, 3, 0}
    };
    int L = 3;
    
    auto stats = analyze_percolation(matrix, L);
    
    ASSERT_TRUE(stats.percolates);
    ASSERT_EQ(1, stats.total_clusters); // Only one percolating cluster
    ASSERT_EQ(3, stats.largest_cluster_size);
    ASSERT_NEAR(3.0, stats.mean_size, 0.01);
    ASSERT_NEAR(0.0, stats.std_deviation, 0.01); // Only one cluster, so std = 0
    
    std::cout << "PASS: test_analyze_percolation" << std::endl;
    return true;
}

bool test_probability_analysis() {
    // Test with extreme probabilities
    auto analysis_p0 = run_probability_analysis(0.0, 10, 5);
    ASSERT_NEAR(0.0, analysis_p0.percolation_probability, 0.01);
    
    auto analysis_p1 = run_probability_analysis(1.0, 10, 5);
    ASSERT_NEAR(1.0, analysis_p1.percolation_probability, 0.01);
    
    std::cout << "PASS: test_probability_analysis" << std::endl;
    return true;
}

bool test_edge_cases() {
    // Test with L = 1
    std::mt19937 gen(12345);
    auto matrix_1x1 = fill_matrix(1, 0.5, gen);
    ASSERT_EQ(1, matrix_1x1.size());
    ASSERT_EQ(1, matrix_1x1[0].size());
    
    // Test empty matrix
    std::vector<std::vector<int>> empty_matrix = {{0}};
    auto stats_empty = analyze_percolation(empty_matrix, 1);
    ASSERT_FALSE(stats_empty.percolates);
    
    std::cout << "PASS: test_edge_cases" << std::endl;
    return true;
}

int main() {
    std::cout << "Running Percolation Unit Tests..." << std::endl;
    std::cout << "=================================" << std::endl;
    
    std::vector<bool> results;
    
    results.push_back(test_fill_matrix_dimensions());
    results.push_back(test_fill_matrix_values());
    results.push_back(test_count_function());
    results.push_back(test_simple_percolation());
    results.push_back(test_no_percolation());
    results.push_back(test_merge_clusters());
    results.push_back(test_hoshen_kopelman_simple());
    results.push_back(test_analyze_percolation());
    results.push_back(test_probability_analysis());
    results.push_back(test_edge_cases());
    
    int passed = 0;
    int total = results.size();
    
    for (bool result : results) {
        if (result) passed++;
    }
    
    std::cout << "=================================" << std::endl;
    std::cout << "Test Results: " << passed << "/" << total << " passed" << std::endl;
    
    if (passed == total) {
        std::cout << "All tests PASSED! ✓" << std::endl;
        return 0;
    } else {
        std::cout << "Some tests FAILED! ✗" << std::endl