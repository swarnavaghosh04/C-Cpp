#include <iostream>
#include "matrix.hpp"

void printMatrix(const MATRIX<int>& m){
	for(int i = 0; i < m.getRows(); i++){
		for(int j = 0; j < m.getColumns(); j++){
			printf("%-6d", m.get(i, j));
		}
		std::cout << std::endl;
	}
}

int main(int argv, char** argc){

	MATRIX<int> mat1(3, 4);
	MATRIX<int> mat2(4, 3);
	for(int i = 0; i < mat1.getRows(); i++){
		for(int j = 0; j < mat1.getColumns(); j++){
			mat1.set(i, j, i+j);
		}
	}
	for(int i = 0; i < mat2.getRows(); i++){
		for(int j = 0; j < mat2.getColumns(); j++){
			mat2.set(i, j, 5);
		}
	}

	MATRIX<int> mat3 = mat1*mat2;

	std::cout << "Matrix 1:" << std::endl;
	printMatrix(mat1);
	std::cout << std::endl;

	std::cout << "Matrix 2:" << std::endl;
	printMatrix(mat2);
	std::cout << std::endl;

	std::cout << "Matrix 1 * Matrix 2:" << std::endl;
	printMatrix(mat3);

}