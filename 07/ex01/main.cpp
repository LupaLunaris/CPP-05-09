#include "iter.hpp"
#include <iostream>
#include <string>

// Fonction qui modifie (non-const)
void increment(int& n) {
	n++;
}

// Fonction template
template <typename T>
void print(const T& x) {
	std::cout << x << std::endl;
}

// Fonction pour string
void toUpper(std::string& s) {
	for (size_t i = 0; i < s.length(); i++) {
		s[i] = std::toupper(s[i]);
	}
}

int main() {
	std::cout << "=== Test 1 : Display int ===" << std::endl;
	int intArr[] = {1, 2, 3, 4, 5};
	iter(intArr, 5, print<int>);
	std::cout << std::endl;

	std::cout << "\n=== Test 2 : Modification int ===" << std::endl;
	iter(intArr, 5, increment);
	std::cout << "After increment : " << std::endl;
	iter(intArr, 5, print<int>);
	std::cout << std::endl;

	std::cout << "\n=== Test 3 : Template function ===" << std::endl;
	double doubleArr[] = {1.1, 2.2, 3.3};
	iter(doubleArr, 3, print<double>);

	std::cout << "\n=== Test 4 : String ===" << std::endl;
	std::string strArr[] = {"hello", "world", "42"};
	iter(strArr, 3, toUpper);
	iter(strArr, 3, print<std::string>);

	std::cout << "\n=== Test 5 : Const array ===" << std::endl;
	const int constArr[] = {10, 20, 30};
	iter(constArr, 3, print<int>);

	return 0;
}