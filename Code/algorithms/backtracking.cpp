/**
 * @file backtracking.cpp
 * @brief Implementação do algoritmo de backtracking para o problema de seleção de pallets.
 * @brief [EN] Implementation of the backtracking algorithm for the pallet selection problem.
 *
 * Este arquivo contém a implementação da função que resolve o problema de seleção
 * de pallets utilizando backtracking. O algoritmo explora todas as combinações
 * possíveis de pallets de forma sistemática, garantindo a solução ótima.
 *
 * [EN] This file contains the implementation of the function that solves the pallet
 * selection problem using backtracking. The algorithm systematically explores all
 * possible combinations of pallets, guaranteeing the optimal solution.
 */

#include "backtracking.h"
#include <chrono>

/**
 * @brief Função auxiliar recursiva para o algoritmo de backtracking.
 * @brief [EN] Recursive helper function for the backtracking algorithm.
 *
 * Esta função recursiva explora todas as possibilidades de seleção de pallets,
 * construindo a árvore de decisões e mantendo controle da melhor solução encontrada.
 *
 * [EN] This recursive function explores all possibilities of pallet selection,
 * building the decision tree and keeping track of the best solution found.
 *
 * @param pallets Vetor com todos os pallets disponíveis.
 * [EN] Vector with all available pallets.
 * @param index Índice atual do pallet sendo considerado.
 * [EN] Current index of the pallet being considered.
 * @param currentWeight Peso atual dos pallets selecionados.
 * [EN] Current weight of selected pallets.
 * @param currentProfit Lucro atual dos pallets selecionados.
 * [EN] Current profit of selected pallets.
 * @param currentSelection Vetor com os pallets atualmente selecionados.
 * [EN] Vector with currently selected pallets.
 * @param capacity Capacidade máxima do caminhão.
 * [EN] Maximum truck capacity.
 * @param bestProfit Referência para o melhor lucro encontrado até agora.
 * [EN] Reference to the best profit found so far.
 * @param bestSelection Referência para a melhor seleção encontrada até agora.
 * [EN] Reference to the best selection found so far.
 */
void backtrackHelper(const std::vector<Pallet>& pallets,
                     int index,
                     double currentWeight,
                     double currentProfit,
                     std::vector<Pallet>& currentSelection,
                     double capacity,
                     double& bestProfit,
                     std::vector<Pallet>& bestSelection) {

    // Caso base: todos os pallets foram considerados
    // [EN] Base case: all pallets have been considered
    if (index == pallets.size()) {
        // Verifica se a solução atual é melhor que a melhor encontrada
        // [EN] Check if current solution is better than the best found
        if (currentProfit > bestProfit) {
            bestProfit = currentProfit;
            bestSelection = currentSelection;
        }
        return;
    }

    // Poda: se mesmo adicionando todos os pallets restantes não melhorarmos a solução, para
    // [EN] Pruning: if even adding all remaining pallets won't improve solution, stop
    double remainingProfit = 0;
    for (int i = index; i < pallets.size(); i++) {
        remainingProfit += pallets[i].profit;
    }
    if (currentProfit + remainingProfit <= bestProfit) {
        return;
    }

    // Opção 1: Não incluir o pallet atual (ir para o próximo)
    // [EN] Option 1: Don't include current pallet (go to next)
    backtrackHelper(pallets, index + 1, currentWeight, currentProfit,
                    currentSelection, capacity, bestProfit, bestSelection);

    // Opção 2: Incluir o pallet atual (se couber na capacidade)
    // [EN] Option 2: Include current pallet (if it fits in capacity)
    if (currentWeight + pallets[index].weight <= capacity) {
        // Adiciona pallet à seleção atual
        // [EN] Add pallet to current selection
        currentSelection.push_back(pallets[index]);

        // Chama recursivamente com o pallet incluído
        // [EN] Recursively call with pallet included
        backtrackHelper(pallets, index + 1,
                        currentWeight + pallets[index].weight,
                        currentProfit + pallets[index].profit,
                        currentSelection, capacity, bestProfit, bestSelection);

        // Backtrack: remove o pallet da seleção atual
        // [EN] Backtrack: remove pallet from current selection
        currentSelection.pop_back();
    }
}

/**
 * @brief Implementação do algoritmo de backtracking para seleção ótima de pallets.
 * @brief [EN] Implementation of the backtracking algorithm for optimal pallet selection.
 *
 * O algoritmo de backtracking funciona da seguinte forma:
 * 1. Para cada pallet, considera duas opções: incluir ou não incluir
 * 2. Explora recursivamente todas as combinações possíveis
 * 3. Utiliza poda para evitar explorar ramos que não podem melhorar a solução
 * 4. Mantém controle da melhor solução encontrada durante a busca
 *
 * [EN] The backtracking algorithm works as follows:
 * 1. For each pallet, considers two options: include or not include
 * 2. Recursively explores all possible combinations
 * 3. Uses pruning to avoid exploring branches that cannot improve the solution
 * 4. Keeps track of the best solution found during the search
 *
 * @param pallets Vetor contendo todos os pallets disponíveis para seleção.
 * [EN] Vector containing all available pallets for selection.
 *
 * @param truck Estrutura representando o caminhão com sua capacidade máxima.
 * [EN] Structure representing the truck with its maximum capacity.
 *
 * @return Solution Estrutura contendo a solução ótima encontrada pelo backtracking.
 * [EN] Structure containing the optimal solution found by backtracking.
 *
 * @complexity Time Complexity: O(2^n)
 * The time complexity is O(2^n) in the worst case because the algorithm explores all possible subsets of pallets.
 * For each of the n pallets, there are 2 choices: either include it in the subset or not.
 * This results in 2^n possible combinations to check.
 *
 * @complexity Space Complexity: O(n)
 * The space complexity is O(n) due to the storage required for the current selection of pallets.
 * The currentSelection vector can grow up to size n in the worst case.
 * Additionally, the recursion stack uses space proportional to the depth of the recursion tree, which is also O(n).
 */
Solution solveBacktracking(const std::vector<Pallet>& pallets, const Truck& truck) {
    // Inicia cronômetro para medir tempo de execução
    // [EN] Start timer to measure execution time
    auto start = std::chrono::high_resolution_clock::now();

    // Inicializa estrutura da solução
    // [EN] Initialize solution structure
    Solution solution;
    solution.algorithmName = "Backtracking";
    solution.truck = truck;

    // Variáveis para controlar a melhor solução encontrada
    // [EN] Variables to control the best solution found
    double bestProfit = 0;
    std::vector<Pallet> bestSelection;
    std::vector<Pallet> currentSelection;

    // Inicia o processo de backtracking recursivo
    // [EN] Start the recursive backtracking process
    backtrackHelper(pallets, 0, 0.0, 0.0, currentSelection,
                    truck.capacity, bestProfit, bestSelection);

    // Armazena a melhor solução encontrada
    // [EN] Store the best solution found
    solution.selectedPallets = bestSelection;
    solution.totalProfit = static_cast<int>(bestProfit);

    // Para cronômetro e calcula tempo de execução
    // [EN] Stop timer and calculate execution time
    auto end = std::chrono::high_resolution_clock::now();
    solution.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return solution;
}
