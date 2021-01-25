#include "StateTests.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "App.h"
#include "StateLoadFile.h"
#include "GeneticAlgorithm.h"

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
    //b³¹d je¿eli nie uda³o siê otworzyæ
    if (!file.is_open()) {
        std::cout << std::endl << "Nie udalo sie otworzyc pliku!";
        return false;
    }
    std::string line;
    std::istringstream is_ss;
    while (!file.eof()) {
        //pobranie linii
        std::getline(file, line);
        //b³¹d podczas pobierania linii
        if (file.fail() || line.empty()) {
            break;
        }
        is_ss = std::istringstream(line);
        // pobieranie indeksu zadania
        unsigned int index;
        is_ss >> index;
        //b³ad pobierania
        if (is_ss.fail()) {
            continue;
        }
        //pobieranie priorytetu zadania
        unsigned int tardiness;
        is_ss >> tardiness;
        //b³¹d pobierania
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

    std::cout << "\nPodaj nazwe pliku rozwiazan: ";
    std::string fileName;
    std::getline(std::cin, fileName);
    if (this->loadFile(fileName)) {
        std::cout << std::endl << "Pomyslnie zakonczono wczytywanie pliku";
        std::cout << "Podaj nazwe plikow problemow [np instances\\wt_40_]";
        std::cout << "\nDo nazwy pliku zostanie doklejone xxx.txt gdzie xxx to numer zadania: ";
        std::getline(std::cin, this->nameProblems);
        unsigned errorNr = this->runAlgorithms();

        std::cout << "\nZakonczono testy algorytmow";

    }  else {
        std::cout << std::endl << "Wczytywanie pliku z wynikami zakonczone niepowodzeniem";
    }
    std::cout << "\n\nNacisnij dowolny przycisk by powrocic...";
}

bool StateTests::handleInput(char key)
{
    return false;
}

void StateTests::populationTests()
{
    WeightedTardiness* problem = App::getInstance()->getWeightedTardiness();

    unsigned times[] = { 1, 2, 5, 10, 20, 30 };
    unsigned population[] = { 20, 100, 600 };

    std::cout << "Test wielkosci populacji:\n";
    problem->crossFunction = GeneticAlgorithm::PMX;
    problem->mutationFunction = GeneticAlgorithm::insertMutation;
    std::cout << "\nKrzyzowanie PMX mutacja insertion:\n";
    std::cout << "lp;opt";
    for (unsigned p = 0; p < sizeof(population) / sizeof(unsigned); p++) {
        for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
            std::cout << ";pop-" << population[p] << " time-" << times[t];
        }
    }
    std::cout << "\n";
    for (auto const& item : (*this->results)) {
        std::string filename = std::to_string(item->nr);
        filename = std::string(3 - filename.length(), '0') + filename + ".txt";
        if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
            return;
        }
        std::cout << item->nr << ";" << item->tardiness;
        for (unsigned p = 0; p < sizeof(population) / sizeof(unsigned); p++) {
            problem->populationSize = population[p];
            GeneticAlgorithm algorithm(problem);
            for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
                problem->stopSeconds = times[t];
                algorithm.runAlgorithm();
                std::cout << ";" << algorithm.best->totalLoos;
            }
        }
        std::cout << "\n";
    }


    problem->mutationFunction = GeneticAlgorithm::transpositionMutation;
    problem->crossFunction = GeneticAlgorithm::PMX;
    std::cout << "\nKrzyzowanie PMX mutacja transposiotion:\n";
    std::cout << "lp;opt";
    for (unsigned p = 0; p < sizeof(population) / sizeof(unsigned); p++) {
        for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
            std::cout << ";pop-" << population[p] << " time-" << times[t];
        }
    }
    std::cout << "\n";
    for (auto const& item : (*this->results)) {
        std::string filename = std::to_string(item->nr);
        filename = std::string(3 - filename.length(), '0') + filename + ".txt";
        if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
            return;
        }
        std::cout << item->nr << ";" << item->tardiness;
        for (unsigned p = 0; p < sizeof(population) / sizeof(unsigned); p++) {
            problem->populationSize = population[p];
            GeneticAlgorithm algorithm(problem);
            for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
                problem->stopSeconds = times[t];
                algorithm.runAlgorithm();
                std::cout << ";" << algorithm.best->totalLoos;
            }
        }
        std::cout << "\n";
    }

    problem->crossFunction = GeneticAlgorithm::OX;
    problem->mutationFunction = GeneticAlgorithm::insertMutation;
    std::cout << "\nKrzyzowanie OX mutacja insertion:\n";
    std::cout << "lp;opt";
    for (unsigned p = 0; p < sizeof(population) / sizeof(unsigned); p++) {
        for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
            std::cout << ";pop-" << population[p] << " time-" << times[t];
        }
    }
    std::cout << "\n";
    for (auto const& item : (*this->results)) {
        std::string filename = std::to_string(item->nr);
        filename = std::string(3 - filename.length(), '0') + filename + ".txt";
        if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
            return;
        }
        std::cout << item->nr << ";" << item->tardiness;
        for (unsigned p = 0; p < sizeof(population) / sizeof(unsigned); p++) {
            problem->populationSize = population[p];
            GeneticAlgorithm algorithm(problem);
            for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
                problem->stopSeconds = times[t];
                algorithm.runAlgorithm();
                std::cout << ";" << algorithm.best->totalLoos;
            }
        }
        std::cout << "\n";
    }

    problem->mutationFunction = GeneticAlgorithm::transpositionMutation;
    problem->crossFunction = GeneticAlgorithm::OX;
    std::cout << "\nKrzyzowanie OX mutacja transposiotion:\n";
    std::cout << "lp;opt";
    for (unsigned p = 0; p < sizeof(population) / sizeof(unsigned); p++) {
        for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
            std::cout << ";pop-" << population[p] << " time-" << times[t];
        }
    }
    std::cout << "\n";
    for (auto const& item : (*this->results)) {
        std::string filename = std::to_string(item->nr);
        filename = std::string(3 - filename.length(), '0') + filename + ".txt";
        if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
            return;
        }
        std::cout << item->nr << ";" << item->tardiness;
        for (unsigned p = 0; p < sizeof(population) / sizeof(unsigned); p++) {
            problem->populationSize = population[p];
            GeneticAlgorithm algorithm(problem);
            for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
                problem->stopSeconds = times[t];
                algorithm.runAlgorithm();
                std::cout << ";" << algorithm.best->totalLoos;
            }
        }
        std::cout << "\n";
    }
}

