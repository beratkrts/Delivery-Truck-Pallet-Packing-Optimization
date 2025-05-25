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
        std::cout << "\nEnter your choice (1-8): ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "❌ Invalid input. Please enter a number between 1 and 8.\n";
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                selectDataset();
                break;
            case 2:
                if (dataLoaded) {
                    selectAlgorithm();
                } else {
                    std::cout << "❌ Please load data first!\n";
                }
                break;
            case 3:
                if (dataLoaded) {
                    std::cout << "\n🚀 Running " << getAlgorithmName(currentAlgorithm) << " algorithm...\n";
                    runAlgorithm();
                } else {
                    std::cout << "❌ Please load data first!\n";
                }
                break;
            case 4:
                if (dataLoaded) {
                    runAllAlgorithms();
                } else {
                    std::cout << "❌ Please load data first!\n";
                }
                break;
            case 5:
                if (dataLoaded) {
                    displayResults();
                } else {
                    std::cout << "❌ No results to display! Please run some algorithms first.\n";
                }
                break;
            case 6:
                if (dataLoaded) {
                    clearData();
                } else {
                    std::cout << "❌ No data to clear!\n";
                }
                break;
            case 7:
                displayHelp();
                break;
            case 8:
                exitProgram();
                return;
            default:
                std::cout << "❌ Invalid choice. Please enter a number between 1 and 8.\n";
        }
    }
}

void Menu::displayMainMenu() {
    std::cout << "\n╔════════════════════════════════════════╗\n"
              << "║      Delivery Truck Optimization       ║\n"
              << "╠════════════════════════════════════════╣\n"
              << "║ 1. Select and Load Dataset             ║\n"
              << "║ 2. Select Algorithm                    ║\n"
              << "║ 3. Run Selected Algorithm              ║\n"
              << "║ 4. Run All Algorithms                  ║\n"
              << "║ 5. Display Results                     ║\n"
              << "║ 6. Clear Data                          ║\n"
              << "║ 7. Help                                ║\n"
              << "║ 8. Exit                                ║\n"
              << "╚════════════════════════════════════════╝\n";
    
    if (dataLoaded) {
        std::cout << "\n📦 Current Status:\n";
        displayDatasetInfo();
        std::cout << "🔧 Selected Algorithm: " << getAlgorithmName(currentAlgorithm) << "\n";
    } else {
        std::cout << "\n⚠️  Please select and load a dataset first!\n";
    }
}

void Menu::selectAlgorithm() {
    std::cout << "\n╔════════════════════════════════════════╗\n"
              << "║         Available Algorithms           ║\n"
              << "╠════════════════════════════════════════╣\n"
              << "║ 1. Greedy                             ║\n"
              << "║    - Fast but may not be optimal      ║\n"
              << "║ 2. Brute Force                        ║\n"
              << "║    - Optimal but slow for large sets  ║\n"
              << "║ 3. Dynamic Programming                ║\n"
              << "║    - Efficient for medium datasets    ║\n"
              << "║ 4. Integer Linear Programming         ║\n"
              << "║    - Optimal solution using OR-Tools  ║\n"
              << "╚════════════════════════════════════════╝\n";
    
    int choice;
    std::cout << "\nSelect algorithm (1-" << MAX_ALGORITHMS << "): ";
    if (!(std::cin >> choice) || choice < 1 || choice > MAX_ALGORITHMS) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "❌ Invalid algorithm selection. Please enter a number between 1 and " << MAX_ALGORITHMS << ".\n";
        return;
    }
    
    currentAlgorithm = choice;
    std::cout << "✅ Selected algorithm: " << getAlgorithmName(currentAlgorithm) << "\n";
}

std::string Menu::getAlgorithmName(int algorithmNumber) const {
    switch (algorithmNumber) {
        case 1: return "Greedy";
        case 2: return "Brute Force";
        case 3: return "Dynamic Programming";
        case 4: return "Integer Linear Programming";
        default: return "Unknown";
    }
}

