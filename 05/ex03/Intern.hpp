#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include <string>

struct FormCreator {
    std::string name;
    AForm* (*createFunction)(std::string target);
};

class Intern {
public:
    Intern();
    ~Intern();
    
    AForm* makeForm(std::string formName, std::string target);

private:
    static const FormCreator _creators[];
    static const int _nbCreators;
};

#endif
