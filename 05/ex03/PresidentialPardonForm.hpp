#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"
#include <iostream>


class PresidentialPardonForm : public AForm {
private:
	std::string _target;

protected:
	virtual void executeAction() const;

public:
	PresidentialPardonForm(const std::string &target);
	PresidentialPardonForm(const PresidentialPardonForm &other);
	PresidentialPardonForm &operator=(const PresidentialPardonForm &other);
	virtual ~PresidentialPardonForm();

	const std::string &getTarget() const;
};

#endif
