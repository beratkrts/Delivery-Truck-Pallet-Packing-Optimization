#include "brute_force.h"
#include <climits>
#include <chrono>

// Time limit in seconds
constexpr double TIME_LIMIT = 30.0; // 30 seconds limit

/**
 * @brief Resolve o problema de seleção de pallets para um caminhão usando força bruta.
 * @brief [EN] Solves the pallet selection problem for a truck using brute force.
 *
 * Esta função tenta todas as combinações possíveis de pallets para encontrar o conjunto
 * com o maior lucro possível que não ultrapasse a capacidade máxima do caminhão.
 * A execução é limitada por tempo para evitar processamento excessivo.
 *
 * [EN] This function tests all possible combinations of pallets to find the subset
 * with the highest possible profit that does not exceed the truck's maximum capacity.
 * Execution is time-limited to prevent excessive processing.
 *
 * @param pallets Vetor contendo os pallets disponíveis, cada um com peso e lucro.
 * [EN] Vector containing the available pallets, each with weight and profit.
 *
 * @param truck Caminhão com capacidade máxima de carga.
 * [EN] Truck with maximum load capacity.
 *
 * @return Solution Objeto contendo o resultado da execução: pallets selecionados,
 * lucro total, tempo de execução, nome do algoritmo e se foi interrompido por limite de tempo.
 * [EN] Object containing the execution result: selected pallets, total profit,
 * execution time, algorithm name, and whether it was terminated due to the time limit.
 *
 * @complexity Time Complexity: O(2^n)
 * The time complexity is O(2^n) because the algorithm checks all possible subsets of pallets.
 * For each of the n pallets, there are 2 choices: either include it in the subset or not.
 * This results in 2^n possible combinations to check.
 *
 * @complexity Space Complexity: O(n)
 * The space complexity is O(n) due to the storage required for the selected pallets.
 * The selectedPallets vector can grow up to size n in the worst case.
 * Additionally, the recursion stack or loop variables use constant space.
 */

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