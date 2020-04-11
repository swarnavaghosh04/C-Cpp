#include <iostream>
#include <chrono>
#include <cstdlib>
#include "matrix.hpp"
//#include "..\Other\Time.hpp"

void printTransposedMatrix(math::MATRIX& m){
    for(int i = 0; i < m.getTransposedRows(); i++){
        for(int j = 0; j < m.getTransposedColumns(); j++)
            printf("%-6.1f", m.transposed(i, j));
        std::cout << std::endl;
    }
}

void printMatrix(math::MATRIX& m){
    for(int i = 0; i < m.getRows(); i++){
        for(int j = 0; j < m.getColumns(); j++)
            printf("%-6.1f", m(i, j));
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
#define ITERS 10000
#define SQR_SIZE 6
#define SQUARE SQR_SIZE, SQR_SIZE

int main(int argv, char** argc){

    const double mat_matrix[] = {1,1,1,2,2,2,2,3,3,3,3,4,4,3,3,4,2,1,1,1,6,5,3,2,2};
    math::MATRIX mat(5, 5, mat_matrix);

    printMatrix(mat);
    printf("Determinent: %.1f\n", mat.determinant());

}
