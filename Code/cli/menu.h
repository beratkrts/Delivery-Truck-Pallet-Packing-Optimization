#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <map>
#include "../algorithms/common.h"
#include "../algorithms/greedy.h"
#include "../algorithms/brute_force.h"
#include "../algorithms/dp.h"
#include "../algorithms/ilp_solver.h"
#include "../input/data_loader.h"

/**
 * @file menu.h
 * @brief Declaração da classe Menu para interface do usuário do sistema de otimização de pallets.
 * @brief [EN] Declaration of the Menu class for the pallet optimization system user interface.
 *
 * Este cabeçalho define a classe Menu que gerencia toda a interação com o usuário,
 * incluindo carregamento de dados, seleção de algoritmos, execução e exibição de resultados.
 *
 * [EN] This header defines the Menu class that manages all user interaction,
 * including data loading, algorithm selection, execution, and results display.
 */

/**
 * @brief Classe responsável pela interface do usuário e controle do fluxo do programa.
 * @brief [EN] Class responsible for user interface and program flow control.
 *
 * A classe Menu fornece uma interface de linha de comando completa para o sistema
 * de otimização de seleção de pallets. Ela permite ao usuário carregar diferentes
 * conjuntos de dados, selecionar algoritmos específicos, executar otimizações e
 * visualizar/salvar resultados de forma organizada.
 *
 * [EN] The Menu class provides a complete command-line interface for the pallet
 * selection optimization system. It allows users to load different datasets,
 * select specific algorithms, run optimizations, and view/save results in an
 * organized manner.
 */
class Menu {
public:
    /**
     * @brief Construtor da classe Menu.
     * @brief [EN] Constructor of the Menu class.
     *
     * Inicializa o menu com valores padrão e prepara o sistema para uso.
     *
     * [EN] Initializes the menu with default values and prepares the system for use.
     */
    Menu();

    /**
     * @brief Executa o loop principal do menu interativo.
     * @brief [EN] Runs the main loop of the interactive menu.
     *
     * Função principal que controla todo o fluxo de execução do programa,
     * exibindo opções e processando escolhas do usuário.
     *
     * [EN] Main function that controls the entire program execution flow,
     * displaying options and processing user choices.
     */
    void run();

private:
    /**
     * @brief Exibe o menu principal com todas as opções disponíveis.
     * @brief [EN] Displays the main menu with all available options.
     */
    void displayMainMenu();

    /**
     * @brief Carrega dados de pallets e caminhão a partir de arquivos.
     * @brief [EN] Loads pallet and truck data from files.
     */
    void loadData();

    /**
     * @brief Permite ao usuário selecionar um conjunto de dados específico.
     * @brief [EN] Allows user to select a specific dataset.
     */
    void selectDataset();

    /**
     * @brief Permite ao usuário escolher um algoritmo para execução.
     * @brief [EN] Allows user to choose an algorithm for execution.
     */
    void selectAlgorithm();

    /**
     * @brief Executa o algoritmo atualmente selecionado.
     * @brief [EN] Runs the currently selected algorithm.
     */
    void runAlgorithm();

    /**
     * @brief Executa todos os algoritmos disponíveis sequencialmente.
     * @brief [EN] Runs all available algorithms sequentially.
     */
    void runAllAlgorithms();

    /**
     * @brief Exibe os resultados do último algoritmo executado.
     * @brief [EN] Displays results from the last executed algorithm.
     */
    void displayResults();

    /**
     * @brief Exibe uma comparação de todos os resultados obtidos.
     * @brief [EN] Displays a comparison of all obtained results.
     */
    void displayAllResults();

    /**
     * @brief Salva os resultados em arquivo para análise posterior.
     * @brief [EN] Saves results to file for later analysis.
     */
    void saveResults();

    /**
     * @brief Limpa todos os dados carregados e resultados armazenados.
     * @brief [EN] Clears all loaded data and stored results.
     */
    void clearData();

    /**
     * @brief Encerra o programa de forma segura.
     * @brief [EN] Safely exits the program.
     */
    void exitProgram();

    /**
     * @brief Exibe informações de ajuda sobre como usar o sistema.
     * @brief [EN] Displays help information about how to use the system.
     */
    void displayHelp();

    /**
     * @brief Valida se os dados carregados são consistentes e válidos.
     * @brief [EN] Validates if loaded data is consistent and valid.
     *
     * @return true se os dados são válidos, false caso contrário.
     * [EN] true if data is valid, false otherwise.
     */
    bool validateData() const;

    /**
     * @brief Exibe informações detalhadas sobre o conjunto de dados atual.
     * @brief [EN] Displays detailed information about the current dataset.
     */
    void displayDatasetInfo() const;

    /**
     * @brief Obtém o caminho do arquivo para um conjunto de dados específico.
     * @brief [EN] Gets the file path for a specific dataset.
     *
     * @param datasetNumber Número identificador do conjunto de dados.
     * [EN] Dataset identifier number.
     *
     * @return String com o caminho completo do arquivo.
     * [EN] String with the complete file path.
     */
    std::string getDatasetPath(int datasetNumber) const;

    /**
     * @brief Obtém o nome do algoritmo baseado em seu número identificador.
     * @brief [EN] Gets the algorithm name based on its identifier number.
     *
     * @param algorithmNumber Número identificador do algoritmo.
     * [EN] Algorithm identifier number.
     *
     * @return String com o nome do algoritmo.
     * [EN] String with the algorithm name.
     */
    std::string getAlgorithmName(int algorithmNumber) const;

    /**
     * @brief Exibe os resultados de uma solução específica de forma formatada.
     * @brief [EN] Displays results from a specific solution in formatted way.
     *
     * @param solution Objeto Solution contendo os resultados a serem exibidos.
     * [EN] Solution object containing results to be displayed.
     */
    void displaySingleResult(const Solution& solution) const;

    // Atributos da classe / Class attributes

    /**
     * @brief Vetor contendo todos os pallets carregados do conjunto de dados atual.
     * @brief [EN] Vector containing all pallets loaded from current dataset.
     */
    std::vector<Pallet> pallets;

    /**
     * @brief Estrutura representando o caminhão com sua capacidade.
     * @brief [EN] Structure representing the truck with its capacity.
     */
    Truck truck;

    /**
     * @brief Mapa que armazena resultados de cada algoritmo executado.
     * @brief [EN] Map that stores results from each executed algorithm.
     */
    std::map<int, Solution> algorithmResults;

    /**
     * @brief Flag indicando se dados foram carregados com sucesso.
     * @brief [EN] Flag indicating if data was loaded successfully.
     */
    bool dataLoaded;

    /**
     * @brief Identificador do conjunto de dados atualmente selecionado.
     * @brief [EN] Identifier of currently selected dataset.
     */
    int currentDataset;

    /**
     * @brief Identificador do algoritmo atualmente selecionado.
     * @brief [EN] Identifier of currently selected algorithm.
     */
    int currentAlgorithm;

    /**
     * @brief Número máximo de conjuntos de dados disponíveis.
     * @brief [EN] Maximum number of available datasets.
     */
    static const int MAX_DATASETS = 10;

    /**
     * @brief Número total de algoritmos implementados.
     * @brief [EN] Total number of implemented algorithms.
     */
    static const int MAX_ALGORITHMS = 4;
};

#endif // MENU_H