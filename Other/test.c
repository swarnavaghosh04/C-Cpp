#include <stdio.h>


int main(){

    int var = 9;
    int q = 7;
    int y = 8;

    int* pvar = &var;

    *pvar = 70-1;

    printf("Location of var: %u\n", &var);
    printf("Location of q:   %u\n", &q);
    printf("Location of y:   %u\n", &y);

}