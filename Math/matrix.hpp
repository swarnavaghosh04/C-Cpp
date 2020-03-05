
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

typedef const unsigned int& m_index;

namespace math{

    class DimensionException : public std::exception{
        public:
            const char* what() const throw(){
                return "The dimensions of the matrices are not compatible with the specified operation";
            }
    };

    class AccessViolationException : public std::exception{
        public:
            const char* what() const throw(){
                return "The index that is trying to be read or written to is invalid";
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
        public:
            MATRIX(m_index = 0, m_index = 0);          // Constructor (takes in length and width of matrix)
            MATRIX(m_index, m_index, const T* const);  // Constructor (takes in length, width, and a pointer to an already allocated space of memory. Could be used to create constant matrices)
            MATRIX(const MATRIX<T>&);                        // Copy Constructor (allocates new memory and copies matrix)
            ~MATRIX();               	                     // Destructor (frees the memory)
            // Getters ---------------
            int getRows() const;     	        // Returns the number of rows
            int getColumns() const;  	        // Returns the number of column
            int getLength() const;   	        // Returns the total length of the matrix (rows x columns)
            const T* getMatrix() const;         // Returns the location of the matrix
            // Assignment Operators ---------
            T* operator[](m_index) const;              // Access matrix content
            T& operator()(m_index, m_index) const;     // Access matrix content (safer)
            TYPE_U void operator=(const MATRIX<U>&);             // Assignment operator 
            TYPE_U void operator=(const MATRIX<U>&&);            // Move operator
            TYPE_U MATRIX<T>& operator+=(const MATRIX<U>&);      // Add matrix to self
            TYPE_U MATRIX<T>& operator-=(const MATRIX<U>&);      // Subtract matrix from self
            TYPE_U MATRIX<T>& operator*=(const MATRIX<U>&);      // Multiply matrix to self
            TYPE_U MATRIX<T>& operator*=(const U&);              // Multiply scalar to self
            TYPE_U MATRIX<T>& operator/=(const U&);              // Divide scalar to self
            // Arithmatic Operators ---------
            TYPE_AB friend MATRIX<A> operator+(const MATRIX<A>&, const MATRIX<B>&);    // Add matrices
            TYPE_AB friend MATRIX<A> operator-(const MATRIX<A>&, const MATRIX<B>&);    // Subtract matrices
            TYPE_AB friend MATRIX<A> operator*(const MATRIX<A>&, const MATRIX<B>&);    // Multiply matrices
            TYPE_AB friend MATRIX<A> operator*(const MATRIX<B>&, const A&);            // Scalar Multipliers
            TYPE_AB friend MATRIX<A> operator*(const A&, const MATRIX<B>&);
            TYPE_AB friend MATRIX<A> operator/(const MATRIX<B>&, const A&);            // Scalar Divisors
            TYPE_AB friend MATRIX<A> operator/(const A&, const MATRIX<B>&);
            // Comparison Operators ---------
            TYPE_AB friend bool operator==(const MATRIX<A>&, const MATRIX<B>&);        // Equals
            TYPE_AB friend bool operator!=(const MATRIX<A>&, const MATRIX<B>&);        // Not Equals
            // Arithmatic functions ----------
            T& transposed(m_index row) const;
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
    MATRIX<T>::MATRIX(m_index rows, m_index columns) : 
        rows(rows), 
        columns(columns),
        length(rows*columns)
    { matrix = new T[length]; std::cout << "CONSTRUCT" << std::endl; }

    /* Matrix Constructor (rows, columns, pointer to 1D heap allocated memory)
    This constructor not only takes in the dimensions of the matrix, but also
    takes in the address of a previously allocated block of memory of the
    specified size. This could be used to make constant matrices. */
    TYPE_T
    MATRIX<T>::MATRIX(m_index rows, m_index columns, const T* const matrixPointer) :
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

    // Assignment Operators ===================================

    /* Operator[] (unsafe)
    The goal of this funtion:
    be able to call m[i][j], where 'm'
    is an obejct of this class, to access
    the value at row 'i' and column 'j' of 'm'.
    However, this is not as safe as the next
    function as this can access memeory that
    is beyond the range of allocated memory*/
    TYPE_T
    T* MATRIX<T>::operator[](m_index row) const{
        return matrix + (row*columns);
    }

    /* Operator ()    (safe)
    This the safer version of the previous function.
    It allows the user to access row 'i' and column
    'j' of a MATRIX object 'm' via this notation: 
    m(i, j)
    If 'i' and 'j' are not valid, then this function
    throws an instance of 'AccessViolationException' */
    TYPE_T
    T& MATRIX<T>::operator()(m_index i, m_index j) const{
        if(i >= rows || j >= columns) throw AccessViolationException();
        return matrix[i*columns + j];
    }

    /* Operator= (assign)
    Performs deep copy of entire matrix*/
    TYPE_T TYPE_U
    void MATRIX<T>::operator=(const MATRIX<U>& mat){
        std::cout << "ASSIGN" << std::endl;
        /* If the two matrices do not have the
        same dimensions, deallocate this matrix,
        and allocate a new chunck of memory of
        appropriate length.*/
        if(rows != mat.rows || columns != mat.columns){
            rows = mat.rows;
            columns = mat.columns;
            length = mat.length;
            delete[] matrix;
            matrix = new T[length];
        }
        // Copy over the matrix
        for(int i = 0; i < length; i++) matrix[i] = (T)mat.matrix[i];
    }

    /* Operator= (move)
    The move operator does not perform a deep copy.
    It only exchanges the pointer values. In the case
    that the dimensions are not the same, the members: 
    rows, columns and length are updated. In the case
    that the two objects are not of the same template
    type, then the entire thing is ran through a
    re-casting loop */
    TYPE_T TYPE_U void MATRIX<T>::operator=(const MATRIX<U>&& mat){
        std::cout << "MOVE" << std::endl;
        if(rows != mat.rows || columns != mat.columns){         // update dimension specifying member sif necessary
            rows = mat.rows;
            columns = mat.columns;
            length = mat.length;
        }
        /*since mat is going to get destroyed after the function
        terminates, the matrix is going to get deallocated.
        To prevent this, mat.canDelete is set to false as we are
        going to assign the mat's matrix to this matrix */
        mat.canDelete = false;
        delete[] matrix;                 // Deallocate this matrix
        matrix = (T*)mat.matrix;         // Assign mat's matrix to this matrix
        if(!std::is_same<T, U>::value)   // Reinterpret the casts if mat and this to not have the same template args
            for(int i = 0; i < length; i++) matrix[i] = (T)matrix[i];
    }

    /* Operator+=
    Straight forward addition of matrices.
    Throws 'DimensionException' if matrices don't
    match in terms of size */
    TYPE_T TYPE_U
    MATRIX<T>& MATRIX<T>::operator+=(const MATRIX<U>& mat){
        if(rows != mat.rows || columns != mat.columns){
            throw DimensionException();
        }
        for(int i = 0; i < length; i++) matrix[i] += (T)mat.matrix[i];
        return (*this);
    }

    /* Operator-=
    Straight forward subtraction of matrices.
    Throws 'DimensionException' if matrices don't
    match in terms of size */
    TYPE_T TYPE_U
    MATRIX<T>& MATRIX<T>::operator-=(const MATRIX<U>& mat){
        if(rows != mat.rows || columns != mat.columns){
            throw DimensionException();
        }
        for(int i = 0; i < length; i++) matrix[i] -= (T)mat.matrix[i];
        retrun (*this);
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

    TYPE_T TYPE_U MATRIX<T>& MATRIX<T>::operator*=(const U& c){
        for(int i = 0; i < length; i++) matrix[i] *= (T)c;
        return (*this);
    }

    TYPE_T TYPE_U MATRIX<T>& MATRIX<T>::operator/=(const U& c){
        for(int i = 0; i < length; i++) matrix[i] /= (T)c;
        return (*this);
    }

    // Arithmatic Operators =================

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

    /* Scalar Multiplier
    Allows that matrix to be scaled up or down
    by a factor. This operator is commutative*/
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

    /* Scalar Divisor
    Allows that matrix to be scaled up or down
    by some factor. This operator is non-commutative*/
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

    /* Fill matrix - overload 1
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

    /* Fill matrix - overload 2
    This is the second overloaded function of the previous
    one. It just fill the entire matrix with a constant value
    specified by the argument. */
    TYPE_T
    void MATRIX<T>::fill(const T& val){
        for(int i = 0; i < length; i++) matrix[i] = val;
    }

    
}

#endif