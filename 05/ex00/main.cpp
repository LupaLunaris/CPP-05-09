/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:38:52 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/12/31 16:16:36 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main() {
	std::cout << "\n=== Welcome to Konoha ===\n" << std::endl;

	// Valid bureaucrat
	try {
		Bureaucrat naruto("Naruto", 75);
		std::cout << naruto << std::endl;
	} catch (std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	// Too high grade
	std::cout << "\n--- Trying grade 0 ---" << std::endl;
	try {
		Bureaucrat sasuke("Sasuke", 0);
		std::cout << sasuke << std::endl;
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}

	// Too low grade
	std::cout << "\n--- Trying grade 151 ---" << std::endl;
	try {
		Bureaucrat kiba("Kiba", 151);
		std::cout << kiba << std::endl;
	} catch (std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}

	// Incrementing
	std::cout << "\n--- Shikamaru gets promoted ---" << std::endl;
	Bureaucrat shika("Shikamaru", 2);
	std::cout << shika << std::endl;
	shika.incrementGrade();
	std::cout << shika << std::endl;
	
	try {
		shika.incrementGrade(); // should fail
	} catch (std::exception &e) {
		std::cout << "Can't increment: " << e.what() << std::endl;
	}

	// Decrementing
	std::cout << "\n--- Lee gets demoted ---" << std::endl;
	Bureaucrat lee("Rock Lee", 149);
	std::cout << lee << std::endl;
	lee.decrementGrade();
	std::cout << lee << std::endl;
	
	try {
		lee.decrementGrade(); // should fail
	} catch (std::exception &e) {
		std::cout << "Can't decrement: " << e.what() << std::endl;
	}

	// Copy test
	std::cout << "\n--- Testing copy ---" << std::endl;
	Bureaucrat hinata("Hinata", 50);
	Bureaucrat hinata_copy(hinata);
	std::cout << "Original: " << hinata << std::endl;
	std::cout << "Copy: " << hinata_copy << std::endl;
	hinata_copy.incrementGrade();
	std::cout << "After modifying copy:" << std::endl;
	std::cout << "Original: " << hinata << std::endl;
	std::cout << "Copy: " << hinata_copy << std::endl;

	// Assignment test
	std::cout << "\n--- Testing assignment ---" << std::endl;
	Bureaucrat kakashi("Kakashi", 10);
	Bureaucrat ino("Ino", 100);
	std::cout << "Before: " << kakashi << " | " << ino << std::endl;
	ino = kakashi;
	std::cout << "After assignment: " << ino << std::endl;

	// Boundaries
	std::cout << "\n--- Edge cases ---" << std::endl;
	try {
		Bureaucrat hokage("Hokage", 1);
		Bureaucrat genin("Genin", 150);
		std::cout << hokage << std::endl;
		std::cout << genin << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n=== Goodbye from Konoha ===\n" << std::endl;
	return 0;
}
