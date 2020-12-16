#pragma once
#include <vector>
#include <chrono>
#include "WeightedTardiness.h"
#include "ANeighborhood.h"
#include "JobsOrder.h"

// klasa odpowiadaj¹ca za logikê algorytmu symulowanego wy¿a¿ania
class SimulatedAnnealing
{
    // maksymalna temperatura
    static double temperatureMinimum;

    // obecnie przetwarzana kolejnoœæ zadañ
    std::vector<size_t>* currentOrder;
    // instancja problemu (dane dotycz¹ce zadañ, parametrów)
    WeightedTardiness* problem;
    // aktualna temperatura
    double temperature;
    // iloœæ iteracji przetwarzania jednej temperatury
    unsigned int stepsize;

    // czas rozpoczêcia (dla kryterium stopu)
    std::chrono::high_resolution_clock::time_point start;
    // obecnie przetwarzane najlepsze wa¿one opóŸnienie
    unsigned int currentBestLoos;
    // s¹siedztwo z którego algorytm korzysta (polimorfizm)
    ANeighborhood* neighborhood;

    // ustawienie pierwszej temperatury
    void setFirstTemperature();
    // wyliczenie temperatury kolejnych iteracji
    void setNextTemperature();
    // test probabilistyczny, czy obecne opóŸnienie powinno zostaæ zaakceptowane
    bool shouldAssignCurrent(unsigned int loos);
public:
    // najlepszy znaleziony wynik
    JobsOrder* bestOrder;

    SimulatedAnnealing(WeightedTardiness* problem);

    // pêtla g³ówna algorytmu
    void run();

    ~SimulatedAnnealing();
};