void Menu::selectDataset() {
    std::cout << "\n╔════════════════════════════════════════╗\n"
              << "║         Available Datasets             ║\n"
              << "╠════════════════════════════════════════╣\n";
    
    for (int i = 1; i <= MAX_DATASETS; ++i) {
        std::cout << "║ " << std::setw(2) << i << ". Dataset " << std::setw(2) << i 
                  << std::string(25, ' ') << "║\n";
    }
    std::cout << "╚════════════════════════════════════════╝\n";
    
    int choice;
    std::cout << "\nSelect dataset (1-" << MAX_DATASETS << "): ";
    if (!(std::cin >> choice) || choice < 1 || choice > MAX_DATASETS) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "❌ Invalid dataset selection. Please enter a number between 1 and " << MAX_DATASETS << ".\n";
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
    
    return true;
}

void Menu::displayDatasetInfo() const {
    std::cout << "\nCurrent Dataset: " << currentDataset << "\n";
    std::cout << "Truck Capacity: " << std::fixed << std::setprecision(2) << truck.capacity << " kg\n";
    std::cout << "Total Available Pallets: " << pallets.size() << "\n";
}

std::string Menu::getDatasetPath(int datasetNumber) const {
    return "datasets/TruckAndPallets_" +
           std::string(datasetNumber < 10 ? "0" : "") + 
           std::to_string(datasetNumber) + ".csv";
}

void Menu::clearData() {
    pallets.clear();
    truck = Truck();
    algorithmResults.clear();
    dataLoaded = false;
    std::cout << "✅ Data and results cleared successfully.\n";
}

void Menu::runAlgorithm() {
    Solution solution;
    switch (currentAlgorithm) {
        case 1:
            solution = solveGreedy(pallets, {truck});
            break;
        case 2:
            solution = solveBruteForce(pallets, {truck});
            break;
        case 3:
            solution = solveDP(pallets, {truck});
            break;
        case 4:
            solution = solveILP(pallets, {truck});
            break;
        default:
            std::cout << "Invalid algorithm selection!\n";
            return;
    }
    
    // Store the result
    algorithmResults[currentAlgorithm] = solution;
    
    std::cout << "\n✅ Algorithm completed successfully!\n";
    std::cout << "\n📊 Current Results:\n";
    displaySingleResult(solution);
}

void Menu::displaySingleResult(const Solution& solution) const {
    std::cout << "\n╔════════════════════════════════════════════════════╗\n"
              << "║              Detailed Results                      ║\n"
              << "╠════════════════════════════════════════════════════╣\n"
              << "║ Algorithm: " << std::setw(40) << std::left << solution.algorithmName << "║\n"
              << "║ Truck Capacity: " << std::setw(32) << std::fixed << std::setprecision(2) << solution.truck.capacity << "kg ║\n"
              << "║ Total Profit: $" << std::setw(36) << std::fixed << std::setprecision(2) << solution.totalProfit << "║\n"
              << "║ Execution Time: " << std::setw(32) << std::fixed << std::setprecision(2) << solution.executionTime << "ms ║\n";

    if (solution.terminated) {
        std::cout << "╠════════════════════════════════════════════════════╣\n"
                  << "║ !!!Algorithm terminated at 30s limit!!!            ║\n"
                  << "║ Estimated total time: " << std::setw(27) << std::fixed << std::setprecision(2) << solution.estimatedTotalTime << "s ║\n"
                  << "║ (approximately " << std::setw(33) << std::fixed << std::setprecision(2) << solution.estimatedTotalTime / 3600.0 << "h) ║\n"
                  << "║ Results shown are best found so far                ║\n";
    }

    std::cout << "╠════════════════════════════════════════════════════╣\n"
              << "║ Selected Pallets:                                  ║\n"
              << "║ ID    Weight          Profit                       ║\n"
              << "╠════════════════════════════════════════════════════╣\n";

    for (const auto& pallet : solution.selectedPallets) {
        std::cout << "║ " << std::setw(6) << pallet.id
                  << std::setw(19) << std::fixed << std::setprecision(2) << pallet.weight
                  << std::setw(8) << std::fixed << std::setprecision(2) << pallet.profit
                  << std::string(18, ' ') << "║\n";
    }
    std::cout << "╚════════════════════════════════════════════════════╝\n\n";
}

