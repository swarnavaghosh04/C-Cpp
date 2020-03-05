#include <iostream>
#include <chrono>
#include "matrix.hpp"

using namespace math;

void printTransposedMatrix(MATRIX<int>& m){
    for(int i = 0; i < m.getTransposedRows(); i++){
        for(int j = 0; j < m.getTransposedColumns(); j++)
            printf("%-6d", m.transposed(i, j));
        std::cout << std::endl;
    }
}

void printMatrix(MATRIX<int>& m){
    for(int i = 0; i < m.getRows(); i++){
        for(int j = 0; j < m.getColumns(); j++)
            printf("%-6d", m(i, j));
        std::cout << std::endl;
    }
}

int main(int argv, char** argc){
    MATRIX<int> mat1(3, 4);
    mat1.fill([](m_index i, m_index j){return i+j;});
    printMatrix(mat1);
    std::cout << std::endl;
    printTransposedMatrix(mat1);
    std::cout << "\n<=======END=======>" << std::endl;
}
