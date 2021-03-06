
/*
================== C++ Matrix Library ==================
================== By Swarnava Ghosh ===================
*/

#ifndef LIB_MATRIX_HPP
#define LIB_MATRIX_HPP

#include <iostream>
#include <exception>

#define FUNCTION_TYPE template<typename Function>

typedef const unsigned int& m_index;

namespace math{

    class DimensionException : public std::exception{
        public:
            const char* what() const throw();
    };

    class AccessViolationException : public std::exception{
        public:
            const char* what() const throw();
    };

    class MatrixInitializationSizeError : public std::exception{
        public:
            const char* what() const throw();
    };

    class MatrixInitializationDimensionError : public std::exception{
        public:
            const char* what() const throw();
    };

    class MatrixInverseComputationError : public std::exception{
        public:
            const char* what() const throw();
    };
    
    class MATRIX{
        private:
            unsigned int rows;                                  // Number of rows in the matrix
            unsigned int columns;                               // Number of columns in the matrix
            unsigned int length;                                // Number of rows x number of columns = total length of the matrix
            double* matrix;                                     // Pointer to the memory location where the actual matrix array is located
            mutable bool canDelete = true;                      // Specfies whether or not the matrix should be deallocated on destruction (this variable is only modified in the move constructor; it should always stay as true otherwise)
            double det_rec(const MATRIX&) const;                // The recursion function for finding determinent
        public:
            MATRIX(m_index = 0, m_index = 0);                   // Constructor (takes in length and width of matrix)
            MATRIX(m_index, m_index, const double* const);      // Constructor (takes in length, width, and a pointer to an already allocated space of memory. Could be used to create constant matrices)
            MATRIX(const MATRIX&);                              // Copy Constructor (allocates new memory and copies matrix)
            ~MATRIX();               	                        // Destructor (frees the memory)
            // Getters ---------------
            unsigned int getRows() const;     	                // Returns the number of rows
            unsigned int getColumns() const;  	                // Returns the number of column
            unsigned int getLength() const;   	                // Returns the total length of the matrix (rows x columns)
            bool getCanDelete() const;
            const double* const getMatrix() const;              // Returns the location of the matrix
            int getTransposedRows() const;
            int getTransposedColumns() const;
            // Assignment Operators ---------
            double* operator[](m_index) const;              // Access matrix content
            double& operator()(m_index, m_index) const;     // Access matrix content (safer)
            void operator=(const MATRIX&);                  // Assignment operator 
            void operator=(const MATRIX&&);                 // Move operator
            MATRIX& operator+=(const MATRIX&);              // Add matrix to self
            MATRIX& operator-=(const MATRIX&);              // Subtract matrix from self
            MATRIX& operator*=(const double&);              // Multiply scalar to self
            MATRIX& operator/=(const double&);              // Divide scalar to self
            // Arithmatic Operators ---------
            friend MATRIX operator+(const MATRIX&, const MATRIX&);    // Add matrices
            friend MATRIX operator-(const MATRIX&, const MATRIX&);    // Subtract matrices
            friend MATRIX operator*(const MATRIX&, const MATRIX&);    // Multiply matrices
            friend MATRIX operator*(const MATRIX&, const double&);    // Scalar Multipliers
            friend MATRIX operator*(const double&, const MATRIX&);
            friend MATRIX operator/(const MATRIX& m, const double&);  // Scalar Divisors
            friend MATRIX operator/(const double&, const MATRIX&);
            // Comparison Operators ---------
            friend bool operator==(const MATRIX&, const MATRIX&);     // Equals
            friend bool operator!=(const MATRIX&, const MATRIX&);     // Not Equals
            // Arithmatic functions ----------
            double& transposed(m_index, m_index) const;   // Pseudo Transpose
            double& _transposed(m_index, m_index) const;  // Pseudo Tranpose Without Bounds Checking
            MATRIX transpose() const;                     // Returns new transposed matrix
            double determinant() const;                   // Returns determinent of matrix
            FUNCTION_TYPE void rowop(m_index, m_index, Function);
            FUNCTION_TYPE void colop(m_index, m_index, Function);
            MATRIX ref() const;                                        // Returns new matrix in row-echelon form
            MATRIX rref(MATRIX* = nullptr, bool = false) const;        // Returns new matrix in reduced-row-echelon form
            MATRIX inverse() const;                                    // Returns the inverse of the matrix
            // Other functions ------------
            FUNCTION_TYPE void fill(Function);                // Fills The matrix with a pattern based off of position
            void fill(const double&);                         // Fill the entire matrix with a single value
            static MATRIX identity(m_index, m_index=0);
    };
    
    MATRIX operator+(const MATRIX&, const MATRIX&);    // Add matrices
    MATRIX operator-(const MATRIX&, const MATRIX&);    // Subtract matrices
    MATRIX operator*(const MATRIX&, const MATRIX&);    // Multiply matrices
    MATRIX operator*(const MATRIX&, const double&);    // Scalar Multipliers
    MATRIX operator*(const double&, const MATRIX&);
    MATRIX operator/(const MATRIX& m, const double&);  // Scalar Divisors
    MATRIX operator/(const double&, const MATRIX&);
    bool operator==(const MATRIX&, const MATRIX&);     // Equals
    bool operator!=(const MATRIX&, const MATRIX&);     // Not Equals

}

// Template Functions ============================

FUNCTION_TYPE
void math::MATRIX::rowop(m_index row1, m_index row2, Function func){
    if(row1 >= rows || row2 >= rows) throw AccessViolationException();
    for(int i = 0; i < columns; i++)
        func((*this)[row1][i],(*this)[row2][i]);
}

FUNCTION_TYPE
void math::MATRIX::colop(m_index col1, m_index col2, Function func){
    if(col1 >= columns || col2 >= columns) throw AccessViolationException();
    for(int i = 0; i < rows; i++)
        func((*this)[i][col1],(*this)[i][col2]);
}

/* Fill matrix - overload 1
This is one of two overloaded functions that help
fill the matrix. This particular function has a
function pointer as its argument. This function
pointed to by the argument should have two
arguments of type m_index (const int&) and return
a value of type T. essentially what this
function does, to summuerize in one equation:
matrix[i][j] = func(i, j) where func is the argument. */
FUNCTION_TYPE
void math::MATRIX::fill(Function func){
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
            (*this)[i][j] = func(i, j);
}

#endif