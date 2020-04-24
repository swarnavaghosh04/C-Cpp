#include <iostream>
#include <chrono>
#include <cstdlib>
#include "matrix.hpp"
#include <exception>
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

    double matArr[] = {1,9,2,1,2,3,3,6,5};
    double vectArr[] = {2,4,5};

    const math::MATRIX mat(3, 3, matArr);
    const math::MATRIX vect(3,1, vectArr);

    math::MATRIX invMat = mat.inverse();

    try{
        
        math::MATRIX vect2 = mat*vect;
        printMatrix(vect2, "A*v = w");
        math::MATRIX vect3 = invMat*vect2;
        printMatrix(vect3, "A^-1*w = v");
        
    } catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

    printf("Det = %.4f\n", mat.determinant());
}
