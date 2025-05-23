#include "brute_force.h"

Solution solveBruteForce(const std::vector<Pallet>& pallets, const Truck& truck) {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution;
    solution.algorithmName = "Brute Force";
    solution.truck = truck;
    solution.totalProfit = 0;

    int maxWeight = truck.capacity;
    int n = pallets.size();

    for (int i = 0; i < (1 << n); ++i) {
        double totalWeight = 0;
        double totalProfit = 0;
        std::vector<Pallet> selectedPallets;

        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                totalWeight += pallets[j].weight;
                totalProfit += pallets[j].profit;
                selectedPallets.push_back(pallets[j]);
            }
        }

        if (totalWeight <= maxWeight && selectedPallets.size() <= truck.maxPallets && totalProfit > solution.totalProfit) {
            solution.totalProfit = totalProfit;
            solution.selectedPallets = selectedPallets;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    solution.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return solution;
}