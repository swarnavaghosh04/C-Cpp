#include <iostream>
#include "../include/fractions.hpp"

int main(int argc, char**argv){
	Math::Fraction f1(4,5);
	Math::Fraction f2(9,8);
	std::cout << f1.toString() << std::endl;
	std::cout << f2.toString() << std::endl;
	return 0;
}
