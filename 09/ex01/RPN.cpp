#include "RPN.hpp"

#include <list>
#include <sstream>
#include <stdexcept>
#include <cctype>

RPN::RPN() {}
RPN::RPN(const RPN& other) { (void)other; }
RPN& RPN::operator=(const RPN& other) { (void)other; return *this; }
RPN::~RPN() {}

static bool isOp(const std::string& t)
{
	return (t.size() == 1 && (t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/'));
}

static bool isDigitToken(const std::string& t)
{
	return (t.size() == 1 && std::isdigit(static_cast<unsigned char>(t[0])) != 0);
}

long RPN::calculate(const std::string& expr) const
{
	std::istringstream iss(expr);
	std::string tok;
	std::list<long> st;

	while (iss >> tok)
	{
		if (isDigitToken(tok))
			st.push_back(tok[0] - '0');
		else if (isOp(tok))
		{
			if (st.size() < 2)
				throw std::runtime_error("Error");
			long b = st.back(); st.pop_back();
			long a = st.back(); st.pop_back();
			long r = 0;
			switch (tok[0])
			{
				case '+': r = a + b; break;
				case '-': r = a - b; break;
				case '*': r = a * b; break;
				case '/':
					if (b == 0)
						throw std::runtime_error("Error");
					r = a / b;
					break;
			}
			st.push_back(r);
		}
		else
			throw std::runtime_error("Error");
	}
	if (st.size() != 1)
		throw std::runtime_error("Error");
	return st.back();
}
