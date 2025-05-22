#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>

struct Pallet {
    int id;
    double weight;
    double profit;
    double weightProfitRatio;  // Stored ratio of profit/weight
};

struct Truck {
    double capacity;
    int maxPallets;
    std::vector<Pallet> loadedPallets;
};

struct Solution {
    Truck truck;
    std::vector<Pallet> selectedPallets;  // Pallets that were selected to be loaded
    double totalProfit;
    double executionTime;
    std::string algorithmName;
};


#endif // COMMON_H 