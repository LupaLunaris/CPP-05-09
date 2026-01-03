#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp" 
#include "PresidentialPardonForm.hpp"
#include <iostream>

static AForm* createShrubberyForm(std::string const &target) {
	return new ShrubberyCreationForm(target);
}

static AForm* createRobotomyForm(std::string const &target) {
	return new RobotomyRequestForm(target);
}

static AForm* createPresidentialForm(std::string const &target) {
	return new PresidentialPardonForm(target);
}

const FormCreator Intern::_creators[] = {
	{"shrubbery creation", createShrubberyForm},
	{"robotomy request", createRobotomyForm}, 
	{"presidential pardon", createPresidentialForm}
};

Intern::Intern(Intern const &src) {
	std::cout << "Copy constructor called for Intern" << std::endl;
	*this = src;
}

Intern& Intern::operator=(Intern const &src) {
	std::cout << "Assignment operator called for Intern" << std::endl;
	(void)src;
	return *this;
}

//const int Intern::_nbCreators = 3;

Intern::Intern() {
	std::cout << "Constructor called for Intern" << std::endl;
}

Intern::~Intern() {
	std::cout << "Destructor called for Intern" << std::endl;
}

AForm* Intern::makeForm(std::string const &formName, std::string const &target) {
	for (int i = 0; i < 3; i++) {
		if (_creators[i].name == formName) {
			std::cout << "Intern creates " << formName << std::endl;
			return _creators[i].createFunction(target);
		}
	}
	
	std::cout << "Error: Unknown form name '" << formName << "'" << std::endl;
	return NULL;
}
