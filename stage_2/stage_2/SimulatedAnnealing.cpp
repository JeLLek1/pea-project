#include "SimulatedAnnealing.h"
#include "RandomGenerator.h"
#include <cmath>
#include <iostream>

// opisy parametrów i metod znajduj¹ siê w plikach nag³ówkowych

double SimulatedAnnealing::temperatureMinimum = 0.01;

SimulatedAnnealing::SimulatedAnnealing(WeightedTardiness* problem) {
    this->problem = problem;
    this->currentOrder = problem->randomOrder();
    this->currentBestLoos = problem->getTotalWeightedLoos(this->currentOrder);
    this->bestOrder = new JobsOrder();
    this->bestOrder->setOrder(this->currentOrder, this->currentBestLoos);
    this->neighborhood = problem->getNeighborhood();

    this->stepsize = this->neighborhood->assignComplexity(problem->countJobs());

    this->setFirstTemperature();
}

// g³ówna pêtla algorytmu
void SimulatedAnnealing::run()
{
    this->start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end;

    do {
        for (size_t i = 0; i < this->stepsize; i++) {
            this->neighborhood->draw(this->currentOrder, this->problem);

            if (this->shouldAssignCurrent(this->neighborhood->getLoos())) {
                this->currentBestLoos = this->neighborhood->getLoos();
                this->neighborhood->applyChanges(this->currentOrder);
                if (this->currentBestLoos < this->bestOrder->totalLoos) {
                    this->bestOrder->setOrder(this->currentOrder, this->neighborhood->getLoos());
                }
            }
        }

        this->setNextTemperature();
        end = std::chrono::high_resolution_clock::now();
    } while (
        std::chrono::duration_cast<std::chrono::seconds>(end - this->start).count() < this->problem->getStopSeconds()
        && this->temperature > SimulatedAnnealing::temperatureMinimum );
}

void SimulatedAnnealing::setFirstTemperature()
{
    this->temperature = 10000.0;
}

void SimulatedAnnealing::setNextTemperature()
{
    // wyk³adnicza zmiana temperatury
    this->temperature *= 0.99;
}

bool SimulatedAnnealing::shouldAssignCurrent(unsigned int loos)
{
    if (loos < this->currentBestLoos)
        return true;

    if (std::exp(-  ((loos - this->currentBestLoos) / this->temperature)) > RandomGenerator::getInstance()->getRandomDouble(0.0, 1.0))
        return true;

    return false;
}

SimulatedAnnealing::~SimulatedAnnealing()
{
    delete this->bestOrder;
    delete this->currentOrder;
}