#include "menu.h"
#include <iostream>
#include <limits>

Menu::Menu() : dataLoaded(false) {}

void Menu::run() {
    while (true) {
        displayMainMenu();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        // Clear input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                loadData();
                break;
            case 2:
                if (dataLoaded) {
                    runAlgorithm();
                } else {
                    std::cout << "Please load data first!\n";
                }
                break;
            case 3:
                if (dataLoaded) {
                    displayResults();
                } else {
                    std::cout << "No results to display!\n";
                }
                break;
            case 4:
                if (dataLoaded) {
                    saveResults();
                } else {
                    std::cout << "No results to save!\n";
                }
                break;
            case 5:
                exitProgram();
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Menu::displayMainMenu() {
    std::cout << "\n=== Delivery Truck Optimization ===\n"
              << "1. Load Data\n"
              << "2. Run Algorithm\n"
              << "3. Display Results\n"
              << "4. Save Results\n"
              << "5. Exit\n";
}

void Menu::loadData() {
    // TODO: Implement data loading
    std::cout << "Data loading functionality to be implemented.\n";
    dataLoaded = true;
}

void Menu::runAlgorithm() {
    // TODO: Implement algorithm selection and execution
    std::cout << "Algorithm execution functionality to be implemented.\n";
}

void Menu::displayResults() {
    // TODO: Implement results display
    std::cout << "Results display functionality to be implemented.\n";
}

void Menu::saveResults() {
    // TODO: Implement results saving
    std::cout << "Results saving functionality to be implemented.\n";
}

void Menu::exitProgram() {
    std::cout << "Thank you for using the Delivery Truck Optimization program!\n";
} 