void StateTests::mutateTests()
{
    WeightedTardiness* problem = App::getInstance()->getWeightedTardiness();

    unsigned times[] = { 1, 2, 5, 10, 20, 30 };
    float mutateRate[] = { 0.01, 0.05, 0.1 };
    problem->crossoverRatio = 0.8;
    problem->populationSize = 100;

    std::cout << "Test wspó³czynnika mutacji:\n";
    problem->crossFunction = GeneticAlgorithm::PMX;
    problem->mutationFunction = GeneticAlgorithm::insertMutation;
    std::cout << "\nKrzyzowanie PMX mutacja insertion:\n";
    std::cout << "lp;opt";
    for (unsigned p = 0; p < sizeof(mutateRate) / sizeof(unsigned); p++) {
        for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
            std::cout << ";mRate-" << mutateRate[p] << " time-" << times[t];
        }
    }
    std::cout << "\n";
    for (auto const& item : (*this->results)) {
        std::string filename = std::to_string(item->nr);
        filename = std::string(3 - filename.length(), '0') + filename + ".txt";
        if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
            return;
        }
        std::cout << item->nr << ";" << item->tardiness;
        for (unsigned p = 0; p < sizeof(mutateRate) / sizeof(unsigned); p++) {
            problem->mutationRatio = mutateRate[p];
            GeneticAlgorithm algorithm(problem);
            for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
                problem->stopSeconds = times[t];
                algorithm.runAlgorithm();
                std::cout << ";" << algorithm.best->totalLoos;
            }
        }
        std::cout << "\n";
    }


    problem->mutationFunction = GeneticAlgorithm::transpositionMutation;
    problem->crossFunction = GeneticAlgorithm::PMX;
    std::cout << "\nKrzyzowanie PMX mutacja transposiotion:\n";
    std::cout << "lp;opt";
    for (unsigned p = 0; p < sizeof(mutateRate) / sizeof(unsigned); p++) {
        for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
            std::cout << ";mRate-" << mutateRate[p] << " time-" << times[t];
        }
    }
    std::cout << "\n";
    for (auto const& item : (*this->results)) {
        std::string filename = std::to_string(item->nr);
        filename = std::string(3 - filename.length(), '0') + filename + ".txt";
        if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
            return;
        }
        std::cout << item->nr << ";" << item->tardiness;
        for (unsigned p = 0; p < sizeof(mutateRate) / sizeof(unsigned); p++) {
            problem->mutationRatio = mutateRate[p];
            GeneticAlgorithm algorithm(problem);
            for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
                problem->stopSeconds = times[t];
                algorithm.runAlgorithm();
                std::cout << ";" << algorithm.best->totalLoos;
            }
        }
        std::cout << "\n";
    }

    problem->crossFunction = GeneticAlgorithm::OX;
    problem->mutationFunction = GeneticAlgorithm::insertMutation;
    std::cout << "\nKrzyzowanie OX mutacja insertion:\n";
    std::cout << "lp;opt";
    for (unsigned p = 0; p < sizeof(mutateRate) / sizeof(unsigned); p++) {
        for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
            std::cout << ";mRate-" << mutateRate[p] << " time-" << times[t];
        }
    }
    std::cout << "\n";
    for (auto const& item : (*this->results)) {
        std::string filename = std::to_string(item->nr);
        filename = std::string(3 - filename.length(), '0') + filename + ".txt";
        if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
            return;
        }
        std::cout << item->nr << ";" << item->tardiness;
        for (unsigned p = 0; p < sizeof(mutateRate) / sizeof(unsigned); p++) {
            problem->mutationRatio = mutateRate[p];
            GeneticAlgorithm algorithm(problem);
            for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
                problem->stopSeconds = times[t];
                algorithm.runAlgorithm();
                std::cout << ";" << algorithm.best->totalLoos;
            }
        }
        std::cout << "\n";
    }

    problem->mutationFunction = GeneticAlgorithm::transpositionMutation;
    problem->crossFunction = GeneticAlgorithm::OX;
    std::cout << "\nKrzyzowanie OX mutacja transposiotion:\n";
    std::cout << "lp;opt";
    for (unsigned p = 0; p < sizeof(mutateRate) / sizeof(unsigned); p++) {
        for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
            std::cout << ";mRate-" << mutateRate[p] << " time-" << times[t];
        }
    }
    std::cout << "\n";
    for (auto const& item : (*this->results)) {
        std::string filename = std::to_string(item->nr);
        filename = std::string(3 - filename.length(), '0') + filename + ".txt";
        if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
            return;
        }
        std::cout << item->nr << ";" << item->tardiness;
        for (unsigned p = 0; p < sizeof(mutateRate) / sizeof(unsigned); p++) {
            problem->mutationRatio = mutateRate[p];
            GeneticAlgorithm algorithm(problem);
            for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
                problem->stopSeconds = times[t];
                algorithm.runAlgorithm();
                std::cout << ";" << algorithm.best->totalLoos;
            }
        }
        std::cout << "\n";
    }

}

