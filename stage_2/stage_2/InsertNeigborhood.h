#pragma once
#include "ANeighborhood.h"
// klasa implementacji s�siedztwa typu wstawienia
// (pobranie elementu o podanym indeksie i wstawienie go w miejsce innego indeksu, zadania pomi�dzy s� przesuni�te)
class InsertNeigborhood : public ANeighborhood
{
    // obecnie przetwarzany s�siad
    size_t changeX = 0, changeY = 0;

    // wa�one op�nienie obecnie przetwarzanego s�siada
    unsigned int loos = UINT_MAX;
    // kolejno�� obecnie przetwarzanego s�siada
    std::vector<size_t>* tmpOrder = nullptr;

    // specyficzne dla TS (najlepszy dot�d znaleziony s�siad)
    size_t bestX = 0, bestY = 0;

    // wykonanie operacj przeniesienia elementu o podanym indeksie x do indeksu y
    void insert(size_t x, size_t y, std::vector<size_t>* order);
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

    ~InsertNeigborhood();
};

