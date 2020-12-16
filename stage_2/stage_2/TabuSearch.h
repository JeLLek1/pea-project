#pragma once
#include <vector>
#include <chrono>
#include "WeightedTardiness.h"
#include "ANeighborhood.h"
#include "JobsOrder.h"

// klasa odpowiedzialna za dzia�anie algorytmu przeszukiwania z zakazami
class TabuSearch
{
    // Przy dywersyfikacji po ilu pogarszaj�cych przej�ciach ma wylosowa� kolejne rozwi�zanie 
    unsigned randAfterIters;
    // ilo�� iteracji pogarszaj�cych wynik
    unsigned itersWithoutImprovement = 0;

    // obecnie przetwarzana kolejno�� zada� (dla kt�rej b�d� przetwarzane s�siedztwa)
    std::vector<size_t>* currentOrder;
    // instancja problemu przechowuj�ca parametry zada� i algorytmu
    WeightedTardiness* problem;

    // czas rozpocz�scia algorytmu dla kryterium stopu
    std::chrono::high_resolution_clock::time_point start;
    // najlepsze op�nienie lokalne
    unsigned int currentBestLoos;
    // s�siedztwo u�ywane w algorytmie ( polimorfizm ) 
    ANeighborhood* neighborhood;

    // lista tabu
    std::vector<std::vector<unsigned>> tabu;
    // ilo�� iteracji przez kt�re zadanie bedzie w li�cie tabu
    unsigned tabuTime;
    // lista kar za przej�cia kt�re nie przynosi�y zysku (dywersyfikacja)
    std::vector<std::vector<unsigned>> punishment;
    // kara za przej�cie z pogorszeniem
    unsigned punish;
public:
    // najlepszy znaleziony dot�d wynik
    JobsOrder* bestOrder;

    TabuSearch(WeightedTardiness* problem);
    
    // algorytm bez dywersyfikacji
    void run();
    // algorytm z dywersyfikacj�
    void runDiversifi();

    ~TabuSearch();
};

