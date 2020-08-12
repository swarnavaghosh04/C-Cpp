#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include "../include/fractions.hpp"

Math::Fraction::Fraction(int numerator, int denomenator) : 
	numerator(numerator), 
	denomenator(denomenator) 
{}

std::string Math::Fraction::toString(int base){
	std::stringstream str;
	str << this->numerator << "/" << this->denomenator;
	return str.str();
}
