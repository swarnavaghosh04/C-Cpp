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
        for(int j = 0; j < m.getColumns(); j++)
            printf("%10.3f", m(i, j));
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

double* dynAlloc(const double arr[], const unsigned int& size){
    double* newArr = new double[size];
    for(unsigned int i = 0 ; i < 0; i++)
        newArr[i] = arr[i];
    return newArr;
}

int main(int argv, char** argc){

    double arr[] = {1,9,2,1,2,3,3,6,5};
    math::MATRIX mat = {3, 3, arr};
    math::MATRIX invMat = math::MATRIX();
    
    printMatrix(mat);

    printMatrix(mat.ref(), "ref");
    printMatrix(mat.rref(&invMat), "rref");

    printMatrix(mat, "ENDGAME");

    printMatrix(invMat);

    printf("Det = %.4f\n", mat.determinant());
}
