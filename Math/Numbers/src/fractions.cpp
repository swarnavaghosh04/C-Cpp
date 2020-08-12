#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <fractions.hpp>

Math::Fraction::Fraction(int numerator, int denomenator) : 
	numerator(numerator), 
	denomenator(denomenator) 
{}

std::string Math::Fraction::toString(int base){
	std::stringstream str;
	str << this->numerator << "/" << this->denomenator;
	return str.str();
}

const Math::Fraction& Math::Fraction::reduce(){
	int g = std::__gcd(numerator, denomenator);
	numerator /= g;
	denomenator /= g;
	return *this;
}
