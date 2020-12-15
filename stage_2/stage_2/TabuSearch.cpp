#include "TabuSearch.h"

TabuSearch::TabuSearch(WeightedTardiness* problem)
{
    this->problem = problem;
    this->currentOrder = problem->randomOrder();
    this->currentBestLoos = problem->getTotalWeightedLoos(this->currentOrder);
    this->bestOrder = new JobsOrder();
    this->bestOrder->setOrder(this->currentOrder, this->currentBestLoos);
    this->neighborhood = problem->getNeighborhood();

    this->tabu.resize(problem->countJobs(), std::vector<unsigned>(problem->countJobs(), 0));
    this->punishment.resize(problem->countJobs(), std::vector<unsigned>(problem->countJobs(), 0));
}

void TabuSearch::run()
{
    this->start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end;
    do {


        end = std::chrono::high_resolution_clock::now();
    } while (std::chrono::duration_cast<std::chrono::seconds>(end - this->start).count() < this->problem->getStopSeconds());
}

TabuSearch::~TabuSearch()
{
    delete this->bestOrder;
}
