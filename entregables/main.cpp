#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include "functions.h"

int main(int argc, char **argv){
    int const L = atoi(argv[1]);
    double const p = atof(argv[2]);
    std::random_device rd;
    std::mt19937 gen(rd());                                // Random seed from rd

    // Implementation of Hoshen-Kopelman Algorithm
    auto id_matrix = Hoshen_Kopelman(fill_matrix(L, p, gen), L);  // Toma la matriz que se llenó en fill_matrix y coloca los id 

    //print_matrix(id_matrix, L); // Descomentar esta línea y comentar la siguiente si se quiere visualizar la matriz
    print_sizes(id_matrix, L);    // Imprime el tamaño de cada cluster percolante (si hay)

    return 0;   
}