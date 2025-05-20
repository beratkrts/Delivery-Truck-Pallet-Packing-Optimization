#include "greedy.h"
#include "common.h"
#include <algorithm>
#include <vector>
#include <iostream>

Solution solveGreedy(const std::vector<Pallet>& pallets, const std::vector<Truck>& trucks) {
    Solution solution;
    solution.algorithmName = "Greedy";
    // TODO: Implement greedy algorithm
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