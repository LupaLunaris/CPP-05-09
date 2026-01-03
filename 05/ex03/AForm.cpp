#include "AForm.hpp"
#include "Bureaucrat.hpp"

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

const char* AForm::GradeTooHighException::what() const throw() {
	return "Grade too high!";
}

const char* AForm::GradeTooLowException::what() const throw() {
	return "Grade too low!";
}

const char* AForm::FormAlreadySignedException::what() const throw() {
	return "Form is already signed!";
}

const char* AForm::FormNotSignedException::what() const throw() {
	return "Form is not signed!";
}

void AForm::beSigned(Bureaucrat &bureaucrat) {
	if (_signed)
		throw FormAlreadySignedException();
	if (bureaucrat.getGrade() > _gradeSign)
		throw GradeTooLowException();
	_signed = true;
}

void AForm::execute(Bureaucrat const &executor) const {
	if (!_signed)
		throw FormNotSignedException();
	if (executor.getGrade() > _gradeExe)
		throw GradeTooLowException();
	executeAction();
}

std::ostream &operator<<(std::ostream &out, const AForm &form) {
	out << "Form: " << form.getName()
		<< " [sign grade: " << form.getGradeSign()
		<< ", exec grade: " << form.getGradeExe()
		<< ", signed: " << (form.isSigned() ? "yes" : "no") << "]";
	return out;
}

AForm::~AForm() {}