#pragma once
#include <vector>
#include <chrono>
#include "WeightedTardiness.h"
#include "ANeighborhood.h"
#include "JobsOrder.h"

class SimulatedAnnealing
{
    static double temperatureMinimum;

    std::vector<size_t>* currentOrder;
    WeightedTardiness* problem;
    double temperature;
    unsigned int stepsize;

    std::chrono::high_resolution_clock::time_point start;
    unsigned int currentBestLoos;
    ANeighborhood* neighborhood;

    void setFirstTemperature();
    void setNextTemperature();
    bool shouldAssignCurrent(unsigned int loos);
public:
    JobsOrder* bestOrder;
    SimulatedAnnealing(WeightedTardiness* problem);

    void run();

    ~SimulatedAnnealing();
};

