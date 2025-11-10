#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp" 
#include "PresidentialPardonForm.hpp"
#include <iostream>

// Fonctions de création
static AForm* createShrubberyForm(std::string target) {
    return new ShrubberyCreationForm(target);
}

static AForm* createRobotomyForm(std::string target) {
    return new RobotomyRequestForm(target);
}

static AForm* createPresidentialForm(std::string target) {
    return new PresidentialPardonForm(target);
}

// Array des créateurs
const FormCreator Intern::_creators[] = {
    {"shrubbery creation", createShrubberyForm},
    {"robotomy request", createRobotomyForm}, 
    {"presidential pardon", createPresidentialForm}
};

const int Intern::_nbCreators = 3;

// Implémentations des méthodes
Intern::Intern() {
    std::cout << "Constructor called for Intern" << std::endl;
}

Intern::~Intern() {
    std::cout << "Destructor called for Intern" << std::endl;
}

AForm* Intern::makeForm(std::string formName, std::string target) {
    for (int i = 0; i < _nbCreators; i++) {
        if (_creators[i].name == formName) {
            std::cout << "Intern creates " << formName << std::endl;
            return _creators[i].createFunction(target);
        }
    }
    
    std::cout << "Error: Unknown form name '" << formName << "'" << std::endl;
    return NULL;
}
