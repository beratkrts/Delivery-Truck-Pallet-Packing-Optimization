#include "menu.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include "../algorithms/greedy.h"

Menu::Menu() : dataLoaded(false), currentDataset(1), currentAlgorithm(1) {}

void Menu::run() {
    while (true) {
        displayMainMenu();
        int choice;
        std::cout << "Enter your choice: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                selectDataset();
                break;
            case 2:
                selectAlgorithm();
                break;
            case 3:
                if (dataLoaded) {
                    runAlgorithm();
                } else {
                    std::cout << "Please load data first!\n";
                }
                break;
            case 4:
                if (dataLoaded) {
                    displayResults();
                } else {
                    std::cout << "No results to display!\n";
                }
                break;
            case 5:
                if (dataLoaded) {
                    saveResults();
                } else {
                    std::cout << "No results to save!\n";
                }
                break;
            case 6:
                clearData();
                break;
            case 7:
                exitProgram();
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Menu::displayMainMenu() {
    std::cout << "\n=== Delivery Truck Optimization ===\n"
              << "1. Select and Load Dataset\n"
              << "2. Select Algorithm\n"
              << "3. Run Algorithm\n"
              << "4. Display Results\n"
              << "5. Save Results\n"
              << "6. Clear Data\n"
              << "7. Exit\n";
    
    if (dataLoaded) {
        displayDatasetInfo();
        std::cout << "Selected Algorithm: " << getAlgorithmName(currentAlgorithm) << "\n";
    }
}

void Menu::selectAlgorithm() {
    std::cout << "\nAvailable Algorithms:\n"
              << "1. Greedy\n"
              << "2. Brute Force\n"
              << "3. Dynamic Programming\n"
              << "4. Integer Linear Programming\n"
              << "5. Backtracking\n";
    
    int choice;
    std::cout << "Select algorithm (1-" << MAX_ALGORITHMS << "): ";
    if (!(std::cin >> choice) || choice < 1 || choice > MAX_ALGORITHMS) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid algorithm selection.\n";
        return;
    }
    
    currentAlgorithm = choice;
    std::cout << "Selected algorithm: " << getAlgorithmName(currentAlgorithm) << "\n";
}

std::string Menu::getAlgorithmName(int algorithmNumber) const {
    switch (algorithmNumber) {
        case 1: return "Greedy";
        case 2: return "Brute Force";
        case 3: return "Dynamic Programming";
        case 4: return "Integer Linear Programming";
        case 5: return "Backtracking";
        default: return "Unknown";
    }
}

void Menu::selectDataset() {
    std::cout << "\nAvailable Datasets:\n";
    for (int i = 1; i <= MAX_DATASETS; ++i) {
        std::cout << i << ". Dataset " << i << "\n";
    }
    
    int choice;
    std::cout << "Select dataset (1-" << MAX_DATASETS << "): ";
    if (!(std::cin >> choice) || choice < 1 || choice > MAX_DATASETS) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid dataset selection.\n";
        return;
    }
    
    currentDataset = choice;
    loadData();
}

void Menu::loadData() {
    DataLoader loader;
    std::string truckFile = getDatasetPath(currentDataset);
    std::string palletFile = "datasets/Pallets_" + 
                            std::string(currentDataset < 10 ? "0" : "") + 
                            std::to_string(currentDataset) + ".csv";
    
    // Check if files exist
    if (!std::filesystem::exists(truckFile) || !std::filesystem::exists(palletFile)) {
        std::cout << "Error: Dataset files not found!\n";
        return;
    }
    
    // Load truck data
    if (!loader.loadTruckData(truckFile)) {
        std::cout << "Error loading truck data from " << truckFile << "!\n";
        return;
    }
    
    // Load pallet data
    if (!loader.loadPalletData(palletFile)) {
        std::cout << "Error loading pallet data from " << palletFile << "!\n";
        return;
    }
    
    // Store the loaded data
    truck = loader.getTruck();
    pallets = loader.getPallets();
    
    // Validate the loaded data
    if (!validateData()) {
        std::cout << "Data validation failed. Please check the dataset.\n";
        clearData();
        return;
    }
    
    dataLoaded = true;
    std::cout << "Data loaded successfully!\n";
    displayDatasetInfo();
}

bool Menu::validateData() const {
    if (pallets.empty()) {
        std::cout << "Error: No pallets loaded.\n";
        return false;
    }
    
    // Check for duplicate pallet IDs
    std::vector<int> palletIds;
    for (const auto& pallet : pallets) {
        if (pallet.weight <= 0) {
            std::cout << "Error: Pallet " << pallet.id << " has invalid weight.\n";
            return false;
        }
        if (pallet.profit < 0) {
            std::cout << "Error: Pallet " << pallet.id << " has negative profit.\n";
            return false;
        }
        if (std::find(palletIds.begin(), palletIds.end(), pallet.id) != palletIds.end()) {
            std::cout << "Error: Duplicate pallet ID " << pallet.id << " found.\n";
            return false;
        }
        palletIds.push_back(pallet.id);
    }
    
    // Validate truck data
    if (truck.capacity <= 0) {
        std::cout << "Error: Invalid truck capacity.\n";
        return false;
    }
    if (truck.maxPallets <= 0) {
        std::cout << "Error: Invalid maximum pallets per truck.\n";
        return false;
    }
    
    return true;
}

