#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

static void testSubjectExample() {
	std::cout << "== Subject example ==" << std::endl;

	Span sp(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << sp.shortestSpan() << std::endl; // expected 2
	std::cout << sp.longestSpan() << std::endl;  // expected 14
}

static void testExceptions() {
	std::cout << "== Exceptions ==" << std::endl;

	// full
	try {
		Span sp(2);
		sp.addNumber(1);
		sp.addNumber(2);
		sp.addNumber(3); // should throw
		std::cout << "ERROR: expected FullException" << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}

	// not enough
	try {
		Span sp(10);
		sp.addNumber(42);
		std::cout << sp.shortestSpan() << std::endl; // should throw
		std::cout << "ERROR: expected NotEnoughException" << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}

static void testRangeAdd() {
	std::cout << "== Range add ==" << std::endl;

	Span sp(5);
	std::vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

	sp.addNumber(v.begin(), v.end()); // adds 3 numbers

	std::cout << "shortest: " << sp.shortestSpan() << std::endl; // 10
	std::cout << "longest : " << sp.longestSpan() << std::endl;  // 20

	// test range overflow (should throw before inserting anything)
	try {
		std::list<int> lst;
		lst.push_back(1);
		lst.push_back(2);
		lst.push_back(3);

		sp.addNumber(lst.begin(), lst.end()); // would exceed capacity (already has 3, adding 3 -> 6 > 5)
		std::cout << "ERROR: expected FullException on range overflow" << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}

static void testBig() {
	std::cout << "== Big test (10000) ==" << std::endl;

	const unsigned int N = 10000;
	Span sp(N);

	std::vector<int> data;
	data.reserve(N);

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	for (unsigned int i = 0; i < N; ++i)
		data.push_back(std::rand());

	sp.addNumber(data.begin(), data.end());

	std::cout << "shortest: " << sp.shortestSpan() << std::endl;
	std::cout << "longest : " << sp.longestSpan() << std::endl;
}

int main() {
	try {
		testSubjectExample();
		testExceptions();
		testRangeAdd();
		testBig();
	} catch (const std::exception& e) {
		std::cout << "Unexpected: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
