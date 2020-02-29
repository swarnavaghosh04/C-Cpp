#include <iostream>
#include "matrix.hpp"

void printMatrix(const sg::MATRIX<int>& m){
    for(int i = 0; i < m.getRows(); i++){
        for(int j = 0; j < m.getColumns(); j++){
            printf("%-6d", m[i][j]);
        }
        std::cout << std::endl;
    }
}

int main(int argv, char** argc){

    sg::MATRIX<int> mat1(3, 4);
    sg::MATRIX<int> mat2(4, 3);
    mat1.fill([](m_index i, m_index j){return i+j;});
    mat2.fill(5);

    mat1 = 3*mat1;
    sg::MATRIX<int> mat3 = mat1*mat2;

    std::cout << "Matrix 1:" << std::endl;
    printMatrix(mat1);
    std::cout << std::endl;

    std::cout << "Matrix 2:" << std::endl;
    printMatrix(mat2);
    std::cout << std::endl;

    std::cout << "Matrix 1 * Matrix 2:" << std::endl;
    printMatrix(mat3);

    return 0;
}