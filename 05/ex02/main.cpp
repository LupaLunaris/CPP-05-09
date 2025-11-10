#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
    try {
        Bureaucrat boss("Boss", 1);
        Bureaucrat intern("Intern", 150);
        
        ShrubberyCreationForm shrub("garden");
        RobotomyRequestForm robot("Bender");
        PresidentialPardonForm pardon("Arthur");
        
        boss.signForm(shrub);
        boss.executeForm(shrub);
        
        boss.signForm(robot);
        boss.executeForm(robot);
        
        boss.signForm(pardon);
        boss.executeForm(pardon);
        
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
