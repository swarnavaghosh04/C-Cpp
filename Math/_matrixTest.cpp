#include <iostream>
#include <chrono>
#include <cstdlib>
#include "matrix.hpp"
//#include "..\Other\Time.hpp"

void printTransposedMatrix(const math::MATRIX& m){
    for(int i = 0; i < m.getTransposedRows(); i++){
        for(int j = 0; j < m.getTransposedColumns(); j++)
            printf("%-6.1f", m.transposed(i, j));
        std::cout << std::endl;
    }
}

void printMatrix(const math::MATRIX& m, const char* message = ""){
    printf("%s:\n", message);
    for(int i = 0; i < m.getRows(); i++){
        printf("\t");
        for(int j = 0; j < m.getColumns(); j++)
            printf("%-6.1f", m(i, j));
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(int argv, char** argc){
    const double dp[] = {1.,2,7,8,5,6,7,3,9,10,11,12,13,14,15,16};
    const math::MATRIX mat1 = {4, 4, dp};
    printMatrix(mat1, "A");
    printf("|A| = %.4f\n", mat1.determinant());
}
