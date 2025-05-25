#ifndef ILP_SOLVER_H
#define ILP_SOLVER_H

#include "common.h"

/**
 * @file ilp_solver.h
 * @brief Declaração da função que implementa o algoritmo de Programação Linear Inteira.
 * @brief [EN] Declaration of the function that implements the Integer Linear Programming algorithm.
 *
 * Este cabeçalho declara a função que resolve o problema de seleção de pallets
 * utilizando uma abordagem de Programação Linear Inteira (ILP).
 *
 * [EN] This header declares the function that solves the pallet selection problem
 * using an Integer Linear Programming (ILP) approach.
 */

/**
 * @brief Resolve o problema de seleção de pallets usando Programação Linear Inteira.
 * @brief [EN] Solves the pallet selection problem using Integer Linear Programming.
 *
 * Esta função utiliza uma abordagem de Programação Linear Inteira para encontrar
 * a solução ótima para o problema de seleção de pallets. O ILP garante a
 * solução matematicamente ótima ao formular o problema como um modelo de
 * otimização com variáveis binárias e restrições lineares.
 *
 * [EN] This function uses an Integer Linear Programming approach to find the
 * optimal solution for the pallet selection problem. ILP guarantees the
 * mathematically optimal solution by formulating the problem as an optimization
 * model with binary variables and linear constraints.
 *
 * @param pallets Vetor contendo os pallets disponíveis.
 * [EN] Vector containing the available pallets.
 *
 * @param truck Caminhão com capacidade de carga.
 * [EN] Truck with load capacity.
 *
 * @return Solution Objeto contendo os pallets selecionados, lucro total e estatísticas da execução.
 * [EN] Object containing selected pallets, total profit, and execution statistics.
 */
Solution solveILP(const std::vector<Pallet>& pallets, const Truck& truck);

#endif // ILP_SOLVER_H