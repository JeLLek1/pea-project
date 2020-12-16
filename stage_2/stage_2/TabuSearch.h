#pragma once
#include <vector>
#include <chrono>
#include "WeightedTardiness.h"
#include "ANeighborhood.h"
#include "JobsOrder.h"

// klasa odpowiedzialna za dzia³anie algorytmu przeszukiwania z zakazami
class TabuSearch
{
    // Przy dywersyfikacji po ilu pogarszaj¹cych przejœciach ma wylosowaæ kolejne rozwi¹zanie 
    unsigned randAfterIters;
    // iloœæ iteracji pogarszaj¹cych wynik
    unsigned itersWithoutImprovement = 0;

    // obecnie przetwarzana kolejnoœæ zadañ (dla której bêd¹ przetwarzane s¹siedztwa)
    std::vector<size_t>* currentOrder;
    // instancja problemu przechowuj¹ca parametry zadañ i algorytmu
    WeightedTardiness* problem;

    // czas rozpoczêscia algorytmu dla kryterium stopu
    std::chrono::high_resolution_clock::time_point start;
    // najlepsze opóŸnienie lokalne
    unsigned int currentBestLoos;
    // s¹siedztwo u¿ywane w algorytmie ( polimorfizm ) 
    ANeighborhood* neighborhood;

    // lista tabu
    std::vector<std::vector<unsigned>> tabu;
    // iloœæ iteracji przez które zadanie bedzie w liœcie tabu
    unsigned tabuTime;
    // lista kar za przejœcia które nie przynosi³y zysku (dywersyfikacja)
    std::vector<std::vector<unsigned>> punishment;
    // kara za przejœcie z pogorszeniem
    unsigned punish;
public:
    // najlepszy znaleziony dot¹d wynik
    JobsOrder* bestOrder;

    TabuSearch(WeightedTardiness* problem);
    
    // algorytm bez dywersyfikacji
    void run();
    // algorytm z dywersyfikacj¹
    void runDiversifi();

    ~TabuSearch();
};

