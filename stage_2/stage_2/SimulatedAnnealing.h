#pragma once
#include <vector>
#include <chrono>
#include "WeightedTardiness.h"
#include "ANeighborhood.h"
#include "JobsOrder.h"

// klasa odpowiadaj�ca za logik� algorytmu symulowanego wy�a�ania
class SimulatedAnnealing
{
    // maksymalna temperatura
    static double temperatureMinimum;

    // obecnie przetwarzana kolejno�� zada�
    std::vector<size_t>* currentOrder;
    // instancja problemu (dane dotycz�ce zada�, parametr�w)
    WeightedTardiness* problem;
    // aktualna temperatura
    double temperature;
    // ilo�� iteracji przetwarzania jednej temperatury
    unsigned int stepsize;

    // czas rozpocz�cia (dla kryterium stopu)
    std::chrono::high_resolution_clock::time_point start;
    // obecnie przetwarzane najlepsze wa�one op�nienie
    unsigned int currentBestLoos;
    // s�siedztwo z kt�rego algorytm korzysta (polimorfizm)
    ANeighborhood* neighborhood;

    // ustawienie pierwszej temperatury
    void setFirstTemperature();
    // wyliczenie temperatury kolejnych iteracji
    void setNextTemperature();
    // test probabilistyczny, czy obecne op�nienie powinno zosta� zaakceptowane
    bool shouldAssignCurrent(unsigned int loos);
public:
    // najlepszy znaleziony wynik
    JobsOrder* bestOrder;

    SimulatedAnnealing(WeightedTardiness* problem);

    // p�tla g��wna algorytmu
    void run();

    ~SimulatedAnnealing();
};

