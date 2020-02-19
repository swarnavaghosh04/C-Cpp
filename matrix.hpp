#pragma once
#include <stdlib.h>

template<typename T>
class MATRIX{
	
	private:
		int rows;
		int columns;
		int length;
		mutable int iterCounter = 0;
		mutable T* matrix;
	
	public:
		T get(int, int) const;      // Gets a value from the matrix from a position relative to the rows and columns
		T get(int) const;      		// Gets a value from the matrix from a position relative to the length of the matrix (rows x columns)
		T get() const;              // Gets value from the matrix from the poisition specified by the iterator
		T iterate() const;          // iterates to the function and resets after reaching the ends
		void set(int, int, T) const;      // Sets a value in the matrix at a specific location relative to rows and columns
		void set(int, T) const;      	  // Sets a value in the matrix at a specific location relative to the total length (rows x columns)
		void set(T) const;                // Sets a value in the matrix at a specific location relative to the iterator
		int getRows() const;     	// Returns the number of rows
		int getColumns() const;  	// Returns the number of column
		int getLength() const;   	// Retruns the total length of the matrix (rows x columns)
		template<typename U>
		MATRIX<T> operator+(MATRIX<U>) const;   // Add matrices together
		MATRIX(int, int);        	// Constructor (takes in length and width of matrix)
		~MATRIX();               	// Destructor (frees the memory)
};

// =========== Matrix Class =================

// Matic Constructor ====
template<typename T>
MATRIX<T>::MATRIX(int rows, int columns) : rows(rows), columns(columns){
    int size = sizeof(T);
	length = rows*columns;
    this->matrix = (T*)calloc(rows*columns, size);
}

// Matrix Destrctor ======
template<typename T>
MATRIX<T>::~MATRIX(){
    free(matrix);
}

// Get =====
template<typename T>
T MATRIX<T>::get(int i, int j) const{
    matrix += (columns*i + j);
    T val = *matrix;
    matrix -= (columns*i + j);
    return val;
}

// Get =====
template<typename T>
T MATRIX<T>::get(int i) const{
    matrix += i;
    T val = *matrix;
    matrix -= i;
    return val;
}

// Get =======
template<typename T>
T MATRIX<T>::get()const{return *matrix;}

// ===================== FIX THIS! =====================

// Iterate ======
template <typename T>
T MATRIX<T>::iterate() const{
	T num = *matrix;
	iterCounter++;
	matrix++;
	if(iterCounter == length){
		matrix -= iterCounter;
		iterCounter = 0;
		return num;
	}
	return num;
}

// ======================================================

// Set =====
template<typename T>
void MATRIX<T>::set(int i, int j, T val) const{
    matrix += (columns*i + j - iterCounter);
    *matrix = val;
    matrix -= (columns*i + j - iterCounter);
}

// Set ====
template<typename T>
void MATRIX<T>::set(int i, T val) const{
    matrix += i;
    *matrix = val;
    matrix -= i;
}

// Set ====
template<typename T>
void MATRIX<T>::set(T val) const{*matrix = val;}

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
MATRIX<T> MATRIX<T>::operator+(MATRIX<U> m) const {
    MATRIX<T> mat(rows, columns);
    for(int i = 0; i < this->getLength(); i++){
        mat.set(i, ((T)(m.iterate()) + this->iterate()));
    }
    return mat;
}