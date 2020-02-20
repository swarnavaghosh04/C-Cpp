#include <iostream>
#include "matrix.hpp"

int main(int argv, char** argc){

	MATRIX<int> mat1(3, 5);
	MATRIX<int> mat2(3, 5);
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 5; j++){
			mat1.set(i, j, 5);
			mat2.set(i, j, i*j);
		}
	}

	MATRIX<int> mat3 = mat1+mat2;

	std::cout << "Matrix 1:" << std::endl;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 5; j++){
			printf("%-5d", mat1.get(i, j));
		}
		std::cout << std::endl;
	}
	
	std::cout << std::endl;

	std::cout << "Matrix 2:" << std::endl;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 5; j++){
			printf("%-5d", mat2.get(i, j));
		}
		std::cout << std::endl;
	}
	
	std::cout << std::endl;

	std::cout << "Matrix 1 + Matrix 2:" << std::endl;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 5; j++){
			printf("%-5d", mat3.get(i, j));
		}
		std::cout << std::endl;
	}

}