#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
    PmergeMe pm;
    if (!pm.run(argc, argv))
        return 1;
    return 0;
}

// ./PmergeMe $(shuf -i 1-100000 -n 3000)