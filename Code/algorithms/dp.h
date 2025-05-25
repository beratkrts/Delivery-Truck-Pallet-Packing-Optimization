#ifndef DP_H
#define DP_H

#include "common.h"

/**
 * @file dp.h
 * @brief Declaração da função que implementa o algoritmo de programação dinâmica.
 * @brief [EN] Declaration of the function that implements the dynamic programming algorithm.
 *
 * Este cabeçalho declara a função que resolve o problema de seleção de pallets
 * utilizando uma abordagem de programação dinâmica.
 *
 * [EN] This header declares the function that solves the pallet selection problem
 * using a dynamic programming approach.
 */

/**
 * @brief Resolve o problema de seleção de pallets usando programação dinâmica.
 * @brief [EN] Solves the pallet selection problem using dynamic programming.
 *
 * Esta função utiliza uma abordagem baseada em programação dinâmica para selecionar
 * os pallets que maximizam o lucro sem ultrapassar a capacidade do caminhão.
 *
 * [EN] This function uses a dynamic programming-based approach to select
 * the pallets that maximize profit without exceeding the truck's capacity.
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
Solution solveDP(const std::vector<Pallet>& pallets, const Truck& truck);

#endif // DP_H
