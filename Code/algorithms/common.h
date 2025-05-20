#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>

struct Pallet {
    int id;
    double width;
    double length;
    double height;
    double weight;
    std::string type;  // e.g., "fragile", "standard", etc.
};

struct Truck {
    int id;
    double maxWidth;
    double maxLength;
    double maxHeight;
    double maxWeight;
    std::vector<Pallet> loadedPallets;
};

struct Solution {
    std::vector<Truck> trucks;
    double totalUtilization;
    double executionTime;
    std::string algorithmName;
};

// Common utility functions
double calculateVolume(const Pallet& pallet);
double calculateVolume(const Truck& truck);
double calculateUtilization(const Truck& truck);

#endif // COMMON_H 