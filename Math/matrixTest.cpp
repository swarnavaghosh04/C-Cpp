#include <iostream>
#include "matrix.hpp"

using namespace math;

TYPE_T
void printMatrix(MATRIX<T>& m){
    for(int i = 0; i < m.getRows(); i++){
        for(int j = 0; j < m.getColumns(); j++){
            printf("%-10.3f", (double)m(i, j));
        }
        std::cout << std::endl;
    }
};

int main(int argv, char** argc){
    MATRIX<int> mat1(3, 4);
    MATRIX<double> mat2(4, 4);

    mat1.fill(12);
    mat2.fill([](m_index i, m_index j){return (double)(i+j);});

    mat1(2,1) = 6;
    std::cout << "MATRIX 1:\n";
    printMatrix(mat1);

    std::cout << "MATRIX 1:\n";
    printMatrix(mat1);

    std::cout << "\nMatrix 2:\n";
    printMatrix(mat2);

    std::cout << "\n<=======END=======>" << std::endl;
}
