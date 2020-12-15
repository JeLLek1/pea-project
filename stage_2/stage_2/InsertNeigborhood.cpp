#include "InsertNeigborhood.h"
#include "WeightedTardiness.h"
#include "RandomGenerator.h"

NeigborhoodTypes InsertNeigborhood::getType()
{
    return NeigborhoodTypes::INSERT;
}

void InsertNeigborhood::draw(std::vector<size_t>* order, WeightedTardiness* problem)
{
    if (this->tmpOrder != nullptr) {
        delete this->tmpOrder;
    }

    this->changeX = RandomGenerator::getInstance()->getRandom<size_t>(0, order->size() - 1);
    this->changeY = RandomGenerator::getInstance()->getRandom<size_t>(0, order->size() - 1);
    
    this->tmpOrder = new std::vector<size_t>(order->size());
    if (this->changeX < this->changeY) {
        std::copy(order->begin(), order->begin() + this->changeX, this->tmpOrder->begin());
        std::copy(order->begin() + this->changeX + 1, order->begin() + this->changeY + 1, this->tmpOrder->begin() + this->changeX);
        std::copy(order->begin() + this->changeY + 1, order->begin() + order->size(), this->tmpOrder->begin() + this->changeY + 1);
    } else {
        std::copy(order->begin(), order->begin() + this->changeY, this->tmpOrder->begin());
        std::copy(order->begin() + this->changeY, order->begin() + this->changeX, this->tmpOrder->begin() + this->changeY + 1);
        std::copy(order->begin() + this->changeX + 1, order->begin() + order->size(), this->tmpOrder->begin() + this->changeX + 1);
    }
    (*this->tmpOrder)[this->changeY] = (*order)[this->changeX];

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
    return n*n;
}
