#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
    PmergeMe pm;
    if (!pm.run(argc, argv))
        return 1;
    return 0;
}
