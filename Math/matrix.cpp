#include ".\\matrix.hpp"

const char* math::DimensionException::what() const throw(){
    return "The dimensions of the matrices are not compatible with the specified operation";;
}

const char* math::AccessViolationException::what() const throw(){
    return "The index that is trying to be read or written to is invalid";
}

const char* math::MatrixInitializationSizeError::what() const throw(){
    return "The matrix trying to be initalized is too big";
}

const char* math::MatrixInitializationDimensionError::what() const throw(){
    return "The matrix trying to be initalized is invalid due to incompatible row and column dimensions";
}

// =========== Matrix Class =================

/* Matix Constructor (rows, columns):
This constructor is very simple. It just takes
in the dimensions of the matrix and dynamically
allocates that much space. */
math::MATRIX::MATRIX(m_index rows, m_index columns) : 
    rows(rows), 
    columns(columns),
    length(rows*columns)
{ matrix = new double[length]; } /*std::cout << "CONSTRUCT" << std::endl;*/

/* Matrix Constructor (rows, columns, pointer to 1D heap allocated memory)
This constructor not only takes in the dimensions of the matrix, but also
takes in the address of a previously allocated block of memory of the
specified size. This could be used to make constant matrices. */
math::MATRIX::MATRIX(m_index rows, m_index columns, const double* const matrixPointer) :
    rows(rows), 
    columns(columns),
    length(rows*columns),
    matrix((double*)matrixPointer),
    canDelete(false)
{ /*std::cout << "CONSTRUCT" << std::endl;*/ }

/* Copy Constructor (allocates new memory and copies matrix; performs deep copy)
The copy constructor invokes a deep copy. it creates a new matrix by copying
all the content of the other matrix and writing them into a new block of memory. */
math::MATRIX::MATRIX(const MATRIX& mat) : 
    rows(mat.rows),
    columns(mat.columns),
    length(mat.length)
{
    std::cout << "COPY" << std::endl;
    matrix = new double[length];
    for(int i = 0; i < length; i++) matrix[i] = mat.matrix[i];
}

/* Matrix Destructor
A very simple dtor that frees the memory pointed
to by the 'matrix' variable. However, There are 
situations where this should not be done. therefore,
a protection vairable 'canDelete' is there to
regulate that (See move operator for more details). */
math::MATRIX::~MATRIX(){
    if(canDelete) { 
        delete[] matrix;
        std::cout << "DESTROYED" <<std::endl;
    }
}

// Getters =======================================

// Get Rows

unsigned int math::MATRIX::getRows() const{ return rows; }

// Get Columns

unsigned int math::MATRIX::getColumns() const{ return columns; }

// Get Length

unsigned int math::MATRIX::getLength() const{ return length; }

// Get Matrix

const double* const math::MATRIX::getMatrix() const{ return matrix; }

int math::MATRIX::getTransposedRows() const{ return columns; }

int math::MATRIX::getTransposedColumns() const{ return rows; }

// Assignment Operators ===================================

/* Operator[] (unsafe)
The goal of this funtion:
be able to call m[i][j], where 'm'
is an obejct of this class, to access
the value at row 'i' and column 'j' of 'm'.
However, this is not as safe as the next
function as this can access memeory that
is beyond the range of allocated memory*/
double* math::MATRIX::operator[](m_index row) const{
    return (matrix + (row*columns));
}

/* Operator ()    (safe)
This the safer version of the previous function.
It allows the user to access row 'i' and column
'j' of a MATRIX object 'm' via this notation: 
m(i, j)
If 'i' and 'j' are not valid, then this function
throws an instance of 'AccessViolationException' */
double& math::MATRIX::operator()(m_index i, m_index j) const{
    if(i >= rows || j >= columns) throw AccessViolationException();
    return matrix[i*columns + j];
}

/* Operator= (assign)
Performs deep copy of entire matrix*/
void math::MATRIX::operator=(const MATRIX& mat){
    //std::cout << "ASSIGN" << std::endl;
    /* If the two matrices do not have the
    same dimensions, deallocate this matrix,
    and allocate a new chunck of memory of
    appropriate length.*/
    if(rows != mat.rows || columns != mat.columns){
        rows = mat.rows;
        columns = mat.columns;
        length = mat.length;
        if(canDelete) delete[] matrix;
        matrix = new double[length];
    }
    // Copy over the matrix
    for(int i = 0; i < length; i++) matrix[i] = mat.matrix[i];
}

