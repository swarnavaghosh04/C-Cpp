
/*
================== C++ Matrix Library ==================
================== By Swarnava Ghosh ===================
*/

#ifndef LIB_MATRIX_H
#define LIB_MATRIX_H

#include <iostream>
#include <exception>

#define TYPE_T template<typename T>
#define TYPE_U template<typename U>
#define TYPE_AB template<typename A, typename B>

typedef const int& m_index;      // Useful for 'fill' function call

namespace math{

    class DimensionException : public std::exception{
        public:
            const char* what() const throw(){
                return "The dimensions of the matrices are not compatible with the specified operation";
            }
    };

    class AccessException : public std::exception{
        public:
            const char* what() const throw(){
                return "The location in the matrix trying to be accessed is not valid";
            }
    };

    TYPE_T
    class MATRIX final{                      // Template class; Cannot be inherited from
        private:
            int rows;                        // Number of rows in the matrix
            int columns;                     // Number of columns in the matrix
            int length;                      // Number of rows x number of columns = total length of the matrix
            T* matrix;                       // Pointer to the memory location where the actual matrix array is located
            mutable bool canDelete = true;   // Specfies whether or not the matrix should be deallocated on destruction (this variable is only modified in the move constructor; it should always stay as true otherwise)
            typedef T (*FillFunction)(m_index, m_index);     // Used as argument type for 'fill' function
            struct ColumnVal{
                private:
                    T* location;
                public:
                T operator[](int column){
                    return matrix[location + column];
                };
            };
        public:
            MATRIX(const int& = 0, const int& = 0);          // Constructor (takes in length and width of matrix)
            MATRIX(const int&, const int&, const T* const);  // Constructor (takes in length, width, and a pointer to an already allocated space of memory. Could be used to create constant matrices)
            MATRIX(const MATRIX<T>&);                        // Copy Constructor (allocates new memory and copies matrix)
            ~MATRIX();               	                     // Destructor (frees the memory)
            // Getters ---------------
            int getRows() const;     	        // Returns the number of rows
            int getColumns() const;  	        // Returns the number of column
            int getLength() const;   	        // Returns the total length of the matrix (rows x columns)
            const T* getMatrix() const;         // Returns the location of the matrix
            // Arithmatic Operators ---------
            T* operator[](unsigned int i) const;                                       // Access numbers in the matrix
            TYPE_U void operator=(const MATRIX<U>&);                                   // Assignment operator 
            TYPE_U void operator=(const MATRIX<U>&&);                                  // Move operator
            TYPE_AB friend MATRIX<A> operator+(const MATRIX<A>&, const MATRIX<B>&);    // Add matrices
            TYPE_U MATRIX<T>& operator+=(const MATRIX<U>&);                            // Add matrix to this one
            TYPE_AB friend MATRIX<A> operator-(const MATRIX<A>&, const MATRIX<B>&);    // Subtract matrices
            TYPE_U MATRIX<T>& operator-=(const MATRIX<U>&);                            // Subtract matrix from this one
            TYPE_AB friend MATRIX<A> operator*(const MATRIX<A>&, const MATRIX<B>&);    // Multiply matrices
            TYPE_U MATRIX<T>& operator*=(const MATRIX<U>&);                            // Multiply matrix to this one
            TYPE_AB friend MATRIX<A> operator*(const MATRIX<B>&, const A&);            // Scalar Multipliers
            TYPE_AB friend MATRIX<A> operator*(const A&, const MATRIX<B>&);
            TYPE_U MATRIX<T>& operator*=(const U&);                                    // Multiply scalar to this one
            TYPE_AB friend MATRIX<A> operator/(const MATRIX<B>&, const A&);            // Scalar Divisors
            TYPE_AB friend MATRIX<A> operator/(const A&, const MATRIX<B>&);
            TYPE_U MATRIX<T>& operator/=(const U&);                                    // Divide scalar to this one
            // Comparison Operators ---------
            TYPE_AB friend bool operator==(const MATRIX<A>&, const MATRIX<B>&);        // Equals
            TYPE_AB friend bool operator!=(const MATRIX<A>&, const MATRIX<B>&);        // Not Equals
            // Other functions ------------
            void fill(FillFunction);            // Fills The matrix with a pattern based off of position
            void fill(const T&);                // Fill the entire matrix with a single value
    };

    // =========== Matrix Class =================

