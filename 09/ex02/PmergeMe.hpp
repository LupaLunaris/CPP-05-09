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

	bool run(int argc, char** argv);

private:
	static void parseArgsToVector(int argc, char** argv, std::vector<int>& out);
	static void parseArgsToDeque(int argc, char** argv, std::deque<int>& out);

	void printBefore(const std::vector<int>& unsorted) const;
	void printAfter(const std::vector<int>& sorted) const;

	void sortVectorFordJohnson(std::vector<int>& v);
	void sortDequeFordJohnson(std::deque<int>& d);

	static bool isStrictPositiveInt(const std::string& s);
};

#endif
