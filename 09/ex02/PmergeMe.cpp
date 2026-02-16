#include "PmergeMe.hpp"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <iomanip>
#include <utility>
#include <algorithm>

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deq(other._deq) {}
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}
PmergeMe::~PmergeMe() {}

bool PmergeMe::isStrictPositiveInt(const std::string& s)
{
	if (s.empty()) return false;
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	// "0" n'est pas positif
	if (s.size() == 1 && s[0] == '0') return false;
	return true;
}

void PmergeMe::parseArgs(int argc, char** argv)
{
	_vec.clear();
	_deq.clear();

	for (int i = 1; i < argc; ++i)
	{
		std::string token(argv[i]);

		if (!isStrictPositiveInt(token))
			throw std::runtime_error("Error");

		// overflow check
		long val = std::strtol(token.c_str(), 0, 10);
		if (val <= 0 || val > INT_MAX)
			throw std::runtime_error("Error");

		_vec.push_back(static_cast<int>(val));
		_deq.push_back(static_cast<int>(val));
	}

	if (_vec.empty())
		throw std::runtime_error("Error");
}

void PmergeMe::printBefore() const
{
	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		std::cout << _vec[i];
		if (i + 1 < _vec.size())
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printAfter(const std::vector<int>& sorted) const
{
	std::cout << "After: ";
	for (size_t i = 0; i < sorted.size(); ++i)
	{
		std::cout << sorted[i];
		if (i + 1 < sorted.size())
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::sortVectorFordJohnson(std::vector<int>& v)
{

	std::sort(v.begin(), v.end());
}

void PmergeMe::sortDequeFordJohnson(std::deque<int>& d)
{

	std::sort(d.begin(), d.end());
}

void PmergeMe::run(int argc, char** argv)
{
	try
	{
		parseArgs(argc, argv);

		printBefore();

		std::vector<int> v = _vec;
		std::deque<int>  d = _deq;

		clock_t startV = clock();
		sortVectorFordJohnson(v);
		clock_t endV = clock();

		// 4) deque timing
		clock_t startD = clock();
		sortDequeFordJohnson(d);
		clock_t endD = clock();

		printAfter(v);

		double timeV = (double)(endV - startV) / CLOCKS_PER_SEC * 1000000.0;
		double timeD = (double)(endD - startD) / CLOCKS_PER_SEC * 1000000.0;

		std::cout << "Time to process a range of " << _vec.size()
				  << " elements with std::vector : "
				  << std::fixed << std::setprecision(5) << timeV << " us" << std::endl;
				  
		std::cout << "Time to process a range of " << _deq.size()
				  << " elements with std::deque : "
				  << std::fixed << std::setprecision(5) << timeD << " us" << std::endl;
	}
	catch (...)
	{
		std::cerr << "Error" << std::endl;
	}
}