    /* Matix Constructor (rows, columns):
    This constructor is very simple. It just takes
    in the dimensions of the matrix and dynamically
    allocates that much space. */
    TYPE_T
    MATRIX<T>::MATRIX(const int& rows, const int& columns) : 
        rows(rows), 
        columns(columns),
        length(rows*columns)
    { matrix = new T[length]; std::cout << "CONSTRUCT" << std::endl; }

    /* Matrix Constructor (rows, columns, pointer to 1D heap allocated memory)
    This constructor not only takes in the dimensions of the matrix, but also
    takes in the address of a previously allocated block of memory of the
    specified size. This could be used to make constant matrices. */
    TYPE_T
    MATRIX<T>::MATRIX(const int& rows, const int& columns, const T* const matrixPointer) :
        rows(rows), 
        columns(columns),
        length(rows*columns),
        matrix(matrixPointer)
    { std::cout << "CONSTRUCT" << std::endl; }

    /* Copy Constructor (allocates new memory and copies matrix; performs deep copy)
    The copy constructor invokes a deep copy. it creates a new matrix by copying
    all the content of the other matrix and writing them into a new block of memory. */
    TYPE_T
    MATRIX<T>::MATRIX(const MATRIX<T>& mat) : 
        rows(mat.rows),
        columns(mat.columns),
        length(mat.length)
    {
        std::cout << "COPY" << std::endl;
        matrix = new T[length];
        for(int i = 0; i < length; i++) matrix[i] = mat.matrix[i];
    }

    /* Matrix Destrctor
    A very simple dtor that frees the memory pointed
    to by the 'matrix' variable. However, There are 
    situations where this should not be done. therefore,
    a protection vairable 'canDelete' is there to
    regulate that (See move operator for more details). */
    TYPE_T
    MATRIX<T>::~MATRIX(){
        if(canDelete) { 
            delete[] matrix;
            std::cout << "DESTROYED" <<std::endl;
        }
    }

    TYPE_T
    T MATRIX<T>::ColumnVal::operator[](int column){
        return matrix[location + column];
    };

    // Getters =======================================

    // Get Rows
    TYPE_T
    int MATRIX<T>::getRows() const{ return rows; }

    // Get Columns
    TYPE_T
    int MATRIX<T>::getColumns() const{ return columns; }

    // Get Length
    TYPE_T
    int MATRIX<T>::getLength() const{ return length; }

    // Get Matrix
    TYPE_T
    const T* MATRIX<T>::getMatrix() const{ return matrix; }

    // Arithmatic Operators ===================================

    // Operator[]
    TYPE_T
    T* MATRIX<T>::operator[](unsigned int i) const{ return (T*)&(matrix[i*columns]); }

    // Operator= (assign)
    TYPE_T TYPE_U void MATRIX<T>::operator=(const MATRIX<U>& mat){
        std::cout << "ASSIGN" << std::endl;
        if(rows != mat.rows || columns != mat.columns){
            rows = mat.rows;
            columns = mat.columns;
            length = mat.length;
            delete[] matrix;
            matrix = new T[length];
        }
        for(int i = 0; i < length; i++) matrix[i] = (T)mat.matrix[i];
    }

    // Operator= (move)
    TYPE_T TYPE_U void MATRIX<T>::operator=(const MATRIX<U>&& mat){
        std::cout << "MOVE" << std::endl;
        if(rows != mat.rows || columns != mat.columns){
            rows = mat.rows;
            columns = mat.columns;
            length = mat.length;
        }
        mat.canDelete = false;
        delete[] matrix;
        matrix = mat.matrix;
        if(!std::is_same<T, U>::value)
            for(int i = 0; i < length; i++) matrix[i] = (T)matrix[i];
    }

    // Operator+
    TYPE_AB
    MATRIX<A> operator+(const MATRIX<A>& m1, const MATRIX<B>& m2) {      // Argument needs to be a reference, or else local copy will affect the input matrix
        
        // Error checking (dimension need to be the same)
        if(m1.rows != m2.rows || m1.columns != m2.columns)
            throw DimensionException();

        // Create new matrix
        MATRIX<A> mat(m1.rows, m1.columns);
        
        // copy the added values to this new matrix
        for(int i = 0; i < m1.length; i++){
            mat.matrix[i] = m1.matrix[i] + (A)m2.matrix[i];
        }
        return mat;
    }

