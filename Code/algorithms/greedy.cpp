/**
 * @file greedy.cpp
 * @brief Implementação do algoritmo guloso para o problema de seleção de pallets.
 * @brief [EN] Implementation of the greedy algorithm for the pallet selection problem.
 *
 * Este arquivo contém a implementação da função que resolve o problema de seleção
 * de pallets utilizando uma abordagem gulosa baseada na razão peso-lucro.
 *
 * [EN] This file contains the implementation of the function that solves the pallet
 * selection problem using a greedy approach based on weight-to-profit ratio.
 */

#include "greedy.h"
#include "common.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>

/**
 * @brief Implementação do algoritmo guloso para seleção de pallets.
 * @brief [EN] Implementation of the greedy algorithm for pallet selection.
 *
 * O algoritmo guloso funciona da seguinte forma:
 * 1. Ordena os pallets pela razão peso-lucro em ordem decrescente
 * 2. Seleciona pallets sequencialmente enquanto houver capacidade
 * 3. Para cada pallet, verifica se cabe no caminhão antes de adicionar
 *
 * [EN] The greedy algorithm works as follows:
 * 1. Sorts pallets by weight-to-profit ratio in descending order
 * 2. Selects pallets sequentially while there is capacity
 * 3. For each pallet, checks if it fits in the truck before adding
 *
 * @param pallets Vetor contendo todos os pallets disponíveis para seleção.
 * [EN] Vector containing all available pallets for selection.
 *
 * @param truck Estrutura representando o caminhão com sua capacidade máxima.
 * [EN] Structure representing the truck with its maximum capacity.
 *
 * @return Solution Estrutura contendo a solução encontrada pelo algoritmo guloso.
 * [EN] Structure containing the solution found by the greedy algorithm.
 *
 * @complexity Time Complexity: O(n log n)
 * The time complexity is O(n log n) due to the sorting step, where n is the number of pallets.
 * The subsequent selection process is O(n), but the sorting step dominates the time complexity.
 *
 * @complexity Space Complexity: O(n)
 * The space complexity is O(n) due to the storage required for the sorted pallets.
 * The algorithm creates a copy of the pallets vector for sorting.
 */
Solution solveGreedy(const std::vector<Pallet>& pallets, const Truck& truck) {
    // Inicia cronômetro para medir tempo de execução
    // [EN] Start timer to measure execution time
    auto start = std::chrono::high_resolution_clock::now();

    // Inicializa estrutura da solução
    // [EN] Initialize solution structure
    Solution solution;
    solution.algorithmName = "Greedy";
    solution.truck = truck;

    // Cria cópia dos pallets que pode ser ordenada
    // [EN] Create a copy of pallets that can be sorted
    std::vector<Pallet> sortedPallets = pallets;

    // Ordena pallets pela razão peso-lucro em ordem decrescente (melhores primeiro)
    // [EN] Sort pallets by weight-to-profit ratio in descending order (best first)
    std::sort(sortedPallets.begin(), sortedPallets.end(),
        [](const Pallet& a, const Pallet& b) {
            return a.weightProfitRatio > b.weightProfitRatio;
        });

    // Variáveis para controle do peso atual e contagem de pallets
    // [EN] Variables to control current weight and pallet count
    double currentWeight = 0.0;
    int palletCount = 0;

    // Seleciona pallets de forma gulosa baseado na razão peso-lucro
    // [EN] Select pallets greedily based on weight-to-profit ratio
    for (const auto& pallet : sortedPallets) {
        // Verifica se o pallet cabe na capacidade restante do caminhão
        // [EN] Check if the pallet fits in the truck's remaining capacity
        if (currentWeight + pallet.weight <= truck.capacity) {
            // Adiciona pallet à solução
            // [EN] Add pallet to solution
            solution.selectedPallets.push_back(pallet);
            currentWeight += pallet.weight;
            palletCount++;
            solution.totalProfit += pallet.profit;
        }
    }

    // Para cronômetro e calcula tempo de execução
    // [EN] Stop timer and calculate execution time
    auto end = std::chrono::high_resolution_clock::now();
    solution.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return solution;
}
