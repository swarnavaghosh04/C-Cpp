#include <iostream>
#include <fractions.hpp>

int main(int argc, char**argv){
	Math::Fraction frac[4];

	frac[0] = Math::Fraction(2,6).reduce();
	frac[1] = Math::Fraction(3,6).reduce();
	frac[2] = Math::Fraction(10,5).reduce();
	frac[3] = Math::Fraction(3,4).reduce();

	for(int i = 0; i < 4; i++) std::cout << frac[i].toString() << std::endl;
	return 0;
}
