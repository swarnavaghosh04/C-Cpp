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

    double dp[] = {1., 2., 3., 4., 5., 6., 7., 8.};
    math::MATRIX mat = {2, 4, dp};
    math::MATRIX mat2 = {2, 3};
    mat2 = mat.transpose()*mat;
    printMatrix(mat2);

}
