#ifndef GREEDY_H
#define GREEDY_H

#include "common.h"

// Function declarations
double calculateTotalWeight(const std::vector<Pallet>& pallets);
double calculateTotalProfit(const std::vector<Pallet>& pallets);
Solution solveGreedy(const std::vector<Pallet>& pallets, const std::vector<Truck>& trucks);

#endif // GREEDY_H 