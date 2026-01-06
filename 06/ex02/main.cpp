#include "Base.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(void)
{
	std::srand(std::time(NULL));
	std::cout << "== Test aleatoire ==" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		Base* obj = generate();
		std::cout << "Object " << i + 1 << ": \n";
		identify(obj);
		identify(*obj);
		delete obj;
	}

	std::cout << "\n== Test A B C ==" << std::endl;
	
	Base* b = new A();
	Base* a = new B();
	Base* c = new C();

	std::cout << "Type A (ptr): ";
	identify(a);
	std::cout << "Type A (ref): ";
	identify(*a);

	std::cout << "Type B (ptr): ";
	identify(b);
	std::cout << "Type B (ref): ";
	identify(*b);

	std::cout << "Type C (ptr): ";
	identify(c);
	std::cout << "Type C (ref): ";
	identify(*c);

	delete a;
	delete b;
	delete c;

	std::cout << "\n== Test pointeur null ==" << std::endl;
	Base* ptr = NULL;
	identify(ptr);
	
	return 0;
}
