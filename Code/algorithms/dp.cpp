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
    int K = truck.maxPallets;
    std::vector<std::vector<std::vector<double>>> dp_matrix(n + 1, std::vector<std::vector<double>>(W + 1, std::vector<double>(K + 1)));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            for (int k = 0; k <= K; k++) {
                dp_matrix[i][w][k] = dp_matrix[i - 1][w][k];

                double palletWeight = pallets[i-1].weight;
                double palletProfit = pallets[i - 1].profit;
                if (w >= palletWeight && k >= 1) {
                    dp_matrix[i][w][k] = std::max(dp_matrix[i][w][k],
                        dp_matrix[i - 1][w - palletWeight][k - 1] + palletProfit);
                }
            }
        }
    }
    int w = W;
    int k = K;
    double totalProfit = 0.0;
    for (int i = n; i > 0 && k > 0; i--) {
        if (dp_matrix[i-1][w][k] != dp_matrix[i][w][k]) {
            solution.selectedPallets.push_back(pallets[i - 1]);
            w -= pallets[i - 1].weight;
            k--;
            totalProfit += pallets[i - 1].profit;
        }
    }
    solution.totalProfit = totalProfit;
    auto end = std::chrono::high_resolution_clock::now();
    solution.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return solution;
} 