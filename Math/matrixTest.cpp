#include <iostream>
#include "matrix.hpp"

void printMatrix(const math::MATRIX<int>& m){
    for(int i = 0; i < m.getRows(); i++){
        for(int j = 0; j < m.getColumns(); j++){
            printf("%-6d", m[i][j]);
        }
        std::cout << std::endl;
    }
}

typedef math::MATRIX<int> MAT;

MAT thisThing(){
    MAT mat = {5, 5};
    std::cout << "Func: " << &mat << ", "<< mat.getMatrix() << std::endl;
    mat.fill(5);
    return mat;
}

int main(int argv, char** argc){
    MAT thisMat;
    thisMat = thisThing();
    std::cout << "Main: " << &thisMat << ", " << thisMat.getMatrix() << std::endl;
    thisMat = thisMat * 3;
    printMatrix(thisMat);
    std::cout << "Main: " << &thisMat << ", " << thisMat.getMatrix() << std::endl;
}