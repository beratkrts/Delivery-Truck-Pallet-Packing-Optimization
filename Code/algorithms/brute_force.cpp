#include "brute_force.h"
#include <vector>
#include <algorithm>

Solution solveBruteForce(const std::vector<Pallet>& pallets, const std::vector<Truck>& trucks) {
    Solution solution;
    solution.algorithmName = "Brute Force";
    solution.totalProfit = 0;


    if (trucks.empty()) {
        return solution;
    }

    const Truck& truck = trucks[0];
    int maxWeight = truck.capacity;
    int n = pallets.size();

    // Iterate over all possible subsets
    for (int i = 0; i < (1 << n); ++i) {
        int totalWeight = 0;
        int totalProfit = 0;
        std::vector<Pallet> selectedPallets;

        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                totalWeight += pallets[j].weight;
                totalProfit += pallets[j].profit;
                selectedPallets.push_back(pallets[j]);
            }
        }


        if (totalWeight <= maxWeight && totalProfit > solution.totalProfit) {
            solution.totalProfit = totalProfit;
            solution.trucks.clear();
            solution.trucks.push_back(truck);
            solution.trucks[0].loadedPallets = selectedPallets;
        }
    }

    return solution;
}
