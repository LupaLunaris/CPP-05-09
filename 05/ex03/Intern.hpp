#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include <string>

struct FormCreator {
	std::string name;
	AForm* (*createFunction)(std::string const &target);
};

class Intern {
public:
	Intern();
	Intern(Intern const & src);
	Intern & operator=(Intern const & rhs);
	~Intern();
	
	AForm* makeForm(std::string const &formName, std::string const &target);

private:
	static const FormCreator _creators[];
	static const int _nbCreators;
};

#endif