/* Operator= (move)
The move operator does not perform a deep copy.
It only exchanges the pointer values. In the case
that the dimensions are not the same, the members: 
rows, columns and length are updated. In the case
that the two objects are not of the same template
type, then the entire thing is ran through a
re-casting loop */
void math::MATRIX::operator=(const MATRIX&& mat){
    std::cout << "MOVE" << std::endl;
    rows = mat.rows;
    columns = mat.columns;
    length = mat.length;
    if(canDelete) delete[] matrix;   // Deallocate this matrix
    canDelete = mat.canDelete;       // Copy over delete flag
    /*since mat is going to get destroyed after the function
    terminates, the matrix is going to get deallocated.
    To prevent this, mat.canDelete is set to false as we are
    going to assign the mat's matrix to this matrix */
    mat.canDelete = false;
    matrix = mat.matrix;             // Assign mat's matrix to this matrix
}

/* Operator+=
Straight forward addition of matrices.
Throws 'DimensionException' if matrices don't
match in terms of size */
math::MATRIX& math::MATRIX::operator+=(const MATRIX& mat){
    if(rows != mat.rows || columns != mat.columns){
        throw DimensionException();
    }
    for(int i = 0; i < length; i++) matrix[i] += mat.matrix[i];
    return (*this);
}

/* Operator-=
Straight forward subtraction of matrices.
Throws 'DimensionException' if matrices don't
match in terms of size */
math::MATRIX& math::MATRIX::operator-=(const MATRIX& mat){
    if(rows != mat.rows || columns != mat.columns){
        throw DimensionException();
    }
    for(int i = 0; i < length; i++) matrix[i] -= mat.matrix[i];
    return (*this);
}

// Operator*=
math::MATRIX& math::MATRIX::operator*=(const double& c){
    for(int i = 0; i < length; i++) matrix[i] *= c;
    return (*this);
}

math::MATRIX& math::MATRIX::operator/=(const double& c){
    for(int i = 0; i < length; i++) matrix[i] /= c;
    return (*this);
}

// Arithmatic Operators =================

// Operator+
math::MATRIX math::operator+(const MATRIX& m1, const MATRIX& m2) {
    
    // Error checking (dimension need to be the same)
    if(m1.rows != m2.rows || m1.columns != m2.columns)
        throw DimensionException();

    // Create new matrix
    math::MATRIX mat(m1.rows, m1.columns);
    
    // copy the added values to this new matrix
    for(int i = 0; i < m1.length; i++){
        mat.matrix[i] = m1.matrix[i] + m2.matrix[i];
    }
    return mat;
}

// Operator-
math::MATRIX math::operator-(const MATRIX& m1 , const MATRIX& m2) {
    if(m1.rows != m2.rows || m1.columns != m2.columns){
        throw DimensionException();
    }
    math::MATRIX mat(m1.rows, m1.columns);
    for(int i = 0; i < m1.length; i++){
        mat.matrix[i] = m1.matrix[i] - m2.matrix[i];
    }
    return mat;
}

// Operator*
math::MATRIX math::operator*(const MATRIX& m1 , const MATRIX& m2) {

    if(m1.columns != m2.rows) throw math::DimensionException();
    
    math::MATRIX mat(m1.rows, m2.columns);
    double temp = 0;
    for(int i = 0; i < m1.rows; i++){
        for(int j = 0; j < m2.columns; j++){
            for(int k = 0; k < m1.columns; k++){
                temp += m1[i][k]  *  (m2[k][j]);
            }
            mat[i][j] =  temp;
            temp = 0.;
        }
    }
    return mat;
}

/* Scalar Multiplier
Allows that matrix to be scaled up or down
by a factor. This operator is commutative*/
math::MATRIX math::operator*(const MATRIX& m, const double& c){
    math::MATRIX mat(m.rows, m.columns);
    for(int i = 0; i < m.length; i++) mat.matrix[i] = m.matrix[i] * c;
    return mat;
}

