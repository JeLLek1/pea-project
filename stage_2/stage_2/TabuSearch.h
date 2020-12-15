#pragma once
#include <vector>
#include <chrono>
#include "WeightedTardiness.h"
#include "ANeighborhood.h"
#include "JobsOrder.h"

class TabuSearch
{
    unsigned randAfterIters;
    unsigned itersWithoutImprovement = 0;

    std::vector<size_t>* currentOrder;
    WeightedTardiness* problem;

    std::chrono::high_resolution_clock::time_point start;
    unsigned int currentBestLoos;
    ANeighborhood* neighborhood;

    std::vector<std::vector<unsigned>> tabu;
    std::vector<std::vector<unsigned>> punishment;
public:
    JobsOrder* bestOrder;
    TabuSearch(WeightedTardiness* problem);

    void run();

    ~TabuSearch();
};

