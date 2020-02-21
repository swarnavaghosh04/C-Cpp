/*
======= To do =========
> Copy constructor
=======================
*/

#pragma once
#include <stdlib.h>
#include <iostream>
#include <exception>

#define TYPE_T template<typename T>
#define TYPE_U template<typename U>

class DimensionException : public std::exception{
	public:
		const char* what() const throw(){
			return "The dimensions of the matrices are not compatible with the specified operation";
		}
};

TYPE_T
class MATRIX{
	
	private:
		int rows;                   // Number of rows in the matrix
		int columns;                // number of columns in the matrix
		int length;                 // number of rows x number of columns = total length of the matrix
		T* matrix;                  // Pointer to the memory location where the actual matrix array is located
		bool flag = 1;              // Whether matrix needs to be deleted by the destructor or not (determied by which constructor is being used)
	
	public:
		MATRIX(int, int);        	// Constructor (takes in length and width of matrix)
		MATRIX(int, int, T*);       // Constructor (takes in length, width, and a pointer to an already allocated space of memory. Could be used to create constant matrices)
		~MATRIX();               	// Destructor (frees the memory)
		T get(int, int) const;      // Gets a value from the matrix from a position relative to the rows and columns
		T get(int) const;      		// Gets a value from the matrix from a position relative to the length of the matrix (rows x columns)
		void set(int, int, T);      // Sets a value in the matrix at a specific location relative to rows and columns
		void set(int, T);      	    // Sets a value in the matrix at a specific location relative to the total length (rows x columns)
		int getRows() const;     	// Returns the number of rows
		int getColumns() const;  	// Returns the number of column
		int getLength() const;   	// Returns the total length of the matrix (rows x columns)
		const T* getMatrix() const; // Returns the location of the matrix
		// Operators ---------
		TYPE_U MATRIX<T> operator+(const MATRIX<U>&) const;   // Add matrices
		TYPE_U MATRIX<T> operator-(const MATRIX<U>&) const;   // Subtract matrices
		TYPE_U MATRIX<T> operator*(const MATRIX<U>&) const;   // Multiply matrices
		TYPE_U MATRIX<T> operator/(const MATRIX<U>&) const;   // Divide Matrices
		TYPE_U MATRIX<T> operator*(U) const;            // Scalar Multiplier
		TYPE_U MATRIX<T> operator/(U) const;            // Scalar Divisor
};

// =========== Matrix Class =================

// Matix Constructor ====
TYPE_T
MATRIX<T>::MATRIX(int rows, int columns) : 
	rows(rows), 
	columns(columns),
	length(rows*columns)
{ this->matrix = new T[length]; }

// Matrix Constructor ====
TYPE_T
MATRIX<T>::MATRIX(int rows, int columns, T* matrixPointer) :
	rows(rows), 
	columns(columns),
	length(rows*columns),
	matrix(matrixPointer),
	flag(0)
{}

// Matrix Destrctor ======
TYPE_T
MATRIX<T>::~MATRIX(){
	if(flag){
    	delete[] matrix;
		std::cout << "DESTROY" << std::endl;
	}
}

// Get =====
TYPE_T
T MATRIX<T>::get(int i, int j) const{
    return matrix[(columns*i)+j];
}

// Get =====
TYPE_T
T MATRIX<T>::get(int i) const{
    return matrix[i];
}

// Set =====
TYPE_T
void MATRIX<T>::set(int i, int j, T val) {
    matrix[(columns*i)+j] = val;
}

// Set ====
TYPE_T
void MATRIX<T>::set(int i, T val) {
    matrix[i] = val;
}

// Get Rows ======
TYPE_T
int MATRIX<T>::getRows() const{ return rows; }

// Get Columns ========
TYPE_T
int MATRIX<T>::getColumns() const{ return columns; }

// Get Length ========
TYPE_T
int MATRIX<T>::getLength() const{ return length; }

// Get Matrix
TYPE_T
const T* MATRIX<T>::getMatrix() const{ return matrix; }

// Operator+ =========

TYPE_T TYPE_U
MATRIX<T> MATRIX<T>::operator+(const MATRIX<U>& m) const {      // Argument needs to be a reference, or else local copy will affect the input matrix
    if(m.getRows() != rows || m.getColumns() != columns){
		throw DimensionException();
	}
	MATRIX<T> mat(rows, columns);
    for(int i = 0; i < getLength(); i++){
        mat.set(i, (((T)m.get(i)) + this->get(i)));
    }
    return mat;
}

// Operator- ==========

TYPE_T TYPE_U
MATRIX<T> MATRIX<T>::operator-(const MATRIX<U>& m) const {      // Argument needs to be a reference, or else local copy will affect the input matrix
    if(m.getRows() != rows || m.getColumns() != columns){
		throw DimensionException();
	}
	MATRIX<T> mat(rows, columns);
    for(int i = 0; i < getLength(); i++){
        mat.set(i, (((T)m.get(i)) - this->get(i)));
    }
    return mat;
}

// Operator* =========

TYPE_T TYPE_U
MATRIX<T> MATRIX<T>::operator*(const MATRIX<U>& m) const {
	if(columns != m.getRows()){
		throw DimensionException();
	}
	MATRIX<T> mat(rows, m.getColumns());
	T temp = (T)0;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < m.getColumns(); j++){
			for(int k = 0; k < columns; k++){
				temp += (this->get(i, k))  *  ((T)m.get(k, j));
			}
			mat.set(i, j, temp);
			temp = (T)0;
		}
	}
	return mat;
}

// Operator* scalar =======

TYPE_T TYPE_U
MATRIX<T> MATRIX<T>::operator*(U s) const {
	MATRIX<T> mat(rows, columns);
	for(int i = 0; i < length; i++){
		mat.set(i, get(i)*(T)s);
	}

}
