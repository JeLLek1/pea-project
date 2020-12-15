#include "ExchangeNeighborhood.h"
#include "RandomGenerator.h"
#include "WeightedTardiness.h"

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

    this->changeX = RandomGenerator::getInstance()->getRandom<size_t>(0, order->size()-1);
    this->changeY = RandomGenerator::getInstance()->getRandom<size_t>(this->changeX, order->size()-1);
    size_t tmp = (*this->tmpOrder)[this->changeX];
    (*this->tmpOrder)[this->changeX] = (*order)[this->changeY];
    (*this->tmpOrder)[this->changeY] = tmp;

    this->loos = problem->getTotalWeightedLoos(this->tmpOrder);
}

unsigned int ExchangeNeighborhood::getLoos()
{
    return this->loos;
}

void ExchangeNeighborhood::applyChanges(std::vector<size_t>* &order)
{
    delete order;
    order = this->tmpOrder;
    this->tmpOrder = nullptr;
}

unsigned int ExchangeNeighborhood::assignComplexity(unsigned int n)
{
    return n*n;
}