void StateTests::crossTest()
{
    WeightedTardiness* problem = App::getInstance()->getWeightedTardiness();

    unsigned times[] = { 1, 2, 5, 10, 20, 30 };
    float crossRate[] = { 0.5, 0.7, 0.9 };
    problem->mutationRatio = 0.01;
    problem->populationSize = 100;

    std::cout << "Test wspó³czynnika mutacji:\n";
    problem->crossFunction = GeneticAlgorithm::PMX;
    problem->mutationFunction = GeneticAlgorithm::insertMutation;
    std::cout << "\nKrzyzowanie PMX mutacja insertion:\n";
    std::cout << "lp;opt";
    for (unsigned p = 0; p < sizeof(crossRate) / sizeof(unsigned); p++) {
        for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
            std::cout << ";cRate-" << crossRate[p] << " time-" << times[t];
        }
    }
    std::cout << "\n";
    for (auto const& item : (*this->results)) {
        std::string filename = std::to_string(item->nr);
        filename = std::string(3 - filename.length(), '0') + filename + ".txt";
        if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
            return;
        }
        std::cout << item->nr << ";" << item->tardiness;
        for (unsigned p = 0; p < sizeof(crossRate) / sizeof(unsigned); p++) {
            problem->crossoverRatio = crossRate[p];
            GeneticAlgorithm algorithm(problem);
            for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
                problem->stopSeconds = times[t];
                algorithm.runAlgorithm();
                std::cout << ";" << algorithm.best->totalLoos;
            }
        }
        std::cout << "\n";
    }


    problem->mutationFunction = GeneticAlgorithm::transpositionMutation;
    problem->crossFunction = GeneticAlgorithm::PMX;
    std::cout << "\nKrzyzowanie PMX mutacja transposiotion:\n";
    std::cout << "lp;opt";
    for (unsigned p = 0; p < sizeof(crossRate) / sizeof(unsigned); p++) {
        for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
            std::cout << ";cRate-" << crossRate[p] << " time-" << times[t];
        }
    }
    std::cout << "\n";
    for (auto const& item : (*this->results)) {
        std::string filename = std::to_string(item->nr);
        filename = std::string(3 - filename.length(), '0') + filename + ".txt";
        if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
            return;
        }
        std::cout << item->nr << ";" << item->tardiness;
        for (unsigned p = 0; p < sizeof(crossRate) / sizeof(unsigned); p++) {
            problem->crossoverRatio = crossRate[p];
            GeneticAlgorithm algorithm(problem);
            for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
                problem->stopSeconds = times[t];
                algorithm.runAlgorithm();
                std::cout << ";" << algorithm.best->totalLoos;
            }
        }
        std::cout << "\n";
    }

    problem->crossFunction = GeneticAlgorithm::OX;
    problem->mutationFunction = GeneticAlgorithm::insertMutation;
    std::cout << "\nKrzyzowanie OX mutacja insertion:\n";
    std::cout << "lp;opt";
    for (unsigned p = 0; p < sizeof(crossRate) / sizeof(unsigned); p++) {
        for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
            std::cout << ";cRate-" << crossRate[p] << " time-" << times[t];
        }
    }
    std::cout << "\n";
    for (auto const& item : (*this->results)) {
        std::string filename = std::to_string(item->nr);
        filename = std::string(3 - filename.length(), '0') + filename + ".txt";
        if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
            return;
        }
        std::cout << item->nr << ";" << item->tardiness;
        for (unsigned p = 0; p < sizeof(crossRate) / sizeof(unsigned); p++) {
            problem->crossoverRatio = crossRate[p];
            GeneticAlgorithm algorithm(problem);
            for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
                problem->stopSeconds = times[t];
                algorithm.runAlgorithm();
                std::cout << ";" << algorithm.best->totalLoos;
            }
        }
        std::cout << "\n";
    }

    problem->mutationFunction = GeneticAlgorithm::transpositionMutation;
    problem->crossFunction = GeneticAlgorithm::OX;
    std::cout << "\nKrzyzowanie OX mutacja transposiotion:\n";
    std::cout << "lp;opt";
    for (unsigned p = 0; p < sizeof(crossRate) / sizeof(unsigned); p++) {
        for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
            std::cout << ";cRate-" << crossRate[p] << " time-" << times[t];
        }
    }
    std::cout << "\n";
    for (auto const& item : (*this->results)) {
        std::string filename = std::to_string(item->nr);
        filename = std::string(3 - filename.length(), '0') + filename + ".txt";
        if (!StateLoadFile::loadFile(this->nameProblems + filename)) {
            return;
        }
        std::cout << item->nr << ";" << item->tardiness;
        for (unsigned p = 0; p < sizeof(crossRate) / sizeof(unsigned); p++) {
            problem->crossoverRatio = crossRate[p];
            GeneticAlgorithm algorithm(problem);
            for (unsigned t = 0; t < sizeof(times) / sizeof(unsigned); t++) {
                problem->stopSeconds = times[t];
                algorithm.runAlgorithm();
                std::cout << ";" << algorithm.best->totalLoos;
            }
        }
        std::cout << "\n";
    }
}

// uruchamianie algorytmów wed³ug podanych danych i przedstawianie wyników
// w formacie csv (Wystarczy skopiowaæ do pliku i wczytaæ przez arkusz kalkulacyjny)
unsigned StateTests::runAlgorithms()
{
    crossTest();
    
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
