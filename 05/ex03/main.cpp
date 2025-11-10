#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

int main() {
    try {
        std::cout << "=== CREATING BUREAUCRATS ===" << std::endl;
        Bureaucrat boss("Boss", 1);
        Bureaucrat intern("LowGrade", 150);
        
        std::cout << "\n=== CREATING INTERN ===" << std::endl;
        Intern someRandomIntern;
        
        std::cout << "\n=== TEST 1: CREATE SHRUBBERY FORM ===" << std::endl;
        AForm* shrub = someRandomIntern.makeForm("shrubbery creation", "garden");
        if (shrub) {
            boss.signForm(*shrub);
            boss.executeForm(*shrub);
            delete shrub;
        }
        
        std::cout << "\n=== TEST 2: CREATE ROBOTOMY FORM ===" << std::endl;
        AForm* robot = someRandomIntern.makeForm("robotomy request", "Bender");
        if (robot) {
            boss.signForm(*robot);
            boss.executeForm(*robot);
            delete robot;
        }
        
        std::cout << "\n=== TEST 3: CREATE PRESIDENTIAL FORM ===" << std::endl;
        AForm* pardon = someRandomIntern.makeForm("presidential pardon", "Arthur");
        if (pardon) {
            boss.signForm(*pardon);
            boss.executeForm(*pardon);
            delete pardon;
        }
        
        std::cout << "\n=== TEST 4: UNKNOWN FORM ===" << std::endl;
        AForm* unknown = someRandomIntern.makeForm("unknown form", "test");
        if (!unknown) {
            std::cout << "✅ Correctly handled unknown form" << std::endl;
        }
        
        std::cout << "\n=== TEST 5: INTERN CAN'T EXECUTE ===" << std::endl;
        AForm* test = someRandomIntern.makeForm("shrubbery creation", "test");
        if (test) {
            try {
                intern.executeForm(*test);  // Should fail - not signed
            } catch (std::exception& e) {
                std::cout << "Expected: " << e.what() << std::endl;
            }
            delete test;
        }
        
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}
