#include <iostream>
#include <chrono>
#include <cstdlib>
#include "matrix.hpp"
//#include "..\Other\Time.hpp"


using namespace math;

void printTransposedMatrix(MATRIX<float>& m){
    for(int i = 0; i < m.getTransposedRows(); i++){
        for(int j = 0; j < m.getTransposedColumns(); j++)
            printf("%-6.1f", m.transposed(i, j));
        std::cout << std::endl;
    }
}

void printMatrix(MATRIX<float>& m){
    for(int i = 0; i < m.getRows(); i++){
        for(int j = 0; j < m.getColumns(); j++)
            printf("%-6.1f", m(i, j));
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printMatrix(MATRIX<int>& m){
    for(int i = 0; i < m.getRows(); i++){
        for(int j = 0; j < m.getColumns(); j++)
            printf("%-6d", m(i, j));
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

#define ITERS 10000
#define SQR_SIZE 6
#define SQUARE SQR_SIZE, SQR_SIZE

int main(int argv, char** argc){

    MATRIX<float> mat(SQUARE);
    mat.fill(0.f);

    for(int i = 0; i < mat.getRows(); i++){
        mat(i, i) = 2;
        try { mat(i, i+1) = -1; }
        catch(AccessViolationException e){}
        try { mat(i, i-1) = -1; }
        catch(AccessViolationException e){}
    }

    printMatrix(mat);

    MATRIX<float> e[6];
    for(int i = 0; i < SQR_SIZE; i++) e[i] = identity<float>(SQUARE);

    for(int i = 0; i < SQR_SIZE-1; i++){
        e[i](i, i+1) = i+1;
        e[i](i+1, i) = 1;
        e[i](i+1, i+1) = i+2;
    }

    e[SQR_SIZE-1](SQR_SIZE-1, SQR_SIZE-1) = 1.f/7.f;

    for(int i = 0; i < SQR_SIZE; i++) mat = e[i]*mat;

    printMatrix(mat);
    
    //for(int i = 0; i < SQR_SIZE; i++) printMatrix(e[i]);

    printMatrix(mat);

}