math::MATRIX math::operator*(const double& c, const MATRIX& m){
    MATRIX mat(m.rows, m.columns);
    for(int i = 0; i < m.length; i++) mat.matrix[i] = m.matrix[i] * c;
    return mat;
}

/* Scalar Divisor
Allows that matrix to be divided by some factor.
This operator is non-commutative */
math::MATRIX math::operator/(const MATRIX& m, const double& c){
    MATRIX mat(m.rows, m.columns);
    for(int i = 0; i < m.length; i++) mat.matrix[i] = m.matrix[i] / c;
    return mat;
}

math::MATRIX math::operator/(const double& c, const MATRIX& m){
    MATRIX mat(m.rows, m.columns);
    for(int i = 0; i < m.length; i++) mat.matrix[i] = c / m.matrix[i];
    return mat;
}

// Comparison operators ======================

// Equals
bool math::operator==(const MATRIX& matA, const MATRIX& matB){
    if(matA.rows != matB.rows || matA.columns != matB.columns) return false;
    for(int i = 0; i < matA.length; i++)
        if(matA.matrix[i] != matB.matrix[i]) return false;
    return true;
}

// Not Equals
bool math::operator!=(const MATRIX& matA, const MATRIX& matB){
    return !(matA==matB);
}

// Arithmatic functions ============================

/* transposed
This function does not do any computations.
It just provides an 'illusion' of transposing
a matrix. It takes in the index of an element
that you want to access in the tranposed version
of the matrix and returns that value without
alterring the contents of the matrix. */
double& math::MATRIX::transposed(m_index i, m_index j) const{
    if(i >= columns || j >= rows) throw AccessViolationException();
    return matrix[j*columns + i];
}

/* transpose
This function figures out the transpose
of the matrix and returns another MATRIX
object which carries the tranpose. Note
that this does not change the contents
of the original matrix. */
math::MATRIX math::MATRIX::transpose() const{
    MATRIX mat(columns, rows);
    for(int i = 0; i < columns; i++)
        for(int j = 0; j < rows; j++)
            mat.matrix[i*rows+j] = matrix[j*columns+i];
    return mat;
}

/* det_rec
This is the actual function that computes
the determinent using recursion. Most of
the checking is skipped as this function
is only called by the memeber function
determinent(). Here is how it workd:
    > Check is 2x2
    > If yes, return 2x2 determinent
    > Else, initiate double det = 0;
    > Calculate the determinent for each cofactor
    > Add or Subtract that (depending on position) from det
    > return det
*/

extern void printMatrix(const math::MATRIX&, const char* m="");

double math::MATRIX::det_rec(const MATRIX& mat) const{
    if(mat.rows == 2) return ((mat[0][0]*mat[1][1]) - (mat[0][1]*mat[1][0]));
    MATRIX mat2(mat.rows-1, mat.columns-1);
    double det = 0;
    for(int i = 0; i < mat.columns; i++){
        for(int j = mat.columns, index = 0; j < mat.length; j++){
            if((j-i)%mat.columns != 0){
                mat2.matrix[index] = mat.matrix[j];
                index++;
            }
        }
        printf("%d", i);
        printMatrix(mat2);
        det += (i%2?-1:1)*mat[0][i]*det_rec(mat2);
    }
    return det;
}

/* determinent
This is a function for the user to compute
the determinent of the matrix. However, the
real calculation happens in the private
function det_rec(). All this function does
is to check the size of the matrix and if
everything looks good, it sends it off to
det_rec(). */
double math::MATRIX::determinant() const{
    if(rows != columns) return 0;
    if(rows == 1) return matrix[0];
    return det_rec(*this);
}

math::MATRIX math::MATRIX::rref() const{

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

void math::MATRIX::fill(FillFunction func){
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
            (*this)[i][j] = func(i, j);
}

/* Fill matrix - overload 2
This is the second overloaded function of the previous
one. It just fill the entire matrix with a constant value
specified by the argument. */

void math::MATRIX::fill(const double& val){
    for(int i = 0; i < length; i++) matrix[i] = val;
}

/* identity
produces an identity matrix based on the given dimension
*/
math::MATRIX math::identity(m_index rows, m_index columns){
    MATRIX mat(rows, columns);
    mat.fill([](m_index i, m_index j){return (double)(i==j);});
    return mat;
}
