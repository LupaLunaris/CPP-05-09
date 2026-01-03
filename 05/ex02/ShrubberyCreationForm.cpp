#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target) {
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
	: AForm(other), _target(other._target) {
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
}

const std::string &ShrubberyCreationForm::getTarget() const {
	return _target;
}

void ShrubberyCreationForm::executeAction() const {

	std::string filename = _target + "_shrubbery";
	std::ofstream file(filename.c_str());

	if (!file) {
		throw std::runtime_error("Could not create file");
	}

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
