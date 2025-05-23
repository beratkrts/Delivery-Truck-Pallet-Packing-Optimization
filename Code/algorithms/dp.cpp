#include "dp.h"
#include <vector>
#include <algorithm>

Solution solveDP(const std::vector<Pallet>& pallets, const std::vector<Truck>& trucks) {
    Solution solution;
    solution.algorithmName = "Dynamic Programming";
    solution.totalProfit = 0;

    // Assuming there is only one truck for simplicity
    if (trucks.empty()) {
        return solution;
    }

    const Truck& truck = trucks[0];
    int maxWeight = truck.capacity;
    int n = pallets.size();

    // Create a DP table to store the maximum profit for different capacities
    std::vector<std::vector<double>> dp(n + 1, std::vector<double>(maxWeight + 1, 0.0));

    // Fill the DP table
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= maxWeight; ++w) {
            if (pallets[i - 1].weight <= w) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - pallets[i - 1].weight] + pallets[i - 1].profit);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Backtrack to find the selected pallets
    int w = maxWeight;
    std::vector<Pallet> selectedPallets;
    for (int i = n; i > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedPallets.push_back(pallets[i - 1]);
            w -= pallets[i - 1].weight;
        }
    }

    // Update the solution
    solution.totalProfit = dp[n][maxWeight];
    solution.trucks.clear();
    solution.trucks.push_back(truck);
    solution.trucks[0].loadedPallets = selectedPallets;

    return solution;
}
