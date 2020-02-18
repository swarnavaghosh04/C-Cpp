#pragma once

template<typename T>
class MATRIX{
	
	private:
		int rows;
		int columns;
		mutable T* matrix;
	
	public:
		T get(int, int) const;      // Gets a value from the matrix
		T get(int) const;      		// Gets a value from the matrix
		void set(int, int, T) const;      // Sets a value in the matrix
		void set(int, T) const;      		// Sets a value in the matrix
		int getRows() const;     	// Returns the number of rows
		int getColumns() const;  	// Returns the number of column
		int getLength() const;   	// Retruns the total length of the matrix (rows x columns)
		template<typename U>
		MATRIX<T> operator+(MATRIX<U>) const;   // Add matrices together
		MATRIX(int, int);        	// Constructor (takes in length and width of matrix)
		~MATRIX();               	// Destructor (frees the memory)
};