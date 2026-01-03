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
	
	protected:
			virtual void executeAction() const = 0;

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
				const char* what() const throw();
		};
		
		class GradeTooLowException : public std::exception {
			public:
				const char* what() const throw();
		};

		class FormAlreadySignedException : public std::exception {
			public:
				const char* what() const throw();
		};

		class FormNotSignedException : public std::exception {
    		public:
        		const char* what() const throw();
    };
	
		void beSigned(Bureaucrat &bureaucrat);

		void execute(Bureaucrat const &executor) const;
} ;

std::ostream &operator<<(std::ostream &out, const AForm &AForm);

#endif