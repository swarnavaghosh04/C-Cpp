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

class Time{
    private:
        std::chrono::system_clock::time_point start, end;
        const char* endMessage;
    public:
        Time(const char* endMessage) : endMessage(endMessage){
            start = std::chrono::system_clock::now();
        }
        ~Time(){
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> dur = end-start;
            printf("%s lasted %f ms\n", endMessage, (dur*1000));
        }
};

#define ITERS 10001
#define MAT_ROWS 7
#define MAT_COLUMNS 5

int main(int argv, char** argc){
    MATRIX<int> mat(MAT_ROWS, MAT_COLUMNS);
    MATRIX<int> tmat(MAT_COLUMNS, MAT_ROWS);
    mat.fill([](m_index i, m_index j){return i+j;});
    {
        Time t("transpose() test");
        for(int i = 0; i < ITERS; i++) tmat = mat.transpose();
    }
    {
        Time t("tranposeSelf() test");
        for(int i = 0; i < ITERS; i++) tmat = mat.transposeSelf();
    }
    printMatrix(mat);
}
