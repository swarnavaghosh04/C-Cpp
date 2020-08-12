#ifndef FRACTION_H_
#define FRACTION_H_

#include <string>

namespace Math{
	class Fraction{
		private:
			int numerator;
			int denomenator;
		public:
			Fraction(int numerator=1, int denometor=1);
			std::string toString(int base=10);
			const Fraction& reduce();
	};
}

#endif