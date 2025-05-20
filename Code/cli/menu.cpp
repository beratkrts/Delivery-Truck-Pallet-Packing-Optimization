#include "menu.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include "../algorithms/greedy.cpp"

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
    DataLoader loader;
    
    // Load truck data
    if (!loader.loadTrucks("Code/datasets/TruckAndPallets_01.csv")) {
        std::cout << "Error loading truck data!\n";
        return;
    }
    
    // Load pallet data
    if (!loader.loadPallets("Code/datasets/Pallets_01.csv")) {
        std::cout << "Error loading pallet data!\n";
        return;
    }
    
    // Store the loaded data
    trucks = loader.getTrucks();
    pallets = loader.getPallets();
    dataLoaded = true;
    
    std::cout << "Data loaded successfully!\n";
    std::cout << "Loaded " << trucks.size() << " trucks and " << pallets.size() << " pallets.\n";
}

void Menu::runAlgorithm() {
    // Run the greedy algorithm
    currentSolution = solveGreedy(pallets, trucks);
    std::cout << "Algorithm completed successfully!\n";
}

void Menu::displayResults() {
    std::cout << "\n=== Allocation Results ===\n";
    std::cout << "Algorithm: " << currentSolution.algorithmName << "\n";
    std::cout << "Total Profit: " << currentSolution.totalProfit << "\n\n";
    
    for (size_t i = 0; i < currentSolution.trucks.size(); ++i) {
        const auto& truck = currentSolution.trucks[i];
        std::cout << "Truck " << (i + 1) << ":\n";
        std::cout << "Capacity: " << truck.capacity << "\n";
        std::cout << "Max Pallets: " << truck.maxPallets << "\n";
        std::cout << "Loaded Pallets: " << truck.loadedPallets.size() << "\n";
        
        double totalWeight = 0.0;
        double totalProfit = 0.0;
        
        std::cout << "\nPallet Details:\n";
        std::cout << std::setw(8) << "ID" << std::setw(10) << "Weight" << std::setw(10) << "Profit\n";
        std::cout << std::string(28, '-') << "\n";
        
        for (const auto& pallet : truck.loadedPallets) {
            std::cout << std::setw(8) << pallet.id 
                      << std::setw(10) << pallet.weight 
                      << std::setw(10) << pallet.profit << "\n";
            totalWeight += pallet.weight;
            totalProfit += pallet.profit;
        }
        
        std::cout << std::string(28, '-') << "\n";
        std::cout << "Total Weight: " << totalWeight << "\n";
        std::cout << "Total Profit: " << totalProfit << "\n\n";
    }
}

void Menu::saveResults() {
    // TODO: Implement results saving to file
    std::cout << "Results saving functionality to be implemented.\n";
}

void Menu::exitProgram() {
    std::cout << "Thank you for using the Delivery Truck Optimization program!\n";
} 