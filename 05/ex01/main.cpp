/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:38:52 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/09/27 17:12:34 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main() {
	
	std::cout << "=== Creating Konoha ===\n" << std::endl;
	try {
		Bureaucrat naruto("Naruto", 75);
		std::cout << naruto << std::endl;
	} catch (std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	// Too high grade
	std::cout << "\n=== Sasuke wants grade 0 ===\n";
	try {
		Bureaucrat sasuke("Sasuke", 0);
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// Too low grade  
	std::cout << "\n=== Kiba gets grade 151 ===\n";
	try {
		Bureaucrat kiba("Kiba", 151);
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// Increment test
	std::cout << "\n=== Shikamaru promotion ===\n";
	Bureaucrat shika("Shikamaru", 2);
	std::cout << shika << std::endl;
	
	shika.incrementGrade(); // 2 -> 1
	std::cout << shika << std::endl;
	
	try {
		shika.incrementGrade(); // 1 -> exception
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// Decrement test
	std::cout << "\n=== Lee demotion ===\n";
	Bureaucrat lee("Lee", 149);
	std::cout << lee << std::endl;
	
	lee.decrementGrade(); // 149 -> 150
	std::cout << lee << std::endl;
	
	try {
		lee.decrementGrade(); // 150 -> exception
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
	std::cout << "\n=== Bye Konoha ===\n"<< std::endl;

	return 0;
}
