#include <_matrix.hpp>
#include <iostream>

void printBits(int c, int nbits = 32){
    unsigned char n = 1 << (nbits-1);
    while(n){
        if(c & n) std::printf("1");
        else printf("0");
        n >>= 1;
    }
    std::printf("\n");
    return;
}

int main(int argc, char** argv){
    printf("\n---- Attrib Test ----\n");
    math::MATRIX mat = {0,0};

    mat.toggleAttribs(TRANSPOSE | LOWER_TRI);
    printBits(mat.getAttrib(), 4);

    mat.toggleAttribs(TRANSPOSE);

    printBits(mat.getAttrib(), 4);

    printf("false:%s\n", mat.checkAttribs(TRANSPOSE)?"true":"false");
    printf("true:%s\n", mat.checkAttribs(LOWER_TRI)?"true":"false");


    return 0;
}
