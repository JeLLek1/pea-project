#pragma once
#include "ANeighborhood.h"

// klasa s¹siedztwa typu zamiany elementów miedzy sob¹
// opis dziedziczonych metod znajduje siê w klasie ANeighborhood
class ExchangeNeighborhood : public ANeighborhood
{
    // obecnie przetwarzany s¹siad
    size_t changeX = 0, changeY = 0;

    // przechowywane wa¿one opóŸnienie obecnego s¹siada
    unsigned int loos = UINT_MAX;
    // przechowywanie kolejnoœci obecnego s¹siada
    std::vector<size_t>* tmpOrder = nullptr;

    // specyficzne dla TS (najlepszy dot¹d znaleziony s¹siad)
    size_t bestX = 0, bestY = 0;

    // zamiana na indeksach x i y elementów w tmpOrder
    void swap(size_t x, size_t y);
public:
    virtual NeigborhoodTypes getType();
    virtual unsigned int getLoos();

    // specyficzne dla SA
    virtual void draw(std::vector<size_t>* order, WeightedTardiness* problem);
    virtual void applyChanges(std::vector<size_t>*& order);
    virtual unsigned int assignComplexity(unsigned int n);

    // specuficzne dla TS
    virtual void init();
    virtual bool getNext(std::vector<size_t>* order, WeightedTardiness* problem);
    virtual void saveCurrent();
    virtual void refreaschTabu(std::vector<std::vector<unsigned>>& tabu);
    virtual void increaseTabu(std::vector<std::vector<unsigned>>& tabu, unsigned iters);
    virtual void increasePunishment(std::vector<std::vector<unsigned>>& punishment, unsigned punish);
    virtual unsigned int getLoosWithPunish(std::vector<std::vector<unsigned>>& punishment);
    virtual void applyBest(std::vector<size_t>*& order, WeightedTardiness* problem);
    virtual bool notInTabu(std::vector<std::vector<unsigned>>& tabu);
    virtual void punischClear(std::vector<std::vector<unsigned>>& punishment);

    ~ExchangeNeighborhood();
};