    // Operator+=
    TYPE_T TYPE_U
    MATRIX<T>& MATRIX<T>::operator+=(const MATRIX<U>& mat){
        if(rows != mat.rows || columns != mat.columns){
            throw DimensionException();
        }
        for(int i = 0; i < length; i++) matrix[i] += (T)mat.matrix[i];
        return (*this);
    }

    // Operator-
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

    // Operator-=
    TYPE_T TYPE_U
    MATRIX<T>& MATRIX<T>::operator-=(const MATRIX<U>& mat){
        if(rows != mat.rows || columns != mat.columns){
            throw DimensionException();
        }
        for(int i = 0; i < length; i++) matrix[i] -= (T)mat.matrix[i];
        retrun (*this);
    }

    // Operator*
    TYPE_AB
    MATRIX<A> operator*(const MATRIX<A>& m1 , const MATRIX<B>& m2) {

        if(m1.columns != m2.rows) throw DimensionException();
        
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

    // Operator*=
    TYPE_T TYPE_U MATRIX<T>& MATRIX<T>::operator*=(const MATRIX<U>& mat){

        if(mat.rows != columns) throw DimensionException();

        MATRIX<T> mat2 = (*this)*mat;
        rows = mat2.rows;
        columns = mat2.columns;
        mat2.canDelete = false;
        delete[] matrix;
        matrix = mat2.matrix;
        return (*this);
    }

    // Scalar Multiplier
    TYPE_AB
    MATRIX<A> operator*(const MATRIX<B>& m, const A& c){
        MATRIX<A> mat(m.rows, m.columns);
        for(int i = 0; i < m.length; i++) mat.matrix[i] = (A)m.matrix[i] * c;
        return mat;
    }

    TYPE_AB
    MATRIX<A> operator*(const A& c, const MATRIX<B>& m){
        MATRIX<A> mat(m.rows, m.columns);
        for(int i = 0; i < m.length; i++) mat.matrix[i] = (A)m.matrix[i] * c;
        return mat;
    }

    TYPE_T TYPE_U MATRIX<T>& MATRIX<T>::operator*=(const U& c){
        for(int i = 0; i < length; i++) matrix[i] *= (T)c;
        return (*this);
    }

    // Scalar Divisor
    TYPE_AB
    MATRIX<A> operator/(const MATRIX<B>& m, const A& c){
        MATRIX<A> mat(m.rows, m.columns);
        for(int i = 0; i < m.length; i++) mat.matrix[i] = (A)m.matrix[i] / c;
        return mat;
    }

    TYPE_AB
    MATRIX<A> operator/(const A& c, const MATRIX<B>& m){
        MATRIX<A> mat(m.rows, m.columns);
        for(int i = 0; i < m.length; i++) mat.matrix[i] = c / (A)m.matrix[i];
        return mat;
    }

    TYPE_T TYPE_U MATRIX<T>& MATRIX<T>::operator/=(const U& c){
        for(int i = 0; i < length; i++) matrix[i] /= (T)c;
        return (*this);
    }

    // Comparison operators ======================

    // Equals
    TYPE_AB bool operator==(const MATRIX<A>& matA, const MATRIX<B>& matB){
        if(matA.rows != matB.rows || matA.columns != matB.columns) return false;
        for(int i = 0; i < matA.length; i++)
            if(matA.matrix[i] != (A)matB.matrix[i]) return false;
        return true;
    }

    // Not Equals
    TYPE_AB bool operator!=(const MATRIX<A>& matA, const MATRIX<B>& matB){
        return !(matA==matB);
    }

    // Other functions ===================================

    /* Fill matrix
    This is one of two overloaded functions that help
    fill the matrix. This particular function has a
    function pointer as its argument. This function
    pointed to by the argument should have two
    arguments of type m_index (const int&) and return
    a value of type T. essentially what this
    function does, to summuerize in one equation:
    matrix[i][j] = func(i, j) where func is the argument. */
    TYPE_T
    void MATRIX<T>::fill(FillFunction func){
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < columns; j++)
                (*this)[i][j] = func(i, j);
    }

    /* Fill matrix
    This is the second overloaded function of the previous
    one. It just fill the entire matrix with a constant value
    specified by the argument. */
    TYPE_T
    void MATRIX<T>::fill(const T& val){
        for(int i = 0; i < length; i++) matrix[i] = val;
    }

    
}

#endif