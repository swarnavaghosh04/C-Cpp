
#include "..\\headers\\matrix.h"
#include <stdlib.h>
#include <stdio.h>

#define DEBUG 1

// Access Matrix Data
void* md_get(d_Matrix* mat, m_index i, m_index j){
    return mat->mat_ptr + ((mat->status & TRANSPOSE)?i+(mat->columns*j):j+(mat->columns*i));
}

void md_add(d_Matrix* a, d_Matrix* b, d_Matrix* res, char creationFlag){
    m_index size = a->rows*a->columns;
    if(creationFlag){ 
        res->mat_ptr = malloc(size*sizeof(double));
        res->columns = a->columns;
        res->rows = a->columns;
        res->status = a->status & b->status & TRANSPOSE;
    }else if(res->rows != a->rows || res->columns != a->columns){
        res = NULL;
        return;
    }
    if((a->status ^ b->status) & TRANSPOSE){
        if(a->status & TRANSPOSE)
        for(int i = 0; i < a->rows; i++){
            for(int i = 0; i < a->columns; i++){
                res[i+res->]
            }
        }
    }
    else{
        for(m_index i = 0; i < a->length; i++)
            res->mat_ptr[i] = a->mat_ptr[i] + b->mat_ptr[i];
    }
}

void md_s_mult(d_Matrix* mat, double d, d_Matrix* res, char creationFlag){
    if(creationFlag){
        res->mat_ptr = malloc(mat->length*sizeof(double));
        res->columns - mat->columns;
        res->length = mat->length;
        res->status = 0;
    }else if(res->length != mat->length || res->columns != mat->columns){
        res = NULL;
        return;
    }
    for(m_index i = 0; i < mat->length; i++)
        res->mat_ptr[i] = d*mat->mat_ptr[i];
}

void md_mult(d_Matrix* a, d_Matrix* b, d_Matrix* res, char creationFlag){

    m_index rows_a = a->length/a->columns;

    if(creationFlag){
        res->mat_ptr = malloc(a->length*sizeof(double));
        res->columns - a->columns;
        res->length = a->length;
        res->status = 0;
    }else if(res->length != rows_a*b->columns || res->columns != b->columns){
        res = NULL;
        return;
    }

    double temp;
    for(m_index i = 0; i < rows_a; i++)
        for(m_index j = 0; j < b->columns; j++){
            temp=0.;
            for(m_index k = 0; k < a->columns; k++){
                temp += (*(double*)md_get(a,i,k))*(*(double*)md_get(b,k,j));
            }
            res->mat_ptr[i*res->columns+j] = temp;
        }
}
