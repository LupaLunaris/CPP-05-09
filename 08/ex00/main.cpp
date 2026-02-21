#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

int main() {
	// Test vector
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	
	try {
		std::vector<int>::iterator it = easyfind(vec, 3);
		std::cout << "Trouvé : " << *it << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Pas trouvé" << std::endl;
	}
	
	// Test list
	std::list<int> lst;
	lst.push_back(10);
	lst.push_back(20);
	
	try {
		std::list<int>::iterator it = easyfind(lst, 11);
		std::cout << "Trouvé : " << *it << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Pas trouvé" << std::endl;
	}
	
	return 0;
}
