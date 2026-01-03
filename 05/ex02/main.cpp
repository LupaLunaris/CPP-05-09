#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main() {
	std::srand(static_cast<unsigned int>(std::time(0)));
	std::cout << "Konoha Mission\n" << std::endl;

	try {
		Bureaucrat naruto("Naruto", 1);
		Bureaucrat sakura("Sakura", 45);
   		Bureaucrat shikamaru("Shikamaru", 137);
		Bureaucrat ino("Ino", 150);

		ShrubberyCreationForm treeMission("Village");
		RobotomyRequestForm medScroll("Test_med");
		PresidentialPardonForm pardonScroll("Gaara");

		std::cout << "\n--- Tree mission ---" << std::endl;
		shikamaru.signForm(treeMission);
		shikamaru.executeForm(treeMission);

		std::cout << "\n--- Medical ninja ---" << std::endl;
		sakura.signForm(medScroll);
		sakura.executeForm(medScroll);
		sakura.executeForm(medScroll);  // randomness

		// Ino too low ranked
		std::cout << "\n--- Ino tries to help ---" << std::endl;
		ShrubberyCreationForm flowers("Yamanaka_Shop");
		ino.signForm(flowers);

		// Naruto can't pardon  without signing first
		std::cout << "\n--- Hokage's mistake ---" << std::endl;
		naruto.executeForm(pardonScroll);

		std::cout << "\n--- Hokage's official pardon ---" << std::endl;
		naruto.signForm(pardonScroll);
		naruto.executeForm(pardonScroll);

		// Sakura tries pardon (not high enough rank)
		std::cout << "\n--- Sakura's attempt ---" << std::endl;
		PresidentialPardonForm another("Rock_Lee");
		sakura.signForm(another);
	} catch (std::exception &e) {
		std::cerr << "Critical error during setup: " << e.what() << std::endl;
		return 1;
	}

	std::cout << "\nBye Konoha!" << std::endl;
	return 0;
}
