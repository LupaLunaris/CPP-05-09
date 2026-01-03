#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string &target) 
	: AForm("RobotomyRequestForm", 72, 45), _target(target) {
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) 
	: AForm(other), _target(other._target) {
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
}

const std::string &RobotomyRequestForm::getTarget() const {
	return _target;
}

const char* RobotomyRequestForm::RobotomyFailedException::what() const throw(){
	return "Robotomy failed";
}

void RobotomyRequestForm::executeAction() const {

	std::cout << "* BZZZZT * DRILLING NOISES * BZZZZT *" << std::endl;

	if (std::rand() % 2 == 0) {
		std::cout << _target << " has been robotomized successfully!" << std::endl;
	} else {
		std::cout << "Robotomy of " << _target << " failed!" << std::endl;
	}
}
