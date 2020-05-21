#include <stdio.h>

__cdecl void swap(int*, int*);
__fastcall void swap2(int*,int*);

void m_swap(int* i, int* j){
    int temp = *i;
    *i = *j;
    *j = temp;
}

int main(int argc, char** argv){
    int i = 0; 
    int j = 1;
    printf("%d, %d\n", i, j);
    swap2(&i, &j);
    printf("%d, %d\n", i, j);
}