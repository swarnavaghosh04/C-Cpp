#include <iostream>
#include "matrix.hpp"
typedef math::MATRIX<int> MAT;

void printMatrix(const MAT& m){
    for(int i = 0; i < m.getRows(); i++){
        for(int j = 0; j < m.getColumns(); j++){
            printf("%-6d", m[i][j]);
        }
        std::cout << std::endl;
    }
}

int main(int argv, char** argc){
    MAT mat1(3, 4);
    MAT mat2(4, 4);

    mat1.fill(12);
    mat2.fill([](m_index i, m_index j){return i+j;});

    mat1(2,1) = 6;
    std::cout << "MATRIX 1:\n";
    printMatrix(mat1);

    std::cout << "MATRIX 1:\n";
    printMatrix(mat1);

    std::cout << "\nMatrix 2:\n";
    printMatrix(mat2);


    std::cout << "\n<=======END=======>" << std::endl;
}