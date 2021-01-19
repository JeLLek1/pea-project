#include "ExchangeNeighborhood.h"
#include "RandomGenerator.h"
#include "WeightedTardiness.h"

void ExchangeNeighborhood::swap(size_t x, size_t y)
{
    size_t tmp = (*this->tmpOrder)[x];
    (*this->tmpOrder)[x] = (*this->tmpOrder)[y];
    (*this->tmpOrder)[y] = tmp;
}

NeigborhoodTypes ExchangeNeighborhood::getType()
{
    return NeigborhoodTypes::EXCHANGE;
}

void ExchangeNeighborhood::draw(std::vector<size_t>* order, WeightedTardiness* problem)
{
    if (this->tmpOrder != nullptr) {
        delete this->tmpOrder;
    }
    this->tmpOrder = new std::vector<size_t>(*order);

    this->changeX = RandomGenerator::getInstance()->getRandom<size_t>(0, order->size() - 1);
    this->changeY = RandomGenerator::getInstance()->getRandom<size_t>(this->changeX, order->size() - 1);

    this->swap(this->changeX, this->changeY);

    this->loos = problem->getTotalWeightedLoos(this->tmpOrder);
}

unsigned int ExchangeNeighborhood::getLoos()
{
    return this->loos;
}

void ExchangeNeighborhood::applyChanges(std::vector<size_t>*& order)
{
    delete order;
    order = this->tmpOrder;
    this->tmpOrder = nullptr;
}

unsigned int ExchangeNeighborhood::assignComplexity(unsigned int n)
{
    return n * n;
}

void ExchangeNeighborhood::init()
{
    this->changeX = 0;
    this->changeY = 0;
}

bool ExchangeNeighborhood::getNext(std::vector<size_t>* order, WeightedTardiness* problem)
{
    this->changeY++;
    if (this->changeY >= order->size()) {
        this->changeX++;
        this->changeY = this->changeX + 1;
    }
    if (this->changeX >= order->size() - 1) return false;

    if (this->tmpOrder != nullptr) {
        delete this->tmpOrder;
    }
    this->tmpOrder = new std::vector<size_t>(*order);
    this->swap(this->changeX, this->changeY);
    this->loos = problem->getTotalWeightedLoos(this->tmpOrder);
    return true;
}

void ExchangeNeighborhood::saveCurrent()
{
    this->bestX = this->changeX;
    this->bestY = this->changeY;
}

void ExchangeNeighborhood::refreaschTabu(std::vector<std::vector<unsigned>>& tabu)
{
    for (size_t x = 0; x < this->tmpOrder->size() - 1; x++) {
        for (size_t y = x + 1; y < this->tmpOrder->size(); y++) {
            if (tabu[x][y] > 0) tabu[x][y]--;
        }
    }
}

void ExchangeNeighborhood::increaseTabu(std::vector<std::vector<unsigned>>& tabu, unsigned iters)
{
    tabu[this->bestX][this->bestY] = iters;
}

void ExchangeNeighborhood::increasePunishment(std::vector<std::vector<unsigned>>& punishment, unsigned punish)
{
    punishment[this->bestX][this->bestY] += punish;
}

unsigned int ExchangeNeighborhood::getLoosWithPunish(std::vector<std::vector<unsigned>>& punishment)
{
    return this->getLoos() + punishment[this->changeX][this->changeY];
}

void ExchangeNeighborhood::applyBest(std::vector<size_t>*& order, WeightedTardiness* problem)
{
    if (this->tmpOrder != nullptr) {
        delete this->tmpOrder;
    }
    this->tmpOrder = new std::vector<size_t>(*order);
    this->swap(this->bestX, this->bestY);
    delete order;
    order = this->tmpOrder;
    this->tmpOrder = nullptr;
    this->loos = problem->getTotalWeightedLoos(order);
}

bool ExchangeNeighborhood::notInTabu(std::vector<std::vector<unsigned>>& tabu)
{
    return tabu[this->changeX][this->changeY] == 0;
}

void ExchangeNeighborhood::punischClear(std::vector<std::vector<unsigned>>& punishment)
{
    for (size_t x = 0; x < punishment.size() - 1; x++) {
        std::fill(punishment[x].begin()+ x + 1, punishment[x].end(), 0);
    }
}

ExchangeNeighborhood::~ExchangeNeighborhood()
{
    if (this->tmpOrder != nullptr) {
        delete this->tmpOrder;
    }
}
