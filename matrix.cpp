#include <iostream>
#include "matrix.hpp"

template<typename T>
T MATRIX<T>::get(int i, int j) const{
    matrix += (columns*i + j);
    T val = *matrix;
    matrix -= (columns*i + j);
    return val;
}

template<typename T>
T MATRIX<T>::get(int i) const{
    matrix += i;
    T val = *matrix;
    matrix -= i;
    return val;
}

template<typename T>
void MATRIX<T>::set(int i, int j, T val) const{
    matrix += (columns*i + j);
    *matrix = val;
    matrix -= (columns*i + j);
}

template<typename T>
void MATRIX<T>::set(int i, T val) const{
    matrix += i;
    *matrix = val;
    matrix -= i;
}

template<typename T>
MATRIX<T>::MATRIX(int rows, int columns){
    this->rows = rows;
    this->columns = columns;
    this->matrix = (T*)calloc(rows*columns, sizeof(T));
}

template<typename T>
MATRIX<T>::~MATRIX(){
    free(matrix);
}

template<typename T>
int MATRIX<T>::getRows() const{ return rows; }

template<typename T>
int MATRIX<T>::getColumns() const{ return columns; }

template<typename T>
int MATRIX<T>::getLength() const{ return (rows * columns); }

template<typename T>
template<typename U>
MATRIX<T> MATRIX<T>::operator+(MATRIX<U> m) const {
    MATRIX<T> mat(rows, columns);
    for(int i = 0; i < this->getLength(); i++){
        mat.set(i, ((T)(m.get(i)) + this->get(i)));
    }
    return mat;
}

int main(int argv, char** argc){
    const MATRIX<int>* mat1 = new MATRIX<int>(3, 5);
    const MATRIX<double>* mat2 = new MATRIX<double>(3, 5);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 5; j++){
            mat1->set(i, j, 1);
            mat2->set(i, j, 2.0);
        }
    }

    MATRIX<double> mat3 = (*mat2)+(*mat1);

    for(int i = 0; i < mat3.getRows(); i++){
        for(int j = 0; j < mat3.getColumns(); j++){
            printf("%-5.3f", mat3.get(i, j));
        }
        std::cout << std::endl;
    }

    delete mat1;
    delete mat2;
    delete &mat3;
}
