#include "brute_force.h"
#include <climits>
#include <chrono>

// Time limit in seconds
constexpr double TIME_LIMIT = 10.0; // 10 seconds limit

Solution solveBruteForce(const std::vector<Pallet>& pallets, const Truck& truck) {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution;
    solution.algorithmName = "Brute Force";
    solution.truck = truck;
    solution.totalProfit = 0;
    solution.executionTime = 0;
    solution.terminated = false;  // New field to indicate if algorithm was terminated

    // Use long long to handle large numbers
    long long maxWeight = static_cast<long long>(truck.capacity);
    int n = pallets.size();
    
    // Calculate estimated time
    long long totalCombinations = 1LL << n;
    double estimatedTimeSeconds = (totalCombinations * 1000.0) / 1e9; // Rough estimate: 1000 cycles per combination
    
    // Pre-allocate the selected pallets vector to avoid reallocations
    std::vector<Pallet> selectedPallets;
    selectedPallets.reserve(n);

    // Use long long for weight calculations to avoid overflow
    for (long long i = 0; i < (1LL << n); ++i) {
        // Check time limit
        auto current = std::chrono::high_resolution_clock::now();
        double elapsedSeconds = std::chrono::duration_cast<std::chrono::microseconds>(current - start).count() / 1000000.0;
        
        if (elapsedSeconds > TIME_LIMIT) {
            solution.terminated = true;
            solution.estimatedTotalTime = estimatedTimeSeconds;
            solution.executionTime = elapsedSeconds;
            return solution;
        }

        long long totalWeight = 0;
        double totalProfit = 0;
        selectedPallets.clear();

        for (int j = 0; j < n; ++j) {
            if (i & (1LL << j)) {
                totalWeight += static_cast<long long>(pallets[j].weight);
                totalProfit += pallets[j].profit;
                selectedPallets.push_back(pallets[j]);
            }
        }

        if (totalWeight <= maxWeight &&
            totalProfit > solution.totalProfit) {
            solution.totalProfit = totalProfit;
            solution.selectedPallets = selectedPallets;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    solution.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return solution;
}