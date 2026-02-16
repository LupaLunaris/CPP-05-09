#include "RPN.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2) {
		std::cerr << "Error\nUsage: ./RPN \"expression\"\nEx : ./RPN \"1 2 + 3 *\"" << std::endl;
		return 1;
	}
	try {
		RPN rpn;
		long result = rpn.calculate(argv[1]);
		std::cout << result << std::endl;
	}
	catch (...) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	return 0;
}
