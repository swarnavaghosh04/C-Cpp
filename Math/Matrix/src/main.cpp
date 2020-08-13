#include <_matrix.hpp>

int main(int argc, char** argv){
    printf("\n---- Attrib Test ----\n");
    math::MATRIX mat = {0,0};
    mat.setAttrib(LOWER_TRI);
    mat.setAttrib(UPPER_TRI);
    printf("true:%s\n", (mat.checkAttrib(DIAGONAL) ? "true":"false"));
    printf("true:%s\n", (mat.checkAttrib(LOWER_TRI) ? "true":"false"));
    mat.removeAttrib(LOWER_TRI);
    printf("false:%s\n", (mat.checkAttrib(DIAGONAL) ? "true":"false"));
    mat.removeAttrib((unsigned char)0b1111);
    printf("false:%s\n", (mat.checkAttrib(TRANSPOSED) ? "true":"false"));
    mat.setAttrib(TRANSPOSED);
    printf("true:%s\n", (mat.checkAttrib(TRANSPOSED) ? "true":"false"));

}
