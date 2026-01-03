#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

class RobotomyRequestForm : public AForm {
private:
	std::string _target;

protected:
	virtual void executeAction() const;

public:
	RobotomyRequestForm(const std::string &target);
	RobotomyRequestForm(const RobotomyRequestForm &other);
	RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
	virtual ~RobotomyRequestForm();

	const std::string &getTarget() const;
	
	class RobotomyFailedException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

#endif
