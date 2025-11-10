/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:14:11 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/11/10 16:46:34 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string> 

class Bureaucrat;

class Form {
	private:
		const std::string _name;
		bool _signed;
		const int _gradeSign;
		const int _gradeExe;

	public :
		Form();
		Form(const std::string &name, const int gradeSign, const int gradeExe);
		Form(const Form &other);
		Form &operator=(const Form &other);
		~Form();
		
		const std::string getName() const;
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
} ;

std::ostream &operator<<(std::ostream &out, const Form &Form);

#endif