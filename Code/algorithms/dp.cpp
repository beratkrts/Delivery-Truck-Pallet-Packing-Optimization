#include "dp.h"
#include <algorithm>
#include <iostream>


Solution solveDP(const std::vector<Pallet>& pallets, const Truck& truck) {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution;
    solution.algorithmName = "Dynamic Programming";
    solution.truck = truck;
    int n = pallets.size();
    int W = truck.capacity;
    std::vector<std::vector<double>> dp_matrix(n + 1, std::vector<double>(W + 1));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp_matrix[i][w] = dp_matrix[i - 1][w];

            double palletWeight = pallets[i - 1].weight;
            double palletProfit = pallets[i - 1].profit;
            if (w >= palletWeight) {
                dp_matrix[i][w] = std::max(dp_matrix[i][w],
                    dp_matrix[i - 1][w - palletWeight] + palletProfit);
            }
        }
    }
    int w = W;
    double totalProfit = 0.0;
    for (int i = n; i > 0; i--) {
        if (dp_matrix[i-1][w] != dp_matrix[i][w]) {
            solution.selectedPallets.push_back(pallets[i - 1]);
            w -= pallets[i - 1].weight;
            totalProfit += pallets[i - 1].profit;
        }
    }
    solution.totalProfit = totalProfit;
    auto end = std::chrono::high_resolution_clock::now();
    solution.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return solution;
} 