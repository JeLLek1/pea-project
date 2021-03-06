#include "StateTests.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "App.h"
#include "StateLoadFile.h"
#include "ANeighborhood.h"
#include "ExchangeNeighborhood.h"
#include "InsertNeigborhood.h"
#include "SimulatedAnnealing.h"
#include "TabuSearch.h"

//reset czasu
void StateTests::resetTimer()
{
    this->start = std::chrono::high_resolution_clock::now();
}
//czas od ostatniego restartu
long long StateTests::returnTime()
{
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - this->start).count();
}

bool StateTests::loadFile(std::string filename)
{
    this->results = new std::list<Result*>;
    //otwarcie pliku o podanej nazwie
    std::fstream file = std::fstream(filename, std::ios::in);
    //b��d je�eli nie uda�o si� otworzy�
    if (!file.is_open()) {
        std::cout << std::endl << "Nie udalo sie otworzyc pliku!";
        return false;
    }
    std::string line;
    std::istringstream is_ss;
    while (!file.eof()) {
        //pobranie linii
        std::getline(file, line);
        //b��d podczas pobierania linii
        if (file.fail() || line.empty()) {
            break;
        }
        is_ss = std::istringstream(line);
        // pobieranie indeksu zadania
        unsigned int index;
        is_ss >> index;
        //b�ad pobierania
        if (is_ss.fail()) {
            continue;
        }
        //pobieranie priorytetu zadania
        unsigned int tardiness;
        is_ss >> tardiness;
        //b��d pobierania
        if (is_ss.fail()) {
            continue;
        }
        Result* current = new Result;
        current->nr = index;
        current->tardiness = tardiness;
        this->results->push_back(current);
    }

    return true;
}

void StateTests::process()
{
    WeightedTardiness* problem = App::getInstance()->getWeightedTardiness();
    bool canBeRuuded = true;
    if (problem->getStopSeconds() < 1) {
        std::cout << "Nalezy najpierw wprowadzic kryterium stopu\n";
        canBeRuuded = false;
    }

    if (canBeRuuded) {
        std::cout << "\nKryterium stopu: " << problem->getStopSeconds();
        std::cout << "\nPodaj nazwe pliku rozwiazan: ";
        std::string fileName;
        std::getline(std::cin, fileName);
        if (this->loadFile(fileName)) {
            std::cout << std::endl << "Pomyslnie zakonczono wczytywanie pliku";
            std::cout << "Podaj nazwe plikow problemow [np instances\\wt_40_]";
            std::cout << "\nDo nazwy pliku zostanie doklejone xxx.txt gdzie xxx to numer zadania: ";
            std::getline(std::cin, this->nameProblems);
            unsigned errorNr = this->runAlgorithms();
            if (errorNr > 0) {
                std::cout << "\nWystapil problem podczas wczytywania problemu " << errorNr;
            } else {
                std::cout << "\nZakonczono testy algorytmow";
            }
        }
        else {
            std::cout << std::endl << "Wczytywanie pliku z wynikami zakonczone niepowodzeniem";
        }
    }
    std::cout << "\n\nNacisnij dowolny przycisk by powrocic...";
}

bool StateTests::handleInput(char key)
{
    return false;
}

// uruchamianie algorytm�w wed�ug podanych danych i przedstawianie wynik�w
// w formacie csv (Wystarczy skopiowa� do pliku i wczyta� przez arkusz kalkulacyjny)
unsigned StateTests::runAlgorithms()
{
    WeightedTardiness* problem = App::getInstance()->getWeightedTardiness();

    // przechowanie typu s�siedztwa
    ANeighborhood* tmpNeighborhood = problem->getNeighborhood();
    std::vector< ANeighborhood*> testNeighborhoods = { new ExchangeNeighborhood, new InsertNeigborhood};
    long long time = 0;
    SimulatedAnnealing* sa;
    TabuSearch* ts;
    //dla ka�dego typu s�siedztwa
    for (auto neigbor : testNeighborhoods) {
        problem->setNeighborhood(neigbor);
        // testy Sumulowania Wy�a�ania
        std::cout << "\n\nuruchamianie testow SA, sasiedztwo: " << ANeighborhood::typeNames.at(neigbor->getType());
        std::cout << "\nnr;najlepszy znaleziony;najlepszy znany;czas [ms];blad wzgledny";
        for (auto const& i : (*this->results)) {
            std::string filename = std::to_string(i->nr);
            filename = std::string(3 - filename.length(), '0') + filename + ".txt";
            if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
                return i->nr;
            }
            this->resetTimer();
            sa = new SimulatedAnnealing(problem);
            sa->run();
            time = this->returnTime();
            std::cout << std::fixed << "\n" << i->nr << ";"
                << sa->bestOrder->totalLoos << ";"
                << i->tardiness << ";"
                << static_cast<double>(time) * 0.001 << ";"
                << std::abs(static_cast<double>(sa->bestOrder->totalLoos - i->tardiness)) / i->tardiness;
            if (sa->bestOrder->totalLoos < i->tardiness) std::cout << "; lepszy";
            delete sa;
        }

        // testy Tabu Search bez dywersyfikacji
        std::cout << "\n\nuruchamianie testow TS z dywersyfikacja, sasiedztwo: " << ANeighborhood::typeNames.at(neigbor->getType());
        std::cout << "\nnr;najlepszy znaleziony;najlepszy znany;czas [ms];blad wzgledny";
        for (auto const& i : (*this->results)) {
            std::string filename = std::to_string(i->nr);
            filename = std::string(3 - filename.length(), '0') + filename + ".txt";
            if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
                return i->nr;
            }
            this->resetTimer();
            ts = new TabuSearch(problem);
            ts->runDiversifi();
            time = this->returnTime();

            std::cout << std::fixed << "\n" << i->nr << ";"
                << ts->bestOrder->totalLoos << ";"
                << i->tardiness << ";"
                << static_cast<double>(time) * 0.001 << ";"
                << std::abs(static_cast<double>(ts->bestOrder->totalLoos - i->tardiness)) / i->tardiness;

            if (ts->bestOrder->totalLoos < i->tardiness) std::cout << "; lepszy";
            delete ts;
        }

        // testy Tabu Search z dywersyfikacj�
        std::cout << "\n\nuruchamianie testow TS bez dywersyfikacji, sasiedztwo: " << ANeighborhood::typeNames.at(neigbor->getType());
        std::cout << "\nnr;najlepszy znaleziony;najlepszy znany;czas [ms];blad wzgledny";
        for (auto const& i : (*this->results)) {
            std::string filename = std::to_string(i->nr);
            filename = std::string(3 - filename.length(), '0') + filename + ".txt";
            if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
                return i->nr;
            }

            this->resetTimer();
            ts = new TabuSearch(problem);
            ts->run();
            time = this->returnTime();

            std::cout << std::fixed << "\n" << i->nr << ";"
                << ts->bestOrder->totalLoos << ";"
                << i->tardiness << ";"
                << static_cast<double>(time) * 0.001 << ";"
                << std::abs(static_cast<double>(ts->bestOrder->totalLoos - i->tardiness)) / i->tardiness;

            if (ts->bestOrder->totalLoos < i->tardiness) std::cout << "; lepszy";
            delete ts;
        }
    }
    problem->setNeighborhood(nullptr);
    return 0;
}

StateTests::~StateTests()
{
    if (this->results == nullptr) {
        return;
    }

    for (auto const& i : (*this->results)) {
        delete i;
    }
    delete this->results;
}
