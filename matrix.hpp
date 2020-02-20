#pragma once
#include <stdlib.h>

template<typename T>
class MATRIX{
	
	private:
		int rows;                   // Number of rows in the matrix
		int columns;                // number of columns in the matrix
		int length;                 // number of rows x number of columns = total length of the matrix
		T* matrix;                  // Pointer to the memory location where the actual matrix array is located
		bool flag = 1;              // Whether matrix needs to be deleted by the destructor or not (determied by which constructor is being used)
		int iterator = 0;           // Iterates throught the matrix. Resets once it reaches the length of the matrix
	
	public:
		T get(int, int) const;      // Gets a value from the matrix from a position relative to the rows and columns
		T get(int) const;      		// Gets a value from the matrix from a position relative to the length of the matrix (rows x columns)
		void set(int, int, T);      // Sets a value in the matrix at a specific location relative to rows and columns
		void set(int, T);      	    // Sets a value in the matrix at a specific location relative to the total length (rows x columns)
		int getRows() const;     	// Returns the number of rows
		int getColumns() const;  	// Returns the number of column
		int getLength() const;   	// Returns the total length of the matrix (rows x columns)
		template<typename U>
		MATRIX<T> operator+(MATRIX<U>&) const;   // Add matrices together
		MATRIX(int, int);        	// Constructor (takes in length and width of matrix)
		MATRIX(int, int, T*);       //
		~MATRIX();               	// Destructor (frees the memory)
};

// =========== Matrix Class =================

// Matic Constructor ====
template<typename T>
MATRIX<T>::MATRIX(int rows, int columns) : 
	rows(rows), 
	columns(columns),
	length(rows*columns)
{ this->matrix = new T[length]; }

template<typename T>
MATRIX<T>::MATRIX(int rows, int columns, T* matrixPointer) :
	rows(rows), 
	columns(columns),
	length(rows*columns),
	matrix(matrixPointer),
	flag(0)
{}

// Matrix Destrctor ======
template<typename T>
MATRIX<T>::~MATRIX(){
	if(flag){
    	delete[] matrix;
	}
}

// Get =====
template<typename T>
T MATRIX<T>::get(int i, int j) const{
    return matrix[(columns*i)+j];
}

// Get =====
template<typename T>
T MATRIX<T>::get(int i) const{
    return matrix[i];
}

// Set =====
template<typename T>
void MATRIX<T>::set(int i, int j, T val) {
    matrix[(columns*i)+j] = val;
}

// Set ====
template<typename T>
void MATRIX<T>::set(int i, T val) {
    matrix[i] = val;
}

// Get Rows ======
template<typename T>
int MATRIX<T>::getRows() const{ return rows; }

// Get Columns ========
template<typename T>
int MATRIX<T>::getColumns() const{ return columns; }

// Get Length ========
template<typename T>
int MATRIX<T>::getLength() const{ return length; }

// Operator+ =========

template<typename T>
template<typename U>
MATRIX<T> MATRIX<T>::operator+(MATRIX<U>& m) const {      // Argument needs to be a reference, or else local copy will affect the input matrix
    MATRIX<T> mat(rows, columns);
    for(int i = 0; i < getLength(); i++){
        mat.set(i, (((T)m.get(i)) + this->get(i)));
    }
    return mat;
}