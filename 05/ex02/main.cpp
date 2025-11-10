#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"

int main() {
    std::cout << "=== TEST INCREMENT/DECREMENT ===" << std::endl;
    
    try {
        // Test 1: Grade normal (doit fonctionner)
        std::cout << "\n--- Test Charlie (grade 50) ---" << std::endl;
        Bureaucrat charlie("Charlie", 50);
        std::cout << "Avant increment: " << charlie << std::endl;
        charlie.incrementGrade();  // 50 → 49 (mieux)
        std::cout << "Après increment: " << charlie << std::endl;
        charlie.decrementGrade();  // 49 → 50 (retour)
        std::cout << "Après decrement: " << charlie << std::endl;
        
    } catch (std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    try {
        // Test 2: Grade parfait (doit lever exception)
        std::cout << "\n--- Test Alice (grade 1 parfait) ---" << std::endl;
        Bureaucrat alice("Alice", 1);
        std::cout << "Avant increment: " << alice << std::endl;
        alice.incrementGrade();  // ❌ Doit lever une exception !
        std::cout << "Cette ligne ne devrait jamais s'afficher" << std::endl;
        
    } catch (std::exception &e) {
        std::cout << "✅ Exception attrapée: " << e.what() << std::endl;
    }
    
    try {
        // Test 3: Grade pire (doit lever exception)
        std::cout << "\n--- Test Bob (grade 150 pire) ---" << std::endl;
        Bureaucrat bob("Bob", 150);
        std::cout << "Avant decrement: " << bob << std::endl;
        bob.decrementGrade();  // ❌ Doit lever une exception !
        std::cout << "Cette ligne ne devrait jamais s'afficher" << std::endl;
        
    } catch (std::exception &e) {
        std::cout << "✅ Exception attrapée: " << e.what() << std::endl;
    }
    
    return 0;
}
