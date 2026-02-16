#include "PmergeMe.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <utility>

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deq(other._deq) {}
PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}
PmergeMe::~PmergeMe() {}

bool PmergeMe::isStrictPositiveInt(const std::string& s)
{
	if (s.empty()) return false;
	for (size_t i = 0; i < s.size(); ++i) {
		if (s[i] < '0' || s[i] > '9') return false;
	}
	if (s == "0") return false;
	return true;
}

void PmergeMe::parseArgs(int argc, char** argv)
{
	_vec.clear();
	_deq.clear();

	if (argc < 2)
		throw std::runtime_error("Error");

	for (int i = 1; i < argc; ++i)
	{
		std::string t(argv[i]);
		if (!isStrictPositiveInt(t))
			throw std::runtime_error("Error");

		char* end = 0;
		long v = std::strtol(t.c_str(), &end, 10);
		if (!end || *end != '\0')
			throw std::runtime_error("Error");
		if (v <= 0 || v > INT_MAX)
			throw std::runtime_error("Error");

		_vec.push_back(static_cast<int>(v));
		_deq.push_back(static_cast<int>(v));
	}
}

void PmergeMe::printBefore() const
{
	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size(); ++i) {
		std::cout << _vec[i] << (i + 1 < _vec.size() ? " " : "");
	}
	std::cout << std::endl;
}

void PmergeMe::printAfter(const std::vector<int>& sorted) const
{
	std::cout << "After: ";
	for (size_t i = 0; i < sorted.size(); ++i) {
		std::cout << sorted[i] << (i + 1 < sorted.size() ? " " : "");
	}
	std::cout << std::endl;
}

static void buildJacobsthalOrderVector(size_t k, std::vector<size_t>& order)
{
    order.clear();
    if (k == 0) return;

    std::vector<size_t> js;
    size_t a = 0;
    size_t b = 1;
    js.push_back(1);

    while (true)
    {
        size_t c = b + 2 * a;
        a = b;
        b = c;
        if (b > k) break;
        if (js.back() != b)
            js.push_back(b);
    }

    size_t last = 0;
    for (size_t i = 0; i < js.size(); ++i)
    {
        size_t j = js[i];
        for (size_t idx = j; idx > last; --idx)
            order.push_back(idx - 1); // 0-based
        last = j;
    }
    for (size_t idx = k; idx > last; --idx)
        order.push_back(idx - 1);
}

static void buildJacobsthalOrderDeque(size_t k, std::deque<size_t>& order)
{
	order.clear();
	if (k == 0) return;

	std::deque<size_t> js;
	size_t j0 = 0, j1 = 1;
	js.push_back(1);
	while (true) {
		size_t j2 = j1 + 2 * j0;
		j0 = j1;
		j1 = j2;
		if (j1 > k) break;
		if (js.empty() || js.back() != j1)
			js.push_back(j1);
	}

	size_t last = 0;
	for (size_t a = 0; a < js.size(); ++a)
	{
		size_t j = js[a];
		if (j <= last) continue;
		for (size_t idx = j; idx > last; --idx)
			order.push_back(idx - 1);
		last = j;
	}
	for (size_t idx = k; idx > last; --idx)
		order.push_back(idx - 1);
}

static void makePairsVector(const std::vector<int>& in, std::vector< std::pair<int,int> >& pairs, bool& hasOdd, int& odd)
{
	pairs.clear();
	hasOdd = (in.size() % 2 != 0);
	if (hasOdd) odd = in.back();

	for (size_t i = 0; i + 1 < in.size(); i += 2)
	{
		int a = in[i];
		int b = in[i + 1];
		if (a < b) pairs.push_back(std::make_pair(a, b));
		else       pairs.push_back(std::make_pair(b, a));
	}
}

void PmergeMe::sortVectorFordJohnson(std::vector<int>& v)
{
	if (v.size() <= 1) return;

	std::vector< std::pair<int,int> > pairs;
	bool hasOdd = false;
	int odd = 0;
	makePairsVector(v, pairs, hasOdd, odd);

	std::vector<int> mainChain;
	mainChain.reserve(pairs.size());
	for (size_t i = 0; i < pairs.size(); ++i)
		mainChain.push_back(pairs[i].second);

	sortVectorFordJohnson(mainChain);

	std::vector<size_t> order;
	buildJacobsthalOrderVector(pairs.size(), order);

	for (size_t oi = 0; oi < order.size(); ++oi)
	{
		size_t idx = order[oi];
		int mn = pairs[idx].first;
		int mx = pairs[idx].second;

		std::vector<int>::iterator itMax = std::lower_bound(mainChain.begin(), mainChain.end(), mx);
		std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), itMax, mn);
		mainChain.insert(pos, mn);
	}

	if (hasOdd)
	{
		std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), odd);
		mainChain.insert(pos, odd);
	}

	v = mainChain;
}

static void makePairsDeque(const std::deque<int>& in, std::deque< std::pair<int,int> >& pairs, bool& hasOdd, int& odd)
{
	pairs.clear();
	hasOdd = (in.size() % 2 != 0);
	if (hasOdd) odd = in.back();

	for (size_t i = 0; i + 1 < in.size(); i += 2)
	{
		int a = in[i];
		int b = in[i + 1];
		if (a < b) pairs.push_back(std::make_pair(a, b));
		else       pairs.push_back(std::make_pair(b, a));
	}
}

void PmergeMe::sortDequeFordJohnson(std::deque<int>& d)
{
	if (d.size() <= 1) return;

	std::deque< std::pair<int,int> > pairs;
	bool hasOdd = false;
	int odd = 0;
	makePairsDeque(d, pairs, hasOdd, odd);

	std::deque<int> mainChain;
	for (size_t i = 0; i < pairs.size(); ++i)
		mainChain.push_back(pairs[i].second);

	sortDequeFordJohnson(mainChain);

	std::deque<size_t> order;
	buildJacobsthalOrderDeque(pairs.size(), order);

	for (size_t oi = 0; oi < order.size(); ++oi)
	{
		size_t idx = order[oi];
		int mn = pairs[idx].first;
		int mx = pairs[idx].second;

		std::deque<int>::iterator itMax = std::lower_bound(mainChain.begin(), mainChain.end(), mx);
		std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), itMax, mn);
		mainChain.insert(pos, mn);
	}

	if (hasOdd)
	{
		std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), odd);
		mainChain.insert(pos, odd);
	}

	d = mainChain;
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