void Menu::displayResults() {
    if (algorithmResults.empty()) {
        std::cout << "❌ No results available! Please run some algorithms first.\n";
        return;
    }

    std::cout << "\n╔═════════════════════════════════════════════════════════════════════════════════╗\n"
              << "║                               Comparison Results                                ║\n"
              << "╠═════════════════════════════════════════════════════════════════════════════════╣\n"
              << "║ Algorithm                           Profit                           Time (ms)  ║\n"
              << "╠═════════════════════════════════════════════════════════════════════════════════╣\n";

    for (const auto& [algoNum, solution] : algorithmResults) {
        std::cout << "║ " << std::setw(26) << std::left << getAlgorithmName(algoNum)
                  << std::setw(17) << std::right << std::fixed << std::setprecision(2) << solution.totalProfit
                  << std::setw(34) << std::fixed << std::setprecision(2) << solution.executionTime << "   ║\n";
        
        // Show termination info for brute force
        if (solution.terminated) {
            std::cout << "║ ⚠ Terminated at 30s -               Estimated Time: "
                      << std::setw(26) << std::fixed << std::setprecision(2)
                      << solution.estimatedTotalTime << "s ║\n";
        }
    }
    std::cout << "╚═════════════════════════════════════════════════════════════════════════════════╝\n\n";

    // Ask if user wants to see detailed results
    std::cout << "Would you like to see detailed results for a specific algorithm? (y/n): ";
    char choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 'y' || choice == 'Y') {
        std::cout << "\nSelect algorithm number (1-" << MAX_ALGORITHMS << "): ";
        int algoChoice;
        if (std::cin >> algoChoice && algoChoice >= 1 && algoChoice <= MAX_ALGORITHMS) {
            auto it = algorithmResults.find(algoChoice);
            if (it != algorithmResults.end()) {
                displaySingleResult(it->second);
            } else {
                std::cout << "❌ No results available for this algorithm.\n";
            }
        } else {
            std::cout << "❌ Invalid algorithm selection.\n";
        }
    }
}

void Menu::exitProgram() {
    std::cout << "Thank you for using the Delivery Truck Optimization program!\n";
}

void Menu::displayHelp() {
    std::cout << "\n╔════════════════════════════════════════╗\n"
              << "║             Help Guide                 ║\n"
              << "╠════════════════════════════════════════╣\n"
              << "║ 1. Select Dataset                      ║\n"
              << "║    - Choose from available datasets    ║\n"
              << "║ 2. Select Algorithm                    ║\n"
              << "║    - Pick an algorithm to use          ║\n"
              << "║ 3. Run Selected Algorithm              ║\n"
              << "║    - Execute current algorithm         ║\n"
              << "║ 4. Run All Algorithms                  ║\n"
              << "║    - Execute all algorithms            ║\n"
              << "║ 5. Display Results                     ║\n"
              << "║    - View comparison of results        ║\n"
              << "║ 6. Clear Data                          ║\n"
              << "║    - Reset current dataset/algorithm   ║\n"
              << "║ 7. Help                                ║\n"
              << "║    - Show this help guide              ║\n"
              << "║ 8. Exit                                ║\n"
              << "║    - Close the program                 ║\n"
              << "╚════════════════════════════════════════╝\n\n"
              << "📝 Note: You must select a dataset before running algorithms.\n"
              << "📊 Tip: Use 'Run All Algorithms' to compare all solutions at once.\n";
}

void Menu::runAllAlgorithms() {
    std::cout << "\n🚀 Running all algorithms...\n\n";
    
    // Clear previous results
    algorithmResults.clear();
    
    // Run each algorithm
    for (int algo = 1; algo <= MAX_ALGORITHMS; ++algo) {
        std::cout << "Running " << getAlgorithmName(algo) << "...\n";
        currentAlgorithm = algo;
        runAlgorithm();
        std::cout << "\n";
    }
    
    std::cout << "✅ All algorithms completed!\n\n";
    displayResults();
} 