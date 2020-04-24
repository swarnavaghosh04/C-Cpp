#include ".\\matrix.hpp"
#include <stdio.h>


//#define DEBUG

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

const char* math::MatrixInverseComputationError::what() const throw(){
    return "An error occured while computing the inverse of a matrix";
}

// =========== Matrix Class =================

/** Matrix Constructor (rows, colummns)
 * Dynamically allocates double array of length rows*columns.
 * Allocation will be deleted by destructor.
*/
math::MATRIX::MATRIX(m_index rows, m_index columns) : 
    rows(rows), 
    columns(columns),
    length(rows*columns)
{   
    #ifdef DEBUG
    printf("CONSTRUCTED: %dx%d @ 0x%x\n", rows, columns, this);
    #endif 
    matrix = (length==0?nullptr:new double[length]);
}

/** Matrix Constructor (rows, columns, array)
 * Takes in pre-initiated array of double of length rows*columns.
 * This array is NOT deallocated by destructor.
*/
math::MATRIX::MATRIX(m_index rows, m_index columns, const double* const matrixPointer) :
    rows(rows), 
    columns(columns),
    length(rows*columns),
    matrix((double*)matrixPointer),
    canDelete(false)
{
    #ifdef DEBUG
    printf("CONSTRUCTED: %dx%d @ 0x%x (no alloc)\n", rows, columns, this);
    #endif
}

/* Copy Constructor (allocates new memory and copies matrix; performs deep copy)
The copy constructor invokes a deep copy. it creates a new matrix by copying
all the content of the other matrix and writing them into a new block of memory. */
math::MATRIX::MATRIX(const MATRIX& mat) : 
    rows(mat.rows),
    columns(mat.columns),
    length(rows*columns)
{
    #ifdef DEBUG
    printf("COPY: %dx%d to 0x%x from 0x%x\n", rows, columns, this, &mat);
    #endif
    matrix = (length==0?nullptr:new double[length]);
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
        #ifdef DEBUG
        printf("DESTROYED: %dx%d @ 0x%x\n", rows, columns, this);
        #endif
    }
}

// Getters =======================================

// Get Rows
unsigned int math::MATRIX::getRows() const{ return rows; }

// Get Columns
unsigned int math::MATRIX::getColumns() const{ return columns; }

// Get Matrix
const double* const math::MATRIX::getMatrix() const{ return matrix; }

bool math::MATRIX::getCanDelete()const {return canDelete;}

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
    /* If the two matrices do not have the
    same dimensions, deallocate this matrix,
    and allocate a new chunck of memory of
    appropriate length.*/
    if(rows != mat.rows || columns != mat.columns){
        rows = mat.rows;
        columns = mat.columns;
        length = mat.length;
        if(canDelete) delete[] matrix;
        matrix = (length==0?nullptr:new double[length]);
    }
    // Copy over the matrix
    for(int i = 0; i < length; i++) matrix[i] = mat.matrix[i];
    #ifdef DEBUG
    printf("ASSIGNED: %dx%d to 0x%x by 0x%x\n", rows, columns, this, &mat);
    #endif
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
    #ifdef DEBUG
    printf("MOVE: %dx%d to 0x%x from 0x%x\n", rows, columns, this, &mat);
    #endif
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

void math::MATRIX::add(const MATRIX& mat1, const MATRIX& mat2, MATRIX& answer){
    if(mat1.length!= mat2.length || mat2.rows!=mat1.rows) throw DimensionException();
    if(answer.length!=mat1.length){
        if(answer.canDelete) delete[] answer.matrix;
        answer.matrix = new double[mat1.length];
    }
    answer.rows = mat1.rows;
    answer.columns = mat1.columns;
    answer.length = mat1.length;
    for(int i = 0; i < answer.length; i++) answer.matrix[i] = mat1.matrix[i]+mat2.matrix[i];
    return;
}

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

extern void printMatrix(const math::MATRIX&, const char* message = "matrix");

/* ref
returns new matrix in row echelon form.
It first declares the new matrix <refMat>
and copies over the values. After that,
two nested for-loops loop through the matrix
and does row operations to get the result:
outer loop: j=0; j < min(rows,columns), j++
inner loop: i=0; i < rows; i++
The outer loop essential points to the each
pivot row while the inner loop goes through
all the non-pivot rows below the pivot row,
making the the respective entries 0.*/
math::MATRIX math::MATRIX::ref() const{
    MATRIX refMat(rows, columns);
    for(int i = 0; i < length; i++) refMat.matrix[i] = matrix[i];   // Copy
    double m;        // temporary variable used in row operation
    unsigned int condition = (rows<columns?rows:columns);
    for(unsigned int j = 0; j < condition; j++){        // loop: points to pivot row
        if(refMat[j][j] == 0) continue;                     // Skip if pivot entry is 0
        for(unsigned int i = j+1; i < rows; i++){           // loop: points to non pivot rows below the pivot row
            if(refMat[i][j] == 0) continue;                     // skip if leading entry is already 0
            m = refMat[i][j]/refMat[j][j];                      // m = <non_pivot_entry>/<pivot_entry> => used in row operation
            refMat.rowop(i, j, [&](double& r1, double& r2){     // row operation (preserves the determinent)
                r1 = (r1 - r2*m);});
        }
    }
    return refMat;
}

/*rref
returns new matrix in reduce-row-echelon-form.
It works quit similiar to ref(), but the only
difference is that the inner loop goes through
ALL non-pivot rows as opposed to only the one's
below the pivot row. */
math::MATRIX math::MATRIX::rref(MATRIX* inv, bool invFlag) const{
    if(rows!=columns){
        *inv = MATRIX();
        if(invFlag) throw MatrixInverseComputationError();
        inv = nullptr;
    }else *inv = identity(rows);
    MATRIX rrefMat(rows, columns);
    for(int i = 0; i < length; i++) rrefMat.matrix[i] = matrix[i];
    double m;
    unsigned int condition = (rows<columns?rows:columns);
    for(unsigned int j = 0; j < condition; j++){
        if(rrefMat[j][j] == 0){
            *inv = MATRIX();      // deallocate matrix
            if(invFlag) throw MatrixInverseComputationError();
            inv = nullptr;        // make nullptr
            continue;
        }
        for(unsigned int i = 0; i < rows; i++){
            if(i == j || rrefMat[i][j] == 0) continue;
            m = rrefMat[i][j]/rrefMat[j][j];
            rrefMat.rowop(i, j, [&](double& r1, double& r2){
                r1 = (r1 - r2*m); });
            if(inv != nullptr)
                inv->rowop(i, j, [&](double& r1,double& r2){
                    r1 = (r1-r2*m); });
        }
    }
    if(inv != nullptr){
        for(int i = 0; i < rows;i++){
            m = rrefMat[i][i];
            inv->rowop(i, i, [&](double& r, double& na){ r = r/m;});
        }
    }
    return rrefMat;
}

math::MATRIX math::MATRIX::inverse() const{
    MATRIX inv = MATRIX();
    this->rref(&inv, true);
    return inv;
}

// Other functions ===================================

/* Fill matrix - overload 2
This is the second overloaded function of the previous
one. It just fill the entire matrix with a constant value
specified by the argument. */
void math::MATRIX::fill(const double& val){
    for(int i = 0; i < length; i++) matrix[i] = val;
}

/* identity
produces an identity matrix based on the given dimension */
math::MATRIX math::MATRIX::identity(m_index rows, m_index columns){
    MATRIX mat(rows, (columns==0?rows:columns));
    mat.fill([](m_index i, m_index j){return (double)(i==j);});
    return mat;
}
