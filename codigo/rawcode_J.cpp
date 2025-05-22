#include <iostream>
#include <vector>
#include <random>

std::vector<std::vector<int>>  merge_clusters(std::vector<std::vector<int>> & matrix, int const L, int const id_toe, int const id_tor);
int print_matrix(std::vector<std::vector<int>> const & matrix, int const L);

int main(void){
    int L = 30;
    double p = 0.65;
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
                        id_matrix[ii][jj] = id_label;//si [0][0] está vacio, el primer label es 3. Si [0][0] está lleno, el primer label es 2
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
                    merge_clusters(id_matrix, L, id_matrix[ii][jj-1], id_matrix[ii-1][jj]); // le da prioridad al 'ii pasado'
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

    return 0;
}

std::vector<std::vector<int>>  merge_clusters(std::vector<std::vector<int>> & matrix, int const L, int const id_toe, int const id_tor){
    for(int ii = 0; ii < L; ++ii) {
        for(int jj = 0; jj < L; ++jj) {
            if (matrix[ii][jj]== id_toe){
                matrix[ii][jj]== id_tor;
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






    
    
    
    
/*  DONE Crear arreglo LxL Matriz probabilidades
    DONE Rellenar arreglo con numeros entre 0 y 1 
    Indicando si está lleno
    Indices
    Crear arreglo LxL Matriz id
    
    Verificar si el arreglo tiene al menos un cluster percolante

    Contar el numero de elementos de todos los clusters percolantes
    sacar estadisticas (mean size and standard deviation)
*/