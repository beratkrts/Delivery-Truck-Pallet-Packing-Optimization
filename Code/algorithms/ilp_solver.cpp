/**
 * @file ilp_solver.cpp
 * @brief Implementação do algoritmo de Programação Linear Inteira para o problema de seleção de pallets.
 * @brief [EN] Implementation of the Integer Linear Programming algorithm for the pallet selection problem.
 *
 * Este arquivo contém a implementação da função que resolve o problema de seleção
 * de pallets utilizando Programação Linear Inteira (ILP) através da biblioteca OR-Tools.
 * O problema é formulado como um problema da mochila 0-1.
 *
 * [EN] This file contains the implementation of the function that solves the pallet
 * selection problem using Integer Linear Programming (ILP) through the OR-Tools library.
 * The problem is formulated as a 0-1 knapsack problem.
 */

#include "ilp_solver.h"
#include "ortools/linear_solver/linear_solver.h"
#include <chrono>

using namespace operations_research;

/**
 * @brief Implementação do algoritmo ILP para seleção ótima de pallets.
 * @brief [EN] Implementation of the ILP algorithm for optimal pallet selection.
 *
 * O algoritmo formula o problema como um modelo de otimização linear inteira:
 * - Variáveis: x_i ∈ {0,1} para cada pallet i (selecionado ou não)
 * - Objetivo: Maximizar Σ(profit_i * x_i)
 * - Restrição: Σ(weight_i * x_i) ≤ capacity
 *
 * [EN] The algorithm formulates the problem as an integer linear optimization model:
 * - Variables: x_i ∈ {0,1} for each pallet i (selected or not)
 * - Objective: Maximize Σ(profit_i * x_i)
 * - Constraint: Σ(weight_i * x_i) ≤ capacity
 *
 * @param pallets Vetor contendo todos os pallets disponíveis para seleção.
 * [EN] Vector containing all available pallets for selection.
 *
 * @param truck Estrutura representando o caminhão com sua capacidade máxima.
 * [EN] Structure representing the truck with its maximum capacity.
 *
 * @return Solution Estrutura contendo a solução ótima encontrada pelo ILP.
 * [EN] Structure containing the optimal solution found by ILP.
 *
 * @complexity Time Complexity: Dependent on the ILP solver
 * The time complexity is dependent on the ILP solver used (e.g., CBC in this case).
 * ILP problems are generally NP-Hard, and the time complexity can be exponential in the worst case.
 *
 * @complexity Space Complexity: O(n)
 * The space complexity is O(n) due to the storage required for the variables and constraints.
 * The algorithm creates a binary variable for each pallet and a constraint for the capacity.
 */
Solution solveILP(const std::vector<Pallet>& pallets, const Truck& truck) {
    // Inicia cronômetro para medir tempo de execução
    // [EN] Start timer to measure execution time
    auto start = std::chrono::high_resolution_clock::now();

    // Inicializa estrutura da solução
    // [EN] Initialize solution structure
    Solution solution;
    solution.truck = truck;
    solution.algorithmName = "Integer Linear Programming";

    // Cria solver ILP usando CBC (Coin-or Branch and Cut)
    // [EN] Create ILP solver using CBC (Coin-or Branch and Cut)
    MPSolver solver("KnapsackILP", MPSolver::CBC_MIXED_INTEGER_PROGRAMMING);

    // Número total de pallets disponíveis
    // [EN] Total number of available pallets
    int n = pallets.size();

    // Cria variáveis binárias x_i para cada pallet i (0 = não selecionado, 1 = selecionado)
    // [EN] Create binary variables x_i for each pallet i (0 = not selected, 1 = selected)
    std::vector<MPVariable*> x(n);
    for (int i = 0; i < n; i++) {
        x[i] = solver.MakeIntVar(0, 1, "x" + std::to_string(i));
    }

    // Define restrição de capacidade: Σ(weight_i * x_i) ≤ truck.capacity
    // [EN] Define capacity constraint: Σ(weight_i * x_i) ≤ truck.capacity
    MPConstraint* ct = solver.MakeRowConstraint(0, truck.capacity);
    for (int i = 0; i < n; ++i) {
        ct->SetCoefficient(x[i], pallets[i].weight);
    }

    // Define função objetivo: Maximizar Σ(profit_i * x_i)
    // [EN] Define objective function: Maximize Σ(profit_i * x_i)
    MPObjective* objective = solver.MutableObjective();
    for (int i = 0; i < n; ++i) {
        objective->SetCoefficient(x[i], pallets[i].profit);
    }
    objective->SetMaximization();

    // Resolve o modelo de otimização
    // [EN] Solve the optimization model
    if (solver.Solve() == MPSolver::OPTIMAL) {
        // Extrai lucro total da solução ótima
        // [EN] Extract total profit from optimal solution
        solution.totalProfit = static_cast<int>(objective->Value());

        // Identifica pallets selecionados na solução ótima
        // [EN] Identify selected pallets in optimal solution
        for (int i = 0; i < n; ++i) {
            // Verifica se variável x_i = 1 (pallet selecionado)
            // [EN] Check if variable x_i = 1 (pallet selected)
            if (x[i]->solution_value() > 0.5) {
                solution.selectedPallets.push_back(pallets[i]);
            }
        }
    }

    // Para cronômetro e calcula tempo de execução
    // [EN] Stop timer and calculate execution time
    auto end = std::chrono::high_resolution_clock::now();
    solution.executionTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return solution;
}
