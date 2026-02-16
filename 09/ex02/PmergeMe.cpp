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

// Binary search insertion for vector
static void binaryInsertVector(std::vector<int>& sorted, int value)
{
	size_t left = 0;
	size_t right = sorted.size();
	
	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (sorted[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	sorted.insert(sorted.begin() + left, value);
}

void PmergeMe::sortVectorFordJohnson(std::vector<int>& v)
{
	size_t n = v.size();
	if (n <= 1)
		return;
	
	// For small arrays, use simple sorting
	if (n == 2)
	{
		if (v[0] > v[1])
			std::swap(v[0], v[1]);
		return;
	}
	
	// Step 1: Create pairs and sort them
	typedef std::pair<int, int> IntPair;
	std::vector<IntPair> pairs;
	bool hasStraggler = (n % 2 == 1);
	int straggler = hasStraggler ? v[n - 1] : 0;
	
	size_t pairCount = n / 2;
	for (size_t i = 0; i < pairCount; ++i)
	{
		int a = v[2 * i];
		int b = v[2 * i + 1];
		if (a > b)
			pairs.push_back(std::make_pair(a, b));
		else
			pairs.push_back(std::make_pair(b, a));
	}
	
	// Step 2: Recursively sort based on larger elements
	std::vector<int> larger;
	for (size_t i = 0; i < pairs.size(); ++i)
		larger.push_back(pairs[i].first);
	
	sortVectorFordJohnson(larger);
	
	// Rearrange pairs based on sorted larger elements
	std::vector<IntPair> sortedPairs;
	for (size_t i = 0; i < larger.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].first == larger[i])
			{
				sortedPairs.push_back(pairs[j]);
				pairs[j].first = -1; // Mark as used
				break;
			}
		}
	}
	
	// Step 3: Build main chain starting with first small element, then all larger elements
	std::vector<int> result;
	result.push_back(sortedPairs[0].second);
	for (size_t i = 0; i < sortedPairs.size(); ++i)
		result.push_back(sortedPairs[i].first);
	
	// Step 4: Insert remaining smaller elements using binary insertion
	for (size_t i = 1; i < sortedPairs.size(); ++i)
	{
		binaryInsertVector(result, sortedPairs[i].second);
	}
	
	// Step 5: Insert straggler if exists
	if (hasStraggler)
	{
		binaryInsertVector(result, straggler);
	}
	
	v = result;
}

// Binary search insertion for deque
static void binaryInsertDeque(std::deque<int>& sorted, int value)
{
	size_t left = 0;
	size_t right = sorted.size();
	
	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (sorted[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	sorted.insert(sorted.begin() + left, value);
}

void PmergeMe::sortDequeFordJohnson(std::deque<int>& d)
{
	size_t n = d.size();
	if (n <= 1)
		return;
	
	// For small arrays, use simple sorting
	if (n == 2)
	{
		if (d[0] > d[1])
			std::swap(d[0], d[1]);
		return;
	}
	
	// Step 1: Create pairs and sort them
	typedef std::pair<int, int> IntPair;
	std::vector<IntPair> pairs;
	bool hasStraggler = (n % 2 == 1);
	int straggler = hasStraggler ? d[n - 1] : 0;
	
	size_t pairCount = n / 2;
	for (size_t i = 0; i < pairCount; ++i)
	{
		int a = d[2 * i];
		int b = d[2 * i + 1];
		if (a > b)
			pairs.push_back(std::make_pair(a, b));
		else
			pairs.push_back(std::make_pair(b, a));
	}
	
	// Step 2: Recursively sort based on larger elements
	std::deque<int> larger;
	for (size_t i = 0; i < pairs.size(); ++i)
		larger.push_back(pairs[i].first);
	
	sortDequeFordJohnson(larger);
	
	// Rearrange pairs based on sorted larger elements
	std::vector<IntPair> sortedPairs;
	for (size_t i = 0; i < larger.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].first == larger[i])
			{
				sortedPairs.push_back(pairs[j]);
				pairs[j].first = -1; // Mark as used
				break;
			}
		}
	}
	
	// Step 3: Build main chain starting with first small element, then all larger elements
	std::deque<int> result;
	result.push_back(sortedPairs[0].second);
	for (size_t i = 0; i < sortedPairs.size(); ++i)
		result.push_back(sortedPairs[i].first);
	
	// Step 4: Insert remaining smaller elements using binary insertion
	for (size_t i = 1; i < sortedPairs.size(); ++i)
	{
		binaryInsertDeque(result, sortedPairs[i].second);
	}
	
	// Step 5: Insert straggler if exists
	if (hasStraggler)
	{
		binaryInsertDeque(result, straggler);
	}
	
	d = result;
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
