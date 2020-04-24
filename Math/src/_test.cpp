#define SOMETHING "hello"
#include <iostream>

void printSomething(int num){
	printf("This is my number %d\n", num);
	return;
}

int main(int argc, const char** argv){

    std::cout << "This is SOMETHING BIG!" << std::endl;
    printSomething(7);
    return 0;
}
