#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <cstdlib>
#include <ctime>

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

void RobotomyRequestForm::execute(Bureaucrat const & executor) const {
    // Vérifications dans la classe de base ou ici
    if (!isSigned()) {
        throw std::runtime_error("Form not signed!");
    }
    if (executor.getGrade() > getGradeExe()) {
        throw GradeTooLowException();
    }
    
    // Bruits de perceuse
    std::cout << "* BZZZZT * DRILLING NOISES * BZZZZT *" << std::endl;
    
    // 50% de chance de succès
    std::srand(std::time(0));
    if (std::rand() % 2) {
        std::cout << _target << " has been robotomized successfully!" << std::endl;
    } else {
        std::cout << "Robotomy of " << _target << " failed!" << std::endl;
    }
}

const std::string &RobotomyRequestForm::getTarget() const {
    return _target;
}
