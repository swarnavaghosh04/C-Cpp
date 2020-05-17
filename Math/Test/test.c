#include <cblas.h>
#include <stdio.h>

void printMatrix(
    const double* mat,
    const unsigned int m,
    const unsigned int n,
    OPENBLAS_CONST CBLAS_TRANSPOSE t,
    const char* label)
{
    printf("> %s:", label);

    int i,j, *pr, *pc, nn;

    switch(t){
        case CblasNoTrans:
            pr = &i;
            pc = &j;
            nn = n;
            break;
        case CblasTrans:
            pr = &j;
            pc = &i;
            nn = m;
            break;
        defualt:
            printf(" ERROR\n");
            return;
    }

    for(i = 0; i < m; i++){
        printf("\n\t");
        for(j = 0; j < n; j++) printf("%6.2f", mat[(*pr)*nn+(*pc)]);
    }
    printf("\n");

}

int main(int argc, char** argv){

    double 
        x[] = {1.,2,3},
        A[12],
        y[4];

    for(int i = 0; i < 12; i++) A[i] = i+1;

    cblas_dgemv(CblasRowMajor, CblasNoTrans, 4., 3., 1., A, 3., x, 1, 0., y, 1);

    printMatrix(x, 3,1, CblasNoTrans, "x");
    printMatrix(A, 4,3, CblasTrans, "A");
    printMatrix(y, 4,1, CblasNoTrans, "y");

    return 0;
}
