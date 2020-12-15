#pragma once
#include "ANeighborhood.h"

class InsertNeigborhood : public ANeighborhood
{
    size_t changeX = 0, changeY = 0;

    unsigned int loos = UINT_MAX;
    std::vector<size_t>* tmpOrder = nullptr;

    // specyficzne dla TS
    size_t bestX = 0, bestY = 0;
public:
    virtual NeigborhoodTypes getType();
    virtual unsigned int getLoos();

    // specyficzne dla SA
    virtual void draw(std::vector<size_t>* order, WeightedTardiness* problem);
    virtual void applyChanges(std::vector<size_t>* &order);
    virtual unsigned int assignComplexity(unsigned int n);

};

