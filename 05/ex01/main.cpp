/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:38:52 by Jpaulis           #+#    #+#             */
/*   Updated: 2026/01/02 11:17:29 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    std::cout << "=== Creating Konoha ===\n" << std::endl;

    // Basic bureaucrats for testing
    std::cout << "--- Creating bureaucrats ---" << std::endl;
    Bureaucrat naruto("Naruto", 1);
    Bureaucrat sasuke("Sasuke",2);
    Bureaucrat sakura("Sakura", 150);
    std::cout << naruto << std::endl;
    std::cout << sasuke << std::endl;
    std::cout << sakura << std::endl;

    // Valid form creation
    std::cout << "\n--- Valid form creation ---" << std::endl;
    try {
        Form missionA("Mission A", 50, 25);
        std::cout << missionA << std::endl;
    } catch (std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Form grade too high
    std::cout << "\n--- Form grade too high (0) ---" << std::endl;
    try {
        Form impossible("Impossible Mission", 0, 50);
		std::cout << impossible << std::endl;
    } catch (std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Form grade too low
    std::cout << "\n--- Form grade too low (151) ---" << std::endl;
    try {
        Form tooEasy("Too Easy", 151, 100);
		std::cout << tooEasy << std::endl;
    } catch (std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Succesful signing (high rank)
    std::cout << "\n--- Hokage signs scroll ---" << std::endl;
    Form scroll("Secret Scroll", 10, 5);
    std::cout << "Before: " << scroll << std::endl;
    sasuke.signForm(scroll);  // Grade 2, can sign grade 10
    std::cout << "After:  " << scroll << std::endl;

    // Grade too low to sign
    std::cout << "\n--- Genin tries to sign importent form ---" << std::endl;
    Form importantForm("Hokage Orders", 10, 5);
    std::cout << "Before: " << importantForm << std::endl;
    sakura.signForm(importantForm);  // Grade 150, cant sign grade 10
    std::cout << "After:  " << importantForm << std::endl;

    // Boundary test - exactly at limit
    std::cout << "\n--- Exact grade match ---" << std::endl;
    Bureaucrat chunnin("Shikamaru", 50);
    Form examForm("Chunin Exam", 50, 30);
    std::cout << chunnin << std::endl;
    std::cout << examForm << std::endl;
    chunnin.signForm(examForm);  // Should work
    std::cout << examForm << std::endl;

    // Alredy signed form
    std::cout << "\n--- Trying to sign already signed form ---" << std::endl;
    naruto.signForm(scroll);  // scroll was signed by sasuke earlier

    std::cout << "\n=== Goodbye from Konoha ===\n" << std::endl;
    return 0;
}
