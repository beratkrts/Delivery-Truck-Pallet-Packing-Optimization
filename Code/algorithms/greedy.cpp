#include "greedy.h"
#include "common.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>

Solution solveGreedy(const std::vector<Pallet>& pallets, const Truck& truck) {
    auto start = std::chrono::high_resolution_clock::now();
    
    Solution solution;
    solution.algorithmName = "Greedy";
    solution.truck = truck;
    
    // Create a copy of pallets that we can sort
    std::vector<Pallet> sortedPallets = pallets;
    
    // Sort pallets by weight-to-profit ratio in descending order
    std::sort(sortedPallets.begin(), sortedPallets.end(), 
        [](const Pallet& a, const Pallet& b) {
            return a.weightProfitRatio > b.weightProfitRatio;
        });
    
    double currentWeight = 0.0;
    int palletCount = 0;
    
    // Select pallets greedily based on weight-to-profit ratio
    for (const auto& pallet : sortedPallets) {
        if (currentWeight + pallet.weight <= truck.capacity && 
            palletCount < truck.maxPallets) {
            solution.selectedPallets.push_back(pallet);
            currentWeight += pallet.weight;
            palletCount++;
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