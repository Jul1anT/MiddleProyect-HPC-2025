#include <iostream>
#include <vector>
#include <random>
#include <cmath>

std::vector<std::vector<int>> merge_clusters(std::vector<std::vector<int>> & matrix, int const L, int const id_toe, int const id_tor);
int print_matrix(std::vector<std::vector<int>> const & matrix, int const L);
std::vector<int> check_if_percolant(std::vector<std::vector<int>> const & matrix, int const L);
std::vector<double> make_stats(std::vector<int> & percolant_indexes, std::vector<std::vector<int>> const & matrix, int const L);
int count(std::vector<std::vector<int>> const & matrix, int const L, int const index_to_count);

int main(void){
    int L = 13;
    double p = 0.7;
    std::vector<std::vector<int>> id_matrix(L, std::vector<int>(L, 0));
    std::mt19937 gen(1);                                // fixed seed = 1
    std::uniform_real_distribution<> dis(0.0, 1.0);     // uniform distribution in 0-1
    for(int ii = 0; ii < L; ++ii) {
        for(int jj = 0; jj < L; ++jj) {
            if(dis(gen)<=p){
                id_matrix[ii][jj]  = 1;                  // fill elements in matrix with 1 with probability p
            }
        }
    }
    
    // Implementation of Hoshen-Kopelman Algorithm
    int id_label = 2;
    for(int ii = 0; ii < L; ++ii) {
        for(int jj = 0; jj < L; ++jj) {
            if (ii==0){
                if (jj==0){
                    if (id_matrix[ii][jj]==1){
                        id_matrix[ii][jj]=id_label;
                    }
                } else if (id_matrix[ii][jj]!=0){
                    if(id_matrix[ii][jj-1]!=0){
                        id_matrix[ii][jj] = id_matrix[ii][jj-1];
                    } else{
                        ++id_label;
                        id_matrix[ii][jj] = id_label;           // if [0][0] is empty, the first label is 3. If [0][0] is full, the first label is 2
                    }
                }
            } else if (jj==0){
                if(id_matrix[ii-1][jj]!=0){
                    id_matrix[ii][jj] = id_matrix[ii-1][jj];
                } else {
                    ++id_label;
                    id_matrix[ii][jj] = id_label;
                }
            } else if (id_matrix[ii][jj]!=0){
                if ((id_matrix[ii-1][jj]!=0)&&(id_matrix[ii][jj-1]!=0)){
                    merge_clusters(id_matrix, L, id_matrix[ii][jj-1], id_matrix[ii-1][jj]); // gives priority to 'last ii'
                    id_matrix[ii][jj] = id_matrix[ii-1][jj];  
                } else if(id_matrix[ii-1][jj]==0){
                    id_matrix[ii][jj] = id_matrix[ii][jj-1];
                } else if(id_matrix[ii][jj-1]==0){
                    id_matrix[ii][jj] = id_matrix[ii-1][jj];
                } else {
                    ++id_label;
                    id_matrix[ii][jj] = id_label;
                }

            } 
        }
    }
    print_matrix(id_matrix, L);
    /* std::vector<int> result = check_if_percolant(id_matrix, L);
    if(result[0] == -1){
        std::cout << result[0] << "\t";
        std::vector<double> percolant_size_stats = make_stats(result, id_matrix, L);
        std::cout <<  percolant_size_stats[0] << "\t" << percolant_size_stats[1] << "\n";
    } else {
        std::cout << result[0] << "\t" << result[0] << "\t" << result[0] << "\n";
    }*/
    return 0;   
}

std::vector<std::vector<int>> merge_clusters(std::vector<std::vector<int>> & matrix, int const L, int const id_toe, int const id_tor){
    for(int ii = 0; ii < L; ++ii) {
        for(int jj = 0; jj < L; ++jj) {
            if (matrix[ii][jj]== id_toe){
                matrix[ii][jj]= id_tor;
            }
        }
    }
    return matrix;
}

int print_matrix(std::vector<std::vector<int>> const & matrix, int const L){
    for(int ii = 0; ii < L; ++ii) {
        for(int jj = 0; jj < L; ++jj) {
            std::cout << ii << "\t" << jj << "\t" << matrix[ii][jj]   << "\n";
        }
    }
    return 1;
}

std::vector<int> check_if_percolant(std::vector<std::vector<int>> const & matrix, int const L){
    std::vector<int> results(1,0);  
    int is_unique;
    for(int ii0 = 0; ii0 < L; ++ii0) {
        for(int iif = 0; iif < L; ++iif) {
            is_unique = 1;
            if ((matrix[ii0][0]==matrix[iif][L-1])&&(matrix[ii0][0]!=0)){
                results[0] = -1;
                for (auto x: results){
                    if (x==matrix[ii0][0]){
                        is_unique =  0;
                    }
                }
                if (is_unique==1){
                    results.push_back(matrix[ii0][0]);
                }
            } 
        }
    }
    for(int jj0 = 0; jj0 < L; ++jj0) {
        for(int jjf = 0; jjf < L; ++jjf) {
            is_unique = 1;
            if ((matrix[0][jj0]==matrix[L-1][jjf])&&(matrix[0][jj0]!=0)){
                results[0] = -1;
                for (auto x: results){
                    if (x==matrix[0][jj0]){
                        is_unique =  0;
                    }
                }
                if (is_unique==1){
                    results.push_back(matrix[0][jj0]);
                } 
            }
        }
                                                                            
    }
    return results;
}

std::vector<double> make_stats(std::vector<int> & percolant_indexes, std::vector<std::vector<int>> const & matrix, int const L){
    percolant_indexes.erase(percolant_indexes.begin());
    std::vector<int> element_sizes;
    std::vector<double> stats(2,0);
    for (auto x: percolant_indexes){
        element_sizes.push_back(count(matrix, L, x));
    }
    int total_mean = 0, total_std = 0;
    for (auto x: element_sizes){
        total_mean += x;
    }
    double partial =  (1.0*total_mean)/element_sizes.size();
    stats[0] = partial;
    for (auto x: element_sizes){
        x = std::pow(x-stats[0] ,2);
        total_std += x; 
    }
    partial = (1.0*total_std)/element_sizes.size();
    stats[1] = std::sqrt(partial);
    return stats;
}

int count(std::vector<std::vector<int>> const & matrix, int const L, int const index_to_count){
    int n_elements = 0;
    for(int ii = 0; ii < L; ++ii) {
        for(int jj = 0; jj < L; ++jj) {
            if (matrix[ii][jj]==index_to_count){
                ++n_elements;
            } 
        }
    }
    return n_elements;
}     
/*  DONE Crear arreglo LxL Matriz probabilidades
    DONE Rellenar arreglo con numeros entre 0 y 1 
    DONE Indicando si está lleno
    DONE Indices
    NOT NEEDCrear arreglo LxL Matriz id
    
    DONE Verificar si el arreglo tiene al menos un cluster percolante

    DONE Contar el numero de elementos de todos los clusters percolantes
    DONE sacar estadisticas (mean size and standard deviation)
*/
// nohup stress -c 1 &
// tmux 