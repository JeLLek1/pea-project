#pragma once
#include <chrono>
#include <vector>
#include <utility>
#include "WeightedTardiness.h"
#include "JobsOrder.h"

class GeneticAlgorithm
{
    // instancja problemu
    WeightedTardiness* problem;
    // wektor par zawierajacych sumaryczne opoznienie wraz z lista wierzchokow (obecna populacja)
    std::vector<std::pair<std::vector<size_t>*, unsigned int>> population;

    // czas rozpoczecia algorytmu
    std::chrono::high_resolution_clock::time_point timeStart;

public:
    // najlepsze znalezione dot¹d rozwi¹zanie
    JobsOrder* best;

    GeneticAlgorithm(WeightedTardiness* problem);

    // partially matched crossover
    // parentFirst, parentSecond - rodzice z ktorych wynika krzyzowanie
    // problem - obecnie przetwarzany problem
    static std::pair<std::vector<size_t>*, unsigned int> PMX(
        std::pair<std::vector<size_t>*, unsigned int>& parentFirst,
        std::pair<std::vector<size_t>*, unsigned int>& parentSecond,
        WeightedTardiness* problem);
    // Order crossover
    // parentFirst, parentSecond - rodzice z ktorych wynika krzyzowanie
    // problem - obecnie przetwarzany problem
    static std::pair<std::vector<size_t>*, unsigned int> OX(
        std::pair<std::vector<size_t>*, unsigned int>& parentFirst,
        std::pair<std::vector<size_t>*, unsigned int>& parentSecond,
        WeightedTardiness* problem);

    // mutacja insertion
    // specimen - osobnik który podlega mutacji
    static void insertMutation(
        std::pair<std::vector<size_t>*, unsigned int>& specimen,
        WeightedTardiness* problem);
    // mutacja transposition
    // elememnt - element który podlega mutacji
    static void transpositionMutation(
        std::pair<std::vector<size_t>*, unsigned int>& specimen,
        WeightedTardiness* problem);

    // generowanie nowej populacji
    void generatePopulation();
    // czyszczenie starej populacji
    void clearPopulation();

    void runAlgorithm();

    ~GeneticAlgorithm();
};

