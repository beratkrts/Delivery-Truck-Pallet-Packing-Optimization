#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "common.h"

/**
 * @file backtracking.h
 * @brief Declaração da função que implementa o algoritmo de backtracking.
 * @brief [EN] Declaration of the function that implements the backtracking algorithm.
 *
 * Este cabeçalho declara a função que resolve o problema de seleção de pallets
 * utilizando uma abordagem de backtracking (busca com retrocesso).
 *
 * [EN] This header declares the function that solves the pallet selection problem
 * using a backtracking (search with backtrack) approach.
 */

/**
 * @brief Resolve o problema de seleção de pallets usando algoritmo de backtracking.
 * @brief [EN] Solves the pallet selection problem using backtracking algorithm.
 *
 * Esta função utiliza uma abordagem de backtracking para explorar sistematicamente
 * todas as combinações possíveis de pallets, garantindo a solução ótima. O algoritmo
 * constrói uma árvore de decisões onde cada nó representa a escolha de incluir ou
 * não um pallet, utilizando poda para melhorar a eficiência.
 *
 * [EN] This function uses a backtracking approach to systematically explore
 * all possible combinations of pallets, guaranteeing the optimal solution. The algorithm
 * builds a decision tree where each node represents the choice to include or
 * not include a pallet, using pruning to improve efficiency.
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
Solution solveBacktracking(const std::vector<Pallet>& pallets, const Truck& truck);

#endif // BACKTRACKING_H