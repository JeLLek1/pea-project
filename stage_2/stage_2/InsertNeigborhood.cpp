#include "InsertNeigborhood.h"
#include "WeightedTardiness.h"
#include "RandomGenerator.h"

void InsertNeigborhood::insert(size_t x, size_t y, std::vector<size_t>* order)
{
    std::vector<size_t>* tmp = new std::vector<size_t>(order->size());
    if (x < y) {
        std::copy(order->begin(), order->begin() + x, tmp->begin());
        std::copy(order->begin() + x + 1, order->begin() + y + 1, tmp->begin() + x);
        std::copy(order->begin() + y + 1, order->begin() + order->size(), tmp->begin() + y + 1);
    }
    else {
        std::copy(order->begin(), order->begin() + y, tmp->begin());
        std::copy(order->begin() + y, order->begin() + x, tmp->begin() + y + 1);
        std::copy(order->begin() + x + 1, order->begin() + order->size(), tmp->begin() + x + 1);
    }
    (*tmp)[y] = (*order)[x];

    if (this->tmpOrder != nullptr) {
        delete this->tmpOrder;
    }

    this->tmpOrder = tmp;
}

NeigborhoodTypes InsertNeigborhood::getType()
{
    return NeigborhoodTypes::INSERT;
}

void InsertNeigborhood::draw(std::vector<size_t>* order, WeightedTardiness* problem)
{
    this->changeX = RandomGenerator::getInstance()->getRandom<size_t>(0, order->size() - 1);
    this->changeY = RandomGenerator::getInstance()->getRandom<size_t>(0, order->size() - 1);

    this->insert(this->changeX, this->changeY, order);

    this->loos = problem->getTotalWeightedLoos(this->tmpOrder);
}

unsigned int InsertNeigborhood::getLoos()
{
    return this->loos;
}

void InsertNeigborhood::applyChanges(std::vector<size_t>*& order)
{
    delete order;
    order = this->tmpOrder;
    this->tmpOrder = nullptr;
}

unsigned int InsertNeigborhood::assignComplexity(unsigned int n)
{
    return n * n;
}

void InsertNeigborhood::init()
{
    this->changeX = 0;
    this->changeY = 0;
}

bool InsertNeigborhood::getNext(std::vector<size_t>* order, WeightedTardiness* problem)
{
    this->changeY++;
    if (this->changeY >= order->size()) {
        this->changeY = 0;
        this->changeX++;
    }
    if (this->changeY == this->changeX) {
        if (this->changeX >= order->size() - 1) return false;
        this->changeY++;
    }

    this->insert(this->changeX, this->changeY, order);
    this->loos = problem->getTotalWeightedLoos(this->tmpOrder);

    return true;
}

void InsertNeigborhood::saveCurrent()
{
    this->bestX = this->changeX;
    this->bestY = this->changeY;
}

void InsertNeigborhood::refreaschTabu(std::vector<std::vector<unsigned>>& tabu)
{
    for (size_t x = 0; x < this->tmpOrder->size(); x++) {
        for (size_t y = 0; y < this->tmpOrder->size(); y++) {
            if (tabu[x][y] > 0) tabu[x][y]--;
        }
    }
}

void InsertNeigborhood::increaseTabu(std::vector<std::vector<unsigned>>& tabu, unsigned iters)
{
    tabu[this->bestY][this->bestX] = iters;
}

void InsertNeigborhood::increasePunishment(std::vector<std::vector<unsigned>>& punishment, unsigned punish)
{
    punishment[this->bestX][this->bestY] += punish;
}

unsigned int InsertNeigborhood::getLoosWithPunish(std::vector<std::vector<unsigned>>& punishment)
{
    return this->getLoos() + punishment[this->changeX][this->changeY];
}

void InsertNeigborhood::applyBest(std::vector<size_t>*& order, WeightedTardiness* problem)
{
    this->insert(this->bestX, this->bestY, order);
    delete order;
    order = this->tmpOrder;
    this->tmpOrder = nullptr;
    this->loos = problem->getTotalWeightedLoos(order);
}

bool InsertNeigborhood::notInTabu(std::vector<std::vector<unsigned>>& tabu)
{
    return tabu[this->changeX][this->changeY] == 0;
}

InsertNeigborhood::~InsertNeigborhood()
{
    if (this->tmpOrder != nullptr) {
        delete this->tmpOrder;
    }
}
