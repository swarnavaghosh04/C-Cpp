/*
======= To do =========
> Copy Constructor
> Move Constructor
=======================
*/

/* =========== C++ Matrix Library ==============
=============== By Swarnava Ghosh ==============

MATRIX is a highly optimized stand-alone class that provides basic matrix operations.

*/

#pragma once
#include <stdlib.h>
#include <iostream>
#include <exception>

#define TYPE_T template<typename T>
#define TYPE_AB template<typename A, typename B>

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
		
	public:
		MATRIX(const int&, const int&);        	         // Constructor (takes in length and width of matrix)
		MATRIX(const int&, const int&, T* const);        // Constructor (takes in length, width, and a pointer to an already allocated space of memory. Could be used to create constant matrices)
		~MATRIX();               	                     // Destructor (frees the memory)
		int getRows() const;     	        // Returns the number of rows
		int getColumns() const;  	        // Returns the number of column
		int getLength() const;   	        // Returns the total length of the matrix (rows x columns)
		const T* getMatrix() const;         // Returns the location of the matrix
		void fillMatrix(T (*)(int,int));    // Fills The matrix with 
		// Operators ---------
		T* operator[](unsigned int i) const;                                       // Access numbers in the matrix
		TYPE_AB friend MATRIX<A> operator+(const MATRIX<A>&, const MATRIX<B>&);    // Add matrices
		TYPE_AB friend MATRIX<A> operator-(const MATRIX<A>&, const MATRIX<B>&);    // Subtract matrices
		TYPE_AB friend MATRIX<A> operator*(const MATRIX<A>&, const MATRIX<B>&);    // Multiply matrices
		TYPE_AB friend MATRIX<A> operator*(const MATRIX<A>&, const B&);            // Scalar Multiplier
		TYPE_AB friend MATRIX<A> operator*(const B&, const MATRIX<A>&);            // Scalar Multiplier
		TYPE_AB friend MATRIX<A> operator/(const MATRIX<A>&, const B&);            // Scalar Divisor
};

// =========== Matrix Class =================

// Matix Constructor (rows, columns) ====
TYPE_T
MATRIX<T>::MATRIX(const int& rows, const int& columns) : 
	rows(rows), 
	columns(columns),
	length(rows*columns)
{ this->matrix = new T[length]; }

// Matrix Constructor (rows, columns, pointer to 1D heap allocated memory) ======
TYPE_T
MATRIX<T>::MATRIX(const int& rows, const int& columns, T* const matrixPointer) :
	rows(rows), 
	columns(columns),
	length(rows*columns),
	matrix(matrixPointer),
{}

// Matrix Destrctor ======
TYPE_T
MATRIX<T>::~MATRIX(){
	delete[] matrix;
	std::cout << "DESTROY" << std::endl;
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

// Operator- =========
TYPE_T
T* MATRIX<T>::operator[](unsigned int i) const{ return (T*)&(matrix[i*columns]); }

// Operator+ =========
TYPE_AB
MATRIX<A> operator+(const MATRIX<A>& m1, const MATRIX<B>& m2) {      // Argument needs to be a reference, or else local copy will affect the input matrix
    if(m1.rows != m2.rows || m1.columns != m2.columns){
		throw DimensionException();
	}
	MATRIX<A> mat(m1.rows, m1.columns);
    for(int i = 0; i < m1.length; i++){
        mat.matrix[i] = m1.matrix[i] + (A)(m2.matrix[i]);
    }
    return mat;
}

// Operator- ==========
TYPE_AB
MATRIX<A> operator-(const MATRIX<A>& m1 , const MATRIX<B>& m2) {      // Argument needs to be a reference, or else local copy will affect the input matrix
    if(m1.rows != m2.rows || m1.columns != m2.columns){
		throw DimensionException();
	}
	MATRIX<A> mat(m1.rows, m1.columns);
    for(int i = 0; i < m1.length; i++){
        mat.matrix[i] = m1.matrix[i] - (A)(m2.matrix[i]);
    }
    return mat;
}

// Operator* =========
TYPE_AB
MATRIX<A> operator*(const MATRIX<A>& m1 , const MATRIX<B>& m2) {
	if(m1.columns != m2.rows){
		throw DimensionException();
	}
	MATRIX<A> mat(m1.rows, m2.columns);
	A temp = (A)0;
	for(int i = 0; i < m1.rows; i++){
		for(int j = 0; j < m2.columns; j++){
			for(int k = 0; k < m1.columns; k++){
				temp += m1[i][k]  *  (A)(m2[k][j]);
			}
			mat[i][j] =  temp;
			temp = (A)0;
		}
	}
	return mat;
}

// Scalar Multiplier ========
TYPE_AB
MATRIX<A> operator*(const MATRIX<A>& m, const B& c){
	MATRIX<A> mat(m.rows, m.columns);
	for(int i = 0; i < m.length; i++){
		mat.matrix[i] = m.matrix[i] * (A)c;
	}
	return mat;
}

TYPE_AB
MATRIX<A> operator*(const B& c, const MATRIX<A>& m){ return m*c; }

