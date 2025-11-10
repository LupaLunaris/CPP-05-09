/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:38:52 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/11/10 17:02:53 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
	
	std::cout << "=== Creating Konoha ===\n" << std::endl;
	    // ========== TEST 1: Valid construction ==========
    std::cout << "=== TEST 1: Valid construction ===\n";
    try {
        Bureaucrat naruto("Naruto", 75);
        std::cout << naruto << std::endl;
    } catch (std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // ========== TEST 2: Grade too high (< 1) ==========
    std::cout << "\n=== TEST 2: Grade too high (0) ===\n";
    try {
        Bureaucrat sasuke("Sasuke", 0);
        std::cout << sasuke << std::endl;  // Ne devrait jamais print
    } catch (std::exception &e) {
        std::cout << "✓ Exception caught: " << e.what() << std::endl;
    }

    // ========== TEST 3: Grade too low (> 150) ==========
    std::cout << "\n=== TEST 3: Grade too low (151) ===\n";
    try {
        Bureaucrat kiba("Kiba", 151);
        std::cout << kiba << std::endl;  // Ne devrait jamais print
    } catch (std::exception &e) {
        std::cout << "✓ Exception caught: " << e.what() << std::endl;
    }

    // ========== TEST 4: Increment normal ==========
    std::cout << "\n=== TEST 4: Increment (2 -> 1) ===\n";
    Bureaucrat shika("Shikamaru", 2);
    std::cout << "Before: " << shika << std::endl;
    shika.incrementGrade();
    std::cout << "After:  " << shika << std::endl;

    // ========== TEST 5: Increment beyond limit ==========
    std::cout << "\n=== TEST 5: Increment beyond limit (1 -> 0) ===\n";
    try {
        shika.incrementGrade();  // Devrait throw
        std::cout << "ERROR: No exception thrown!" << std::endl;
    } catch (std::exception &e) {
        std::cout << "✓ Exception caught: " << e.what() << std::endl;
    }
    std::cout << "Grade after failed increment: " << shika << std::endl;

    // ========== TEST 6: Decrement normal ==========
    std::cout << "\n=== TEST 6: Decrement (149 -> 150) ===\n";
    Bureaucrat lee("Rock Lee", 149);
    std::cout << "Before: " << lee << std::endl;
    lee.decrementGrade();
    std::cout << "After:  " << lee << std::endl;

    // ========== TEST 7: Decrement beyond limit ==========
    std::cout << "\n=== TEST 7: Decrement beyond limit (150 -> 151) ===\n";
    try {
        lee.decrementGrade();  // Devrait throw
        std::cout << "ERROR: No exception thrown!" << std::endl;
    } catch (std::exception &e) {
        std::cout << "✓ Exception caught: " << e.what() << std::endl;
    }
    std::cout << "Grade after failed decrement: " << lee << std::endl;

    // ========== TEST 8: Copy constructor ==========
    std::cout << "\n=== TEST 8: Copy constructor ===\n";
    Bureaucrat hinata("Hinata", 50);
    Bureaucrat hinata_copy(hinata);
    std::cout << "Original: " << hinata << std::endl;
    std::cout << "Copy:     " << hinata_copy << std::endl;
    
    std::cout << "Modifying copy's grade...\n";
    hinata_copy.incrementGrade();
    std::cout << "Original: " << hinata << std::endl;
    std::cout << "Copy:     " << hinata_copy << " (should be 49)" << std::endl;

    // ========== TEST 9: Assignment operator ==========
    std::cout << "\n=== TEST 9: Assignment operator ===\n";
    Bureaucrat kakashi("Kakashi", 10);
    Bureaucrat ino("Ino", 100);
    std::cout << "Before assignment:\n";
    std::cout << "  kakashi: " << kakashi << std::endl;
    std::cout << "  ino:     " << ino << std::endl;
    
    ino = kakashi;
    std::cout << "After ino = kakashi:\n";
    std::cout << "  kakashi: " << kakashi << std::endl;
    std::cout << "  ino:     " << ino << " (name unchanged, grade copied)" << std::endl;

    // ========== TEST 10: Operator<< in different contexts ==========
    std::cout << "\n=== TEST 10: Operator<< ===\n";
    Bureaucrat sakura("Sakura", 42);
    std::cout << "Direct: " << sakura << std::endl;
    std::cout << "In sentence: Hello, " << sakura << "!" << std::endl;

    // ========== TEST 11: Boundary values ==========
    std::cout << "\n=== TEST 11: Boundary values ===\n";
    try {
        Bureaucrat min("MinGrade", 150);
        Bureaucrat max("MaxGrade", 1);
        std::cout << "✓ " << min << std::endl;
        std::cout << "✓ " << max << std::endl;
    } catch (std::exception &e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }

	std::cout << "=== TEST 12: Valid form creation ===\n";
	Form missionA("Mission A", 50, 25);
	std::cout << missionA << std::endl;

	// Test 13: Grade too high for signing
	std::cout << "\n=== TEST 13: Grade too high for form ===\n";
	try {
	    Form impossible("Impossible", 0, 50);
	} catch (std::exception &e) {
    	std::cout << "✓ Exception: " << e.what() << std::endl;
	}

// Test 14: Successful signing
std::cout << "\n=== TEST 14: Successful signing ===\n";
Bureaucrat hokage("Hokage", 5);
Form scroll("Scroll", 10, 5);
hokage.signForm(scroll);  // ✅ Succès

// Test 15: Grade too low to sign
std::cout << "\n=== TEST 15: Grade too low to sign ===\n";
Bureaucrat genin("Genin", 100);
Form scroll2("Scroll2", 10, 5);  // 👈 NOUVEAU FORM non signé !
genin.signForm(scroll2);  // ❌ Grade trop bas

// Test 16: Already signed
std::cout << "\n=== TEST 16: Already signed ===\n";
hokage.signForm(scroll);  // ❌ Déjà signé (scroll du TEST 14)


	return 0;
}
