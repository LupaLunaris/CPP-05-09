#ifndef SPAN_HPP
# define SPAN_HPP

#include <vector>
#include <algorithm>
#include <exception>

class Span {
	private:
		unsigned int _max;
		std::vector<int> _v;
	public:
		Span(unsigned int n);
		Span(const Span& other);
		Span& operator=(const Span&other);
		~Span();

		void addNumber(int x);

		template <typename t>
		void addNumber(t first, t last) {
			unsigned int count = std::distance(first, last);
			if (_v.size() + count > _max)
				throw FullException();
			_v.insert(_v.end(), first, last);
		}

		int shortestSpan() const;
		int longestSpan() const;

		class FullException : public std::exception {
		public:
			virtual const char* what() const throw();
		};

		class NotEnoughException : public std::exception {
		public:
			virtual const char* what() const throw();
		};
};

#endif