#include <iostream>
#include "matrix.hpp"

template<typename T>
T MATRIX<T>::get(int i, int j){
    matrix += (columns*i + j);
    T val = *matrix;
    matrix -= (columns*i + j);
    return val;
}

template<typename T>
void MATRIX<T>::set(int i, int j, T val){
    matrix += (columns*i + j);
    *matrix = val;
    matrix -= (columns*i + j);
}

template<typename T>
MATRIX<T>::MATRIX(int rows, int columns){
    this->rows = rows;
    this->columns = columns;
    this->matrix = (T*)calloc(rows*columns, sizeof(T));
}

template<typename T>
MATRIX<T>::~MATRIX(){
    free(this->matrix);
}

int main(int argv, char** argc){
    MATRIX<int>* mat = new MATRIX<int>(3, 5);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 5; j++){
            mat->set(i, j, i*j);
        }
    }

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 5; j++){
            printf("%-5d", mat->get(i, j));
        }
        std::cout << std::endl;
    }
}
