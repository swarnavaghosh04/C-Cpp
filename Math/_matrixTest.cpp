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

void printMatrix(const math::MATRIX& m, const char* message = "matrix"){
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
    char mat[20];

    double matMem[] = {1.,2,3,4};
    
    for(int i = 0; i < 4; i++) matMem[i] = (double)(i+1);

    *(unsigned int*)mat = 2;
    *(unsigned int*)&mat[4] = 2;
    *(unsigned int*)&mat[8] = 4;
    *(double**)&mat[12] = (double*)matMem;
    *(int*)&mat[16] = 0;

    math::MATRIX matr = *(math::MATRIX*)mat;

    printMatrix(matr);
    std::cout << matr.getCanDelete() << std::endl;
}
