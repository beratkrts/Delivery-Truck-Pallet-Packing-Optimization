#include "dp.h"
#include <algorithm>
#include <iostream>
#include <chrono>

/**
 * @brief Resolve o problema de seleção de pallets usando programação dinâmica.
 * @brief [EN] Solves the pallet selection problem using dynamic programming.
 *
 * Esta função utiliza uma abordagem de programação dinâmica para determinar
 * o subconjunto de pallets que maximiza o lucro total sem ultrapassar a
 * capacidade de carga do caminhão. O algoritmo calcula uma matriz de lucro
 * ótimo para cada combinação de pallets e capacidade e reconstrói a solução final.
 *
 * [EN] This function uses a dynamic programming approach to determine
 * the subset of pallets that maximizes total profit without exceeding the
 * truck's load capacity. It builds a profit matrix for each combination
 * of pallets and capacity and reconstructs the final solution.
 *
 * @param pallets Vetor de pallets disponíveis.
 * [EN] Vector of available pallets.
 *
 * @param truck Caminhão com capacidade máxima de carga.
 * [EN] Truck with maximum load capacity.
 *
 * @return Solution Estrutura contendo os pallets selecionados, o lucro total,
 * o tempo de execução e o nome do algoritmo.
 * [EN] Structure containing the selected pallets, total profit,
 * execution time, and algorithm name.
 *
 * @complexity Time Complexity: O(n * W)
 * The time complexity is O(n * W) where n is the number of pallets and W is the truck's capacity.
 * This is because the algorithm fills a 2D array of size (n+1) x (W+1).
 *
 * @complexity Space Complexity: O(n * W)
 * The space complexity is O(n * W) due to the storage requirements of the 2D DP matrix.
 * The matrix stores the maximum profit for each subproblem.
 */
Solution solveDP(const std::vector<Pallet>& pallets, const Truck& truck) {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution;
    solution.algorithmName = "Dynamic Programming";
    solution.truck = truck;

    int n = pallets.size();
    int W = truck.capacity;

    // Cria a matriz DP (lucro máximo para cada subproblema)
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

    // Reconstrução da solução
    int w = W;
    double totalProfit = 0.0;

    for (int i = n; i > 0; i--) {
        if (dp_matrix[i - 1][w] != dp_matrix[i][w]) {
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
