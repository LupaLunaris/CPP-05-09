#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	void run(int argc, char** argv);

private:
	std::vector<int> _vec;
	std::deque<int>  _deq;

	void parseArgs(int argc, char** argv);

	void printBefore() const;
	void printAfter(const std::vector<int>& sorted) const;

	void sortVectorFordJohnson(std::vector<int>& v);
	void sortDequeFordJohnson(std::deque<int>& d);

	static bool isStrictPositiveInt(const std::string& s);
};

#endif
