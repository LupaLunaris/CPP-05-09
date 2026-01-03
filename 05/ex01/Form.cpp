/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:14:20 by Jpaulis           #+#    #+#             */
/*   Updated: 2026/01/02 11:21:26 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("Default"), _signed(false), _gradeSign(150), _gradeExe(150) {
	std::cout << "Default constructor Form called" << std::endl;
}

Form::Form(const std::string &name, const int gradeSign, const int gradeExe) : _name(name), _signed(false), _gradeSign(gradeSign), _gradeExe(gradeExe) {
	std::cout << "Constructor Form called for " << name << std::endl;
	if (_gradeSign < 1 || _gradeExe < 1)
		throw GradeTooHighException();
	if (_gradeSign > 150 || _gradeExe > 150)
		throw GradeTooLowException();
}

Form::Form(const Form &other) : _name(other._name), _signed(other._signed), _gradeSign(other._gradeSign), _gradeExe(other._gradeExe) {
	std::cout << "Copy constructor Form called" << std::endl;
}

Form& Form::operator=(const Form &other) {
	if (this != &other)
		_signed = other._signed;
	return *this;
}

Form::~Form() {
	std::cout << "Destructor Form called" << std::endl;
}

const std::string &Form::getName() const {
	return _name;
}

bool Form::isSigned() const {
	return _signed;
}

int Form::getGradeSign() const {
	return _gradeSign;
}

int Form::getGradeExe() const {
	return _gradeExe;
}

const char* Form::GradeTooHighException::what() const throw() {
	return "Grade too high!";
}

const char* Form::GradeTooLowException::what() const throw() {
	return "Grade too low!";
}

const char* Form::FormAlreadySignedException::what() const throw() {
	return "Form is already signed!";
}

void Form::beSigned(Bureaucrat &bureaucrat) {
	if (_signed)
		throw FormAlreadySignedException();
	if (bureaucrat.getGrade() > _gradeSign)
		throw GradeTooLowException();
	_signed = true;
}

std::ostream &operator<<(std::ostream &out, const Form &form) {
	out << "Form: " << form.getName()
		<< " [sign grade: " << form.getGradeSign()
		<< ", exec grade: " << form.getGradeExe()
		<< ", signed: " << (form.isSigned() ? "yes" : "no") << "]";
	return out;
}
