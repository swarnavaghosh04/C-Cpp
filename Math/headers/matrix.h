#define NO_STAT     0
#define TRANSPOSE   0b1
#define LOWER_TRI   0b10
#define UPPER_TRI   0b100
#define DIAGONAL    0b110
#define SYMMETRIC   0b1000
#define POS_DEF     0b10000

typedef unsigned int m_index;

typedef struct d_Matrix{
    double* mat_ptr;
    m_index rows;
    m_index columns;
    /** status
     * BYTES 0..7 = least significant .. most significant
     * BYTE 0: View - Normal(0) or Tranposed(1)
     * BYTE 1: Lower Triangular
     * BYTE 2: Upper Triangular
     * BYTE 3: Symmetric
     * BYTE 4: Positive Definite
    **/
    unsigned char status;
} d_Matrix, D_MATRIX;

// Access Matrix Data
void* md_get(d_Matrix*, m_index, m_index);

// Arithmetic opertions
void md_add(d_Matrix*, d_Matrix*, d_Matrix*, char);
void md_s_mult(d_Matrix*, double, d_Matrix*, char);
void md_mult(d_Matrix*, d_Matrix*, d_Matrix*, char);