#include <stdio.h>

int main(){
    FILE* f = fopen("C:\\users\\swarn\\OneDrive\\Desktop\\hello.txt", "w+");
    const char* const myName = "Swarnava Ghosh";
    fprintf(f, myName);
    fclose(f);
    return 0;
}