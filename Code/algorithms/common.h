#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>

struct Pallet {
    int id;
    double weight;
    double profit;
};

struct Truck {
    double capacity;
    int maxPallets;
    std::vector<Pallet> loadedPallets;
};

struct Solution {
    std::vector<Truck> trucks;
    double totalProfit;
    double executionTime;
    std::string algorithmName;
};

// Common utility functions
double calculateTotalWeight(const std::vector<Pallet>& pallets);
double calculateTotalProfit(const std::vector<Pallet>& pallets);

#endif // COMMON_H 