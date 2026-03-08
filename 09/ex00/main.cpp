#include "BitcoinExchange.hpp"
#include <iostream>
#include <exception>

int main(int ac, char **av) {
	if (ac != 2) {
		std::cout << "Error: could not open file.\nUsage: ./btc input.txt" << std::endl;
        return 1;
	}
	try {
		BitcoinExchange btc;
		btc.loadData("data.csv");
		btc.processInput(av[1]);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