void Menu::displayDatasetInfo() const {
    std::cout << "\nCurrent Dataset: " << currentDataset << "\n";
    std::cout << "Truck Capacity: " << truck.capacity << "\n";
    std::cout << "Max Pallets: " << truck.maxPallets << "\n";
    std::cout << "Loaded Pallets: " << currentSolution.selectedPallets.size() << "\n";
}

std::string Menu::getDatasetPath(int datasetNumber) const {
    return "datasets/TruckAndPallets_" +
           std::string(datasetNumber < 10 ? "0" : "") + 
           std::to_string(datasetNumber) + ".csv";
}

void Menu::clearData() {
    pallets.clear();
    truck = Truck();
    dataLoaded = false;
    std::cout << "Data cleared successfully.\n";
}

void Menu::runAlgorithm() {
    switch (currentAlgorithm) {
        case 1:
            currentSolution = solveGreedy(pallets, {truck});
            break;
        case 2:
            currentSolution = solveBruteForce(pallets, {truck});
            break;
        case 3:
            currentSolution = solveDP(pallets, {truck});
            break;
        case 4:
            currentSolution = solveILP(pallets, {truck});
            break;
        case 5:
            currentSolution = solveBacktracking(pallets, {truck});
            break;
        default:
            std::cout << "Invalid algorithm selection!\n";
            return;
    }
    std::cout << "Algorithm completed successfully!\n";
}

void Menu::displayResults() {
    std::cout << "\n=== Allocation Results ===\n";
    std::cout << "Algorithm: " << currentSolution.algorithmName << "\n";
    std::cout << "Total Profit: " << currentSolution.totalProfit << "\n\n";
    

    Truck truck = currentSolution.truck;
    std::cout << "Truck:\n";
    std::cout << "Capacity: " << truck.capacity << "\n";
    std::cout << "Max Pallets: " << truck.maxPallets << "\n";
    std::cout << "Loaded Pallets: " << truck.loadedPallets.size() << "\n";
        
    double totalWeight = 0.0;
    double totalProfit = 0.0;
        
    std::cout << "\nPallet Details:\n";
    std::cout << std::setw(8) << "ID" << std::setw(10) << "Weight" << std::setw(10) << "Profit\n";
    std::cout << std::string(28, '-') << "\n";
        
    for (const auto& pallet : currentSolution.selectedPallets) {
        std::cout << std::setw(8) << pallet.id
            << std::setw(10) << pallet.weight
            << std::setw(10) << pallet.profit << "\n";
        totalWeight += pallet.weight;
        totalProfit += pallet.profit;
    }
        
    std::cout << std::string(28, '-') << "\n";
    std::cout << "Total Weight: " << totalWeight << "\n";
    std::cout << "Total Profit: " << totalProfit << "\n\n";
    std::cout << "Execution Time: " << currentSolution.executionTime << "\n";

}

void Menu::saveResults() {
    if (!dataLoaded) {
        std::cout << "No results to save!\n";
        return;
    }
    
    std::string filename = "results_dataset_" + std::to_string(currentDataset) + ".txt";
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "Error: Could not open file for writing.\n";
        return;
    }
    
    file << "=== Allocation Results ===\n";
    file << "Dataset: " << currentDataset << "\n";
    file << "Algorithm: " << currentSolution.algorithmName << "\n";
    file << "Total Profit: " << currentSolution.totalProfit << "\n\n";
    

        Truck truck = currentSolution.truck;
        file << "Truck:\n";
        file << "Capacity: " << truck.capacity << "\n";
        file << "Max Pallets: " << truck.maxPallets << "\n";
        file << "Loaded Pallets: " << truck.loadedPallets.size() << "\n\n";
        
        file << "Pallet Details:\n";
        file << std::setw(8) << "ID" << std::setw(10) << "Weight" << std::setw(10) << "Profit\n";
        file << std::string(28, '-') << "\n";
        
        for (const auto& pallet : currentSolution.selectedPallets) {
            file << std::setw(8) << pallet.id 
                 << std::setw(10) << pallet.weight 
                 << std::setw(10) << pallet.profit << "\n";
        }
        file << "\n";

    
    file.close();
    std::cout << "Results saved to " << filename << "\n";
}

void Menu::exitProgram() {
    std::cout << "Thank you for using the Delivery Truck Optimization program!\n";
} 