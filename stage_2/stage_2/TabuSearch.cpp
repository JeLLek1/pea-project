#include "TabuSearch.h"
#include <list>

// opisy parametr�w i metod znajduj� si� w plikach nag��wkowych

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


    this->tabuTime = static_cast<unsigned>(this->currentOrder->size());
    this->randAfterIters = static_cast<unsigned>(this->currentOrder->size());
    this->punish = static_cast<unsigned>(this->currentOrder->size());
}

// p�tla g��wna algorytmu bez dywersyfikacji
void TabuSearch::run()
{
    this->start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end;
    do {
        unsigned int bestMoovValue = UINT_MAX;
        this->neighborhood->init();
        // przetwarzanie kolejnych s�siad�w
        while (this->neighborhood->getNext(this->currentOrder, this->problem)) {
            if ((   this->neighborhood->notInTabu(this->tabu) && this->neighborhood->getLoos() < bestMoovValue )
                    || (this->neighborhood->getLoos() < this->bestOrder->totalLoos)) {

                bestMoovValue = this->neighborhood->getLoos();
                this->neighborhood->saveCurrent();
            }
        }
        this->neighborhood->refreaschTabu(this->tabu);
        if (bestMoovValue == UINT_MAX) continue;
        this->neighborhood->increaseTabu(this->tabu, this->tabuTime);
        this->neighborhood->applyBest(this->currentOrder, this->problem);
        if (this->bestOrder->totalLoos > this->neighborhood->getLoos()) {
            this->bestOrder->setOrder(this->currentOrder, this->neighborhood->getLoos());
        }

        end = std::chrono::high_resolution_clock::now();
    } while (std::chrono::duration_cast<std::chrono::seconds>(end - this->start).count() < this->problem->getStopSeconds());
}

// p�tla g��wna algorytmu z dywersyfikacj�
void TabuSearch::runDiversifi()
{
    this->start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end;
    do {
        unsigned int bestMoovValue = UINT_MAX;
        this->neighborhood->init();
        // przetwarzanie kolejnych s�siad�w
        while (this->neighborhood->getNext(this->currentOrder, this->problem)) {
            if ((this->neighborhood->notInTabu(this->tabu) && this->neighborhood->getLoosWithPunish(this->punishment) < bestMoovValue)
                || (this->neighborhood->getLoos() < this->bestOrder->totalLoos)) {

                bestMoovValue = this->neighborhood->getLoos();
                this->neighborhood->saveCurrent();
            }
        }

        this->neighborhood->refreaschTabu(this->tabu);
        if (bestMoovValue == UINT_MAX) continue;
        this->neighborhood->increaseTabu(this->tabu, this->tabuTime);
        this->neighborhood->applyBest(this->currentOrder, this->problem);
        if (this->bestOrder->totalLoos > this->neighborhood->getLoos()) {
            this->bestOrder->setOrder(this->currentOrder, this->neighborhood->getLoos());
        }
        // dywersyfikacja - kary za nie przynoszenie zysk�w
        if (this->currentBestLoos > this->neighborhood->getLoos()) {
            this->currentBestLoos = this->neighborhood->getLoos();
            this->itersWithoutImprovement = 0;
        } else {
            this->itersWithoutImprovement++;
            this->neighborhood->increasePunishment(this->punishment, this->punish);
        }
        // dywersyfikacja - losowanie nowej kolejno�ci je�eli kolejne s�siedztwa nie przynosz� zysku
        if (this->itersWithoutImprovement > this->randAfterIters) {
            delete this->currentOrder;
            this->currentOrder = problem->randomOrder();
            this->currentBestLoos = problem->getTotalWeightedLoos(this->currentOrder);
            this->neighborhood->punischClear(this->punishment);
            if (this->currentBestLoos < this->bestOrder->totalLoos) {
                this->bestOrder->setOrder(this->currentOrder, this->currentBestLoos);
            }
        }

        end = std::chrono::high_resolution_clock::now();
    } while (std::chrono::duration_cast<std::chrono::seconds>(end - this->start).count() < this->problem->getStopSeconds());
}


TabuSearch::~TabuSearch()
{
    delete this->currentOrder;
    delete this->bestOrder;
}