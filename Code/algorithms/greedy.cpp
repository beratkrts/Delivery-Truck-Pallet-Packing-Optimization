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
        if (currentWeight + pallet.weight <= truck.capacity) {
            solution.selectedPallets.push_back(pallet);
            currentWeight += pallet.weight;
            palletCount++;
            solution.totalProfit += pallet.profit;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    solution.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return solution;
}
