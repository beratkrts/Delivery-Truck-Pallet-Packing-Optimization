#include "common.h"
#include <algorithm>
#include <vector>
#include <iostream>

Solution solveGreedy(const std::vector<Pallet>& pallets, const std::vector<Truck>& trucks) {
    Solution solution;
    solution.algorithmName = "Greedy";
    
    // Sort pallets by profit-to-weight ratio (highest first)
    std::vector<Pallet> sortedPallets = pallets;
    std::sort(sortedPallets.begin(), sortedPallets.end(),
              [](const Pallet& a, const Pallet& b) {
                  return (a.profit / a.weight) > (b.profit / b.weight);
              });
    
    // Initialize trucks
    solution.trucks = trucks;
    
    // For each truck
    for (auto& truck : solution.trucks) {
        double currentWeight = 0.0;
        int currentPallets = 0;
        
        // Try to fit pallets into the truck
        for (const auto& pallet : sortedPallets) {
            // Check if adding this pallet would exceed capacity or pallet count
            if (currentWeight + pallet.weight <= truck.capacity && 
                currentPallets < truck.maxPallets) {
                
                // Add pallet to truck
                truck.loadedPallets.push_back(pallet);
                currentWeight += pallet.weight;
                currentPallets++;
            }
        }
    }
    
    // Calculate total profit
    solution.totalProfit = 0.0;
    for (const auto& truck : solution.trucks) {
        for (const auto& pallet : truck.loadedPallets) {
            solution.totalProfit += pallet.profit;
        }
    }
    
    return solution;
}

// Implementation of utility functions from common.h
double calculateTotalWeight(const std::vector<Pallet>& pallets) {
    double total = 0.0;
    for (const auto& pallet : pallets) {
        total += pallet.weight;
    }
    return total;
}

double calculateTotalProfit(const std::vector<Pallet>& pallets) {
    double total = 0.0;
    for (const auto& pallet : pallets) {
        total += pallet.profit;
    }
    return total;
} 