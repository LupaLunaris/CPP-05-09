#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <string> 

class Bureaucrat;

class AForm {
	private:
		const std::string _name;
		bool _signed;
		const int _gradeSign;
		const int _gradeExe;

	public :
		AForm();
		AForm(const std::string &name, const int gradeSign, const int gradeExe);
		AForm(const AForm &other);
		AForm &operator=(const AForm &other);
		virtual ~AForm();
		
		const std::string &getName() const;
		bool isSigned() const;
		int getGradeSign() const;
		int getGradeExe() const;
		
		class GradeTooHighException : public std::exception {
			public:
    			const char* what() const throw() {
					return "Grade too high!";
				}
		};
		
		class GradeTooLowException : public std::exception {
			public:
    			const char* what() const throw() {
					return "Grade too low!";
				}
		};

		void beSigned(Bureaucrat &bureaucrat);

		virtual void execute(Bureaucrat const & executor) const = 0;
} ;

std::ostream &operator<<(std::ostream &out, const AForm &AForm);

#endif