#include "common.h"
#include <algorithm>
#include <vector>

Solution solveGreedy(const std::vector<Pallet>& pallets, const std::vector<Truck>& trucks) {
    Solution solution;
    solution.algorithmName = "Greedy";
    
    // Sort pallets by volume (largest first)
    std::vector<Pallet> sortedPallets = pallets;
    std::sort(sortedPallets.begin(), sortedPallets.end(),
              [](const Pallet& a, const Pallet& b) {
                  return calculateVolume(a) > calculateVolume(b);
              });
    
    // Initialize trucks
    solution.trucks = trucks;
    
    // Try to fit each pallet into the first truck that can accommodate it
    for (const auto& pallet : sortedPallets) {
        bool placed = false;
        
        for (auto& truck : solution.trucks) {
            // Check if pallet fits in truck
            if (pallet.width <= truck.maxWidth &&
                pallet.length <= truck.maxLength &&
                pallet.height <= truck.maxHeight &&
                pallet.weight <= truck.maxWeight) {
                
                // Add pallet to truck
                truck.loadedPallets.push_back(pallet);
                placed = true;
                break;
            }
        }
        
        // If pallet couldn't be placed, we might need to add a new truck
        // This is a simplified version - in practice, you might want to
        // implement more sophisticated placement strategies
    }
    
    // Calculate total utilization
    solution.totalUtilization = 0.0;
    for (const auto& truck : solution.trucks) {
        solution.totalUtilization += calculateUtilization(truck);
    }
    solution.totalUtilization /= solution.trucks.size();
    
    return solution;
}

// Implementation of utility functions from common.h
double calculateVolume(const Pallet& pallet) {
    return pallet.width * pallet.length * pallet.height;
}

double calculateVolume(const Truck& truck) {
    return truck.maxWidth * truck.maxLength * truck.maxHeight;
}

double calculateUtilization(const Truck& truck) {
    double totalPalletVolume = 0.0;
    for (const auto& pallet : truck.loadedPallets) {
        totalPalletVolume += calculateVolume(pallet);
    }
    return totalPalletVolume / calculateVolume(truck);
} 