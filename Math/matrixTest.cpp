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
    MAT mat2(3, 4);
    MAT mat3 = mat1*mat2;
    
    printMatrix(mat3);

    std::cout << "<=======END=======>" << std::endl;
}