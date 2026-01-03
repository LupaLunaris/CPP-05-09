#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

int main() {
	std::cout << "\n=== Creating Intern ===" << std::endl;
	Intern intern;
	
	std::cout << "\n=== Valid Forms ===" << std::endl;
	
	AForm* form1 = intern.makeForm("shrubbery creation", "Home");
	AForm* form2 = intern.makeForm("robotomy request", "Bender");
	AForm* form3 = intern.makeForm("presidential pardon", "Arthur");
	
	std::cout << "\n=== Invalid Form ===" << std::endl;
	
	std::cout << "\n=== Testing a form ===" << std::endl;
	
	if (form1) {
		Bureaucrat bob("Bob", 1);
		bob.signForm(*form1);
		bob.executeForm(*form1);
	}
	
	std::cout << "\n=== Cleanup ===" << std::endl;
	
	delete form1;
	delete form2;
	delete form3;
	
	return 0;
}
