#include "Span.hpp"

Span::Span(unsigned int n) : _max(n), _v() {
    _v.reserve(n);
}

Span::Span(const Span& other) : _max(other._max), _v(other._v) {}

Span& Span::operator=(const Span& other) {
	if (this != &other) {
		_max = other._max;
		_v = other._v;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(int x) {
    if (_v.size() >= _max)
        throw FullException();
    _v.push_back(x);
}

int Span::longestSpan() const {
    if (_v.size() < 2)
        throw FullException();

    std::vector<int>::const_iterator minIt = std::min_element(_v.begin(), _v.end());
    std::vector<int>::const_iterator maxIt = std::max_element(_v.begin(), _v.end());
    return *maxIt - *minIt;
}

int Span::shortestSpan() const {
	if (_v.size() < 2)
		throw NotEnoughException();
	std::vector<int> tmp(_v);
	std::sort(tmp.begin(), tmp.end());
	int minSpan = tmp[1] - tmp[0];
	for (size_t i = 1; i < tmp.size(); ++i) {
		int diff = tmp[i] - tmp[i - 1];
		if (diff < minSpan)
			minSpan = diff;
	}
	return minSpan;
}

const char* Span::FullException::what() const throw() {
    return "Span is full";
}

const char* Span::NotEnoughException::what() const throw() {
    return "Not enough numbers to find a span";
}
