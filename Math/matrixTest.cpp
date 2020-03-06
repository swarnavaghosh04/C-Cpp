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
    MATRIX<int> mat(8, 1);
    mat.fill([](m_index i, m_index j){return (i*i + j*j - 2*i*j);});
    std::cout << "mat:\n";
    printMatrix(mat);
    mat.transposeSelf();
    std::cout << "\nmat: \n";
    printMatrix(mat);
    std::cout << "\n<=======END=======>" << std::endl;
}
