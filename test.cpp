#include <iostream>
#include "matrix.hpp"

int main(int argv, char** argc){
    const MATRIX<int> mat1(3, 5);
    const MATRIX<int> mat2(3, 5);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 5; j++){
            mat1.set(i, j, i*j);
            mat2.set(i, j, i*j);
        }
    }

    MATRIX<int> mat3 = mat2+mat1;

    for(int i = 0; i < mat1.getLength(); i++){
        printf("%-5d", mat1.iterate());
        if(((i+1) % mat1.getColumns()) == 0) std::cout << std::endl;
    }

    std::cout << "\n============================\n" << std::endl;

    for(int i = 0; i < mat1.getLength(); i++){
        printf("%-5d", mat1.iterate());
        if(((i+1) % mat1.getColumns()) == 0) std::cout << std::endl;
    }

    std::cout << "\n============================\n" << std::endl;
    
    for(int i = 0; i < mat2.getLength(); i++){
        printf("%-5d", mat2.iterate());
        if(((i+1) % mat2.getColumns()) == 0) std::cout << std::endl;
    }
    
    std::cout << std::endl;
    
    for(int i = 0; i < mat3.getLength(); i++){
        printf("%-5d", mat3.iterate());
        if(((i+1) % mat3.getColumns()) == 0) std::cout << std::endl;
    }




}