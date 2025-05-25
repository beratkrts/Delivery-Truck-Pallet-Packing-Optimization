void Menu::displayResults(const std::string& algorithmName) {
    auto it = results.find(algorithmName);
    if (it == results.end()) {
        std::cout << "\nNo results found for " << algorithmName << ".\n";
        return;
    }

    const Solution& solution = it->second;
    std::cout << "\n=== Results for " << solution.algorithmName << " ===\n";
    std::cout << "Truck Capacity: " << solution.truck.capacity << " kg\n";
    std::cout << "Max Pallets: " << solution.truck.maxPallets << "\n";
    std::cout << "Total Profit: $" << solution.totalProfit << "\n";
    std::cout << "Execution Time: " << solution.executionTime << " seconds\n";
    
    if (solution.terminated) {
        std::cout << "\n⚠️  Algorithm was terminated due to time limit!\n";
        std::cout << "Estimated total execution time: " << solution.estimatedTotalTime << " seconds\n";
        std::cout << "This is approximately " << solution.estimatedTotalTime / 3600.0 << " hours\n";
        std::cout << "Note: Results shown are the best solution found before termination\n";
    }
    
    std::cout << "\nSelected Pallets:\n";
    std::cout << std::setw(5) << "ID" << std::setw(15) << "Weight" << std::setw(15) << "Profit" << "\n";
    std::cout << std::string(35, '-') << "\n";
    
    for (const auto& pallet : solution.selectedPallets) {
        std::cout << std::setw(5) << pallet.id 
                  << std::setw(15) << pallet.weight 
                  << std::setw(15) << pallet.profit << "\n";
    }
    std::cout << "\n";
}

void Menu::displayAllResults() {
    if (results.empty()) {
        std::cout << "\nNo results available.\n";
        return;
    }

    std::cout << "\n=== Comparison of All Results ===\n";
    std::cout << std::setw(20) << "Algorithm" 
              << std::setw(15) << "Profit" 
              << std::setw(15) << "Time (s)" 
              << std::setw(15) << "Pallets" << "\n";
    std::cout << std::string(65, '-') << "\n";

    for (const auto& [name, solution] : results) {
        std::cout << std::setw(20) << name 
                  << std::setw(15) << solution.totalProfit 
                  << std::setw(15) << solution.executionTime 
                  << std::setw(15) << solution.selectedPallets.size() << "\n";
        
        if (solution.terminated) {
            std::cout << std::setw(20) << " " 
                      << "⚠️ Terminated - Est. time: " 
                      << std::fixed << std::setprecision(2)
                      << solution.estimatedTotalTime << "s ("
                      << solution.estimatedTotalTime / 3600.0 << "h)\n";
        }
    }
    std::cout << "\n";
} 