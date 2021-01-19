#pragma once
#include "ANeighborhood.h"

// klasa s�siedztwa typu zamiany element�w miedzy sob�
// opis dziedziczonych metod znajduje si� w klasie ANeighborhood
class ExchangeNeighborhood : public ANeighborhood
{
    // obecnie przetwarzany s�siad
    size_t changeX = 0, changeY = 0;

    // przechowywane wa�one op�nienie obecnego s�siada
    unsigned int loos = UINT_MAX;
    // przechowywanie kolejno�ci obecnego s�siada
    std::vector<size_t>* tmpOrder = nullptr;

    // specyficzne dla TS (najlepszy dot�d znaleziony s�siad)
    size_t bestX = 0, bestY = 0;

    // zamiana na indeksach x i y element�w w tmpOrder
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

