#include "Array.hpp"
#include <iostream>

int main()
{
	std::cout << "--- Array empty ---" << std::endl;
	Array<int> empty;
	std::cout << "Size: " << empty.size() << std::endl;

	std::cout << "\n--- Array 5 ints ---" << std::endl;
	Array<int> arr(5);
	std::cout << "size: " << arr.size() << std::endl;
	
	arr[0] = 10;
	arr[2] = 42;
	arr[4] = 99;
	
	std::cout << "arr[0] = " << arr[0] << std::endl;
	std::cout << "arr[2] = " << arr[2] << std::endl;
	std::cout << "arr[4] = " << arr[4] << std::endl;

	std::cout << "\n--- Test out of range ---" << std::endl;
	try {
		std::cout << arr[10] << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
