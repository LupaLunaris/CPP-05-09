#include "AForm.hpp"

AForm::AForm() : _name("default"), _signed(false), _gradeSign(150), _gradeExe(150)  {
}

AForm::AForm(const std::string &name, int gradeSign, int gradeExe)
	: _name(name), _signed(false), _gradeSign(gradeSign), _gradeExe(gradeExe) {
		if(_gradeSign < 1 || _gradeExe < 1)
			throw GradeTooHighException();
		if(_gradeSign > 150 || _gradeExe > 150)
			throw GradeTooLowException();
}

AForm::AForm(const AForm& other) : _name(other._name), _signed(other._signed),
	_gradeSign(other._gradeSign), _gradeExe(other._gradeExe) {
}

AForm& AForm::operator=(const AForm& other) {
	if (this != &other)
		_signed = other._signed;
	return *this;
}

const std::string& AForm::getName() const {
	return _name;
}

bool AForm::isSigned() const {
	return _signed;
}

int AForm::getGradeSign() const {
	return _gradeSign;
}

int AForm::getGradeExe() const {
	return _gradeExe;
}

void AForm::beSigned(Bureaucrat &bureaucrat) {
	if (bureaucrat.getGrade() > _gradeSign)
		throw GradeTooLowException();
	_signed = true;
}

std::ostream &operator<<(std::ostream &out, const AForm &form) {
    out << "Form " << form.getName() 
        << (form.isSigned() ? " (signed)" : " (not signed)")
        << ", grade required to sign: " << form.getGradeSign()
        << ", grade required to execute: " << form.getGradeExe();
    return out;
}

AForm::~AForm() {}