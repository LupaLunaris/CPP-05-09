#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

// Constructeur
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("ShrubberyCreationForm", 145, 137), _target(target) {
}

// Constructeur de copie
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
    : AForm(other), _target(other._target) {
}

// Opérateur d'assignation
ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
    if (this != &other) {
        AForm::operator=(other);  // Appel à l'assignation de la classe mère
        _target = other._target;
    }
    return *this;
}

// Destructeur
ShrubberyCreationForm::~ShrubberyCreationForm() {
}

// Getter
const std::string &ShrubberyCreationForm::getTarget() const {
    return _target;
}

// 🎯 LA MÉTHODE PRINCIPALE : execute()
void ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
    // 1. Vérifier si le formulaire est signé
    if (!isSigned()) {
        throw std::runtime_error("Form is not signed");
        // Ou créer une exception spécifique FormNotSignedException
    }
    
    // 2. Vérifier si le bureaucrate a le grade suffisant
    if (executor.getGrade() > getGradeExe()) {
        throw GradeTooLowException();
    }
    
    // 3. Action spécifique : créer le fichier avec les arbres ASCII
    std::string filename = _target + "_shrubbery";
    std::ofstream file(filename.c_str());
    
    if (!file) {
        throw std::runtime_error("Could not create file");
    }
    
    // 🌲 ASCII Trees !
    file << "       _-_\n";
    file << "    /~~   ~~\\\n";
    file << " /~~         ~~\\\n";
    file << "{               }\n";
    file << " \\  _-     -_  /\n";
    file << "   ~  \\\\ //  ~\n";
    file << "_- -   | | _- _\n";
    file << "  _ -  | |   -_\n";
    file << "      // \\\\\n\n";
    
    file << "         /\\\n";
    file << "        /  \\\n";
    file << "       /    \\\n";
    file << "      /______\\\n";
    file << "         ||\n";
    file << "         ||\n";
    file << "         ||\n\n";
    
    file.close();
    
    std::cout << "Shrubbery has been planted at " << _target << std::endl;
}
