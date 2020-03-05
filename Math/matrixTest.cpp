#include <iostream>
#include <chrono>
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

    {
        Timer t;
        for(int i = 0; i < 10000; i++){
            mat1[i%3][i%4] = 9;
        }
    }

    std::cout << "\n<=======END=======>" << std::endl;
}
