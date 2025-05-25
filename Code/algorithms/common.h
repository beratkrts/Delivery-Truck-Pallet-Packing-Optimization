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
    std::vector<Pallet> loadedPallets;
};

struct Solution {
    std::string algorithmName;
    Truck truck;
    std::vector<Pallet> selectedPallets;
    double totalProfit;
    double executionTime;  // in seconds
    bool terminated;       // indicates if algorithm was terminated due to time limit
    double estimatedTotalTime;  // estimated total time in seconds if algorithm were to complete
};


#endif // COMMON_H 